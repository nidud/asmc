; RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcmove proc pRECT:PVOID, wp:PVOID, flag, x, y

    mov eax,pRECT
    mov eax,[eax]
    push eax
    .if rchide(eax, flag, wp)
        pop  eax
        mov  ecx,pRECT
        mov  al,byte ptr x
        mov  ah,byte ptr y
        mov  [ecx],eax
        push eax
        mov  ecx,flag
        and  ecx,not _D_ONSCR
        rcshow(eax, ecx, wp)
    .endif
    pop eax
    ret

rcmove endp

    END
