; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

if WINVER GE 0x0600

_strlwr proc uses rsi string:string_t

    .for ( rsi = string : byte ptr [rsi] : rsi++ )

        movzx ecx,byte ptr [rsi]
        tolower(ecx)
        mov [rsi],al
    .endf
    mov rax,string

else

    option dotname

_strlwr proc string:string_t

ifndef _WIN64
    mov     ecx,string
endif
    mov     rdx,rcx
.0:
    mov     al,[rcx]
    test    al,al
    jz      .1

    sub     al,'A'
    cmp     al,'Z' - 'A' + 1
    sbb     al,al
    and     al,'a' - 'A'
    xor     [rcx],al
    inc     rcx
.1:
    mov     rax,rdx

endif
    ret

_strlwr endp

    end
