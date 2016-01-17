#!/bin/bash
module load compilers/solarisstudio-12.3
gcc -g -fopenmp -lm  main.c -o executabil

#collect ~/App_OPENMP/executabil expr.txt

START=$(date +%s)
time collect ~/App_OPENMP/executabil expr.txt > timp.txt 
END=$(date +%s)
DIFF=$(( $END - $START ))
echo " A durat $DIFF secunde "

