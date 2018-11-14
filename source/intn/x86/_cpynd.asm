; _CPYND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cpynd() - Copy
;
include intn.inc

.code

_cpynd proc uses esi edi dst:ptr, src:ptr, n:dword

    mov edi,dst
    mov esi,src
    mov ecx,n
    mov eax,edi
    rep movsd
    ret

_cpynd endp

    end
