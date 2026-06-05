#include "pvn.h"

int main(int argc, char *argv[])
{
#ifdef PVN_MPFR
  if ((argc != 2) && (argc != 3)) {
    (void)fprintf(stderr, "%s n [prec]\n", *argv);
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
  mpfr_prec_t prec = ((argc == 3) ? atol(argv[2]) : 113l);
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
  float *y = (float*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&y, PVN_VECLEN, m));
  (void)memset(y, 0, m);
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
  (void)printf("%10zu, ", n);
  (void)fflush(stdout);
  long long f = pvn_time_mono_ns();
  for (size_t i = 0u; i < n; ++i) {
    do {
      a[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
    } while (!__builtin_isfinite(a[i]));
#ifndef NDEBUG
    (void)fprintf(stderr, "%s,", pvn_stoa(s, a[i]));
#endif /* !NDEBUG */
    do {
      b[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
    } while (!__builtin_isfinite(b[i]));
#ifndef NDEBUG
    (void)fprintf(stderr, "%s,", pvn_stoa(s, b[i]));
#endif /* !NDEBUG */
    do {
      c[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
    } while (!__builtin_isfinite(c[i]));
#ifndef NDEBUG
    (void)fprintf(stderr, "%s,", pvn_stoa(s, c[i]));
#endif /* !NDEBUG */
    do {
      d[i] = PVN_FABI(pvn_ran_f,PVN_RAN_F)(&u);
    } while (!__builtin_isfinite(d[i]));
#ifndef NDEBUG
    (void)fprintf(stderr, "%s;", pvn_stoa(s, d[i]));
#endif /* !NDEBUG */
  }
  f = pvn_time_mono_ns() - f;
  (void)printf("%lld, ", f);
  (void)fflush(stdout);
  u = PVN_FABI(pvn_ran_close,PVN_RAN_CLOSE)(&u);
  f = pvn_time_mono_ns();
  for (size_t i = 0u; i < n; ++i) {
    r[i] = PVN_FABI(pvn_sdet,PVN_SDET)((a + i), (b + i), (c + i), (d + i), (x + i), (t + i));
#ifndef NDEBUG
    (void)fprintf(stderr, "%s,%5d;", pvn_stoa(s, x[i]), t[i]);
#endif /* !NDEBUG */
  }
  f = pvn_time_mono_ns() - f;
  (void)printf("%lld, ", f);
  (void)fflush(stdout);
  const float g = (FLT_EPSILON * 0.5f);
  f = pvn_time_mono_ns();
  u = 0;
  for (size_t i = 0u; i < n; ++i) {
    (void)mpfr_set_d(ma, a[i], MPFR_RNDN);
    (void)mpfr_set_d(mb, b[i], MPFR_RNDN);
    (void)mpfr_set_d(mc, c[i], MPFR_RNDN);
    (void)mpfr_set_d(md, d[i], MPFR_RNDN);
    (void)mpfr_set_d(mx, x[i], MPFR_RNDN);
    (void)mpfr_mul_2si(mx, mx, t[i], MPFR_RNDN);
    (void)mpfr_fmms(mr, ma, md, mb, mc, MPFR_RNDN);
    (void)mpfr_sub(mx, mr, mx, MPFR_RNDN);
    (void)mpfr_div(mx, mx, mr, MPFR_RNDN);
    (void)mpfr_abs(mx, mx, MPFR_RNDN);
    (void)mpfr_div_d(mx, mx, g, MPFR_RNDN);
    y[i] = mpfr_get_flt(mx, MPFR_RNDN);
#ifndef NDEBUG
    (void)fprintf(stderr, "%s\n", pvn_stoa(s, y[i]));
#endif /* !NDEBUG */
    e = __builtin_fminf(e, y[i]);
    E = __builtin_fmaxf(E, y[i]);
    if (!__builtin_isfinite(r[i]))
      ++u;
  }
  f = pvn_time_mono_ns() - f;
  (void)printf("%lld, %u,", f, *(const unsigned*)&u);
  mpfr_clear(mx);
  mpfr_clear(mr);
  mpfr_clear(md);
  mpfr_clear(mc);
  mpfr_clear(mb);
  mpfr_clear(ma);
  u = PVN_FABI(pvn_mpfr_stop,PVN_MPFR_STOP)();
  (void)printf("%s,", pvn_stoa(s, e));
  (void)printf("%s, ", pvn_stoa(s, E));
  (void)fflush(stdout);
#ifdef __AVX512F__
  f = pvn_time_mono_ns();
  for (size_t i = 0u; i < n; i += 16u) {
    PVN_FABI(pvn_zdetf,PVN_ZDETF)((a + i), (b + i), (c + i), (d + i), (z + i), (v + i), (y + i));
#ifndef NDEBUG
    for (size_t j = 0u; j < 16u; ++j)
      (void)fprintf(stderr, "%s,%5d;", pvn_stoa(s, z[i + j]), v[i + j]);
#endif /* !NDEBUG */
  }
  f = pvn_time_mono_ns() - f;
  (void)printf("%lld, ", f);
  (void)fflush(stdout);
  u = 0;
  for (size_t i = 0u; i < n; ++i) {
    if (x[i] != z[i]) {
      (void)fprintf(stderr, "x %s ", pvn_stoa(s, x[i]));
      (void)fprintf(stderr, "z %s\n", pvn_stoa(s, z[i]));
      *(unsigned*)&u = (unsigned)(i + 1u);
      break;
    }
    if (t[i] != v[i]) {
      (void)fprintf(stderr, "t %d v %d\n", t[i], v[i]);
      *(unsigned*)&u = (unsigned)(i + 1u);
      break;
    }
    if (r[i] != y[i]) {
      (void)fprintf(stderr, "r %s ", pvn_stoa(s, r[i]));
      (void)fprintf(stderr, "y %s\n", pvn_stoa(s, y[i]));
      *(unsigned*)&u = (unsigned)(i + 1u);
      break;
    }
  }
  (void)printf("%u\n", *(const unsigned*)&u);
  (void)fflush(stdout);
  free(v);
#endif /* __AVX512F__ */
  free(t);
#ifdef __AVX512F__
  free(z);
#endif /* __AVX512F__ */
  free(y);
  free(x);
  free(r);
  free(d);
  free(c);
  free(b);
  free(a);
  if (u)
    return EXIT_FAILURE;
#else /* !PVN_MPFR */
  if (argc != 5) {
    (void)fprintf(stderr, "%s a b c d\n", *argv);
    return EXIT_FAILURE;
  }
  const float a = (float)atof(argv[1]);
  const float b = (float)atof(argv[2]);
  const float c = (float)atof(argv[3]);
  const float d = (float)atof(argv[4]);
  char s[17] = { '\0' };
  float x = __builtin_nanf("x"),
    y = pvn_sdet(a, b, c, d);
  (void)printf("pvn_sdet=%s\n", pvn_stoa(s, y));
  int t = 0;
  y = PVN_FABI(pvn_sdet,PVN_SDET)(&a, &b, &c, &d, &x, &t);
  (void)printf("PVN_SDET=%s (", pvn_stoa(s, y));
  (void)printf("%s,%d)\n", pvn_stoa(s, x), t);
#endif /* ?PVN_MPFR */
  return EXIT_SUCCESS;
}
