[![Build and Regression Tests](https://github.com/chrislupp/Philote-Cpp/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/chrislupp/Philote-Cpp/actions/workflows/build.yml)

# Philote-Cpp
C++ library for using and creating Philote analysis disciplines.


## Platform Support

Philote-Cpp is tested against the following platforms and compilers:

    - Ubuntu 22.04
        - gRPC 1.51.1 using:
            - gcc-9/g++-9
            - gcc-10/g++-10
            - gcc-11/g++-11
            - gcc-12/g++-12
            - clang-12/clang++-12
            - clang-13/clang++-13
            - clang-14/clang++-14

While early tests were written to run on all three major operating system
(Linux, Windows, and macOS), the GitHub billing for the non-Linux OS's is so
high (macOS is billed at a factor of ten higher than Linux) that it is not
feasible to run anything other than Linux. However, as the main dependency for
Philote-Cpp is gRPC, it is likely that any system that can compile and run gRPC
will be able to run Philote-Cpp. This is especially true, as Philote-Cpp follows
the same C++ standards as gRPC.