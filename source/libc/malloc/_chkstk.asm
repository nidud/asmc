; _CHKSTK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include libc.inc

_PAGESIZE_ equ 0x1000 ; one page

; Called by the compiler when you have more than one page of
; local variables in your function. For x86 compilers, _chkstk
; Routine is called when the local variables exceed 4K bytes;
; for x64 compilers it is 8K.

    .code

_chkstk::
___chkstk_ms::
_alloca_probe::

    push    rcx
ifdef _WIN64
    push    rax
    lea     rcx,[rsp+24]
    xchg    rcx,rsp
    cmp     eax,_PAGESIZE_
    jb      done
next:
    sub     rax,_PAGESIZE_
    sub     rsp,_PAGESIZE_
    test    [rsp],rcx
    cmp     eax,_PAGESIZE_
    ja      next
done:
    sub     rsp,rax
    test    [rsp],rcx
    mov     rsp,rcx
    pop     rax
    pop     rcx
else
    lea     ecx,[esp+4]
    sub     ecx,eax
    sbb     eax,eax
    not     eax
    and     ecx,eax
    mov     eax,esp
    and     eax,not (_PAGESIZE_ - 1)
cs10:
    cmp     ecx,eax
    jb      cs20
    mov     eax,ecx
    pop     ecx
    xchg    esp,eax
    mov     eax,[eax]
    mov     [esp],eax
    ret
cs20:
    sub     eax,_PAGESIZE_
    test    [eax],eax
    jmp     cs10
endif
    ret

    end
