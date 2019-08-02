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

    option win64:rsp nosave noauto

__cvtq_ss proc x:ptr, q:ptr

    mov r10,rcx
    mov rcx,[rdx]
    mov rax,[rdx+8]
    .if rdx == r10
        xor r8d,r8d
        mov [rdx],r8
        mov [rdx+8],r8
    .endif
    shld rdx,rax,16
    shrd rcx,rax,16
    shr  rax,16

    mov r9d,0xFFFFFF00  ; get mask of bits to keep
    mov r8w,dx
    and r8d,Q_EXPMASK
    neg r8d
    rcr eax,1
    mov r8d,eax         ; duplicate it
    shl r8d,25          ; get rounding bit
    mov r8w,dx          ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if ecx == 0
                shl r9d,1
            .endif
        .endif
        add eax,0x0100
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc r8w
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,r9d         ; mask off bottom bits
    mov r9d,r8d         ; save exponent and sign
    and r8w,0x7FFF      ; if number not 0
    .ifnz
        .if r8w == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl r9w,1
            rcr eax,1
        .else
            add r8w,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor eax,eax
                _set_errno(ERANGE)
            .else
                .ifs r8w >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl r9w,1
                    rcr eax,1
                    _set_errno(ERANGE)
                .else
                    shl eax,1
                    shrd eax,r8d,8
                    shl r9w,1
                    rcr eax,1
                    .ifs !r8w && eax < DDFLT_MIN
                        _set_errno(ERANGE)
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov [r10],eax
    mov rax,r10
    ret

__cvtq_ss endp

    end
