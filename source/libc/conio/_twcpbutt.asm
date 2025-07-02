; _TWCPBUTT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

wcpbutt proc uses rsi rdi rbx wp:PCHAR_INFO, l:int_t, x:int_t, string:tstring_t

    ldr rdi,wp
    ldr ecx,x

    xor eax,eax
    mov al,at_background[BG_PBUTTON]
    or  al,at_foreground[FG_TITLE]
    shl eax,16
    mov al,' '
    mov rbx,rdi
    mov rdx,rdi
    rep stosd

    mov eax,[rdi+2]
    and eax,11110000B
    or  al,at_foreground[FG_PBSHADE]
    shl eax,16
    mov ax,U_LOWER_HALF_BLOCK
    stosd

    mov ecx,l
    inc ecx
    shl ecx,2
    lea rdi,[rdx+rcx]
    mov ecx,x
    mov ax,U_UPPER_HALF_BLOCK
    rep stosd

    mov rsi,string
    mov rdi,rbx
    add rdi,8
    xor eax,eax
    mov al,at_background[BG_PBUTTON]
    or  al,at_foreground[FG_TITLEKEY]
    shl eax,16

    .while 1

        _tlodsb
        .break .if !_tal

        .if _tal != '&'
            mov [rdi],_tal
            add rdi,4
        .else
            _tlodsb
            .break .if !_tal
            stosd
        .endif
    .endw
    mov rax,wp
    ret

wcpbutt endp

    END
