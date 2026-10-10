/* mcs251-push-pop-branch.c - register saves across MCS-251 compare jumps.

   The dead push/pop removal did not know JE/JNE/JG/JLE/JSL/JSG/JSLE/JSGE as
   conditional jumps.  It paired a push before a 32-bit compare with the pop
   on the fall-through path and removed both, while the other path still
   popped, and SPX ended up 2 bytes low (bug-2031 with --stack-auto, when an
   assertion failed).
 */

#include <testfwk.h>

#pragma disable_warning 322

static unsigned char mismatches;

static void
mismatch (int line)
{
  (void) line;
  mismatches++;
}

unsigned long gv;
unsigned long *gp = &gv;
unsigned long gl = 1;   /* never equal to (unsigned long) gp */
unsigned int gi = 2;

static unsigned char
locals (void)
{
  unsigned long lv;
  unsigned long *lp = &lv;
  unsigned char lc = (unsigned char) &lv;
  unsigned int li = (unsigned int) &lv;
  unsigned long ll = (unsigned long) &lv;

  if (gi == (unsigned int) gp)
    mismatch (__LINE__);
  if (gl != (unsigned long) gp)
    mismatch (__LINE__);
  if (gl == (unsigned long) gp)
    mismatch (__LINE__);
  if (gl != (unsigned long) gp)
    mismatch (__LINE__);

  ASSERT (lc == (unsigned char) lp);
  ASSERT (li == (unsigned int) lp);
  ASSERT (ll == (unsigned long) lp);
  return lc;
}

void
testPushPopBranch (void)
{
  unsigned char r;

  mismatches = 0;
  r = locals ();
  ASSERT (mismatches == 2);
  r = locals ();
  ASSERT (mismatches == 4);
  (void) r;
}
