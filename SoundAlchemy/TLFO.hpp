
#include "SoundAlchemy.hpp"

namespace SoundAlchemy
{

    inline double dsp_osc_step(double freq, unsigned int rate)
    {
        return rate ? freq / rate : 0.0;
    }

    /**
     * Increment the time using the step.
     *   @t: The time.
     *   @step: The step.
     */

    inline double dsp_osc_inc(double t, double step)
    {
        return fmod(t + step, 1.0);
    }

    /**
     * Decrement the time using the step.
     *   @t: The time.
     *   @step: The step.
     */

    inline double dsp_osc_dec(double t, double step)
    {
        return fmod(fmod(t - step, 1.0) + 1.0, 1.0);
    }

    /**
     * Generate a sine wave data point.
     *   @t: The time.
     *   &returns: The data point.
     */

    inline double dsp_osc_sine(double t)
    {
        return sin(2.0 * M_PI * t);
    }

    /**
     * Generate a square wave data point.
     *   @t: The time.
     *   &returns: The data point.
     */

    inline double dsp_osc_square(double t)
    {
        return (t < 0.5) ? 1.0 : -1.0;
    }

    /**
     * Generate a sawtooth wave data point.
     *   @t: The time.
     *   &returns: The data point.
     */

    inline double dsp_osc_saw(double t)
    {
        return fmod(1.0 + 2.0 * t, 2.0) - 1.0;
    }

    /**
     * Generate a reverse sawtooth wave data point.
     *   @t: The time.
     *   &returns: The data point.
     */

    inline double dsp_osc_rsaw(double t)
    {
        return fmod(3.0 - 2.0 * t, 2.0) - 1.0;
    }

    /**
     * Generate a triangle wave data point.
     *   @t: The time.
     *   &returns: The data point.
     */

    inline double dsp_osc_tri(double t)
    {
        return 2.0 * fabs(2.0 * t - 1.0) - 1.0;
    }

    template<class T>
    struct NonBandlimitedOsc : public Object<T>
    {
        T phase;
        T freq;
        T step;        
    
        double (*function)(double);
        
        enum Type {
                SIN,
                SAW,
                REVERSE_SAW,
                SQUARE,
                TRIANGLE,
            } _type;

        void SetFunction(Type t) {
            
        }
        NonBandlimitedOsc(Type t, T f, T sr = 44100) {
            freq = f;
            sample_rate = sr;
            step = dsp_osc_step(f,sr);
            _type = t;
            SetFunction(t);
        }

        void Increment() {
            phase += dsp_osc_inc(phase,step);
            if(phase > 1.0) phase -= 1.0;
            if(phase < 0) phase += 1.0;
        }
        void Decrement() {
            phase += dsp_osc_dec(phase,step);
            if(phase > 1.0) phase -= 1.0;
            if(phase < 0) phase += 1.0;
            
        }
        T Tick()
        {            
            Increment();
            // return the sample present at the calculated offset within the table
            return function(phase);
        }

        T Tick(T I, T A=1, T X=0,T Y=0) {                
            T tp = phase;                
            T tf = freq;
            phase = phase + Y;
            if(phase > 1.0) phase -=1.0;
            if(phase < 0) phase += 1.0;
            T ts = step;
            step = dsp_osc_step(freq + X,sample_rate);
            T r = I*A*Tick();                
            phase = tp;
            freq  = tf;
            step = dsp_osc_step(freq,sampleRate);
            return r;
        }
    };
    // can be used as a non-bandlimited oscillator
    template<class T>
    class TLFO : public Object<T> 
    {
        public:
        
            enum Type {
                SIN,
                SAW,
                REVERSE_SAW,
                SQUARE,
                TRIANGLE,
            } _type;

            void setFunction(Type t)  {
                _type = t;
                switch(_type)
                {
                    case SIN: function = dsp_osc_sin; break;
                    case SAW: function = dsp_osc_saw; break;
                    case SQUARE: function = dsp_osc_square; break;
                    case TRIANGLE: function = dsp_osc_triangle; break;
                    case REVERSE_SAW: function = dsp_osc_rsaw; break;
                }
            }

            TLFO( T freq, T sampleRate, Type type) 
            {
                _freq        = freq;
                _rate        = dsp_osc_step(freq,sampleRate);
                _accumulator = 0.f;
                _sampleRate  = sampleRate;                
                setFunction(type);
            }
            ~TLFO() = default;


            T getRate()
            {
                return _rate;
            }            
            void setRate( T value )
            {
                _rate = dsp_osc_strp(value,_sampleRate);
            }            
            void setAccumulator( T value )
            {
                _accumulator = value;
            }            
            T getAccumulator()
            {
                return _accumulator;
            }
            
            
            /**
             * retrieve a value from the wave table for the current
             * accumulator position, this method also increments
             * the accumulator and keeps it within bounds
             */
            T Tick()
            {
                
                _accumulator += _rate;

                // keep the accumulator within the bounds of the sample frequency
                if ( _accumulator > _sampleRate )
                    _accumulator -= _sampleRate;

                // return the sample present at the calculated offset within the table
                return function(_accumulator);
            }

            T Tick(T I, T A=1, T X=0,T Y=0) {                
                T tf = _freq;                
                T f = _freq + X*_freq;                
                _rate = dsp_osc_step(f,sampleRate) + Y;
                if(_rate > 1.0) _rate -= 1.0;
                if(_rate < 0) _rate += 1.0;
                T r = I*A*Tick();                
                _rate = dsp_osc_step(tf,sampleRate);
                if(_rate > 1.0) _rate -= 1.0;
                if(_rate < 0) _rate += 1.0;
                return r;
            }

        private:


        double (*function)(double);
        static const int TABLE_SIZE = 128;            
        T _freq;
        T _rate;
        T _accumulator;   // is read offset in wave table buffer
        T _sampleRate;
        sample_vector<T> TABLE;
};
}