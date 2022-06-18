#ifndef STK_TUBEBELL_H
#define STK_TUBEBELL_H

#include "StkFM.hpp"

namespace stk {

/***************************************************/
/*! \class TubeBell
    \brief STK tubular bell (orchestral chime) FM
           synthesis instrument.

    This class implements two simple FM Pairs
    summed together, also referred to as algorithm
    5 of the TX81Z.

    \code
    Algorithm 5 is :  4->3--\
                             + --> Out
                      2->1--/
    \endcode

    Control Change Numbers: 
       - Modulator Index One = 2
       - Crossfade of Outputs = 4
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
class TubeBell : public FM<T>
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  TubeBell( void );

  //! Class destructor.
  ~TubeBell( void );

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
inline T TubeBell<T>::tick( unsigned int )
{
  T temp, temp2;

  temp = gains_[1] * adsr_[1]->tick() * waves_[1]->tick();
  temp = temp * control1_;

  waves_[0]->addPhaseOffset( temp );
  waves_[3]->addPhaseOffset( twozero_.lastOut() );
  temp = gains_[3] * adsr_[3]->tick() * waves_[3]->tick();
  twozero_.tick( temp );

  waves_[2]->addPhaseOffset( temp );
  temp = ( 1.0 - (control2_ * 0.5)) * gains_[0] * adsr_[0]->tick() * waves_[0]->tick();
  temp += control2_ * 0.5 * gains_[2] * adsr_[2]->tick() * waves_[2]->tick();

  // Calculate amplitude modulation and apply it to output.
  temp2 = vibrato_.tick() * modDepth_;
  temp = temp * (1.0 + temp2);
    
  lastFrame_[0] = temp * 0.5;
  return lastFrame_[0];
}

template<typename T>
inline StkFrames<T>& TubeBell<T>::tick( StkFrames<T>& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "TubeBell::tick(): channel and StkFrames<T> arguments are incompatible!";
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
/*! \class TubeBell
    \brief STK tubular bell (orchestral chime) FM
           synthesis instrument.

    This class implements two simple FM Pairs
    summed together, also referred to as algorithm
    5 of the TX81Z.

    \code
    Algorithm 5 is :  4->3--\
                             + --> Out
                      2->1--/
    \endcode

    Control Change Numbers: 
       - Modulator Index One = 2
       - Crossfade of Outputs = 4
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
TubeBell<T>::TubeBell( void )
  : FM()
{
  // Concatenate the STK rawwave path to the rawwave files
  for ( unsigned int i=0; i<3; i++ )
    waves_[i] = new FileLoop( (Stk::rawwavePath() + "sinewave.raw").c_str(), true );
  waves_[3] = new FileLoop( (Stk::rawwavePath() + "fwavblnk.raw").c_str(), true );

  this->setRatio(0, 1.0   * 0.995);
  this->setRatio(1, 1.414 * 0.995);
  this->setRatio(2, 1.0   * 1.005);
  this->setRatio(3, 1.414 * 1.000);

  gains_[0] = fmGains_[94];
  gains_[1] = fmGains_[76];
  gains_[2] = fmGains_[99];
  gains_[3] = fmGains_[71];

  adsr_[0]->setAllTimes( 0.005, 4.0, 0.0, 0.04);
  adsr_[1]->setAllTimes( 0.005, 4.0, 0.0, 0.04);
  adsr_[2]->setAllTimes( 0.001, 2.0, 0.0, 0.04);
  adsr_[3]->setAllTimes( 0.004, 4.0, 0.0, 0.04);

  twozero_.setGain( 0.5 );
  vibrato_.setFrequency( 2.0 );
}  

template<typename T>
TubeBell<T>::~TubeBell( void )
{
}

template<typename T>
void TubeBell<T>::noteOn( T frequency, T amplitude )
{
  gains_[0] = amplitude * fmGains_[94];
  gains_[1] = amplitude * fmGains_[76];
  gains_[2] = amplitude * fmGains_[99];
  gains_[3] = amplitude * fmGains_[71];
  this->setFrequency( frequency );
  this->keyOn();
}

} // stk namespace
