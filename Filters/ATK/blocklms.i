%module blocklms
%{
#include <fstream>
#include <iostream>
#include <cassert>

#include <ATK/Adaptive/BlockLMSFilter.h>
#include <ATK/Core/InPointerFilter.h>
#include <ATK/Core/OutPointerFilter.h>
#include <ATK/Core/Utilities.h>
//#include <ATK/Mock/SimpleSinusGeneratorFilter.h>
//#include <ATK/Mock/TriangleCheckerFilter.h>
#include <ATK/Tools/SumFilter.h>
#include <Eigen/Core>
#include <gtest/gtest.h>
#include <boost/math/constants/constants.hpp>
%}

%include "stdint.i"
%include "std_vector.i"

%inline %{

    template<typename T>
    struct BlockLMSFilter
    {
        ATK::BlockLMSFilter<T> * filter;

        BlockLMSFilter(size_t n, T in_sr=44100, T out_sr=44100, T mem=0.999, T mu=0.0001) {
            filter = ATK::BlockLMSFilter<T>(n);
            assert(filter != nullptr);
            SetInputSampleRate(in_sr);
            SetOutputSampleRate(out_sr);
            SetMem(mem);
            SetMu(mem);
        }
        ~BlockLMSFilter() {
            if(filter) delete filter;
        }

        void SetInputSampleRate(T sr) {
            filter->set_input_sampling_rate(sr);
        }
        void SetOutputSampleRate(T sr) {
            filter->set_output_sampling_rate(sr);
        }
        void SetMemory(T mem) {
            filter->set_memory(mem);
        }
        void SetMu(T mu) {
            filter->set_mu(mu);
        }

        void SetInputPort(size_t n, T * data, size_t x) {
            filter->set_input_port(n,data,x);
        }
        void SetOutputPort(size_t n, T * data, size_t x) {
            filter->set_output_port(n,data,x);
        }

        void Process(size_t n) {
            filter->process(n);
        }

    };

%}

%template(FloatBlockLMSFilter) BlockLMSFilter<float>;
%template(DoubleBlockLMSFilter) BlockLMSFilter<double>;