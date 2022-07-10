# TStk
Templated Synthesis Toolkit

# Conversion is finished
* At least, it all compiles now
* Hopefully did not break anything converting it
* Now will test stuff 

# SIMD, Fixed point
* The idea is that with the templates you can be able to use vectorizer classes
* I have a fixed point class that is like a floating point number
* You just make the template use the class
* I have SSE and AVX vector classes
* Needs aligned memory
* Possible library you can use like Vc with Gcc 
* We can modify to work on ARM too later

# CSound
* Can run CSound files
* Set ksmps to the size of the audio buffer

# FaustGTK
* can run Faust scripts as Stk class with GTK gui

# LuaJIT
* embed LuaJIT 

# GNU Octave
* Run octave scripts
* Call octave functions

