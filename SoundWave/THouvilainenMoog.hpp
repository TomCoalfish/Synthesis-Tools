#include "TLadderBase.hpp"

namspace SoundWave {
    template<typename T>
    class THuovilainenMoog : public TLadderFilterBase<T>
    {
    public:
        
        THuovilainenMoog(Tt sampleRate) : TLadderFilterBase<T>(sampleRate), thermal(0.000025)
        {
            memset(stage, 0, sizeof(stage));
            memset(delay, 0, sizeof(delay));
            memset(stageTanh, 0, sizeof(stageTanh));
            SetCutoff(1000.0f);
            SetResonance(0.10f);
        }
        
        virtual ~THuovilainenMoog()
        {
            
        }
        
        void Process(uint32_t n, T* _input, T* _output)
        {
            for (int s = 0; s < n; ++s)
            {
                // Oversample
                for (int j = 0; j < 2; j++) 
                {
                    float input = _input[s] - resQuad * delay[5];
                    delay[0] = stage[0] = delay[0] + tune * (tanh(input * thermal) - stageTanh[0]);
                    for (int k = 1; k < 4; k++) 
                    {
                        input = stage[k-1];
                        stage[k] = delay[k] + tune * ((stageTanh[k-1] = tanh(input * thermal)) - (k != 3 ? stageTanh[k] : tanh(delay[k] * thermal)));
                        delay[k] = stage[k];
                    }
                    // 0.5 sample delay for phase compensation
                    delay[5] = (stage[3] + delay[4]) * 0.5;
                    delay[4] = stage[3];
                }
                _output[s] = delay[5];
            }
        }

        void Process(T * _input, uint32_t n)
        {
            for (int s = 0; s < n; ++s)
            {
                // Oversample
                for (int j = 0; j < 2; j++) 
                {
                    float input = _input[s] - resQuad * delay[5];
                    delay[0] = stage[0] = delay[0] + tune * (tanh(input * thermal) - stageTanh[0]);
                    for (int k = 1; k < 4; k++) 
                    {
                        input = stage[k-1];
                        stage[k] = delay[k] + tune * ((stageTanh[k-1] = tanh(input * thermal)) - (k != 3 ? stageTanh[k] : tanh(delay[k] * thermal)));
                        delay[k] = stage[k];
                    }
                    // 0.5 sample delay for phase compensation
                    delay[5] = (stage[3] + delay[4]) * 0.5;
                    delay[4] = stage[3];
                }
                _input[s] = delay[5];
            }
        }
        
        T Tick(T input) {
            T r = 0.0;
            Process(1,&input,&r);
            return r;
        }
        
        virtual void SetResonance(T r) override
        {
            resonance = r;
            resQuad = 4.0 * resonance * acr;
        }
        
        virtual void SetCutoff(T c) override
        {
            cutoff = c;

            double fc =  cutoff / sampleRate;
            double f  =  fc * 0.5; // oversampled 
            double fc2 = fc * fc;
            double fc3 = fc * fc * fc;

            double fcr = 1.8730 * fc3 + 0.4955 * fc2 - 0.6490 * fc + 0.9988;
            acr = -3.9364 * fc2 + 1.8409 * fc + 0.9968;

            tune = (1.0 - exp(-((2 * MOOG_PI) * f * fcr))) / thermal; 

            SetResonance(resonance);
        }
        
        
    private:
        
        double stage[4];
        double stageTanh[3];
        double delay[6];

        double thermal;
        double tune;
        double acr;
        double resQuad;
        
    }; 
}
