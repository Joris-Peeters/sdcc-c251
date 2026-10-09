/* mcs251-far-pointer-spaces.c - MCS251 __far pointer conversions.

   __far and generic pointers are both flat 24-bit on MCS251, so a __far
   pointer parameter accepts code, idata, data and generic pointers, like
   Keil C251's far.
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
static const char __code code_string[] = "CODE";
static char __idata idata_string[] = "IDATA";
static char __xdata xdata_string[] = "XDATA";
static char data_string[] = "DATA";

static unsigned char
length (const char __far *s)
{
  unsigned char n = 0;
  while (*s++)
    n++;
  return n;
}

static void
lower (char __far *s)
{
  for (; *s; s++)
    *s += 'a' - 'A';
}
#endif

void
testFarPointerSpaces (void)
{
#if defined (__SDCC_mcs251)
  const char *generic = code_string;

  ASSERT (length (code_string) == 4);
  ASSERT (length (idata_string) == 5);
  ASSERT (length (xdata_string) == 5);
  ASSERT (length (data_string) == 4);
  ASSERT (length (generic) == 4);
  ASSERT (length ("literal") == 7);
  lower (idata_string);
  lower (xdata_string);
  ASSERT (idata_string[0] == 'i');
  ASSERT (xdata_string[4] == 'a');
#endif
}
