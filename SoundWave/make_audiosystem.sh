swig -lua -I/usr/local/include audiosystem.i
gcc -fpermissive -I/usr/local/include -O2 -march=native -mavx2 -fPIC -shared -o audiosystem.so audiosystem_wrap.c -pthread -lrt -lm -lluajit -L/usr/local/lib -lportaudio -lportmidi
