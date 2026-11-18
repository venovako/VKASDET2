# VKASDET2
Vectorizable Kahan's Algorithm with Scaling for Determinants of order two

(... work in progress ...)

Requires [libpvn](https://github.com/venovako/libpvn) with:
* [GMP](https://gmplib.org),
* [MPFR](https://mpfr.org), and
* [MPC](https://www.multiprecision.org) libraries.

An `AVX512F`-compatible system is required for the full functionality, using either `icx` or `gcc`.

See the examples in `src/build-icx.sh` and `src/build-gcc.sh`.

This work has been supported in part by Croatian Science Foundation under the project IP-2014-09-3670 ([MFBDA](https://web.math.pmf.unizg.hr/mfbda/)).
