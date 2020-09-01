_VCRT_ALLOW_INTERNALS equ 1

include vcruntime_internal.inc
include setjmp.inc
include stdlib.inc

__longjmp_internal proto :jmp_buf, :int_t
__except_validate_jump_buffer proto :jmp_buf

    .code

longjmp proc JumpBuffer:jmp_buf, ReturnValue:int_t

    __except_validate_jump_buffer(rcx)
    __longjmp_internal(JumpBuffer, ReturnValue)
    ret

longjmp endp

    option win64:rsp noauto
    assume rcx:ptr _JUMP_BUFFER

_setjmp proc JumpBuffer:jmp_buf

    mov [rcx]._Rbp,rbp
    mov [rcx]._Rbx,rbx
    mov [rcx]._Rdi,rdi
    mov [rcx]._Rsi,rsi
    mov [rcx]._R12,r12
    mov [rcx]._R13,r13
    mov [rcx]._R14,r14
    mov [rcx]._R15,r15
    mov [rcx]._Rsp,rsp
    mov rax,[rsp]
    mov [rcx]._Rip,rax
    xor rax,rax
    ret

_setjmp endp

__longjmp_internal proc JumpBuffer:jmp_buf, retval:int_t

    mov rbp,[rcx]._Rbp
    mov rbx,[rcx]._Rbx
    mov rdi,[rcx]._Rdi
    mov rsi,[rcx]._Rsi
    mov r12,[rcx]._R12
    mov r13,[rcx]._R13
    mov r14,[rcx]._R14
    mov r15,[rcx]._R15
    mov rsp,[rcx]._Rsp
    mov rax,[rcx]._Rip
    mov [rsp],rax
    mov rax,rdx
    ret

__longjmp_internal endp

    end
