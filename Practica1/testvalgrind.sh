#/bin/bash 
valgrind --tool=cachegrind ./a.out 
#valgrind --tool=memcheck --leak-check=yes ./a.out 
