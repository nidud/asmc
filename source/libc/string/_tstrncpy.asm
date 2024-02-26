; _TSTRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcsncpy proc uses rdi rbx dst:LPTSTR, src:LPTSTR, count:size_t

    ldr     rdi,dst
    ldr     rcx,count
    ldr     rdx,src
    mov     rbx,rdi
.0:
    test    ecx,ecx
    jz      .1
    dec     ecx
    mov     __a,[rdx]
    mov     [rdi],__a
    add     rdx,TCHAR
    add     rdi,TCHAR
    test    __a,__a
    jnz     .0
    rep     stosb
.1:
    mov     rax,rbx
    ret

_tcsncpy endp

    end

