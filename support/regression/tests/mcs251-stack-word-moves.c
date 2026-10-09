/* mcs251-stack-word-moves.c - MCS251 peephole merging of stack byte moves.

   With --stack-auto, "mov a,@spx-N / mov r3,a / mov a,@spx-N+1 / mov r2,a"
   was merged into "mov wr2,@spx-N+1" although the code after it still read
   A.  This is the C fallback of the library's _moduint.
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
#define MSB_SET(x) ((x >> (8*sizeof(x)-1)) & 1)

static unsigned int
modulo (unsigned int a, unsigned int b)
{
  unsigned char count = 0;

  while (!MSB_SET(b))
    {
      b <<= 1;
      if (b > a)
        {
          b >>=1;
          break;
        }
      count++;
    }
  do
    {
      if (a >= b)
        a -= b;
      b >>= 1;
    }
  while (count--);
  return a;
}

static volatile unsigned int ua = 50000u, ub = 300;
#endif

void
testStackWordMoves (void)
{
#if defined (__SDCC_mcs251)
  ASSERT (modulo (50000u, 300) == 200);
  ASSERT (modulo (65535u, 7) == 1);
  ASSERT (modulo (1234, 1235) == 1234);
  ASSERT (ua % ub == 200);
#endif
}
