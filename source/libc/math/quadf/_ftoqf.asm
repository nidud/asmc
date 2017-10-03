;
; Convert float to quad float
;
include intn.inc

.code

_ftoqf proc p:ptr, f:dword

    mov eax,f       ; get float value
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
    mov edx,p
    shl eax,1
    xchg eax,edx
    mov [eax+10],edx
    xor edx,edx
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],dx
    shl ecx,1
    rcr cx,1
    mov [eax+14],cx
    ret

_ftoqf endp

    end
