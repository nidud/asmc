; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

if WINVER GE 0x0600

_strupr proc frame uses rsi string:string_t

    .for ( rsi = rcx : byte ptr [rsi] : rsi++ )

        movzx ecx,byte ptr [rsi]
        toupper(ecx)
        mov [rsi],al
    .endf

    mov rax,string

else

    option win64:rsp nosave noauto

_strupr proc string:string_t

    mov rax,rcx
    .while 1
        mov dl,[rcx]
        .break .if !dl
        sub dl,'a'
        cmp dl,'Z' - 'A' + 1
        sbb dl,dl
        and dl,'a' - 'A'
        xor [rcx],dl
        inc rcx
    .endw

endif
    ret

_strupr endp

    END
