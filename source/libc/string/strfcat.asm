; STRFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strfcat proc uses rbx rsi rdi buffer:string_t, path:string_t, file:string_t

    ldr rsi,path
    ldr rbx,file
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
ifdef __UNIX__
        .if ( al != '/' )

            mov al,'/'
else
        .if ( !( al == '\' || al == '/' ) )

            mov al,'\'
endif
            stosb
        .endif
    .endif

    mov rsi,rbx ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    .return(rdx)

strfcat endp

    end
