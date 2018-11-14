; TOGETBITFLAG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

togetbitflag proc uses ebx tobj:ptr S_TOBJ, count, flag
    mov ebx,flag
    mov eax,count
    mov ecx,eax
    dec eax
    shl eax,4
    add eax,tobj
    mov edx,eax
    xor eax,eax
    .while  ecx
        .if bx & [edx]
            or al,1
        .endif
        shl eax,1
        sub edx,SIZE S_TOBJ
        dec ecx
    .endw
    shr eax,1
    ret
togetbitflag endp

    END
