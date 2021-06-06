; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

define MAX_EXP_INDEX 13

    .code

_fltscale proc uses rsi rdi rbx r12 fp:ptr STRFLT

    mov rbx,rcx
    mov edi,[rbx].STRFLT.exponent
    lea rsi,_fltpowtable
    .ifs ( edi < 0 )

        neg edi
        add rsi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if edi

        .for ( r12d = 0 : edi && r12d < MAX_EXP_INDEX : r12d++, edi >>= 1, rsi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul(rbx, rsi)
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov [rbx].STRFLT.mantissa.l,rax
            mov [rbx].STRFLT.mantissa.h,rax
            mov [rbx].STRFLT.mantissa.e,0x7FFF
        .endif
    .endif
    mov rax,rbx
    ret

_fltscale endp

    end
