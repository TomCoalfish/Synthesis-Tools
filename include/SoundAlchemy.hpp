////////////////////////////////////////////////////////////////////////////////////////////////////
// SoundAlchemy
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "SABase.hpp"

// Std
// #include <Std/Std.hpp>

// Math
// <cmath>
// <limits>
// <valarray>
// <eigen>

// PureData
// #include <libpd>

using std::vector;

// Gamma
#include <Gamma/Gamma.h>

//#include <Std/Std.h>
#include <Std/StdRandom.h>


//////////////////////////////////////////////////////
// SoundWave
//////////////////////////////////////////////////////

#include "TOscillators.hpp"
#include "TFilters.hpp"
#include "TEnvelopes.hpp"

// Parametric
// Quadratic 
// Polar
// Unipolar +/- [0,1][-1,0]
// Bipolar [-1,1]
// I = Input
// A = Amplitude
// F = Frequency/Cutoff
// P = Phase/Q
// X * Y
// Tick()
// TICK(I,A,F,P)
// (A*I) * (F*P)            
// parametric circle
// r = sqrt(x^2 + y^2)
// sin = X/R
// cos = Y/R
// tan = Y/X
// theta = asin(x)
// theta = acos(x)
// theta = atan(x)
// cot = 1/tan
// sec = 1/cos
// csc = 1/sin
// sin^2 = 1-cos^2
// cos^2 = 1-sin^2
// tan^2 +1 = sec^2
// tan^2 = sec^2-1
// cot^2+1 = csc^2
// cot^2 = csc^2-1
// cos(asin) = sqrt(1-x^2)
// cos(atan) = 1/(sqrt(1+x^2))
// tan(acos) = sqrt(1-x^2)/x
// sin(acos) = sqrt(1-x^2)
// sin(atan) = x / sqrt(1+x^2)
// tan(asin) = x / sqrt(1-x^2)
// sin = cos(pi/2 - theta)
// cos = sin(pi/2 - theta)
// sin^2 + cos^2 = 1
// 1 + tan^2 = sec^2
// 1 + cot^2 = csc^2
// sin(-x) = -sin(x)
// tan(-x) = tan(x)
// cos(-x) = cos(x)
// tan = sin/cos
// cot = cos/sin
// sin(2a) = 2sin(x)cos(a)
// cos(2a) = cos^2(a) - sin^2(a)
// cos(2a) = 2cos^2(a) - 1
// cos(2a) = 1 - sin^2(a)
// tan(2a) = (2*tan(a))/(1-tan^2(a))
// sin(a +/- b) = sin(a)cos(b) +/- cos(a)sin(b)
// cos(a +/- b) = cos(a)cos(b) +/- sin(a)sin(b)
// tan(a +/- b) = (tan(a) +- tan(b))/(1 +/- tan(a)tan(b))
// polar (X,Y)
// quadratic (X,Y)
// bipolar +-X,+-Y            
// (X+Y)
// (X-Y)
// (X%Y)
// A - F*P*I
// A + F*P*I
// A % F*P*I
// (A+F) * P * I
// (A-F) * P * I 
// (A%F) * P * I             
// A * (F+P) * I 
// A * (F-P) * I
// A * (F%P) * I
// (A+I) * F * P 
// (A%I) * F * P
// A * I % (F*P)
// A * I + (F*P)
// A * I - (F*P)

template<typename T>
struct TOscillator
{
    T freq;
    T phase;    
    T period;
    T fs;
    std::function<(T (T,T,T))> generator;

    TOscillator(std::function<(T (T,T,T))> func, T freq, T sr) : generator(func), freq(f), fs(sr) { period = freq/fs; }
    // A * sin(2*PI*Index*(freq+fm)/fs+(phase+pm)
    T Tick(T A = 1, T fm = 0, T pm = 0) {              
        return A*generator(freq,phase,A,fm*freq,pm*period);     
    }  
    // Add = osc1 + osc2 ...
    // Modulate = osc1 * osc2 ...
    // Circular = osc1 % osc2 ...
};


template<typename T>
struct TWaveShaper
{
    std::function<T (T)> clipper;

    TWaveShaper(std::function<T (T)> f) : clipper(f) {}

    T Tick(T I, T A = 1) { return A*clipper(I); }
    // cascade = f(g(x))
    // add = f1 + f2 ...
    // Modulated = f1*f2..
    // Circular = f1%f2
};

// phase accumulator = Wrap(phase += inc)
template<typename T>
struct TPhaseAccumulator
{
    T phase;
    T inc;
    T freq;
    T sr;
    
    TPhaseAccumulator(T f, T fs) {
        phase = 0;
        inc = f/fs;
        freq = f;
        sr = fs;
    }
    T operatnr()() {
        phase += inc;
        if(phase >= 1.0) phase -= 1.0;
        return phase;
    }
    T inc() {
        return (*this)();
    }
    T set_frequency(T f) {
        freq = f;
        inc = f/sr;
    }
    int whole() { return (int)phase; }
    int fraction() { return phase - (int)phase; }
};

template<typename T>
struct TIntegrator
{
    T prev;

    TIntegrator() : prev(T(0)) {}

    T Tick(T I) {
        T r = I + prev;
        prev = I;
        return r;
    }
};

template<typename T>
struct TDifferentiator
{
    T prev;

    TIntegrator() : prev(T(0)) {}

    T Tick(T I) {
        T r = I - prev;
        prev = I;
        return r;
    }
};

template<typnemae T>
struct TRingBuffer
{
    sample_vector<T> buffer;

    TRingBuffer(size_t size) { buffer.resize(size); }

    T operator[](size_t n) { return buffer[n]; }
    size_t size() const { return buffer.size(); }
    T first() { return buffer[0]; }
    T last() { return buffer[buffer.size()-1]; }
    T insert(T x) {
        for(size_t i = 1; i < buffer.size()-1; i++) buffer[i] = buffer[i-1];
        T r = buffer[size()-1];
        buffer[0] = x;
        return r;
    }
    T get(size_t i) { return buffer[i]}; 
    T interpolate(T i) {
        float f = i - (int)i;
        int idx = (int)i;        
        if(idx >= size()-1) return buffer[idx-1];
        return f*buffer[idx] + (T(1)-f)*buffer[idx+1];
    }    
};

template<typnemae T>
struct TDelayLine
{
    sample_vector<T> buffer;

    TDelayLine(size_t size) { buffer.resize(size); }

    T operator[](size_t n) { return buffer[n]; }
    
    size_t size() const { return buffer.size(); }
    
    T first() { return buffer[0]; }
    
    T last() { return buffer[buffer.size()-1]; }
    
    T insert(T x) {
        for(size_t i = 1; i < buffer.size()-1; i++) buffer[i] = buffer[i-1];
        T r = buffer[size()-1];
        buffer[0] = x;
        return r;
    }
    
    T get(int i) { return buffer[i]; }
    
    T interpolate(T i) {
        int idx = (int)i;        
        if(idx >= size()) return buffer[size()-1];
        T f = i - idx;
        return f*buffer[idx] + (T(1)-f)*buffer[idx+1];
    }
};

template<typename T>
T parametric_modulation(T I1, T I2, T X, T Y) {
    return (I1*X)*(I2*Y);
}

template<typename T>
T parametric_modulus(T I1, T I2, T X, T Y) {
    return std::fmod(I1*X),(I2*Y));
}
template<typename T>
T parametric_dual_modulus(T I1, T I2, T X, T Y) {
    return std::fmod(std::fmod(I1,X)),std::fmod(I2,Y));
}

template<typname T>
T parametric_circle_x(float r, float theta) {
    return r * std::cos(theta);
}

template<typname T>
T parametric_circle_y(float r, float theta) {
    return r * std::sin(theta);
}

template<typename T>
T quadratic_solver_plus(T a, T b, T c)
{
    return (-b + std::sqrt(b*b - 4*a*c)) / (2*a);
}
template<typename T>
T quadratic_solver_minus(T a, T b, T c)
{
    return (-b - std::sqrt(b*b - 4*a*c)) / (2*a);
}

// unipolar positive [0..1]
// unipolar negative [-1..0]
// bipolar [-1..1]
// quadraitc [0,PI/2][PI/2,PI][PI,3PI/4][3PI/4,2PI]  ax + by +c = 0
// parametric circles x,y
// pwm unipolar positive
// x = saw + inverted saw 
// inverted saw = -saw out of phase 
// x = -saw + -inverted saw
// bipolar wave
// u = saw + isaw 
// n = -saw + -isaw
// x = u + n




