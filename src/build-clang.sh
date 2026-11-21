#!/bin/bash
#Usage: ./build-clang.sh with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=clang NDEBUG=3 VECLEN=64 SAFE=SV2,NRM GMP=$HOME/gnu/lib MPFR=$HOME/gnu/lib MPC=$HOME/gnu/lib clean
make COMPILER=clang NDEBUG=3 VECLEN=64 SAFE=SV2,NRM GMP=$HOME/gnu/lib MPFR=$HOME/gnu/lib MPC=$HOME/gnu/lib -j
cd -
make clean
make -j
