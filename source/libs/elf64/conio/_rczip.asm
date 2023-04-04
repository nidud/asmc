; _RCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rczip proc uses rbx r12 r13 _rc:TRECT, dst:ptr, src:PCHAR_INFO

   .new     rc:TRECT = _rc
   .new     count:int_t
    mov     r12,dst
    mov     r13,src
    movzx   eax,rc.col
    mul     rc.row
    mov     count,eax

    .for ( ecx=0, rsi=r13 : ecx < count : ecx++, rsi+=4 )

        mov al,[rsi+2]
        mov dl,al
        shr dl,4
        and al,0x0F
        mov [rsi+2],al
        mov [rsi+3],dl
    .endf

    mov rdi,r12
    mov rsi,r13
    mov ecx,count
    compress()
    mov rsi,r13
    inc rsi
    mov ecx,count
    compress()
    mov rsi,r13
    add rsi,2
    mov ecx,count
    compress()
    mov rsi,r13
    add rsi,3
    mov ecx,count
    compress()
    mov rax,rdi
    sub rax,r12
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

    end
