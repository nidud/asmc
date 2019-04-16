; _SCENTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scenter proc frame x:int_t, y:int_t, lsize:int_t, string:string_t

    .ifd strlen(r9) > lsize

        mov ecx,lsize
        add string,rax
        sub string,rcx

    .else

        mov ecx,eax
        mov eax,lsize
        sub eax,ecx
        shr eax,1
        add x,eax
    .endif
    _scputs(x, y, string)
    ret

_scenter endp

    end
