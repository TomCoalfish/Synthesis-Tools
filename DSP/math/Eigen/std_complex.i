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

%template(float_vector) std::vector<float>;
%template(double_vector) std::vector<double>;
%template(fcomplex) std::complex<float>;
%template(zcomplex) std::complex<double>;
