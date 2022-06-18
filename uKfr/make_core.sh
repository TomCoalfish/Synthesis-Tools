swig -lua -c++ -Iinclude/Kfr -I/usr/local/include/kfr kfr.i
gcc -std=c++17 -fmax-errors=1  -Iinclude/Kfr -O2 -fPIC -march=native -mavx2 -shared -o kfr.so kfr_wrap.cxx -lstdc++ -lm -lluajit -lkfr_dft -lkfr_io 
