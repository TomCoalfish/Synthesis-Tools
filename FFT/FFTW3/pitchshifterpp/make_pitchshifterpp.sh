swig -Iinclude/pitchshifterpp -lua -c++ pitchshifterpp.i
gcc -Iinclude/pitchshifterpp -O2 -fPIC -march=native -mavx2 -shared -o pitchshifterpp.so pitchshifterpp_wrap.cxx -lstdc++ -lm -lsndfile -lfftw3
