/**
 * \file config.h
 */

#ifndef ATK_CONFIG_H
#define ATK_CONFIG_H

#define ATK_PROFILING 0

#define ATK_USE_LIBSNDFILE 1

#define ATK_USE_FFTW 1
#define ATK_USE_IPP 0
#define ATK_USE_THREADPOOL 0
#define ATK_USE_SIMD 0
#define ATK_ENABLE_INSTANTIATION 1

#define ATK_SOURCE_TREE "/home/quake/Projects/SynthWave/filters/ATK"

#if defined __INTEL_COMPILER
# define ATK_RESTRICT restrict
# define ATK_VECTORIZE __pragma(simd)
# define ATK_VECTORIZE_REMAINDER __pragma(simd vecremainder)
#elif defined _MSC_VER
# define ATK_RESTRICT __restrict
# define ATK_VECTORIZE __pragma(loop(hint_parallel(8)))
# define ATK_VECTORIZE_REMAINDER
#elif defined __clang__
# define ATK_RESTRICT __restrict__
# define ATK_VECTORIZE _Pragma("clang loop vectorize(enable) interleave(enable)")
# define ATK_VECTORIZE_REMAINDER
#elif defined __GNUC__
# define ATK_RESTRICT __restrict__
# define ATK_VECTORIZE
# define ATK_VECTORIZE_REMAINDER
#else
# define ATK_RESTRICT
# define ATK_VECTORIZE
# define ATK_VECTORIZE_REMAINDER
#endif

#endif
