/* mcs251-pointer-literal-init.c - static pointers initialized from integers.

   (void *) 0xAABB in a static initializer was emitted in the MCS-51 generic
   pointer layout (low byte, high byte, tag) and read back as 0xAABB00.
   Character pointers took another path and were right.
 */

#include <testfwk.h>

#ifdef __SDCC_mcs251
void *gp = (void *) 0xAABB;
__xdata int *xp = (__xdata int *) 0x012345;
const int *const tab[] = {(const int *) 0x1234, (const int *) 0x56789aUL};
struct
{
  void *arg;
  unsigned char c;
} gs[] = {{(void *) 0x0420, 1}};
#endif

void
testPointerLiteralInit (void)
{
#ifdef __SDCC_mcs251
  volatile unsigned long a = 0xAABB;

  ASSERT (gp == (void *) a);
  ASSERT ((unsigned long) gp == 0xAABBUL);
  ASSERT ((unsigned long) xp == 0x012345UL);
  ASSERT ((unsigned long) tab[0] == 0x1234UL);
  ASSERT ((unsigned long) tab[1] == 0x56789aUL);
  ASSERT ((unsigned long) gs[0].arg == 0x0420UL);
  ASSERT (gs[0].c == 1);
#endif
}
