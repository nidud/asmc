_VCRT_ALLOW_INTERNALS equ 1

include vcruntime_internal.inc
include stdlib.inc
include setjmp.inc

_guard_icall_checks_enforced proto

    .code

__except_validate_context_record proc ContextRecord:PCONTEXT

    .if _guard_icall_checks_enforced()

        mov rdx,NtCurrentTeb()
        mov rcx,ContextRecord
        mov rcx,[rcx]._JUMP_BUFFER._Rsp

        .if ((rcx < [rdx].NT_TIB.StackLimit) || (rcx > [rdx].NT_TIB.StackBase))

            __fastfail(FAST_FAIL_INVALID_SET_OF_CONTEXT)
        .endif
    .endif
    ret

__except_validate_context_record endp


__except_validate_jump_buffer proc JumpBuffer:jmp_buf


    .if _guard_icall_checks_enforced()

        mov rdx,NtCurrentTeb()
        mov rcx,jmp_buf
        mov rcx,[rcx]._JUMP_BUFFER._Rsp

        .if ((rcx < [rdx].NT_TIB.StackLimit) || (rcx > [rdx].NT_TIB.StackBase))

            __fastfail(FAST_FAIL_INVALID_SET_OF_CONTEXT)
        .endif

ifndef JUMP_BUFFER_NO_FRAME
        mov rcx,jmp_buf
        .if ([rcx]._JUMP_BUFFER._Frame == 0)

            __fastfail(FAST_FAIL_INVALID_SET_OF_CONTEXT)
        .endif
endif
    .endif
    ret

__except_validate_jump_buffer endp

    end
