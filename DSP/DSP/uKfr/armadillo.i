%module arma
%{
#include<armadillo>
#include<vector>
#include<complex>
#include<string>

using namespace arma;
%}
%include "std_complex.i"
%include "std_vector.i"
%include "std_string.i"
%include "arma.i"

%template(fcomplex) std::complex<float>;
%template(xcomplex) std::complex<double>;

%template(fmat) arma::Mat<float>;
%template(dmat) arma::Mat<double>;

%template(cfmat) arma::Mat<std::complex<float>>;
%template(cxmat) arma::Mat<std::complex<double>>;
%template(imat) arma::Mat<int>;
%template(umat) arma::Mat<unsigned>;
%template(lmat) arma::Mat<long>;
%template(ulmat) arma::Mat<unsigned long>;
%template(llmat) arma::Mat<long long>;
%template(ullmat) arma::Mat<unsigned long long>;

%template(fvec) arma::Col<float>;
%template(dvec) arma::Col<double>;
%template(cfvec) arma::Col<std::complex<float>>;
%template(cxvec) arma::Col<std::complex<double>>;

// i'm not sure what armadillo calls row atm
%template(frow) arma::Row<float>;
%template(drow) arma::Row<double>;
%template(cfrow) arma::Row<std::complex<float>>;
%template(cxrow) arma::Row<std::complex<double>>;



%template(cfreal) std::real<float>;
%template(czreal) std::real<double>;

%template(cfimag) std::imag<float>;
%template(czimag) std::imag<double>;

%template(cfabs) std::abs<float>;
%template(czabs) std::abs<double>;

%template(cfarg) std::arg<float>;
%template(czarg) std::arg<double>;

%template(cfnorm) std::norm<float>;
%template(cznorm) std::norm<double>;

%template(cfproj) std::proj<float>;
%template(czproj) std::proj<double>;

%template(cfpolar) std::polar<float>;
%template(czpolar) std::polar<double>;

%template(cfexp) std::exp<float>;
%template(czexp) std::exp<double>;

%template(cflog) std::log<float>;
%template(czlog) std::log<double>;

%template(cflog10) std::log10<float>;
%template(czlog10) std::log10<double>;

%template(cfpow) std::pow<float>;
%template(czpow) std::pow<double>;

%template(cfsqrt) std::sqrt<float>;
%template(czsqrt) std::sqrt<double>;

%template(cfsin) std::sin<float>;
%template(czsin) std::sin<double>;
    
%template(cfcos) std::cos<float>;
%template(czcos) std::cos<double>;

%template(cftan) std::tan<float>;
%template(cztan) std::tan<double>;

%template(cfasin) std::asin<float>;
%template(czasin) std::asin<double>;
    
%template(cfacos) std::acos<float>;
%template(czacos) std::acos<double>;

%template(cfatan) std::atan<float>;
%template(czatan) std::atan<double>;

%template(cfsinh) std::sinh<float>;
%template(czsinh) std::sinh<double>;
    
%template(cfcosh) std::cosh<float>;
%template(czcosh) std::cosh<double>;

%template(cftanh) std::tanh<float>;
%template(cztanh) std::tanh<double>;

%template(cfasinh) std::asinh<float>;
%template(czasinh) std::asinh<double>;
    
%template(cfacosh) std::acosh<float>;
%template(czacosh) std::acosh<double>;

%template(cfatanh) std::atanh<float>;
%template(czatanh) std::atanh<double>;

// they only work for double
%template(linspace) ops::linspace<double>;
%template(logpace) ops::logspace<double>;
%template(regpace) ops::logspace<double>;
//%template(randperm) ops::randperm<double>;
%template(eye) ops::eye<double>;

%template(col_zero) ops::zero<arma::Col<double>>;
%template(col_ones) ops::zero<arma::Col<double>>;
%template(col_random) ops::zero<arma::Col<double>>;
%template(col_randu) ops::randu<arma::Col<double>>;

%template(random_vector) ops::random_vector<double>;
%template(toeplitz) ops::toeplitz<double>;
%template(circ_toeplitz) ops::circ_toeplitz<double>;
