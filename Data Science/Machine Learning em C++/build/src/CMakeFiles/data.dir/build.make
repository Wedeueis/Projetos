# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wedeueis/Documentos/ufabc/am/programas/machine_learning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build

# Include any dependencies generated for this target.
include src/CMakeFiles/data.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/data.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/data.dir/flags.make

src/CMakeFiles/data.dir/data.cpp.o: src/CMakeFiles/data.dir/flags.make
src/CMakeFiles/data.dir/data.cpp.o: ../src/data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/data.dir/data.cpp.o"
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/data.dir/data.cpp.o -c /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/src/data.cpp

src/CMakeFiles/data.dir/data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data.dir/data.cpp.i"
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/src/data.cpp > CMakeFiles/data.dir/data.cpp.i

src/CMakeFiles/data.dir/data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data.dir/data.cpp.s"
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/src/data.cpp -o CMakeFiles/data.dir/data.cpp.s

src/CMakeFiles/data.dir/data.cpp.o.requires:

.PHONY : src/CMakeFiles/data.dir/data.cpp.o.requires

src/CMakeFiles/data.dir/data.cpp.o.provides: src/CMakeFiles/data.dir/data.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/data.dir/build.make src/CMakeFiles/data.dir/data.cpp.o.provides.build
.PHONY : src/CMakeFiles/data.dir/data.cpp.o.provides

src/CMakeFiles/data.dir/data.cpp.o.provides.build: src/CMakeFiles/data.dir/data.cpp.o


# Object files for target data
data_OBJECTS = \
"CMakeFiles/data.dir/data.cpp.o"

# External object files for target data
data_EXTERNAL_OBJECTS =

src/libdata.a: src/CMakeFiles/data.dir/data.cpp.o
src/libdata.a: src/CMakeFiles/data.dir/build.make
src/libdata.a: src/CMakeFiles/data.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdata.a"
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && $(CMAKE_COMMAND) -P CMakeFiles/data.dir/cmake_clean_target.cmake
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/data.dir/build: src/libdata.a

.PHONY : src/CMakeFiles/data.dir/build

src/CMakeFiles/data.dir/requires: src/CMakeFiles/data.dir/data.cpp.o.requires

.PHONY : src/CMakeFiles/data.dir/requires

src/CMakeFiles/data.dir/clean:
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src && $(CMAKE_COMMAND) -P CMakeFiles/data.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/data.dir/clean

src/CMakeFiles/data.dir/depend:
	cd /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wedeueis/Documentos/ufabc/am/programas/machine_learning /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/src /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src /home/wedeueis/Documentos/ufabc/am/programas/machine_learning/build/src/CMakeFiles/data.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/data.dir/depend
