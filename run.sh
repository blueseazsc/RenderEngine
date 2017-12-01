#!/bin/bash
mkdir -p build
cd build
cmake ..
make
#make VERBOSE=1
./main
