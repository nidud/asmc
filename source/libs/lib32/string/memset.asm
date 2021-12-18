; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

memset::

    mov     edx,edi
    mov     edi,[esp+4]
    mov     eax,[esp+8]
    mov     ecx,[esp+12]
    rep     stosb
    mov     edi,edx
    mov     eax,[esp+4]
    ret

    end
