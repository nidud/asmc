; _RCUNZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcunzip proc uses rsi rdi rbx rc:TRECT, dst:PCHAR_INFO, src:ptr, flags:uint_t

   .new count:int_t

    ldr eax,rc
    ldr rdi,dst
    ldr rsi,src
    ldr ecx,flags

    shr eax,16
    mul ah
    mov count,eax

    .if !( ecx & W_UTF16 )

        lea rdx,[rdi+2]
        mov ecx,count
        xor eax,eax
        rep stosd

        mov rdi,rdx
        mov ecx,count
        decompress()
        mov rdi,dst
        mov ecx,count
        decompress()

        .for ( rbx = dst, rsi = &_unicode850, ecx = 0 : ecx < count : ecx++, rbx+=4 )

            movzx eax,byte ptr [rbx]
            mov ax,[rsi+rax*2]
            mov [rbx],ax
        .endf

    .else

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
    .endif
    .if ( flags & W_RESAT )
        _rcunzipat(rc, dst)
    .endif
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
