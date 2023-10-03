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
CMAKE_SOURCE_DIR = /home/tomsabala/workspace/proj/geomtery/CGEO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tomsabala/workspace/proj/geomtery/CGEO/build

# Include any dependencies generated for this target.
include src/data_structures/CMakeFiles/Datastructures2D.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/data_structures/CMakeFiles/Datastructures2D.dir/compiler_depend.make

# Include the progress variables for this target.
include src/data_structures/CMakeFiles/Datastructures2D.dir/progress.make

# Include the compile flags for this target's objects.
include src/data_structures/CMakeFiles/Datastructures2D.dir/flags.make

src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o: src/data_structures/CMakeFiles/Datastructures2D.dir/flags.make
src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o: ../src/data_structures/SegmentBalancedTree.cpp
src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o: src/data_structures/CMakeFiles/Datastructures2D.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomsabala/workspace/proj/geomtery/CGEO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o"
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o -MF CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o.d -o CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o -c /home/tomsabala/workspace/proj/geomtery/CGEO/src/data_structures/SegmentBalancedTree.cpp

src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.i"
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomsabala/workspace/proj/geomtery/CGEO/src/data_structures/SegmentBalancedTree.cpp > CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.i

src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.s"
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomsabala/workspace/proj/geomtery/CGEO/src/data_structures/SegmentBalancedTree.cpp -o CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.s

# Object files for target Datastructures2D
Datastructures2D_OBJECTS = \
"CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o"

# External object files for target Datastructures2D
Datastructures2D_EXTERNAL_OBJECTS =

src/data_structures/libDatastructures2D.so: src/data_structures/CMakeFiles/Datastructures2D.dir/SegmentBalancedTree.cpp.o
src/data_structures/libDatastructures2D.so: src/data_structures/CMakeFiles/Datastructures2D.dir/build.make
src/data_structures/libDatastructures2D.so: src/2D/shapes_2D/libShapes2D.so
src/data_structures/libDatastructures2D.so: src/data_structures/CMakeFiles/Datastructures2D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomsabala/workspace/proj/geomtery/CGEO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libDatastructures2D.so"
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Datastructures2D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/data_structures/CMakeFiles/Datastructures2D.dir/build: src/data_structures/libDatastructures2D.so
.PHONY : src/data_structures/CMakeFiles/Datastructures2D.dir/build

src/data_structures/CMakeFiles/Datastructures2D.dir/clean:
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures && $(CMAKE_COMMAND) -P CMakeFiles/Datastructures2D.dir/cmake_clean.cmake
.PHONY : src/data_structures/CMakeFiles/Datastructures2D.dir/clean

src/data_structures/CMakeFiles/Datastructures2D.dir/depend:
	cd /home/tomsabala/workspace/proj/geomtery/CGEO/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomsabala/workspace/proj/geomtery/CGEO /home/tomsabala/workspace/proj/geomtery/CGEO/src/data_structures /home/tomsabala/workspace/proj/geomtery/CGEO/build /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures /home/tomsabala/workspace/proj/geomtery/CGEO/build/src/data_structures/CMakeFiles/Datastructures2D.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/data_structures/CMakeFiles/Datastructures2D.dir/depend

