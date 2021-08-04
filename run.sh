#!/bin/bash

mkdir build
cd build
cmake ..
# cmake CMAKE_BUILD_TYPE=DEBUG ..
# cmake -DCMAKE_BUILD_TYPE=DEBUG ..

cmake --build .