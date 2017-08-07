; _mulnf() - Multiply Float
;
include intn.inc
include alloc.inc

.code

_mulnf proc uses esi edi ebx dest:ptr, source:ptr, n:dword

local exp:word, h[16]
local bits, expp

    mov ecx,n
    mov edx,8
    .if ecx != 3
        shl ecx,2
        sub ecx,2
        mov edx,ecx
    .endif

    mov expp,edx
    mov ebx,dest
    mov edi,source
    lea esi,h

    mov ax,[ebx+edx]
    mov cx,[edi+edx]
    and eax,0x7FFF
    and ecx,0x7FFF
    lea eax,[eax+ecx-EXPONENT_BIAS+1]
    mov exp,ax
    mov bits,_bsrnd(ebx, n)
    _mulnd(ebx, edi, esi, n)
if 0
    .if _bsrnd(esi, n)
        mov ecx,n
        shl ecx,5
        sub ecx,bits
        add eax,ecx
    .else
endif
        .if _bsrnd(ebx, n) > bits
            sub eax,bits

    .endif
    add ax,exp
    mov edx,expp
    mov [ebx+edx],ax

    ret

_mulnf endp

    end
