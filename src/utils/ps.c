#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ()
{
  fputs("\n", stdout);
  fputs("  Memory: [\033[92m|||||||||||           \033[0m] 250 / 376 Mib\n", stdout);
  fputs("\n", stdout);
  fputs(" PID | Name  \n", stdout);
  fputs("----------------------\n", stdout);
  fputs("   1 | Master\n", stdout);
  fputs("   2 | Shell\n", stdout);
  fputs("   5 | Ps\n", stdout);
  fputs("\n", stdout);
  fputs("  \033[96mTXWA\033[0m\n", stdout);
  fputs("\n", stdout);
  return 0;
}

