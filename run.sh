#!/bin/bash -v
make clean && make && opt -load ./CountOpCode.so -CountOpCode -enable-new-pm=0 main.bc