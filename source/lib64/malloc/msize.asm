
include cruntime.inc
include malloc.inc
include mtdll.inc
include winheap.inc
include windows.inc
include dbgint.inc
include internal.inc

    .code

_msize_base proc pblock:ptr

    local retval:size_t

    .repeat

        ;; validation section
        _VALIDATE_RETURN(rcx, EINVAL, -1)

        HeapSize(_crtheap, 0, pblock)

    .until 1
    ret

_msize_base endp

    end

