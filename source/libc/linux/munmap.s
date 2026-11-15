; MUNMAP.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/syscall.inc
include sys/mman.inc

.code

 munmap proc p:ptr, len:size_t
    .ifsd ( sys_munmap( ldr(p), ldr(len) ) < 0 )
        neg eax
        _set_errno( eax )
    .endif
    ret
    endp

    end
