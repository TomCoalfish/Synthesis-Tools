swig -lua -I/usr/local/include portaudio.i
gcc -shared -fPIC -O2 -I/usr/local/include -L/usr/local/include -o luapa.so portaudio_wrap.c -lm -lportaudio -lluajit-5.1