;
; v2.26 -- AVX-512
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code


    vaddpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vaddps zmm30,zmm29,dword ptr [rcx]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vdivpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vdivps zmm30,zmm29,dword ptr [rcx]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vmaxpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vmaxps zmm30,zmm29,dword ptr [rcx]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vminpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vminps zmm30,zmm29,dword ptr [rcx]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vmulpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vmulps zmm30,zmm29,dword ptr [rcx]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vsubpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vsubps zmm30,zmm29,dword ptr [rcx]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vsqrtpd zmm30,qword ptr [rcx]{1to8}
    vsqrtpd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vsqrtpd zmm30,qword ptr [rdx+0x400]{1to8}
    vsqrtpd zmm30,qword ptr [rdx-0x400]{1to8}
    vsqrtpd zmm30,qword ptr [rdx-0x408]{1to8}
    vsqrtps zmm30,dword ptr [rcx]{1to16}
    vsqrtps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vsqrtps zmm30,dword ptr [rdx+0x200]{1to16}
    vsqrtps zmm30,dword ptr [rdx-0x200]{1to16}
    vsqrtps zmm30,dword ptr [rdx-0x204]{1to16}


    vcmppd k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b
    vcmpps k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vcvtdq2pd zmm30{k7},dword ptr [rcx]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx+0x200]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx-0x200]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx-0x204]{1to8}

    vcvtdq2ps zmm30,dword ptr [rcx]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtpd2dq ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvtpd2ps ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx-0x408]{1to8}


    vpabsd zmm30,dword ptr [rcx]{1to16}
    vpabsd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpabsd zmm30,dword ptr [rdx+0x200]{1to16}
    vpabsd zmm30,dword ptr [rdx-0x200]{1to16}
    vpabsd zmm30,dword ptr [rdx-0x204]{1to16}

    vpaddd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpaddq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpcmpeqd k5,zmm30,dword ptr [rcx]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vpcmpeqq k5,zmm30,qword ptr [rcx]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx-0x408]{1to8}
    vpcmpgtd k5,zmm30,dword ptr [rcx]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vpcmpgtq k5,zmm30,qword ptr [rcx]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx-0x408]{1to8}

    vpmaxsd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpmaxud zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpminsd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpminud zmm30,zmm29,dword ptr [rcx]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpmuldq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vpmulld zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpmuludq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpshufd zmm30,dword ptr [rcx]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx-0x204]{1to16},0x7b


    vpslld zmm30,dword ptr [rcx]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsllq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpsrad zmm30,dword ptr [rcx]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsrld zmm30,dword ptr [rcx]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsrlq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vcvtps2dq zmm30,dword ptr [rcx]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtps2pd zmm30{k7},dword ptr [rcx]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx+0x200]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx-0x200]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx-0x204]{1to8}

    vpsubd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpsubq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpunpckhdq zmm30,zmm29,dword ptr [rcx]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpunpckhqdq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpunpckldq zmm30,zmm29,dword ptr [rcx]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpunpcklqdq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vshufpd zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vshufps zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b

    vunpckhpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vunpckhps zmm30,zmm29,dword ptr [rcx]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vunpcklpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vunpcklps zmm30,zmm29,dword ptr [rcx]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpandd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpandq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpandnd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpandnq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpxord zmm30,zmm29,dword ptr [rcx]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpxorq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsraq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpconflictd zmm30,dword ptr [rcx]{1to16}
    vpconflictd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpconflictd zmm30,dword ptr [rdx+0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x204]{1to16}

    vpconflictq zmm30,qword ptr [rcx]{1to8}
    vpconflictq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpconflictq zmm30,qword ptr [rdx+0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x408]{1to8}

    vplzcntd	zmm30,dword ptr [rcx]{1to16}
    vplzcntd	zmm30,dword ptr [rdx+0x1fc]{1to16}
    vplzcntd	zmm30,dword ptr [rdx+0x200]{1to16}
    vplzcntd	zmm30,dword ptr [rdx-0x200]{1to16}
    vplzcntd	zmm30,dword ptr [rdx-0x204]{1to16}

    vplzcntq	zmm30,qword ptr [rcx]{1to8}
    vplzcntq	zmm30,qword ptr [rdx+0x3f8]{1to8}
    vplzcntq	zmm30,qword ptr [rdx+0x400]{1to8}
    vplzcntq	zmm30,qword ptr [rdx-0x400]{1to8}
    vplzcntq	zmm30,qword ptr [rdx-0x408]{1to8}

    vptestnmd	k5,zmm29,dword ptr [rcx]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx+0x200]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx-0x200]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx-0x204]{1to16}

    vptestnmq	k5,zmm29,qword ptr [rcx]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx+0x400]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx-0x400]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx-0x408]{1to8}

    vexp2ps zmm30,dword ptr [rcx]{1to16}
    vexp2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vexp2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vexp2pd zmm30,qword ptr [rcx]{1to8}
    vexp2pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vexp2pd zmm30,qword ptr [rdx+0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp28ps zmm30,dword ptr [rcx]{1to16}
    vrcp28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrcp28pd zmm30,qword ptr [rcx]{1to8}
    vrcp28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x408]{1to8}


    vrsqrt28ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrsqrt28pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrsqrt14pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}


    vcvtpd2udq ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvtps2udq zmm30,dword ptr [rcx]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvttpd2udq ymm30{k7},qword ptr [rcx]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvttps2udq zmm30,dword ptr [rcx]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtudq2ps zmm30,dword ptr [rcx]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx-0x204]{1to16}


    vgetexppd zmm30,qword ptr [rcx]{1to8}
    vgetexppd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vgetexppd zmm30,qword ptr [rdx+0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x408]{1to8}

    vgetexpps zmm30,dword ptr [rcx]{1to16}
    vgetexpps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vgetexpps zmm30,dword ptr [rdx+0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x204]{1to16}


    vrcp14pd zmm30,qword ptr [rcx]{1to8}
    vrcp14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp14ps zmm30,dword ptr [rcx]{1to16}
    vrcp14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrndscalepd zmm30,qword ptr [rcx]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vrndscaleps zmm30,dword ptr [rcx]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    valignd zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b

    vblendmpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vblendmps zmm30,zmm29,dword ptr [rcx]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vcvttpd2dq ymm30{k7},qword ptr [rcx]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvttps2dq zmm30,dword ptr [rcx]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx-0x204]{1to16}

    vfmadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}


    vfmadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}


    vfmadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}


    vfmaddsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmaddsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmaddsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmaddsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmaddsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmaddsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsubadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsubadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsubadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsubadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfmsubadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfmsubadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfnmadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfnmadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfnmadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfnmsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfnmsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}


    vfnmsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vfnmsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vgetmantpd zmm30,qword ptr [rcx]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vgetmantps zmm30,dword ptr [rcx]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpabsq zmm30,qword ptr [rcx]{1to8}
    vpabsq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpabsq zmm30,qword ptr [rdx+0x400]{1to8}
    vpabsq zmm30,qword ptr [rdx-0x400]{1to8}
    vpabsq zmm30,qword ptr [rdx-0x408]{1to8}

    vpblendmd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}


    vpcmpd k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpcmpq k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpcmpud k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b


    vpcmpuq k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpblendmq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermilpd zmm30,qword ptr [rcx]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermilpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermilps zmm30,dword ptr [rcx]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpermilps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermpd zmm30,qword ptr [rcx]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermq zmm30,qword ptr [rcx]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpmaxsq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpmaxuq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpminsq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpminuq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpord  zmm30,zmm29,dword ptr [rcx]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vporq  zmm30,zmm29,qword ptr [rcx]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsllvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpsllvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsravd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpsravq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsrlvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpsrlvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vptestmd k5,zmm30,dword ptr [rcx]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vptestmq k5,zmm30,qword ptr [rcx]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx-0x408]{1to8}

    vpternlogd zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vshuff32x4 zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vshufi32x4 zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    valignq zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vscalefpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vscalefps zmm30,zmm29,dword ptr [rcx]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vfixupimmps zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b

    vfixupimmpd zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vprolvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vprold zmm30,dword ptr [rcx]{1to16},0x7b
    vprold zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vprold zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vprold zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vprold zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vprolvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vprolq zmm30,qword ptr [rcx]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vprorvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vprord zmm30,dword ptr [rcx]{1to16},0x7b
    vprord zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vprord zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vprord zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vprord zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vprorvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vprorq zmm30,qword ptr [rcx]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermi2d zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermi2q zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermi2ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermi2pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}


    vaddpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vaddpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vaddpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vaddpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vaddpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vaddps zmm0,zmm1,dword ptr [rcx]{1to16}
    vaddps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vaddps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vaddps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vaddps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vdivpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vdivpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vdivpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vdivpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vdivpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vdivps zmm0,zmm1,dword ptr [rcx]{1to16}
    vdivps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vdivps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vdivps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vdivps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vmaxpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vmaxpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vmaxpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vmaxpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vmaxpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vmaxps zmm0,zmm1,dword ptr [rcx]{1to16}
    vmaxps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vmaxps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vmaxps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vmaxps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vminpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vminpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vminpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vminpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vminpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vminps zmm0,zmm1,dword ptr [rcx]{1to16}
    vminps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vminps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vminps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vminps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vmulpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vmulpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vmulpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vmulpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vmulpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vmulps zmm0,zmm1,dword ptr [rcx]{1to16}
    vmulps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vmulps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vmulps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vmulps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vsubpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vsubpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vsubpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vsubpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vsubpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vsubps zmm0,zmm1,dword ptr [rcx]{1to16}
    vsubps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vsubps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vsubps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vsubps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vsqrtpd zmm0,qword ptr [rcx]{1to8}
    vsqrtpd zmm0,qword ptr [rdx+0x3f8]{1to8}
    vsqrtpd zmm0,qword ptr [rdx+0x400]{1to8}
    vsqrtpd zmm0,qword ptr [rdx-0x400]{1to8}
    vsqrtpd zmm0,qword ptr [rdx-0x408]{1to8}

    vsqrtps zmm0,dword ptr [rcx]{1to16}
    vsqrtps zmm0,dword ptr [rdx+0x1fc]{1to16}
    vsqrtps zmm0,dword ptr [rdx+0x200]{1to16}
    vsqrtps zmm0,dword ptr [rdx-0x200]{1to16}
    vsqrtps zmm0,dword ptr [rdx-0x204]{1to16}

    vcmppd k5,zmm0,qword ptr [rcx]{1to8},0x7b
    vcmppd k5,zmm0,qword ptr [rdx+0x3f8]{1to8},0x7b
    vcmppd k5,zmm0,qword ptr [rdx+0x400]{1to8},0x7b
    vcmppd k5,zmm0,qword ptr [rdx-0x400]{1to8},0x7b
    vcmppd k5,zmm0,qword ptr [rdx-0x408]{1to8},0x7b

    vcmpps k5,zmm0,dword ptr [rcx]{1to16},0x7b
    vcmpps k5,zmm0,dword ptr [rdx+0x1fc]{1to16},0x7b
    vcmpps k5,zmm0,dword ptr [rdx+0x200]{1to16},0x7b
    vcmpps k5,zmm0,dword ptr [rdx-0x200]{1to16},0x7b
    vcmpps k5,zmm0,dword ptr [rdx-0x204]{1to16},0x7b

    vcvtdq2pd zmm0{k7},dword ptr [rcx]{1to8}
    vcvtdq2pd zmm0{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtdq2pd zmm0{k7},dword ptr [rdx+0x200]{1to8}
    vcvtdq2pd zmm0{k7},dword ptr [rdx-0x200]{1to8}
    vcvtdq2pd zmm0{k7},dword ptr [rdx-0x204]{1to8}

    vcvtdq2ps zmm0,dword ptr [rcx]{1to16}
    vcvtdq2ps zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvtdq2ps zmm0,dword ptr [rdx+0x200]{1to16}
    vcvtdq2ps zmm0,dword ptr [rdx-0x200]{1to16}
    vcvtdq2ps zmm0,dword ptr [rdx-0x204]{1to16}

    vcvtpd2dq ymm0{k7},qword ptr [rcx]{1to8}
    vcvtpd2dq ymm0{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2dq ymm0{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2dq ymm0{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2dq ymm0{k7},qword ptr [rdx-0x408]{1to8}

    vcvtpd2ps ymm0{k7},qword ptr [rcx]{1to8}
    vcvtpd2ps ymm0{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2ps ymm0{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2ps ymm0{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2ps ymm0{k7},qword ptr [rdx-0x408]{1to8}

    vpabsd zmm0,dword ptr [rcx]{1to16}
    vpabsd zmm0,dword ptr [rdx+0x1fc]{1to16}
    vpabsd zmm0,dword ptr [rdx+0x200]{1to16}
    vpabsd zmm0,dword ptr [rdx-0x200]{1to16}
    vpabsd zmm0,dword ptr [rdx-0x204]{1to16}

    vpaddd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpaddd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpaddd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpaddd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpaddd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpaddq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpaddq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpaddq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpaddq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpaddq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpcmpeqd k5,zmm0,dword ptr [rcx]{1to16}
    vpcmpeqd k5,zmm0,dword ptr [rdx+0x1fc]{1to16}
    vpcmpeqd k5,zmm0,dword ptr [rdx+0x200]{1to16}
    vpcmpeqd k5,zmm0,dword ptr [rdx-0x200]{1to16}
    vpcmpeqd k5,zmm0,dword ptr [rdx-0x204]{1to16}

    vpcmpgtd k5,zmm0,dword ptr [rcx]{1to16}
    vpcmpgtd k5,zmm0,dword ptr [rdx+0x1fc]{1to16}
    vpcmpgtd k5,zmm0,dword ptr [rdx+0x200]{1to16}
    vpcmpgtd k5,zmm0,dword ptr [rdx-0x200]{1to16}
    vpcmpgtd k5,zmm0,dword ptr [rdx-0x204]{1to16}

    vpcmpgtq k5,zmm0,qword ptr [rcx]{1to8}
    vpcmpgtq k5,zmm0,qword ptr [rdx+0x3f8]{1to8}
    vpcmpgtq k5,zmm0,qword ptr [rdx+0x400]{1to8}
    vpcmpgtq k5,zmm0,qword ptr [rdx-0x400]{1to8}
    vpcmpgtq k5,zmm0,qword ptr [rdx-0x408]{1to8}

    vpmaxsd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpmaxsd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpmaxsd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpmaxsd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpmaxsd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpmaxud zmm0,zmm1,dword ptr [rcx]{1to16}
    vpmaxud zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpmaxud zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpmaxud zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpmaxud zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpminsd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpminsd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpminsd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpminsd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpminsd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpminud zmm0,zmm1,dword ptr [rcx]{1to16}
    vpminud zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpminud zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpminud zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpminud zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpmuldq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpmuldq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpmuldq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpmuldq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpmuldq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpmulld zmm0,zmm1,dword ptr [rcx]{1to16}
    vpmulld zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpmulld zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpmulld zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpmulld zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpmuludq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpmuludq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpmuludq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpmuludq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpmuludq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpshufd zmm0,dword ptr [rcx]{1to16},0x7b
    vpshufd zmm0,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpshufd zmm0,dword ptr [rdx+0x200]{1to16},0x7b
    vpshufd zmm0,dword ptr [rdx-0x200]{1to16},0x7b
    vpshufd zmm0,dword ptr [rdx-0x204]{1to16},0x7b

    vcvtps2dq zmm0,dword ptr [rcx]{1to16}
    vcvtps2dq zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2dq zmm0,dword ptr [rdx+0x200]{1to16}
    vcvtps2dq zmm0,dword ptr [rdx-0x200]{1to16}
    vcvtps2dq zmm0,dword ptr [rdx-0x204]{1to16}

    vcvtps2pd zmm0{k7},dword ptr [rcx]{1to8}
    vcvtps2pd zmm0{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtps2pd zmm0{k7},dword ptr [rdx+0x200]{1to8}
    vcvtps2pd zmm0{k7},dword ptr [rdx-0x200]{1to8}
    vcvtps2pd zmm0{k7},dword ptr [rdx-0x204]{1to8}

    vpsubd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpsubd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpsubd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpsubd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpsubd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpsubq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpsubq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpsubq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpsubq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpsubq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpunpckhdq zmm0,zmm1,dword ptr [rcx]{1to16}
    vpunpckhdq zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpunpckhdq zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpunpckhdq zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpunpckhdq zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpunpckhqdq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpunpckhqdq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpunpckhqdq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpunpckhqdq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpunpckhqdq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpunpckldq zmm0,zmm1,dword ptr [rcx]{1to16}
    vpunpckldq zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpunpckldq zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpunpckldq zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpunpckldq zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpunpcklqdq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpunpcklqdq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpunpcklqdq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpunpcklqdq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpunpcklqdq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vshufpd zmm0,zmm1,qword ptr [rcx]{1to8},0x7b
    vshufpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshufpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8},0x7b
    vshufpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8},0x7b
    vshufpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8},0x7b

    vshufps zmm0,zmm1,dword ptr [rcx]{1to16},0x7b
    vshufps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshufps zmm0,zmm1,dword ptr [rdx+0x200]{1to16},0x7b
    vshufps zmm0,zmm1,dword ptr [rdx-0x200]{1to16},0x7b
    vshufps zmm0,zmm1,dword ptr [rdx-0x204]{1to16},0x7b

    vunpckhpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vunpckhpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vunpckhpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vunpckhpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vunpckhpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vunpckhps zmm0,zmm1,dword ptr [rcx]{1to16}
    vunpckhps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vunpckhps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vunpckhps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vunpckhps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vunpcklpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vunpcklpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vunpcklpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vunpcklpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vunpcklpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vunpcklps zmm0,zmm1,dword ptr [rcx]{1to16}
    vunpcklps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vunpcklps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vunpcklps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vunpcklps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpandd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpandd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpandd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpandd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpandd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpandq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpandq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpandq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpandq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpandq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpandnd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpandnd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpandnd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpandnd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpandnd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpandnq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpandnq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpandnq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpandnq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpandnq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpxord zmm0,zmm1,dword ptr [rcx]{1to16}
    vpxord zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpxord zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpxord zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpxord zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpxorq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpxorq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpxorq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpxorq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpxorq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpconflictd zmm0,dword ptr [rcx]{1to16}
    vpconflictd zmm0,dword ptr [rdx+0x1fc]{1to16}
    vpconflictd zmm0,dword ptr [rdx+0x200]{1to16}
    vpconflictd zmm0,dword ptr [rdx-0x200]{1to16}
    vpconflictd zmm0,dword ptr [rdx-0x204]{1to16}

    vptestnmd	k5,zmm1,dword ptr [rcx]{1to16}
    vptestnmd	k5,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vptestnmd	k5,zmm1,dword ptr [rdx+0x200]{1to16}
    vptestnmd	k5,zmm1,dword ptr [rdx-0x200]{1to16}
    vptestnmd	k5,zmm1,dword ptr [rdx-0x204]{1to16}

    vptestnmq	k5,zmm1,qword ptr [rcx]{1to8}
    vptestnmq	k5,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vptestnmq	k5,zmm1,qword ptr [rdx+0x400]{1to8}
    vptestnmq	k5,zmm1,qword ptr [rdx-0x400]{1to8}
    vptestnmq	k5,zmm1,qword ptr [rdx-0x408]{1to8}

    vrsqrt14ps zmm0,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx-0x204]{1to16}

    vrsqrt14ps zmm0,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm0,dword ptr [rdx-0x204]{1to16}


    vcvtpd2udq ymm0{k7},qword ptr [rcx]{1to8}
    vcvtpd2udq ymm0{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2udq ymm0{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2udq ymm0{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2udq ymm0{k7},qword ptr [rdx-0x408]{1to8}

    vcvtps2udq zmm0,dword ptr [rcx]{1to16}
    vcvtps2udq zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2udq zmm0,dword ptr [rdx+0x200]{1to16}
    vcvtps2udq zmm0,dword ptr [rdx-0x200]{1to16}
    vcvtps2udq zmm0,dword ptr [rdx-0x204]{1to16}

    vcvttpd2udq ymm0{k7},qword ptr [rcx]{1to8}
    vcvttpd2udq ymm0{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2udq ymm0{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2udq ymm0{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2udq ymm0{k7},qword ptr [rdx-0x408]{1to8}
    vcvttps2udq zmm0,dword ptr [rcx]{1to16}
    vcvttps2udq zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2udq zmm0,dword ptr [rdx+0x200]{1to16}
    vcvttps2udq zmm0,dword ptr [rdx-0x200]{1to16}
    vcvttps2udq zmm0,dword ptr [rdx-0x204]{1to16}

    vcvtudq2pd zmm0{k7},dword ptr [rcx]{1to8}
    vcvtudq2pd zmm0{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtudq2pd zmm0{k7},dword ptr [rdx+0x200]{1to8}
    vcvtudq2pd zmm0{k7},dword ptr [rdx-0x200]{1to8}
    vcvtudq2pd zmm0{k7},dword ptr [rdx-0x204]{1to8}

    vcvtudq2ps zmm0,dword ptr [rcx]{1to16}
    vcvtudq2ps zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvtudq2ps zmm0,dword ptr [rdx+0x200]{1to16}
    vcvtudq2ps zmm0,dword ptr [rdx-0x200]{1to16}
    vcvtudq2ps zmm0,dword ptr [rdx-0x204]{1to16}



    valignd zmm0,zmm1,dword ptr [rcx]{1to16},0x7b
    valignd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16},0x7b
    valignd zmm0,zmm1,dword ptr [rdx+0x200]{1to16},0x7b
    valignd zmm0,zmm1,dword ptr [rdx-0x200]{1to16},0x7b
    valignd zmm0,zmm1,dword ptr [rdx-0x204]{1to16},0x7b

    vblendmpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vblendmpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vblendmpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vblendmpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vblendmpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vblendmps zmm0,zmm1,dword ptr [rcx]{1to16}
    vblendmps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vblendmps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vblendmps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vblendmps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vcvttpd2dq ymm0{k7},qword ptr [rcx]{1to8}
    vcvttpd2dq ymm0{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2dq ymm0{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2dq ymm0{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2dq ymm0{k7},qword ptr [rdx-0x408]{1to8}

    vcvttps2dq zmm0,dword ptr [rcx]{1to16}
    vcvttps2dq zmm0,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2dq zmm0,dword ptr [rdx+0x200]{1to16}
    vcvttps2dq zmm0,dword ptr [rdx-0x200]{1to16}
    vcvttps2dq zmm0,dword ptr [rdx-0x204]{1to16}

    vfmadd132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmadd132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmadd132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmadd132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmadd132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmadd132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmadd132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmadd132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmadd132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmadd132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmadd213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmadd213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmadd213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmadd213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmadd213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmadd213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmadd213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmadd213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmadd213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmadd213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmadd231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmadd231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmadd231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmadd231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmadd231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmadd231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmadd231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmadd231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmadd231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmadd231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmaddsub132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmaddsub132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmaddsub132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmaddsub132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmaddsub132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmaddsub132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmaddsub132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmaddsub132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmaddsub213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmaddsub213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmaddsub213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmaddsub213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmaddsub213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmaddsub213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmaddsub213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmaddsub213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmaddsub231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmaddsub231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmaddsub231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmaddsub231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmaddsub231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmaddsub231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmaddsub231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmaddsub231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsub132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsub132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsub132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsub132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsub132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsub132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsub132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsub132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsub132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsub132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsub213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsub213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsub213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsub213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsub213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsub213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsub213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsub213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsub213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsub213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsub231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsub231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsub231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsub231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsub231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsub231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsub231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsub231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsub231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsub231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsubadd132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsubadd132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsubadd132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsubadd132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsubadd132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsubadd132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsubadd132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsubadd132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsubadd213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsubadd213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsubadd213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsubadd213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsubadd213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsubadd213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsubadd213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsubadd213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfmsubadd231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfmsubadd231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfmsubadd231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfmsubadd231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfmsubadd231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfmsubadd231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfmsubadd231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfmsubadd231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmadd132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmadd132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmadd132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmadd132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfnmadd132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmadd132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmadd132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmadd132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmadd213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmadd213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmadd213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmadd213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfnmadd213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmadd213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmadd213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmadd213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmadd231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmadd231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmadd231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmadd231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}
    vfnmadd231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmadd231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmadd231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmadd231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmsub132pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmsub132pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub132pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmsub132pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmsub132pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfnmsub132ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmsub132ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub132ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmsub132ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmsub132ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmsub213pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmsub213pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub213pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmsub213pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmsub213pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfnmsub213ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmsub213ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub213ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmsub213ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmsub213ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfnmsub231pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vfnmsub231pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub231pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vfnmsub231pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vfnmsub231pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vfnmsub231ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vfnmsub231ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub231ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vfnmsub231ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vfnmsub231ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpabsq zmm0,qword ptr [rcx]{1to8}
    vpabsq zmm0,qword ptr [rdx+0x3f8]{1to8}
    vpabsq zmm0,qword ptr [rdx+0x400]{1to8}
    vpabsq zmm0,qword ptr [rdx-0x400]{1to8}
    vpabsq zmm0,qword ptr [rdx-0x408]{1to8}

    vpblendmd zmm0,zmm1,dword ptr [rcx]{1to16}
    vpblendmd zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpblendmd zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpblendmd zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpblendmd zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpblendmq zmm0,zmm1,qword ptr [rcx]{1to8}
    vpblendmq zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpblendmq zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpblendmq zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpblendmq zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vscalefpd zmm0,zmm1,qword ptr [rcx]{1to8}
    vscalefpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vscalefpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vscalefpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vscalefpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vscalefps zmm0,zmm1,dword ptr [rcx]{1to16}
    vscalefps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vscalefps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vscalefps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vscalefps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vfixupimmps zmm0,zmm1,dword ptr [rcx]{1to16},0x7b
    vfixupimmps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16},0x7b
    vfixupimmps zmm0,zmm1,dword ptr [rdx+0x200]{1to16},0x7b
    vfixupimmps zmm0,zmm1,dword ptr [rdx-0x200]{1to16},0x7b
    vfixupimmps zmm0,zmm1,dword ptr [rdx-0x204]{1to16},0x7b

    vfixupimmpd zmm0,zmm1,qword ptr [rcx]{1to8},0x7b
    vfixupimmpd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8},0x7b
    vfixupimmpd zmm0,zmm1,qword ptr [rdx+0x400]{1to8},0x7b
    vfixupimmpd zmm0,zmm1,qword ptr [rdx-0x400]{1to8},0x7b
    vfixupimmpd zmm0,zmm1,qword ptr [rdx-0x408]{1to8},0x7b

    vpermi2d zmm0,zmm1,dword ptr [rcx]{1to16}
    vpermi2d zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpermi2d zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpermi2d zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpermi2d zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpermi2q zmm0,zmm1,qword ptr [rcx]{1to8}
    vpermi2q zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpermi2q zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpermi2q zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpermi2q zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    vpermi2ps zmm0,zmm1,dword ptr [rcx]{1to16}
    vpermi2ps zmm0,zmm1,dword ptr [rdx+0x1fc]{1to16}
    vpermi2ps zmm0,zmm1,dword ptr [rdx+0x200]{1to16}
    vpermi2ps zmm0,zmm1,dword ptr [rdx-0x200]{1to16}
    vpermi2ps zmm0,zmm1,dword ptr [rdx-0x204]{1to16}

    vpermi2pd zmm0,zmm1,qword ptr [rcx]{1to8}
    vpermi2pd zmm0,zmm1,qword ptr [rdx+0x3f8]{1to8}
    vpermi2pd zmm0,zmm1,qword ptr [rdx+0x400]{1to8}
    vpermi2pd zmm0,zmm1,qword ptr [rdx-0x400]{1to8}
    vpermi2pd zmm0,zmm1,qword ptr [rdx-0x408]{1to8}

    end
