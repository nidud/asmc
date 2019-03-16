; _WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

.code

_write proc uses rdi rsi rbx r12 h:SINT, b:PVOID, l:UINT

  local result:UINT, count:UINT, lb[1026]:SBYTE

    mov eax,r8d ; l
    mov ebx,ecx ; h

    .repeat

        .break .if !eax

        .if ecx >= _NFILE_

            xor eax,eax
            mov _doserrno,eax
            mov errno,EBADF
            dec rax
            .break
        .endif

        lea rax,_osfile
        mov r12b,[rax+rcx]

        .if r12b & FH_APPEND
            _lseek( ecx, 0, SEEK_END )
        .endif

        xor eax,eax
        mov result,eax
        mov count,eax

        .if r12b & FH_TEXT

            mov rsi,b
            .repeat

                mov rax,rsi
                sub rax,b
                .break .if eax >= l

                lea rdi,lb
                .while 1
                    lea rdx,lb
                    mov rax,rdi
                    sub rax,rdx
                    .break .if eax >= 1024
                    mov rax,rsi
                    sub rax,b
                    .break .if eax >= l
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
            .until rax < rdx
        .else
            .break .if oswrite(ebx, b, l)
            inc result
        .endif

        mov eax,count
        .if !eax
            .if eax == result
                .if _doserrno == 5 ; access denied
                    mov errno,EBADF
                .endif
            .else
                .if r12b & FH_DEVICE
                    mov rbx,b
                    .break .if byte ptr [rbx] == 26
                .endif
                mov errno,ENOSPC
                mov _doserrno,eax
            .endif
            dec rax
        .endif
    .until 1
    ret

_write endp

    end
