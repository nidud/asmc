; _RCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

.code

_rczip proc uses rsi rdi rbx rc:TRECT, dst:ptr, src:PCHAR_INFO

   .new count:int_t

    movzx   eax,rc.col
    mul     rc.row
    mov     count,eax

    .for ( ecx = 0, rsi = src : ecx < count : ecx++, rsi += 4 )

        mov al,[rsi+2]
        mov dl,al
        shr dl,4
        and al,0x0F
        mov [rsi+2],al
        mov [rsi+3],dl
    .endf

    mov rdi,dst
    mov rsi,src
    mov ecx,count
    compress()
    mov rsi,src
    inc rsi
    mov ecx,count
    compress()
    mov rsi,src
    add rsi,2
    mov ecx,count
    compress()
    mov rsi,src
    add rsi,3
    mov ecx,count
    compress()
    mov rax,rdi
    sub rax,dst
    ret

    option dotname

compress:

    mov     al,[rsi]
    mov     dl,al
    mov     dh,al
    and     dh,0xF0
    cmp     al,[rsi+4]
    jnz     .1
    mov     ebx,0xF001
    jmp     .3
.1:
    cmp     dh,0xF0
    jnz     .7
    mov     eax,0x01F0
    jmp     .6
.2:
    inc     ebx
    add     rsi,4
    mov     al,[rsi]
    cmp     al,[rsi+4]
    jne     .4
.3:
    dec     ecx
    jnz     .2
.4:
    mov     eax,ebx
    cmp     ebx,0xF002
    jnz     .5
    cmp     dh,0xF0
    jz      .5
    mov     al,dl
    stosb
    jmp     .7
.5:
    xchg    ah,al
.6:
    stosw
    mov     al,dl
.7:
    stosb
    test    ecx,ecx
    jz      .8
    add     rsi,4
    dec     ecx
    jnz     compress
.8:
    retn

_rczip endp

_rcunzip proc uses rsi rdi rbx rc:TRECT, dst:PCHAR_INFO, src:ptr

   .new count:int_t

    movzx   eax,rc.col
    mul     rc.row
    mov     count,eax

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

    .for ( ecx = 0, rsi = dst : ecx < count : ecx++, rsi += 4 )

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
