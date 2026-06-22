#!/bin/bash
#Usage: ./build_phi.sh on an Intel Xeon Phi machine with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=icx NATIVE=common-avx512 NDEBUG=3 OPENMP=0 SAFE=DET,SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr clean
make COMPILER=icx NATIVE=common-avx512 NDEBUG=3 OPENMP=0 SAFE=DET,SV2,NRM GMP=/opt/gmp MPFR=/opt/mpfr -j
cd -
make clean
make -j
