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
CMAKE_SOURCE_DIR = /home/quake/Projects/TStk/stk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/quake/Projects/TStk/stk/build

# Include any dependencies generated for this target.
include projects/demo/CMakeFiles/stk-demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include projects/demo/CMakeFiles/stk-demo.dir/compiler_depend.make

# Include the progress variables for this target.
include projects/demo/CMakeFiles/stk-demo.dir/progress.make

# Include the compile flags for this target's objects.
include projects/demo/CMakeFiles/stk-demo.dir/flags.make

projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o: projects/demo/CMakeFiles/stk-demo.dir/flags.make
projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o: /home/quake/Projects/TStk/stk/projects/demo/demo.cpp
projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o: projects/demo/CMakeFiles/stk-demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/TStk/stk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o -MF CMakeFiles/stk-demo.dir/demo.cpp.o.d -o CMakeFiles/stk-demo.dir/demo.cpp.o -c /home/quake/Projects/TStk/stk/projects/demo/demo.cpp

projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stk-demo.dir/demo.cpp.i"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/TStk/stk/projects/demo/demo.cpp > CMakeFiles/stk-demo.dir/demo.cpp.i

projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stk-demo.dir/demo.cpp.s"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/TStk/stk/projects/demo/demo.cpp -o CMakeFiles/stk-demo.dir/demo.cpp.s

projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o: projects/demo/CMakeFiles/stk-demo.dir/flags.make
projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o: /home/quake/Projects/TStk/stk/projects/demo/utilities.cpp
projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o: projects/demo/CMakeFiles/stk-demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/TStk/stk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o -MF CMakeFiles/stk-demo.dir/utilities.cpp.o.d -o CMakeFiles/stk-demo.dir/utilities.cpp.o -c /home/quake/Projects/TStk/stk/projects/demo/utilities.cpp

projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stk-demo.dir/utilities.cpp.i"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/TStk/stk/projects/demo/utilities.cpp > CMakeFiles/stk-demo.dir/utilities.cpp.i

projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stk-demo.dir/utilities.cpp.s"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/TStk/stk/projects/demo/utilities.cpp -o CMakeFiles/stk-demo.dir/utilities.cpp.s

# Object files for target stk-demo
stk__demo_OBJECTS = \
"CMakeFiles/stk-demo.dir/demo.cpp.o" \
"CMakeFiles/stk-demo.dir/utilities.cpp.o"

# External object files for target stk-demo
stk__demo_EXTERNAL_OBJECTS =

/home/quake/Projects/TStk/stk/projects/demo/stk-demo: projects/demo/CMakeFiles/stk-demo.dir/demo.cpp.o
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: projects/demo/CMakeFiles/stk-demo.dir/utilities.cpp.o
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: projects/demo/CMakeFiles/stk-demo.dir/build.make
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: /usr/lib/x86_64-linux-gnu/libjack.so
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: /usr/lib/x86_64-linux-gnu/libasound.so
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: libstk.a
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: /usr/lib/x86_64-linux-gnu/libjack.so
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: /usr/lib/x86_64-linux-gnu/libasound.so
/home/quake/Projects/TStk/stk/projects/demo/stk-demo: projects/demo/CMakeFiles/stk-demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/quake/Projects/TStk/stk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/quake/Projects/TStk/stk/projects/demo/stk-demo"
	cd /home/quake/Projects/TStk/stk/build/projects/demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stk-demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/demo/CMakeFiles/stk-demo.dir/build: /home/quake/Projects/TStk/stk/projects/demo/stk-demo
.PHONY : projects/demo/CMakeFiles/stk-demo.dir/build

projects/demo/CMakeFiles/stk-demo.dir/clean:
	cd /home/quake/Projects/TStk/stk/build/projects/demo && $(CMAKE_COMMAND) -P CMakeFiles/stk-demo.dir/cmake_clean.cmake
.PHONY : projects/demo/CMakeFiles/stk-demo.dir/clean

projects/demo/CMakeFiles/stk-demo.dir/depend:
	cd /home/quake/Projects/TStk/stk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/quake/Projects/TStk/stk /home/quake/Projects/TStk/stk/projects/demo /home/quake/Projects/TStk/stk/build /home/quake/Projects/TStk/stk/build/projects/demo /home/quake/Projects/TStk/stk/build/projects/demo/CMakeFiles/stk-demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/demo/CMakeFiles/stk-demo.dir/depend
