swig -lua -c++ -I/usr/include smf.i
gcc -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -O2 -fPIC -march=native -mavx2 -shared -o smf.so smf_wrap.cxx -lstdc++ -lm -lluajit -lsmf
