        .module imm_a
        .globl stack_top
        .area MCS251CODE (REL,CON,CODE)

; MOV/CMP DRk,#imm with a relocatable value: the zero-extending forms
; (7E x8, BE x8), whatever the value is at assembly time ("stack_top - 1"
; is -1 there).  Absolute values keep the sign-extending form for FFxxxx.
start::
        mov dr60,#stack_top - 1
        mov dr4,#stack_top
        cmp dr4,#stack_top - 1
        mov dr60,#0xff0040
        mov dr4,#-1
        mov dr4,#0x1234
        cmp dr4,#-1
