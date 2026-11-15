; MMAP.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/syscall.inc
include sys/mman.inc

.code

 mmap proc p:ptr, length:size_t, prot:int_t, flags:int_t, fd:int_t, offs:size_t
    .if ( sys_mmap( ldr(p), ldr(length), ldr(prot), ldr(flags), ldr(fd), ldr(offs) ) > -4096 )
        neg eax
        _set_errno( eax )
    .endif
    ret
    endp

    end
