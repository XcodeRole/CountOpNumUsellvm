clang -emit-llvm -c test.c &&
clang++ -fPIC -shared -o callhello.so CallHello.cpp Hello.cpp `llvm-config --cxxflags` &&
opt -load ./callhello.so -caller -enable-new-pm=0 test.bc