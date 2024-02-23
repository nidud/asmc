; LLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.code

lldiv proc p:ptr _lldiv_t, x:int64_t, y:int64_t

ifdef _WIN64
    ldr     rcx,p
    ldr     rax,x
    ldr     r8,y
    cqo
    idiv    r8
    mov     [rcx]._lldiv_t.quot,rax
    mov     [rcx]._lldiv_t.rem,rdx
    mov     rax,rcx
else
    push    ebx
    push    edi
    alldiv(x, y)
    mov     edi,p
    mov     dword ptr [edi]._lldiv_t.quot[0],eax
    mov     dword ptr [edi]._lldiv_t.quot[4],edx
    mov     dword ptr [edi]._lldiv_t.rem[0],ebx
    mov     dword ptr [edi]._lldiv_t.rem[4],ecx
    mov     eax,edi
    pop     edi
    pop     ebx
endif
    ret

lldiv endp

    end
