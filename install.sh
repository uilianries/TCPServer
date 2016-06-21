#!/bin/bash

for program in conan cmake; do
    type $program &> /dev/null
    if [ $? -ne 0 ]; then
        echo "ERROR: $program is required"
        exit 1
    fi
done

mkdir build
cd build

conan install ..
if [ $? -ne 0 ]; then
  echo "ERROR: Could not install dependencies"
  exit 1
fi

cmake ..
if [ $? -ne 0 ]; then
  echo "ERROR: Could not solve CMake"
  exit 1
fi

cmake --build . --config release
if [ $? -ne 0 ]; then
  echo "ERROR: Could not build the project"
  exit 1
fi

sudo make install
if [ $? -ne 0 ]; then
  echo "ERROR: Could not install the files"
  exit 1
fi

echo Done!
exit 0
