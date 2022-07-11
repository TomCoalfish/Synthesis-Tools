swig -python -c++ -Ikfr/include/kfr kfrdsp.i
g++ -std=c++17 -I/usr/local/include/pypy3.9 -fmax-errors=1 -O2 -march=native -fPIC -shared -o _kfrdsp.so kfrdsp_wrap.cxx -lstdc++ -lkfr_dft -lkfr_io

