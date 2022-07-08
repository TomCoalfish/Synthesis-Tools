# TStk
Templated Synthesis Toolkit

# Almost finished
* Working on it
 
# Templates
* With template you can use it for all kinds of types
* Fixed point, SIMD, GPU
* I haven't tested the idea at all yet with it but that is the Gist

# Simd
* I have some classes to start with for SSE and AVX
* float4 and float8
* So you make the StkFrames a template of those types
* Then you can acclerate the Stk with them
* But it needs to have aligned memory allocator first

# GPU
* I have tiny linear algebra I made with cublas called Viperfish
* I will eventually try to use it and see if I can accelerate Stk with the GPU
