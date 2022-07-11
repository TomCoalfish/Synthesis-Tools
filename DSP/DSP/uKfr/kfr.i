%module kfr
%{
#include <cmath>
#include <vector>
#include <complex>
#include <iostream>
#include <random> 

#include <kfr/kfr.h>
#include <kfr/dft.hpp>
#include <kfr/io.hpp>
#include <kfr/math.hpp>
#include "kfrcore.hpp"
using namespace kfr;
%}

%include "stdint.i"
%include "std_complex.i"
%include "std_vector.i"

%include "kfr_biquad.hpp"
%include "kfr_bessel.hpp"
%include "kfr_butterworth.hpp"
%include "kfr_chebyshev1.hpp"
%include "kfr_chebyshev2.hpp"
%include "kfr_convolve.hpp"
%include "kfr_dct.hpp"
%include "kfr_dft.hpp"
%include "kfr_fileio.hpp"
%include "kfr_fir.hpp"
%include "kfr_resample.hpp"
%include "kfr_window.hpp"
%include "kfrcore.hpp"


%include "ukfr_core.i"
%include "ukfr_samplerate.i"
%include "ukfr_biquad.i"
%include "ukfr_convolution.i"
%include "ukfr_fir.i"
%include "ukfr_dft.i"

%inline
%{

    template<typename T>
    kfr::univector<T> univector_from_stdvector(std::vector<T> & in) {
        kfr::univector<T> r(in.size);
        std::copy(in.begin(),in.end,r.begin());
        return r;
    }
    template<typename T>
    std::vector<T> univector_to_stdvector(kfr::univector<T> & in) {
        std::vector<T> r(in.size);
        std::copy(in.begin(),in.end,r.begin());
        return r;
    }
    template<typename T>
    kfr::univector<T> univector_from_pointer(T * ptr, size_t n)
    {
        kfr::univector<T> r(n);
        memcpy(r.data(),ptr,n*sizeof(T));
        return r;
    }
    template<typename T>
    void univector_to_pointer(kfr::univector<T> & in, T * ptr)
    {        
        memcpy(ptr,in.data(),in.size()*sizeof(T));        
    }

        
%}


%template(copy_from_vector) univector_from_stdvector<T>;
%template(copy_to_vector) univector_to_stdvector<T>;
%template(copy_from_pointer) univector_from_pointer<T>;
%template(copy_to_pointer) univector_to_pointer<T>;