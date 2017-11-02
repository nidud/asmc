;
; v2.26 - AVX512
;
    .x64
    .model flat
    .code

    vaddpd xmm1,xmm2,xmm3
    vaddps xmm1,xmm2,xmm3
    vaddsd xmm1,xmm2,xmm3
    vaddss xmm1,xmm2,xmm3
    vaddpd xmm1{k1}{z},xmm2,xmm3
    vaddps xmm1{k1}{z},xmm2,xmm3
    vaddsd xmm1{k1}{z},xmm2,xmm3
    vaddss xmm1{k1}{z},xmm2,xmm3
    vaddpd ymm1,ymm2,ymm3
    vaddps ymm1,ymm2,ymm3
    vaddpd ymm1{k1}{z},ymm2,ymm3
    vaddps ymm1{k1}{z},ymm2,ymm3
    vaddpd zmm1,zmm2,zmm3
    vaddps zmm1,zmm2,zmm3
    vaddpd zmm1{k1}{z},zmm2,zmm3
    vaddps zmm1{k1}{z},zmm2,zmm3
    vaddpd xmm1,xmm2,[rax]
    vaddps xmm1,xmm2,[rax]
    vaddsd xmm1,xmm2,[rax]
    vaddss xmm1,xmm2,[rax]
    vaddpd xmm1{k1}{z},xmm2,[rax]
    vaddps xmm1{k1}{z},xmm2,[rax]
    vaddsd xmm1{k1}{z},xmm2,[rax]
    vaddss xmm1{k1}{z},xmm2,[rax]
    vaddpd ymm1,ymm2,[rax]
    vaddps ymm1,ymm2,[rax]
    vaddpd ymm1{k1}{z},ymm2,[rax]
    vaddps ymm1{k1}{z},ymm2,[rax]
    vaddpd zmm1,zmm2,[rax]
    vaddps zmm1,zmm2,[rax]
    vaddpd zmm1{k1}{z},zmm2,[rax]
    vaddps zmm1{k1}{z},zmm2,[rax]

    vaddpd xmm16,xmm2,xmm3
    vaddps xmm16,xmm2,xmm3
    vaddsd xmm16,xmm2,xmm3
    vaddss xmm16,xmm2,xmm3
    vaddpd xmm16{k1}{z},xmm2,xmm3
    vaddps xmm16{k1}{z},xmm2,xmm3
    vaddsd xmm16{k1}{z},xmm2,xmm3
    vaddss xmm16{k1}{z},xmm2,xmm3
    vaddpd ymm16,ymm2,ymm3
    vaddps ymm16,ymm2,ymm3
    vaddpd ymm16{k1}{z},ymm2,ymm3
    vaddps ymm16{k1}{z},ymm2,ymm3
    vaddpd xmm16,xmm2,[rax]
    vaddps xmm16,xmm2,[rax]
    vaddsd xmm16,xmm2,[rax]
    vaddss xmm16,xmm2,[rax]
    vaddpd xmm16{k1}{z},xmm2,[rax]
    vaddps xmm16{k1}{z},xmm2,[rax]
    vaddsd xmm16{k1}{z},xmm2,[rax]
    vaddss xmm16{k1}{z},xmm2,[rax]
    vaddpd ymm16,ymm2,[rax]
    vaddps ymm16,ymm2,[rax]
    vaddpd ymm16{k1}{z},ymm2,[rax]
    vaddps ymm16{k1}{z},ymm2,[rax]

    vdivpd xmm1,xmm2,xmm3
    vdivps xmm1,xmm2,xmm3
    vdivsd xmm1,xmm2,xmm3
    vdivss xmm1,xmm2,xmm3
    vdivpd xmm1{k1}{z},xmm2,xmm3
    vdivps xmm1{k1}{z},xmm2,xmm3
    vdivsd xmm1{k1}{z},xmm2,xmm3
    vdivss xmm1{k1}{z},xmm2,xmm3
    vdivpd ymm1,ymm2,ymm3
    vdivps ymm1,ymm2,ymm3
    vdivpd ymm1{k1}{z},ymm2,ymm3
    vdivps ymm1{k1}{z},ymm2,ymm3
    vdivpd zmm1,zmm2,zmm3
    vdivps zmm1,zmm2,zmm3
    vdivpd zmm1{k1}{z},zmm2,zmm3
    vdivps zmm1{k1}{z},zmm2,zmm3
    vdivpd xmm1,xmm2,[rax]
    vdivps xmm1,xmm2,[rax]
    vdivsd xmm1,xmm2,[rax]
    vdivss xmm1,xmm2,[rax]
    vdivpd xmm1{k1}{z},xmm2,[rax]
    vdivps xmm1{k1}{z},xmm2,[rax]
    vdivsd xmm1{k1}{z},xmm2,[rax]
    vdivss xmm1{k1}{z},xmm2,[rax]
    vdivpd ymm1,ymm2,[rax]
    vdivps ymm1,ymm2,[rax]
    vdivpd ymm1{k1}{z},ymm2,[rax]
    vdivps ymm1{k1}{z},ymm2,[rax]
    vdivpd zmm1,zmm2,[rax]
    vdivps zmm1,zmm2,[rax]
    vdivpd zmm1{k1}{z},zmm2,[rax]
    vdivps zmm1{k1}{z},zmm2,[rax]

    vmaxpd xmm1,xmm2,xmm3
    vmaxps xmm1,xmm2,xmm3
    vmaxsd xmm1,xmm2,xmm3
    vmaxss xmm1,xmm2,xmm3
    vmaxpd xmm1{k1}{z},xmm2,xmm3
    vmaxps xmm1{k1}{z},xmm2,xmm3
    vmaxsd xmm1{k1}{z},xmm2,xmm3
    vmaxss xmm1{k1}{z},xmm2,xmm3
    vmaxpd ymm1,ymm2,ymm3
    vmaxps ymm1,ymm2,ymm3
    vmaxpd ymm1{k1}{z},ymm2,ymm3
    vmaxps ymm1{k1}{z},ymm2,ymm3
    vmaxpd zmm1,zmm2,zmm3
    vmaxps zmm1,zmm2,zmm3
    vmaxpd zmm1{k1}{z},zmm2,zmm3
    vmaxps zmm1{k1}{z},zmm2,zmm3
    vmaxpd xmm1,xmm2,[rax]
    vmaxps xmm1,xmm2,[rax]
    vmaxsd xmm1,xmm2,[rax]
    vmaxss xmm1,xmm2,[rax]
    vmaxpd xmm1{k1}{z},xmm2,[rax]
    vmaxps xmm1{k1}{z},xmm2,[rax]
    vmaxsd xmm1{k1}{z},xmm2,[rax]
    vmaxss xmm1{k1}{z},xmm2,[rax]
    vmaxpd ymm1,ymm2,[rax]
    vmaxps ymm1,ymm2,[rax]
    vmaxpd ymm1{k1}{z},ymm2,[rax]
    vmaxps ymm1{k1}{z},ymm2,[rax]
    vmaxpd zmm1,zmm2,[rax]
    vmaxps zmm1,zmm2,[rax]
    vmaxpd zmm1{k1}{z},zmm2,[rax]
    vmaxps zmm1{k1}{z},zmm2,[rax]

    vminpd xmm1,xmm2,xmm3
    vminps xmm1,xmm2,xmm3
    vminsd xmm1,xmm2,xmm3
    vminss xmm1,xmm2,xmm3
    vminpd xmm1{k1}{z},xmm2,xmm3
    vminps xmm1{k1}{z},xmm2,xmm3
    vminsd xmm1{k1}{z},xmm2,xmm3
    vminss xmm1{k1}{z},xmm2,xmm3
    vminpd ymm1,ymm2,ymm3
    vminps ymm1,ymm2,ymm3
    vminpd ymm1{k1}{z},ymm2,ymm3
    vminps ymm1{k1}{z},ymm2,ymm3
    vminpd zmm1,zmm2,zmm3
    vminps zmm1,zmm2,zmm3
    vminpd zmm1{k1}{z},zmm2,zmm3
    vminps zmm1{k1}{z},zmm2,zmm3
    vminpd xmm1,xmm2,[rax]
    vminps xmm1,xmm2,[rax]
    vminsd xmm1,xmm2,[rax]
    vminss xmm1,xmm2,[rax]
    vminpd xmm1{k1}{z},xmm2,[rax]
    vminps xmm1{k1}{z},xmm2,[rax]
    vminsd xmm1{k1}{z},xmm2,[rax]
    vminss xmm1{k1}{z},xmm2,[rax]
    vminpd ymm1,ymm2,[rax]
    vminps ymm1,ymm2,[rax]
    vminpd ymm1{k1}{z},ymm2,[rax]
    vminps ymm1{k1}{z},ymm2,[rax]
    vminpd zmm1,zmm2,[rax]
    vminps zmm1,zmm2,[rax]
    vminpd zmm1{k1}{z},zmm2,[rax]
    vminps zmm1{k1}{z},zmm2,[rax]

    vmulpd xmm1,xmm2,xmm3
    vmulps xmm1,xmm2,xmm3
    vmulsd xmm1,xmm2,xmm3
    vmulss xmm1,xmm2,xmm3
    vmulpd xmm1{k1}{z},xmm2,xmm3
    vmulps xmm1{k1}{z},xmm2,xmm3
    vmulsd xmm1{k1}{z},xmm2,xmm3
    vmulss xmm1{k1}{z},xmm2,xmm3
    vmulpd ymm1,ymm2,ymm3
    vmulps ymm1,ymm2,ymm3
    vmulpd ymm1{k1}{z},ymm2,ymm3
    vmulps ymm1{k1}{z},ymm2,ymm3
    vmulpd zmm1,zmm2,zmm3
    vmulps zmm1,zmm2,zmm3
    vmulpd zmm1{k1}{z},zmm2,zmm3
    vmulps zmm1{k1}{z},zmm2,zmm3
    vmulpd xmm1,xmm2,[rax]
    vmulps xmm1,xmm2,[rax]
    vmulsd xmm1,xmm2,[rax]
    vmulss xmm1,xmm2,[rax]
    vmulpd xmm1{k1}{z},xmm2,[rax]
    vmulps xmm1{k1}{z},xmm2,[rax]
    vmulsd xmm1{k1}{z},xmm2,[rax]
    vmulss xmm1{k1}{z},xmm2,[rax]
    vmulpd ymm1,ymm2,[rax]
    vmulps ymm1,ymm2,[rax]
    vmulpd ymm1{k1}{z},ymm2,[rax]
    vmulps ymm1{k1}{z},ymm2,[rax]
    vmulpd zmm1,zmm2,[rax]
    vmulps zmm1,zmm2,[rax]
    vmulpd zmm1{k1}{z},zmm2,[rax]
    vmulps zmm1{k1}{z},zmm2,[rax]

    vsubpd xmm1,xmm2,xmm3
    vsubps xmm1,xmm2,xmm3
    vsubsd xmm1,xmm2,xmm3
    vsubss xmm1,xmm2,xmm3
    vsubpd xmm1{k1}{z},xmm2,xmm3
    vsubps xmm1{k1}{z},xmm2,xmm3
    vsubsd xmm1{k1}{z},xmm2,xmm3
    vsubss xmm1{k1}{z},xmm2,xmm3
    vsubpd ymm1,ymm2,ymm3
    vsubps ymm1,ymm2,ymm3
    vsubpd ymm1{k1}{z},ymm2,ymm3
    vsubps ymm1{k1}{z},ymm2,ymm3
    vsubpd zmm1,zmm2,zmm3
    vsubps zmm1,zmm2,zmm3
    vsubpd zmm1{k1}{z},zmm2,zmm3
    vsubps zmm1{k1}{z},zmm2,zmm3
    vsubpd xmm1,xmm2,[rax]
    vsubps xmm1,xmm2,[rax]
    vsubsd xmm1,xmm2,[rax]
    vsubss xmm1,xmm2,[rax]
    vsubpd xmm1{k1}{z},xmm2,[rax]
    vsubps xmm1{k1}{z},xmm2,[rax]
    vsubsd xmm1{k1}{z},xmm2,[rax]
    vsubss xmm1{k1}{z},xmm2,[rax]
    vsubpd ymm1,ymm2,[rax]
    vsubps ymm1,ymm2,[rax]
    vsubpd ymm1{k1}{z},ymm2,[rax]
    vsubps ymm1{k1}{z},ymm2,[rax]
    vsubpd zmm1,zmm2,[rax]
    vsubps zmm1,zmm2,[rax]
    vsubpd zmm1{k1}{z},zmm2,[rax]
    vsubps zmm1{k1}{z},zmm2,[rax]

    vsqrtpd xmm1,xmm2
    vsqrtps xmm1,xmm2
    vsqrtsd xmm1,xmm2,xmm3
    vsqrtss xmm1,xmm2,xmm3
    vsqrtpd xmm1{k1}{z},xmm2
    vsqrtps xmm1{k1}{z},xmm2
    vsqrtsd xmm1{k1}{z},xmm2,xmm3
    vsqrtss xmm1{k1}{z},xmm2,xmm3
    vsqrtpd ymm1,ymm2
    vsqrtps ymm1,ymm2
    vsqrtpd ymm1{k1}{z},ymm2
    vsqrtps ymm1{k1}{z},ymm2
    vsqrtpd zmm1,zmm2
    vsqrtps zmm1,zmm2
    vsqrtpd zmm1{k1}{z},zmm2
    vsqrtps zmm1{k1}{z},zmm2
    vsqrtpd xmm1,[rax]
    vsqrtps xmm1,[rax]
    vsqrtsd xmm1,xmm3,[rax]
    vsqrtss xmm1,xmm3,[rax]
    vsqrtpd xmm1{k1}{z},[rax]
    vsqrtps xmm1{k1}{z},[rax]
    vsqrtsd xmm1{k1}{z},xmm2,[rax]
    vsqrtss xmm1{k1}{z},xmm2,[rax]
    vsqrtpd ymm1,[rax]
    vsqrtps ymm1,[rax]
    vsqrtpd ymm1{k1}{z},[rax]
    vsqrtps ymm1{k1}{z},[rax]
    vsqrtpd zmm1,[rax]
    vsqrtps zmm1,[rax]
    vsqrtpd zmm1{k1}{z},[rax]
    vsqrtps zmm1{k1}{z},[rax]

    vcmppd xmm1,xmm2,xmm3,7
    vcmpps xmm1,xmm2,xmm3,7
    vcmpsd xmm1,xmm2,xmm3,7
    vcmpss xmm1,xmm2,xmm3,7
    vcmppd ymm1,ymm2,ymm3,7
    vcmpps ymm1,ymm2,ymm3,7
    vcmppd xmm1,xmm2,[rax],7
    vcmpps xmm1,xmm2,[rax],7
    vcmpsd xmm1,xmm2,[rax],7
    vcmpss xmm1,xmm2,[rax],7
    vcmppd ymm1,ymm2,[rax],7
    vcmpps ymm1,ymm2,[rax],7

    vcmppd k1{k2},xmm2,xmm3,7
    vcmpps k1{k2},xmm2,xmm3,7
    vcmpsd k1{k2},xmm2,xmm3,7
    vcmpss k1{k2},xmm2,xmm3,7
    vcmppd k1{k2},ymm2,ymm3,7
    vcmpps k1{k2},ymm2,ymm3,7

    vcmppd k1{k2},xmm2,[rax],7
    vcmpps k1{k2},xmm2,[rax],7
    vcmpsd k1{k2},xmm2,[rax],7
    vcmpss k1{k2},xmm2,[rax],7

    vcmppd k1{k2},zmm2,zmm3,7
    vcmpps k1{k2},zmm2,zmm3,7
    vcmppd k1{k2},ymm2,[rax],7
    vcmpps k1{k2},ymm2,[rax],7
    vcmppd k1{k2},zmm2,[rax],7
    vcmpps k1{k2},zmm2,[rax],7

    vandpd xmm1{k2}{z},xmm2,xmm3
    vandpd ymm1{k2}{z},ymm2,ymm3
    vandpd zmm1{k2}{z},zmm2,zmm3
    vandpd xmm1{k2}{z},xmm2,[rax]
    vandpd ymm1{k2}{z},ymm2,[rax]
    vandpd zmm1{k2}{z},zmm2,[rax]

    vandps xmm1{k2}{z},xmm2,xmm3
    vandps ymm1{k2}{z},ymm2,ymm3
    vandps zmm1{k2}{z},zmm2,zmm3
    vandps xmm1{k2}{z},xmm2,[rax]
    vandps ymm1{k2}{z},ymm2,[rax]
    vandps zmm1{k2}{z},zmm2,[rax]

    vandnpd xmm1{k2}{z},xmm2,xmm3
    vandnpd ymm1{k2}{z},ymm2,ymm3
    vandnpd zmm1{k2}{z},zmm2,zmm3
    vandnpd xmm1{k2}{z},xmm2,[rax]
    vandnpd ymm1{k2}{z},ymm2,[rax]
    vandnpd zmm1{k2}{z},zmm2,[rax]

    vandnps xmm1{k2}{z},xmm2,xmm3
    vandnps ymm1{k2}{z},ymm2,ymm3
    vandnps zmm1{k2}{z},zmm2,zmm3
    vandnps xmm1{k2}{z},xmm2,[rax]
    vandnps ymm1{k2}{z},ymm2,[rax]
    vandnps zmm1{k2}{z},zmm2,[rax]

    vorpd xmm1{k2}{z},xmm2,xmm3
    vorpd ymm1{k2}{z},ymm2,ymm3
    vorpd zmm1{k2}{z},zmm2,zmm3
    vorpd xmm1{k2}{z},xmm2,[rax]
    vorpd ymm1{k2}{z},ymm2,[rax]
    vorpd zmm1{k2}{z},zmm2,[rax]

    vorps xmm1{k2}{z},xmm2,xmm3
    vorps ymm1{k2}{z},ymm2,ymm3
    vorps zmm1{k2}{z},zmm2,zmm3
    vorps xmm1{k2}{z},xmm2,[rax]
    vorps ymm1{k2}{z},ymm2,[rax]
    vorps zmm1{k2}{z},zmm2,[rax]

    vxorpd xmm1{k2}{z},xmm2,xmm3
    vxorpd ymm1{k2}{z},ymm2,ymm3
    vxorpd zmm1{k2}{z},zmm2,zmm3
    vxorpd xmm1{k2}{z},xmm2,[rax]
    vxorpd ymm1{k2}{z},ymm2,[rax]
    vxorpd zmm1{k2}{z},zmm2,[rax]

    vxorps xmm1{k2}{z},xmm2,xmm3
    vxorps ymm1{k2}{z},ymm2,ymm3
    vxorps zmm1{k2}{z},zmm2,zmm3
    vxorps xmm1{k2}{z},xmm2,[rax]
    vxorps ymm1{k2}{z},ymm2,[rax]
    vxorps zmm1{k2}{z},zmm2,[rax]

    vcvtdq2pd   zmm1{k1}{z},ymm2
    vcvtdq2ps   zmm1{k1}{z},zmm2
    vcvttps2dq  zmm1{k1}{z},zmm2
    vcvtps2pd   zmm1{k1}{z},ymm2
    vcvtsd2si   rax,xmm1
    vcvttsd2si  rax,xmm1
    vcvtsd2ss   xmm1{k1}{z},xmm2,xmm3
    vcvtsi2sd   xmm1,xmm2,rax
    vcvtsi2ss   xmm1,xmm2,rax
    vcvtss2sd   xmm1 {k1}{z},xmm2,xmm3
    vcvtss2si   rax,xmm1
    vcvttss2si  rax,xmm1
    vextractps  eax,xmm1,7
    vinsertps   xmm1,xmm2,xmm3,7
    vmovapd     zmm2{k1}{z},zmm1
    vmovaps     zmm2{k1}{z},zmm1
    vmovd       eax,xmm1
    vmovhlps    xmm1,xmm2,xmm3
    vmovlhps    xmm1,xmm2,xmm3
    vmovsd      xmm1{k1}{z},xmm2,xmm3
    vmovss      xmm1{k1}{z},xmm2,xmm3
    vmovntdq    [rax],zmm1
    vmovntdqa   zmm1,[rax]
    vmovntpd    [rax],zmm1
    vmovntps    [rax],zmm1
    vmovshdup   zmm1{k1}{z},zmm2
    vmovsldup   zmm1{k1}{z},zmm2
    vmovupd     zmm1{k1}{z},zmm2
    vmovups     zmm1{k1}{z},zmm2
    vpabsb      zmm1{k1}{z},zmm2
    vpabsw      zmm1{k1}{z},zmm2
    vpabsd      zmm1{k1}{z},zmm2
    vpacksswb   zmm1{k1}{z},zmm2,zmm3
    vpackssdw   zmm1{k1}{z},zmm2,zmm3
    vpackuswb   zmm1{k1}{z},zmm2,zmm3
    vpackusdw   zmm1{k1}{z},zmm2,zmm3
    vpaddb      ymm1{k1}{z},ymm2,ymm3
    vpaddw      zmm1{k1}{z},zmm2,zmm3
    vpaddd      ymm1{k1}{z},ymm2,ymm3
    vpaddq      zmm1{k1}{z},zmm2,zmm3
    vpaddsb     zmm1{k1}{z},zmm2,zmm3
    vpaddsw     zmm1{k1}{z},zmm2,zmm3
    vpaddusb    ymm1{k1}{z},ymm2,ymm3
    vpaddusw    zmm1{k1}{z},zmm2,zmm3
    vpavgb      zmm1{k1}{z},zmm2,zmm3
    vpavgw      zmm1{k1}{z},zmm2,zmm3
    vpcmpeqb    k1{k2},zmm2,zmm3
    vpcmpeqw    k1{k2},zmm2,zmm3
    vpcmpeqd    k1{k2},zmm2,zmm3
    vpcmpeqq    k1{k2},zmm2,zmm3
    vpcmpgtb    k1{k2},zmm2,zmm3
    vpcmpgtw    k1{k2},zmm2,zmm3
    vpcmpgtd    k1{k2},zmm2,zmm3
    vpcmpgtq    k1{k2},zmm2,zmm3
    vpextrb     eax,xmm2,7
    vpextrd     eax,xmm2,7
    vpinsrb     xmm1,xmm2,eax,7
    vpinsrw     xmm1,xmm2,eax,7
    vpinsrd     xmm1,xmm2,eax,7
    vpextrq     rax,xmm2,7
    vpinsrq     xmm1,xmm2,rax,7
    vpmaddwd    zmm1{k1}{z},zmm2,zmm3
    vpmaddubsw  zmm1{k1}{z},zmm2,zmm3
    vpmaxsb     zmm1{k1}{z},zmm2,zmm3
    vpmaxsw     ymm1{k1}{z},ymm2,ymm3
    vpmaxsd     zmm1{k1}{z},zmm2,zmm3
    vpmaxub     zmm1{k1}{z},zmm2,zmm3
    vpmaxuw     zmm1{k1}{z},zmm2,zmm3
    vpmaxud     zmm1{k1}{z},zmm2,zmm3
    vpminsb     zmm1{k1}{z},zmm2,zmm3
    vpminsw     zmm1{k1}{z},zmm2,zmm3
    vpminsd     zmm1{k1}{z},zmm2,zmm3
    vpminub     zmm1{k1}{z},zmm2,zmm3
    vpminuw     zmm1{k1}{z},zmm2,zmm3
    vpminud     zmm1{k1}{z},zmm2,zmm3
    vpmovsxbw   zmm1{k1}{z},ymm3
    vpmovsxbd   zmm1{k1}{z},xmm3
    vpmovsxbq   zmm1{k1}{z},xmm3
    vpmovsxdq   zmm1{k1}{z},ymm3
    vpmovzxwq   zmm1{k1}{z},xmm2
    vpmovzxdq   zmm1{k1}{z},ymm2
    vpmulhrsw   zmm1{k1}{z},zmm2,zmm3
    vpmulhw     zmm1{k1}{z},zmm2,zmm3
    vpmullw     zmm1{k1}{z},zmm2,zmm3
    vpmulld     zmm1{k1}{z},zmm2,zmm3
    vpmuludq    zmm1{k1}{z},zmm2,zmm3
    vpmuldq     zmm1{k1}{z},zmm2,zmm3
    vpsadbw     zmm1,zmm2,zmm3
    vpshufb     zmm1{k1}{z},zmm2,zmm3
    vpshufd     zmm1{k1}{z},zmm2,3
    vpshufhw    zmm1{k1}{z},zmm2,3
    vpshuflw    zmm1{k1}{z},zmm2,3
    vpslldq     zmm1,zmm2,3
    vpsrldq     zmm1,zmm2,3
    vpsllw      zmm1{k1}{z},zmm2,3
    vpslld      zmm1{k1}{z},zmm2,xmm3
    vpsllq      zmm1{k1}{z},zmm2,xmm3
    vpsraw      zmm1,zmm2,3
    vpsrad      zmm1{k1}{z},zmm2,xmm3
    vpsrlw      zmm1{k1}{z},zmm2,xmm3
    vpsrld      zmm1{k1}{z},zmm2,3
    vpsrlq      zmm1{k1}{z},zmm2,xmm3

    vcvtps2dq   ymm1{k1}{z},zmm2
    vpalignr    zmm1{k1}{z},zmm2,zmm3,7
    vpmovsxwd   zmm1{k1}{z},xmm3
    vpmovsxwq   zmm1{k1}{z},ymm3
    vpsubb      zmm1{k1}{z},zmm2,zmm3
    vpsubw      zmm1{k1}{z},zmm2,zmm3
    vpsubd      zmm1{k1}{z},zmm2,zmm3
    vpsubq      zmm1{k1}{z},zmm2,zmm3
    vpsubsb     zmm1{k1}{z},zmm2,zmm3
    vpsubsw     zmm1{k1}{z},zmm2,zmm3
    vpsubusb    zmm1{k1}{z},zmm2,zmm3
    vpsubusw    zmm1{k1}{z},zmm2,zmm3
    vpunpckhbw  zmm1{k1}{z},zmm2,zmm3
    vpunpckhwd  zmm1{k1}{z},zmm2,zmm3
    vpunpckhdq  zmm1{k1}{z},zmm2,zmm3
    vpunpckhqdq zmm1{k1}{z},zmm2,zmm3
    vpunpcklbw  zmm1{k1}{z},zmm2,zmm3
    vpunpcklwd  zmm1{k1}{z},zmm2,zmm3
    vpunpckldq  zmm1{k1}{z},zmm2,zmm3
    vpunpcklqdq zmm1{k1}{z},zmm2,zmm3
    vshufpd     zmm1{k1}{z},zmm2,zmm3,7
    vshufps     zmm1{k1}{z},zmm2,zmm3,7
    vunpckhpd   zmm1{k1}{z},zmm2,zmm3
    vunpckhps   zmm1{k1}{z},zmm2,zmm3
    vunpcklpd   zmm1{k1}{z},zmm2,zmm3
    vunpcklps   zmm1{k1}{z},zmm2,zmm3

    vcvtps2dq   ymm1{k1}{z},[rax]
    vpalignr    zmm1{k1}{z},zmm2,[rax],7
    vpmovsxwd   zmm1{k1}{z},[rax]
    vpmovsxwq   zmm1{k1}{z},[rax]
    vpsubb      zmm1{k1}{z},zmm2,[rax]
    vpsubw      zmm1{k1}{z},zmm2,[rax]
    vpsubd      zmm1{k1}{z},zmm2,[rax]
    vpsubq      zmm1{k1}{z},zmm2,[rax]
    vpsubsb     zmm1{k1}{z},zmm2,[rax]
    vpsubsw     zmm1{k1}{z},zmm2,[rax]
    vpsubusb    zmm1{k1}{z},zmm2,[rax]
    vpsubusw    zmm1{k1}{z},zmm2,[rax]
    vpunpckhbw  zmm1{k1}{z},zmm2,[rax]
    vpunpckhwd  zmm1{k1}{z},zmm2,[rax]
    vpunpckhdq  zmm1{k1}{z},zmm2,[rax]
    vpunpckhqdq zmm1{k1}{z},zmm2,[rax]
    vpunpcklbw  zmm1{k1}{z},zmm2,[rax]
    vpunpcklwd  zmm1{k1}{z},zmm2,[rax]
    vpunpckldq  zmm1{k1}{z},zmm2,[rax]
    vpunpcklqdq zmm1{k1}{z},zmm2,[rax]
    vshufpd     zmm1{k1}{z},zmm2,[rax],7
    vshufps     zmm1{k1}{z},zmm2,[rax],7
    vunpckhpd   zmm1{k1}{z},zmm2,[rax]
    vunpckhps   zmm1{k1}{z},zmm2,[rax]
    vunpcklpd   zmm1{k1}{z},zmm2,[rax]
    vunpcklps   zmm1{k1}{z},zmm2,[rax]

    vpsllw      xmm1{k1}{z},xmm2,xmm3
    vpsllw      ymm1{k1}{z},ymm2,xmm3
    vpsllw      zmm1{k1}{z},zmm2,xmm3
    vpsllw      xmm1{k1}{z},xmm2,[rax]
    vpsllw      ymm1{k1}{z},ymm2,[rax]
    vpsllw      zmm1{k1}{z},zmm2,[rax]

    vpsllw      xmm1{k1}{z},xmm2,7
    vpsllw      ymm1{k1}{z},ymm2,7
    vpsllw      zmm1{k1}{z},zmm2,7
    vpsllw      xmm1{k1}{z},[rax],7
    vpsllw      ymm1{k1}{z},[rax],7
    vpsllw      zmm1{k1}{z},[rax],7

    vpermw      xmm1, xmm2, xmm3
    vpermw      ymm1, ymm2, ymm3
    vpermw      zmm1, zmm2, zmm3
    vpermw      zmm3, zmm2, zmm1

    vpsravw     xmm1, xmm2, xmm3
    vpsravw     ymm1, ymm2, ymm3
    vpsravw     zmm1, zmm2, zmm3

    vpsravq     xmm1, xmm2, xmm3
    vpsravq     ymm1, ymm2, ymm3
    vpsravq     zmm1, zmm2, zmm3

    vpsrlvw     xmm1, xmm2, xmm3
    vpsrlvw     ymm1, ymm2, ymm3
    vpsrlvw     zmm1, zmm2, zmm3

    vpermw      zmm1{k1},zmm2,zmm3
    vpermw      zmm1{k1}{z},zmm2,zmm3
    vpermw      zmm1{k2}{z},zmm2,zmm3
    vpermw      zmm1{k3}{z},zmm2,zmm3
    vpermw      zmm1{k4}{z},zmm2,zmm3
    vpermw      zmm1{k5}{z},zmm2,zmm3
    vpermw      zmm1{k6}{z},zmm2,zmm3
    vpermw      zmm1{k7}{z},zmm2,zmm3

    vpermw      xmm1,xmm2,[rax]
    vpermw      xmm1{k1},xmm2,[rax]
    vpermw      xmm1{k1}{z},xmm2,[rax]
    vpermw      xmm1{k2}{z},xmm2,[rax]
    vpermw      xmm1{k3}{z},xmm2,[rax]
    vpermw      xmm1{k4}{z},xmm2,[rax]
    vpermw      xmm1{k5}{z},xmm2,[rax]
    vpermw      xmm1{k6}{z},xmm2,[rax]
    vpermw      xmm1{k7}{z},xmm2,[rax]

    vpermw      ymm1,ymm2,[rax]
    vpermw      ymm1{k1},ymm2,[rax]
    vpermw      ymm1{k1}{z},ymm2,[rax]
    vpermw      ymm1{k2}{z},ymm2,[rax]
    vpermw      ymm1{k3}{z},ymm2,[rax]
    vpermw      ymm1{k4}{z},ymm2,[rax]
    vpermw      ymm1{k5}{z},ymm2,[rax]
    vpermw      ymm1{k6}{z},ymm2,[rax]
    vpermw      ymm1{k7}{z},ymm2,[rax]

    vpermw      zmm1,zmm2,[rax]
    vpermw      zmm1{k1},zmm2,[rax]
    vpermw      zmm1{k1}{z},zmm2,[rax]
    vpermw      zmm1{k2}{z},zmm2,[rax]
    vpermw      zmm1{k3}{z},zmm2,[rax]
    vpermw      zmm1{k4}{z},zmm2,[rax]
    vpermw      zmm1{k5}{z},zmm2,[rax]
    vpermw      zmm1{k6}{z},zmm2,[rax]
    vpermw      zmm1{k7}{z},zmm2,[rax]

    vpermw      zmm21,zmm2, zmm3
    vpermw      zmm21,zmm21,zmm3
    vpermw      zmm21,zmm21,zmm31
    vpermw      zmm21,zmm2, zmm31
    vpermw      zmm1, zmm2, zmm31
    vpermw      zmm1, zmm20,zmm31
    vpermw      zmm1, zmm20,zmm3

    vpandd      zmm1{k1}{z},zmm2,zmm3
    vpandq      zmm1{k1}{z},zmm2,zmm3
    vpandnd     zmm1{k1}{z},zmm2,zmm3
    vpandnq     zmm1{k1}{z},zmm2,zmm3
    vpxord      zmm1{k1}{z},zmm2,zmm3
    vpxorq      zmm1{k1}{z},zmm2,zmm3

    vpsraq      xmm1{k1}{z},xmm2,xmm3
    vpsraq      ymm1{k1}{z},ymm2,xmm3
    vpsraq      zmm1{k1}{z},zmm2,xmm3
    vpsraq      xmm1{k1}{z},xmm2,[rax]
    vpsraq      ymm1{k1}{z},ymm2,[rax]
    vpsraq      zmm1{k1}{z},zmm2,[rax]

    vpsraq      xmm1{k1}{z},xmm2,7
    vpsraq      ymm1{k1}{z},ymm2,7
    vpsraq      zmm1{k1}{z},zmm2,7
    vpsraq      xmm1{k1}{z},[rax],7
    vpsraq      ymm1{k1}{z},[rax],7
    vpsraq      zmm1{k1}{z},[rax],7

    vpconflictd zmm30,zmm1
    vpconflictd zmm30,zmm31
    vpconflictd zmm1,zmm31
    vpconflictd zmm3,zmm1
    vpconflictd xmm27,xmm3
    vpconflictd ymm27,ymm3

    vpconflictd zmm30,zmm29
    vpconflictd zmm30{k7},zmm29
    vpconflictd zmm30{k7}{z},zmm29
    vpconflictd zmm30,zmmword ptr [rcx]
    vpconflictd zmm30,zmmword ptr [rax+r14*8+0x123]
    vpconflictd zmm30,dword ptr [rcx]{1to16}
    vpconflictd zmm30,zmmword ptr [rdx+0x1fc0]
    vpconflictd zmm30,zmmword ptr [rdx+0x2000]
    vpconflictd zmm30,zmmword ptr [rdx-0x2000]
    vpconflictd zmm30,zmmword ptr [rdx-0x2040]
    vpconflictd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpconflictd zmm30,dword ptr [rdx+0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x204]{1to16}
    vpconflictq zmm30,zmm29
    vpconflictq zmm30{k7},zmm29
    vpconflictq zmm30{k7}{z},zmm29
    vpconflictq zmm30,zmmword ptr [rcx]
    vpconflictq zmm30,zmmword ptr [rax+r14*8+0x123]
    vpconflictq zmm30,qword ptr [rcx]{1to8}
    vpconflictq zmm30,zmmword ptr [rdx+0x1fc0]
    vpconflictq zmm30,zmmword ptr [rdx+0x2000]
    vpconflictq zmm30,zmmword ptr [rdx-0x2000]
    vpconflictq zmm30,zmmword ptr [rdx-0x2040]
    vpconflictq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpconflictq zmm30,qword ptr [rdx+0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x408]{1to8}

    vplzcntd    zmm30,zmm29
    vplzcntd    zmm30{k7},zmm29
    vplzcntd    zmm30{k7}{z},zmm29
    vplzcntd    zmm30,zmmword ptr [rcx]
    vplzcntd    zmm30,zmmword ptr [rax+r14*8+0x123]
    vplzcntd    zmm30,dword ptr [rcx]{1to16}
    vplzcntd    zmm30,zmmword ptr [rdx+0x1fc0]
    vplzcntd    zmm30,zmmword ptr [rdx+0x2000]
    vplzcntd    zmm30,zmmword ptr [rdx-0x2000]
    vplzcntd    zmm30,zmmword ptr [rdx-0x2040]
    vplzcntd    zmm30,dword ptr [rdx+0x1fc]{1to16}
    vplzcntd    zmm30,dword ptr [rdx+0x200]{1to16}
    vplzcntd    zmm30,dword ptr [rdx-0x200]{1to16}
    vplzcntd    zmm30,dword ptr [rdx-0x204]{1to16}
    vplzcntq    zmm30,zmm29
    vplzcntq    zmm30{k7},zmm29
    vplzcntq    zmm30{k7}{z},zmm29
    vplzcntq    zmm30,zmmword ptr [rcx]
    vplzcntq    zmm30,zmmword ptr [rax+r14*8+0x123]
    vplzcntq    zmm30,qword ptr [rcx]{1to8}
    vplzcntq    zmm30,zmmword ptr [rdx+0x1fc0]
    vplzcntq    zmm30,zmmword ptr [rdx+0x2000]
    vplzcntq    zmm30,zmmword ptr [rdx-0x2000]
    vplzcntq    zmm30,zmmword ptr [rdx-0x2040]
    vplzcntq    zmm30,qword ptr [rdx+0x3f8]{1to8}
    vplzcntq    zmm30,qword ptr [rdx+0x400]{1to8}
    vplzcntq    zmm30,qword ptr [rdx-0x400]{1to8}
    vplzcntq    zmm30,qword ptr [rdx-0x408]{1to8}

    vptestnmd   k5,zmm29,zmm28
    vptestnmd   k5{k7},zmm29,zmm28
    vptestnmd   k5,zmm29,zmmword ptr [rcx]
    vptestnmd   k5,zmm29,zmmword ptr [rax+r14*8+0x123]
    vptestnmd   k5,zmm29,dword ptr [rcx]{1to16}
    vptestnmd   k5,zmm29,zmmword ptr [rdx+0x1fc0]
    vptestnmd   k5,zmm29,zmmword ptr [rdx+0x2000]
    vptestnmd   k5,zmm29,zmmword ptr [rdx-0x2000]
    vptestnmd   k5,zmm29,zmmword ptr [rdx-0x2040]
    vptestnmd   k5,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx+0x200]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx-0x200]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx-0x204]{1to16}
    vptestnmq   k5,zmm29,zmm28
    vptestnmq   k5{k7},zmm29,zmm28
    vptestnmq   k5,zmm29,zmmword ptr [rcx]
    vptestnmq   k5,zmm29,zmmword ptr [rax+r14*8+0x123]
    vptestnmq   k5,zmm29,qword ptr [rcx]{1to8}
    vptestnmq   k5,zmm29,zmmword ptr [rdx+0x1fc0]
    vptestnmq   k5,zmm29,zmmword ptr [rdx+0x2000]
    vptestnmq   k5,zmm29,zmmword ptr [rdx-0x2000]
    vptestnmq   k5,zmm29,zmmword ptr [rdx-0x2040]
    vptestnmq   k5,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vptestnmq   k5,zmm29,qword ptr [rdx+0x400]{1to8}
    vptestnmq   k5,zmm29,qword ptr [rdx-0x400]{1to8}
    vptestnmq   k5,zmm29,qword ptr [rdx-0x408]{1to8}

    vpbroadcastmw2d zmm30,k6
    vpbroadcastmb2q zmm30,k6

    kaddb       k1,k2,k3
    kaddw       k1,k2,k3
    kandb       k1,k2,k3
    kandw       k1,k2,k3
    kandnb      k1,k2,k3
    kandnw      k1,k2,k3
    korb        k1,k2,k3
    korw        k1,k2,k3
    kxorb       k1,k2,k3
    kxorw       k1,k2,k3
    kxnorb      k1,k2,k3
    kxnorw      k1,k2,k3

    kunpckbw    k1,k2,k3
    kunpckwd    k1,k2,k3

    kaddd       k1,k2,k3
    kaddq       k1,k2,k3
    kandd       k1,k2,k3
    kandq       k1,k2,k3
    kandnd      k1,k2,k3
    kandnq      k1,k2,k3
    kord        k1,k2,k3
    korq        k1,k2,k3
    kxord       k1,k2,k3
    kxorq       k1,k2,k3
    kxnord      k1,k2,k3
    kxnorq      k1,k2,k3
    kunpckdq    k1,k2,k3

    knotb       k1,k2
    knotw       k1,k2
    knotd       k1,k2
    knotq       k1,k2

    kortestb    k1,k2
    kortestw    k1,k2
    kortestd    k1,k2
    kortestq    k1,k2
    kshiftlb    k1,k2,3
    kshiftlw    k1,k2,3
    kshiftld    k1,k2,3
    kshiftlq    k1,k2,3
    kshiftrb    k1,k2,3
    kshiftrw    k1,k2,3
    kshiftrd    k1,k2,3
    kshiftrq    k1,k2,3

    kmovb       k1,k2
    kmovd       k1,k2
    kmovq       k1,k2
    kmovw       k1,k2
    kmovb       k1,[rax]
    kmovd       k1,[rax]
    kmovq       k1,[rax]
    kmovw       k1,[rax]
    kmovb       [rax],k2
    kmovd       [rax],k2
    kmovq       [rax],k2
    kmovw       [rax],k2

    end
