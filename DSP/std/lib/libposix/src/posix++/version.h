/* This is free and unencumbered software released into the public domain. */

#ifndef POSIXXX_VERSION_H
#define POSIXXX_VERSION_H

#ifndef __cplusplus
#error "<posix++/version.h> requires a C++ compiler"
#endif

////////////////////////////////////////////////////////////////////////////////

#include <string> /* for std::string */

namespace posix {
  namespace version {
    const std::string string = "6335b6d-dirty";
    const short major = 0;
    const short minor = 0;
    const short patch = 0;
  };
}

////////////////////////////////////////////////////////////////////////////////

#endif /* POSIXXX_VERSION_H */
