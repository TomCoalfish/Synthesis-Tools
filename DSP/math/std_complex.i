%{
#include <complex>
%}

namespace std 
{
    template<typename T>
    class complex {
    public:        
        complex(const T& re = T(), const T& im = T());        
        complex(const complex<T>& other);

        T real() const;
        T imag() const;
        void real(T re);
        void imag(T im);

        complex<T>& operator = (const complex<T> &b) { *$self = b; return *this; }

        %extend {
            complex<T> __add__(const complex<T> &b) { return *$self + b; }
            complex<T> __sub__(const complex<T> &b) { return *$self - b; }
            complex<T> __div__(const complex<T> &b) { return *$self / b; }        
            complex<T> __mul__(const complex<T> &b) { return *$self * b; }
            complex<T> __pow__(const complex<T> &b) { return std::pow(*$self,b); }
            complex<T> __pow__(const T &b) { return std::pow(*$self,b); }
            bool       __eq__(const complex<T> &b) { return *$self == b; }
            //bool       __lt__(const complex<T> &b) { return *$self < b; }
            //bool       __le__(const complex<T> &b) { return *$self <= b; }
        }

    };

    template<typename T> T real(const complex<T> & z);
    template<typename T> T imag(const complex<T> & z);

    template<typename T> T abs(const complex<T> & z);
    template<typename T> T arg(const complex<T> & z);
    template<typename T> T norm(const complex<T> & z);
    template<typename T> complex<T> proj(const complex<T> & z);
    template<typename T> complex<T> polar(const T& r, const T& theta=T());

    template<typename T> complex<T> exp(const complex<T> & z);
    template<typename T> complex<T> log(const complex<T> & z);
    template<typename T> complex<T> log10(const complex<T> & z);
    template<typename T> complex<T> pow(const complex<T>& x, const complex<T> & z);
    template<typename T> complex<T> pow(const complex<T>& x, const T& z);
    template<typename T> complex<T> pow(const T& x, const complex<T> & z);

    template<typename T> complex<T> sqrt(const complex<T> & z);
    
    template<typename T> complex<T> sin(const complex<T> & z);
    template<typename T> complex<T> cos(const complex<T> & z);
    template<typename T> complex<T> tan(const complex<T> & z);

    template<typename T> complex<T> asin(const complex<T> & z);
    template<typename T> complex<T> acos(const complex<T> & z);
    template<typename T> complex<T> atan(const complex<T> & z);

    template<typename T> complex<T> sinh(const complex<T> & z);
    template<typename T> complex<T> cosh(const complex<T> & z);
    template<typename T> complex<T> tanh(const complex<T> & z);

    template<typename T> complex<T> asinh(const complex<T> & z);
    template<typename T> complex<T> acosh(const complex<T> & z);
    template<typename T> complex<T> atanh(const complex<T> & z);
};


%template(real) std::real<std::complex<float>>;
%template(real) std::real<std::complex<double>>;
%template(imag) std::imag<std::complex<float>>;
%template(imag) std::imag<std::complex<double>>;
%template(abs) std::abs<std::complex<float>>;
%template(abs) std::abs<std::complex<double>>;
%template(arg) std::arg<std::complex<float>>;
%template(arg) std::arg<std::complex<double>>;
%template(norm) std::norm<std::complex<float>>;
%template(norm) std::norm<std::complex<double>>;
%template(proj) std::proj<std::complex<float>>;
%template(proj) std::proj<std::complex<double>>;
%template(polar) std::polar<std::complex<float>>;
%template(polar) std::polar<std::complex<double>>;
%template(exp) std::exp<std::complex<float>>;
%template(exp) std::exp<std::complex<double>>;
%template(log) std::log<std::complex<float>>;
%template(log) std::log<std::complex<double>>;
%template(log10) std::log10<std::complex<float>>;
%template(log10) std::log10<std::complex<double>>;
%template(pow) std::pow<std::complex<float>>;
%template(pow) std::pow<std::complex<double>>;
%template(sqrt) std::sqrt<std::complex<float>>;
%template(sqrt) std::sqrt<std::complex<double>>;
%template(sin) std::sin<std::complex<float>>;
%template(sin) std::sin<std::complex<double>>;
%template(cos) std::cos<std::complex<float>>;
%template(cos) std::cos<std::complex<double>>;
%template(tan) std::tan<std::complex<float>>;
%template(tan) std::tan<std::complex<double>>;
%template(asin) std::asin<std::complex<float>>;
%template(asin) std::asin<std::complex<double>>;
%template(acos) std::acos<std::complex<float>>;
%template(acos) std::acos<std::complex<double>>;
%template(atan) std::atan<std::complex<float>>;
%template(atan) std::atan<std::complex<double>>;
%template(sinh) std::sinh<std::complex<float>>;
%template(sinh) std::sinh<std::complex<double>>;
%template(cosh) std::cosh<std::complex<float>>;
%template(cosh) std::cosh<std::complex<double>>;
%template(tanh) std::tanh<std::complex<float>>;
%template(tanh) std::tanh<std::complex<double>>;
%template(asinh) std::asinh<std::complex<float>>;
%template(asinh) std::asinh<std::complex<double>>;
%template(acosh) std::acosh<std::complex<float>>;
%template(acosh) std::acosh<std::complex<double>>;
%template(atanh) std::atanh<std::complex<float>>;
%template(atanh) std::atanh<std::complex<double>>;
