swig -lua -c++ adsr.i
gcc -O2 -fPIC -march=native -mavx2 -fPIC -shared -o adsr.so adsr_wrap.cxx ADSR.cpp -lstdc++ -lm -lluajit
