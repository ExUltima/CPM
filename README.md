# Project Description
CPM is a modern cross-platform build system for solving C++ building complexity,
such as difference toolchain on each platform, dependency management and so on.

# Build Status
|Platform     |Master                                                                                                                                                            |
|-------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|Linux & macOS|[![Build Status](https://travis-ci.org/ultimaweapon/cpm.svg?branch=master)](https://travis-ci.org/ultimaweapon/cpm)                                               |
|Windows      |[![Build status](https://ci.appveyor.com/api/projects/status/v1ddnjc6r3m1n92x/branch/master?svg=true)](https://ci.appveyor.com/project/ExUltima/cpm/branch/master)|

# Motivation
C++ is my very first language I have learned. On that time it is not a productive language.
Therefore I switched to C# and Go and working on them for a while (around 3 and 1 years).
In the meantime I also checked back on C++11 and found out it is a big improvement for C++ but
still no anything like NuGet or Go tools. So I started this project.

# Goals
* Lightweight, easy to use and cross-platform.
* The only dependency is C++14 and platform API.
* Supports multiple toolchains.
* Easy to manage dependencies.
* Multiple build's configurations.

# Naming
CPM is stand for C++ Project Manager.

# Dependencies
* C++14
* POSIX or Win32 API

# Build instructions for *nix

```sh
./autogen.sh && ./configure && make
```

# Build instructions for Windows

Open Visual Studio Command Prompt and run the following command in the root of repository:

```bat
nmake -f Makefile.mak
```
