#!/bin/bash
#Usage: ./build-gcc.sh with GMP and MPFR installed as specified below
cd ../../libpvn/src
make NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=$HOME/gnu MPFR=$HOME/gnu clean
make NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=$HOME/gnu MPFR=$HOME/gnu -j
cd -
make clean
make -j
