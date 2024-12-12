; MPROTECT.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/syscall.inc
include sys/mman.inc

.code

mprotect proc p:ptr, len:size_t, prot:int_t

    .ifsd ( sys_mprotect( ldr(p), ldr(len), ldr(prot) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

mprotect endp

    end
