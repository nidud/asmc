; STRSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strstr proc uses rdi rbx dst:LPSTR, src:LPSTR

   .new len:size_t

    ldr rbx,src

    .if strlen(rbx)

        mov len,rax
        .if strlen(dst)

            mov rcx,rax
            xor eax,eax
            dec len
            mov rdi,dst

            .repeat

                mov al,[rbx]
                repne scasb
                mov al,0

                .break .ifnz
                .if len

                    .break .if ( rcx < len )
                     mov rdx,len
                    .repeat
                        mov al,[rbx+rdx]
                        .continue(01) .if ( al != [rdi+rdx-1] )
                        dec rdx
                    .untilz
                .endif
                lea rax,[rdi-1]
            .until 1
        .endif
    .endif
    ret

strstr endp

    end
