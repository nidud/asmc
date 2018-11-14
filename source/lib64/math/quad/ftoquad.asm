; FTOQUAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert float to quad float
;
include quadmath.inc

    .code

ftoquad proc p:ptr, f:ptr

    mov r8,rcx
    mov eax,[rdx]
    mov ecx,eax     ; get exponent and sign
    shl eax,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,0x3FFF-0x7F
        .else
            or ch,0x7F
            .if !(eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                or eax,0x40000000 ; QNaN
                mov qerrno,EDOM
            .endif
        .endif
        or eax,0x80000000
    .elseif eax
        or cx,0x3FFF-0x7F+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif

    shl eax,1
    mov [r8+10],eax
    xor eax,eax
    mov [r8],rax
    mov [r8+8],ax
    add ecx,ecx
    rcr cx,1
    mov [r8+14],cx
    mov rax,r8
    ret

ftoquad endp

    end
