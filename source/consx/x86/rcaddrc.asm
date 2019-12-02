; RCADDRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

rcaddrc proc uses ebx result:PVOID, r1, r2

    mov eax,r2
    add ax,word ptr r1
    mov ebx,result
    mov [ebx],eax
    ret

rcaddrc endp

    END