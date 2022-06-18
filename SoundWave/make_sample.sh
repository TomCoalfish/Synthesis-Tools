swig -lua -c++ sample.i
gcc -I../include -O2 -fPIC -march=native -mavx2 -shared -o sample.so sample_wrap.cxx -lstdc++ -lm -lluajit
