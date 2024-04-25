# Requirements

  * g++ v5.4 or newer
  * Boost 1.58.0 or newer
    * The `boost/multiprecision/float128.hpp` header must be available
  * Make
  * Cmake

## Installed Boost Packages

For development the following boost packages were installed.

```
libboost-date-time1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-filesystem1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-iostreams1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-python1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-regex1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-system1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-test-dev/xenial,now 1.58.0.1ubuntu1 amd64 [installed]
libboost-test1.58-dev/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-test1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost1.58-dev/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost1.58-doc/xenial-updates,xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 all [installed]
```

This listing was obtained by running `apt list --installed | grep boost`.

# Clone repository

To run this project, you first need to clone its repository to your computer using the Git command:
git clone

# Build project

You need to build the project with CMake. To do this, use the following commands depending on your operating system:

## Windows

cmake -S . -B build

cmake --build build --config Release

## Unix (Linux, macOS і т.д.)

cmake -S . -B build

cmake --build build

# Compilation

The code can be compiled with the provided makefile using the standard `make`
command.

If compiling the code manually, or integrating into a larger program, include
the following flags:

```
FLAGS=-std=c++17 -fsanitize=address -fuse-ld=gold -Wall -MMD \
      -fext-numeric-literals -lquadmath #-O3
```

Note that flag `-fuse-ld=gold` is only required on certain Ubuntu systems due
to a know bug with g++ 5.x.

# Run project

## Program

To run the program in normal mode, you need to run it without program arguments:

./build/(project_file_name)

## Unit testing

To run unit tests, you need to run a program with one program argument "test":

./build/(project_file_name) test
