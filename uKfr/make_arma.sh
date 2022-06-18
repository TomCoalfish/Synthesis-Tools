swig -lua -c++ -Iinclude armadillo.i
gcc -std=c++11 -Iinclude -fmax-errors=1 -O2 -fPIC -march=native -mavx2 -shared -o arma.so armadillo_wrap.cxx -lstdc++ -lm -lluajit -larmadillo
