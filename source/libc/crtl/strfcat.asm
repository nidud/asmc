; STRFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

strfcat proc uses rsi rdi buffer:string_t, path:string_t, file:string_t

    ldr rsi,path
    ldr rdx,buffer

    xor eax,eax
    mov ecx,-1

    .if ( rsi )

        mov   rdi,rsi ; overwrite buffer
        repne scasb
        mov   rdi,rdx
        not   ecx
        rep   movsb
    .else
        mov   rdi,rdx ; length of buffer
        repne scasb
    .endif
    dec rdi

    .if ( rdi != rdx ) ; add slash if missing

        mov al,[rdi-1]

        .if ( !( al == '\' || al == '/' ) )

            mov al,'\'
            stosb
        .endif
    .endif

    mov rsi,file    ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    .return(rdx)

strfcat endp

    end
