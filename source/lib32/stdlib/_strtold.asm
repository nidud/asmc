; _STRTOLD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc
include fltintrn.inc
include crtl.inc

    .code

_strtold proc uses esi edi ebx string:LPSTR, suffix:LPSTR

    mov esi,_strtoflt(string)
    mov ebx,[esi].S_STRFLT.mantissa
    mov edi,[esi].S_STRFLT.flags
    mov ax,[ebx+8]
    and eax,0x7FFF

    .switch
      .case edi & _ST_ISZERO
        .endc
      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
        xor eax,eax
        mov [ebx],eax
        .if edi & _ST_NEGNUM
            mov eax,80000000h
        .endif
        mov [ebx+4],eax
        .if edi & _ST_ISNAN or _ST_ISINF
            mov eax,7FFFh
            .if edi & _ST_ISNAN
                or eax,8000h
            .endif
            mov [ebx+8],ax
        .endif
        .endc
      .case edi & _ST_OVERFLOW
      .case eax >= 43FFh
        xor eax,eax
        xor edx,edx
        .if edi & _ST_NEGNUM
            or edx,80000000h
        .endif
        mov [ebx],eax
        mov [ebx+4],edx
        mov edx,7FFFh
        mov [ebx+8],dx
        jmp err_range
      .case edi & _ST_UNDERFLOW
      .case eax < 3BCCh
        xor eax,eax
        mov [ebx],eax
        mov [ebx+4],eax
        mov [ebx+8],ax
        jmp err_range
      .case eax >= 3BCDh
        .if !( edi & _ST_OVERFLOW )
            mov ax,[ebx+8]
            and ax,7FFFh
            .if !ZERO?
                mov ax,[ebx+8]
                and ax,7FFFh
                .endc .if ax != 7FFFh
            .endif
        .endif
        jmp err_range
      .case eax >= 3BCCh
        mov eax,[ebx]
        or  eax,[ebx+4]
        .if !ZERO?
            mov ax,[ebx+8]
            and ax,7FFFh
            .endc .if !ZERO?
        .endif
       err_range:
        mov errno,ERANGE
    .endsw
    mov eax,suffix
    .if eax
        mov edx,[esi].S_STRFLT.string
        mov [eax],edx
    .endif
    fld TBYTE PTR [ebx]
    ret
_strtold endp

    END
