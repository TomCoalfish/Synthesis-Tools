# TStk
Templated Synthesis Toolkit

# It's not really important
* You only use float or double anyways
* You can use long doubles but I don't think it has any kind of advantage
* It can't use fixed point integers 

# Everything should just use doubles
* The only place where float is needed is going to the audio system or a file
* It can all be converted at the end of the pipeline to integers or float32s
