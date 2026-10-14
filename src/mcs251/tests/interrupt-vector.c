volatile unsigned char timer_ticks;

void
timer0_interrupt (void) __interrupt (1)
{
    timer_ticks++;
}

/* Loads DPXL for its own far store; must save it (bug 35). */
void
timer1_far_store (void) __interrupt (3)
{
    *(volatile unsigned char __far *) 0x014000UL = timer_ticks;
}

void
serial_bank1 (void) __interrupt (4) __using (1)
{
    timer_ticks++;
}

/* Writes DPXL through its register-file name. */
void
external0_inline (void) __interrupt (0)
{
    __asm
        mov     wr56,#0x0001
    __endasm;
}

void
main (void)
{
    for (;;)
        {
        }
}
