#include "pvn.h"

/* noinline to account for the function calls, just as with PVN_DDET and PVN_ZDET */
#if (defined(__INTEL_CLANG_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__INTEL_COMPILER))
__attribute__((noinline))
#else /* GCC */
__attribute__((noipa))
#endif /* ?Intel */
double fn_ddet(const double a, const double b, const double c, const double d)
{
  return pvn_ddet(a, b, c, d);
}

int main(int argc, char *argv[])
{
  if ((argc < 2) && (argc > 4)) {
    (void)fprintf(stderr, "%s n [prec [m]]\n", *argv);
    return EXIT_FAILURE;
  }
  size_t n = pvn_atoz(argv[1]);
  if (!n)
    return EXIT_SUCCESS;
  size_t m =
#ifdef __AVX512F__
    (n & 7u);
  if (m)
    n += (8u - m);
  m =
#endif /* __AVX512F__ */
  n * sizeof(double);
  mpfr_rnd_t rnd = MPFR_RNDN;
  mpfr_exp_t emin = __MPFR_EXP_INVALID, emax = __MPFR_EXP_INVALID;
  mpfr_prec_t prec = ((argc >= 3) ? atol(argv[2]) : 113l);
  int u = PVN_FABI(pvn_mpfr_start,PVN_MPFR_START)(&rnd, &prec, &emin, &emax);
  if (u) {
    (void)fprintf(stderr, "PVN_MPFR_START=%d\n", u);
    return EXIT_FAILURE;
  }
  double *a = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&a, PVN_VECLEN, m));
  (void)memset(a, 0, m);
  double *b = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&b, PVN_VECLEN, m));
  (void)memset(b, 0, m);
  double *c = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&c, PVN_VECLEN, m));
  (void)memset(c, 0, m);
  double *d = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&d, PVN_VECLEN, m));
  (void)memset(d, 0, m);
  double *r = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&r, PVN_VECLEN, m));
  (void)memset(r, 0, m);
  double *x = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&x, PVN_VECLEN, m));
  (void)memset(x, 0, m);
  double *h = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&h, PVN_VECLEN, m));
  (void)memset(h, 0, m);
#ifdef __AVX512F__
  double *z = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&z, PVN_VECLEN, m));
  (void)memset(z, 0, m);
#endif /* __AVX512F__ */
  m = n * sizeof(int);
  int *t = (int*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&t, PVN_VECLEN, m));
  (void)memset(t, 0, m);
#ifdef __AVX512F__
  int *v = (int*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&v, PVN_VECLEN, m));
  (void)memset(v, 0, m);
#endif /* __AVX512F__ */
  double e = __builtin_inf(), E = 0.0;
  mpfr_t ma, mb, mc, md, mr, mx;
  u = mpfr_init_set_d(ma, E, MPFR_RNDN);
  u = mpfr_init_set_d(mb, E, MPFR_RNDN);
  u = mpfr_init_set_d(mc, E, MPFR_RNDN);
  u = mpfr_init_set_d(md, E, MPFR_RNDN);
  u = mpfr_init_set_d(mr, E, MPFR_RNDN);
  u = mpfr_init_set_d(mx, E, MPFR_RNDN);
  u = PVN_FABI(pvn_ran_open,PVN_RAN_OPEN)();
  char s[26] = { '\0' };
  m = ((argc >= 4) ? pvn_atoz(argv[3]) : (size_t)1u);
  (void)printf("%10zu, ", (n * m));
  (void)fflush(stdout);
  long long T[3] = { 0ll, 0ll, 0ll };
  unsigned K[4] = { 0u, 0u, 0u, 0u };
  for (size_t j = 0u; j < m; ++j) {
    for (size_t i = 0u; i < n; ++i) {
      do {
        a[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(a[i]));
      do {
        b[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(b[i]));
      do {
        c[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(c[i]));
      do {
        d[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(d[i]));
    }
    long long f = pvn_time_mono_ns();
    for (size_t i = 0u; i < n; ++i)
      r[i] = fn_ddet(a[i], b[i], c[i], d[i]);
    f = pvn_time_mono_ns() - f;
    T[0] += f;
    for (size_t i = 0u; i < n; ++i)
      if (!__builtin_isfinite(r[i]))
        ++(K[0]);
    f = pvn_time_mono_ns();
    for (size_t i = 0u; i < n; ++i)
      r[i] = PVN_FABI(pvn_ddet,PVN_DDET)((a + i), (b + i), (c + i), (d + i), (x + i), (t + i));
    f = pvn_time_mono_ns() - f;
    T[1] += f;
    for (size_t i = 0u; i < n; ++i)
      if (!__builtin_isfinite(r[i]))
        ++(K[1]);
    const double g = (DBL_EPSILON * 0.5);
    for (size_t i = 0u; i < n; ++i) {
      (void)mpfr_set_d(ma, a[i], MPFR_RNDN);
      (void)mpfr_set_d(mb, b[i], MPFR_RNDN);
      (void)mpfr_set_d(mc, c[i], MPFR_RNDN);
      (void)mpfr_set_d(md, d[i], MPFR_RNDN);
      (void)mpfr_set_d(mx, x[i], MPFR_RNDN);
      (void)mpfr_mul_2si(mx, mx, t[i], MPFR_RNDN);
      (void)mpfr_fmms(mr, ma, md, mb, mc, MPFR_RNDN);
      (void)mpfr_sub(mx, mr, mx, MPFR_RNDN);
      (void)mpfr_mul_d(mr, mr, g, MPFR_RNDN);
      (void)mpfr_div(mx, mx, mr, MPFR_RNDN);
      (void)mpfr_abs(mx, mx, MPFR_RNDN);
      h[i] = mpfr_get_d(mx, MPFR_RNDN);
      if (!(h[i] < 3.0)) {
        (void)fprintf(stderr, "a=%s %# a\n", pvn_dtoa(s, a[i]), a[i]);
        (void)fprintf(stderr, "b=%s %# a\n", pvn_dtoa(s, b[i]), b[i]);
        (void)fprintf(stderr, "c=%s %# a\n", pvn_dtoa(s, c[i]), c[i]);
        (void)fprintf(stderr, "d=%s %# a\n", pvn_dtoa(s, d[i]), d[i]);
        (void)fprintf(stderr, "x=%s %# a\n", pvn_dtoa(s, x[i]), x[i]);
        (void)fprintf(stderr, "t=%d\n", t[i]);
        (void)fprintf(stderr, "r=%s %# a\n", pvn_dtoa(s, r[i]), r[i]);
        (void)fprintf(stderr, "h=%s %# a\n\n", pvn_dtoa(s, h[i]), h[i]);
        (void)fflush(stderr);
      }
      else {
        e = __builtin_fmin(e, h[i]);
        E = __builtin_fmax(E, h[i]);
      }
    }
#ifdef __AVX512F__
    f = pvn_time_mono_ns();
    for (size_t i = 0u; i < n; i += 8u)
      K[2] += (unsigned)PVN_FABI(pvn_zdet,PVN_ZDET)((const __m512d*)(a + i), (const __m512d*)(b + i), (const __m512d*)(c + i), (const __m512d*)(d + i), (__m512d*)(z + i), (__m256i*)(v + i), (__m512d*)(h + i));
    f = pvn_time_mono_ns() - f;
    T[2] += f;
    for (size_t i = 0u; i < n; ++i) {
      if (x[i] != z[i]) {
        (void)fprintf(stderr, "x %s ", pvn_dtoa(s, x[i]));
        (void)fprintf(stderr, "z %s\n", pvn_dtoa(s, z[i]));
        ++(K[3]);
        continue;
      }
      if (t[i] != v[i]) {
        (void)fprintf(stderr, "t %d v %d\n", t[i], v[i]);
        ++(K[3]);
        continue;
      }
      if (r[i] != h[i]) {
        (void)fprintf(stderr, "r %s ", pvn_dtoa(s, r[i]));
        (void)fprintf(stderr, "h %s\n", pvn_dtoa(s, h[i]));
        ++(K[3]);
        continue;
      }
    }
  }
  (void)printf("%lld, %u, %lld, %u,", T[0], K[0], T[1], K[1]);
  (void)printf("%s,", pvn_dtoa(s, e));
  (void)printf("%s, ", pvn_dtoa(s, E));
  (void)printf("%u, %lld, %u\n", K[2], T[2], K[3]);
  (void)fflush(stdout);
  u = PVN_FABI(pvn_ran_close,PVN_RAN_CLOSE)(&u);
  mpfr_clear(mx);
  mpfr_clear(mr);
  mpfr_clear(md);
  mpfr_clear(mc);
  mpfr_clear(mb);
  mpfr_clear(ma);
  u = PVN_FABI(pvn_mpfr_stop,PVN_MPFR_STOP)();
  free(v);
#endif /* __AVX512F__ */
  free(t);
#ifdef __AVX512F__
  free(z);
#endif /* __AVX512F__ */
  free(h);
  free(x);
  free(r);
  free(d);
  free(c);
  free(b);
  free(a);
  return (u ? EXIT_FAILURE : EXIT_SUCCESS);
}
