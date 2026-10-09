/* mcs251-far-store-cache.c - MCS251 DPTR cache.

   The code generator remembers which far address DPTR/DPXL hold to skip
   reloads.  Loading another far operand through DPX (here a parameter in
   xdata, --model-large) must invalidate that, or the following store goes
   to the parameter instead of the target.
 */

#include <testfwk.h>

#if defined (__SDCC_mcs251)
static volatile unsigned char __far sink_a;
static volatile unsigned char __far sink_b;
static unsigned char __far source = 0x5a;

static void
store_back_to_back (unsigned char tag, unsigned char value)
{
  sink_a = 1;
  sink_a = tag;
  sink_b = 2;
  sink_b = value;
  sink_b = source;
  sink_a = value;
}
#endif

void
testFarStoreCache (void)
{
#if defined (__SDCC_mcs251)
  store_back_to_back (0x41, 0x99);
  ASSERT (sink_a == 0x99);
  ASSERT (sink_b == 0x5a);
  store_back_to_back (0x17, 0x23);
  ASSERT (sink_a == 0x23);
  ASSERT (sink_b == 0x5a);
#endif
}
