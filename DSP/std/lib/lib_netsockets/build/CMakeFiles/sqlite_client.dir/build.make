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
include CMakeFiles/sqlite_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sqlite_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sqlite_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sqlite_client.dir/flags.make

CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o: CMakeFiles/sqlite_client.dir/flags.make
CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sqlite_client.cc
CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o: CMakeFiles/sqlite_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o -MF CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o.d -o CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sqlite_client.cc

CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sqlite_client.cc > CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.i

CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sqlite_client.cc -o CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.s

CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o: CMakeFiles/sqlite_client.dir/flags.make
CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sql_message.cc
CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o: CMakeFiles/sqlite_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o -MF CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o.d -o CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sql_message.cc

CMakeFiles/sqlite_client.dir/examples/sql_message.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqlite_client.dir/examples/sql_message.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sql_message.cc > CMakeFiles/sqlite_client.dir/examples/sql_message.cc.i

CMakeFiles/sqlite_client.dir/examples/sql_message.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqlite_client.dir/examples/sql_message.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/examples/sql_message.cc -o CMakeFiles/sqlite_client.dir/examples/sql_message.cc.s

CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o: CMakeFiles/sqlite_client.dir/flags.make
CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/sqlite-3.18.0/sqlite3.c
CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o: CMakeFiles/sqlite_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o -MF CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o.d -o CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/sqlite-3.18.0/sqlite3.c

CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/sqlite-3.18.0/sqlite3.c > CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.i

CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/sqlite-3.18.0/sqlite3.c -o CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.s

CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o: CMakeFiles/sqlite_client.dir/flags.make
CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o: /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp
CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o: CMakeFiles/sqlite_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o -MF CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o.d -o CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o -c /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp

CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp > CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.i

CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/external/gason/src/gason.cpp -o CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.s

# Object files for target sqlite_client
sqlite_client_OBJECTS = \
"CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o" \
"CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o" \
"CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o" \
"CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o"

# External object files for target sqlite_client
sqlite_client_EXTERNAL_OBJECTS =

sqlite_client: CMakeFiles/sqlite_client.dir/examples/sqlite_client.cc.o
sqlite_client: CMakeFiles/sqlite_client.dir/examples/sql_message.cc.o
sqlite_client: CMakeFiles/sqlite_client.dir/external/sqlite-3.18.0/sqlite3.c.o
sqlite_client: CMakeFiles/sqlite_client.dir/external/gason/src/gason.cpp.o
sqlite_client: CMakeFiles/sqlite_client.dir/build.make
sqlite_client: liblib_netsockets.a
sqlite_client: CMakeFiles/sqlite_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable sqlite_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqlite_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sqlite_client.dir/build: sqlite_client
.PHONY : CMakeFiles/sqlite_client.dir/build

CMakeFiles/sqlite_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sqlite_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sqlite_client.dir/clean

CMakeFiles/sqlite_client.dir/depend:
	cd /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build /home/quake/Projects/LuaJIT-Std/lib_netsockets/lib_netsockets/build/CMakeFiles/sqlite_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sqlite_client.dir/depend
