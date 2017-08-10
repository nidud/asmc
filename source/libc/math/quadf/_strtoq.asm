include intn.inc
include errno.inc

    .code

_strtoq proc uses esi edi ebx number:ptr, string:LPSTR, suffix:LPSTR

local exponent:dword

    mov edi,_atonf(number, string, suffix, &exponent, Q_SIGBITS, Q_EXPBITS, 4)
    mov ebx,number
    mov ax,[ebx+14]
    and eax,Q_EXPMASK
    mov edx,1

    .switch
      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
        mov edx,0x7FFF0000
        .if edi & _ST_ISNAN or _ST_INVALID
            or edx,0x00004000
        .endif
        .endc
      .case edi & _ST_OVERFLOW
      .case eax >= Q_EXPMAX + Q_EXPBIAS
        mov edx,0x7FFF0000
        .if edi & _ST_NEGNUM
            or edx,0x80000000
        .endif
        .endc
      .case edi & _ST_UNDERFLOW
        xor edx,edx
        .endc
    .endsw
    .if edx != 1
        xor eax,eax
        mov [ebx],eax
        mov [ebx+4],eax
        mov [ebx+8],eax
        mov [ebx+12],edx
        mov errno,ERANGE
    .elseif exponent
        _normalizefq(number, exponent)
    .endif
    mov eax,number
    ret

_strtoq endp

    END
