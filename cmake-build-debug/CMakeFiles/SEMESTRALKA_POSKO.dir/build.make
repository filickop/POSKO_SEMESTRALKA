# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /tmp/tmp.B5VJnpLHyD

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.B5VJnpLHyD/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SEMESTRALKA_POSKO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SEMESTRALKA_POSKO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SEMESTRALKA_POSKO.dir/flags.make

CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o: CMakeFiles/SEMESTRALKA_POSKO.dir/flags.make
CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.B5VJnpLHyD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o -c /tmp/tmp.B5VJnpLHyD/main.c

CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.B5VJnpLHyD/main.c > CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.i

CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.B5VJnpLHyD/main.c -o CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.s

# Object files for target SEMESTRALKA_POSKO
SEMESTRALKA_POSKO_OBJECTS = \
"CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o"

# External object files for target SEMESTRALKA_POSKO
SEMESTRALKA_POSKO_EXTERNAL_OBJECTS =

SEMESTRALKA_POSKO: CMakeFiles/SEMESTRALKA_POSKO.dir/main.c.o
SEMESTRALKA_POSKO: CMakeFiles/SEMESTRALKA_POSKO.dir/build.make
SEMESTRALKA_POSKO: /usr/lib/x86_64-linux-gnu/libcurses.so
SEMESTRALKA_POSKO: /usr/lib/x86_64-linux-gnu/libform.so
SEMESTRALKA_POSKO: CMakeFiles/SEMESTRALKA_POSKO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.B5VJnpLHyD/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SEMESTRALKA_POSKO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SEMESTRALKA_POSKO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SEMESTRALKA_POSKO.dir/build: SEMESTRALKA_POSKO

.PHONY : CMakeFiles/SEMESTRALKA_POSKO.dir/build

CMakeFiles/SEMESTRALKA_POSKO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SEMESTRALKA_POSKO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SEMESTRALKA_POSKO.dir/clean

CMakeFiles/SEMESTRALKA_POSKO.dir/depend:
	cd /tmp/tmp.B5VJnpLHyD/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.B5VJnpLHyD /tmp/tmp.B5VJnpLHyD /tmp/tmp.B5VJnpLHyD/cmake-build-debug /tmp/tmp.B5VJnpLHyD/cmake-build-debug /tmp/tmp.B5VJnpLHyD/cmake-build-debug/CMakeFiles/SEMESTRALKA_POSKO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SEMESTRALKA_POSKO.dir/depend

