/* long-identifier.c - an operand longer than the peephole pattern buffer.

   The peephole optimizer copied the value of a pattern variable into a
   MAX_PATTERN_LEN (256) byte buffer without a bound, so an instruction
   operand built from a long identifier overflowed the stack, and an
   unbalanced '(' ran past the end of the line ("stack smashing detected").
   mcs251 shows it, as its DPXL operand, #((name + 0x0004) >> 16), is the
   longest.
 */

#include <testfwk.h>

struct six
{
  unsigned char b[6];
};

#if defined(__SDCC_mcs51) || defined(__SDCC_mcs251) || defined(__SDCC_ds390)
#define FAR __xdata
#else
#define FAR
#endif

FAR struct six a_far_object_whose_name_is_longer_than_the_peephole_pattern_buffer_of_two_hundred_and_fifty_six_characters_that_bindvar_used_to_copy_its_operands_into_without_any_bound_so_that_this_line_overflowed_the_stack_and_crashed_the_compiler_with_stack_smashi;

void
testLongIdentifier (void)
{
  a_far_object_whose_name_is_longer_than_the_peephole_pattern_buffer_of_two_hundred_and_fifty_six_characters_that_bindvar_used_to_copy_its_operands_into_without_any_bound_so_that_this_line_overflowed_the_stack_and_crashed_the_compiler_with_stack_smashi.b[4] = 0x5a;
  a_far_object_whose_name_is_longer_than_the_peephole_pattern_buffer_of_two_hundred_and_fifty_six_characters_that_bindvar_used_to_copy_its_operands_into_without_any_bound_so_that_this_line_overflowed_the_stack_and_crashed_the_compiler_with_stack_smashi.b[5] = 0xa5;
  ASSERT (a_far_object_whose_name_is_longer_than_the_peephole_pattern_buffer_of_two_hundred_and_fifty_six_characters_that_bindvar_used_to_copy_its_operands_into_without_any_bound_so_that_this_line_overflowed_the_stack_and_crashed_the_compiler_with_stack_smashi.b[4] == 0x5a);
  ASSERT (a_far_object_whose_name_is_longer_than_the_peephole_pattern_buffer_of_two_hundred_and_fifty_six_characters_that_bindvar_used_to_copy_its_operands_into_without_any_bound_so_that_this_line_overflowed_the_stack_and_crashed_the_compiler_with_stack_smashi.b[5] == 0xa5);
}
