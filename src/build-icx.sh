#!/bin/bash
#Usage: ./build-icx.sh with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=icx NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr clean
make COMPILER=icx NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr -j
cd -
make clean
make -j
