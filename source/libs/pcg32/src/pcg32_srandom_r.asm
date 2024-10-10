; PCG32_SRANDOM_R.ASM--
;
; unsigned pcg32_srandom_r( pcg32_random_t *, unsigned __int64, unsigned __int64 );
;

include pcg_basic.inc

.code

pcg32_srandom_r proc uses rbx rng:ptr pcg32_random_t, initstate:uint64_t, initseq:uint64_t

    ldr rbx,rng
    xor eax,eax

ifdef _WIN64
    ldr rcx,initseq
    add rcx,rcx
    or  rcx,1
    mov [rbx].pcg32_random_t.rngseq,rcx
    mov [rbx].pcg32_random_t.state,rax
else
    mov dword ptr [rbx].pcg32_random_t.state[0],eax
    mov dword ptr [rbx].pcg32_random_t.state[4],eax
    mov eax,dword ptr initseq
    mov edx,dword ptr initseq[4]
    add eax,eax
    adc edx,edx
    or  eax,1
    mov dword ptr [rbx].pcg32_random_t.rngseq[0],eax
    mov dword ptr [rbx].pcg32_random_t.rngseq[4],edx
endif
    pcg32_random_r(rbx)
    add [rbx].pcg32_random_t.state,initstate
    pcg32_random_r(rbx)
    ret

pcg32_srandom_r endp

    end
