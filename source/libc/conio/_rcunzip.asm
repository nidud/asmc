; _RCUNZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcunzip proc uses rsi rdi rbx rc:TRECT, dst:PCHAR_INFO, src:ptr

   .new count:int_t

    movzx eax,rc.col
    mul rc.row
    mov count,eax

    mov rsi,src
    mov rdi,dst
    mov ecx,count
    decompress()
    mov rdi,dst
    inc rdi
    mov ecx,count
    decompress()
    mov rdi,dst
    add rdi,2
    mov ecx,count
    decompress()
    mov rdi,dst
    add rdi,3
    mov ecx,count
    decompress()
    ret

decompress:

    .repeat
        lodsb
        mov dl,al
        and dl,0xF0
        .if dl == 0xF0
            mov ah,al
            lodsb
            and eax,0xFFF
            mov ebx,eax
            lodsb
            .repeat
                stosb
                add rdi,3
                dec ebx
               .break .ifz
            .untilcxz
            .break .if !ecx
        .else
            stosb
            add rdi,3
        .endif
    .untilcxz
    retn

_rcunzip endp

    end
