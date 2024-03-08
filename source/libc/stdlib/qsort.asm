; QSORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

define STKSIZ   (8*size_t - 2)
define swap     <memxchg>

    .code

ifdef _WIN64

qsort proc uses rbx r12 r13 r14 r15 p:ptr, n:size_t, w:size_t, compare:LPQSORTCMD

    define lo    <r12>
    define hi    <r13>
    define loguy <r14>
    define higuy <r15>

else

qsort proc uses rbx p:ptr, n:size_t, w:size_t, compare:LPQSORTCMD

   .new lo:ptr
   .new hi:ptr
   .new loguy:ptr
   .new higuy:ptr

endif

   .new stkptr:int_t = 0
   .new lostk[STKSIZ]:ptr
   .new histk[STKSIZ]:ptr

    ldr rcx,p
    ldr rdx,n

    .if ( edx > 1 )

        lea eax,[rdx-1]
        mul w
        mov lo,rcx
        lea rax,[rcx+rax]
        mov hi,rax

        .while 1

            mov rcx,w
            mov rax,hi
            add rax,rcx ; middle from (hi - lo) / 2
            sub rax,lo
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif
            mov rbx,lo
            add rbx,rax

            .ifsd compare(lo, rbx) > 0
                swap(lo, rbx, w)
            .endif
            .ifsd compare(lo, hi) > 0
                swap(lo, hi, w)
            .endif
            .ifsd compare(rbx, hi) > 0
                swap(rbx, hi, w)
            .endif

            mov loguy,lo
            mov higuy,hi

            .while 1

                mov rcx,w
                add loguy,rcx
                .if loguy < hi

                    .continue .ifsd compare(loguy, rbx) <= 0
                .endif

                .while 1

                    mov rcx,w
                    sub higuy,rcx

                    .break .if higuy <= rbx
                    .break .ifsd compare(higuy, rbx) <= 0
                .endw

                mov rcx,higuy
                mov rax,loguy
                .if rcx < rax
                    .break
                .endif
                .if rbx == rcx
                    mov rbx,rax
                .endif
                swap(rcx, rax, w)
            .endw

            add higuy,w

            .if ( rbx < higuy )

                .while 1

                    sub higuy,w

                    .break .if higuy <= rbx
                    .break .ifd compare(higuy, rbx)
                .endw
            .endif

            .if ( rbx >= higuy )

                .while 1

                    sub higuy,w

                    .break .if higuy <= lo
                    .break .ifd compare(higuy, rbx)
                .endw
            .endif

            mov rdx,loguy
            mov rax,higuy
            sub rax,lo
            mov rcx,hi
            sub rcx,rdx

            .if rax < rcx

                .if rdx < hi

                    mov ecx,stkptr
                    mov lostk[rcx*size_t],rdx
                    mov histk[rcx*size_t],hi
                    inc stkptr
                .endif

                mov rax,higuy
                .if lo < rax

                    mov hi,rax
                   .continue
                .endif
            .else

                mov rax,higuy
                .if lo < rax

                    mov ecx,stkptr
                    mov histk[rcx*size_t],rax
                    mov lostk[rcx*size_t],lo
                    inc stkptr
                .endif

                .if rdx < hi

                    mov lo,rdx
                   .continue
                .endif
            .endif
            .break .if !stkptr

            dec stkptr
            mov ecx,stkptr
            mov lo,lostk[rcx*size_t]
            mov hi,histk[rcx*size_t]
        .endw
    .endif
    ret

qsort endp

    end
