swig -lua -c++ kiss_complex.i
swig -lua -c++ kiss_real.i
gcc -I/usr/local/include/kissfft -L/usr/local/lib -O2 -march=native -mavx2 -fPIC -shared -o kiss_complex.so kiss_complex_wrap.cxx -lstdc++ -lm -lluajit -lkissfft-float
gcc -I/usr/local/include/kissfft -L/usr/local/lib -O2 -march=native -mavx2 -fPIC -shared -o kiss_real.so kiss_real_wrap.cxx -lstdc++ -lm -lluajit -lkissfft-float
