/* mcs251-long-far-symbol.c - DPTR loads of far objects with long names.

   The DPTR cache copied operands into 64-byte buffers, so the DPXL operand
   of a long name, "#((name + 0x0004) >> 16)", lost its end.  That loaded a
   wrong DPXL, or crashed the peephole optimizer on the unbalanced
   parenthesis (gcc-torture 20080519-1, large model).
 */

#include <testfwk.h>

struct quad
{
  unsigned char b[6];
};

__xdata struct quad a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer;

static void
fill (__xdata struct quad *q, unsigned char base)
{
  unsigned char i;

  for (i = 0; i < 6; i++)
    q->b[i] = base + i;
}

void
testLongFarSymbol (void)
{
  static __xdata unsigned long a_static_local_with_a_long_name_like_the_gcc_torture_test[3];

  fill (&a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer, 0x10);
  a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer.b[4] ^= 0xff;
  a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer.b[5] += 3;
  ASSERT (a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer.b[4] == (0x14 ^ 0xff));
  ASSERT (a_far_object_whose_name_is_long_enough_to_overflow_the_dptr_cache_buffer.b[5] == 0x18);

  a_static_local_with_a_long_name_like_the_gcc_torture_test[1] = 0x12345678ul;
  a_static_local_with_a_long_name_like_the_gcc_torture_test[2] = ~a_static_local_with_a_long_name_like_the_gcc_torture_test[1];
  ASSERT (a_static_local_with_a_long_name_like_the_gcc_torture_test[2] == 0xedcba987ul);
}
