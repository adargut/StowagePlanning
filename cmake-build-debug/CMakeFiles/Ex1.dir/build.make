# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Adar\CLionProjects\Ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ex1.dir/flags.make

CMakeFiles/Ex1.dir/src/main.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ex1.dir/src/main.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\main.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\main.cpp

CMakeFiles/Ex1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/main.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\main.cpp > CMakeFiles\Ex1.dir\src\main.cpp.i

CMakeFiles/Ex1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/main.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\main.cpp -o CMakeFiles\Ex1.dir\src\main.cpp.s

CMakeFiles/Ex1.dir/src/Ship.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/Ship.cpp.obj: ../src/Ship.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Ex1.dir/src/Ship.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\Ship.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\Ship.cpp

CMakeFiles/Ex1.dir/src/Ship.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/Ship.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\Ship.cpp > CMakeFiles\Ex1.dir\src\Ship.cpp.i

CMakeFiles/Ex1.dir/src/Ship.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/Ship.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\Ship.cpp -o CMakeFiles\Ex1.dir\src\Ship.cpp.s

CMakeFiles/Ex1.dir/src/Port.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/Port.cpp.obj: ../src/Port.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Ex1.dir/src/Port.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\Port.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\Port.cpp

CMakeFiles/Ex1.dir/src/Port.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/Port.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\Port.cpp > CMakeFiles\Ex1.dir\src\Port.cpp.i

CMakeFiles/Ex1.dir/src/Port.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/Port.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\Port.cpp -o CMakeFiles\Ex1.dir\src\Port.cpp.s

CMakeFiles/Ex1.dir/src/Container.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/Container.cpp.obj: ../src/Container.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Ex1.dir/src/Container.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\Container.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\Container.cpp

CMakeFiles/Ex1.dir/src/Container.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/Container.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\Container.cpp > CMakeFiles\Ex1.dir\src\Container.cpp.i

CMakeFiles/Ex1.dir/src/Container.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/Container.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\Container.cpp -o CMakeFiles\Ex1.dir\src\Container.cpp.s

CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.obj: ../src/WeightBalanceCalculator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\WeightBalanceCalculator.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\WeightBalanceCalculator.cpp

CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\WeightBalanceCalculator.cpp > CMakeFiles\Ex1.dir\src\WeightBalanceCalculator.cpp.i

CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\WeightBalanceCalculator.cpp -o CMakeFiles\Ex1.dir\src\WeightBalanceCalculator.cpp.s

CMakeFiles/Ex1.dir/src/Instruction.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/Instruction.cpp.obj: ../src/Instruction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Ex1.dir/src/Instruction.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\Instruction.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\Instruction.cpp

CMakeFiles/Ex1.dir/src/Instruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/Instruction.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\Instruction.cpp > CMakeFiles\Ex1.dir\src\Instruction.cpp.i

CMakeFiles/Ex1.dir/src/Instruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/Instruction.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\Instruction.cpp -o CMakeFiles\Ex1.dir\src\Instruction.cpp.s

CMakeFiles/Ex1.dir/src/Utility.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/Utility.cpp.obj: ../src/Utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Ex1.dir/src/Utility.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\Utility.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\Utility.cpp

CMakeFiles/Ex1.dir/src/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/Utility.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\Utility.cpp > CMakeFiles\Ex1.dir\src\Utility.cpp.i

CMakeFiles/Ex1.dir/src/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/Utility.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\Utility.cpp -o CMakeFiles\Ex1.dir\src\Utility.cpp.s

CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.obj: CMakeFiles/Ex1.dir/flags.make
CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.obj: ../src/StowageAlgorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.obj"
	C:\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ex1.dir\src\StowageAlgorithm.cpp.obj -c C:\Users\Adar\CLionProjects\Ex1\src\StowageAlgorithm.cpp

CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.i"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adar\CLionProjects\Ex1\src\StowageAlgorithm.cpp > CMakeFiles\Ex1.dir\src\StowageAlgorithm.cpp.i

CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.s"
	C:\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adar\CLionProjects\Ex1\src\StowageAlgorithm.cpp -o CMakeFiles\Ex1.dir\src\StowageAlgorithm.cpp.s

# Object files for target Ex1
Ex1_OBJECTS = \
"CMakeFiles/Ex1.dir/src/main.cpp.obj" \
"CMakeFiles/Ex1.dir/src/Ship.cpp.obj" \
"CMakeFiles/Ex1.dir/src/Port.cpp.obj" \
"CMakeFiles/Ex1.dir/src/Container.cpp.obj" \
"CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.obj" \
"CMakeFiles/Ex1.dir/src/Instruction.cpp.obj" \
"CMakeFiles/Ex1.dir/src/Utility.cpp.obj" \
"CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.obj"

# External object files for target Ex1
Ex1_EXTERNAL_OBJECTS =

Ex1.exe: CMakeFiles/Ex1.dir/src/main.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/Ship.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/Port.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/Container.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/WeightBalanceCalculator.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/Instruction.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/Utility.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/src/StowageAlgorithm.cpp.obj
Ex1.exe: CMakeFiles/Ex1.dir/build.make
Ex1.exe: CMakeFiles/Ex1.dir/linklibs.rsp
Ex1.exe: CMakeFiles/Ex1.dir/objects1.rsp
Ex1.exe: CMakeFiles/Ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Ex1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Ex1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ex1.dir/build: Ex1.exe

.PHONY : CMakeFiles/Ex1.dir/build

CMakeFiles/Ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Ex1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Ex1.dir/clean

CMakeFiles/Ex1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adar\CLionProjects\Ex1 C:\Users\Adar\CLionProjects\Ex1 C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug C:\Users\Adar\CLionProjects\Ex1\cmake-build-debug\CMakeFiles\Ex1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ex1.dir/depend

