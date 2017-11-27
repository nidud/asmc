; _pownd() - returns the base to the exponent power
;
include intn.inc
include malloc.inc

.code

_pownd proc uses esi edi ebx base:ptr, exponent:sdword, n:dword

local h, e

    mov eax,n
    shl eax,2
    mov e,alloca(eax)
    mov ecx,n
    mov edi,eax
    mov esi,base
    rep movsd

    mov ebx,n
    shr ebx,1
    mov esi,base
    lea edi,[esi+ebx*4] ; high product
    .if !ebx
        lea edi,h
        mov ebx,1
    .endif

    .while exponent > 1

        _mulnd(esi, e, edi, ebx)
        dec exponent
    .endw
    mov eax,esi
    ret

_pownd endp

    end
