; _TSTRSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcsstr proc uses rdi rbx dst:LPTSTR, src:LPTSTR

   .new len:size_t

    ldr rbx,src

    .if _tcslen(rbx)

        mov len,rax
        .if _tcslen(dst)

            mov rcx,rax
            xor eax,eax
            dec len
            mov rdi,dst

            .repeat

                mov __a,[rbx]
                repne .scasb
                mov __a,0

                .break .ifnz
                .if len

                    .break .if ( rcx < len )
                     mov rdx,len
                    .repeat
                        mov __a,[rbx+rdx*TCHAR]
                        .continue(01) .if ( __a != [rdi+rdx*TCHAR-TCHAR] )
                        dec rdx
                    .untilz
                .endif
                lea rax,[rdi-TCHAR]
            .until 1
        .endif
    .endif
    ret

_tcsstr endp

    end