/* mcs251-peephole-high-reg.c - MCS-51 peephole rules and R8-R15.

   Some MCS-51 rules move an operand into ADDC, SUBB or XCH A,Rn, which only
   encode R0-R7.  With the operand in R8-R15 the result did not assemble
   ("ADDC/SUBB register source must be R0 through R7", "XCH register operand
   must be R0 through R7").  Rule 240 (16-bit + constant, gcc-torture
   mode-dependent-address) and rules 261.a/b (16-bit rotates) did this.
 */

#include <testfwk.h>

static volatile unsigned int v[7] = {0x8001, 0x4002, 0x2004, 0x1008, 0x0810, 0x0420, 0x0241};

static unsigned int
rotates (void)
{
  unsigned int a = v[0], b = v[1], c = v[2], d = v[3], e = v[4], f = v[5], g = v[6];

  a = (a << 1) | (a >> 15);
  b = (b << 1) | (b >> 15);
  c = (c << 1) | (c >> 15);
  d = (d >> 1) | (d << 15);
  e = (e >> 1) | (e << 15);
  f = (f << 1) | (f >> 15);
  g = (g >> 1) | (g << 15);
  return a ^ b ^ c ^ d ^ e ^ f ^ g;
}

static int
adds (void)
{
  int a = v[0], b = v[1], c = v[2], d = v[3], e = v[4], f = v[5], g = v[6];

  a = (a ^ 1) + 32;
  b = (b ^ 1) + 32;
  c = (c ^ 1) + 32;
  d = (d ^ 1) - -32;
  e = (e ^ 1) - -32;
  f = (f ^ 1) + 32;
  g = (g ^ 1) + 32;
  return a ^ b ^ c ^ d ^ e ^ f ^ g;
}

void
testPeepholeHighReg (void)
{
  ASSERT (rotates () == (0x0003 ^ 0x8004 ^ 0x4008 ^ 0x0804 ^ 0x0408 ^ 0x0840 ^ 0x8120));
  ASSERT (adds () == (int) (0x8020 ^ 0x4023 ^ 0x2025 ^ 0x1029 ^ 0x0831 ^ 0x0441 ^ 0x0260));
}
