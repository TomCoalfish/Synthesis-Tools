swig -lua -c++ -Iinclude onposix.i
gcc -Iinclude -O2 -fPIC -march=native -mavx2 -shared -o onposix.so onposix_wrap.cxx -lstdc++ -lm -lluajit-5.1 -L. -lonposix
