# GDExample

Example GDExtension derived from the [Official guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/) and [godot-cpp-template](https://github.com/godotengine/godot-cpp-template).

***This project is intended for reference only***

# Prerequisites

* Godot v4.2+
* a C++ compiler
* Build tools:
  * Scons - Godot and Godot-CPP requirement
  * Make - Mainly for build command reference, commands can be run manually.
  * CMake - Unit testing (doctest) seems to be a preferred tool.

[Official list of prerequisites](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#setting-up-the-project)

> See also [Compiling](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling), as the build tools are identical to those you need to compile Godot from the source.

## Build

The [Makefile](Makefile) defines targets for building based on the OS and debug vs release.

Run `make help` for a list of targets and descriptions.

## Bugs

### Makefile stack smash
__2024.02.24__:

When using the Makefile to build the gdextension with debug there will be a stack smashing error when the extension is loaded if two scons commands are run sequentially.

If you remove one scons command from the debug, Godot will load the extension without issue. You can even run the removed command manually, and everything should still work (based on my testing).

This bug only afflicts the debug builds, as additional memory checks are enabled.

_Steps to reproduce_:

1. Clone the repository or run `make clean` to clear build artifacts.
2. Build the godot_cpp library (e.x., `make godot_cpp_linux`).
3. Build the GDExtension (e.x., `make gdextension_linux_debug`).
4. Load Godot

_Expected results_:

Blank project loads extension and ready to create.

_Actual results_:

Stack smashing error, process terminated.

### Doctest integration
__2024.03.26__:

The current branch, doctest, fails to link or expose the GDExtension code properly.

1. Setup environment: `make godot_cpp_linux gdextension_linux_debug`
2. Execute tests: `make tests`

_Expected results_:

One test executed and passed: godot::GDExtension::is_prime(int)

_Actual results_:


```
~/git/gdexample$ make tests
cmake -S ./test -B ./.cmake
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Git: /usr/bin/git (found version "2.34.1") 
-- Godot CPP library found: ~/git/gdexample/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a
-- GDExample library found: ~/git/gdexample/bin/linux/libgdexample.linux.template_debug.x86_64.so
-- GDExample Include Directories: ~/git/gdexample/test/../src
-- Configuring done
-- Generating done
-- Build files have been written to: ~/git/gdexample/.cmake
cmake --build ./.cmake --verbose
gmake[1]: Entering directory '~/git/gdexample/.cmake'
/usr/bin/cmake -S~/git/gdexample/test -B~/git/gdexample/.cmake --check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start ~/git/gdexample/.cmake/CMakeFiles ~/git/gdexample/.cmake//CMakeFiles/progress.marks
/usr/bin/gmake  -f CMakeFiles/Makefile2 all
gmake[2]: Entering directory '~/git/gdexample/.cmake'
/usr/bin/gmake  -f CMakeFiles/doctest.dir/build.make CMakeFiles/doctest.dir/depend
gmake[3]: Entering directory '~/git/gdexample/.cmake'
cd ~/git/gdexample/.cmake && /usr/bin/cmake -E cmake_depends "Unix Makefiles" ~/git/gdexample/test ~/git/gdexample/test ~/git/gdexample/.cmake ~/git/gdexample/.cmake ~/git/gdexample/.cmake/CMakeFiles/doctest.dir/DependInfo.cmake --color=
gmake[3]: Leaving directory '~/git/gdexample/.cmake'
/usr/bin/gmake  -f CMakeFiles/doctest.dir/build.make CMakeFiles/doctest.dir/build
gmake[3]: Entering directory '~/git/gdexample/.cmake'
[ 10%] Creating directories for 'doctest'

...

[ 80%] Completed 'doctest'
/usr/bin/cmake -E make_directory ~/git/gdexample/.cmake/CMakeFiles
/usr/bin/cmake -E touch ~/git/gdexample/.cmake/CMakeFiles/doctest-complete
/usr/bin/cmake -E touch ~/git/gdexample/.cmake/doctest/src/doctest-stamp/doctest-done
gmake[3]: Leaving directory '~/git/gdexample/.cmake'
[ 80%] Built target doctest
/usr/bin/gmake  -f CMakeFiles/gdexample_test.dir/build.make CMakeFiles/gdexample_test.dir/depend
gmake[3]: Entering directory '~/git/gdexample/.cmake'
cd ~/git/gdexample/.cmake && /usr/bin/cmake -E cmake_depends "Unix Makefiles" ~/git/gdexample/test ~/git/gdexample/test ~/git/gdexample/.cmake ~/git/gdexample/.cmake ~/git/gdexample/.cmake/CMakeFiles/gdexample_test.dir/DependInfo.cmake --color=
gmake[3]: Leaving directory '~/git/gdexample/.cmake'
/usr/bin/gmake  -f CMakeFiles/gdexample_test.dir/build.make CMakeFiles/gdexample_test.dir/build
gmake[3]: Entering directory '~/git/gdexample/.cmake'
[ 90%] Building CXX object CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o
/usr/bin/c++  -I~/git/gdexample/.cmake/doctest/src/doctest/doctest -isystem ~/git/gdexample/test/../src -isystem ~/git/gdexample/test/../godot-cpp/gdextension -isystem ~/git/gdexample/test/../godot-cpp/gen/include -isystem ~/git/gdexample/test/../godot-cpp/include  -MD -MT CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o -MF CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o.d -o CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o -c ~/git/gdexample/test/src/test_gdexample.cpp
[100%] Linking CXX executable gdexample_test
/usr/bin/cmake -E cmake_link_script CMakeFiles/gdexample_test.dir/link.txt --verbose=1
/usr/bin/c++ CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o -o gdexample_test  -Wl,-rpath,~/git/gdexample/bin/linux ~/git/gdexample/bin/linux/libgdexample.linux.template_debug.x86_64.so ~/git/gdexample/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a 
/usr/bin/ld: CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o: in function `DOCTEST_ANON_FUNC_14()':
test_gdexample.cpp:(.text+0x15e2f): undefined reference to `godot::GDExample::GDExample()'
/usr/bin/ld: test_gdexample.cpp:(.text+0x15eb3): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x15fd0): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x160ed): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x1620a): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x16327): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x163cf): undefined reference to `godot::GDExample::~GDExample()'
/usr/bin/ld: test_gdexample.cpp:(.text+0x1668b): undefined reference to `godot::GDExample::~GDExample()'
/usr/bin/ld: CMakeFiles/gdexample_test.dir/src/test_gdexample.cpp.o: in function `DOCTEST_ANON_FUNC_16()':
test_gdexample.cpp:(.text+0x16744): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x16861): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x1697e): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x16a9b): undefined reference to `godot::GDExample::is_prime(int)'
/usr/bin/ld: test_gdexample.cpp:(.text+0x16bb8): undefined reference to `godot::GDExample::is_prime(int)'
collect2: error: ld returned 1 exit status
gmake[3]: *** [CMakeFiles/gdexample_test.dir/build.make:99: gdexample_test] Error 1
gmake[3]: Leaving directory '~/git/gdexample/.cmake'
gmake[2]: *** [CMakeFiles/Makefile2:111: CMakeFiles/gdexample_test.dir/all] Error 2
gmake[2]: Leaving directory '~/git/gdexample/.cmake'
gmake[1]: *** [Makefile:91: all] Error 2
gmake[1]: Leaving directory '~/git/gdexample/.cmake'
make: *** [Makefile:83: tests] Error 2
```
