####
#### ATK configuration file for CMake
####

set(ATK_VERSION 3.3.0)

if()
  SET(IPPROOT )
  find_package(IPP)
  SET(FFT_INCLUDES )
  SET(FFT_LIBRARIES )
  SET(USE_IPP 1)
else(HAVE_IPP)
  if(ENABLE_GPL)
    FIND_PACKAGE(FFTW REQUIRED)
    SET(USE_FFTW 1)
    include_directories(/usr/include)
    SET(FFT_INCLUDES /usr/include)
    SET(FFT_LIBRARIES /usr/lib/x86_64-linux-gnu/libfftw3.so;/usr/lib/x86_64-linux-gnu/libfftw3f.so)
  else(ENABLE_GPL)
    MESSAGE(FATAL_ERROR "No FFT support")
  endif(ENABLE_GPL)
endif(HAVE_IPP)

include(/usr/local/lib/ATK.cmake)
