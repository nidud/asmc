; MPROTECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
ifdef __UNIX__
include sys/syscall.inc
include sys/mman.inc
endif

.code

mprotect proc p:ptr, len:size_t, prot:int_t

ifdef __UNIX__
    .ifsd ( sys_mprotect( ldr(p), ldr(len), ldr(prot) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

mprotect endp

    end
