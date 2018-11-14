; SIGNAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include signal.inc

    .data
    sig_table dq NSIG dup(0)

    .code

    option win64:nosave

raise proc index:UINT

    lea r8,sig_table
    mov rax,[r8+rcx*8]
    .if rax
        call rax
    .endif
    ret

raise endp

    option win64:rsp noauto

signal proc index:UINT, func:ptr proc

    lea r8,sig_table
    mov rax,[r8+rcx*8]
    mov [r8+rcx*8],rdx
    ret

signal endp

    end
