#pragma once

#include "samples.hpp"
#include "AudioDevice.h"
//#include "MidiDevice.h"



#include "AudioFFT.h"
#include "FFTConvolver.h"
#include "TwoStageFFTConvolver.h"
#include "kissfft.h"

#include "FaustFilters.h"
#include "StateVariableFilter.h"
#include "HybridCurtisVCF.h"
#include "Moog.h"

#include "Envelope.h"

#include "sndfile.h"
#include "Resampler.h"

#include "NoiseGenerator.h"
#include "Noise.h"

#include "BandLimitedOscillator.h"
#include "WaveTable.h"


#include "fo_apf.h"
#include "fo_lpf.h"
#include "fo_hpf.h"
#include "fo_shelving_high.h"
#include "fo_shelving_low.h"
#include "so_apf.h"
#include "so_bpf.h"
#include "so_bsf.h"
#include "so_lpf.h"
#include "so_hsf.h"
#include "so_butterworth_bpf.h"
#include "so_butterworth_bsf.h"
#include "so_butterworth_hpf.h"
#include "so_butterworth_lpf.h"
#include "so_linkwitz_riley_hpf.h"
#include "so_linkwitz_riley_lpf.h"
#include "so_parametric_cq_boost.h"
#include "so_parametric_cq_cut.h"
#include "so_parametric_ncq.h"

#include "TPolyBLEPOsc.h"