include Windows.inc

CALLBACK(GUARDCF_CHECK_ROUTINE, :uintptr_t)

    .code

_guard_check_icall_nop proc Target:uintptr_t

    ret

_guard_check_icall_nop endp

option dotname

.00cfg SEGMENT ALIGN(8) 'CONST'
__guard_check_icall_fptr PVOID _guard_check_icall_nop
.00cfg ENDS

    .code

_guard_icall_checks_enforced proc

    lea     rcx,__guard_check_icall_fptr
    mov     rax,[rcx]
    lea     rcx,_guard_check_icall_nop
    cmp     rax,rcx
    mov     eax,0
    setne   al
    ret

_guard_icall_checks_enforced endp

    end
