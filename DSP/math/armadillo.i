%module arma
%{
#include "SimpleArmadillo.h"
using namespace Matlab;
%}
%include "std_complex.i"

%include "SimpleArmadillo.h"

%template(float_complex) std::complex<float>;
%template(double_domplex) std::complex<double>;

%template(flt_mat) Matlab::Matrix<float>;
%template(dbl_mat) Matlab::Matrix<double>;
%template(fltcomplex_mat) Matlab::Matrix<std::complex<float>>;
%template(dblcomplex_mat) Matlab::Matrix<std::complex<double>>;
%template(int_mat) Matlab::Matrix<int>;
%template(uint_mat) Matlab::Matrix<unsigned>;
%template(long_mat) Matlab::Matrix<long>;
%template(ulong_mat) Matlab::Matrix<unsigned long>;
%template(llong_mat) Matlab::Matrix<long long>;
%template(ullong_mat) Matlab::Matrix<unsigned long long>;

%template(flt_vec) Matlab::Vector<float>;
%template(dbl_vec) Matlab::Vector<double>;
%template(fltcomplex_vec) Matlab::Vector<std::complex<float>>;
%template(dblcomplex_vec) Matlab::Vector<std::complex<double>>;

/*
%typemap(in) arma::vec {
    $1 = Matlab::Vector<double>;
}
%typemap(out) arma::vec {
    $result = Matlab::Vector<double>($1);
}
%typemap(in) arma::mat {
    $1 = Matlab::Matrix<double>;
}
%typemap(out) arma::mat {
    $result = Matlab::Matrix<double>($1);
}
%typemap(in) arma::dmat {
    $1 = Matlab::Matrix<double>;
}
%typemap(out) arma::dmat {
    $result = Matlab::Matrix<double>($1);
}
%typemap(in) arma::fmat {
    $1 = Matlab::Matrix<float>;
}
%typemap(out) arma::fmat {
    $result = Matlab::Matrix<float>($1);
}
%typemap(in) arma::cx_mat {
    $1 = Matlab::Matrix<std::complex<double>>;
}
%typemap(out) arma::cx_mat {
    $result = Matlab::Matrix<std::complex<double>>($1);
}
%typemap(in) arma::cx_dmat {
    $1 = Matlab::Matrix<std::complex<double>>;
}
%typemap(out) arma::cx_dmat {
    $result = Matlab::Matrix<std::complex<double>>($1);
}
%typemap(in) arma::cx_fmat {
    $1 = Matlab::Matrix<std::complex<float>>;
}
%typemap(out) arma::cx_fmat {
    $result = Matlab::Matrix<std::complex<float>>($1);
}
%typemap(in) arma::umat {
    $1 = Matlab::Matrix<unsigned>;
}
%typemap(out) arma::umat {
    $result = Matlab::Matrix<unsigned>($1);
}
%typemap(in) arma::imat {
    $1 = Matlab::Matrix<int>;
}
%typemap(out) arma::imat {
    $result = Matlab::Matrix<int>($1);
}

%include "armadsp.i"
*/

%inline
%{
    arma::Mat<float> to_mat_float(Matlab::Matrix<float> & m) {
        return arma::Mat<float>(m.matrix);
    }
    Matlab::Matrix<float> from_mat_float(arma::Mat<float> & m) {
        return Matlab::Matrix<float>(m);
    }
    arma::Mat<double> to_mat_double(Matlab::Matrix<double> & m) {
        return arma::Mat<double>(m.matrix);
    }
    Matlab::Matrix<double> from_mat_double(arma::Mat<double> & m) {
        return Matlab::Matrix<double>(m);
    }
    
    arma::Mat<std::complex<float>> to_mat_complex_float(Matlab::Matrix<std::complex<float>> & m) {
        return arma::Mat<std::complex<float>>(m.matrix);
    }
    Matlab::Matrix<std::complex<float>> from_mat_complex_float(arma::Mat<std::complex<float>> & m) {
        return Matlab::Matrix<std::complex<float>>(m);
    }
    arma::Mat<std::complex<double>> to_mat_complex_double(Matlab::Matrix<std::complex<double>> & m) {
        return arma::Mat<std::complex<double>>(m.matrix);
    }
    Matlab::Matrix<std::complex<double>> from_mat_complex_double(arma::Mat<std::complex<double>> & m) {
        return Matlab::Matrix<std::complex<double>>(m);
    }

    arma::Col<float> to_vec_float(Matlab::Vector<float> & m) {
        return arma::Col<float>(m.vector);
    }
    Matlab::Vector<float> from_vec_float(arma::Col<float> & m) {
        return Matlab::Vector<float>(m);
    }
    arma::Col<double> to_vec_double(Matlab::Vector<double> & m) {
        return arma::Col<double>(m.vector);
    }
    Matlab::Vector<double> from_vec_double(arma::Col<double> & m) {
        return Matlab::Vector<double>(m);
    }

    arma::Col<std::complex<float>> to_vec_complex_float(Matlab::Vector<std::complex<float>> & m) {
        return arma::Col<std::complex<float>>(m.vector);
    }
    Matlab::Vector<std::complex<float>> from_vec_complex_float(arma::Col<std::complex<float>> & m) {
        return Matlab::Vector<std::complex<float>>(m);
    }
    arma::Col<std::complex<double>> to_vec_complex_double(Matlab::Vector<std::complex<double>> & m) {
        return arma::Col<std::complex<double>>(m.vector);
    }
    Matlab::Vector<std::complex<double>> from_vec_complex_double(arma::Col<std::complex<double>> & m) {
        return Matlab::Vector<std::complex<double>>(m);
    }

    arma::Row<float> to_row_float(Matlab::Vector<float> & m) {
        return arma::Row<float>(m.vector);
    }
    Matlab::RowVector<float> from_row_float(arma::Row<float> & m) {
        return Matlab::RowVector<float>(m);
    }
    arma::Row<double> to_row_double(Matlab::Vector<double> & m) {
        return arma::Row<double>(m.vector);
    }
    Matlab::RowVector<double> from_row_double(arma::Row<double> & m) {
        return Matlab::RowVector<double>(m);
    }

    arma::Row<std::complex<float>> to_row_complex_float(Matlab::RowVector<std::complex<float>> & m) {
        return arma::Row<std::complex<float>>(m.vector);
    }
    Matlab::RowVector<std::complex<float>> from_row_complex_float(arma::Row<std::complex<float>> & m) {
        return Matlab::RowVector<std::complex<float>>(m);
    }
    arma::Row<std::complex<double>> to_mat_complex_double(Matlab::Vector<std::complex<double>> & m) {
        return arma::Row<std::complex<double>>(m.vector);
    }
    Matlab::RowVector<std::complex<double>> from_mat_complex_double(arma::Row<std::complex<double>> & m) {
        return Matlab::RowVector<std::complex<double>>(m);
    }

%}