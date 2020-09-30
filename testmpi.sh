#/bin/bash

mpicc -g -Wall -O2 pingpong.c

mpiexec -n 2 ./a.out
