swig -lua -c++ TDiodeLadder.i
gcc -fmax-errors=1 -O2 -fPIC -march=native -mavx2 -shared -o TDiodeLadder.so TDiodeLadder_wrap.cxx -lstdc++ -lm -lluajit
