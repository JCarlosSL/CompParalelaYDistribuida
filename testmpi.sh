#/bin/bash

mpicc -g -Wall -O2 TrapezoidalRule.c

mpiexec -n 2 ./a.out
