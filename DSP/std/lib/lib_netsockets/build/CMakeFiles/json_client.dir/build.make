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
CMAKE_SOURCE_DIR = /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build

# Include any dependencies generated for this target.
include CMakeFiles/json_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/json_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/json_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/json_client.dir/flags.make

CMakeFiles/json_client.dir/examples/json_client.cc.o: CMakeFiles/json_client.dir/flags.make
CMakeFiles/json_client.dir/examples/json_client.cc.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_client.cc
CMakeFiles/json_client.dir/examples/json_client.cc.o: CMakeFiles/json_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/json_client.dir/examples/json_client.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/json_client.dir/examples/json_client.cc.o -MF CMakeFiles/json_client.dir/examples/json_client.cc.o.d -o CMakeFiles/json_client.dir/examples/json_client.cc.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_client.cc

CMakeFiles/json_client.dir/examples/json_client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_client.dir/examples/json_client.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_client.cc > CMakeFiles/json_client.dir/examples/json_client.cc.i

CMakeFiles/json_client.dir/examples/json_client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_client.dir/examples/json_client.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_client.cc -o CMakeFiles/json_client.dir/examples/json_client.cc.s

CMakeFiles/json_client.dir/examples/json_message.cc.o: CMakeFiles/json_client.dir/flags.make
CMakeFiles/json_client.dir/examples/json_message.cc.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_message.cc
CMakeFiles/json_client.dir/examples/json_message.cc.o: CMakeFiles/json_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/json_client.dir/examples/json_message.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/json_client.dir/examples/json_message.cc.o -MF CMakeFiles/json_client.dir/examples/json_message.cc.o.d -o CMakeFiles/json_client.dir/examples/json_message.cc.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_message.cc

CMakeFiles/json_client.dir/examples/json_message.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_client.dir/examples/json_message.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_message.cc > CMakeFiles/json_client.dir/examples/json_message.cc.i

CMakeFiles/json_client.dir/examples/json_message.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_client.dir/examples/json_message.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/json_message.cc -o CMakeFiles/json_client.dir/examples/json_message.cc.s

CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o: CMakeFiles/json_client.dir/flags.make
CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp
CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o: CMakeFiles/json_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o -MF CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o.d -o CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp

CMakeFiles/json_client.dir/external/gason/src/gason.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/json_client.dir/external/gason/src/gason.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp > CMakeFiles/json_client.dir/external/gason/src/gason.cpp.i

CMakeFiles/json_client.dir/external/gason/src/gason.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/json_client.dir/external/gason/src/gason.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp -o CMakeFiles/json_client.dir/external/gason/src/gason.cpp.s

# Object files for target json_client
json_client_OBJECTS = \
"CMakeFiles/json_client.dir/examples/json_client.cc.o" \
"CMakeFiles/json_client.dir/examples/json_message.cc.o" \
"CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o"

# External object files for target json_client
json_client_EXTERNAL_OBJECTS =

json_client: CMakeFiles/json_client.dir/examples/json_client.cc.o
json_client: CMakeFiles/json_client.dir/examples/json_message.cc.o
json_client: CMakeFiles/json_client.dir/external/gason/src/gason.cpp.o
json_client: CMakeFiles/json_client.dir/build.make
json_client: liblib_netsockets.a
json_client: CMakeFiles/json_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable json_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/json_client.dir/build: json_client
.PHONY : CMakeFiles/json_client.dir/build

CMakeFiles/json_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/json_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/json_client.dir/clean

CMakeFiles/json_client.dir/depend:
	cd /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles/json_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/json_client.dir/depend
