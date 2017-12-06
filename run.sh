#!/bin/bash
mkdir -p build
cd build
cmake ..
rm bin/main
make
#make VERBOSE=1
bin/main
