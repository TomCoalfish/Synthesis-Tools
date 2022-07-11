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

/*
%typemap(in) arma::vec {
    $1 = arma::Col<double>;
}
%typemap(out) arma::vec {
    $result = arma::Col<double>($1);
}
%typemap(in) arma::mat {
    $1 = arma::Mat<double>;
}
%typemap(out) arma::mat {
    $result = arma::Mat<double>($1);
}
%typemap(in) arma::dmat {
    $1 = arma::Mat<double>;
}
%typemap(out) arma::dmat {
    $result = arma::Mat<double>($1);
}
%typemap(in) arma::fmat {
    $1 = arma::Mat<float>;
}
%typemap(out) arma::fmat {
    $result = arma::Mat<float>($1);
}
%typemap(in) arma::cx_mat {
    $1 = arma::Mat<std::complex<double>>;
}
%typemap(out) arma::cx_mat {
    $result = arma::Mat<std::complex<double>>($1);
}
%typemap(in) arma::cx_dmat {
    $1 = arma::Mat<std::complex<double>>;
}
%typemap(out) arma::cx_dmat {
    $result = arma::Mat<std::complex<double>>($1);
}
%typemap(in) arma::cx_fmat {
    $1 = arma::Mat<std::complex<float>>;
}
%typemap(out) arma::cx_fmat {
    $result = arma::Mat<std::complex<float>>($1);
}
%typemap(in) arma::umat {
    $1 = arma::Mat<unsigned>;
}
%typemap(out) arma::umat {
    $result = arma::Mat<unsigned>($1);
}
%typemap(in) arma::imat {
    $1 = arma::Mat<int>;
}
%typemap(out) arma::imat {
    $result = arma::Mat<int>($1);
}

%include "armadsp.i"
*/

