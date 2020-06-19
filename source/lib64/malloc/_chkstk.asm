; _CHKSTK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

_PAGESIZE_ equ 0x1000 ; one page

; Called by the compiler when you have more than one page of
; local variables in your function. For x86 compilers, _chkstk
; Routine is called when the local variables exceed 4K bytes;
; for x64 compilers it is 8K.

    .code

_chkstk::
___chkstk_ms::
_alloca_probe::

    mov rcx,rsp
    lea rsp,[rsp+8]

    .while rax >= _PAGESIZE_

        sub rax,_PAGESIZE_
        sub rsp,_PAGESIZE_
        cmp al,[rsp]
    .endw

    sub rsp,rax
    cmp al,[rsp] ; probe page
    mov rax,rsp
    mov rsp,rcx
    ret

    end
