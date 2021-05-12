; SIGNAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include signal.inc

    .data
    sig_table sigfunc_t NSIG dup(0)

    .code

raise proc frame index:SINT

  local sigp:sigfunc_t

    lea rax,sig_table
    mov rax,[rax+rcx*8]
    .if rax
        mov sigp,rax
        sigp(ecx)
    .endif
    ret

raise endp

signal proc frame index:SINT, func:sigfunc_t

    lea r8,sig_table
    mov rax,[r8+rcx*8]
    mov [r8+rcx*8],rdx
    ret

signal endp

    end
