# TStk
Templated Synthesis Toolkit

# Almost finished
* Working on it
 
# SIMD, Fixed point
* The idea is that with the templates you can be able to use vectorizer classes
* I have a fixed point class that is like a floating point number
* You just make the template use the class
* For SIMD it needs some work on Stk frames to make it compatible with the classes
* I have SSE and AVX 
* Possible library you can use like Vc with Gcc 

# So then all the classes now work on the type
* I removed some baggage from the main Stk class as it made templated awkward
* In some places I took enums out of the class as it's just a real mouthful having to access it
* In other cases I added enums for the old static values and changed them into enums

# Some classes shouldn't be a template
* It just doesn't sense to make MidiFileIn template float a whole lot
* So I might dissect Stk base class a bit and make a new one that is not templated
* It's not a huge deal but I just think it's awkward as everything derived from the Stk base class
* And that needed to be templated to work
* SO either I will make Stk base class not a template at all or something else
