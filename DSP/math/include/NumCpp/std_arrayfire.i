%{
#include <cstdint>
#include "af.h"
using namespace ArrayFire;
%}

%include "std_complex.i"
%include "af.h"

%template(FloatArray) ArrayFire::Array<float>;
%template(DoubleArray) ArrayFire::Array<double>;

%template(Complex32) std::complex<float>;
%template(Complex64) std::complex<double>;

%template(Complex32Array) ArrayFire::Array<std::complex<float>>;
%template(Complex64Array) ArrayFire::Array<stc::complex<double>>;

// missing af_write
//%template(af_bool) ArrayFire::Array<bool,b8>;
%template(UInt8Array) ArrayFire::Array<uint8_t>;
%template(Int16Array) ArrayFire::Array<int16_t>;
%template(UInt16Array) ArrayFire::Array<uint16_t>;
%template(Int32Array) ArrayFire::Array<int32_t>;
%template(UInt32Array) ArrayFire::Array<uint32_t>;
// not sure why int64_t is a problem.
%template(Int64Array) ArrayFire::Array<long long int>;
%template(UInt64Array) ArrayFire::Array<unsigned long long int>;
%template(HalfArray)        ArrayFire::Array<float,fp16>;

%template(FloatVector) ArrayFire::Vector<float>;
%template(DoubleVector) ArrayFire::Vector<double>;

%template(FloatMatrix) ArrayFire::Matrix<float>;
%template(DoubleMatrix) ArrayFire::Matrix<double>;

%inline %{
    void  set_float(float * p, size_t i, float v) { p[i] = v; }
    float get_float(float * p, size_t i) { return p[i]; }
%}