swig -I../include/Std -lua -c++ noisey.i
gcc -fmax-errors=1 -I../include/Std -O2 -fPIC -shared -o noisey.so noisey_wrap.cxx -lstdc++ -lm -lluajit
