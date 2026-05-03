; PCG32_BOUNDEDRAND_R.ASM--
;
; unsigned pcg32_boundedrand_r( pcg32_random_t *, unsigned );
;

include pcg_basic.inc

.code

pcg32_boundedrand_r proc uses rbx rng:ptr pcg32_random_t, _bound:uint32_t

    ldr     ecx,_bound
    mov     eax,ecx
    neg     eax
    xor     edx,edx
    div     ecx
    mov     ebx,edx

    .for (::)

        .continue( 0 ) .ifd ( pcg32_random_r(rng) < ebx )

        xor edx,edx
        div _bound
        mov eax,edx
       .break
    .endf
    ret
    endp

    end
