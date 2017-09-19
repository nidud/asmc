include consx.inc
include alloc.inc

    .code

rcalloc proc rc:S_RECT, shade:UINT

    malloc(rcmemsize(rc, shade))
    ret

rcalloc endp

    END
