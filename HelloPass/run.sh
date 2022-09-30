#!/bin/bash
make clean
make
# compile hello.bc
clang++ -O3 -emit-llvm test.cpp -c -o test.bc

#opt load
opt -load ./HelloPass.so -hello  -enable-new-pm=0 test.bc
# opt -load ./hello.so -hello -enable-new-pm=0  < hello.bc > hello2.bc
