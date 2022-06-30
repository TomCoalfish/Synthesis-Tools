# Synthesis Tools
Templated Synthesis Toolkit

# It is Stk + Gamma
* Stk has all the basics and the class hierarchy is nice and simple
* Gamma has all the functions that Stk is missing like FFT

# Templated
* Most of Stk is now templated
* It's not finished

# It's not really important
* You only use float or double anyways
* You can use long doubles but I don't think it has any kind of advantage
* It can't use fixed point integers 

# Fixed point
* STK doesn't seem to support it at all anyways

# With the template you could use SSE or AVX registers
* if you have a class that works like a floating point number

# Everything should just use doubles
* The only place where float is needed is going to the audio system or a file
* It can all be converted at the end of the pipeline to integers or float32s
