#include "pvn.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    (void)fprintf(stderr, "%s (S|D|X)\n", *argv);
    return EXIT_FAILURE;
  }
  const char T = toupper(*(argv[1]));
  char s[46] = { '\0' };
  do {
    if (scanf(" %s", s) <= 0)
      break;
    else if (T == 'S')
      (void)printf("%# a\n", pvn_atos(s));
    else if (T == 'D')
      (void)printf("%# la\n", pvn_atod(s));
    else if (T == 'X')
      (void)printf("%# La\n", pvn_atox(s));
    else
      return EXIT_FAILURE;
  } while(true);
  return EXIT_SUCCESS;
}
