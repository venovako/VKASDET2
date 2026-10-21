#!/bin/bash
#Usage: ./build_icx.sh on an Intel Xeon Phi machine with GMP and MPFR installed as specified below
cd ../../libpvn/src
make COMPILER=icx NATIVE=COMMON-AVX512 NDEBUG=3 VECLEN=64 SAFE=SV2,NRM GMP=/opt/gmp/lib MPFR=/opt/mpfr/lib clean
make COMPILER=icx NATIVE=COMMON-AVX512 NDEBUG=3 VECLEN=64 SAFE=SV2,NRM GMP=/opt/gmp/lib MPFR=/opt/mpfr/lib -j
cd -
make clean
make -j
