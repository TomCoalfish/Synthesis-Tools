swig -lua -c++ PolyBLEP.i
gcc -O2 -fPIC -march=native -mavx2 -shared -o PolyBLEP.so PolyBLEP_wrap.cxx PolyBLEP.cpp -lstdc++ -lm -lluajit
