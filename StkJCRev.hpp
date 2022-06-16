#pragma
#include "StkEffect.hpp"
#include "StkDelay.hpp"
#include "StkOnePole.hpp"
#include <cmath>


namespace stk {

/***************************************************/
/*! \class JCRev
    \brief John Chowning's reverberator class.

    This class takes a monophonic input signal and
    produces a stereo output signal.  It is derived
    from the CLM JCRev function, which is based on
    the use of networks of simple allpass and comb
    delay filters.  This class implements three
    series allpass units, followed by four parallel
    comb filters, and two decorrelation delay lines
    in parallel at the output.

    Although not in the original JC reverberator,
    one-pole lowpass filters have been added inside
    the feedback comb filters.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

class JCRev : public Effect
{
 public:
  //! Class constructor taking a T60 decay time argument (one second default value).
  JCRev( T T60 = 1.0 );

  //! Reset and clear all internal state.
  void clear( void );

  //! Set the reverberation T60 decay time.
  void setT60( T T60 );

  //! Return the specified channel value of the last computed stereo frame.
  /*!
    Use the lastFrame() function to get both values of the last
    computed stereo frame.  The \c channel argument must be 0 or 1
    (the first channel is specified by 0).  However, range checking is
    only performed if _STK_DEBUG_ is defined during compilation, in
    which case an out-of-range value will trigger an StkError
    exception.
  */
  T lastOut( unsigned int channel = 0 );

  //! Input one sample to the effect and return the specified \c channel value of the computed stereo frame.
  /*!
    Use the lastFrame() function to get both values of the computed
    stereo output frame. The \c channel argument must be 0 or 1 (the
    first channel is specified by 0).  However, range checking is only
    performed if _STK_DEBUG_ is defined during compilation, in which
    case an out-of-range value will trigger an StkError exception.
  */
  T tick( T input, unsigned int channel = 0 );

  //! Take a channel of the StkFrames<T> object as inputs to the effect and replace with stereo outputs.
  /*!
    The StkFrames<T> argument reference is returned.  The stereo
    outputs are written to the StkFrames<T> argument starting at the
    specified \c channel.  Therefore, the \c channel argument must be
    less than ( channels() - 1 ) of the StkFrames<T> argument (the first
    channel is specified by 0).  However, range checking is only
    performed if _STK_DEBUG_ is defined during compilation, in which
    case an out-of-range value will trigger an StkError exception.
  */
  StkFrames<T>& tick( StkFrames<T>& frames, unsigned int channel = 0 );

  //! Take a channel of the \c iFrames object as inputs to the effect and write stereo outputs to the \c oFrames object.
  /*!
    The \c iFrames object reference is returned.  The \c iChannel
    argument must be less than the number of channels in the \c
    iFrames argument (the first channel is specified by 0).  The \c
    oChannel argument must be less than ( channels() - 1 ) of the \c
    oFrames argument.  However, range checking is only performed if
    _STK_DEBUG_ is defined during compilation, in which case an
    out-of-range value will trigger an StkError exception.
  */
  StkFrames<T>& tick( StkFrames<T>& iFrames, StkFrames<T> &oFrames, unsigned int iChannel = 0, unsigned int oChannel = 0 );

 protected:

  Delay<T> allpassDelays_[3];
  Delay<T> combDelays_[4];
  OnePole<T> combFilters_[4];
  Delay<T> outLeftDelay_;
  Delay<T> outRightDelay_;
  T allpassCoefficient_;
  T combCoefficient_[4];

};

template<typename T>
inline T JCRev<T>::lastOut( unsigned int channel )
{
#if defined(_STK_DEBUG_)
  if ( channel > 1 ) {
    oStream_ << "JCRev::lastOut(): channel argument must be less than 2!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  return lastFrame_[channel];
}

template<typename T>
inline T JCRev<T>::tick( T input, unsigned int channel )
{
#if defined(_STK_DEBUG_)
  if ( channel > 1 ) {
    oStream_ << "JCRev::tick(): channel argument must be less than 2!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T temp, temp0, temp1, temp2, temp3, temp4, temp5, temp6;
  T filtout;

  temp = allpassDelays_[0].lastOut();
  temp0 = allpassCoefficient_ * temp;
  temp0 += input;
  allpassDelays_[0].tick(temp0);
  temp0 = -(allpassCoefficient_ * temp0) + temp;
    
  temp = allpassDelays_[1].lastOut();
  temp1 = allpassCoefficient_ * temp;
  temp1 += temp0;
  allpassDelays_[1].tick(temp1);
  temp1 = -(allpassCoefficient_ * temp1) + temp;
    
  temp = allpassDelays_[2].lastOut();
  temp2 = allpassCoefficient_ * temp;
  temp2 += temp1;
  allpassDelays_[2].tick(temp2);
  temp2 = -(allpassCoefficient_ * temp2) + temp;
    
  temp3 = temp2 + ( combFilters_[0].tick( combCoefficient_[0] * combDelays_[0].lastOut() ) );
  temp4 = temp2 + ( combFilters_[1].tick( combCoefficient_[1] * combDelays_[1].lastOut() ) );
  temp5 = temp2 + ( combFilters_[2].tick( combCoefficient_[2] * combDelays_[2].lastOut() ) );
  temp6 = temp2 + ( combFilters_[3].tick( combCoefficient_[3] * combDelays_[3].lastOut() ) );

  combDelays_[0].tick(temp3);
  combDelays_[1].tick(temp4);
  combDelays_[2].tick(temp5);
  combDelays_[3].tick(temp6);

  filtout = temp3 + temp4 + temp5 + temp6;

  lastFrame_[0] = effectMix_ * (outLeftDelay_.tick(filtout));
  lastFrame_[1] = effectMix_ * (outRightDelay_.tick(filtout));
  temp = (1.0 - effectMix_) * input;
  lastFrame_[0] += temp;
  lastFrame_[1] += temp;
    
  return 0.7 * lastFrame_[channel];
}

/***************************************************/
/*! \class JCRev
    \brief John Chowning's reverberator class.

    This class takes a monophonic input signal and
    produces a stereo output signal.  It is derived
    from the CLM JCRev function, which is based on
    the use of networks of simple allpass and comb
    delay filters.  This class implements three
    series allpass units, followed by four parallel
    comb filters, and two decorrelation delay lines
    in parallel at the output.

    Although not in the original JC reverberator,
    one-pole lowpass filters have been added inside
    the feedback comb filters.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/


template<typename T>
JCRev<T>::JCRev( T T60 )
{
  if ( T60 <= 0.0 ) {
    oStream_ << "JCRev::JCRev: argument (" << T60 << ") must be positive!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }

  lastFrame_.resize( 1, 2, 0.0 ); // resize lastFrame_ for stereo output

  // Delay lengths for 44100 Hz sample rate.
  int lengths[9] = {1116, 1356, 1422, 1617, 225, 341, 441, 211, 179};
  double scaler = Stk::sampleRate() / 44100.0;

  int delay, i;
  if ( scaler != 1.0 ) {
    for ( i=0; i<9; i++ ) {
      delay = (int) floor( scaler * lengths[i] );
      if ( (delay & 1) == 0) delay++;
      while ( !this->isPrime(delay) ) delay += 2;
      lengths[i] = delay;
    }
  }

  for ( i=0; i<3; i++ ) {
	  allpassDelays_[i].setMaximumDelay( lengths[i+4] );
	  allpassDelays_[i].setDelay( lengths[i+4] );
  }

  for ( i=0; i<4; i++ ) {
    combDelays_[i].setMaximumDelay( lengths[i] );
    combDelays_[i].setDelay( lengths[i] );
    combFilters_[i].setPole( 0.2 );
  }

  this->setT60( T60 );
  outLeftDelay_.setMaximumDelay( lengths[7] );
  outLeftDelay_.setDelay( lengths[7] );
  outRightDelay_.setMaximumDelay( lengths[8] );
  outRightDelay_.setDelay( lengths[8] );
  allpassCoefficient_ = 0.7;
  effectMix_ = 0.3;
  this->clear();
}

template<typename T>
void JCRev<T>::clear()
{
  allpassDelays_[0].clear();
  allpassDelays_[1].clear();
  allpassDelays_[2].clear();
  combDelays_[0].clear();
  combDelays_[1].clear();
  combDelays_[2].clear();
  combDelays_[3].clear();
  outRightDelay_.clear();
  outLeftDelay_.clear();
  lastFrame_[0] = 0.0;
  lastFrame_[1] = 0.0;
}

template<typename T>
void JCRev<T>::setT60( T T60 )
{
  if ( T60 <= 0.0 ) {
    oStream_ << "JCRev::setT60: argument (" << T60 << ") must be positive!";
    handleError( StkError::WARNING ); return;
  }

  for ( int i=0; i<4; i++ )
    combCoefficient_[i] = pow(10.0, (-3.0 * combDelays_[i].getDelay() / (T60 * Stk::sampleRate())));
}

template<typename T>
StkFrames<T>& JCRev<T>::tick( StkFrames<T>& frames, unsigned int channel )
{
#if defined(_STK_DEBUG_)
  if ( channel >= frames.channels() - 1 ) {
    oStream_ << "JCRev::tick(): channel and StkFrames<T> arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T *samples = &frames[channel];
  unsigned int hop = frames.channels();
  for ( unsigned int i=0; i<frames.frames(); i++, samples += hop ) {
    *samples = tick( *samples );
    *(samples+1) = lastFrame_[1];
  }

  return frames;
}


template<typename T>
StkFrames<T>& JCRev<T>::tick( StkFrames<T>& iFrames, StkFrames<T>& oFrames, unsigned int iChannel, unsigned int oChannel )
{
#if defined(_STK_DEBUG_)
  if ( iChannel >= iFrames.channels() || oChannel >= oFrames.channels() - 1 ) {
    oStream_ << "JCRev::tick(): channel and StkFrames<T> arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T *iSamples = &iFrames[iChannel];
  T *oSamples = &oFrames[oChannel];
  unsigned int iHop = iFrames.channels(), oHop = oFrames.channels();
  for ( unsigned int i=0; i<iFrames.frames(); i++, iSamples += iHop, oSamples += oHop ) {
    *oSamples = tick( *iSamples );
    *(oSamples+1) = lastFrame_[1];
  }

  return iFrames;
}

} // stk namespace


