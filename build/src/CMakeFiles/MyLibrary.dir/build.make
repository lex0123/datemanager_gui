# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lizheng/Desktop/123/gitdirectory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lizheng/Desktop/123/gitdirectory/build

# Include any dependencies generated for this target.
include src/CMakeFiles/MyLibrary.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/MyLibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/MyLibrary.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MyLibrary.dir/flags.make

src/CMakeFiles/MyLibrary.dir/gui.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/gui.cpp.o: ../src/gui.cpp
src/CMakeFiles/MyLibrary.dir/gui.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lizheng/Desktop/123/gitdirectory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/MyLibrary.dir/gui.cpp.o"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/gui.cpp.o -MF CMakeFiles/MyLibrary.dir/gui.cpp.o.d -o CMakeFiles/MyLibrary.dir/gui.cpp.o -c /home/lizheng/Desktop/123/gitdirectory/src/gui.cpp

src/CMakeFiles/MyLibrary.dir/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/gui.cpp.i"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lizheng/Desktop/123/gitdirectory/src/gui.cpp > CMakeFiles/MyLibrary.dir/gui.cpp.i

src/CMakeFiles/MyLibrary.dir/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/gui.cpp.s"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lizheng/Desktop/123/gitdirectory/src/gui.cpp -o CMakeFiles/MyLibrary.dir/gui.cpp.s

src/CMakeFiles/MyLibrary.dir/task.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/task.cpp.o: ../src/task.cpp
src/CMakeFiles/MyLibrary.dir/task.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lizheng/Desktop/123/gitdirectory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/MyLibrary.dir/task.cpp.o"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/task.cpp.o -MF CMakeFiles/MyLibrary.dir/task.cpp.o.d -o CMakeFiles/MyLibrary.dir/task.cpp.o -c /home/lizheng/Desktop/123/gitdirectory/src/task.cpp

src/CMakeFiles/MyLibrary.dir/task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/task.cpp.i"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lizheng/Desktop/123/gitdirectory/src/task.cpp > CMakeFiles/MyLibrary.dir/task.cpp.i

src/CMakeFiles/MyLibrary.dir/task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/task.cpp.s"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lizheng/Desktop/123/gitdirectory/src/task.cpp -o CMakeFiles/MyLibrary.dir/task.cpp.s

src/CMakeFiles/MyLibrary.dir/user.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/user.cpp.o: ../src/user.cpp
src/CMakeFiles/MyLibrary.dir/user.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lizheng/Desktop/123/gitdirectory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/MyLibrary.dir/user.cpp.o"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/user.cpp.o -MF CMakeFiles/MyLibrary.dir/user.cpp.o.d -o CMakeFiles/MyLibrary.dir/user.cpp.o -c /home/lizheng/Desktop/123/gitdirectory/src/user.cpp

src/CMakeFiles/MyLibrary.dir/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/user.cpp.i"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lizheng/Desktop/123/gitdirectory/src/user.cpp > CMakeFiles/MyLibrary.dir/user.cpp.i

src/CMakeFiles/MyLibrary.dir/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/user.cpp.s"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lizheng/Desktop/123/gitdirectory/src/user.cpp -o CMakeFiles/MyLibrary.dir/user.cpp.s

# Object files for target MyLibrary
MyLibrary_OBJECTS = \
"CMakeFiles/MyLibrary.dir/gui.cpp.o" \
"CMakeFiles/MyLibrary.dir/task.cpp.o" \
"CMakeFiles/MyLibrary.dir/user.cpp.o"

# External object files for target MyLibrary
MyLibrary_EXTERNAL_OBJECTS =

src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/gui.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/task.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/user.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/build.make
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lizheng/Desktop/123/gitdirectory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libMyLibrary.a"
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MyLibrary.dir/cmake_clean_target.cmake
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyLibrary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MyLibrary.dir/build: src/libMyLibrary.a
.PHONY : src/CMakeFiles/MyLibrary.dir/build

src/CMakeFiles/MyLibrary.dir/clean:
	cd /home/lizheng/Desktop/123/gitdirectory/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MyLibrary.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MyLibrary.dir/clean

src/CMakeFiles/MyLibrary.dir/depend:
	cd /home/lizheng/Desktop/123/gitdirectory/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lizheng/Desktop/123/gitdirectory /home/lizheng/Desktop/123/gitdirectory/src /home/lizheng/Desktop/123/gitdirectory/build /home/lizheng/Desktop/123/gitdirectory/build/src /home/lizheng/Desktop/123/gitdirectory/build/src/CMakeFiles/MyLibrary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MyLibrary.dir/depend
