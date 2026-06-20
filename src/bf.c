#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC optimize ("rounding-math")
#endif /* __GNUC__ && !__clang__ */
#pragma STDC FENV_ACCESS ON

#include "pvn.h"

static long double al;
static double ad;
static float af;

static void a2()
{
  const float a2f = (af * af);
  (void)printf("%#a ", a2f);
  const float e2f = __builtin_fmaf(-af, af, a2f);
  (void)printf("%#a ", e2f);
  const double a2d = (ad * ad);
  (void)printf("%#a ", a2d);
  const double e2d = __builtin_fma(-ad, ad, a2d);
  (void)printf("%#a ", e2d);
  const long double a2l = (al * al);
  (void)printf("%#La ", a2l);
  const long double e2l = __builtin_fmal(-al, al, a2l);
  (void)printf("%#La\n", e2l);
}

int main(int argc, char* argv[])
{
  if (argc != 1) {
    (void)fprintf(stderr, "%s takes no arguments\n", *argv);
    return EXIT_FAILURE;
  }
  if (fegetround() < 0)
    return EXIT_FAILURE;
  al = nextafterl(1.0L, 0.0L);
  ad = nextafter(1.0, 0.0);
  af = nextafterf(1.0f, 0.0f);
  (void)printf("predecessor(1): %#a %#a %#La\n", af, ad, al);
  (void)printf("FE_TONEAREST  : ");
  if (fesetround(FE_TONEAREST))
    return EXIT_FAILURE;
  a2();
  (void)printf("FE_DOWNWARD   : ");
  if (fesetround(FE_DOWNWARD))
    return EXIT_FAILURE;
  a2();
  (void)printf("FE_UPWARD     : ");
  if (fesetround(FE_UPWARD))
    return EXIT_FAILURE;
  a2();
  return EXIT_SUCCESS;
}
