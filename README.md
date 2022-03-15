
# SHA-256 C library

This repository holds an implementation of the secure hash algorithm 256
(better known as SHA-256) in the C programming language.

This project has no external dependencies.

### Usage

To use this library in a C project, do the following:

 1. clone the repository in the `libs/` directory of your project;
 2. run `make all` after `cd`ing into the `libs/SHA` directory;
 3. add the `-Ilibs/SHA/include` option to your `CFLAGS` (so you can `#include <sha256.,h>` into your project source files), and
 4. link any required object files from the `libs/SHA/obj/` directory.

### Motivation

All of the code within this repository was written by me so I could

 1. learn about hashing algorithms;
 2. gain more experience with C programming, and
 3. develop a C library that *could* technically be used by other developers.

### Current state of the project

As of now (15/03/2022) the `sha256hash` function passes all tests in
`test/sha256.c`. These tests consists of the test vectors given in FIPS
publication 180-2 among others.

### Security notice

Most likely, the source code for this library is not secure. As is stated in
the license: do not use this for actual applications.
