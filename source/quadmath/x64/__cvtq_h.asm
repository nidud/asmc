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

__cvtq_h proc frame uses rbx x:ptr, q:ptr

    cmp rdx,rcx
    mov ebx,[rdx+10]
    mov cx,[rdx+14]
    .ifz
        xor eax,eax
        mov [rdx],rax
        mov [rdx+8],rax
    .endif
    shr ebx,1
    .if ecx & Q_EXPMASK
        or ebx,0x80000000
    .endif

    mov eax,ebx         ; duplicate it
    shl eax,H_SIGBITS+1 ; get rounding bit
    mov eax,0xFFE00000  ; get mask of bits to keep

    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [rdx+6] == 0
                shl eax,1
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

            .if cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && ebx > eax )
                ;
                ; overflow
                ;
                mov ebx,0x7BFF0000 shl 1
                shl dx,1
                rcr ebx,1
                _set_errno(ERANGE)
                .break

            .endif

            and  ebx,eax ; mask off bottom bits
            shl  ebx,1
            shrd ebx,ecx,H_EXPBITS
            shl  dx,1
            rcr  ebx,1

            .break .ifs cx || ebx >= HFLT_MIN

            _set_errno(ERANGE)
            .break

        .endif
        and ebx,eax
    .until 1
    mov rax,x
    shr ebx,16
    mov [rax],bx
    ret

__cvtq_h endp

    end
