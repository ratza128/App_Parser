#!/bin/bash
module load compilers/solarisstudio-12.3
gcc -g main.c -o executabil -lm -fopenmp

START=$(date +%s)
time ~/App_OPENMP/executabil expr.txt > timp.txt 
END=$(date +%s)
DIFF=$(( $END - $START ))
echo " A durat $DIFF secunde "
