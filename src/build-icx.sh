#!/bin/bash
#Usage: ./build-icx.sh VECLEN with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=icx NDEBUG=3 VECLEN=$1 SAFE=SV2,NRM GMP=/opt/gmp/lib MPFR=/opt/mpfr/lib clean
make COMPILER=icx NDEBUG=3 VECLEN=$1 SAFE=SV2,NRM GMP=/opt/gmp/lib MPFR=/opt/mpfr/lib -j
cd -
make clean
make -j
