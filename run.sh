#!/bin/bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake -DCMAKE_BUILD_TYPE=Debug ..
rm bin/main
# make
make VERBOSE=1
bin/main
