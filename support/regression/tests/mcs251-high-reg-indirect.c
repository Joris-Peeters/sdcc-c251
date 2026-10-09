/* mcs251-high-reg-indirect.c - MCS251 @Ri moves with R8-R15.

   MOV @Ri,src and MOV dst,@Ri take only A (R11) or a direct address, and
   R8-R15 have no direct address.  The code generator emitted
   "mov @r1,r13" (rejected by the assembler) and "mov r12,@r1" (which the
   peephole turned into "mov ar12,@r1", an undefined symbol).
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
#define N 10

static __idata unsigned char lo[2][N];
static __idata unsigned char hi[2][N];
static const unsigned int __code table[5] = {0x00f7, 0x038f, 0x0039, 0x030f, 0x0079};
static volatile __idata long values[5] = {-2147483647L - 1, -1, 0, 1, 2147483647L};

static unsigned int
glyph (unsigned char i)
{
  return table[i % 5] + i;
}

static void
put_row (unsigned char row)
{
  unsigned char i;
  unsigned int g;

  for (i = 0; i < N; i++)
    {
      g = glyph (i);
      lo[row][i] = (unsigned char)g;
      hi[row][i] = (unsigned char)(g >> 8);
    }
}

static unsigned char
relation (long a, long b)
{
  return (a < b) | (a <= b) << 1 | (a > b) << 2 | (a >= b) << 3 | (a == b) << 4 | (a != b) << 5;
}
#endif

void
testHighRegIndirect (void)
{
#if defined (__SDCC_mcs251)
  unsigned char i, j, sum = 0;

  put_row (1);
  put_row (0);
  for (i = 0; i < N; i++)
    {
      ASSERT (lo[1][i] == (unsigned char)(table[i % 5] + i));
      ASSERT (hi[0][i] == (unsigned char)((table[i % 5] + i) >> 8));
    }
  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      sum += relation (values[i], values[j]);
  ASSERT (sum == 0x98);
#endif
}
