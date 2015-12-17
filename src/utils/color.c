#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOREM_IPSUM(c,f)  "\033[" #f "8;4" #c "mLorem \033[0m"       \
                          "\033[" #f "0;4" #c "mIpsum \033[0m"       \
                          "\033[" #f "1;4" #c "mdolor \033[0m"       \
                          "\033[" #f "2;4" #c "msit \033[0m"         \
                          "\033[" #f "3;4" #c "mamet, \033[0m"       \
                          "\033[" #f "4;4" #c "mVivamus \033[0m"     \
                          "\033[" #f "5;4" #c "mfermentum \033[0m"   \
                          "\033[" #f "6;4" #c "msemper \033[0m"      \
                          "\033[" #f "7;4" #c "mporta. \033[0m" "\n"


int main () 
{
  fputs("Background | Foreground colors - Dark colors\n", stdout);
  fputs("--------------------------------------------------------------------------\n", stdout);

  fputs("  Default  | " LOREM_IPSUM(8, 3), stdout);
  fputs("  Black    | " LOREM_IPSUM(0, 3), stdout);
  fputs("  Red      | " LOREM_IPSUM(1, 3), stdout);
  fputs("  Green    | " LOREM_IPSUM(2, 3), stdout);
  fputs("  Yellow   | " LOREM_IPSUM(3, 3), stdout);
  fputs("  Blue     | " LOREM_IPSUM(4, 3), stdout);
  fputs("  Magenta  | " LOREM_IPSUM(5, 3), stdout);
  fputs("  Cyan     | " LOREM_IPSUM(6, 3), stdout);
  fputs("  White    | " LOREM_IPSUM(7, 3), stdout);

  fputs("--------------------------------------------------------------------------\n", stdout);
  fputs("Background | Foreground colors - Light colors\n", stdout);
  fputs("--------------------------------------------------------------------------\n", stdout);

  fputs("  Default  | " LOREM_IPSUM(8, 9), stdout);
  fputs("  Black    | " LOREM_IPSUM(0, 9), stdout);
  fputs("  Red      | " LOREM_IPSUM(1, 9), stdout);
  fputs("  Green    | " LOREM_IPSUM(2, 9), stdout);
  fputs("  Yellow   | " LOREM_IPSUM(3, 9), stdout);
  fputs("  Blue     | " LOREM_IPSUM(4, 9), stdout);
  fputs("  Magenta  | " LOREM_IPSUM(5, 9), stdout);
  fputs("  Cyan     | " LOREM_IPSUM(6, 9), stdout);
  fputs("  White    | " LOREM_IPSUM(7, 9), stdout);

  fputs("--------------------------------------------------------------------------\n", stdout);
  return 0;
}

