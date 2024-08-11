; CVTQ_SS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_ss() - Quad to float
;
include fltintrn.inc
include errno.inc

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

    .code

__cvtq_ss proc __ccall uses rbx s:ptr float_t, q:ptr qfloat_t

    ldr rbx,q

    mov edx,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[rbx+10]    ; get top part
    mov cx,[rbx+14]
    and ecx,Q_EXPMASK
    neg ecx
    rcr eax,1
    mov ecx,eax         ; duplicate it
    shl ecx,F_SIGBITS+1 ; get rounding bit
    mov cx,[rbx+14]     ; get exponent and sign

    .ifc                ; if have to round
        .ifz            ; - if half way between

            .if ( dword ptr [rbx+6] == 0 )

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
        .if ( cx == 0x7FFF )

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
                mov qerrno,ERANGE
                xor eax,eax

            .else

                .ifs ( cx >= 0x00FF )
                    ;
                    ; overflow
                    ;
                    mov qerrno,ERANGE
                    mov eax,0x7F800000 shl 1
                    shl bx,1
                    rcr eax,1

                .else

                    shl eax,1
                    shrd eax,ecx,8
                    shl bx,1
                    rcr eax,1

                    .ifs ( !cx && eax < DDFLT_MIN )
                        mov ebx,eax
                        mov qerrno,ERANGE
                        mov eax,ebx
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov ecx,eax

    mov rax,s
    mov [rax],ecx
    .if ( rax == q )

        xor ecx,ecx
        mov [rax+4],ecx
        mov [rax+8],ecx
        mov [rax+12],ecx
    .endif
    ret

__cvtq_ss endp

    end
