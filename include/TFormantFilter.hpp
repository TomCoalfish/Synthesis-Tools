
#pragma once
#include <cmath>
#include <vector>

namespace SoundAlchemy 
{
    enum
    {
        // ids for all visual controls

        kVowelLId = 1,         // formant vowel L
        kVowelRId,             // formant vowel R
        kVowelSyncId,          // formant vowel sync
        kLFOVowelLId,          // formant vowel L LFO rate
        kLFOVowelLDepthId,     // formant vowel L LFO depth
        kLFOVowelRId,          // formant vowel R LFO rate
        kLFOVowelRDepthId,     // formant vowel R LFO depth
        kDistortionTypeId,     // distortion type
        kDriveId,              // distortion drive amount
        kDistortionChainId,    // distortion pre/pos formant mix
        kVuPPMId               // for the Vu value return to host
    };
    enum {
        type_lowpass = 1,
        type_highpass,
        type_bandpass,
        type_notch,
        type_peak,
        type_lowshelf,
        type_highshelf
    };

    template<class T>
    class TFormantFilter : public Object<T>
    {
    public:
        TFormantFilter();
        ~TFormantFilter();

        void prepareToPlay(T sampleRate, int samplesPerBlock);

        T simpleFIRHiPass(T currentSample, T sliderValue);
        T simpleIIRHiPass(T currentSample, T sliderValue);
        T simpleIIRLowPass(T currentSample, T sliderValue);

        void setBiquad(int type, T Freq, T Q, T peakGain);
        T processBiquad(T in);

        T Tick(T in, T A = 1, T F = 0, T P = 0) {
            T fc = frequency;
            T q  = Q;
            setButterworth(type,fc,q);
            T r = A*processButterworth(in);
            setButterworth(type,fx,q);
            return r;
        }
        void setButterworth(int type, T Freq, T Q, T peakGain);
        T processButterworth(T in);
        //Static values, set up in prepare to play.
        int bufferLength;
        int sampleRate;
        T* sn;
        T* cs;

    protected:
        void calcBiquad(void);
        void calcButterworth(void);

        //type of filter
        int type;
        //Coefficient values
        T a0, a1, a2, b1, b2 , c0, c1, c2, d1, d2;
        T frequency, Q, peakGain;
        T z1, z2;

        //Post-process delayed samples y[n]
        T delayedSampleY1;
        T delayedSampleY2;
        //Pre-processed delayed samples x[n]
        T delayedSampleX1;
        T delayedSampleX2;
    };

    template<class T>
    inline T TFormantFilter<T>::processBiquad(T in)
    {
        T out = in * a0 + z1;
        z1 = in * a1 + z2 - b1 * out;
        z2 = in * a2 - b2 * out;
        return out;
    }

    template<class T>
    inline T TFormantFilter<T>::processButterworth(T in)
    {
        T V = pow(10, fabs(peakGain) / 20.0);
        T out = in * a0 + delayedSampleX1 * a1 + delayedSampleX2 * a2 - delayedSampleY1 * b1 - delayedSampleY2 * b2;
        delayedSampleX2 = delayedSampleX1;
        delayedSampleY2 = delayedSampleY1;
        delayedSampleX1 = in;
        delayedSampleY1 = out;

        return out;
    }

    template<class T>
    TFormantFilter<T>::TFormantFilter()
    {
        sampleRate = 0;
        type = type_lowpass;
        a0 = 1.0;
        a1 = a2 = b1 = b2 = 0.0;
        frequency = 20;
        Q = 0.707;
        peakGain = 0.0;
        //Dummy variables to set sin/cos pointers.
        T a = 4;
        T b = 4;
        sn = &a;
        cs = &b;
    }

    template<class T>
    TFormantFilter<T>::~TFormantFilter()
    {
    }

    template<class T>
    void TFormantFilter<T>::prepareToPlay(T sampleRate, int samplesPerBlock)
    {
        this->sampleRate = sampleRate;
        this->bufferLength = samplesPerBlock;
        delayedSampleY1 = 0.0;
        delayedSampleX1 = 0.0;
        delayedSampleY2 = 0.0;
        delayedSampleX2 = 0.0;
    }

    template<class T>
    T TFormantFilter<T>::simpleFIRHiPass(T currentSample, T sliderValue)
    {
        //design equation a0 = a1 - 1.0
        T a0 = sliderValue - 1.0;
        T previousSample = delayedSampleX1;

        T processedSample = a0 * currentSample + sliderValue * previousSample;
        delayedSampleX1 = currentSample;
        return processedSample;
    }

    template<class T>
    T TFormantFilter<T>::simpleIIRLowPass(T currentSample, T sliderValue)
    {
        T previousSample = delayedSampleY1;

        //Should be same thing, Test and remove top if it is
        //T processedSample = (sliderValue * currentSample) + ((1-sliderValue) * previousSample);
        T processedSample = previousSample + sliderValue * (currentSample - previousSample);
        delayedSampleY1 = processedSample;
        return processedSample;
    }

    template<class T>
    void TFormantFilter<T>::setBiquad(int type, T Fc, T Q, T peakGainDB) {
        this->type = type;
        this->Q = Q;
        this->frequency = Fc;
        this->peakGain = peakGainDB;
        calcBiquad();
    }

    template<class T>
    void TFormantFilter<T>::setButterworth(int type, T Fc, T Q, T peakGainDB) {
        this->type = type;
        this->Q = Q;
        this->frequency = Fc;
        this->peakGain = peakGainDB;
        calcButterworth();
    }

    template<class T>
    void TFormantFilter<T>::calcBiquad(void) {
        T norm;
        T V = pow(10, fabs(peakGain) / 20.0);
        T K = tan(M_PI * (frequency / sampleRate));
        switch (this->type) {
        case type_lowpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = K * K * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;

        case type_highpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = 1 * norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;

        case type_bandpass:
            norm = 1 / (1 + K / Q + K * K);
            a0 = K / Q * norm;
            a1 = 0;
            a2 = -a0;
            b1 = 2 * (K * K - 1) * norm;
            b2 = (1 - K / Q + K * K) * norm;
            break;

        case type_notch:
            norm = 1 / (1 + K / Q + K * K);
            a0 = (1 + K * K) * norm;
            a1 = 2 * (K * K - 1) * norm;
            a2 = a0;
            b1 = a1;
            b2 = (1 - K / Q + K * K) * norm;
            break;

        case type_peak:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + 1 / Q * K + K * K);
                a0 = (1 + V / Q * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - V / Q * K + K * K) * norm;
                b1 = a1;
                b2 = (1 - 1 / Q * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (1 + V / Q * K + K * K);
                a0 = (1 + 1 / Q * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - 1 / Q * K + K * K) * norm;
                b1 = a1;
                b2 = (1 - V / Q * K + K * K) * norm;
            }
            break;
        case type_lowshelf:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * K + K * K);
                a0 = (1 + sqrt(2 * V) * K + V * K * K) * norm;
                a1 = 2 * (V * K * K - 1) * norm;
                a2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
                b1 = 2 * (K * K - 1) * norm;
                b2 = (1 - sqrt(2) * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (1 + sqrt(2 * V) * K + V * K * K);
                a0 = (1 + sqrt(2) * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - sqrt(2) * K + K * K) * norm;
                b1 = 2 * (V * K * K - 1) * norm;
                b2 = (1 - sqrt(2 * V) * K + V * K * K) * norm;
            }
            break;
        case type_highshelf:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * K + K * K);
                a0 = (V + sqrt(2 * V) * K + K * K) * norm;
                a1 = 2 * (K * K - V) * norm;
                a2 = (V - sqrt(2 * V) * K + K * K) * norm;
                b1 = 2 * (K * K - 1) * norm;
                b2 = (1 - sqrt(2) * K + K * K) * norm;
            }
            else {    // cut
                norm = 1 / (V + sqrt(2 * V) * K + K * K);
                a0 = (1 + sqrt(2) * K + K * K) * norm;
                a1 = 2 * (K * K - 1) * norm;
                a2 = (1 - sqrt(2) * K + K * K) * norm;
                b1 = 2 * (K * K - V) * norm;
                b2 = (V - sqrt(2 * V) * K + K * K) * norm;
            }
            break;
        }

        return;
    }

    template<class T>
    void TFormantFilter<T>::calcButterworth(void)
    {
        T norm;
        T freqT = 2 * tan(frequency * M_PI / sampleRate);
        T V = pow(10, fabs(peakGain) / 20.0);
        switch (this->type)
        {
        case type_lowpass:
            a0 = (freqT * freqT) / (4 + (2 * sqrt(2) * freqT) + freqT * freqT);
            a1 = 2 * a0;
            a2 = a0;
            b1 = ((2 * freqT * freqT) - 8) / (4 + (2 * sqrt(2) * freqT) + freqT * freqT);
            b2 = (4 - (2 * sqrt(2) * freqT) + freqT * freqT) / (4 + (2 * sqrt(2) * freqT) + freqT * freqT);
            break;
        case type_highpass:
            norm = freqT * freqT / 4 + freqT / sqrt(2) + 1;
            a0 = 1 / norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = ((freqT * freqT) / 2 - 2) / norm;
            b2 = ((freqT * freqT) / 4 - (freqT / sqrt(2)) + 1) / norm;
            break;
        }        
    }

    template<class T>
    T TFormantFilter<T>::simpleIIRHiPass(T currentSample, T sliderValue)
    {
        T a0 = sliderValue - 1.0;
        T previousSampleX = delayedSampleX1;
        T previousSampleY = delayedSampleY1;

        T processedSample = a0 * (previousSampleY + currentSample - previousSampleX);
        delayedSampleY1 = processedSample;
        delayedSampleX1 = currentSample;
        return processedSample;
    }
}