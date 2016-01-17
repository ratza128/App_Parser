#!/bin/bash
rm -r script.sh.*
rm -r test.*
qsub -q ibm-nehalem.q -cwd script.sh
