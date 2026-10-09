/* MCS251: __far and generic pointers share the flat 24-bit space, so a
   __far pointer accepts code, idata, data and generic pointers.  On MCS51
   __far is xdata only and the same conversions stay errors. */
static const char __code code_text[] = "code";
static char __idata idata_text[] = "idata";
static char data_text[] = "data";

unsigned char
far_length (const char __far *s)
{
  unsigned char n = 0;
  while (*s++)
    n++;
  return n;
}

unsigned char
far_conversions (const char *generic)
{
  const char __far *p = code_text;

  return far_length (code_text) + far_length (idata_text) +
         far_length (data_text) + far_length (generic) + far_length (p);
}
