swig -lua -c++ -I/usr/local/include/eigen3 array.i
gcc -fmax-errors=1 -I/usr/local/include/eigen3 -O2 -fPIC -march=native -mavx2 -shared -o eigen_array.so array_wrap.cxx -lstdc++ -lm -lluajit
