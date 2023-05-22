; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc

    .code

qsort proc uses rsi rdi rbx p:ptr, n:size_t, w:size_t, compare:LPQSORTCMD

   .new level:int_t = 0

    ldr rcx,p
    ldr rdx,n

    .if ( edx > 1 )

        lea eax,[rdx-1]
        mul w
        mov rsi,rcx
        lea rdi,[rsi+rax]

        .while 1

            mov rcx,w
            lea rax,[rdi+rcx] ; middle from (hi - lo) / 2
            sub rax,rsi
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif
ifdef _WIN64
            sub rsp,0x20
endif
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

            .new _si:ptr = rsi
            .new _di:ptr = rdi

            .while 1

                mov rcx,w
                add _si,rcx
                .if _si < rdi

                    .continue .ifsd compare(_si, rbx) <= 0
                .endif

                .while 1

                    mov rcx,w
                    sub _di,rcx

                    .break .if _di <= rbx
                    .break .ifsd compare(_di, rbx) <= 0
                .endw

                mov rcx,_di
                mov rax,_si
                .break .if rcx < rax
                memxchg(rcx, rax, w)

                .if rbx == _di

                    mov rbx,_si
                .endif
            .endw

            mov rcx,w
            add _di,rcx

            .while 1

                mov rcx,w
                sub _di,rcx

                .break .if _di <= rsi
                .break .ifd compare(_di, rbx)
            .endw

ifdef _WIN64
            add rsp,0x20
endif
            mov rdx,_si
            mov rax,_di
            sub rax,rsi
            mov rcx,rdi
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,_di

                .if rdx < rdi

                    push rdx
                    push rdi
                    inc level
                .endif

                .if rsi < rcx

                    mov rdi,rcx
                    .continue
                .endif
            .else
                mov rcx,_di

                .if rsi < rcx

                    push rsi
                    push rcx
                    inc level
                .endif

                .if rdx < rdi

                    mov rsi,rdx
                    .continue
                .endif
            .endif

            .break .if !level

            dec level
            pop rdi
            pop rsi
        .endw
    .endif
    ret

qsort endp

    end
