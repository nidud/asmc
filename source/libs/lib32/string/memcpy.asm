; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

memmove::
memcpy::

    push    esi
    push    edi
    mov     eax,[esp+12] ; -- return value
    mov     esi,[esp+16]
    mov     ecx,[esp+20]

    mov     edi,eax
    cmp     eax,esi
    ja      @F
    rep     movsb
    pop     edi
    pop     esi
    ret
@@:
    lea     esi,[esi+ecx-1]
    lea     edi,[edi+ecx-1]
    std
    rep     movsb
    cld
    pop     edi
    pop     esi
    ret

    end
