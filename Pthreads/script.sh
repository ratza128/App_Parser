#!/bin/bash
module load compilers/solarisstudio-12.3
gcc -g -lm  main.c -o executabil -lpthreads

#collect ~/Pthreads/executabil expr.txt

START=$(date +%s)
time collect ~/Pthreads/executabil expr.txt > timp.txt 
END=$(date +%s)
DIFF=$(( $END - $START ))
echo " A durat $DIFF secunde "

