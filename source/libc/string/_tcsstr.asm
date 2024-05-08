; _TCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

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

                mov _tal,[rbx]
                repne _tscasb
                mov _tal,0

                .break .ifnz
                .if len

                    .break .if ( rcx < len )
                     mov rdx,len
                    .repeat
                        mov _tal,[rbx+rdx*TCHAR]
                        .continue(01) .if ( _tal != [rdi+rdx*TCHAR-TCHAR] )
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
