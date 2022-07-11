swig -lua -c++ -Iinclude Std.i
gcc -std=c++17 -fmax-errors=1 -Iinclude -O2 -march=native -mavx2 -fPIC -shared -oStd.so Std_wrap.cxx include/gnuplot_i.c -lstdc++ -lm -lluajit-5.1 -Llib -lposix -ljsoncpp
