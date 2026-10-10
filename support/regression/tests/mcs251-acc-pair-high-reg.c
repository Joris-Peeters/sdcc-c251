/* mcs251-acc-pair-high-reg.c - a 16-bit value in A and B combined with R8-R15.

   A function result that is used once stays in A and B.  The MCS-51 forms of
   ADDC, SUBB, ANL, ORL and XRL A,Rn only encode R0-R7, so an R8-R15 operand
   goes through B, and that overwrote the high byte of the value in B
   (bug-3087 and dhrystone, 7 * (x - y) - z).
 */

#include <testfwk.h>

void mcs251AccPairProc7 (int i1, int i2, int *out);
void mcs251AccPairProc2 (int *p);
int mcs251AccPairDhry (void);

static volatile int v[6] = {0x0123, 0x4567, 0x0089, 0x0a0b, 0x1c1d, 0x2e2f};

static int
id (int x)
{
  return x;
}

/* Six values stay live across each call, more than R0-R7 hold. */
static int
ops (void)
{
  int a = v[0], b = v[1], c = v[2], d = v[3], e = v[4], f = v[5];
  int r;

  r = id (a) - f;
  r += id (b) + e;
  r ^= id (c) & d;
  r |= id (d) ^ c;
  r += id (e) | b;
  r -= id (f) - a;
  return r + a + b + c + d + e + f;
}

void
mcs251AccPairProc7 (int i1, int i2, int *out)
{
  (void) i1;
  (void) i2;
  *out = 1;
}

void
mcs251AccPairProc2 (int *p)
{
  (void) p;
}

/* The Dhrystone sequence: the product is in A:B, i1 in R8-R15. */
int
mcs251AccPairDhry (void)
{
  int i1, i2, i3, run;

  for (run = 1; run <= 2; ++run)
    {
      i1 = 2;
      i2 = 3;
      while (i1 < i2)
        {
          mcs251AccPairProc7 (i1, i2, &i3);
          i1 += 1;
        }
      i2 = i2 * i1;
      i1 = i2 / i3;
      i2 = 7 * (i2 - i3) - i1;
      mcs251AccPairProc2 (&i1);
    }
  return i2;
}

void
testAccPairHighReg (void)
{
  int a = 0x0123, b = 0x4567, c = 0x0089, d = 0x0a0b, e = 0x1c1d, f = 0x2e2f;
  int r;

  r = a - f;
  r += b + e;
  r ^= c & d;
  r |= d ^ c;
  r += e | b;
  r -= f - a;
  ASSERT (ops () == r + a + b + c + d + e + f);
  ASSERT (mcs251AccPairDhry () == 47);
}
