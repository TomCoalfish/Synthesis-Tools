#pragma once
#include "StkFilter.hpp"
#include <cmath>

namespace stk {

/***************************************************/
/*! \class Fir
    \brief STK general finite impulse response filter class.

    This class provides a generic digital filter structure that can be
    used to implement FIR filters.  For filters with feedback terms,
    the Iir class should be used.

    In particular, this class implements the standard difference
    equation:

    y[n] = b[0]*x[n] + ... + b[nb]*x[n-nb]

    The \e gain parameter is applied at the filter input and does not
    affect the coefficient values.  The default gain value is 1.0.
    This structure results in one extra multiply per computed sample,
    but allows easy control of the overall filter gain.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
class Fir : public Filter<T>
{
public:
  //! Default constructor creates a zero-order pass-through "filter".
  Fir( void );

  //! Overloaded constructor which takes filter coefficients.
  /*!
    An StkError can be thrown if the coefficient vector size is
    zero.
  */
  Fir( std::vector<T> &coefficients );

  //! Class destructor.
  ~Fir( void );

  //! Set filter coefficients.
  /*!
    An StkError can be thrown if the coefficient vector size is
    zero.  The internal state of the filter is not cleared unless the
    \e clearState flag is \c true.
  */
  void setCoefficients( std::vector<T> &coefficients, bool clearState = false );

  //! Return the last computed output value.
  T lastOut( void ) const { return lastFrame_[0]; };

  //! Input one sample to the filter and return one output.
  T tick( T input );

  //! Take a channel of the StkFrames<T> object as inputs to the filter and replace with corresponding outputs.
  /*!
    The StkFrames<T> argument reference is returned.  The \c channel
    argument must be less than the number of channels in the
    StkFrames<T> argument (the first channel is specified by 0).
    However, range checking is only performed if _STK_DEBUG_ is
    defined during compilation, in which case an out-of-range value
    will trigger an StkError exception.
  */
  StkFrames<T>& tick( StkFrames<T>& frames, unsigned int channel = 0 );

  //! Take a channel of the \c iFrames object as inputs to the filter and write outputs to the \c oFrames object.
  /*!
    The \c iFrames object reference is returned.  Each channel
    argument must be less than the number of channels in the
    corresponding StkFrames<T> argument (the first channel is specified
    by 0).  However, range checking is only performed if _STK_DEBUG_
    is defined during compilation, in which case an out-of-range value
    will trigger an StkError exception.
  */
  StkFrames<T>& tick( StkFrames<T>& iFrames, StkFrames<T> &oFrames, unsigned int iChannel = 0, unsigned int oChannel = 0 );

protected:

};

template<typename T>
inline T Fir<T>::tick( T input )
{
  lastFrame_[0] = 0.0;
  inputs_[0] = gain_ * input;

  for ( unsigned int i=(unsigned int)(b_.size())-1; i>0; i-- ) {
    lastFrame_[0] += b_[i] * inputs_[i];
    inputs_[i] = inputs_[i-1];
  }
  lastFrame_[0] += b_[0] * inputs_[0];

  return lastFrame_[0];
}

template<typename T>
inline StkFrames<T>& Fir<T>::tick( StkFrames<T>& frames, unsigned int channel )
{
#if defined(_STK_DEBUG_)
  if ( channel >= frames.channels() ) {
    oStream_ << "Fir::tick(): channel and StkFrames<T> arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T *samples = &frames[channel];
  unsigned int i, hop = frames.channels();
  for ( unsigned int j=0; j<frames.frames(); j++, samples += hop ) {
    inputs_[0] = gain_ * *samples;
    *samples = 0.0;

    for ( i=(unsigned int)b_.size()-1; i>0; i-- ) {
      *samples += b_[i] * inputs_[i];
      inputs_[i] = inputs_[i-1];
    }
    *samples += b_[0] * inputs_[0];
  }

  lastFrame_[0] = *(samples-hop);
  return frames;
}

template<typename T>
inline StkFrames<T>& Fir<T>::tick( StkFrames<T>& iFrames, StkFrames<T>& oFrames, unsigned int iChannel, unsigned int oChannel )
{
#if defined(_STK_DEBUG_)
  if ( iChannel >= iFrames.channels() || oChannel >= oFrames.channels() ) {
    oStream_ << "Fir::tick(): channel and StkFrames<T> arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  T *iSamples = &iFrames[iChannel];
  T *oSamples = &oFrames[oChannel];
  unsigned int i, iHop = iFrames.channels(), oHop = oFrames.channels();
  for ( unsigned int j=0; j<iFrames.frames(); j++, iSamples += iHop, oSamples += oHop ) {
    inputs_[0] = gain_ * *iSamples;
    *oSamples = 0.0;

    for ( i=(unsigned int)b_.size()-1; i>0; i-- ) {
      *oSamples += b_[i] * inputs_[i];
      inputs_[i] = inputs_[i-1];
    }
    *oSamples += b_[0] * inputs_[0];
  }

  lastFrame_[0] = *(oSamples-oHop);
  return iFrames;
}

/***************************************************/
/*! \class Fir
    \brief STK general finite impulse response filter class.

    This class provides a generic digital filter structure that can be
    used to implement FIR filters.  For filters with feedback terms,
    the Iir class should be used.

    In particular, this class implements the standard difference
    equation:

    y[n] = b[0]*x[n] + ... + b[nb]*x[n-nb]

    The \e gain parameter is applied at the filter input and does not
    affect the coefficient values.  The default gain value is 1.0.
    This structure results in one extra multiply per computed sample,
    but allows easy control of the overall filter gain.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/


template<typename T>
Fir<T>::Fir()
{
  // The default constructor should setup for pass-through.
  b_.push_back( 1.0 );

  inputs_.resize( 1, 1, 0.0 );
}

template<typename T>
Fir<T>::Fir( std::vector<T> &coefficients )
{
  // Check the arguments.
  if ( coefficients.size() == 0 ) {
    oStream_ << "Fir: coefficient vector must have size > 0!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }

  gain_ = 1.0;
  b_ = coefficients;

  inputs_.resize( b_.size(), 1, 0.0 );
  this->clear();
}

template<typename T>
Fir<T>::~Fir()
{
}

template<typename T>
void Fir<T>::setCoefficients( std::vector<T> &coefficients, bool clearState )
{
  // Check the argument.
  if ( coefficients.size() == 0 ) {
    oStream_ << "Fir::setCoefficients: coefficient vector must have size > 0!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }

  if ( b_.size() != coefficients.size() ) {
    b_ = coefficients;
    inputs_.resize( b_.size(), 1, 0.0 );
  }
  else {
    for ( unsigned int i=0; i<b_.size(); i++ ) b_[i] = coefficients[i];
  }

  if ( clearState ) this->clear();
}

} // stk namespace
