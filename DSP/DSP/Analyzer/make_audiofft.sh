swig -lua -c++ -Iinclude src/audiofft.i
gcc -DAUDIOFFT_FFTW3 -Iinclude -O2 -fPIC -march=native -mavx2 -shared -o audiofft.so src/audiofft_wrap.cxx src/AudioFFT.cpp -lstdc++ -lm -lluajit -lfftw3 -lfftw3f
