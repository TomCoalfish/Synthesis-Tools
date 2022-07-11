%module biquad
%{
#include <vector>
#include <complex>
#include <cmath>
#include "BiQuad.h"
%}

%include "stdint.i"
%include "std_complex.i"
%include "std_vector.i"

%template(float_complex) std::complex<float>;
%template(double_complex) std::complex<double>;

%template(float_vector) std::vector<float>;
%template(double_vector) std::vector<double>;

%include "BiQuad.h"
