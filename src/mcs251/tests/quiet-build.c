/* A compile and link that must print nothing (check-quiet-build.sh).
   The far stores to different addresses exercise the DPTR cache, which
   once printed debug lines on stderr. */
#define PORT_A (*(volatile unsigned char __far *)0x01ff00UL)
#define PORT_B (*(volatile unsigned char __far *)0x01ff10UL)

volatile unsigned char __xdata value = 3;

void
main (void)
{
  PORT_A = 1;
  PORT_B = value;
  PORT_A = 2;
  PORT_B = value + 1;
  for (;;)
    ;
}
