/* mcs251-near-ptr-member.c - __near pointer members of far objects.

   For a pointer member of an aggregate, CSE gives the address operand the
   size of the member (aggr2ptr == 2).  With a 1-byte __near member the
   address looked like a 16-bit one and was loaded without DPXL, so the
   store went to whatever region DPXL held (bug-868103).
 */

#include <testfwk.h>

#ifdef __SDCC_mcs251
struct holder
{
  unsigned char tag;
  __near char *p[2];
  __near int *q;
};

__near char c1 = 'x', c2 = 'y';
__near int i1 = 0x1234;
__far struct holder fh;
__near char * __xdata xa[3];
static const char text[] = "code";
#endif

void
testNearPtrMember (void)
{
#ifdef __SDCC_mcs251
  volatile char t;

  /* leave DPXL at the region of code space before every store */
  t = text[0];
  fh.p[1] = &c1;
  t = text[1];
  fh.p[0] = &c2;
  t = text[2];
  fh.q = &i1;
  t = text[3];
  xa[2] = &c2;
  (void) t;

  ASSERT (fh.p[1] == &c1);
  ASSERT (fh.p[0] == &c2);
  ASSERT (*fh.p[1] == 'x');
  ASSERT (*fh.q == 0x1234);
  ASSERT (xa[2] == &c2);
  ASSERT (*xa[2] == 'y');
#endif
}
