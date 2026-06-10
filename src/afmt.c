#include "pvn.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    (void)fprintf(stderr, "%s (S|D|X)\n", *argv);
    return EXIT_FAILURE;
  }
  const char T = toupper(*(argv[1]));
  if (T == 'S') {
    float s;
    if (scanf(" %E", &s) <= 0)
      break;
    (void)printf("%# a\n", (double)s);
  }
  else if (T == 'D') {
    double d;
    if (scanf(" %lE", &d) <= 0)
      break;
    (void)printf("%# a\n", d);
  }
  else if (T == 'X') {
    long double x;
    if (scanf(" %LE", &x) <= 0)
      break;
    (void)printf("%# La\n", x);
  }
  else
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
