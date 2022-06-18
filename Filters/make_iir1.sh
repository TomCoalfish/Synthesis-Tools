swig -lua -c++ -Iiir iir1.i
gcc -Iiir -O2 -march=native -mavx2 -fPIC -shared -o iir1.so iir1_wrap.cxx -lstdc++ -lm -lluajit -Lbin -lfir
