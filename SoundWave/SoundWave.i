%module soundwave
%{
#include "SoundWave.h"
#include "samples.hpp"

using namespace SoundWave;
using namespace audiofft;
using namespace fftconvolver;
using namespace FFT;
%}

%include "stdint.i"
%include "std_vector.i"
%include "std_string.i"
%include "sample.i"


%include "AudioFFT.h"
%include "FFTConvolver.h"
%include "kissfft.h"
%include "SampleVector.h"
%include "FaustFilters.h"
%include "StateVariableFilter.h"
%include "HybridCurtisVCF.h"
%include "Moog.h"
%include "ADSR.h"
%include "ParametricEnvelope.h"
%include "GammaEnv.h"
%include "sndfile.h"
%include "Resampler.h"
%include "NoiseGenerator.h"
%include "Noise.h"
%include "BandLimitedOscillator.h"
%include "WaveTable.h"                                
%include "SampleVector.h"
%include "samples.hpp"

