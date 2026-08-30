#!/bin/bash
#Usage: ./build_gcc.sh with GMP and MPFR installed as specified below, and a non-default GCC-16 compiler
cd ../../libpvn/src
make COMPILER=gcc COMPILER_SUFFIX=-16 NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=$HOME/gnu MPFR=$HOME/gnu clean
make COMPILER=gcc COMPILER_SUFFIX=-16 NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=$HOME/gnu MPFR=$HOME/gnu -j
cd -
make clean
make -j
