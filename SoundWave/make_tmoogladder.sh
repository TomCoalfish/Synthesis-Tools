swig -lua -c++ -Iinclude/Filters TMoogLadder.i
gcc -fmax-errors=1 -Iinclude/Filters -O2 -march=native -mavx2 -fPIC -shared -o TMoogLadder.so TMoogLadder_wrap.cxx -lstdc++ -lm -lluajit
