; _STRTOLD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; long double strtod(nptr, endptr) - convert string to long double
;

include stdlib.inc
include errno.inc
include fltintrn.inc
include quadmath.inc

    .code

_strtold proc uses esi edi ebx string:string_t, suffix:string_t

    mov     esi,_strtoflt(string)
    mov     ebx,[esi].STRFLT.mantissa
    mov     edi,[esi].STRFLT.flags
    ;
    ; real16 --> real10
    ;
    movzx   eax,word ptr [ebx+14]
    mov     edx,[ebx+10]
    mov     ecx,eax
    and     eax,LD_EXPMASK
    neg     eax
    mov     eax,[ebx+6]
    rcr     edx,1
    rcr     eax,1

    .ifc    ; round result

        .if ( eax == -1 && edx == eax )

            xor eax,eax
            mov edx,0x80000000
            inc cx
        .else
            add eax,1
            adc edx,0
        .endif
    .endif
    mov [ebx],eax
    mov [ebx+4],edx
    mov [ebx+8],cx

    and ecx,0x7FFF

    .switch

      .case edi & _ST_ISZERO
        .endc

      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
        xor eax,eax
        mov [ebx],eax
        .if edi & _ST_NEGNUM
            mov eax,0x80000000
        .endif
        mov [ebx+4],eax
        .if edi & _ST_ISNAN or _ST_ISINF
            mov eax,0x7FFF
            .if edi & _ST_ISNAN
                or eax,0x8000
            .endif
            mov [ebx+8],ax
        .endif
        .endc

      .case edi & _ST_OVERFLOW
      .case ecx >= 0x43FF
        xor eax,eax
        mov [ebx],eax
        .if edi & _ST_NEGNUM
            or eax,0x80000000
        .endif
        mov [ebx+4],eax
        mov word ptr [ebx+8],0x7FFF
        mov errno,ERANGE
        .endc

      .case edi & _ST_UNDERFLOW
      .case ecx < 0x3BCC
        xor eax,eax
        mov [ebx],eax
        mov [ebx+4],eax
        mov [ebx+8],ax
        mov errno,ERANGE
        .endc

      .case ecx >= 0x3BCD
        .endc .if ( !( edi & _ST_OVERFLOW ) && ecx != 0x7FFF )
        mov errno,ERANGE
        .endc

      .case ecx >= 0x3BCC
        .endc .if ( ( eax || edx ) && ecx )
        mov errno,ERANGE
        .endc
    .endsw

    mov eax,suffix
    .if eax
        mov edx,[esi].STRFLT.string
        mov [eax],edx
    .endif

    fld TBYTE PTR [ebx]
    ret

_strtold endp

    END
