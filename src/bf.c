#ifdef PVN_SV2_SAFE
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif /* __GNUC__ && !__clang__ */
#pragma STDC FENV_ACCESS ON
#endif /* PVN_SV2_SAFE */

#include "pvn.h"

static float a;

static void a2()
{
  const float a2 = (a * a);
  (void)printf("%#a\n", a2);
}

int main()
{
  a = nextafterf(1.0f, 0.0f);
  if (fesetround(FE_DOWNWARD))
    return EXIT_FAILURE;
  a2();
  if (fesetround(FE_TONEAREST))
    return EXIT_FAILURE;
  a2();
  if (fesetround(FE_TOWARDZERO))
    return EXIT_FAILURE;
  a2();
  if (fesetround(FE_UPWARD))
    return EXIT_FAILURE;
  a2();
  return EXIT_SUCCESS;
}
