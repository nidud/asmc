; _READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

ER_ACCESS_DENIED equ 5
ER_BROKEN_PIPE   equ 109

    .data
    pipech  db _NFILE_ dup(10)
    peekchr db 0

    .code

_read proc uses rsi rdi rbx r12 r13 h:SINT, b:PVOID, count:SIZE_T

  local NumberOfBytesRead:qword

    xor esi,esi         ; nothing read yet
    mov rdi,rdx
    mov rbx,rcx

    xor eax,eax         ; nothing to read or at EOF

    .repeat

        .break .if !r8

        lea r13,_osfile
        add r13,rcx
        mov cl,[r13]
        .break .if cl & FH_EOF

        mov _doserrno,eax

        .if cl & FH_PIPE or FH_DEVICE

            lea rcx,pipech
            mov al,[rcx+rbx]
            .if al != 10

                stosb
                mov BYTE PTR [rcx+rbx],10
                inc rsi
                dec r8
            .endif
        .endif

        lea rcx,_osfhnd
        mov rcx,[rcx+rbx*8]
        .if !ReadFile(rcx, rdi, r8d, &NumberOfBytesRead, 0)

            osmaperr()

            xor eax,eax
            mov edx,_doserrno
            .break .if edx == ER_BROKEN_PIPE

            dec eax
            .break .if edx != ER_ACCESS_DENIED
            mov errno,EBADF
            .break
        .endif

        add rsi,NumberOfBytesRead
        mov rdi,b
        mov al,[r13]

        .if al & FH_TEXT

            and al,not FH_CRLF
            .if byte ptr [rdi] == 10

                or al,FH_CRLF
            .endif
            mov [r13],al
            mov r12,rdi

            .while 1

                mov rax,b
                add rax,rsi
                .break .if rdi >= rax

                mov al,[rdi]
                .if al == 26

                    .break .if BYTE PTR[r13] & FH_DEVICE
                    or BYTE PTR [r13],FH_EOF
                    .break
                .endif

                .if al != 13

                    mov [r12],al
                    inc rdi
                    inc r12
                    .continue
                .endif

                mov rax,b
                lea rax,[rax+rsi-1]
                .if rdi < rax

                    .if byte ptr [rdi+1] == 10

                        add rdi,2
                        mov al,10
                    .else

                        mov al,[rdi]
                        inc rdi
                    .endif
                    mov [r12],al
                    inc r12
                    .continue
                .endif

                inc rdi
                lea rcx,_osfhnd
                mov rcx,[rcx+rbx*8]

                .if !ReadFile(rcx, &peekchr, 1, &NumberOfBytesRead, 0) || !NumberOfBytesRead

                    mov al,13

                .elseif BYTE PTR [r13] & FH_DEVICE or FH_PIPE

                    mov al,10
                    .if peekchr != al

                        mov al,peekchr
                        lea rcx,pipech
                        mov [rcx+rbx],al
                        mov al,13
                    .endif
                .else

                    mov al,10
                    .if b != r12 || peekchr != al

                        _lseek(ebx, -1, SEEK_CUR)
                        mov al,13
                        .continue .if peekchr == 10
                    .endif
                .endif
                mov [r12],al
                inc r12
            .endw
            mov rax,r12
            sub rax,b
        .else
            mov rax,rsi
        .endif
    .until 1
    ret

_read endp

    end
