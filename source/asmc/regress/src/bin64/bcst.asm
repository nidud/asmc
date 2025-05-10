;
; v2.36.29 - reserved word BCST -- Masm style "embedded broadcast"
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code


    vaddpd zmm30,zmm29,qword bcst [rcx]
    vaddpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vaddpd zmm30,zmm29,qword bcst [rdx+0x400]
    vaddpd zmm30,zmm29,qword bcst [rdx-0x400]
    vaddpd zmm30,zmm29,qword bcst [rdx-0x408]
    vaddps zmm30,zmm29,dword bcst [rcx]
    vaddps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vaddps zmm30,zmm29,dword bcst [rdx+0x200]
    vaddps zmm30,zmm29,dword bcst [rdx-0x200]
    vaddps zmm30,zmm29,dword bcst [rdx-0x204]
    vdivpd zmm30,zmm29,qword bcst [rcx]
    vdivpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vdivpd zmm30,zmm29,qword bcst [rdx+0x400]
    vdivpd zmm30,zmm29,qword bcst [rdx-0x400]
    vdivpd zmm30,zmm29,qword bcst [rdx-0x408]
    vdivps zmm30,zmm29,dword bcst [rcx]
    vdivps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vdivps zmm30,zmm29,dword bcst [rdx+0x200]
    vdivps zmm30,zmm29,dword bcst [rdx-0x200]
    vdivps zmm30,zmm29,dword bcst [rdx-0x204]
    vmaxpd zmm30,zmm29,qword bcst [rcx]
    vmaxpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vmaxpd zmm30,zmm29,qword bcst [rdx+0x400]
    vmaxpd zmm30,zmm29,qword bcst [rdx-0x400]
    vmaxpd zmm30,zmm29,qword bcst [rdx-0x408]
    vmaxps zmm30,zmm29,dword bcst [rcx]
    vmaxps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vmaxps zmm30,zmm29,dword bcst [rdx+0x200]
    vmaxps zmm30,zmm29,dword bcst [rdx-0x200]
    vmaxps zmm30,zmm29,dword bcst [rdx-0x204]
    vminpd zmm30,zmm29,qword bcst [rcx]
    vminpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vminpd zmm30,zmm29,qword bcst [rdx+0x400]
    vminpd zmm30,zmm29,qword bcst [rdx-0x400]
    vminpd zmm30,zmm29,qword bcst [rdx-0x408]
    vminps zmm30,zmm29,dword bcst [rcx]
    vminps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vminps zmm30,zmm29,dword bcst [rdx+0x200]
    vminps zmm30,zmm29,dword bcst [rdx-0x200]
    vminps zmm30,zmm29,dword bcst [rdx-0x204]
    vmulpd zmm30,zmm29,qword bcst [rcx]
    vmulpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vmulpd zmm30,zmm29,qword bcst [rdx+0x400]
    vmulpd zmm30,zmm29,qword bcst [rdx-0x400]
    vmulpd zmm30,zmm29,qword bcst [rdx-0x408]
    vmulps zmm30,zmm29,dword bcst [rcx]
    vmulps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vmulps zmm30,zmm29,dword bcst [rdx+0x200]
    vmulps zmm30,zmm29,dword bcst [rdx-0x200]
    vmulps zmm30,zmm29,dword bcst [rdx-0x204]
    vsubpd zmm30,zmm29,qword bcst [rcx]
    vsubpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vsubpd zmm30,zmm29,qword bcst [rdx+0x400]
    vsubpd zmm30,zmm29,qword bcst [rdx-0x400]
    vsubpd zmm30,zmm29,qword bcst [rdx-0x408]
    vsubps zmm30,zmm29,dword bcst [rcx]
    vsubps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vsubps zmm30,zmm29,dword bcst [rdx+0x200]
    vsubps zmm30,zmm29,dword bcst [rdx-0x200]
    vsubps zmm30,zmm29,dword bcst [rdx-0x204]
    vsqrtpd zmm30,qword bcst [rcx]
    vsqrtpd zmm30,qword bcst [rdx+0x3f8]
    vsqrtpd zmm30,qword bcst [rdx+0x400]
    vsqrtpd zmm30,qword bcst [rdx-0x400]
    vsqrtpd zmm30,qword bcst [rdx-0x408]
    vsqrtps zmm30,dword bcst [rcx]
    vsqrtps zmm30,dword bcst [rdx+0x1fc]
    vsqrtps zmm30,dword bcst [rdx+0x200]
    vsqrtps zmm30,dword bcst [rdx-0x200]
    vsqrtps zmm30,dword bcst [rdx-0x204]


    vcmppd k5,zmm30,qword bcst [rcx],0x7b
    vcmppd k5,zmm30,qword bcst [rdx+0x3f8],0x7b
    vcmppd k5,zmm30,qword bcst [rdx+0x400],0x7b
    vcmppd k5,zmm30,qword bcst [rdx-0x400],0x7b
    vcmppd k5,zmm30,qword bcst [rdx-0x408],0x7b
    vcmpps k5,zmm30,dword bcst [rcx],0x7b
    vcmpps k5,zmm30,dword bcst [rdx+0x1fc],0x7b
    vcmpps k5,zmm30,dword bcst [rdx+0x200],0x7b
    vcmpps k5,zmm30,dword bcst [rdx-0x200],0x7b
    vcmpps k5,zmm30,dword bcst [rdx-0x204],0x7b

    vcvtdq2pd zmm30{k7},dword bcst [rcx]
    vcvtdq2pd zmm30{k7},dword bcst [rdx+0x1fc]
    vcvtdq2pd zmm30{k7},dword bcst [rdx+0x200]
    vcvtdq2pd zmm30{k7},dword bcst [rdx-0x200]
    vcvtdq2pd zmm30{k7},dword bcst [rdx-0x204]

    vcvtdq2ps zmm30,dword bcst [rcx]
    vcvtdq2ps zmm30,dword bcst [rdx+0x1fc]
    vcvtdq2ps zmm30,dword bcst [rdx+0x200]
    vcvtdq2ps zmm30,dword bcst [rdx-0x200]
    vcvtdq2ps zmm30,dword bcst [rdx-0x204]

    vcvtpd2dq ymm30{k7},qword bcst [rcx]
    vcvtpd2dq ymm30{k7},qword bcst [rdx+0x3f8]
    vcvtpd2dq ymm30{k7},qword bcst [rdx+0x400]
    vcvtpd2dq ymm30{k7},qword bcst [rdx-0x400]
    vcvtpd2dq ymm30{k7},qword bcst [rdx-0x408]

    vcvtpd2ps ymm30{k7},qword bcst [rcx]
    vcvtpd2ps ymm30{k7},qword bcst [rdx+0x3f8]
    vcvtpd2ps ymm30{k7},qword bcst [rdx+0x400]
    vcvtpd2ps ymm30{k7},qword bcst [rdx-0x400]
    vcvtpd2ps ymm30{k7},qword bcst [rdx-0x408]


    vpabsd zmm30,dword bcst [rcx]
    vpabsd zmm30,dword bcst [rdx+0x1fc]
    vpabsd zmm30,dword bcst [rdx+0x200]
    vpabsd zmm30,dword bcst [rdx-0x200]
    vpabsd zmm30,dword bcst [rdx-0x204]

    vpaddd zmm30,zmm29,dword bcst [rcx]
    vpaddd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpaddd zmm30,zmm29,dword bcst [rdx+0x200]
    vpaddd zmm30,zmm29,dword bcst [rdx-0x200]
    vpaddd zmm30,zmm29,dword bcst [rdx-0x204]

    vpaddq zmm30,zmm29,qword bcst [rcx]
    vpaddq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpaddq zmm30,zmm29,qword bcst [rdx+0x400]
    vpaddq zmm30,zmm29,qword bcst [rdx-0x400]
    vpaddq zmm30,zmm29,qword bcst [rdx-0x408]

    vpcmpeqd k5,zmm30,dword bcst [rcx]
    vpcmpeqd k5,zmm30,dword bcst [rdx+0x1fc]
    vpcmpeqd k5,zmm30,dword bcst [rdx+0x200]
    vpcmpeqd k5,zmm30,dword bcst [rdx-0x200]
    vpcmpeqd k5,zmm30,dword bcst [rdx-0x204]
    vpcmpeqq k5,zmm30,qword bcst [rcx]
    vpcmpeqq k5,zmm30,qword bcst [rdx+0x3f8]
    vpcmpeqq k5,zmm30,qword bcst [rdx+0x400]
    vpcmpeqq k5,zmm30,qword bcst [rdx-0x400]
    vpcmpeqq k5,zmm30,qword bcst [rdx-0x408]
    vpcmpgtd k5,zmm30,dword bcst [rcx]
    vpcmpgtd k5,zmm30,dword bcst [rdx+0x1fc]
    vpcmpgtd k5,zmm30,dword bcst [rdx+0x200]
    vpcmpgtd k5,zmm30,dword bcst [rdx-0x200]
    vpcmpgtd k5,zmm30,dword bcst [rdx-0x204]
    vpcmpgtq k5,zmm30,qword bcst [rcx]
    vpcmpgtq k5,zmm30,qword bcst [rdx+0x3f8]
    vpcmpgtq k5,zmm30,qword bcst [rdx+0x400]
    vpcmpgtq k5,zmm30,qword bcst [rdx-0x400]
    vpcmpgtq k5,zmm30,qword bcst [rdx-0x408]

    vpmaxsd zmm30,zmm29,dword bcst [rcx]
    vpmaxsd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpmaxsd zmm30,zmm29,dword bcst [rdx+0x200]
    vpmaxsd zmm30,zmm29,dword bcst [rdx-0x200]
    vpmaxsd zmm30,zmm29,dword bcst [rdx-0x204]

    vpmaxud zmm30,zmm29,dword bcst [rcx]
    vpmaxud zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpmaxud zmm30,zmm29,dword bcst [rdx+0x200]
    vpmaxud zmm30,zmm29,dword bcst [rdx-0x200]
    vpmaxud zmm30,zmm29,dword bcst [rdx-0x204]

    vpminsd zmm30,zmm29,dword bcst [rcx]
    vpminsd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpminsd zmm30,zmm29,dword bcst [rdx+0x200]
    vpminsd zmm30,zmm29,dword bcst [rdx-0x200]
    vpminsd zmm30,zmm29,dword bcst [rdx-0x204]

    vpminud zmm30,zmm29,dword bcst [rcx]
    vpminud zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpminud zmm30,zmm29,dword bcst [rdx+0x200]
    vpminud zmm30,zmm29,dword bcst [rdx-0x200]
    vpminud zmm30,zmm29,dword bcst [rdx-0x204]

    vpmuldq zmm30,zmm29,qword bcst [rcx]
    vpmuldq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpmuldq zmm30,zmm29,qword bcst [rdx+0x400]
    vpmuldq zmm30,zmm29,qword bcst [rdx-0x400]
    vpmuldq zmm30,zmm29,qword bcst [rdx-0x408]
    vpmulld zmm30,zmm29,dword bcst [rcx]
    vpmulld zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpmulld zmm30,zmm29,dword bcst [rdx+0x200]
    vpmulld zmm30,zmm29,dword bcst [rdx-0x200]
    vpmulld zmm30,zmm29,dword bcst [rdx-0x204]
    vpmuludq zmm30,zmm29,qword bcst [rcx]
    vpmuludq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpmuludq zmm30,zmm29,qword bcst [rdx+0x400]
    vpmuludq zmm30,zmm29,qword bcst [rdx-0x400]
    vpmuludq zmm30,zmm29,qword bcst [rdx-0x408]

    vpshufd zmm30,dword bcst [rcx],0x7b
    vpshufd zmm30,dword bcst [rdx+0x1fc],0x7b
    vpshufd zmm30,dword bcst [rdx+0x200],0x7b
    vpshufd zmm30,dword bcst [rdx-0x200],0x7b
    vpshufd zmm30,dword bcst [rdx-0x204],0x7b


    vpslld zmm30,dword bcst [rcx],0x7b
    vpslld zmm30,dword bcst [rdx+0x1fc],0x7b
    vpslld zmm30,dword bcst [rdx+0x200],0x7b
    vpslld zmm30,dword bcst [rdx-0x200],0x7b
    vpslld zmm30,dword bcst [rdx-0x204],0x7b

    vpsllq zmm30,qword bcst [rcx],0x7b
    vpsllq zmm30,qword bcst [rdx+0x3f8],0x7b
    vpsllq zmm30,qword bcst [rdx+0x400],0x7b
    vpsllq zmm30,qword bcst [rdx-0x400],0x7b
    vpsllq zmm30,qword bcst [rdx-0x408],0x7b

    vpsrad zmm30,dword bcst [rcx],0x7b
    vpsrad zmm30,dword bcst [rdx+0x1fc],0x7b
    vpsrad zmm30,dword bcst [rdx+0x200],0x7b
    vpsrad zmm30,dword bcst [rdx-0x200],0x7b
    vpsrad zmm30,dword bcst [rdx-0x204],0x7b

    vpsrld zmm30,dword bcst [rcx],0x7b
    vpsrld zmm30,dword bcst [rdx+0x1fc],0x7b
    vpsrld zmm30,dword bcst [rdx+0x200],0x7b
    vpsrld zmm30,dword bcst [rdx-0x200],0x7b
    vpsrld zmm30,dword bcst [rdx-0x204],0x7b

    vpsrlq zmm30,qword bcst [rcx],0x7b
    vpsrlq zmm30,qword bcst [rdx+0x3f8],0x7b
    vpsrlq zmm30,qword bcst [rdx+0x400],0x7b
    vpsrlq zmm30,qword bcst [rdx-0x400],0x7b
    vpsrlq zmm30,qword bcst [rdx-0x408],0x7b

    vcvtps2dq zmm30,dword bcst [rcx]
    vcvtps2dq zmm30,dword bcst [rdx+0x1fc]
    vcvtps2dq zmm30,dword bcst [rdx+0x200]
    vcvtps2dq zmm30,dword bcst [rdx-0x200]
    vcvtps2dq zmm30,dword bcst [rdx-0x204]

    vcvtps2pd zmm30{k7},dword bcst [rcx]
    vcvtps2pd zmm30{k7},dword bcst [rdx+0x1fc]
    vcvtps2pd zmm30{k7},dword bcst [rdx+0x200]
    vcvtps2pd zmm30{k7},dword bcst [rdx-0x200]
    vcvtps2pd zmm30{k7},dword bcst [rdx-0x204]

    vpsubd zmm30,zmm29,dword bcst [rcx]
    vpsubd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpsubd zmm30,zmm29,dword bcst [rdx+0x200]
    vpsubd zmm30,zmm29,dword bcst [rdx-0x200]
    vpsubd zmm30,zmm29,dword bcst [rdx-0x204]

    vpsubq zmm30,zmm29,qword bcst [rcx]
    vpsubq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpsubq zmm30,zmm29,qword bcst [rdx+0x400]
    vpsubq zmm30,zmm29,qword bcst [rdx-0x400]
    vpsubq zmm30,zmm29,qword bcst [rdx-0x408]

    vpunpckhdq zmm30,zmm29,dword bcst [rcx]
    vpunpckhdq zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpunpckhdq zmm30,zmm29,dword bcst [rdx+0x200]
    vpunpckhdq zmm30,zmm29,dword bcst [rdx-0x200]
    vpunpckhdq zmm30,zmm29,dword bcst [rdx-0x204]

    vpunpckhqdq zmm30,zmm29,qword bcst [rcx]
    vpunpckhqdq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpunpckhqdq zmm30,zmm29,qword bcst [rdx+0x400]
    vpunpckhqdq zmm30,zmm29,qword bcst [rdx-0x400]
    vpunpckhqdq zmm30,zmm29,qword bcst [rdx-0x408]

    vpunpckldq zmm30,zmm29,dword bcst [rcx]
    vpunpckldq zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpunpckldq zmm30,zmm29,dword bcst [rdx+0x200]
    vpunpckldq zmm30,zmm29,dword bcst [rdx-0x200]
    vpunpckldq zmm30,zmm29,dword bcst [rdx-0x204]

    vpunpcklqdq zmm30,zmm29,qword bcst [rcx]
    vpunpcklqdq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpunpcklqdq zmm30,zmm29,qword bcst [rdx+0x400]
    vpunpcklqdq zmm30,zmm29,qword bcst [rdx-0x400]
    vpunpcklqdq zmm30,zmm29,qword bcst [rdx-0x408]

    vshufpd zmm30,zmm29,qword bcst [rcx],0x7b
    vshufpd zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    vshufpd zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    vshufpd zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    vshufpd zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    vshufps zmm30,zmm29,dword bcst [rcx],0x7b
    vshufps zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    vshufps zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    vshufps zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    vshufps zmm30,zmm29,dword bcst [rdx-0x204],0x7b

    vunpckhpd zmm30,zmm29,qword bcst [rcx]
    vunpckhpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vunpckhpd zmm30,zmm29,qword bcst [rdx+0x400]
    vunpckhpd zmm30,zmm29,qword bcst [rdx-0x400]
    vunpckhpd zmm30,zmm29,qword bcst [rdx-0x408]
    vunpckhps zmm30,zmm29,dword bcst [rcx]
    vunpckhps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vunpckhps zmm30,zmm29,dword bcst [rdx+0x200]
    vunpckhps zmm30,zmm29,dword bcst [rdx-0x200]
    vunpckhps zmm30,zmm29,dword bcst [rdx-0x204]

    vunpcklpd zmm30,zmm29,qword bcst [rcx]
    vunpcklpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vunpcklpd zmm30,zmm29,qword bcst [rdx+0x400]
    vunpcklpd zmm30,zmm29,qword bcst [rdx-0x400]
    vunpcklpd zmm30,zmm29,qword bcst [rdx-0x408]

    vunpcklps zmm30,zmm29,dword bcst [rcx]
    vunpcklps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vunpcklps zmm30,zmm29,dword bcst [rdx+0x200]
    vunpcklps zmm30,zmm29,dword bcst [rdx-0x200]
    vunpcklps zmm30,zmm29,dword bcst [rdx-0x204]

    vpandd zmm30,zmm29,dword bcst [rcx]
    vpandd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpandd zmm30,zmm29,dword bcst [rdx+0x200]
    vpandd zmm30,zmm29,dword bcst [rdx-0x200]
    vpandd zmm30,zmm29,dword bcst [rdx-0x204]

    vpandq zmm30,zmm29,qword bcst [rcx]
    vpandq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpandq zmm30,zmm29,qword bcst [rdx+0x400]
    vpandq zmm30,zmm29,qword bcst [rdx-0x400]
    vpandq zmm30,zmm29,qword bcst [rdx-0x408]

    vpandnd zmm30,zmm29,dword bcst [rcx]
    vpandnd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpandnd zmm30,zmm29,dword bcst [rdx+0x200]
    vpandnd zmm30,zmm29,dword bcst [rdx-0x200]
    vpandnd zmm30,zmm29,dword bcst [rdx-0x204]

    vpandnq zmm30,zmm29,qword bcst [rcx]
    vpandnq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpandnq zmm30,zmm29,qword bcst [rdx+0x400]
    vpandnq zmm30,zmm29,qword bcst [rdx-0x400]
    vpandnq zmm30,zmm29,qword bcst [rdx-0x408]

    vpxord zmm30,zmm29,dword bcst [rcx]
    vpxord zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpxord zmm30,zmm29,dword bcst [rdx+0x200]
    vpxord zmm30,zmm29,dword bcst [rdx-0x200]
    vpxord zmm30,zmm29,dword bcst [rdx-0x204]

    vpxorq zmm30,zmm29,qword bcst [rcx]
    vpxorq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpxorq zmm30,zmm29,qword bcst [rdx+0x400]
    vpxorq zmm30,zmm29,qword bcst [rdx-0x400]
    vpxorq zmm30,zmm29,qword bcst [rdx-0x408]

    vpsraq zmm30,qword bcst [rcx],0x7b
    vpsraq zmm30,qword bcst [rdx+0x3f8],0x7b
    vpsraq zmm30,qword bcst [rdx+0x400],0x7b
    vpsraq zmm30,qword bcst [rdx-0x400],0x7b
    vpsraq zmm30,qword bcst [rdx-0x408],0x7b

    vpconflictd zmm30,dword bcst [rcx]
    vpconflictd zmm30,dword bcst [rdx+0x1fc]
    vpconflictd zmm30,dword bcst [rdx+0x200]
    vpconflictd zmm30,dword bcst [rdx-0x200]
    vpconflictd zmm30,dword bcst [rdx-0x204]

    vpconflictq zmm30,qword bcst [rcx]
    vpconflictq zmm30,qword bcst [rdx+0x3f8]
    vpconflictq zmm30,qword bcst [rdx+0x400]
    vpconflictq zmm30,qword bcst [rdx-0x400]
    vpconflictq zmm30,qword bcst [rdx-0x408]

    vplzcntd	zmm30,dword bcst [rcx]
    vplzcntd	zmm30,dword bcst [rdx+0x1fc]
    vplzcntd	zmm30,dword bcst [rdx+0x200]
    vplzcntd	zmm30,dword bcst [rdx-0x200]
    vplzcntd	zmm30,dword bcst [rdx-0x204]

    vplzcntq	zmm30,qword bcst [rcx]
    vplzcntq	zmm30,qword bcst [rdx+0x3f8]
    vplzcntq	zmm30,qword bcst [rdx+0x400]
    vplzcntq	zmm30,qword bcst [rdx-0x400]
    vplzcntq	zmm30,qword bcst [rdx-0x408]

    vptestnmd	k5,zmm29,dword bcst [rcx]
    vptestnmd	k5,zmm29,dword bcst [rdx+0x1fc]
    vptestnmd	k5,zmm29,dword bcst [rdx+0x200]
    vptestnmd	k5,zmm29,dword bcst [rdx-0x200]
    vptestnmd	k5,zmm29,dword bcst [rdx-0x204]

    vptestnmq	k5,zmm29,qword bcst [rcx]
    vptestnmq	k5,zmm29,qword bcst [rdx+0x3f8]
    vptestnmq	k5,zmm29,qword bcst [rdx+0x400]
    vptestnmq	k5,zmm29,qword bcst [rdx-0x400]
    vptestnmq	k5,zmm29,qword bcst [rdx-0x408]

    vexp2ps zmm30,dword bcst [rcx]
    vexp2ps zmm30,dword bcst [rdx+0x1fc]
    vexp2ps zmm30,dword bcst [rdx+0x200]
    vexp2ps zmm30,dword bcst [rdx-0x200]
    vexp2ps zmm30,dword bcst [rdx-0x204]

    vexp2pd zmm30,qword bcst [rcx]
    vexp2pd zmm30,qword bcst [rdx+0x3f8]
    vexp2pd zmm30,qword bcst [rdx+0x400]
    vexp2pd zmm30,qword bcst [rdx-0x400]
    vexp2pd zmm30,qword bcst [rdx-0x408]

    vrcp28ps zmm30,dword bcst [rcx]
    vrcp28ps zmm30,dword bcst [rdx+0x1fc]
    vrcp28ps zmm30,dword bcst [rdx+0x200]
    vrcp28ps zmm30,dword bcst [rdx-0x200]
    vrcp28ps zmm30,dword bcst [rdx-0x204]

    vrcp28pd zmm30,qword bcst [rcx]
    vrcp28pd zmm30,qword bcst [rdx+0x3f8]
    vrcp28pd zmm30,qword bcst [rdx+0x400]
    vrcp28pd zmm30,qword bcst [rdx-0x400]
    vrcp28pd zmm30,qword bcst [rdx-0x408]


    vrsqrt28ps zmm30,dword bcst [rcx]
    vrsqrt28ps zmm30,dword bcst [rdx+0x1fc]
    vrsqrt28ps zmm30,dword bcst [rdx+0x200]
    vrsqrt28ps zmm30,dword bcst [rdx-0x200]
    vrsqrt28ps zmm30,dword bcst [rdx-0x204]

    vrsqrt28pd zmm30,qword bcst [rcx]
    vrsqrt28pd zmm30,qword bcst [rdx+0x3f8]
    vrsqrt28pd zmm30,qword bcst [rdx+0x400]
    vrsqrt28pd zmm30,qword bcst [rdx-0x400]
    vrsqrt28pd zmm30,qword bcst [rdx-0x408]

    vrsqrt14ps zmm30,dword bcst [rcx]
    vrsqrt14ps zmm30,dword bcst [rdx+0x1fc]
    vrsqrt14ps zmm30,dword bcst [rdx+0x200]
    vrsqrt14ps zmm30,dword bcst [rdx-0x200]
    vrsqrt14ps zmm30,dword bcst [rdx-0x204]

    vrsqrt14pd zmm30,qword bcst [rcx]
    vrsqrt14pd zmm30,qword bcst [rdx+0x3f8]
    vrsqrt14pd zmm30,qword bcst [rdx+0x400]
    vrsqrt14pd zmm30,qword bcst [rdx-0x400]
    vrsqrt14pd zmm30,qword bcst [rdx-0x408]

    vrsqrt14ps zmm30,dword bcst [rcx]
    vrsqrt14ps zmm30,dword bcst [rdx+0x1fc]
    vrsqrt14ps zmm30,dword bcst [rdx+0x200]
    vrsqrt14ps zmm30,dword bcst [rdx-0x200]
    vrsqrt14ps zmm30,dword bcst [rdx-0x204]


    vcvtpd2udq ymm30{k7},qword bcst [rcx]
    vcvtpd2udq ymm30{k7},qword bcst [rdx+0x3f8]
    vcvtpd2udq ymm30{k7},qword bcst [rdx+0x400]
    vcvtpd2udq ymm30{k7},qword bcst [rdx-0x400]
    vcvtpd2udq ymm30{k7},qword bcst [rdx-0x408]

    vcvtps2udq zmm30,dword bcst [rcx]
    vcvtps2udq zmm30,dword bcst [rdx+0x1fc]
    vcvtps2udq zmm30,dword bcst [rdx+0x200]
    vcvtps2udq zmm30,dword bcst [rdx-0x200]
    vcvtps2udq zmm30,dword bcst [rdx-0x204]

    vcvttpd2udq ymm30{k7},qword bcst [rcx]
    vcvttpd2udq ymm30{k7},qword bcst [rdx+0x3f8]
    vcvttpd2udq ymm30{k7},qword bcst [rdx+0x400]
    vcvttpd2udq ymm30{k7},qword bcst [rdx-0x400]
    vcvttpd2udq ymm30{k7},qword bcst [rdx-0x408]

    vcvttps2udq zmm30,dword bcst [rcx]
    vcvttps2udq zmm30,dword bcst [rdx+0x1fc]
    vcvttps2udq zmm30,dword bcst [rdx+0x200]
    vcvttps2udq zmm30,dword bcst [rdx-0x200]
    vcvttps2udq zmm30,dword bcst [rdx-0x204]

    vcvtudq2ps zmm30,dword bcst [rcx]
    vcvtudq2ps zmm30,dword bcst [rdx+0x1fc]
    vcvtudq2ps zmm30,dword bcst [rdx+0x200]
    vcvtudq2ps zmm30,dword bcst [rdx-0x200]
    vcvtudq2ps zmm30,dword bcst [rdx-0x204]


    vgetexppd zmm30,qword bcst [rcx]
    vgetexppd zmm30,qword bcst [rdx+0x3f8]
    vgetexppd zmm30,qword bcst [rdx+0x400]
    vgetexppd zmm30,qword bcst [rdx-0x400]
    vgetexppd zmm30,qword bcst [rdx-0x408]

    vgetexpps zmm30,dword bcst [rcx]
    vgetexpps zmm30,dword bcst [rdx+0x1fc]
    vgetexpps zmm30,dword bcst [rdx+0x200]
    vgetexpps zmm30,dword bcst [rdx-0x200]
    vgetexpps zmm30,dword bcst [rdx-0x204]


    vrcp14pd zmm30,qword bcst [rcx]
    vrcp14pd zmm30,qword bcst [rdx+0x3f8]
    vrcp14pd zmm30,qword bcst [rdx+0x400]
    vrcp14pd zmm30,qword bcst [rdx-0x400]
    vrcp14pd zmm30,qword bcst [rdx-0x408]

    vrcp14ps zmm30,dword bcst [rcx]
    vrcp14ps zmm30,dword bcst [rdx+0x1fc]
    vrcp14ps zmm30,dword bcst [rdx+0x200]
    vrcp14ps zmm30,dword bcst [rdx-0x200]
    vrcp14ps zmm30,dword bcst [rdx-0x204]

    vrndscalepd zmm30,qword bcst [rcx],0x7b
    vrndscalepd zmm30,qword bcst [rdx+0x3f8],0x7b
    vrndscalepd zmm30,qword bcst [rdx+0x400],0x7b
    vrndscalepd zmm30,qword bcst [rdx-0x400],0x7b
    vrndscalepd zmm30,qword bcst [rdx-0x408],0x7b

    vrndscaleps zmm30,dword bcst [rcx],0x7b
    vrndscaleps zmm30,dword bcst [rdx+0x1fc],0x7b
    vrndscaleps zmm30,dword bcst [rdx+0x200],0x7b
    vrndscaleps zmm30,dword bcst [rdx-0x200],0x7b
    vrndscaleps zmm30,dword bcst [rdx-0x204],0x7b

    valignd zmm30,zmm29,dword bcst [rcx],0x7b
    valignd zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    valignd zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    valignd zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    valignd zmm30,zmm29,dword bcst [rdx-0x204],0x7b

    vblendmpd zmm30,zmm29,qword bcst [rcx]
    vblendmpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vblendmpd zmm30,zmm29,qword bcst [rdx+0x400]
    vblendmpd zmm30,zmm29,qword bcst [rdx-0x400]
    vblendmpd zmm30,zmm29,qword bcst [rdx-0x408]

    vblendmps zmm30,zmm29,dword bcst [rcx]
    vblendmps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vblendmps zmm30,zmm29,dword bcst [rdx+0x200]
    vblendmps zmm30,zmm29,dword bcst [rdx-0x200]
    vblendmps zmm30,zmm29,dword bcst [rdx-0x204]

    vcvttpd2dq ymm30{k7},qword bcst [rcx]
    vcvttpd2dq ymm30{k7},qword bcst [rdx+0x3f8]
    vcvttpd2dq ymm30{k7},qword bcst [rdx+0x400]
    vcvttpd2dq ymm30{k7},qword bcst [rdx-0x400]
    vcvttpd2dq ymm30{k7},qword bcst [rdx-0x408]

    vcvttps2dq zmm30,dword bcst [rcx]
    vcvttps2dq zmm30,dword bcst [rdx+0x1fc]
    vcvttps2dq zmm30,dword bcst [rdx+0x200]
    vcvttps2dq zmm30,dword bcst [rdx-0x200]
    vcvttps2dq zmm30,dword bcst [rdx-0x204]

    vfmadd132pd zmm30,zmm29,qword bcst [rcx]
    vfmadd132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmadd132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmadd132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmadd132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmadd132ps zmm30,zmm29,dword bcst [rcx]
    vfmadd132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmadd132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmadd132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmadd132ps zmm30,zmm29,dword bcst [rdx-0x204]


    vfmadd213pd zmm30,zmm29,qword bcst [rcx]
    vfmadd213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmadd213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmadd213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmadd213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmadd213ps zmm30,zmm29,dword bcst [rcx]
    vfmadd213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmadd213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmadd213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmadd213ps zmm30,zmm29,dword bcst [rdx-0x204]


    vfmadd231pd zmm30,zmm29,qword bcst [rcx]
    vfmadd231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmadd231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmadd231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmadd231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmadd231ps zmm30,zmm29,dword bcst [rcx]
    vfmadd231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmadd231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmadd231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmadd231ps zmm30,zmm29,dword bcst [rdx-0x204]


    vfmaddsub132pd zmm30,zmm29,qword bcst [rcx]
    vfmaddsub132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmaddsub132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmaddsub132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmaddsub132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmaddsub132ps zmm30,zmm29,dword bcst [rcx]
    vfmaddsub132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmaddsub132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmaddsub132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmaddsub132ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmaddsub213pd zmm30,zmm29,qword bcst [rcx]
    vfmaddsub213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmaddsub213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmaddsub213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmaddsub213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmaddsub213ps zmm30,zmm29,dword bcst [rcx]
    vfmaddsub213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmaddsub213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmaddsub213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmaddsub213ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmaddsub231pd zmm30,zmm29,qword bcst [rcx]
    vfmaddsub231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmaddsub231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmaddsub231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmaddsub231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmaddsub231ps zmm30,zmm29,dword bcst [rcx]
    vfmaddsub231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmaddsub231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmaddsub231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmaddsub231ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsub132pd zmm30,zmm29,qword bcst [rcx]
    vfmsub132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsub132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsub132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsub132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsub132ps zmm30,zmm29,dword bcst [rcx]
    vfmsub132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsub132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsub132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsub132ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsub213pd zmm30,zmm29,qword bcst [rcx]
    vfmsub213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsub213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsub213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsub213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsub213ps zmm30,zmm29,dword bcst [rcx]
    vfmsub213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsub213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsub213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsub213ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsub231pd zmm30,zmm29,qword bcst [rcx]
    vfmsub231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsub231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsub231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsub231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsub231ps zmm30,zmm29,dword bcst [rcx]
    vfmsub231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsub231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsub231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsub231ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsubadd132pd zmm30,zmm29,qword bcst [rcx]
    vfmsubadd132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsubadd132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsubadd132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsubadd132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsubadd132ps zmm30,zmm29,dword bcst [rcx]
    vfmsubadd132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsubadd132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsubadd132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsubadd132ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsubadd213pd zmm30,zmm29,qword bcst [rcx]
    vfmsubadd213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsubadd213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsubadd213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsubadd213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsubadd213ps zmm30,zmm29,dword bcst [rcx]
    vfmsubadd213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsubadd213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsubadd213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsubadd213ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfmsubadd231pd zmm30,zmm29,qword bcst [rcx]
    vfmsubadd231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfmsubadd231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfmsubadd231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfmsubadd231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfmsubadd231ps zmm30,zmm29,dword bcst [rcx]
    vfmsubadd231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfmsubadd231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfmsubadd231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfmsubadd231ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfnmadd132pd zmm30,zmm29,qword bcst [rcx]
    vfnmadd132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmadd132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmadd132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmadd132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmadd132ps zmm30,zmm29,dword bcst [rcx]
    vfnmadd132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmadd132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmadd132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmadd132ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfnmadd213pd zmm30,zmm29,qword bcst [rcx]
    vfnmadd213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmadd213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmadd213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmadd213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmadd213ps zmm30,zmm29,dword bcst [rcx]
    vfnmadd213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmadd213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmadd213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmadd213ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfnmadd231pd zmm30,zmm29,qword bcst [rcx]
    vfnmadd231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmadd231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmadd231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmadd231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmadd231ps zmm30,zmm29,dword bcst [rcx]
    vfnmadd231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmadd231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmadd231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmadd231ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfnmsub132pd zmm30,zmm29,qword bcst [rcx]
    vfnmsub132pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmsub132pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmsub132pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmsub132pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmsub132ps zmm30,zmm29,dword bcst [rcx]
    vfnmsub132ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmsub132ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmsub132ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmsub132ps zmm30,zmm29,dword bcst [rdx-0x204]

    vfnmsub213pd zmm30,zmm29,qword bcst [rcx]
    vfnmsub213pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmsub213pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmsub213pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmsub213pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmsub213ps zmm30,zmm29,dword bcst [rcx]
    vfnmsub213ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmsub213ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmsub213ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmsub213ps zmm30,zmm29,dword bcst [rdx-0x204]


    vfnmsub231pd zmm30,zmm29,qword bcst [rcx]
    vfnmsub231pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vfnmsub231pd zmm30,zmm29,qword bcst [rdx+0x400]
    vfnmsub231pd zmm30,zmm29,qword bcst [rdx-0x400]
    vfnmsub231pd zmm30,zmm29,qword bcst [rdx-0x408]

    vfnmsub231ps zmm30,zmm29,dword bcst [rcx]
    vfnmsub231ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vfnmsub231ps zmm30,zmm29,dword bcst [rdx+0x200]
    vfnmsub231ps zmm30,zmm29,dword bcst [rdx-0x200]
    vfnmsub231ps zmm30,zmm29,dword bcst [rdx-0x204]

    vgetmantpd zmm30,qword bcst [rcx],0x7b
    vgetmantpd zmm30,qword bcst [rdx+0x3f8],0x7b
    vgetmantpd zmm30,qword bcst [rdx+0x400],0x7b
    vgetmantpd zmm30,qword bcst [rdx-0x400],0x7b
    vgetmantpd zmm30,qword bcst [rdx-0x408],0x7b

    vgetmantps zmm30,dword bcst [rcx],0x7b
    vgetmantps zmm30,dword bcst [rdx+0x1fc],0x7b
    vgetmantps zmm30,dword bcst [rdx+0x200],0x7b
    vgetmantps zmm30,dword bcst [rdx-0x200],0x7b
    vgetmantps zmm30,dword bcst [rdx-0x204],0x7b

    vpabsq zmm30,qword bcst [rcx]
    vpabsq zmm30,qword bcst [rdx+0x3f8]
    vpabsq zmm30,qword bcst [rdx+0x400]
    vpabsq zmm30,qword bcst [rdx-0x400]
    vpabsq zmm30,qword bcst [rdx-0x408]

    vpblendmd zmm30,zmm29,dword bcst [rcx]
    vpblendmd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpblendmd zmm30,zmm29,dword bcst [rdx+0x200]
    vpblendmd zmm30,zmm29,dword bcst [rdx-0x200]
    vpblendmd zmm30,zmm29,dword bcst [rdx-0x204]


    vpcmpd k5,zmm30,dword bcst [rcx],0x7b
    vpcmpd k5,zmm30,dword bcst [rdx+0x1fc],0x7b
    vpcmpd k5,zmm30,dword bcst [rdx+0x200],0x7b
    vpcmpd k5,zmm30,dword bcst [rdx-0x200],0x7b
    vpcmpd k5,zmm30,dword bcst [rdx-0x204],0x7b

    vpcmpq k5,zmm30,qword bcst [rcx],0x7b
    vpcmpq k5,zmm30,qword bcst [rdx+0x3f8],0x7b
    vpcmpq k5,zmm30,qword bcst [rdx+0x400],0x7b
    vpcmpq k5,zmm30,qword bcst [rdx-0x400],0x7b
    vpcmpq k5,zmm30,qword bcst [rdx-0x408],0x7b

    vpcmpud k5,zmm30,dword bcst [rcx],0x7b
    vpcmpud k5,zmm30,dword bcst [rdx+0x1fc],0x7b
    vpcmpud k5,zmm30,dword bcst [rdx+0x200],0x7b
    vpcmpud k5,zmm30,dword bcst [rdx-0x200],0x7b
    vpcmpud k5,zmm30,dword bcst [rdx-0x204],0x7b


    vpcmpuq k5,zmm30,qword bcst [rcx],0x7b
    vpcmpuq k5,zmm30,qword bcst [rdx+0x3f8],0x7b
    vpcmpuq k5,zmm30,qword bcst [rdx+0x400],0x7b
    vpcmpuq k5,zmm30,qword bcst [rdx-0x400],0x7b
    vpcmpuq k5,zmm30,qword bcst [rdx-0x408],0x7b

    vpblendmq zmm30,zmm29,qword bcst [rcx]
    vpblendmq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpblendmq zmm30,zmm29,qword bcst [rdx+0x400]
    vpblendmq zmm30,zmm29,qword bcst [rdx-0x400]
    vpblendmq zmm30,zmm29,qword bcst [rdx-0x408]

    vpermd zmm30,zmm29,dword bcst [rcx]
    vpermd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpermd zmm30,zmm29,dword bcst [rdx+0x200]
    vpermd zmm30,zmm29,dword bcst [rdx-0x200]
    vpermd zmm30,zmm29,dword bcst [rdx-0x204]

    vpermilpd zmm30,qword bcst [rcx],0x7b
    vpermilpd zmm30,qword bcst [rdx+0x3f8],0x7b
    vpermilpd zmm30,qword bcst [rdx+0x400],0x7b
    vpermilpd zmm30,qword bcst [rdx-0x400],0x7b
    vpermilpd zmm30,qword bcst [rdx-0x408],0x7b

    vpermilpd zmm30,zmm29,qword bcst [rcx]
    vpermilpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpermilpd zmm30,zmm29,qword bcst [rdx+0x400]
    vpermilpd zmm30,zmm29,qword bcst [rdx-0x400]
    vpermilpd zmm30,zmm29,qword bcst [rdx-0x408]

    vpermilps zmm30,dword bcst [rcx],0x7b
    vpermilps zmm30,dword bcst [rdx+0x1fc],0x7b
    vpermilps zmm30,dword bcst [rdx+0x200],0x7b
    vpermilps zmm30,dword bcst [rdx-0x200],0x7b
    vpermilps zmm30,dword bcst [rdx-0x204],0x7b

    vpermilps zmm30,zmm29,dword bcst [rcx]
    vpermilps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpermilps zmm30,zmm29,dword bcst [rdx+0x200]
    vpermilps zmm30,zmm29,dword bcst [rdx-0x200]
    vpermilps zmm30,zmm29,dword bcst [rdx-0x204]

    vpermpd zmm30,qword bcst [rcx],0x7b
    vpermpd zmm30,qword bcst [rdx+0x3f8],0x7b
    vpermpd zmm30,qword bcst [rdx+0x400],0x7b
    vpermpd zmm30,qword bcst [rdx-0x400],0x7b
    vpermpd zmm30,qword bcst [rdx-0x408],0x7b

    vpermpd zmm30,zmm29,qword bcst [rcx]
    vpermpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpermpd zmm30,zmm29,qword bcst [rdx+0x400]
    vpermpd zmm30,zmm29,qword bcst [rdx-0x400]
    vpermpd zmm30,zmm29,qword bcst [rdx-0x408]

    vpermps zmm30,zmm29,dword bcst [rcx]
    vpermps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpermps zmm30,zmm29,dword bcst [rdx+0x200]
    vpermps zmm30,zmm29,dword bcst [rdx-0x200]
    vpermps zmm30,zmm29,dword bcst [rdx-0x204]

    vpermq zmm30,qword bcst [rcx],0x7b
    vpermq zmm30,qword bcst [rdx+0x3f8],0x7b
    vpermq zmm30,qword bcst [rdx+0x400],0x7b
    vpermq zmm30,qword bcst [rdx-0x400],0x7b
    vpermq zmm30,qword bcst [rdx-0x408],0x7b

    vpermq zmm30,zmm29,qword bcst [rcx]
    vpermq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpermq zmm30,zmm29,qword bcst [rdx+0x400]
    vpermq zmm30,zmm29,qword bcst [rdx-0x400]
    vpermq zmm30,zmm29,qword bcst [rdx-0x408]

    vpmaxsq zmm30,zmm29,qword bcst [rcx]
    vpmaxsq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpmaxsq zmm30,zmm29,qword bcst [rdx+0x400]
    vpmaxsq zmm30,zmm29,qword bcst [rdx-0x400]
    vpmaxsq zmm30,zmm29,qword bcst [rdx-0x408]

    vpmaxuq zmm30,zmm29,qword bcst [rcx]
    vpmaxuq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpmaxuq zmm30,zmm29,qword bcst [rdx+0x400]
    vpmaxuq zmm30,zmm29,qword bcst [rdx-0x400]
    vpmaxuq zmm30,zmm29,qword bcst [rdx-0x408]

    vpminsq zmm30,zmm29,qword bcst [rcx]
    vpminsq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpminsq zmm30,zmm29,qword bcst [rdx+0x400]
    vpminsq zmm30,zmm29,qword bcst [rdx-0x400]
    vpminsq zmm30,zmm29,qword bcst [rdx-0x408]

    vpminuq zmm30,zmm29,qword bcst [rcx]
    vpminuq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpminuq zmm30,zmm29,qword bcst [rdx+0x400]
    vpminuq zmm30,zmm29,qword bcst [rdx-0x400]
    vpminuq zmm30,zmm29,qword bcst [rdx-0x408]

    vpord  zmm30,zmm29,dword bcst [rcx]
    vpord  zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpord  zmm30,zmm29,dword bcst [rdx+0x200]
    vpord  zmm30,zmm29,dword bcst [rdx-0x200]
    vpord  zmm30,zmm29,dword bcst [rdx-0x204]

    vporq  zmm30,zmm29,qword bcst [rcx]
    vporq  zmm30,zmm29,qword bcst [rdx+0x3f8]
    vporq  zmm30,zmm29,qword bcst [rdx+0x400]
    vporq  zmm30,zmm29,qword bcst [rdx-0x400]
    vporq  zmm30,zmm29,qword bcst [rdx-0x408]

    vpsllvd zmm30,zmm29,dword bcst [rcx]
    vpsllvd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpsllvd zmm30,zmm29,dword bcst [rdx+0x200]
    vpsllvd zmm30,zmm29,dword bcst [rdx-0x200]
    vpsllvd zmm30,zmm29,dword bcst [rdx-0x204]

    vpsllvq zmm30,zmm29,qword bcst [rcx]
    vpsllvq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpsllvq zmm30,zmm29,qword bcst [rdx+0x400]
    vpsllvq zmm30,zmm29,qword bcst [rdx-0x400]
    vpsllvq zmm30,zmm29,qword bcst [rdx-0x408]

    vpsravd zmm30,zmm29,dword bcst [rcx]
    vpsravd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpsravd zmm30,zmm29,dword bcst [rdx+0x200]
    vpsravd zmm30,zmm29,dword bcst [rdx-0x200]
    vpsravd zmm30,zmm29,dword bcst [rdx-0x204]

    vpsravq zmm30,zmm29,qword bcst [rcx]
    vpsravq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpsravq zmm30,zmm29,qword bcst [rdx+0x400]
    vpsravq zmm30,zmm29,qword bcst [rdx-0x400]
    vpsravq zmm30,zmm29,qword bcst [rdx-0x408]

    vpsrlvd zmm30,zmm29,dword bcst [rcx]
    vpsrlvd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpsrlvd zmm30,zmm29,dword bcst [rdx+0x200]
    vpsrlvd zmm30,zmm29,dword bcst [rdx-0x200]
    vpsrlvd zmm30,zmm29,dword bcst [rdx-0x204]
    vpsrlvq zmm30,zmm29,qword bcst [rcx]
    vpsrlvq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpsrlvq zmm30,zmm29,qword bcst [rdx+0x400]
    vpsrlvq zmm30,zmm29,qword bcst [rdx-0x400]
    vpsrlvq zmm30,zmm29,qword bcst [rdx-0x408]

    vptestmd k5,zmm30,dword bcst [rcx]
    vptestmd k5,zmm30,dword bcst [rdx+0x1fc]
    vptestmd k5,zmm30,dword bcst [rdx+0x200]
    vptestmd k5,zmm30,dword bcst [rdx-0x200]
    vptestmd k5,zmm30,dword bcst [rdx-0x204]
    vptestmq k5,zmm30,qword bcst [rcx]
    vptestmq k5,zmm30,qword bcst [rdx+0x3f8]
    vptestmq k5,zmm30,qword bcst [rdx+0x400]
    vptestmq k5,zmm30,qword bcst [rdx-0x400]
    vptestmq k5,zmm30,qword bcst [rdx-0x408]

    vpternlogd zmm30,zmm29,dword bcst [rcx],0x7b
    vpternlogd zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    vpternlogd zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    vpternlogd zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    vpternlogd zmm30,zmm29,dword bcst [rdx-0x204],0x7b
    vpternlogq zmm30,zmm29,qword bcst [rcx],0x7b
    vpternlogq zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    vpternlogq zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    vpternlogq zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    vpternlogq zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    vshuff32x4 zmm30,zmm29,dword bcst [rcx],0x7b
    vshuff32x4 zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    vshuff32x4 zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    vshuff32x4 zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    vshuff32x4 zmm30,zmm29,dword bcst [rdx-0x204],0x7b
    vshuff64x2 zmm30,zmm29,qword bcst [rcx],0x7b
    vshuff64x2 zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    vshuff64x2 zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    vshuff64x2 zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    vshuff64x2 zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    vshufi32x4 zmm30,zmm29,dword bcst [rcx],0x7b
    vshufi32x4 zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    vshufi32x4 zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    vshufi32x4 zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    vshufi32x4 zmm30,zmm29,dword bcst [rdx-0x204],0x7b
    vshufi64x2 zmm30,zmm29,qword bcst [rcx],0x7b
    vshufi64x2 zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    vshufi64x2 zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    vshufi64x2 zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    vshufi64x2 zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    valignq zmm30,zmm29,qword bcst [rcx],0x7b
    valignq zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    valignq zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    valignq zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    valignq zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    vscalefpd zmm30,zmm29,qword bcst [rcx]
    vscalefpd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vscalefpd zmm30,zmm29,qword bcst [rdx+0x400]
    vscalefpd zmm30,zmm29,qword bcst [rdx-0x400]
    vscalefpd zmm30,zmm29,qword bcst [rdx-0x408]

    vscalefps zmm30,zmm29,dword bcst [rcx]
    vscalefps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vscalefps zmm30,zmm29,dword bcst [rdx+0x200]
    vscalefps zmm30,zmm29,dword bcst [rdx-0x200]
    vscalefps zmm30,zmm29,dword bcst [rdx-0x204]

    vfixupimmps zmm30,zmm29,dword bcst [rcx],0x7b
    vfixupimmps zmm30,zmm29,dword bcst [rdx+0x1fc],0x7b
    vfixupimmps zmm30,zmm29,dword bcst [rdx+0x200],0x7b
    vfixupimmps zmm30,zmm29,dword bcst [rdx-0x200],0x7b
    vfixupimmps zmm30,zmm29,dword bcst [rdx-0x204],0x7b

    vfixupimmpd zmm30,zmm29,qword bcst [rcx],0x7b
    vfixupimmpd zmm30,zmm29,qword bcst [rdx+0x3f8],0x7b
    vfixupimmpd zmm30,zmm29,qword bcst [rdx+0x400],0x7b
    vfixupimmpd zmm30,zmm29,qword bcst [rdx-0x400],0x7b
    vfixupimmpd zmm30,zmm29,qword bcst [rdx-0x408],0x7b

    vprolvd zmm30,zmm29,dword bcst [rcx]
    vprolvd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vprolvd zmm30,zmm29,dword bcst [rdx+0x200]
    vprolvd zmm30,zmm29,dword bcst [rdx-0x200]
    vprolvd zmm30,zmm29,dword bcst [rdx-0x204]

    vprold zmm30,dword bcst [rcx],0x7b
    vprold zmm30,dword bcst [rdx+0x1fc],0x7b
    vprold zmm30,dword bcst [rdx+0x200],0x7b
    vprold zmm30,dword bcst [rdx-0x200],0x7b
    vprold zmm30,dword bcst [rdx-0x204],0x7b

    vprolvq zmm30,zmm29,qword bcst [rcx]
    vprolvq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vprolvq zmm30,zmm29,qword bcst [rdx+0x400]
    vprolvq zmm30,zmm29,qword bcst [rdx-0x400]
    vprolvq zmm30,zmm29,qword bcst [rdx-0x408]

    vprolq zmm30,qword bcst [rcx],0x7b
    vprolq zmm30,qword bcst [rdx+0x3f8],0x7b
    vprolq zmm30,qword bcst [rdx+0x400],0x7b
    vprolq zmm30,qword bcst [rdx-0x400],0x7b
    vprolq zmm30,qword bcst [rdx-0x408],0x7b

    vprorvd zmm30,zmm29,dword bcst [rcx]
    vprorvd zmm30,zmm29,dword bcst [rdx+0x1fc]
    vprorvd zmm30,zmm29,dword bcst [rdx+0x200]
    vprorvd zmm30,zmm29,dword bcst [rdx-0x200]
    vprorvd zmm30,zmm29,dword bcst [rdx-0x204]

    vprord zmm30,dword bcst [rcx],0x7b
    vprord zmm30,dword bcst [rdx+0x1fc],0x7b
    vprord zmm30,dword bcst [rdx+0x200],0x7b
    vprord zmm30,dword bcst [rdx-0x200],0x7b
    vprord zmm30,dword bcst [rdx-0x204],0x7b

    vprorvq zmm30,zmm29,qword bcst [rcx]
    vprorvq zmm30,zmm29,qword bcst [rdx+0x3f8]
    vprorvq zmm30,zmm29,qword bcst [rdx+0x400]
    vprorvq zmm30,zmm29,qword bcst [rdx-0x400]
    vprorvq zmm30,zmm29,qword bcst [rdx-0x408]

    vprorq zmm30,qword bcst [rcx],0x7b
    vprorq zmm30,qword bcst [rdx+0x3f8],0x7b
    vprorq zmm30,qword bcst [rdx+0x400],0x7b
    vprorq zmm30,qword bcst [rdx-0x400],0x7b
    vprorq zmm30,qword bcst [rdx-0x408],0x7b

    vpermi2d zmm30,zmm29,dword bcst [rcx]
    vpermi2d zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpermi2d zmm30,zmm29,dword bcst [rdx+0x200]
    vpermi2d zmm30,zmm29,dword bcst [rdx-0x200]
    vpermi2d zmm30,zmm29,dword bcst [rdx-0x204]

    vpermi2q zmm30,zmm29,qword bcst [rcx]
    vpermi2q zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpermi2q zmm30,zmm29,qword bcst [rdx+0x400]
    vpermi2q zmm30,zmm29,qword bcst [rdx-0x400]
    vpermi2q zmm30,zmm29,qword bcst [rdx-0x408]

    vpermi2ps zmm30,zmm29,dword bcst [rcx]
    vpermi2ps zmm30,zmm29,dword bcst [rdx+0x1fc]
    vpermi2ps zmm30,zmm29,dword bcst [rdx+0x200]
    vpermi2ps zmm30,zmm29,dword bcst [rdx-0x200]
    vpermi2ps zmm30,zmm29,dword bcst [rdx-0x204]

    vpermi2pd zmm30,zmm29,qword bcst [rcx]
    vpermi2pd zmm30,zmm29,qword bcst [rdx+0x3f8]
    vpermi2pd zmm30,zmm29,qword bcst [rdx+0x400]
    vpermi2pd zmm30,zmm29,qword bcst [rdx-0x400]
    vpermi2pd zmm30,zmm29,qword bcst [rdx-0x408]


    vaddpd zmm0,zmm1,qword bcst [rcx]
    vaddpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vaddpd zmm0,zmm1,qword bcst [rdx+0x400]
    vaddpd zmm0,zmm1,qword bcst [rdx-0x400]
    vaddpd zmm0,zmm1,qword bcst [rdx-0x408]

    vaddps zmm0,zmm1,dword bcst [rcx]
    vaddps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vaddps zmm0,zmm1,dword bcst [rdx+0x200]
    vaddps zmm0,zmm1,dword bcst [rdx-0x200]
    vaddps zmm0,zmm1,dword bcst [rdx-0x204]

    vdivpd zmm0,zmm1,qword bcst [rcx]
    vdivpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vdivpd zmm0,zmm1,qword bcst [rdx+0x400]
    vdivpd zmm0,zmm1,qword bcst [rdx-0x400]
    vdivpd zmm0,zmm1,qword bcst [rdx-0x408]

    vdivps zmm0,zmm1,dword bcst [rcx]
    vdivps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vdivps zmm0,zmm1,dword bcst [rdx+0x200]
    vdivps zmm0,zmm1,dword bcst [rdx-0x200]
    vdivps zmm0,zmm1,dword bcst [rdx-0x204]

    vmaxpd zmm0,zmm1,qword bcst [rcx]
    vmaxpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vmaxpd zmm0,zmm1,qword bcst [rdx+0x400]
    vmaxpd zmm0,zmm1,qword bcst [rdx-0x400]
    vmaxpd zmm0,zmm1,qword bcst [rdx-0x408]

    vmaxps zmm0,zmm1,dword bcst [rcx]
    vmaxps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vmaxps zmm0,zmm1,dword bcst [rdx+0x200]
    vmaxps zmm0,zmm1,dword bcst [rdx-0x200]
    vmaxps zmm0,zmm1,dword bcst [rdx-0x204]

    vminpd zmm0,zmm1,qword bcst [rcx]
    vminpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vminpd zmm0,zmm1,qword bcst [rdx+0x400]
    vminpd zmm0,zmm1,qword bcst [rdx-0x400]
    vminpd zmm0,zmm1,qword bcst [rdx-0x408]

    vminps zmm0,zmm1,dword bcst [rcx]
    vminps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vminps zmm0,zmm1,dword bcst [rdx+0x200]
    vminps zmm0,zmm1,dword bcst [rdx-0x200]
    vminps zmm0,zmm1,dword bcst [rdx-0x204]

    vmulpd zmm0,zmm1,qword bcst [rcx]
    vmulpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vmulpd zmm0,zmm1,qword bcst [rdx+0x400]
    vmulpd zmm0,zmm1,qword bcst [rdx-0x400]
    vmulpd zmm0,zmm1,qword bcst [rdx-0x408]

    vmulps zmm0,zmm1,dword bcst [rcx]
    vmulps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vmulps zmm0,zmm1,dword bcst [rdx+0x200]
    vmulps zmm0,zmm1,dword bcst [rdx-0x200]
    vmulps zmm0,zmm1,dword bcst [rdx-0x204]

    vsubpd zmm0,zmm1,qword bcst [rcx]
    vsubpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vsubpd zmm0,zmm1,qword bcst [rdx+0x400]
    vsubpd zmm0,zmm1,qword bcst [rdx-0x400]
    vsubpd zmm0,zmm1,qword bcst [rdx-0x408]

    vsubps zmm0,zmm1,dword bcst [rcx]
    vsubps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vsubps zmm0,zmm1,dword bcst [rdx+0x200]
    vsubps zmm0,zmm1,dword bcst [rdx-0x200]
    vsubps zmm0,zmm1,dword bcst [rdx-0x204]

    vsqrtpd zmm0,qword bcst [rcx]
    vsqrtpd zmm0,qword bcst [rdx+0x3f8]
    vsqrtpd zmm0,qword bcst [rdx+0x400]
    vsqrtpd zmm0,qword bcst [rdx-0x400]
    vsqrtpd zmm0,qword bcst [rdx-0x408]

    vsqrtps zmm0,dword bcst [rcx]
    vsqrtps zmm0,dword bcst [rdx+0x1fc]
    vsqrtps zmm0,dword bcst [rdx+0x200]
    vsqrtps zmm0,dword bcst [rdx-0x200]
    vsqrtps zmm0,dword bcst [rdx-0x204]

    vcmppd k5,zmm0,qword bcst [rcx],0x7b
    vcmppd k5,zmm0,qword bcst [rdx+0x3f8],0x7b
    vcmppd k5,zmm0,qword bcst [rdx+0x400],0x7b
    vcmppd k5,zmm0,qword bcst [rdx-0x400],0x7b
    vcmppd k5,zmm0,qword bcst [rdx-0x408],0x7b

    vcmpps k5,zmm0,dword bcst [rcx],0x7b
    vcmpps k5,zmm0,dword bcst [rdx+0x1fc],0x7b
    vcmpps k5,zmm0,dword bcst [rdx+0x200],0x7b
    vcmpps k5,zmm0,dword bcst [rdx-0x200],0x7b
    vcmpps k5,zmm0,dword bcst [rdx-0x204],0x7b

    vcvtdq2pd zmm0{k7},dword bcst [rcx]
    vcvtdq2pd zmm0{k7},dword bcst [rdx+0x1fc]
    vcvtdq2pd zmm0{k7},dword bcst [rdx+0x200]
    vcvtdq2pd zmm0{k7},dword bcst [rdx-0x200]
    vcvtdq2pd zmm0{k7},dword bcst [rdx-0x204]

    vcvtdq2ps zmm0,dword bcst [rcx]
    vcvtdq2ps zmm0,dword bcst [rdx+0x1fc]
    vcvtdq2ps zmm0,dword bcst [rdx+0x200]
    vcvtdq2ps zmm0,dword bcst [rdx-0x200]
    vcvtdq2ps zmm0,dword bcst [rdx-0x204]

    vcvtpd2dq ymm0{k7},qword bcst [rcx]
    vcvtpd2dq ymm0{k7},qword bcst [rdx+0x3f8]
    vcvtpd2dq ymm0{k7},qword bcst [rdx+0x400]
    vcvtpd2dq ymm0{k7},qword bcst [rdx-0x400]
    vcvtpd2dq ymm0{k7},qword bcst [rdx-0x408]

    vcvtpd2ps ymm0{k7},qword bcst [rcx]
    vcvtpd2ps ymm0{k7},qword bcst [rdx+0x3f8]
    vcvtpd2ps ymm0{k7},qword bcst [rdx+0x400]
    vcvtpd2ps ymm0{k7},qword bcst [rdx-0x400]
    vcvtpd2ps ymm0{k7},qword bcst [rdx-0x408]

    vpabsd zmm0,dword bcst [rcx]
    vpabsd zmm0,dword bcst [rdx+0x1fc]
    vpabsd zmm0,dword bcst [rdx+0x200]
    vpabsd zmm0,dword bcst [rdx-0x200]
    vpabsd zmm0,dword bcst [rdx-0x204]

    vpaddd zmm0,zmm1,dword bcst [rcx]
    vpaddd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpaddd zmm0,zmm1,dword bcst [rdx+0x200]
    vpaddd zmm0,zmm1,dword bcst [rdx-0x200]
    vpaddd zmm0,zmm1,dword bcst [rdx-0x204]

    vpaddq zmm0,zmm1,qword bcst [rcx]
    vpaddq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpaddq zmm0,zmm1,qword bcst [rdx+0x400]
    vpaddq zmm0,zmm1,qword bcst [rdx-0x400]
    vpaddq zmm0,zmm1,qword bcst [rdx-0x408]

    vpcmpeqd k5,zmm0,dword bcst [rcx]
    vpcmpeqd k5,zmm0,dword bcst [rdx+0x1fc]
    vpcmpeqd k5,zmm0,dword bcst [rdx+0x200]
    vpcmpeqd k5,zmm0,dword bcst [rdx-0x200]
    vpcmpeqd k5,zmm0,dword bcst [rdx-0x204]

    vpcmpgtd k5,zmm0,dword bcst [rcx]
    vpcmpgtd k5,zmm0,dword bcst [rdx+0x1fc]
    vpcmpgtd k5,zmm0,dword bcst [rdx+0x200]
    vpcmpgtd k5,zmm0,dword bcst [rdx-0x200]
    vpcmpgtd k5,zmm0,dword bcst [rdx-0x204]

    vpcmpgtq k5,zmm0,qword bcst [rcx]
    vpcmpgtq k5,zmm0,qword bcst [rdx+0x3f8]
    vpcmpgtq k5,zmm0,qword bcst [rdx+0x400]
    vpcmpgtq k5,zmm0,qword bcst [rdx-0x400]
    vpcmpgtq k5,zmm0,qword bcst [rdx-0x408]

    vpmaxsd zmm0,zmm1,dword bcst [rcx]
    vpmaxsd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpmaxsd zmm0,zmm1,dword bcst [rdx+0x200]
    vpmaxsd zmm0,zmm1,dword bcst [rdx-0x200]
    vpmaxsd zmm0,zmm1,dword bcst [rdx-0x204]

    vpmaxud zmm0,zmm1,dword bcst [rcx]
    vpmaxud zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpmaxud zmm0,zmm1,dword bcst [rdx+0x200]
    vpmaxud zmm0,zmm1,dword bcst [rdx-0x200]
    vpmaxud zmm0,zmm1,dword bcst [rdx-0x204]

    vpminsd zmm0,zmm1,dword bcst [rcx]
    vpminsd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpminsd zmm0,zmm1,dword bcst [rdx+0x200]
    vpminsd zmm0,zmm1,dword bcst [rdx-0x200]
    vpminsd zmm0,zmm1,dword bcst [rdx-0x204]

    vpminud zmm0,zmm1,dword bcst [rcx]
    vpminud zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpminud zmm0,zmm1,dword bcst [rdx+0x200]
    vpminud zmm0,zmm1,dword bcst [rdx-0x200]
    vpminud zmm0,zmm1,dword bcst [rdx-0x204]

    vpmuldq zmm0,zmm1,qword bcst [rcx]
    vpmuldq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpmuldq zmm0,zmm1,qword bcst [rdx+0x400]
    vpmuldq zmm0,zmm1,qword bcst [rdx-0x400]
    vpmuldq zmm0,zmm1,qword bcst [rdx-0x408]

    vpmulld zmm0,zmm1,dword bcst [rcx]
    vpmulld zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpmulld zmm0,zmm1,dword bcst [rdx+0x200]
    vpmulld zmm0,zmm1,dword bcst [rdx-0x200]
    vpmulld zmm0,zmm1,dword bcst [rdx-0x204]

    vpmuludq zmm0,zmm1,qword bcst [rcx]
    vpmuludq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpmuludq zmm0,zmm1,qword bcst [rdx+0x400]
    vpmuludq zmm0,zmm1,qword bcst [rdx-0x400]
    vpmuludq zmm0,zmm1,qword bcst [rdx-0x408]

    vpshufd zmm0,dword bcst [rcx],0x7b
    vpshufd zmm0,dword bcst [rdx+0x1fc],0x7b
    vpshufd zmm0,dword bcst [rdx+0x200],0x7b
    vpshufd zmm0,dword bcst [rdx-0x200],0x7b
    vpshufd zmm0,dword bcst [rdx-0x204],0x7b

    vcvtps2dq zmm0,dword bcst [rcx]
    vcvtps2dq zmm0,dword bcst [rdx+0x1fc]
    vcvtps2dq zmm0,dword bcst [rdx+0x200]
    vcvtps2dq zmm0,dword bcst [rdx-0x200]
    vcvtps2dq zmm0,dword bcst [rdx-0x204]

    vcvtps2pd zmm0{k7},dword bcst [rcx]
    vcvtps2pd zmm0{k7},dword bcst [rdx+0x1fc]
    vcvtps2pd zmm0{k7},dword bcst [rdx+0x200]
    vcvtps2pd zmm0{k7},dword bcst [rdx-0x200]
    vcvtps2pd zmm0{k7},dword bcst [rdx-0x204]

    vpsubd zmm0,zmm1,dword bcst [rcx]
    vpsubd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpsubd zmm0,zmm1,dword bcst [rdx+0x200]
    vpsubd zmm0,zmm1,dword bcst [rdx-0x200]
    vpsubd zmm0,zmm1,dword bcst [rdx-0x204]

    vpsubq zmm0,zmm1,qword bcst [rcx]
    vpsubq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpsubq zmm0,zmm1,qword bcst [rdx+0x400]
    vpsubq zmm0,zmm1,qword bcst [rdx-0x400]
    vpsubq zmm0,zmm1,qword bcst [rdx-0x408]

    vpunpckhdq zmm0,zmm1,dword bcst [rcx]
    vpunpckhdq zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpunpckhdq zmm0,zmm1,dword bcst [rdx+0x200]
    vpunpckhdq zmm0,zmm1,dword bcst [rdx-0x200]
    vpunpckhdq zmm0,zmm1,dword bcst [rdx-0x204]

    vpunpckhqdq zmm0,zmm1,qword bcst [rcx]
    vpunpckhqdq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpunpckhqdq zmm0,zmm1,qword bcst [rdx+0x400]
    vpunpckhqdq zmm0,zmm1,qword bcst [rdx-0x400]
    vpunpckhqdq zmm0,zmm1,qword bcst [rdx-0x408]

    vpunpckldq zmm0,zmm1,dword bcst [rcx]
    vpunpckldq zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpunpckldq zmm0,zmm1,dword bcst [rdx+0x200]
    vpunpckldq zmm0,zmm1,dword bcst [rdx-0x200]
    vpunpckldq zmm0,zmm1,dword bcst [rdx-0x204]

    vpunpcklqdq zmm0,zmm1,qword bcst [rcx]
    vpunpcklqdq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpunpcklqdq zmm0,zmm1,qword bcst [rdx+0x400]
    vpunpcklqdq zmm0,zmm1,qword bcst [rdx-0x400]
    vpunpcklqdq zmm0,zmm1,qword bcst [rdx-0x408]

    vshufpd zmm0,zmm1,qword bcst [rcx],0x7b
    vshufpd zmm0,zmm1,qword bcst [rdx+0x3f8],0x7b
    vshufpd zmm0,zmm1,qword bcst [rdx+0x400],0x7b
    vshufpd zmm0,zmm1,qword bcst [rdx-0x400],0x7b
    vshufpd zmm0,zmm1,qword bcst [rdx-0x408],0x7b

    vshufps zmm0,zmm1,dword bcst [rcx],0x7b
    vshufps zmm0,zmm1,dword bcst [rdx+0x1fc],0x7b
    vshufps zmm0,zmm1,dword bcst [rdx+0x200],0x7b
    vshufps zmm0,zmm1,dword bcst [rdx-0x200],0x7b
    vshufps zmm0,zmm1,dword bcst [rdx-0x204],0x7b

    vunpckhpd zmm0,zmm1,qword bcst [rcx]
    vunpckhpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vunpckhpd zmm0,zmm1,qword bcst [rdx+0x400]
    vunpckhpd zmm0,zmm1,qword bcst [rdx-0x400]
    vunpckhpd zmm0,zmm1,qword bcst [rdx-0x408]

    vunpckhps zmm0,zmm1,dword bcst [rcx]
    vunpckhps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vunpckhps zmm0,zmm1,dword bcst [rdx+0x200]
    vunpckhps zmm0,zmm1,dword bcst [rdx-0x200]
    vunpckhps zmm0,zmm1,dword bcst [rdx-0x204]

    vunpcklpd zmm0,zmm1,qword bcst [rcx]
    vunpcklpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vunpcklpd zmm0,zmm1,qword bcst [rdx+0x400]
    vunpcklpd zmm0,zmm1,qword bcst [rdx-0x400]
    vunpcklpd zmm0,zmm1,qword bcst [rdx-0x408]

    vunpcklps zmm0,zmm1,dword bcst [rcx]
    vunpcklps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vunpcklps zmm0,zmm1,dword bcst [rdx+0x200]
    vunpcklps zmm0,zmm1,dword bcst [rdx-0x200]
    vunpcklps zmm0,zmm1,dword bcst [rdx-0x204]

    vpandd zmm0,zmm1,dword bcst [rcx]
    vpandd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpandd zmm0,zmm1,dword bcst [rdx+0x200]
    vpandd zmm0,zmm1,dword bcst [rdx-0x200]
    vpandd zmm0,zmm1,dword bcst [rdx-0x204]

    vpandq zmm0,zmm1,qword bcst [rcx]
    vpandq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpandq zmm0,zmm1,qword bcst [rdx+0x400]
    vpandq zmm0,zmm1,qword bcst [rdx-0x400]
    vpandq zmm0,zmm1,qword bcst [rdx-0x408]

    vpandnd zmm0,zmm1,dword bcst [rcx]
    vpandnd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpandnd zmm0,zmm1,dword bcst [rdx+0x200]
    vpandnd zmm0,zmm1,dword bcst [rdx-0x200]
    vpandnd zmm0,zmm1,dword bcst [rdx-0x204]

    vpandnq zmm0,zmm1,qword bcst [rcx]
    vpandnq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpandnq zmm0,zmm1,qword bcst [rdx+0x400]
    vpandnq zmm0,zmm1,qword bcst [rdx-0x400]
    vpandnq zmm0,zmm1,qword bcst [rdx-0x408]

    vpxord zmm0,zmm1,dword bcst [rcx]
    vpxord zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpxord zmm0,zmm1,dword bcst [rdx+0x200]
    vpxord zmm0,zmm1,dword bcst [rdx-0x200]
    vpxord zmm0,zmm1,dword bcst [rdx-0x204]

    vpxorq zmm0,zmm1,qword bcst [rcx]
    vpxorq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpxorq zmm0,zmm1,qword bcst [rdx+0x400]
    vpxorq zmm0,zmm1,qword bcst [rdx-0x400]
    vpxorq zmm0,zmm1,qword bcst [rdx-0x408]

    vpconflictd zmm0,dword bcst [rcx]
    vpconflictd zmm0,dword bcst [rdx+0x1fc]
    vpconflictd zmm0,dword bcst [rdx+0x200]
    vpconflictd zmm0,dword bcst [rdx-0x200]
    vpconflictd zmm0,dword bcst [rdx-0x204]

    vptestnmd	k5,zmm1,dword bcst [rcx]
    vptestnmd	k5,zmm1,dword bcst [rdx+0x1fc]
    vptestnmd	k5,zmm1,dword bcst [rdx+0x200]
    vptestnmd	k5,zmm1,dword bcst [rdx-0x200]
    vptestnmd	k5,zmm1,dword bcst [rdx-0x204]

    vptestnmq	k5,zmm1,qword bcst [rcx]
    vptestnmq	k5,zmm1,qword bcst [rdx+0x3f8]
    vptestnmq	k5,zmm1,qword bcst [rdx+0x400]
    vptestnmq	k5,zmm1,qword bcst [rdx-0x400]
    vptestnmq	k5,zmm1,qword bcst [rdx-0x408]

    vrsqrt14ps zmm0,dword bcst [rcx]
    vrsqrt14ps zmm0,dword bcst [rdx+0x1fc]
    vrsqrt14ps zmm0,dword bcst [rdx+0x200]
    vrsqrt14ps zmm0,dword bcst [rdx-0x200]
    vrsqrt14ps zmm0,dword bcst [rdx-0x204]

    vrsqrt14ps zmm0,dword bcst [rcx]
    vrsqrt14ps zmm0,dword bcst [rdx+0x1fc]
    vrsqrt14ps zmm0,dword bcst [rdx+0x200]
    vrsqrt14ps zmm0,dword bcst [rdx-0x200]
    vrsqrt14ps zmm0,dword bcst [rdx-0x204]


    vcvtpd2udq ymm0{k7},qword bcst [rcx]
    vcvtpd2udq ymm0{k7},qword bcst [rdx+0x3f8]
    vcvtpd2udq ymm0{k7},qword bcst [rdx+0x400]
    vcvtpd2udq ymm0{k7},qword bcst [rdx-0x400]
    vcvtpd2udq ymm0{k7},qword bcst [rdx-0x408]

    vcvtps2udq zmm0,dword bcst [rcx]
    vcvtps2udq zmm0,dword bcst [rdx+0x1fc]
    vcvtps2udq zmm0,dword bcst [rdx+0x200]
    vcvtps2udq zmm0,dword bcst [rdx-0x200]
    vcvtps2udq zmm0,dword bcst [rdx-0x204]

    vcvttpd2udq ymm0{k7},qword bcst [rcx]
    vcvttpd2udq ymm0{k7},qword bcst [rdx+0x3f8]
    vcvttpd2udq ymm0{k7},qword bcst [rdx+0x400]
    vcvttpd2udq ymm0{k7},qword bcst [rdx-0x400]
    vcvttpd2udq ymm0{k7},qword bcst [rdx-0x408]
    vcvttps2udq zmm0,dword bcst [rcx]
    vcvttps2udq zmm0,dword bcst [rdx+0x1fc]
    vcvttps2udq zmm0,dword bcst [rdx+0x200]
    vcvttps2udq zmm0,dword bcst [rdx-0x200]
    vcvttps2udq zmm0,dword bcst [rdx-0x204]

    vcvtudq2pd zmm0{k7},dword bcst [rcx]
    vcvtudq2pd zmm0{k7},dword bcst [rdx+0x1fc]
    vcvtudq2pd zmm0{k7},dword bcst [rdx+0x200]
    vcvtudq2pd zmm0{k7},dword bcst [rdx-0x200]
    vcvtudq2pd zmm0{k7},dword bcst [rdx-0x204]

    vcvtudq2ps zmm0,dword bcst [rcx]
    vcvtudq2ps zmm0,dword bcst [rdx+0x1fc]
    vcvtudq2ps zmm0,dword bcst [rdx+0x200]
    vcvtudq2ps zmm0,dword bcst [rdx-0x200]
    vcvtudq2ps zmm0,dword bcst [rdx-0x204]



    valignd zmm0,zmm1,dword bcst [rcx],0x7b
    valignd zmm0,zmm1,dword bcst [rdx+0x1fc],0x7b
    valignd zmm0,zmm1,dword bcst [rdx+0x200],0x7b
    valignd zmm0,zmm1,dword bcst [rdx-0x200],0x7b
    valignd zmm0,zmm1,dword bcst [rdx-0x204],0x7b

    vblendmpd zmm0,zmm1,qword bcst [rcx]
    vblendmpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vblendmpd zmm0,zmm1,qword bcst [rdx+0x400]
    vblendmpd zmm0,zmm1,qword bcst [rdx-0x400]
    vblendmpd zmm0,zmm1,qword bcst [rdx-0x408]

    vblendmps zmm0,zmm1,dword bcst [rcx]
    vblendmps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vblendmps zmm0,zmm1,dword bcst [rdx+0x200]
    vblendmps zmm0,zmm1,dword bcst [rdx-0x200]
    vblendmps zmm0,zmm1,dword bcst [rdx-0x204]

    vcvttpd2dq ymm0{k7},qword bcst [rcx]
    vcvttpd2dq ymm0{k7},qword bcst [rdx+0x3f8]
    vcvttpd2dq ymm0{k7},qword bcst [rdx+0x400]
    vcvttpd2dq ymm0{k7},qword bcst [rdx-0x400]
    vcvttpd2dq ymm0{k7},qword bcst [rdx-0x408]

    vcvttps2dq zmm0,dword bcst [rcx]
    vcvttps2dq zmm0,dword bcst [rdx+0x1fc]
    vcvttps2dq zmm0,dword bcst [rdx+0x200]
    vcvttps2dq zmm0,dword bcst [rdx-0x200]
    vcvttps2dq zmm0,dword bcst [rdx-0x204]

    vfmadd132pd zmm0,zmm1,qword bcst [rcx]
    vfmadd132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmadd132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmadd132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmadd132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmadd132ps zmm0,zmm1,dword bcst [rcx]
    vfmadd132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmadd132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmadd132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmadd132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmadd213pd zmm0,zmm1,qword bcst [rcx]
    vfmadd213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmadd213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmadd213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmadd213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmadd213ps zmm0,zmm1,dword bcst [rcx]
    vfmadd213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmadd213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmadd213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmadd213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmadd231pd zmm0,zmm1,qword bcst [rcx]
    vfmadd231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmadd231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmadd231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmadd231pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmadd231ps zmm0,zmm1,dword bcst [rcx]
    vfmadd231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmadd231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmadd231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmadd231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmaddsub132pd zmm0,zmm1,qword bcst [rcx]
    vfmaddsub132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmaddsub132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmaddsub132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmaddsub132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmaddsub132ps zmm0,zmm1,dword bcst [rcx]
    vfmaddsub132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmaddsub132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmaddsub132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmaddsub132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmaddsub213pd zmm0,zmm1,qword bcst [rcx]
    vfmaddsub213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmaddsub213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmaddsub213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmaddsub213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmaddsub213ps zmm0,zmm1,dword bcst [rcx]
    vfmaddsub213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmaddsub213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmaddsub213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmaddsub213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmaddsub231pd zmm0,zmm1,qword bcst [rcx]
    vfmaddsub231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmaddsub231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmaddsub231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmaddsub231pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmaddsub231ps zmm0,zmm1,dword bcst [rcx]
    vfmaddsub231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmaddsub231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmaddsub231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmaddsub231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsub132pd zmm0,zmm1,qword bcst [rcx]
    vfmsub132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsub132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsub132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsub132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsub132ps zmm0,zmm1,dword bcst [rcx]
    vfmsub132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsub132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsub132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsub132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsub213pd zmm0,zmm1,qword bcst [rcx]
    vfmsub213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsub213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsub213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsub213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsub213ps zmm0,zmm1,dword bcst [rcx]
    vfmsub213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsub213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsub213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsub213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsub231pd zmm0,zmm1,qword bcst [rcx]
    vfmsub231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsub231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsub231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsub231pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsub231ps zmm0,zmm1,dword bcst [rcx]
    vfmsub231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsub231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsub231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsub231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsubadd132pd zmm0,zmm1,qword bcst [rcx]
    vfmsubadd132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsubadd132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsubadd132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsubadd132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsubadd132ps zmm0,zmm1,dword bcst [rcx]
    vfmsubadd132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsubadd132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsubadd132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsubadd132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsubadd213pd zmm0,zmm1,qword bcst [rcx]
    vfmsubadd213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsubadd213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsubadd213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsubadd213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsubadd213ps zmm0,zmm1,dword bcst [rcx]
    vfmsubadd213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsubadd213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsubadd213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsubadd213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfmsubadd231pd zmm0,zmm1,qword bcst [rcx]
    vfmsubadd231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfmsubadd231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfmsubadd231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfmsubadd231pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfmsubadd231ps zmm0,zmm1,dword bcst [rcx]
    vfmsubadd231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfmsubadd231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfmsubadd231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfmsubadd231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmadd132pd zmm0,zmm1,qword bcst [rcx]
    vfnmadd132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmadd132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmadd132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmadd132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfnmadd132ps zmm0,zmm1,dword bcst [rcx]
    vfnmadd132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmadd132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmadd132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmadd132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmadd213pd zmm0,zmm1,qword bcst [rcx]
    vfnmadd213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmadd213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmadd213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmadd213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfnmadd213ps zmm0,zmm1,dword bcst [rcx]
    vfnmadd213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmadd213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmadd213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmadd213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmadd231pd zmm0,zmm1,qword bcst [rcx]
    vfnmadd231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmadd231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmadd231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmadd231pd zmm0,zmm1,qword bcst [rdx-0x408]
    vfnmadd231ps zmm0,zmm1,dword bcst [rcx]
    vfnmadd231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmadd231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmadd231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmadd231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmsub132pd zmm0,zmm1,qword bcst [rcx]
    vfnmsub132pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmsub132pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmsub132pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmsub132pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfnmsub132ps zmm0,zmm1,dword bcst [rcx]
    vfnmsub132ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmsub132ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmsub132ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmsub132ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmsub213pd zmm0,zmm1,qword bcst [rcx]
    vfnmsub213pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmsub213pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmsub213pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmsub213pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfnmsub213ps zmm0,zmm1,dword bcst [rcx]
    vfnmsub213ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmsub213ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmsub213ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmsub213ps zmm0,zmm1,dword bcst [rdx-0x204]

    vfnmsub231pd zmm0,zmm1,qword bcst [rcx]
    vfnmsub231pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vfnmsub231pd zmm0,zmm1,qword bcst [rdx+0x400]
    vfnmsub231pd zmm0,zmm1,qword bcst [rdx-0x400]
    vfnmsub231pd zmm0,zmm1,qword bcst [rdx-0x408]

    vfnmsub231ps zmm0,zmm1,dword bcst [rcx]
    vfnmsub231ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vfnmsub231ps zmm0,zmm1,dword bcst [rdx+0x200]
    vfnmsub231ps zmm0,zmm1,dword bcst [rdx-0x200]
    vfnmsub231ps zmm0,zmm1,dword bcst [rdx-0x204]

    vpabsq zmm0,qword bcst [rcx]
    vpabsq zmm0,qword bcst [rdx+0x3f8]
    vpabsq zmm0,qword bcst [rdx+0x400]
    vpabsq zmm0,qword bcst [rdx-0x400]
    vpabsq zmm0,qword bcst [rdx-0x408]

    vpblendmd zmm0,zmm1,dword bcst [rcx]
    vpblendmd zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpblendmd zmm0,zmm1,dword bcst [rdx+0x200]
    vpblendmd zmm0,zmm1,dword bcst [rdx-0x200]
    vpblendmd zmm0,zmm1,dword bcst [rdx-0x204]

    vpblendmq zmm0,zmm1,qword bcst [rcx]
    vpblendmq zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpblendmq zmm0,zmm1,qword bcst [rdx+0x400]
    vpblendmq zmm0,zmm1,qword bcst [rdx-0x400]
    vpblendmq zmm0,zmm1,qword bcst [rdx-0x408]

    vscalefpd zmm0,zmm1,qword bcst [rcx]
    vscalefpd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vscalefpd zmm0,zmm1,qword bcst [rdx+0x400]
    vscalefpd zmm0,zmm1,qword bcst [rdx-0x400]
    vscalefpd zmm0,zmm1,qword bcst [rdx-0x408]

    vscalefps zmm0,zmm1,dword bcst [rcx]
    vscalefps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vscalefps zmm0,zmm1,dword bcst [rdx+0x200]
    vscalefps zmm0,zmm1,dword bcst [rdx-0x200]
    vscalefps zmm0,zmm1,dword bcst [rdx-0x204]

    vfixupimmps zmm0,zmm1,dword bcst [rcx],0x7b
    vfixupimmps zmm0,zmm1,dword bcst [rdx+0x1fc],0x7b
    vfixupimmps zmm0,zmm1,dword bcst [rdx+0x200],0x7b
    vfixupimmps zmm0,zmm1,dword bcst [rdx-0x200],0x7b
    vfixupimmps zmm0,zmm1,dword bcst [rdx-0x204],0x7b

    vfixupimmpd zmm0,zmm1,qword bcst [rcx],0x7b
    vfixupimmpd zmm0,zmm1,qword bcst [rdx+0x3f8],0x7b
    vfixupimmpd zmm0,zmm1,qword bcst [rdx+0x400],0x7b
    vfixupimmpd zmm0,zmm1,qword bcst [rdx-0x400],0x7b
    vfixupimmpd zmm0,zmm1,qword bcst [rdx-0x408],0x7b

    vpermi2d zmm0,zmm1,dword bcst [rcx]
    vpermi2d zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpermi2d zmm0,zmm1,dword bcst [rdx+0x200]
    vpermi2d zmm0,zmm1,dword bcst [rdx-0x200]
    vpermi2d zmm0,zmm1,dword bcst [rdx-0x204]

    vpermi2q zmm0,zmm1,qword bcst [rcx]
    vpermi2q zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpermi2q zmm0,zmm1,qword bcst [rdx+0x400]
    vpermi2q zmm0,zmm1,qword bcst [rdx-0x400]
    vpermi2q zmm0,zmm1,qword bcst [rdx-0x408]

    vpermi2ps zmm0,zmm1,dword bcst [rcx]
    vpermi2ps zmm0,zmm1,dword bcst [rdx+0x1fc]
    vpermi2ps zmm0,zmm1,dword bcst [rdx+0x200]
    vpermi2ps zmm0,zmm1,dword bcst [rdx-0x200]
    vpermi2ps zmm0,zmm1,dword bcst [rdx-0x204]

    vpermi2pd zmm0,zmm1,qword bcst [rcx]
    vpermi2pd zmm0,zmm1,qword bcst [rdx+0x3f8]
    vpermi2pd zmm0,zmm1,qword bcst [rdx+0x400]
    vpermi2pd zmm0,zmm1,qword bcst [rdx-0x400]
    vpermi2pd zmm0,zmm1,qword bcst [rdx-0x408]

    end
