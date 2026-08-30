#!/bin/bash
#DEPRECATED (DO NOT USE)
#Usage: ./build_icx.sh on an Intel Xeon Phi machine with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=icx NATIVE=COMMON-AVX512 NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr clean
make COMPILER=icx NATIVE=COMMON-AVX512 NDEBUG=3 OPENMP=0 SAFE=SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr -j
cd -
make clean
make -j
