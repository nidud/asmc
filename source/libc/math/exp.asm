; EXP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include fltintrn.inc
include intrin.inc

option float: double
.data
align 16
 exp_table double \
  3FF0000000000000r, 3FF059B0D3158540r, 3FF0B5586CF98900r, 3FF11301D0125B40r,
  3FF172B83C7D5140r, 3FF1D4873168B980r, 3FF2387A6E756200r, 3FF29E9DF51FDEC0r,
  3FF306FE0A31B700r, 3FF371A7373AA9C0r, 3FF3DEA64C123400r, 3FF44E0860618900r,
  3FF4BFDAD5362A00r, 3FF5342B569D4F80r, 3FF5AB07DD485400r, 3FF6247EB03A5580r,
  3FF6A09E667F3BC0r, 3FF71F75E8EC5F40r, 3FF7A11473EB0180r, 3FF82589994CCE00r,
  3FF8ACE5422AA0C0r, 3FF93737B0CDC5C0r, 3FF9C49182A3F080r, 3FFA5503B23E2540r,
  3FFAE89F995AD380r, 3FFB7F76F2FB5E40r, 3FFC199BDD855280r, 3FFCB720DCEF9040r,
  3FFD5818DCFBA480r, 3FFDFC97337B9B40r, 3FFEA4AFA2A490C0r, 3FFF50765B6E4540r,
  0000000000000000r, 3D0A1D73E2A475B4r, 3CEEC5317256E308r, 3CF0A4EBBF1AED93r,
  3D0D6E6FBE462876r, 3D053C02DC0144C8r, 3D0C3360FD6D8E0Br, 3D009612E8AFAD12r,
  3CF52DE8D5A46306r, 3CE54E28AA05E8A9r, 3D011ADA0911F09Fr, 3D068189B7A04EF8r,
  3D038EA1CBD7F621r, 3CBDF0A83C49D86Ar, 3D04AC64980A8C8Fr, 3CD2C7C3E81BF4B7r,
  3CE921165F626CDDr, 3D09EE91B8797785r, 3CDB5F54408FDB37r, 3CF28ACF88AFAB35r,
  3CFB5BA7C55A192Dr, 3D027A280E1F92A0r, 3CF01C7C46B071F3r, 3CFC8B424491CAF8r,
  3D06AF439A68BB99r, 3CDBAA9EC206AD4Fr, 3CFC2220CB12A092r, 3D048A81E5E8F4A5r,
  3CDC976816BAD9B8r, 3CFEB968CAC39ED3r, 3CF9858F73A18F5Er, 3C99D3E12DD8A18Br
endif

.code

exp proc x:double
ifdef _WIN64
    _mm_move_sd(xmm1, INFINITY)
    .if ( xmm0 <= 0x1.62e42fefa39f0p9 )
        _mm_setzero_pd(xmm1)
        .if ( xmm0 > -745.5 )
            _mm_move_sd(xmm4, -0.0)
            _mm_and_pd(_mm_move_sd(xmm5, xmm1), xmm4)
            _mm_cmplt_sd(xmm4, xmm0)
            _mm_mul_sd(_mm_move_sd(xmm3, xmm0), 0x1.71547652B82FEp5)
            _mm_add_sd(xmm3,_mm_or_pd( xmm5, { 0.5, 0.5 }))
            _mm_cvttsd_si32(xmm3)
            _mm_cvtsi32_sd(xmm3, eax)
            _mm_sub_sd(xmm0, _mm_mul_sd( _mm_move_sd(xmm1, xmm3), 0x1.62E42FEF00000p-6))
            _mm_mul_sd(xmm3, -2.32519284687887401481e-12)
            _mm_move_sd(xmm5, xmm0)
            _mm_add_sd(xmm0, xmm3)
            _mm_add_sd(_mm_mul_sd(_mm_move_sd(xmm1, xmm0), 0x1.6C1728D739765p-10), 0x1.11115B7AA905Ep-7)
            _mm_add_sd(_mm_mul_sd(xmm1, xmm0), 0x1.5555555545D4Ep-5)
            _mm_add_sd(_mm_mul_sd(xmm1, xmm0), 0x1.5555555548F7Cp-3)
            _mm_add_sd(_mm_mul_sd(xmm1, xmm0), 0.5)
            _mm_mul_sd(_mm_mul_sd(xmm1, xmm0), xmm0)
            _mm_add_sd(_mm_add_sd(xmm1, xmm3), xmm5)
            lea rdx,exp_table
            mov ecx,eax
            and ecx,0x1F
            _mm_move_sd(xmm5, [rdx+rcx*8])
            _mm_move_sd(xmm3, [rdx+rcx*8+32*8])
            sub eax,ecx
            .if ( _mm_cvtsi128_si32( xmm4, edx ) )
                add eax,0x7920
                _mm_move_sd(xmm4, 0x1.0p+54)
            .else
                add eax,0x86a0
                _mm_move_sd(xmm4, 0x1.0p-54)
            .endif
            _mm_cvtsi32_si128(xmm2, eax)
            _mm_slli_epi64(xmm2, 15 + 32)
            _mm_add_sd( _mm_move_pd(xmm0, xmm5), xmm3 )
            _mm_mul_sd( xmm1, xmm0 )
            _mm_add_sd( xmm1, xmm3 )
            _mm_add_sd( xmm1, xmm5 )
            _mm_mul_sd( xmm1, xmm4 )
            _mm_mul_sd( xmm1, xmm2 )
        .endif
    .endif
    _mm_move_sd(xmm0, xmm1)
else
    fld     x
    fxam
    fstsw   ax
    fwait
    sahf
    jnp     L0
    jnc     L0
    test    ah,2
    jz      L1
    fstp    st
    fldz
    jmp     L1
L0:
    fldl2e
    fmul    st,st(1)
    fst     st(1)
    frndint
    fxch    st(1)
    fsub    st,st(1)
    f2xm1
    fld1
    faddp   st(1),st
    fscale
    fstp    st(1)
L1:
endif
    ret
    endp

    end
