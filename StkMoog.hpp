#pragma once
#include "StkFormSwep.hpp"
#include "SKINImsg.h"

namespace stk {

/***************************************************/
/*! \class Moog
    \brief STK moog-like swept filter sampling synthesis class.

    This instrument uses one attack wave, one
    looped wave, and an ADSR envelope (inherited
    from the Sampler class) and adds two sweepable
    formant (FormSwep) filters.

    Control Change Numbers: 
       - Filter Q = 2
       - Filter Sweep Rate = 4
       - Vibrato Frequency = 11
       - Vibrato Gain = 1
       - Gain = 128

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
class Moog : public Sampler<T>
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  Moog( void );

  //! Class destructor.
  ~Moog( void );

  //! Set instrument parameters for a particular frequency.
  void setFrequency( T frequency );

  //! Start a note with the given frequency and amplitude.
  void noteOn( T frequency, T amplitude );

  //! Set the modulation (vibrato) speed in Hz.
  void setModulationSpeed( T mSpeed ) { loops_[1]->setFrequency( mSpeed ); };

  //! Set the modulation (vibrato) depth.
  void setModulationDepth( T mDepth ) { modDepth_ = mDepth * 0.5; };

  //! Perform the control change specified by \e number and \e value (0.0 - 128.0).
  void controlChange( int number, T value );

  //! Compute and return one output sample.
  T tick( unsigned int channel = 0 );

  //! Fill a channel of the StkFrames<T> object with computed outputs.
  /*!
    The \c channel argument must be less than the number of
    channels in the StkFrames<T> argument (the first channel is specified
    by 0).  However, range checking is only performed if _STK_DEBUG_
    is defined during compilation, in which case an out-of-range value
    will trigger an StkError exception.
  */
  StkFrames<T>& tick( StkFrames<T>& frames, unsigned int channel = 0 );

 protected:

  FormSwep filters_[2];
  T modDepth_;
  T filterQ_;
  T filterRate_;

};

template<typename T>
inline T Moog<T>::tick( unsigned int )
{
  T temp;

  if ( modDepth_ != 0.0 ) {
    temp = loops_[1]->tick() * modDepth_;    
    loops_[0]->setFrequency( baseFrequency_ * (1.0 + temp) );
  }

  temp = attackGain_ * attacks_[0]->tick();
  temp += loopGain_ * loops_[0]->tick();
  temp = filter_.tick( temp );
  temp *= adsr_.tick();
  temp = filters_[0].tick( temp );
  lastFrame_[0] = filters_[1].tick( temp );
  return lastFrame_[0] * 6.0;
}

template<typename T>
inline StkFrames<T>& Moog<T>::tick( StkFrames<T>& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "Moog::tick(): channel and StkFrames<T> arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T *samples = &frames[channel];
  unsigned int j, hop = frames.channels() - nChannels;
  if ( nChannels == 1 ) {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
      *samples++ = tick();
  }
  else {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop ) {
      *samples++ = tick();
      for ( j=1; j<nChannels; j++ )
        *samples++ = lastFrame_[j];
    }
  }

  return frames;
}

/***************************************************/
/*! \class Moog
    \brief STK moog-like swept filter sampling synthesis class.

    This instrument uses one attack wave, one
    looped wave, and an ADSR envelope (inherited
    from the Sampler class) and adds two sweepable
    formant (FormSwep) filters.

    Control Change Numbers: 
       - Filter Q = 2
       - Filter Sweep Rate = 4
       - Vibrato Frequency = 11
       - Vibrato Gain = 1
       - Gain = 128

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
Moog<T>::Moog( void )
{
  // Concatenate the STK rawwave path to the rawwave file
  attacks_.push_back( new FileWvIn( (Stk::rawwavePath() + "mandpluk.raw").c_str(), true ) );
  loops_.push_back ( new FileLoop( (Stk::rawwavePath() + "impuls20.raw").c_str(), true ) );
  loops_.push_back ( new FileLoop( (Stk::rawwavePath() + "sinewave.raw").c_str(), true ) ); // vibrato
  loops_[1]->setFrequency( 6.122 );

  filters_[0].setTargets( 0.0, 0.7 );
  filters_[1].setTargets( 0.0, 0.7 );

  adsr_.setAllTimes( 0.001, 1.5, 0.6, 0.250 );
  filterQ_ = 0.85;
  filterRate_ = 0.0001;
  modDepth_ = 0.0;
}  

template<typename T>
Moog<T>::~Moog( void )
{
}

template<typename T>
void Moog<T>::setFrequency( T frequency )
{
#if defined(_STK_DEBUG_)
  if ( frequency <= 0.0 ) {
    oStream_ << "Moog::setFrequency: parameter is less than or equal to zero!";
    handleError( StkError::WARNING ); return;
  }
#endif

  baseFrequency_ = frequency;
  T rate = attacks_[0]->getSize() * 0.01 * baseFrequency_ / Stk::sampleRate();
  attacks_[0]->setRate( rate );
  loops_[0]->setFrequency( baseFrequency_ );
}

template<typename T>
void Moog<T>::noteOn( T frequency, T amplitude )
{
  T temp;
    
  this->setFrequency( frequency );
  this->keyOn();
  attackGain_ = amplitude * 0.5;
  loopGain_ = amplitude;

  temp = filterQ_ + 0.05;
  filters_[0].setStates( 2000.0, temp );
  filters_[1].setStates( 2000.0, temp );

  temp = filterQ_ + 0.099;
  filters_[0].setTargets( frequency, temp );
  filters_[1].setTargets( frequency, temp );

  filters_[0].setSweepRate( filterRate_ * 22050.0 / Stk::sampleRate() );
  filters_[1].setSweepRate( filterRate_ * 22050.0 / Stk::sampleRate() );
}

template<typename T>
void Moog<T>::controlChange( int number, T value )
{
#if defined(_STK_DEBUG_)
  if ( Stk::inRange( value, 0.0, 128.0 ) == false ) {
    oStream_ << "Moog::controlChange: value (" << value << ") is out of range!";
    handleError( StkError::WARNING ); return;
  }
#endif

  T normalizedValue = value * ONE_OVER_128;
  if (number == __SK_FilterQ_) // 2
    filterQ_ = 0.80 + ( 0.1 * normalizedValue );
  else if (number == __SK_FilterSweepRate_) // 4
    filterRate_ = normalizedValue * 0.0002;
  else if (number == __SK_ModFrequency_) // 11
    this->setModulationSpeed( normalizedValue * 12.0 );
  else if (number == __SK_ModWheel_)  // 1
    this->setModulationDepth( normalizedValue );
  else if (number == __SK_AfterTouch_Cont_) // 128
    adsr_.setTarget( normalizedValue );
#if defined(_STK_DEBUG_)
  else {
    oStream_ << "Moog::controlChange: undefined control number (" << number << ")!";
    handleError( StkError::WARNING );
  }
#endif
}

} // stk namespace
