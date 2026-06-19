#ifdef PVN_SV2_SAFE
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif /* __GNUC__ && !__clang__ */
#pragma STDC FENV_ACCESS ON
#endif /* PVN_SV2_SAFE */

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

int main()
{
  ad = nextafter(1.0, 0.0);
  af = nextafterf(1.0f, 0.0f);
  if (fesetround(FE_DOWNWARD))
    return EXIT_FAILURE;
  (void)printf("FE_DOWNWARD  : ");
  a2();
  if (fesetround(FE_TONEAREST))
    return EXIT_FAILURE;
  (void)printf("FE_TONEAREST : ");
  a2();
  if (fesetround(FE_TOWARDZERO))
    return EXIT_FAILURE;
  (void)printf("FE_TOWARDZERO: ");
  a2();
  if (fesetround(FE_UPWARD))
    return EXIT_FAILURE;
  (void)printf("FE_UPWARD    : ");
  a2();
  return EXIT_SUCCESS;
}
