%module netsockets
%{
#include "socket.hh"
#include "http.hh"
#include "ftp.hh"
%}

%include "socket.hh"
%include "http.hh"
%include "ftp.hh"

