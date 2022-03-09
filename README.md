
# SHA-256 C library

This repository holds an implementation of the secure hash algorithm 256
(better known as SHA-256) in the C programming language.

This project has no external dependencies.

### Motivation

All of the code within this repository was written by me so I could

 1. learn about hashing algorithms;
 2. gain more experience with C programming, and
 3. develop a C library that *could* technically be used by other developers.

### Current state of the project

As of now (09/03/2022) the `sha256hash` function passes the two tests in
`test/sha256.c`. These tests are based on the test vectors given in FIPS
publication 180-2.

### Security notice

Most likely, the source code for this library is not secure. As is stated in
the license: do not use this for actual applications.
