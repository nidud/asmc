; CVTQSS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvtqss() - Quad to float
;
include quadmath.inc

define DDFLT_MAX 0x7F7FFFFF
define DDFLT_MIN 0x00800000

    .code

cvtqss proc q:real16

ifdef _WIN64

    movq rcx,xmm0
    movhlps xmm0,xmm0
    movq rax,xmm0
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
                mov qerrno,ERANGE
            .else
                .ifs r8w >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl r9w,1
                    rcr eax,1
                    mov qerrno,ERANGE
                .else
                    shl eax,1
                    shrd eax,r8d,8
                    shl r9w,1
                    rcr eax,1
                    .ifs !r8w && eax < DDFLT_MIN
                        mov qerrno,ERANGE
                    .endif
                .endif
            .endif
        .endif
    .endif
    movd xmm0,eax
else
    int 3
endif
    ret
cvtqss endp

    end
