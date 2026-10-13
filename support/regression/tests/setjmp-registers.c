/* setjmp-registers.c - locals in registers across setjmp.

   setjmp returns a second time from longjmp.  A value the caller keeps in
   a register across the call must still be there then, but the register
   holds whatever the code before longjmp left in it, and a copy the caller
   pushed around the call is overwritten by the saves of its next call
   (mcs251 lost locals in R8, R9 and R12-R15; mcs51 with --stack-auto
   restored shifted bytes after critical_throw).
 */

#include <testfwk.h>
#include <setjmp.h>

static volatile unsigned char v[4] = {0x11, 0x22, 0x44, 0x88};
static jmp_buf global_buf;

static void
thrower (jmp_buf b, int value)
{
  longjmp (b, value);
}

static unsigned int
with_local (void)
{
  jmp_buf b;
  unsigned char w = v[0], x = v[1], y = v[2], z = v[3];
  int r;

  r = setjmp (b);
  if (r == 0)
    thrower (b, 3);
  return r + w + x + y + z;
}

static unsigned int
with_global (void)
{
  unsigned char w = v[0], x = v[1], y = v[2], z = v[3];
  int r;

  r = setjmp (global_buf);
  if (r == 0)
    thrower (global_buf, 5);
  return r + w + x + y + z;
}

static volatile unsigned char sink;

/* t lives across the call to thrower but not across setjmp, so the
   registers saved around that call differ from those around setjmp. */
static unsigned int
shifted_saves (void)
{
  unsigned char w = v[0], x = v[1], y = v[2], z = v[3];
  int r;

  r = setjmp (global_buf);
  if (r == 0)
    {
      unsigned char t = v[3] ^ 0x5a;
      thrower (global_buf, 9);
      sink = t;
    }
  return r + w + x + y + z;
}

/* The critical section saves the interrupt state on the stack before the
   registers saved around thrower, so those land one byte higher. */
static unsigned int
critical_throw (void)
{
  unsigned char w = v[0], x = v[1], y = v[2], z = v[3];
  int r;

  r = setjmp (global_buf);
  if (r == 0)
    __critical
      {
        thrower (global_buf, 11);
      }
  return r + w + x + y + z;
}

void
testSetjmpRegisters (void)
{
  ASSERT (with_local () == 3 + 0x11 + 0x22 + 0x44 + 0x88);
  ASSERT (with_global () == 5 + 0x11 + 0x22 + 0x44 + 0x88);
  ASSERT (shifted_saves () == 9 + 0x11 + 0x22 + 0x44 + 0x88);
  ASSERT (critical_throw () == 11 + 0x11 + 0x22 + 0x44 + 0x88);
}
