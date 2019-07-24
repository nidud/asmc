; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include strlib.inc

    .code

qsort proc uses rsi rdi rbx p:PVOID, n:SIZE_T, w:SIZE_T, compare:LPQSORTCMD

  local stack_level

    mov rax,n
    .if rax > 1

        dec rax
        mul w
        mov rsi,p
        lea rdi,[rsi+rax]
        mov stack_level,0

        .while 1

            mov rcx,w
            lea rax,[rdi+rcx]   ; middle from (hi - lo) / 2
            sub rax,rsi
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif

            sub rsp,0x20

            lea rbx,[rsi+rax]

            .ifsd compare(rsi, rbx) > 0
                memxchg(rsi, rbx, w)
            .endif
            .ifsd compare(rsi, rdi) > 0
                memxchg(rsi, rdi, w)
            .endif
            .ifsd compare(rbx, rdi) > 0
                memxchg(rbx, rdi, w)
            .endif

            mov p,rsi
            mov n,rdi

            .while 1

                add p,w
                .if p < rdi

                    .continue .ifsd compare(p, rbx) <= 0
                .endif

                .while 1

                    sub n,w

                    .break .if n <= rbx
                    .break .ifsd compare(n, rbx) <= 0
                .endw

                mov rcx,n
                mov rax,p
                .break .if rcx < rax
                memxchg(rcx, rax, w)

                .if rbx == n

                    mov rbx,p
                .endif
            .endw

            add n,w

            .while 1

                sub n,w

                .break .if n <= rsi
                .break .ifd compare(n, rbx)
            .endw

            add rsp,0x20

            mov rdx,p
            mov rax,n
            sub rax,rsi
            mov rcx,rdi
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,n

                .if rdx < rdi

                    push rdx
                    push rdi
                    inc stack_level
                .endif

                .if rsi < rcx

                    mov rdi,rcx
                    .continue
                .endif
            .else
                mov rcx,n

                .if rsi < rcx

                    push rsi
                    push rcx
                    inc stack_level
                .endif

                .if rdx < rdi

                    mov rsi,rdx
                    .continue
                .endif
            .endif

            .break .if !stack_level

            dec stack_level
            pop rdi
            pop rsi
        .endw
    .endif
    ret

qsort endp

    end
