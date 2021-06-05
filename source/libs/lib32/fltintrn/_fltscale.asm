; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

define  MAX_EXP_INDEX 13

    .code

_fltscale proc uses esi edi ebx p:ptr STRFLT

    mov ebx,p
    mov edi,[ebx].STRFLT.exponent

    lea esi,_fltpowtable
    .ifs ( edi < 0 )

        neg edi
        add esi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if edi

        .for ( ebx = 0 : edi && ebx < MAX_EXP_INDEX : ebx++, edi >>= 1, esi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul(p, esi)
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov ebx,p
            mov [ebx],eax
            mov [ebx+4],eax
            mov [ebx+8],eax
            mov [ebx+12],eax
            mov word ptr [ebx+16],0x7FFF
        .endif
    .endif
    mov eax,p
    ret

_fltscale endp

    end
