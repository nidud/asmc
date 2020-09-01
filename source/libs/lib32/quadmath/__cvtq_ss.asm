; __CVTQ_SS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_sd() - Quad to float
;

include quadmath.inc
include errno.inc

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

    .code

__cvtq_ss proc uses ebx x:ptr, q:ptr

    mov ebx,q
    mov edx,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[ebx+10]    ; get top part
    mov cx,[ebx+14]
    and ecx,Q_EXPMASK
    neg ecx
    rcr eax,1
    mov ecx,eax         ; duplicate it
    shl ecx,F_SIGBITS+1 ; get rounding bit
    mov cx,[ebx+14]     ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [ebx+6] == 0
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr (F_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,edx         ; mask off bottom bits
    mov ebx,ecx         ; save exponent and sign
    and cx,0x7FFF       ; if number not 0
    .ifnz
        .if cx == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl bx,1
            rcr eax,1
        .else
            add cx,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor eax,eax
                _set_errno(ERANGE)
            .else
                .ifs cx >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl bx,1
                    rcr eax,1
                    _set_errno(ERANGE)
                .else
                    shl eax,1
                    shrd eax,ecx,8
                    shl bx,1
                    rcr eax,1
                    .ifs !cx && eax < DDFLT_MIN
                        _set_errno(ERANGE)
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov ecx,eax
    mov eax,x
    mov [eax],ecx
    .if eax == q
        xor ecx,ecx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
    .endif
    ret

__cvtq_ss endp

    end
