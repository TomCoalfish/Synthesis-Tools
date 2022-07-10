# TStk
Templated Synthesis Toolkit

# Conversion is finished
* At least, it all compiles now
* Hopefully did not break anything converting it
* Now will test stuff 

# Gamma
* Gamma has alot of useful functions some that Stk doesnt like STFT
* I am making it to it will work with Stk like an extensions for algorithms
* It is not really difficult as it's all mostly templates
* It has a peculiar audio scheduler in it you can use as the audio system 


# SIMD, Fixed point
* The idea is that with the templates you can be able to use vectorizer classes
* I have a fixed point class that is like a floating point number
* You just make the template use the class
* I have SSE and AVX vector classes
* Needs aligned memory
* Possible library you can use like Vc with Gcc 
* We can modify to work on ARM too later

# Viperfish
* A tiny cublas linear algebra for the GPU
* It is pretty fast as long as everything stays on the GPU
* It won't work with Stk unless you rewrite them into Cuda which I am not going to do
* But it does have vector expression and I may use nvrtc so you can compile Jit expression on the GPU

# Mkl/IPP
* I will hook it into Stk with some codes I have
* Some linear algebra vector/matrix
* Arrays and aligned std::vector
* You can use Intel IPP DSP functions

# CSound
* Can run CSound files
* Set ksmps to the size of the audio buffer

# FaustGTK
* can run Faust scripts as Stk class with GTK gui
* YOu don't have to have the GUI if you don't want it

# LuaJIT
* embed LuaJIT 

# GNU Octave
* Run octave scripts
* Call octave functions

