; WCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsstr proc uses rdi rbx dst:wstring_t, src:wstring_t

   .new len:size_t

    ldr rbx,src
    .if wcslen(rbx)

        mov len,rax
        .if wcslen(dst)

            mov rcx,rax
            xor eax,eax
            dec len
            mov rdi,dst

            .repeat

                mov ax,[rbx]
                repne scasw
                mov ax,0

                .break .ifnz

                .if len

                    .break .if ( rcx < len )

                    mov rdx,len
                    .repeat

                        mov ax,[rbx+rdx*2]

                        .continue(01) .if ( ax != [rdi+rdx*2-2] )
                        sub rdx,1
                    .untilz
                .endif
                lea rax,[rdi-2]
            .until 1
        .endif
    .endif
    ret

wcsstr endp

    end
