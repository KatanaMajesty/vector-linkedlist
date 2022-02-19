#!/bin/bash

cmake -G "Unix Makefiles" -B ./build/ -S .
cd ./build/
make
./klib-executable
