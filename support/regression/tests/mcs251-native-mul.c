/* mcs251-native-mul.c - MCS251 native 16x16->32 multiply (MUL WR12,WR8).

   - An operand already in A (the product of a preceding MUL AB) was
     overwritten while the other operand was loaded through A.
   - A result tuple overlapping R12-R15 (but not DR12 itself) was
     overwritten when the saved scratch registers were restored.  The
     second case is the mantissa product of the float multiply.
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
union float_long
{
  float f;
  unsigned long l;
};

static volatile unsigned char small_value = 37;
static volatile float fa = 3.75f, fb = -0.5f, fc = 2.0f, fd = 1.5f;

static unsigned long
square_times_thousand (void)
{
  unsigned char t = small_value;
  return (unsigned long) t * t * 1000u;
}

/* The core of the library's __fsmul (device/lib/_fsmul.c). */
static unsigned long
mantissa_product (unsigned long m1, unsigned long m2)
{
  volatile union float_long fl1, fl2;
  unsigned long result;

  fl1.l = m1;
  fl2.l = m2;
  result = (unsigned long)((unsigned short)(fl1.l >> 8)) * (unsigned short)(fl2.l >> 8);
  result += ((unsigned long)((unsigned short)(fl1.l & 0xff)) * (unsigned short)(fl2.l >> 8)) >> 8;
  result += ((unsigned long)((unsigned short)(fl2.l & 0xff)) * (unsigned short)(fl1.l >> 8)) >> 8;
  result += 0x40;
  return result;
}

static unsigned long
bits (float f)
{
  union float_long u;
  u.f = f;
  return u.l;
}
#endif

void
testNativeMul (void)
{
#if defined (__SDCC_mcs251)
  ASSERT (square_times_thousand () == 1369000UL);
  ASSERT (mantissa_product (0xf00000UL, 0x800000UL) == 0x78000040UL);
  ASSERT (mantissa_product (0x800000UL, 0xc00000UL) == 0x60000040UL);
  ASSERT (bits (fa * fb) == 0xbff00000UL);
  ASSERT (bits (fc * fd) == 0x40400000UL);
  ASSERT (bits (fd * fd) == 0x40100000UL);
#endif
}
