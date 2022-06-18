swig -lua -c++ SoundWave.i
gcc -Llib -DAUDIOFFT_FFTW3 -fmax-errors=1 -I/usr/local/include/kissfft -O2 -march=native -mavx2 -fPIC -shared -o soundwave.so SoundWave_wrap.cxx libSoundWave.a -lstdc++ -lm -lluajit -L../lib -lsndfile -lkissfft-float -lsamplerate
