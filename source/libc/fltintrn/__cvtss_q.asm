; __CVTSS_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc
include errno.inc

    .code

__cvtss_q proc __ccall q:ptr qfloat_t, f:ptr float_t

    ldr rax,q
    ldr rdx,f

    mov edx,[rdx]
    mov ecx,edx     ; get exponent and sign
    shl edx,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent

    .if cl
        .if ( cl != 0xFF )
            add cx,0x3FFF-0x7F
        .else
            or ch,0xFF
            .if !( edx & 0x7FFFFFFF )

                ; Invalid exception

                or edx,0x40000000 ; QNaN
                mov qerrno,EDOM
            .endif
        .endif
        ;or edx,0x80000000

    .elseif edx

        or cx,0x3FFF-0x7F+1 ; set exponent
        .while 1

            ; normalize number

            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif

    add ecx,ecx
    rcr cx,1
    mov [rax+14],cx
    shl edx,1
    mov [rax+10],edx
    xor edx,edx
    mov [rax],edx
    mov [rax+4],edx
    mov [eax+8],dx
    ret

__cvtss_q endp

    end
