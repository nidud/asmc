; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

strupr::

if WINVER GE 0x0600

_strupr proc uses rsi string:string_t

    .for ( rsi = string : byte ptr [rsi] : rsi++ )

        movzx ecx,byte ptr [rsi]
        toupper(ecx)
        mov [rsi],al
    .endf

    mov rax,string

else

    option dotname

_strupr proc string:string_t

ifndef _WIN64
    mov     ecx,string
endif
    mov     rax,rcx
.0:
    mov     dl,[rcx]
    test    dl,dl
    jz      .1
    sub     dl,'a'
    cmp     dl,'Z' - 'A' + 1
    sbb     dl,dl
    and     dl,'a' - 'A'
    xor     [rcx],dl
    inc     rcx
    jmp     .0
.1:

endif
    ret

_strupr endp

    END
