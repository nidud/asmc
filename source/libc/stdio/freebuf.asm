; FREEBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

_freebuf proc fp:LPFILE
    ldr rcx,fp
    mov rdx,rcx
    mov eax,[rdx].FILE._flag
    .if ( eax & _IOREAD or _IOWRT or _IORW )
        .if ( eax & _IOMYBUF )
            xor eax,eax
            mov rcx,[rdx].FILE._base
            mov [rdx].FILE._ptr,rax
            mov [rdx].FILE._base,rax
            mov [rdx].FILE._flag,eax
            mov [rdx].FILE._bufsiz,eax
            mov [rdx].FILE._cnt,eax
            free( rcx )
        .endif
    .endif
    ret
    endp

    end
