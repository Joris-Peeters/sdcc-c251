/* mcs251-spill-slot-size.c - values of different sizes in one spill location.

   A spill location is reused by a later value no larger than it.  Big-endian,
   a 3-byte pointer does not keep its least significant byte where a 4-byte
   long had it, so in the iCode where the long dies and the pointer is born
   (pointer + long offset) the first result byte overwrote an operand byte
   that was still to be read (gcc-torture pr20527-1, --stack-auto).
 */

#include <testfwk.h>

static void
deltas (long *limit, long *base, long minLen, long maxLen)
{
  long i;
  long vec = 0;

  for (i = minLen; i <= maxLen; i++)
    {
      vec += base[i + 1] - base[i];
      limit[i] = vec - 1;
    }
}

static void
bytes (unsigned char *out, const unsigned char *in, long from, long to)
{
  long i;

  for (i = from; i <= to; i++)
    out[i] = in[i + 1] - in[i];
}

static long b[] = {1, 5, 11, 23};
static const unsigned char c[] = {3, 7, 15, 31, 63};

void
testSpillSlotSize (void)
{
  long l[3] = {0, 0, 0};
  unsigned char o[4] = {0, 0, 0, 0};

  deltas (l, b, 0, 2);
  ASSERT (l[0] == 3);
  ASSERT (l[1] == 9);
  ASSERT (l[2] == 21);

  bytes (o, c, 0, 3);
  ASSERT (o[0] == 4);
  ASSERT (o[1] == 8);
  ASSERT (o[2] == 16);
  ASSERT (o[3] == 32);
}
