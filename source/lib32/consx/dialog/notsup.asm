; NOTSUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include syserrls.inc

    .code

notsup proc
    ermsg(0, addr CP_ENOSYS)
    ret
notsup endp

    END
