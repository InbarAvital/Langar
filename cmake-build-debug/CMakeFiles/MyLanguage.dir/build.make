# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/Inbar/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Inbar/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MyLanguage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MyLanguage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyLanguage.dir/flags.make

CMakeFiles/MyLanguage.dir/Parser/Parser.c.o: CMakeFiles/MyLanguage.dir/flags.make
CMakeFiles/MyLanguage.dir/Parser/Parser.c.o: ../Parser/Parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyLanguage.dir/Parser/Parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyLanguage.dir/Parser/Parser.c.o   -c /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Parser/Parser.c

CMakeFiles/MyLanguage.dir/Parser/Parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyLanguage.dir/Parser/Parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Parser/Parser.c > CMakeFiles/MyLanguage.dir/Parser/Parser.c.i

CMakeFiles/MyLanguage.dir/Parser/Parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyLanguage.dir/Parser/Parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Parser/Parser.c -o CMakeFiles/MyLanguage.dir/Parser/Parser.c.s

CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o: CMakeFiles/MyLanguage.dir/flags.make
CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o: ../Tokenizer/Tokenizer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o   -c /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Tokenizer/Tokenizer.c

CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Tokenizer/Tokenizer.c > CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.i

CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Tokenizer/Tokenizer.c -o CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.s

CMakeFiles/MyLanguage.dir/Main.c.o: CMakeFiles/MyLanguage.dir/flags.make
CMakeFiles/MyLanguage.dir/Main.c.o: ../Main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MyLanguage.dir/Main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyLanguage.dir/Main.c.o   -c /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Main.c

CMakeFiles/MyLanguage.dir/Main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyLanguage.dir/Main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Main.c > CMakeFiles/MyLanguage.dir/Main.c.i

CMakeFiles/MyLanguage.dir/Main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyLanguage.dir/Main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Main.c -o CMakeFiles/MyLanguage.dir/Main.c.s

CMakeFiles/MyLanguage.dir/ToAssembly.c.o: CMakeFiles/MyLanguage.dir/flags.make
CMakeFiles/MyLanguage.dir/ToAssembly.c.o: ../ToAssembly.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/MyLanguage.dir/ToAssembly.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyLanguage.dir/ToAssembly.c.o   -c /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/ToAssembly.c

CMakeFiles/MyLanguage.dir/ToAssembly.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyLanguage.dir/ToAssembly.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/ToAssembly.c > CMakeFiles/MyLanguage.dir/ToAssembly.c.i

CMakeFiles/MyLanguage.dir/ToAssembly.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyLanguage.dir/ToAssembly.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/ToAssembly.c -o CMakeFiles/MyLanguage.dir/ToAssembly.c.s

CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o: CMakeFiles/MyLanguage.dir/flags.make
CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o: ../Lexer/Lexer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o   -c /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Lexer/Lexer.c

CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Lexer/Lexer.c > CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.i

CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/Lexer/Lexer.c -o CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.s

# Object files for target MyLanguage
MyLanguage_OBJECTS = \
"CMakeFiles/MyLanguage.dir/Parser/Parser.c.o" \
"CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o" \
"CMakeFiles/MyLanguage.dir/Main.c.o" \
"CMakeFiles/MyLanguage.dir/ToAssembly.c.o" \
"CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o"

# External object files for target MyLanguage
MyLanguage_EXTERNAL_OBJECTS =

MyLanguage.exe: CMakeFiles/MyLanguage.dir/Parser/Parser.c.o
MyLanguage.exe: CMakeFiles/MyLanguage.dir/Tokenizer/Tokenizer.c.o
MyLanguage.exe: CMakeFiles/MyLanguage.dir/Main.c.o
MyLanguage.exe: CMakeFiles/MyLanguage.dir/ToAssembly.c.o
MyLanguage.exe: CMakeFiles/MyLanguage.dir/Lexer/Lexer.c.o
MyLanguage.exe: CMakeFiles/MyLanguage.dir/build.make
MyLanguage.exe: CMakeFiles/MyLanguage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable MyLanguage.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyLanguage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyLanguage.dir/build: MyLanguage.exe

.PHONY : CMakeFiles/MyLanguage.dir/build

CMakeFiles/MyLanguage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyLanguage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyLanguage.dir/clean

CMakeFiles/MyLanguage.dir/depend:
	cd /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug /cygdrive/c/Users/Inbar/CLionProjects/MyLanguage/cmake-build-debug/CMakeFiles/MyLanguage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyLanguage.dir/depend

