# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/quake/Projects/grizzly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/quake/Projects/grizzly/build

# Include any dependencies generated for this target.
include CMakeFiles/grizzly.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/grizzly.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/grizzly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grizzly.dir/flags.make

CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o: CMakeFiles/grizzly.dir/flags.make
CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o: /home/quake/Projects/grizzly/FastFourierTransformBase.cpp
CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o: CMakeFiles/grizzly.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/grizzly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o -MF CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o.d -o CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o -c /home/quake/Projects/grizzly/FastFourierTransformBase.cpp

CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/grizzly/FastFourierTransformBase.cpp > CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.i

CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/grizzly/FastFourierTransformBase.cpp -o CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.s

CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o: CMakeFiles/grizzly.dir/flags.make
CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o: /home/quake/Projects/grizzly/Ooura/FastFourierTransformOoura.cpp
CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o: CMakeFiles/grizzly.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/grizzly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o -MF CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o.d -o CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o -c /home/quake/Projects/grizzly/Ooura/FastFourierTransformOoura.cpp

CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/grizzly/Ooura/FastFourierTransformOoura.cpp > CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.i

CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/grizzly/Ooura/FastFourierTransformOoura.cpp -o CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.s

CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o: CMakeFiles/grizzly.dir/flags.make
CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o: /home/quake/Projects/grizzly/Ooura/fftsg.cpp
CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o: CMakeFiles/grizzly.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/grizzly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o -MF CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o.d -o CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o -c /home/quake/Projects/grizzly/Ooura/fftsg.cpp

CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/grizzly/Ooura/fftsg.cpp > CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.i

CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/grizzly/Ooura/fftsg.cpp -o CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.s

# Object files for target grizzly
grizzly_OBJECTS = \
"CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o" \
"CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o" \
"CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o"

# External object files for target grizzly
grizzly_EXTERNAL_OBJECTS =

libgrizzly.so: CMakeFiles/grizzly.dir/FastFourierTransformBase.cpp.o
libgrizzly.so: CMakeFiles/grizzly.dir/Ooura/FastFourierTransformOoura.cpp.o
libgrizzly.so: CMakeFiles/grizzly.dir/Ooura/fftsg.cpp.o
libgrizzly.so: CMakeFiles/grizzly.dir/build.make
libgrizzly.so: CMakeFiles/grizzly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/quake/Projects/grizzly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libgrizzly.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grizzly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grizzly.dir/build: libgrizzly.so
.PHONY : CMakeFiles/grizzly.dir/build

CMakeFiles/grizzly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/grizzly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/grizzly.dir/clean

CMakeFiles/grizzly.dir/depend:
	cd /home/quake/Projects/grizzly/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/quake/Projects/grizzly /home/quake/Projects/grizzly /home/quake/Projects/grizzly/build /home/quake/Projects/grizzly/build /home/quake/Projects/grizzly/build/CMakeFiles/grizzly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grizzly.dir/depend

