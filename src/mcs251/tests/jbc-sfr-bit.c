/* JBC is not made for SFR bits on MCS-251: a TSC80251G1D drops a hardware
   set of the tested flag that lands during the JBC.  Bit variables keep the
   atomic test-and-clear (check-codegen.sh). */
__sbit __at (0x98) RX_FULL;
__sbit __at (0x99) TX_DONE;

volatile __bit shared;
volatile unsigned char received;

void
wait_tx (void)
{
    while (!TX_DONE)
        ;
    TX_DONE = 0;
}

void
serial_isr (void) __interrupt (4)
{
    if (RX_FULL) {
        RX_FULL = 0;
        received++;
    }
}

unsigned char
take (void)
{
    if (shared) {
        shared = 0;
        return 1;
    }
    return 0;
}

void
main (void)
{
    for (;;)
        {
        }
}
