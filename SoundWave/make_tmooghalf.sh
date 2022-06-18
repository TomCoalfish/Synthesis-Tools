swig -lua -c++ -Iinclude/Filters TMoogHalfLadder.i
gcc -fmax-errors=1 -Iinclude/Filters -O2 -fPIC -march=native -mavx2 -shared -o TMoogHalfLadder.so TMoogHalfLadder_wrap.cxx -lstdc++ -lm -lluajit
