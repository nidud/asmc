; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

memxchg proc private a:ptr, b:ptr, size:size_t

    .while rdx >= 8

        sub rdx,8
        mov rax,[rdi+rdx]
        mov rcx,[rsi+rdx]
        mov [rdi+rdx],rcx
        mov [rsi+rdx],rax
    .endw

    .while rdx

        dec rdx
        mov al,[rdi+rdx]
        mov cl,[rsi+rdx]
        mov [rdi+rdx],cl
        mov [rsi+rdx],al
    .endw
    mov rax,rdi
    ret

memxchg endp

qsort proc uses rbx r12 r13 r14 r15 p:ptr, n:size_t, _w:size_t, lpCompare:LPQSORTCMD

   .new stack_level:int_t = 0
   .new compare:LPQSORTCMD = lpCompare
   .new w:size_t = _w

    mov r14,p
    mov r15,n

    mov rax,r15
    .if rax > 1

        dec rax
        mul w
        mov r12,r14
        lea r13,[r12+rax]

        .while 1

            mov rcx,w
            lea rax,[r13+rcx]   ; middle from (hi - lo) / 2
            sub rax,r12
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif

            lea rbx,[r12+rax]

            .ifsd compare(r12, rbx) > 0
                memxchg(r12, rbx, w)
            .endif
            .ifsd compare(r12, r13) > 0
                memxchg(r12, r13, w)
            .endif
            .ifsd compare(rbx, r13) > 0
                memxchg(rbx, r13, w)
            .endif

            mov r14,r12
            mov r15,r13

            .while 1

                add r14,w
                .if r14 < r13

                    .continue .ifsd compare(r14, rbx) <= 0
                .endif

                .while 1

                    sub r15,w

                    .break .if r15 <= rbx
                    .break .ifsd compare(r15, rbx) <= 0
                .endw
                .break .if r15 < r14

                 memxchg(r15, r14, w)

                .if rbx == r15

                    mov rbx,r14
                .endif
            .endw

            add r15,w

            .while 1

                sub r15,w

                .break .if r15 <= r12
                .break .ifd compare(r15, rbx)
            .endw

            mov rdx,r14
            mov rax,r15
            sub rax,r12
            mov rcx,r13
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,r15
                .if rdx < r13

                    push rdx
                    push r13
                    inc stack_level
                .endif

                .if r12 < rcx

                    mov r13,rcx
                    .continue
                .endif
            .else
                mov rcx,r15
                .if r12 < rcx

                    push r12
                    push rcx
                    inc stack_level
                .endif

                .if rdx < r13

                    mov r12,rdx
                    .continue
                .endif
            .endif

            .break .if !stack_level

            dec stack_level
            pop r13
            pop r12
        .endw
    .endif
    ret

qsort endp

    end
