/* mcs251-signed-shift-acc.c - MCS251 signed right shift by a variable.

   The sign bit was taken with RLC A, which destroyed the operand when it
   already lived in A (a volatile read in --model-large), so every result
   was off by one shift.
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
static volatile signed char sc = -0x5b;
static volatile unsigned char counts[] = {0, 1, 3, 7};
static const signed char expected[] = {-0x5b, -46, -12, -1};
#endif

void
testSignedShiftAcc (void)
{
#if defined (__SDCC_mcs251)
  unsigned char i;

  for (i = 0; i < 4; i++)
    ASSERT ((signed char)(sc >> counts[i]) == expected[i]);
#endif
}
