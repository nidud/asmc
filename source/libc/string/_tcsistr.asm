; _TCSISTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc
include tchar.inc

    .code

_tcsistr proc uses rsi rdi rbx dst:LPTSTR, src:LPTSTR

   .new len:int_t
   .new tmp:int_t

    ldr rbx,src

    .if _tcslen(rbx)

        mov len,eax
        .if _tcslen(dst)

            mov ecx,eax
            xor eax,eax
            dec len
            mov rdi,dst
            mov rsi,_pclmap

            .repeat

                movzx edx,TCHAR ptr [rbx]
ifdef _UNICODE
                .if ( edx < 256 )
endif
                    mov dl,[rsi+rdx]
ifdef _UNICODE
                .endif
endif
                .while 1

                    movzx eax,TCHAR ptr [rdi]
                    .if ( eax == 0 )
                        .return
                    .endif
                    add rdi,TCHAR
ifdef _UNICODE
                    .if ( eax < 256 )
endif
                        mov al,[rsi+rax]
ifdef _UNICODE
                    .endif
endif
                    .break .if ( eax == edx )
                .endw

                .if ( len )

                    .if ( ecx < len )

                        .return( 0 )
                    .endif
                    mov edx,len
                    .repeat

                        movzx eax,TCHAR ptr [rbx+rdx*TCHAR]
ifdef _UNICODE
                        .if ( eax < 256 )
endif
                            mov al,[rsi+rax]
ifdef _UNICODE
                        .endif
endif
                        mov tmp,edx
                        movzx edx,TCHAR ptr [rdi+rdx*TCHAR-TCHAR]
ifdef _UNICODE
                        .if ( edx < 256 )
endif
                            mov dl,[rsi+rdx]
ifdef _UNICODE
                        .endif
endif
                        .continue(01) .if ( eax != edx )

                        mov edx,tmp
                        dec edx
                    .untilz
                .endif
                lea rax,[rdi-TCHAR]
            .until 1
        .endif
    .endif
    ret

_tcsistr endp

    end
