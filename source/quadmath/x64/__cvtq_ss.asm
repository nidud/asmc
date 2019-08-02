; __CVTQ_SS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_ss() - Quad to float
;

include quadmath.inc
include errno.inc

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

    .code

__cvtq_ss proc frame uses rbx x:ptr, q:ptr

    cmp rdx,rcx
    mov rcx,[rdx]
    mov rbx,[rdx+8]
    .ifz
        xor eax,eax
        mov [rdx],rax
        mov [rdx+8],rax
    .endif
    shld rdx,rbx,16
    shrd rcx,rbx,16
    shr  rbx,16

    mov ax,dx
    and eax,Q_EXPMASK
    neg eax
    rcr ebx,1
    mov eax,ebx         ; duplicate it
    shl eax,25          ; get rounding bit
    mov eax,0xFFFFFF00  ; get mask of bits to keep
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if ecx == 0
                shl eax,1
            .endif
        .endif
        add ebx,0x0100
        .ifc            ; - if exponent needs adjusting
            mov ebx,0x80000000
            inc dx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and ebx,eax         ; mask off bottom bits
    mov eax,edx         ; save exponent and sign
    and dx,0x7FFF       ; if number not 0
    .ifnz
        .if dx == 0x7FFF
            shl ebx,1   ; infinity or NaN
            shr ebx,8
            or  ebx,0xFF000000
            shl ax,1
            rcr ebx,1
        .else
            add dx,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor ebx,ebx
                _set_errno(ERANGE)
            .else
                .ifs dx >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov ebx,0x7F800000 shl 1
                    shl ax,1
                    rcr ebx,1
                    _set_errno(ERANGE)
                .else
                    shl  ebx,1
                    shrd ebx,edx,8
                    shl  ax,1
                    rcr  ebx,1
                    .ifs !dx && ebx < DDFLT_MIN
                        _set_errno(ERANGE)
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov rax,x
    mov [rax],ebx
    ret

__cvtq_ss endp

    end
