; BSEARCH_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc

    .code

bsearch_s proc frame uses rsi rdi rbx r12 r13 r14 key:ptr, base:ptr, num:size_t,
        _width:size_t, compare:_PtFuncCompare_s, context:ptr

    .repeat

        ;; validation section

        mov rax,compare
        .if ( rax == NULL || ( rdx == NULL && r8 != 0 ) || r9 == 0 )

            mov errno,EINVAL
            xor eax,eax
            .break
        .endif

        ;; We allow a NULL key here because it breaks some older code and
        ;; because we do not dereference this ourselves so we can't be sure that
        ;; it's a problem for the comparison function

        mov rsi,rdx
        lea rax,[r8-1]
        mul r9
        lea rdi,[rax+rsi]
        mov r12,r8
        mov r14,r9

        .while ( rsi <= rdi )

            mov rbx,r12
            shr rbx,1
            .if rbx
                mov r13,rsi
                mov rax,rbx
                .if !(r12b & 1)
                    dec rax
                .endif
                mul r14
                add r13,rax
                .ifd !compare(context, key, r13)
                    mov rax,r13
                    .break(1)
                .elseif sdword ptr eax < 0
                    mov rdi,r13
                    sub rdi,r14
                    .if r12b & 1
                        mov r12,rbx
                    .else
                        lea r12,[rbx-1]
                    .endif
                .else
                    lea rsi,[r13+r14]
                    mov r12,rbx
                .endif
            .elseif r12
                .ifd compare(context, key, rsi)
                    xor eax,eax
                .else
                    mov rax,rsi
                .endif
                .break(1)
            .else
                .break
            .endif
        .endw
        xor eax,eax
    .until 1
    ret

bsearch_s endp

    end
