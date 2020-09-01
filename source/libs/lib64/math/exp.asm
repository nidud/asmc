; EXP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include immintrin.inc

extern exp2_table:double

    .code

    option win64:rsp nosave noauto

exp proc x:double

    movq    rax,xmm0
    add     rax,rax
    sbb     rdx,rdx
    shr     rax,1
    mov     rcx,0x3f662e42fefa39ef
    sub     rax,rcx
    add     rdx,64
    mov     rcx,0x011ff4e8de8082e3

    .repeat

        .if rax > rcx

            .ifg

                mov rcx,0x01211d42457337d4
                .ifs rax > rcx

                    .if _mm_ucominan_sd(xmm0, xmm0)

                        _mm_add_sd(xmm0, xmm0)
                        ret
                    .endif

                    .if _mm_comige_sd(xmm0, _mm_xor_pd(xmm1, xmm1))

                        _mm_mul_sd(xmm0, 7fefffffffffffffr)
                        ret
                    .endif

                    _mm_move_sd(xmm1, 0fff0000000000000r)
                    _mm_cmpneq_sd(xmm1, xmm0)
                    _mm_move_sd(xmm0, 0010000000000001r)
                    _mm_and_pd(xmm1, xmm0)
                    _mm_mul_sd(xmm0, xmm1)
                    ret
                .endif

                .if _mm_comige_sd(xmm0, _mm_xor_pd(xmm1, xmm1))

                    _mm_move_sd(xmm1, 40862e42fefa39efr)
                    .break .if _mm_comige_sd(xmm1, xmm0)
                    _mm_mul_sd(xmm0, 7fefffffffffffffr)
                    ret
                .endif

                _mm_move_pd(xmm1, xmm0)
                _mm_mul_sd(xmm0, 40671547652b82fer)
                _mm_cvttsd_si64()

                add rax,rdx
                mov rdx,rax
                sar rax,7
                and rdx,0x7f
                sal rdx,4

                _mm_move_sd(xmm2, 0010000000000001r)
                _mm_mul_sd(xmm2, xmm2)

                _mm_move_pd(xmm2, xmm1)
                _mm_mul_sd(xmm1, 3ff71547652b82fer)
                _mm_cvtsi64_sd(xmm3)

                _mm_move_pd(xmm0, xmm1)
                _mm_sub_sd(xmm1, xmm3)

                _mm_move_pd(xmm4, xmm2)
                _mm_move_sd(xmm3, 0fffffffff8000000r)
                _mm_mul_sd(xmm4, 03e54ae0bf85ddf44r)

                lea rcx,exp2_table
                _mm_sub_sd(xmm1, [rcx+rdx])

                _mm_move_sd(xmm5, 3f55e52272e0eaecr)
                _mm_mul_sd(xmm5, xmm1)
                _mm_add_sd(xmm5, 3f83b2a8abda3d8fr)
                _mm_mul_sd(xmm5, xmm1)
                _mm_add_sd(xmm5, 3fac6b08d78310b8r)

                _mm_and_pd(xmm3, xmm2)
                _mm_sub_sd(xmm2, xmm3)
                _mm_mul_sd(xmm3, 3ff7154760000000r)
                _mm_mul_sd(xmm2, 3ff7154760000000r)
                _mm_sub_sd(xmm3, xmm0)
                _mm_add_sd(xmm2, xmm3)
                _mm_add_sd(xmm2, xmm4)

                _mm_add_sd(xmm2, xmm1)
                _mm_move_pd(xmm3, xmm2)
                _mm_mul_sd(xmm5, xmm2)
                _mm_mul_sd(xmm3, xmm3)
                _mm_add_sd(xmm5, 3fcebfbdff82bda7r)
                _mm_mul_sd(xmm2, 3fe62e42fefa39efr)
                _mm_mul_sd(xmm3, xmm5)
                _mm_add_sd(xmm2, xmm3)

                add rax,1022
                _mm_slli_epi64(_mm_move_epi64(xmm4), 52)
                _mm_move_sd(xmm1, [rcx+rdx+8])
                _mm_add_pi32(xmm1, xmm4)
                _mm_mul_sd(xmm2, xmm1)
                _mm_move_sd(xmm0, 3ff0000000000000r)
                _mm_move_pd(xmm3, xmm1)
                _mm_add_sd(xmm1, xmm0)
                _mm_move_pd(xmm4, xmm1)
                _mm_sub_sd(xmm1, xmm0)
                _mm_sub_sd(xmm3, xmm1)
                _mm_add_sd(xmm2, xmm3)
                _mm_add_sd(xmm4, xmm2)
                _mm_xor_pd(xmm0, xmm4)
                ret

            .endif

            mov rcx,0xfd19d1bd0105c611
            .if rax <= rcx

                _mm_add_sd(xmm0, 3ff0000000000000r)
                ret
            .endif

            _mm_move_pd(xmm1, xmm0)
            _mm_mul_sd(xmm0, 3f8111116e99ac77r)
            _mm_add_sd(xmm0, 3fa55555ca407ccbr)
            _mm_add_sd(_mm_mul_sd(xmm0, xmm1), 3fc55555555553f0r)
            _mm_add_sd(_mm_mul_sd(xmm0, xmm1), 3fdffffffffffe1fr)
            _mm_add_sd(_mm_mul_sd(xmm0, xmm1), 3ff0000000000000r)
            _mm_add_sd(_mm_mul_sd(xmm0, xmm1), 3ff0000000000000r)
            ret
        .endif
    .until 1

    _mm_move_pd(xmm1, xmm0)
    _mm_mul_sd(xmm0, 40671547652b82fer)
    _mm_cvttsd_si64()

    add rax,rdx
    mov rdx,rax
    sar rax,7
    and rdx,0x7f
    sal rdx,4

    _mm_move_pd(xmm2, xmm1)
    _mm_mul_sd(xmm1, 3ff71547652b82fer)
    _mm_cvtsi64_sd(xmm3)

    _mm_move_pd(xmm0, xmm1)
    _mm_sub_sd(xmm1, xmm3)

    _mm_move_pd(xmm4, xmm2)
    _mm_move_sd(xmm3, 0fffffffff8000000r)
    _mm_mul_sd(xmm4, 3e54ae0bf85ddf44r)

    lea rcx,exp2_table
    _mm_sub_sd(xmm1, [rcx+rdx])

    _mm_move_sd(xmm5, 3f55e52272e0eaecr)
    _mm_mul_sd(xmm5, xmm1)
    _mm_add_sd(xmm5, 3f83b2a8abda3d8fr)
    _mm_mul_sd(xmm5, xmm1)
    _mm_add_sd(xmm5, 3fac6b08d78310b8r)
    _mm_and_pd(xmm3, xmm2)
    _mm_sub_sd(xmm2, xmm3)
    _mm_mul_sd(xmm3, 3ff7154760000000r)
    _mm_mul_sd(xmm2, 3ff7154760000000r)
    _mm_sub_sd(xmm3, xmm0)
    _mm_add_sd(xmm2, xmm3)
    _mm_add_sd(xmm2, xmm4)
    _mm_add_sd(xmm2, xmm1)
    _mm_move_pd(xmm3, xmm2)
    _mm_mul_sd(xmm5, xmm2)
    _mm_mul_sd(xmm3, xmm3)
    _mm_add_sd(xmm5, 3fcebfbdff82bda7r)
    _mm_mul_sd(xmm2, 3fe62e42fefa39efr)
    _mm_mul_sd(xmm3, xmm5)
    _mm_add_sd(xmm2, xmm3)
    _mm_slli_epi64(_mm_move_epi64(xmm4), 52)
    _mm_move_sd(xmm0, [rcx+rdx+8])
    _mm_mul_sd(xmm2, xmm0)
    _mm_add_sd(xmm0, xmm2)
    _mm_add_pi32(xmm0, xmm4)
    ret

exp endp

    end
