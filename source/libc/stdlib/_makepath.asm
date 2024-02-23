; _MAKEPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

.code

_makepath proc uses rsi rdi rbx path:string_t, drive:string_t, dir:string_t, fname:string_t, ext:string_t

    ldr rdi,path
    ldr rsi,drive
    mov rbx,rdi
    xor eax,eax
    .if ( rsi )

        lodsb
        .if ( al )

            stosb
            mov eax,( ( 1 shl 8 ) or ':' )
            stosb
        .endif
    .endif
    ldr rsi,dir
    .if ( rsi )

        mov al,[rsi]
        .if ( al != '\' && al != '/' && ah )
ifdef __UNIX__
            mov al,'/'
else
            mov al,'\'
endif
            stosb
        .endif

        .while 1

            lodsb
            .break .if ( al == 0 )
            stosb
            mov ah,1
        .endw
    .endif
    ldr rsi,fname
    .if ( rsi )

        .if ( ah )

            mov al,[rdi-1]
            .if ( al != '\' && al != '/' )
ifdef __UNIX__
                mov al,'/'
else
                mov al,'\'
endif
                stosb
            .endif
        .endif

        .while 1

            lodsb
            .break .if ( al == 0 )
            stosb
        .endw
    .endif
    ldr rsi,ext
    .if ( rsi )

        mov al,[rsi]
        .if ( al != '.' )

            mov al,'.'
            stosb
        .endif
        .while 1

            lodsb
            .break .if ( al == 0 )
            stosb
        .endw
    .endif
    mov byte ptr [rdi],0
    mov rax,rbx
    ret

_makepath endp

    end
