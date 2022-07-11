# Install script for directory: /home/quake/Projects/grizzly

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/quake/Projects/grizzly/build/libgrizzly.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libgrizzly.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/grizzly" TYPE FILE FILES
    "/home/quake/Projects/grizzly/AllPassFilter.hpp"
    "/home/quake/Projects/grizzly/AnalogOnePoleFilter.hpp"
    "/home/quake/Projects/grizzly/AnalyticTransform.hpp"
    "/home/quake/Projects/grizzly/Biquad.hpp"
    "/home/quake/Projects/grizzly/BiquadCoefficients.hpp"
    "/home/quake/Projects/grizzly/CircularBuffer.hpp"
    "/home/quake/Projects/grizzly/CombFilter.hpp"
    "/home/quake/Projects/grizzly/Convolution.hpp"
    "/home/quake/Projects/grizzly/Delay.hpp"
    "/home/quake/Projects/grizzly/DownSample.hpp"
    "/home/quake/Projects/grizzly/Dynamic.hpp"
    "/home/quake/Projects/grizzly/EnvelopeDetector.hpp"
    "/home/quake/Projects/grizzly/FastFourierTransform.hpp"
    "/home/quake/Projects/grizzly/FastFourierTransformBase.hpp"
    "/home/quake/Projects/grizzly/FirstOrderCoefficients.hpp"
    "/home/quake/Projects/grizzly/FirstOrderFilter.hpp"
    "/home/quake/Projects/grizzly/GordonSmithOscillator.hpp"
    "/home/quake/Projects/grizzly/HilbertTransform.hpp"
    "/home/quake/Projects/grizzly/HighFrequencyContent.hpp"
    "/home/quake/Projects/grizzly/ImpulseResponse.hpp"
    "/home/quake/Projects/grizzly/MidSide.hpp"
    "/home/quake/Projects/grizzly/MultiTapResonator.hpp"
    "/home/quake/Projects/grizzly/Ramp.hpp"
    "/home/quake/Projects/grizzly/SegmentEnvelope.hpp"
    "/home/quake/Projects/grizzly/ShortTimeFourierTransform.hpp"
    "/home/quake/Projects/grizzly/SpectralCentroid.hpp"
    "/home/quake/Projects/grizzly/Spectrum.hpp"
    "/home/quake/Projects/grizzly/UpSample.hpp"
    "/home/quake/Projects/grizzly/Waveform.hpp"
    "/home/quake/Projects/grizzly/Window.hpp"
    "/home/quake/Projects/grizzly/ZTransform.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/grizzly/Ooura" TYPE FILE FILES
    "/home/quake/Projects/grizzly/Ooura/FastFourierTransformOoura.hpp"
    "/home/quake/Projects/grizzly/Ooura/fftsg.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/quake/Projects/grizzly/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
