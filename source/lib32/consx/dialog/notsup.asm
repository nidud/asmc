include consx.inc
include syserrls.inc

    .code

notsup proc
    ermsg(0, addr CP_ENOSYS)
    ret
notsup endp

    END
