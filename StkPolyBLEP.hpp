#pragma once
// Derived class to use the PolyBLEP Oscillator as an stk::Generator.

#include "PolyBLEP.h"

template<typename T>
class PolyBLEPStk : public stk::Generator<T>, public PolyBLEP {
public:
    PolyBLEPStk(T sampleRate, Waveform waveform = SINE, T initialFrequency = 440.0)
            : PolyBLEP(sampleRate, waveform, initialFrequency) {
        const int numFrames = 1;
        const int numChannels = 1;
        lastFrame_.resize(numFrames, numChannels, 0.0);
    }

    virtual ~PolyBLEPStk() {
    }

    virtual T tick() {
        return getAndInc();
    }
    virtual stk::StkFrames<T> &tick(stk::StkFrames<T> &frames, unsigned int channel = 0) override {
        for (size_t frame = 0; frame < frames.size(); ++frame) {
            frames(frame, channel) = getAndInc();
        }
        return frames;
    }

    virtual void sampleRateChanged(stk::StkFloat newRate, stk::StkFloat oldRate) override {
        PolyBLEP::setSampleRate(newRate);
    }

private:
};

