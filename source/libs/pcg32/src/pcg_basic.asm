; PCG_BASIC.ASM--
;
; unsigned pcg32_srandom( unsigned __int64, unsigned __int64 );
; unsigned pcg32_random( void );
; unsigned pcg32_boundedrand( unsigned );
;
include pcg_basic.inc

.data
 pcg32_global pcg32_random_t PCG32_INITIALIZER

.code

pcg32_srandom proc initstate:uint64_t, initseq:uint64_t

    pcg32_srandom_r(&pcg32_global, initstate, initseq)
    ret

pcg32_srandom endp

pcg32_random proc

    pcg32_random_r(&pcg32_global)
    ret

pcg32_random endp

pcg32_boundedrand proc _bound:uint32_t

    pcg32_boundedrand_r(&pcg32_global, _bound)
    ret

pcg32_boundedrand endp

    end
