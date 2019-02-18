; __INITIALIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

    option win64:rsp nosave

__initialize proc uses rsi rdi rbx offset_start:ptr, offset_end:ptr

    mov rax,rdx
    sub rax,rcx

    .ifnz

        .for ( rsi = rcx, rdi = &[rcx+rax] :: )

            .for ( eax = 0,
                   ecx = 256,
                   rbx = rsi,
                   rdx = rdi : rbx != rdi : rbx += 16 )

                .if ( rax != [rbx] && rcx >= [rbx+8] )

                    mov rcx,[rbx+8]
                    mov rdx,rbx

                .endif

            .endf

            .break .if rdx == rdi

            mov  rbx,[rdx]
            mov  [rdx],rax
            call rbx

        .endf

    .endif
    ret

__initialize endp

    end
