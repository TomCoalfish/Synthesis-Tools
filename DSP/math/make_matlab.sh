swig -lua -c++ armadillo.i
gcc -fmax-errors=1 -O2 -fPIC -march=native -mavx2 -shared -o arma.so armadillo_wrap.cxx -lstdc++ -lm -lluajit -larmadillo
