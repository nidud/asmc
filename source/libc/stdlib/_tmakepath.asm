; _TMAKEPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include tchar.inc

option dotname
ifdef _UNICODE
define .lodsb <lodsw>
define .stosb <stosw>
else
define .lodsb <lodsb>
define .stosb <stosb>
endif

.code

_tmakepath proc uses rsi rdi rbx path:tstring_t, drive:tstring_t, dir:tstring_t, fname:tstring_t, ext:tstring_t

    ldr rdi,path
    ldr rsi,drive
    xor ebx,ebx
    xor eax,eax

    .if ( rsi )

        .lodsb
        .if ( eax )

           .stosb
            mov eax,':'
           .stosb
            inc ebx
        .endif
    .endif

    ldr rsi,dir
    .if ( rsi )

        movzx eax,tchar_t ptr [rsi]
        .if ( eax != '\' && eax != '/' && ebx )
ifdef __UNIX__
            mov eax,'/'
else
            mov eax,'\'
endif
           .stosb
        .endif

        .while 1

            .lodsb
            .break .if ( eax == 0 )
            .stosb
            inc ebx
        .endw
    .endif
    ldr rsi,fname
    .if ( rsi )

        .if ( ebx )

            movzx eax,tchar_t ptr [rdi-tchar_t]
            .if ( eax != '\' && eax != '/' )
ifdef __UNIX__
                mov eax,'/'
else
                mov eax,'\'
endif
               .stosb
            .endif
        .endif

        .while 1

            .lodsb
            .break .if ( eax == 0 )
            .stosb
        .endw
    .endif
    ldr rsi,ext
    .if ( rsi )

        movzx eax,tchar_t ptr [rsi]
        .if ( eax != '.' )

            mov eax,'.'
           .stosb
        .endif
        .while 1

            .lodsb
            .break .if ( eax == 0 )
            .stosb
        .endw
    .endif
    mov tchar_t ptr [rdi],0
    mov rax,path
    ret

_tmakepath endp

    end
