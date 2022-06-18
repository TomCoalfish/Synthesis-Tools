#pragma once
#include "StkFM.hpp"

namespace stk {

/***************************************************/
/*! \class PercFlut
    \brief STK percussive flute FM synthesis instrument.

    This class implements algorithm 4 of the TX81Z.

    \code
    Algorithm 4 is :   4->3--\
                          2-- + -->1-->Out
    \endcode

    Control Change Numbers: 
       - Total Modulator Index = 2
       - Modulator Crossfade = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
class PercFlut : public FM<T>
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  PercFlut( void );

  //! Class destructor.
  ~PercFlut( void );

  //! Set instrument parameters for a particular frequency.
  void setFrequency( T frequency );

  //! Start a note with the given frequency and amplitude.
  void noteOn( T frequency, T amplitude );

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

};

template<typename T>
inline T PercFlut<T>::tick( unsigned int )
{
  T temp;

  temp = vibrato_.tick() * modDepth_ * 0.2;    
  waves_[0]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[0]);
  waves_[1]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[1]);
  waves_[2]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[2]);
  waves_[3]->setFrequency(baseFrequency_ * (1.0 + temp) * ratios_[3]);
    
  waves_[3]->addPhaseOffset( twozero_.lastOut() );
  temp = gains_[3] * adsr_[3]->tick() * waves_[3]->tick();

  twozero_.tick(temp);
  waves_[2]->addPhaseOffset( temp );
  temp = (1.0 - (control2_ * 0.5)) * gains_[2] * adsr_[2]->tick() * waves_[2]->tick();

  temp += control2_ * 0.5 * gains_[1] * adsr_[1]->tick() * waves_[1]->tick();
  temp = temp * control1_;

  waves_[0]->addPhaseOffset(temp);
  temp = gains_[0] * adsr_[0]->tick() * waves_[0]->tick();
    
  lastFrame_[0] = temp * 0.5;
  return lastFrame_[0];
}

template<typename T>
inline StkFrames<T>& PercFlut<T>::tick( StkFrames<T>& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "PercFlut::tick(): channel and StkFrames<T> arguments are incompatible!";
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
/*! \class PercFlut
    \brief STK percussive flute FM synthesis instrument.

    This class implements algorithm 4 of the TX81Z.

    \code
    Algorithm 4 is :   4->3--\
                          2-- + -->1-->Out
    \endcode

    Control Change Numbers: 
       - Total Modulator Index = 2
       - Modulator Crossfade = 4
       - LFO Speed = 11
       - LFO Depth = 1
       - ADSR 2 & 4 Target = 128

    The basic Chowning/Stanford FM patent expired
    in 1995, but there exist follow-on patents,
    mostly assigned to Yamaha.  If you are of the
    type who should worry about this (making
    money) worry away.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
PercFlut<T>::PercFlut( void )
  : FM()
{
  // Concatenate the STK rawwave path to the rawwave files
  for ( unsigned int i=0; i<3; i++ )
    waves_[i] = new FileLoop( (Stk::rawwavePath() + "sinewave.raw").c_str(), true );
  waves_[3] = new FileLoop( (Stk::rawwavePath() + "fwavblnk.raw").c_str(), true );

  this->setRatio(0, 1.50 * 1.000);
  this->setRatio(1, 3.00 * 0.995);
  this->setRatio(2, 2.99 * 1.005);
  this->setRatio(3, 6.00 * 0.997);
  gains_[0] = fmGains_[99];
  gains_[1] = fmGains_[71];
  gains_[2] = fmGains_[93];
  gains_[3] = fmGains_[85];

  adsr_[0]->setAllTimes( 0.05, 0.05, fmSusLevels_[14], 0.05);
  adsr_[1]->setAllTimes( 0.02, 0.50, fmSusLevels_[13], 0.5);
  adsr_[2]->setAllTimes( 0.02, 0.30, fmSusLevels_[11], 0.05);
  adsr_[3]->setAllTimes( 0.02, 0.05, fmSusLevels_[13], 0.01);

  twozero_.setGain( 0.0 );
  modDepth_ = 0.005;
}  

template<typename T>
PercFlut<T>::~PercFlut( void )
{
}

template<typename T>
void PercFlut<T>::setFrequency( T frequency )
{    
#if defined(_STK_DEBUG_)
  if ( frequency <= 0.0 ) {
    oStream_ << "PercFlut::setFrequency: argument is less than or equal to zero!";
    handleError( StkError::WARNING ); return;
  }
#endif

  baseFrequency_ = frequency;
}

template<typename T>
void PercFlut<T>::noteOn( T frequency, T amplitude )
{
  gains_[0] = amplitude * fmGains_[99] * 0.5;
  gains_[1] = amplitude * fmGains_[71] * 0.5;
  gains_[2] = amplitude * fmGains_[93] * 0.5;
  gains_[3] = amplitude * fmGains_[85] * 0.5;
  this->setFrequency( frequency );
  this->keyOn();
}

} // stk namespace
