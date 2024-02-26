; PCG32_RANDOM_R.ASM--
;
; unsigned pcg32_random_r( pcg32_random_t * );
;

include pcg_basic.inc

.code

pcg32_random_r proc uses rbx rng:ptr pcg32_random_t

    ldr     rcx,rng
    mov     rbx,[rcx].pcg32_random_t.state
    mov     rax,6364136223846793005
    mul     rbx
    add     rax,[rcx].pcg32_random_t.rngseq
    mov     [rcx].pcg32_random_t.state,rax

    mov     rax,rbx
    sar     rax,18
    xor     rax,rbx
    sar     rax,27

    mov     rcx,rbx
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
