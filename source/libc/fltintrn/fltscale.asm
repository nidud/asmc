; FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

define MAX_EXP_INDEX 13

    .code

_fltscale proc __ccall uses rsi rdi rbx fp:ptr STRFLT

    ldr rbx,fp
    mov edi,[rbx].STRFLT.exponent
    lea rsi,_fltpowtable
    .ifs ( edi < 0 )

        neg edi
        add rsi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if ( edi )

        .for ( ebx = 0 : edi && ebx < MAX_EXP_INDEX : ebx++, edi >>= 1, rsi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul( fp, rsi )
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov rbx,fp
ifdef _WIN64
            mov [rbx].STRFLT.mantissa.l,rax
            mov [rbx].STRFLT.mantissa.h,rax
else
            mov dword ptr [rbx].STRFLT.mantissa.l[0],eax
            mov dword ptr [rbx].STRFLT.mantissa.l[4],eax
            mov dword ptr [rbx].STRFLT.mantissa.h[0],eax
            mov dword ptr [rbx].STRFLT.mantissa.h[4],eax
endif
            mov [rbx].STRFLT.mantissa.e,0x7FFF
        .endif
    .endif
    .return( fp )

_fltscale endp

    end
