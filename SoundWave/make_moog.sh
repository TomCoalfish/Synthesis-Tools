swig -lua -c++ MoogLadders.i
gcc -I../include/MoogLadders -O2 -fPIC -mavx2 -march=native -shared -o MoogLadders.so MoogLadders_wrap.cxx -lstdc++ -lm -lluajit
