; _IFDLD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include errno.inc

.code
    ;
    ; double[eax] to long double[edx]
    ;
_iFDLD proc c uses ecx ebx

    mov  ebx,edx
    mov  edx,[eax+4]
    mov  eax,[eax]
    mov  ecx,edx
    shld edx,eax,11
    shl  eax,11
    sar  ecx,20

    .repeat

        and cx,0x07FF
        .ifnz
            .if cx != 0x07FF
                add cx,0x3C00
            .else
                or ch,0x7F
                .if !(edx & 0x7FFFFFFF) && eax
                    ;
                    ; Invalid exception
                    ;
                    mov errno,ERANGE
                    or  edx,0x40000000
                .endif
            .endif
            or edx,0x80000000
            .break
        .endif
        .break .if !edx && !eax
        or cx,0x3C01
        .if !edx
            xchg edx,eax
            sub ecx,32
        .endif
        .while 1
            test edx,edx
            .break .ifs
            add eax,eax
            adc edx,edx
            dec ecx
        .endw
    .until 1
    mov [ebx],eax
    mov [ebx+4],edx
    add ecx,ecx
    rcr cx,1
    mov [ebx+8],cx
    ret
_iFDLD endp

    END
