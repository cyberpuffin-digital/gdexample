# GDExample

Example GDExtension derived from the [Official guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/) and [godot-cpp-template](https://github.com/godotengine/godot-cpp-template).

***This project is intended for reference only***

# Prerequisites

* Godot v4.2+
* a C++ compiler
* Build tools:
  * Scons - Godot and Godot-CPP requirement
  * Make - Mainly for build command reference.  Commands can be run manually.
  * CMake - Unit testing (doctest), seems to be a preferred tool.

[Official list of prerequisites](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#setting-up-the-project)

> See also [Compiling](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) as the build tools are identical to the ones you need to compile Godot from source.

## Build

The [Makefile](Makefile) defines targets for building based on the OS and debug vs release.

Run `make help` for a list of targets and descriptions.

## Build bug

__2024.02.24__:

When using the Makefile to build the gdextension with debug there will be a stack smashing error when the extension is loaded if two scons commands are run sequentially.

Remove one scons command from the debug and Godot will load the extension without issue.  You can even run the removed command manually and everything should still work (based on my testing).

This bug only afflicts the debug builds, as additional memory checks are being enabled.

_Steps to reproduce_:

1. Clone the repository or run `make clean` to clear build artifacts.
2. Build the godot_cpp library (e.x., `make godot_cpp_linux`).
3. Build the GDExtension (e.x., `make gdextension_linux_debug`).
4. Load Godot

_Expected results_:

Blank project loads extension and ready to create.

_Actual results_:

Stack smashing error, process terminated
