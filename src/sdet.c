#include "pvn.h"

/* noinline to account for the function calls, just as with PVN_SDET and PVN_ZDETF */
#if (defined(__INTEL_CLANG_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__INTEL_COMPILER))
__attribute__((noinline))
#else /* GCC */
__attribute__((noipa))
#endif /* ?Intel */
float fn1_sdet(const float a, const float b, const float c, const float d)
{
  return pvn_sdet(a, b, c, d);
}

#ifdef __AVX512F__
#if (defined(__INTEL_CLANG_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__INTEL_COMPILER))
__attribute__((noinline))
#else /* GCC */
__attribute__((noipa))
#endif /* ?Intel */
void fn8_sdet(const float *const a, const float *const b, const float *const c, const float *const d, float *const r)
{
  _mm256_store_ps(r, pvn_ydetf(_mm256_load_ps(a), _mm256_load_ps(b), _mm256_load_ps(c), _mm256_load_ps(d)));
}
#if (defined(__INTEL_CLANG_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__INTEL_COMPILER))
__attribute__((noinline))
#else /* GCC */
__attribute__((noipa))
#endif /* ?Intel */
void fn16_sdet(const float *const a, const float *const b, const float *const c, const float *const d, float *const r)
{
  _mm512_store_ps(r, pvn_zdetf(_mm512_load_ps(a), _mm512_load_ps(b), _mm512_load_ps(c), _mm512_load_ps(d)));
}
#endif /* __AVX512F__ */

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
    (n & 15u);
  if (m)
    n += (16u - m);
  m =
#endif /* __AVX512F__ */
  n * sizeof(float);
  mpfr_rnd_t rnd = MPFR_RNDN;
  mpfr_exp_t emin = __MPFR_EXP_INVALID, emax = __MPFR_EXP_INVALID;
  mpfr_prec_t prec = ((argc >= 3) ? atol(argv[2]) : 113l);
  int u = PVN_FABI(pvn_mpfr_start,PVN_MPFR_START)(&rnd, &prec, &emin, &emax);
  if (u) {
    (void)fprintf(stderr, "PVN_MPFR_START=%d\n", u);
    return EXIT_FAILURE;
  }
  float *a = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&a, PVN_VECLEN, m));
  (void)memset(a, 0, m);
  float *b = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&b, PVN_VECLEN, m));
  (void)memset(b, 0, m);
  float *c = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&c, PVN_VECLEN, m));
  (void)memset(c, 0, m);
  float *d = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&d, PVN_VECLEN, m));
  (void)memset(d, 0, m);
  float *r = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&r, PVN_VECLEN, m));
  (void)memset(r, 0, m);
  float *x = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&x, PVN_VECLEN, m));
  (void)memset(x, 0, m);
  float *h = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&h, PVN_VECLEN, m));
  (void)memset(h, 0, m);
#ifdef __AVX512F__
  float *z = (float*)NULL;
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
  float e = __builtin_inff(), E = 0.0f;
  mpfr_t ma, mb, mc, md, mr, mx;
  u = mpfr_init_set_d(ma, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(mb, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(mc, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(md, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(mr, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(mx, 0.0, MPFR_RNDN);
  u = PVN_FABI(pvn_ran_open,PVN_RAN_OPEN)();
  char s[17] = { '\0' };
  m = ((argc >= 4) ? pvn_atoz(argv[3]) : (size_t)1u);
  (void)printf("%10zu, ", (n * m));
  (void)fflush(stdout);
  long long T[5] = { 0ll, 0ll, 0ll, 0ll, 0ll };
  unsigned K[4] = { 0u, 0u, 0u, 0u };
  for (size_t j = 0u; j < m; ++j) {
    for (size_t i = 0u; i < n; ++i) {
      do {
        a[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
      } while (!__builtin_isfinite(a[i]));
      do {
        b[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
      } while (!__builtin_isfinite(b[i]));
      do {
        c[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
      } while (!__builtin_isfinite(c[i]));
      do {
        d[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
      } while (!__builtin_isfinite(d[i]));
    }
    long long f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; ++i)
      r[i] = fn1_sdet(a[i], b[i], c[i], d[i]);
    f = pvn_time_proc_ns() - f;
    T[0] += f;
    for (size_t i = 0u; i < n; ++i)
      if (!__builtin_isfinite(r[i]))
        ++(K[0]);
    f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; ++i)
      r[i] = PVN_FABI(pvn_sdet,PVN_SDET)((a + i), (b + i), (c + i), (d + i), (x + i), (t + i));
    f = pvn_time_proc_ns() - f;
    T[1] += f;
    for (size_t i = 0u; i < n; ++i)
      if (!__builtin_isfinite(r[i]))
        ++(K[1]);
    const float g = (FLT_EPSILON * 0.5f);
    for (size_t i = 0u; i < n; ++i) {
      (void)mpfr_set_flt(ma, a[i], MPFR_RNDN);
      (void)mpfr_set_flt(mb, b[i], MPFR_RNDN);
      (void)mpfr_set_flt(mc, c[i], MPFR_RNDN);
      (void)mpfr_set_flt(md, d[i], MPFR_RNDN);
      (void)mpfr_set_flt(mx, x[i], MPFR_RNDN);
      (void)mpfr_mul_2si(mx, mx, t[i], MPFR_RNDN);
      (void)mpfr_fmms(mr, ma, md, mb, mc, MPFR_RNDN);
      (void)mpfr_sub(mx, mr, mx, MPFR_RNDN);
      (void)mpfr_mul_d(mr, mr, g, MPFR_RNDN);
      (void)mpfr_div(mx, mx, mr, MPFR_RNDN);
      (void)mpfr_abs(mx, mx, MPFR_RNDN);
      h[i] = mpfr_get_flt(mx, MPFR_RNDN);
      if (!(h[i] < 3.0f)) {
        (void)fprintf(stderr, "a=%s %# a\n", pvn_stoa(s, a[i]), a[i]);
        (void)fprintf(stderr, "b=%s %# a\n", pvn_stoa(s, b[i]), b[i]);
        (void)fprintf(stderr, "c=%s %# a\n", pvn_stoa(s, c[i]), c[i]);
        (void)fprintf(stderr, "d=%s %# a\n", pvn_stoa(s, d[i]), d[i]);
        (void)fprintf(stderr, "x=%s %# a\n", pvn_stoa(s, x[i]), x[i]);
        (void)fprintf(stderr, "t=%d\n", t[i]);
        (void)fprintf(stderr, "r=%s %# a\n", pvn_stoa(s, r[i]), r[i]);
        (void)fprintf(stderr, "h=%s %# a\n\n", pvn_stoa(s, h[i]), h[i]);
        (void)fflush(stderr);
      }
      else {
        e = __builtin_fminf(e, h[i]);
        E = __builtin_fmaxf(E, h[i]);
      }
    }
#ifdef __AVX512F__
    f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; i += 8u)
      fn8_sdet((a + i), (b + i), (c + i), (d + i), (h + i));
    f = pvn_time_proc_ns() - f;
    T[2] += f;
    f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; i += 16u)
      fn16_sdet((a + i), (b + i), (c + i), (d + i), (h + i));
    f = pvn_time_proc_ns() - f;
    T[3] += f;
    f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; i += 16u)
      K[2] += (unsigned)PVN_FABI(pvn_zdetf,PVN_ZDETF)((a + i), (b + i), (c + i), (d + i), (z + i), (v + i), (h + i));
    f = pvn_time_proc_ns() - f;
    T[4] += f;
    for (size_t i = 0u; i < n; ++i) {
      if (x[i] != z[i]) {
        (void)fprintf(stderr, "x %s ", pvn_stoa(s, x[i]));
        (void)fprintf(stderr, "z %s\n", pvn_stoa(s, z[i]));
        ++(K[3]);
        continue;
      }
      if (t[i] != v[i]) {
        (void)fprintf(stderr, "t %d v %d\n", t[i], v[i]);
        ++(K[3]);
        continue;
      }
      if (r[i] != h[i]) {
        (void)fprintf(stderr, "r %s ", pvn_stoa(s, r[i]));
        (void)fprintf(stderr, "h %s\n", pvn_stoa(s, h[i]));
        ++(K[3]);
        continue;
      }
    }
  }
  (void)printf("%lld, %u, %lld, %u,", T[0], K[0], T[1], K[1]);
  (void)printf("%s,", pvn_stoa(s, e));
  (void)printf("%s, ", pvn_stoa(s, E));
  (void)printf("%lld, %lld, %lld, %u, %u\n", T[2], T[3], T[4], K[2], K[3]);
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
