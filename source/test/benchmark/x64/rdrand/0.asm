
pcg_state_setseq_64 struct
    state   dq ?
    _inc    dq ?
pcg_state_setseq_64 ends

    .code

pcg32_random_r proc pcg:ptr pcg_state_setseq_64

    mov     r8,[rcx].pcg_state_setseq_64.state
    mov     rax,6364136223846793005
    mul     r8
    add     rax,[rcx].pcg_state_setseq_64._inc
    mov     [rcx].pcg_state_setseq_64.state,rax

    mov     rax,r8
    sar     rax,18
    xor     rax,r8
    sar     rax,27

    mov     rcx,r8
    shr     rcx,59
    mov     rdx,rax
    shr     rdx,cl
    neg     ecx
    and     ecx,31
    shl     eax,cl
    or      eax,edx

    ret

pcg32_random_r endp

    end

