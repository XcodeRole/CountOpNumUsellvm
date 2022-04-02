#!/bin/bash -v
make clean &&
make &&
gcc -fPIC -shared toInsert.c -o toInsert.so && 
clang++ -emit-llvm -c test.cpp &&
opt -load ./InsertFunctionPass.so -insert -enable-new-pm=0 test.bc -o test.bc &&
lli -load ./toInsert.so test.bc