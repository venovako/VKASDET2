#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC optimize ("rounding-math")
#endif /* __GNUC__ && !__clang__ */
#pragma STDC FENV_ACCESS ON

#include "pvn.h"

static double ad;
static float af;

static void a2()
{
  const double a2d = (ad * ad);
  (void)printf("%#a ", a2d);
  const float a2f = (af * af);
  (void)printf("%#a\n", a2f);
}

int main(int argc, char* argv[])
{
  if (argc != 1) {
    (void)fprintf(stderr, "%s takes no arguments\n", *argv);
    return EXIT_FAILURE;
  }
  ad = nextafter(1.0, 0.0);
  af = nextafterf(1.0f, 0.0f);
  (void)printf("predecessor(1): %#a %#a\n", ad, af);
  if (fesetround(FE_TONEAREST))
    return EXIT_FAILURE;
  (void)printf("FE_TONEAREST  : ");
  a2();
  /* here, TOWARDZERO has the same effect as DOWNWARD */
  if (fesetround(FE_TOWARDZERO))
    return EXIT_FAILURE;
  (void)printf("FE_TOWARDZERO : ");
  a2();
  if (fesetround(FE_UPWARD))
    return EXIT_FAILURE;
  (void)printf("FE_UPWARD     : ");
  a2();
  return EXIT_SUCCESS;
}
