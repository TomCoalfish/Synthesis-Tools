swig -lua -c++ -Iinclude/Filters TOberheim.i
gcc -fmax-errors=1 -Iinclude/Filters -O2 -march=native -mavx2 -fPIC -shared -o TOberheim.so TOberheim_wrap.cxx -lstdc++ -lm -lluajit
