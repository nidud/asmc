; READLINK.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include unistd.inc
include sys/syscall.inc
include errno.inc

.code

 readlink proc pathname:string_t, buf:string_t, bufsiz:size_t
    .ifsd ( sys_readlink(ldr(pathname), ldr(buf), ldr(bufsiz)) < 0 )
        neg eax
        _set_errno(eax)
    .endif
    ret
    endp

    end
