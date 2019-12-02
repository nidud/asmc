; NOTSUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include errno.inc

    .code

notsup proc

    ermsg(0, _sys_errlist[ENOSYS*4])
    ret

notsup endp

    END
