; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

qsort proc uses rbx p:ptr, n:size_t, w:size_t, compare:LPQSORTCMD

   .new level:int_t = 0
   .new a:ptr
   .new b:ptr
   .new x:ptr
   .new y:ptr

    ldr rcx,p
    ldr rdx,n

    .if ( edx > 1 )

        lea eax,[rdx-1]
        mul w
        mov a,rcx
        lea rax,[rcx+rax]
        mov b,rax

        .while 1

            mov rcx,w
            mov rax,b
            add rax,rcx ; middle from (hi - lo) / 2
            sub rax,a
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif
ifdef _WIN64
            sub rsp,0x20
endif
            mov rbx,a
            add rbx,rax

            .ifsd compare(a, rbx) > 0
                memxchg(a, rbx, w)
            .endif
            .ifsd compare(a, b) > 0
                memxchg(a, b, w)
            .endif
            .ifsd compare(rbx, b) > 0
                memxchg(rbx, b, w)
            .endif

            mov x,a
            mov y,b

            .while 1

                mov rcx,w
                add x,rcx
                .if x < b

                    .continue .ifsd compare(x, rbx) <= 0
                .endif

                .while 1

                    mov rcx,w
                    sub y,rcx

                    .break .if y <= rbx
                    .break .ifsd compare(y, rbx) <= 0
                .endw

                mov rcx,y
                mov rax,x
                .break .if rcx < rax
                memxchg(rcx, rax, w)

                .if rbx == y

                    mov rbx,x
                .endif
            .endw

            mov rcx,w
            add y,rcx

            .while 1

                mov rcx,w
                sub y,rcx

                .break .if y <= a
                .break .ifd compare(y, rbx)
            .endw

ifdef _WIN64
            add rsp,0x20
endif
            mov rdx,x
            mov rax,y
            sub rax,a
            mov rcx,b
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,y

                .if rdx < b

                    push rdx
                    push b
                    inc level
                .endif

                .if a < rcx

                    mov b,rcx
                    .continue
                .endif
            .else
                mov rcx,y

                .if a < rcx

                    push a
                    push rcx
                    inc level
                .endif

                .if rdx < b

                    mov a,rdx
                    .continue
                .endif
            .endif

            .break .if !level

            dec level
            pop b
            pop a
        .endw
    .endif
    ret

qsort endp

    end
