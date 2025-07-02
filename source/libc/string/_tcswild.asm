; _TCSWILD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int strwild(char *, char *);
; int _wstrwild(wchar_t *, wchar_t *);
;
include string.inc
include ctype.inc
include tchar.inc

.code

_tcswild proc uses rsi rdi rbx wild:tstring_t, path:tstring_t

    ldr rdi,wild
    ldr rsi,path

    .while 1

        movzx eax,tchar_t ptr [rsi]
        movzx ebx,tchar_t ptr [rdi]
        add rsi,tchar_t
        add rdi,tchar_t

        .if ( ebx == '*' )

            .while 1

                movzx ebx,tchar_t ptr [rdi]
                add rdi,tchar_t

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

                movzx ebx,tchar_t ptr [rdi]
                add rdi,tchar_t
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

_tcswild endp

    end
