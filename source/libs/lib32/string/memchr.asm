; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

memchr::

    mov     edx,edi
    mov     ecx,[esp+12]
    mov     edi,[esp+4]
    mov     eax,[esp+8]
    repnz   scasb
    lea     eax,[edi-1]
    mov     edi,edx
ifdef __SSE__
    cmovnz  eax,ecx
    ret
else
    jnz     @F
    ret
@@:
    mov     eax,ecx
    ret
endif

    end

