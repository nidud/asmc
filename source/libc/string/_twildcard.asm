; _TWILDCARD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc
include tchar.inc

.code

ifdef __UNIX__
_twildcard proc uses rbx wild:tstring_t, path:tstring_t
else
_twildcard proc uses rsi rdi rbx wild:tstring_t, path:tstring_t
endif

    ldr rdi,wild
    ldr rsi,path

    .while 1

        movzx eax,TCHAR ptr [rsi]
        movzx ebx,TCHAR ptr [rdi]
        add rsi,TCHAR
        add rdi,TCHAR

        .if ( ebx == '*' )

            .while 1

                movzx ebx,TCHAR ptr [rdi]
                add rdi,TCHAR

                .if ( ebx == 0 )

                    .return( 1 )
                .endif
                .continue .if ( ebx != '.' )

                xor edx,edx
                .while ( eax )

                    .if ( eax == ebx )

                        mov rdx,rsi
                    .endif
                    _tlodsb
                .endw

                mov rsi,rdx
                .continue( 1 ) .if rdx

                movzx ebx,TCHAR ptr [rdi]
                add rdi,TCHAR
                .continue .if ( ebx == '*' )

                or eax,ebx
                setz al
                movzx eax,al
               .return
            .endw

        .endif

        mov edx,eax
        xor eax,eax
        .if ( edx == 0 )

            test ebx,ebx
            setz al
           .break
        .endif
        .break .if ( ebx == 0 )
        .continue .if ( ebx == '?' )

        .if ( ebx == '.' )

            .continue .if ( edx == '.' )
            .break
        .endif
        .break .if ( edx == '.' )

ifndef __UNIX__
        mov rax,_pcumap
ifdef _UNICODE
        .if ( ebx < 256 )
endif
            movzx ebx,byte ptr [rax+rbx]
ifdef _UNICODE
        .endif
        .if ( edx < 256 )
endif
            movzx edx,byte ptr [rax+rdx]
ifdef _UNICODE
        .endif
endif
        xor eax,eax
endif
       .break .if ( edx != ebx )
    .endw
    ret

_twildcard endp

    end
