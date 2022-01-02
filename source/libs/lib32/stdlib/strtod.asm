; STRTOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; double strtod(nptr, endptr) - convert string to double
;

include stdlib.inc
include errno.inc
include fltintrn.inc
include quadmath.inc

    .code

strtod proc uses esi edi ebx nptr:string_t, endptr:array_t

    mov esi,_strtoflt(nptr)
    lea ebx,[esi].STRFLT.mantissa
    mov edi,[esi].STRFLT.flags
    mov ax,[ebx+14]
    and eax,0x7FFF

    .switch

      .case edi & _ST_ISZERO
        .endc

      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID

        xor eax,eax
        mov [ebx],eax
        .if edi & _ST_NEGNUM
            mov eax,0x80000000
        .endif
        .if ( edi & _ST_ISNAN or _ST_ISINF )
            or eax,0x7FFF0000
            .if ( edi & _ST_ISNAN )
                or eax,0x00008000
            .endif
        .endif
        mov [ebx+4],eax
        .endc

      .case edi & _ST_OVERFLOW
      .case eax >= 0x43FF
        xor eax,eax
        mov edx,0x7FF00000
        .if edi & _ST_NEGNUM
            or edx,0x80000000
        .endif
        mov [ebx],eax
        mov [ebx+4],edx
        mov errno,ERANGE
        .endc

      .case edi & _ST_UNDERFLOW
      .case eax < 0x3BCC
        xor eax,eax
        mov [ebx],eax
        mov [ebx+4],eax
        mov errno,ERANGE
        .endc

      .case eax >= 0x3BCD
        __cvtq_sd(ebx, ebx)
        .if !( edi & _ST_OVERFLOW )
            mov eax,[ebx+4]
            and eax,0x7FF00000
            .ifnz
                .endc .if eax != 0x7FF00000
            .endif
        .endif
        mov errno,ERANGE
        .endc

      .case eax >= 0x3BCC
        __cvtq_sd(ebx, ebx)
        mov eax,[ebx]
        or  eax,[ebx+4]
        .ifnz
            mov eax,[ebx+4]
            and eax,0x7FF00000
            .endc .ifnz
        .endif
        mov errno,ERANGE
    .endsw

    mov eax,endptr
    .if eax
        mov edx,[esi].STRFLT.string
        mov [eax],edx
    .endif

    fld qword ptr [ebx]
    ret

strtod endp

    END
