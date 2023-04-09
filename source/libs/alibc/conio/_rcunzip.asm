; _RCUNZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcunzip proc uses rbx r12 r13 rc:TRECT, dst:PCHAR_INFO, src:ptr

   .new count:int_t

    mov r12,rsi
    shr edi,16
    mov eax,edi
    mov bl,ah
    movzx eax,al
    mul bl
    mov count,eax

    mov rsi,rdx
    mov rdi,r12
    mov ecx,count
    decompress()
    mov rdi,r12
    inc rdi
    mov ecx,count
    decompress()
    mov rdi,r12
    add rdi,2
    mov ecx,count
    decompress()
    mov rdi,r12
    add rdi,3
    mov ecx,count
    decompress()

    .for ( ecx=0, rsi=r12 : ecx < count : ecx++, rsi += 4 )

        mov ax,[rsi+2]
        shl ah,4
        or  al,ah
        mov ah,0
        mov [rsi+2],ax
    .endf
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
