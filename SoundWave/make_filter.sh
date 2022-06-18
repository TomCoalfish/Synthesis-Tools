swig -lua -c++ Filter.i
gcc -O2 -fPIC -march=native -mavx2 -shared -o Filter.so Filter_wrap.cxx -lstdc++ -lm -lluajit
