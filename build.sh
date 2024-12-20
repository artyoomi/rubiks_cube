#!/bin/bash

# create build directory and makefiles
cmake -B build

# go to build directory
cd build

cmake --build .
