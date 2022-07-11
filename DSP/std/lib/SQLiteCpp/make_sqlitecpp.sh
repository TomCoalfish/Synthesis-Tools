swig -Iinclude -lua -c++ sqlitecpp.i
gcc -fmax-errors=1 -Iinclude -O2 -fPIC -shared -o sqlitecpp.so sqlitecpp_wrap.cxx -lstdc++ -lm -lluajit -L. -lSQLiteCpp -lsqlite3 -pthread
