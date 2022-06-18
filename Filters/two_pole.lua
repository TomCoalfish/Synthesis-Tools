

function make_twopolelp(freq,q,samplerate)
    local f = {}
    f.c = 2*sin(pi*freq/samplerate)
    f.r = 1/q
    f.process = twopolelp_process
    return f
end 

function twopolelp_process(filt,input)
    f.v0 = (1-r*c)*v0 - c*v1 + c*input;
    f.v1 = (1-r*c)*v1 + c*v0;
    local tmp = f.v1;

    f.v0 = (1-f.r*f.c)*f.v0 - f.c*f.v1 + f.c*input;
    f.v1 = (1-f.r*f.c)*f.v1 + f.c*f.v0;
    f.output = (tmp+v1)*0.5;
    return f.output 
end 