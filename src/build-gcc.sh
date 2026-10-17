#!/bin/bash
#Usage: ./build-gcc.sh VECLEN with GMP and MPFR installed as specified below
cd ../../libpvn/src
make NDEBUG=3 VECLEN=$1 SAFE=SV2,NRM GMP=$HOME/gnu/lib MPFR=$HOME/gnu/lib clean
make NDEBUG=3 VECLEN=$1 SAFE=SV2,NRM GMP=$HOME/gnu/lib MPFR=$HOME/gnu/lib -j
cd -
make clean
make -j
