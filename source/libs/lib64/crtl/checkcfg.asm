
_VCRT_ALLOW_INTERNALS equ 1

include vcruntime_internal.inc

CALLBACK(GUARDCF_CHECK_ROUTINE, :uintptr_t)

extern __guard_check_icall_fptr:GUARDCF_CHECK_ROUTINE

    .code

_guard_check_icall proc Target:uintptr_t

    __guard_check_icall_fptr(rcx)
    ret

_guard_check_icall endp

    end
