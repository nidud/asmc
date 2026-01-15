; PCG32_RANDOM_R.ASM--
;
; unsigned pcg32_random_r( pcg32_random_t * );
;

include pcg_basic.inc

.code

pcg32_random_r proc uses rbx rng:ptr pcg32_random_t

ifdef _WIN64

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

else

    push    esi
    mov     esi,rng
    mov     ebx,LOW32(6364136223846793005)
    mov     ecx,HIGH32(6364136223846793005)
    mov     eax,dword ptr [esi].pcg32_random_t.state[0]
    mov     edx,dword ptr [esi].pcg32_random_t.state[4]
    mul     ecx
    mov     ecx,eax
    mov     eax,dword ptr [esi].pcg32_random_t.state[4]
    mul     ebx
    add     ecx,eax
    mov     eax,dword ptr [esi].pcg32_random_t.state[0]
    mul     ebx
    add     edx,ecx
    add     eax,dword ptr [esi].pcg32_random_t.rngseq[0]
    adc     edx,dword ptr [esi].pcg32_random_t.rngseq[4]
    mov     ebx,dword ptr [esi].pcg32_random_t.state[0]
    mov     ecx,dword ptr [esi].pcg32_random_t.state[4]
    mov     dword ptr [esi].pcg32_random_t.state[0],eax
    mov     dword ptr [esi].pcg32_random_t.state[4],edx
    pop     esi
    mov     eax,ebx
    mov     edx,ecx
    shrd    eax,edx,18
    sar     edx,18
    xor     eax,ebx
    xor     edx,ecx
    shrd    eax,edx,27
    shr     ecx,59-32
    mov     edx,eax
    shr     edx,cl

endif
    neg     ecx
    and     ecx,31
    shl     eax,cl
    or      eax,edx
    ret
    endp

    end
