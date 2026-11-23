# VKASDET2
Vectorizable Kahan's Algorithm with Scaling for Determinants of order two

(... work in progress ...)

Requires [libpvn](https://github.com/venovako/libpvn) built with the support for:
* [GMP](https://gmplib.org),
* [MPFR](https://mpfr.org), and
* [MPC](https://www.multiprecision.org) libraries.

An `AVX512F`-compatible system is required for the vectorized functionality (i.e., AMD or Intel's CPUs).

See the examples in `src/build-clang.sh`, `src/build-gcc.sh`, and `src/build-icx.sh`.

This work has been supported in part by Croatian Science Foundation under the project IP-2014-09-3670 ([MFBDA](https://web.math.pmf.unizg.hr/mfbda/)).
