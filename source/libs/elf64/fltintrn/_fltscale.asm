; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

define MAX_EXP_INDEX 13

    .code

_fltscale proc uses rbx r12 r13 r14 fp:ptr STRFLT

    mov rbx,rdi
    mov r14d,[rbx].STRFLT.exponent
    lea r13,_fltpowtable
    .ifs ( r14d < 0 )

        neg r14d
        add r13,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if r14d

        .for ( r12d = 0 : r14d && r12d < MAX_EXP_INDEX : r12d++, r14d >>= 1, r13 += EXTFLOAT )

            .if ( r14d & 1 )

                _fltmul(rbx, r13)
            .endif
        .endf

        .if ( r14d != 0 )

            ; exponent overflow

            xor eax,eax
            mov [rbx].STRFLT.mantissa.l,rax
            mov [rbx].STRFLT.mantissa.h,rax
            mov [rbx].STRFLT.mantissa.e,0x7FFF
        .endif
    .endif
    .return( rbx )

_fltscale endp

    end
