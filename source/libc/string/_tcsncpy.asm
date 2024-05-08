; _TCSNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcsncpy proc uses rdi rbx dst:LPTSTR, src:LPTSTR, count:size_t

    ldr     rdi,dst
    ldr     rcx,count
    ldr     rdx,src
    mov     rbx,rdi
.0:
    test    ecx,ecx
    jz      .1
    dec     ecx
    mov     _tal,[rdx]
    mov     [rdi],_tal
    add     rdx,TCHAR
    add     rdi,TCHAR
    test    _tal,_tal
    jnz     .0
    rep     _tstosb
.1:
    mov     rax,rbx
    ret

_tcsncpy endp

    end

