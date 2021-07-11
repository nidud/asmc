; __CVTQ_H.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_h() - Quad to half
;

include quadmath.inc
include errno.inc

HFLT_MAX equ 0x7BFF
HFLT_MIN equ 0x0001

    .code

__cvtq_h proc uses rbx r12 h:ptr, q:ptr
ifdef __UNIX__
    mov r12,rdi
    mov rbx,[rsi+8]
    mov rdx,[rsi]
else
    mov r12,rcx
    mov rbx,[rdx+8]
    mov rdx,[rdx]
endif
    shld rcx,rbx,16
    rol  rdx,16
    shl  rbx,16
    shld rdx,rbx,16
    shr  rbx,32
    shr  ebx,1
    .if ecx & Q_EXPMASK
        or ebx,0x80000000
    .endif

    mov r9d,ebx         ; duplicate it
    shl r9d,H_SIGBITS+1 ; get rounding bit
    mov r9d,0xFFE00000  ; get mask of bits to keep

    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if edx == 0
                shl r9d,1
            .endif
        .endif
        add ebx,0x80000000 shr (H_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov ebx,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif

    mov edx,ecx         ; save exponent and sign
    and cx,Q_EXPMASK    ; if number not 0

    .repeat

        .ifnz
            .if cx == Q_EXPMASK
                .if ( ebx & 0x7FFFFFFF )

                    mov ebx,-1
                    .break
                .endif
                mov ebx,0x7C000000 shl 1
                shl dx,1
                rcr ebx,1
                .break
            .endif
            add cx,H_EXPBIAS-Q_EXPBIAS
            .ifs
                ;
                ; underflow
                ;
                mov ebx,0x00010000
                _set_errno(ERANGE)
                .break
            .endif

            .if cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && ebx > r9d )
                ;
                ; overflow
                ;
                mov ebx,0x7BFF0000 shl 1
                shl dx,1
                rcr ebx,1
                _set_errno(ERANGE)
                .break

            .endif

            and  ebx,r9d ; mask off bottom bits
            shl  ebx,1
            shrd ebx,ecx,H_EXPBITS
            shl  dx,1
            rcr  ebx,1

            .break .ifs cx || ebx >= HFLT_MIN

            _set_errno(ERANGE)
            .break

        .endif
        and ebx,r9d
    .until 1
    shr ebx,16
    mov [r12],bx
    mov eax,ebx
    ret

__cvtq_h endp

    end
