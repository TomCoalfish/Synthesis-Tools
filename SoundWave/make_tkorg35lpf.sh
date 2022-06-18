swig -lua -c++ -Iinclude/Filters TKorg35LPF.i
gcc -fmax-errors=1 -Iinclude/Filters -O2 -march=native -mavx2 -fPIC -shared -o TKorg35LPF.so TKorg35LPF_wrap.cxx -lstdc++ -lm -lluajit
