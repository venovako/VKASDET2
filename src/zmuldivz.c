#include "pvn.h"

int main(int argc, char *argv[])
{
  if ((argc < 2) && (argc > 4)) {
    (void)fprintf(stderr, "%s n [prec [m]]\n", *argv);
    return EXIT_FAILURE;
  }
  size_t n = pvn_atoz(argv[1]);
  if (!n)
    return EXIT_SUCCESS;
  size_t m = (n & 7u);
  if (m)
    n += (8u - m);
  m = n * sizeof(double);
  mpfr_rnd_t rnd = MPFR_RNDN;
  mpfr_exp_t emin = __MPFR_EXP_INVALID, emax = __MPFR_EXP_INVALID;
  mpfr_prec_t prec = ((argc >= 3) ? atol(argv[2]) : 113l);
  int u = PVN_FABI(pvn_mpc_start,PVN_MPC_START)(&rnd, &prec, &emin, &emax);
  if (u) {
    (void)fprintf(stderr, "PVN_MPC_START=%d\n", u);
    return EXIT_FAILURE;
  }
  double *ar = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&ar, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(ar, 0, m));
  double *ai = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&ai, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(ai, 0, m));
  double *br = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&br, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(br, 0, m));
  double *bi = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&bi, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(bi, 0, m));
  double *cr = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&cr, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(cr, 0, m));
  double *ci = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&ci, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(ci, 0, m));
  double *dr = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&dr, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(dr, 0, m));
  double *di = (double*)NULL;
  PVN_SYSI_CALL(u = posix_memalign((void**)&di, PVN_VECLEN, m));
  PVN_SYSP_CALL(memset(di, 0, m));
  mpc_t mw, mx, my, mz;
  mpc_init2(mw, prec);
  mpc_init2(mx, prec);
  mpc_init2(my, prec);
  mpc_init2(mz, prec);
  mpfr_t mn, md;
  u = mpfr_init_set_d(mn, 0.0, MPFR_RNDN);
  u = mpfr_init_set_d(md, 0.0, MPFR_RNDN);
  double /* relative errors */
    e[6] = { __builtin_inf(), __builtin_inf(), __builtin_inf(), __builtin_inf(), __builtin_inf(), __builtin_inf() },
    E[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  u = PVN_FABI(pvn_ran_open,PVN_RAN_OPEN)();
  char s[26] = { '\0' };
  m = ((argc >= 4) ? pvn_atoz(argv[3]) : (size_t)1u);
  (void)printf("%10zu, ", (n * m));
  (void)fflush(stdout);
  long long T[2] = { 0ll, 0ll };
  for (size_t j = 0u; j < m; ++j) {
    for (size_t i = 0u; i < n; ++i) {
      do {
        ar[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(ar[i]));
      do {
        ai[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(ai[i]));
      do {
        br[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(br[i]));
      do {
        bi[i] = PVN_FABI(pvn_ran,PVN_RAN)(&u);
      } while (!__builtin_isfinite(bi[i]));
    }
    long long f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; i += 8u)
      PVN_FABI(pvn_zmulz,PVN_ZMULZ)((cr + i), (ci + i), (ar + i), (ai + i), (br + i), (bi + i));
    T[0] += (f = pvn_time_proc_ns() - f);
    f = pvn_time_proc_ns();
    for (size_t i = 0u; i < n; i += 8u)
      PVN_FABI(pvn_zdivz,PVN_ZDIVZ)((dr + i), (di + i), (ar + i), (ai + i), (br + i), (bi + i));
    T[1] += (f = pvn_time_proc_ns() - f);
    const double g = (DBL_EPSILON * 0.5);
    for (size_t i = 0u; i < n; ++i) {
      (void)printf("(%s,", pvn_dtoa(s, ar[i]));
      (void)printf("%s) ", pvn_dtoa(s, ai[i]));
      (void)printf("(%s,", pvn_dtoa(s, br[i]));
      (void)printf("%s)\n", pvn_dtoa(s, bi[i]));
      (void)printf("(%s,", pvn_dtoa(s, cr[i]));
      (void)printf("%s) ", pvn_dtoa(s, ci[i]));
      (void)printf("(%s,", pvn_dtoa(s, dr[i]));
      (void)printf("%s)\n", pvn_dtoa(s, di[i]));

      (void)mpc_set_d_d(my, ar[i], ai[i], MPC_RNDNN);
      (void)mpc_set_d_d(mz, br[i], bi[i], MPC_RNDNN);

      (void)mpc_set_d_d(mw, cr[i], ci[i], MPC_RNDNN);
      (void)mpc_mul(mx, my, mz, MPC_RNDNN);

      (void)mpc_sub(mw, mx, mw, MPC_RNDNN);
      (void)mpfr_abs(mn, mpc_realref(mw), MPFR_RNDN);
      (void)mpfr_abs(md, mpc_realref(mx), MPFR_RNDN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      ar[i] = mpfr_get_d(mn, MPFR_RNDN);
      (void)mpfr_abs(mn, mpc_imagref(mw), MPFR_RNDN);
      (void)mpfr_abs(md, mpc_imagref(mx), MPFR_RNDN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      ai[i] = mpfr_get_d(mn, MPFR_RNDN);

      (void)mpc_abs(mn, mw, MPC_RNDNN);
      (void)mpc_abs(md, mx, MPC_RNDNN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      cr[i] = mpfr_get_d(mn, MPFR_RNDN);

      (void)mpc_set_d_d(mw, dr[i], di[i], MPC_RNDNN);
      (void)mpc_div(mx, my, mz, MPC_RNDNN);

      (void)mpc_sub(mw, mx, mw, MPC_RNDNN);
      (void)mpfr_abs(mn, mpc_realref(mw), MPFR_RNDN);
      (void)mpfr_abs(md, mpc_realref(mx), MPFR_RNDN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      br[i] = mpfr_get_d(mn, MPFR_RNDN);
      (void)mpfr_abs(mn, mpc_imagref(mw), MPFR_RNDN);
      (void)mpfr_abs(md, mpc_imagref(mx), MPFR_RNDN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      bi[i] = mpfr_get_d(mn, MPFR_RNDN);

      (void)mpc_abs(mn, mw, MPC_RNDNN);
      (void)mpc_abs(md, mx, MPC_RNDNN);
      (void)mpfr_mul_d(md, md, g, MPFR_RNDN);
      (void)mpfr_div(mn, mn, md, MPFR_RNDN);
      ci[i] = mpfr_get_d(mn, MPFR_RNDN);

      e[0] = __builtin_fmin(e[0], ar[i]);
      E[0] = __builtin_fmax(E[0], ar[i]);
      e[1] = __builtin_fmin(e[1], ai[i]);
      E[1] = __builtin_fmax(E[1], ai[i]);
      e[2] = __builtin_fmin(e[2], br[i]);
      E[2] = __builtin_fmax(E[2], br[i]);
      e[3] = __builtin_fmin(e[3], bi[i]);
      E[3] = __builtin_fmax(E[3], bi[i]);
      e[4] = __builtin_fmin(e[4], cr[i]);
      E[4] = __builtin_fmax(E[4], cr[i]);
      e[5] = __builtin_fmin(e[5], ci[i]);
      E[5] = __builtin_fmax(E[5], ci[i]);
    }
  }
  (void)printf("%lld, %lld,", T[0], T[1]);
  (void)printf("%s,", pvn_dtoa(s, E[0]));
  (void)printf("%s,", pvn_dtoa(s, E[1]));
  (void)printf("%s,", pvn_dtoa(s, E[2]));
  (void)printf("%s,", pvn_dtoa(s, E[3]));
  (void)printf("%s,", pvn_dtoa(s, E[4]));
  (void)printf("%s\n", pvn_dtoa(s, E[5]));
  (void)fflush(stdout);
  u = PVN_FABI(pvn_ran_close,PVN_RAN_CLOSE)(&u);
  mpfr_clear(md);
  mpfr_clear(mn);
  mpc_clear(mz);
  mpc_clear(my);
  mpc_clear(mx);
  mpc_clear(mw);
  u = PVN_FABI(pvn_mpc_stop,PVN_MPC_STOP)();
  free(di);
  free(dr);
  free(ci);
  free(cr);
  free(bi);
  free(br);
  free(ai);
  free(ar);
  return (u ? EXIT_FAILURE : EXIT_SUCCESS);
}
