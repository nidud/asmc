; _SCCENTERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_sccenterA proc uses rbx x:BYTE, y:BYTE, lsize:BYTE, string:LPSTR

    xor eax,eax
    .while ( byte ptr [rcx+rax])
        inc eax
    .endw
    movzx ebx,dl
    .ifd ( eax > ebx )

        add rcx,rax
        sub rcx,rbx
    .else

        sub ebx,eax
        shr ebx,1
        add dil,bl
    .endif
    _scputsA(dil, sil, rcx)
    ret

_sccenterA endp

    end
