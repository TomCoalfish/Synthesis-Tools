swig -lua -c++ -Iinclude gnuplot.i
gcc -fpermissive -Iinclude -O2 -fPIC -shared -o plot.so gnuplot_wrap.cxx include/gnuplot_i.c -lstdc++ -lm -lluajit-5.1
