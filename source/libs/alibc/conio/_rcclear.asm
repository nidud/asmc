; _RCCLEAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcclear proc rc:TRECT, p:PCHAR_INFO, ci:CHAR_INFO

    .if ( dx )

        shr     edi,16
        movzx   eax,dil
        shr     edi,8
        mul     dil
        mov     ecx,eax
        mov     rdi,rsi
        mov     eax,edx
        rep     stosd

    .else

        mov     eax,edi
        mov     ax,0
        shr     edx,16

        _rcputa(edi, eax, rsi, dx )
    .endif
    ret

_rcclear endp

    end
