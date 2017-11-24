include io.inc
include errno.inc

.code

_write proc uses rdi rsi rbx r12 h:SINT, b:PVOID, l:SIZE_T

local result:SIZE_T, count:SIZE_T, lb[1026]:SBYTE

    mov rax,r8  ; l
    mov rbx,rcx ; h

    .repeat

        .break .if !rax

        .if ecx >= _NFILE_

            xor rax,rax
            mov oserrno,eax
            mov errno,EBADF
            dec rax
            .break
        .endif

        lea rax,_osfile
        mov r12b,[rax+rcx]

        .if r12b & FH_APPEND
            _lseek( ecx, 0, SEEK_END )
        .endif

        xor rax,rax
        mov result,rax
        mov count,rax

        .if r12b & FH_TEXT

            mov rsi,b
            .repeat

                mov rax,rsi
                sub rax,b
                .break .if rax >= l

                lea rdi,lb
                .while 1
                    lea rdx,lb
                    mov rax,rdi
                    sub rax,rdx
                    .break .if rax >= 1024

                    mov rax,rsi
                    sub rax,b
                    .break .if rax >= l

                    lodsb
                    .if al == 10
                        mov byte ptr [rdi],13
                        inc rdi
                    .endif
                    stosb
                    inc count
                .endw

                lea rdx,lb
                mov r8,rdi
                sub r8,rdx
                .if !oswrite( ebx, rdx, r8 )
                    inc result
                    .break
                .endif
                lea rcx,lb
                mov rdx,rdi
                sub rdx,rcx
            .until  rax < rdx
        .else
            .break .if oswrite(ebx, b, l)
            inc result
        .endif

        mov rax,count
        .if !rax
            .if rax == result
                .if oserrno == 5 ; access denied
                    mov errno,EBADF
                .endif
            .else
                .if r12b & FH_DEVICE
                    mov rbx,b
                    .break .if byte ptr [rbx] == 26
                .endif
                mov errno,ENOSPC
                mov oserrno,0
            .endif
            dec rax
        .endif
    .until 1
    ret

_write endp

    end
