;
; v2.26 -- AVX-512
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
    vpconflictd zmm30,zword ptr [rcx]
    vpconflictd zmm30,zword ptr [rax+r14*8+0x123]
    vpconflictd zmm30,dword ptr [rcx]{1to16}
    vpconflictd zmm30,zword ptr [rdx+0x1fc0]
    vpconflictd zmm30,zword ptr [rdx+0x2000]
    vpconflictd zmm30,zword ptr [rdx-0x2000]
    vpconflictd zmm30,zword ptr [rdx-0x2040]
    vpconflictd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpconflictd zmm30,dword ptr [rdx+0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x204]{1to16}
    vpconflictq zmm30,zmm29
    vpconflictq zmm30{k7},zmm29
    vpconflictq zmm30{k7}{z},zmm29
    vpconflictq zmm30,zword ptr [rcx]
    vpconflictq zmm30,zword ptr [rax+r14*8+0x123]
    vpconflictq zmm30,qword ptr [rcx]{1to8}
    vpconflictq zmm30,zword ptr [rdx+0x1fc0]
    vpconflictq zmm30,zword ptr [rdx+0x2000]
    vpconflictq zmm30,zword ptr [rdx-0x2000]
    vpconflictq zmm30,zword ptr [rdx-0x2040]
    vpconflictq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpconflictq zmm30,qword ptr [rdx+0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x408]{1to8}

    vplzcntd    zmm30,zmm29
    vplzcntd    zmm30{k7},zmm29
    vplzcntd    zmm30{k7}{z},zmm29
    vplzcntd    zmm30,zword ptr [rcx]
    vplzcntd    zmm30,zword ptr [rax+r14*8+0x123]
    vplzcntd    zmm30,dword ptr [rcx]{1to16}
    vplzcntd    zmm30,zword ptr [rdx+0x1fc0]
    vplzcntd    zmm30,zword ptr [rdx+0x2000]
    vplzcntd    zmm30,zword ptr [rdx-0x2000]
    vplzcntd    zmm30,zword ptr [rdx-0x2040]
    vplzcntd    zmm30,dword ptr [rdx+0x1fc]{1to16}
    vplzcntd    zmm30,dword ptr [rdx+0x200]{1to16}
    vplzcntd    zmm30,dword ptr [rdx-0x200]{1to16}
    vplzcntd    zmm30,dword ptr [rdx-0x204]{1to16}
    vplzcntq    zmm30,zmm29
    vplzcntq    zmm30{k7},zmm29
    vplzcntq    zmm30{k7}{z},zmm29
    vplzcntq    zmm30,zword ptr [rcx]
    vplzcntq    zmm30,zword ptr [rax+r14*8+0x123]
    vplzcntq    zmm30,qword ptr [rcx]{1to8}
    vplzcntq    zmm30,zword ptr [rdx+0x1fc0]
    vplzcntq    zmm30,zword ptr [rdx+0x2000]
    vplzcntq    zmm30,zword ptr [rdx-0x2000]
    vplzcntq    zmm30,zword ptr [rdx-0x2040]
    vplzcntq    zmm30,qword ptr [rdx+0x3f8]{1to8}
    vplzcntq    zmm30,qword ptr [rdx+0x400]{1to8}
    vplzcntq    zmm30,qword ptr [rdx-0x400]{1to8}
    vplzcntq    zmm30,qword ptr [rdx-0x408]{1to8}

    vptestnmd   k5,zmm29,zmm28
    vptestnmd   k5{k7},zmm29,zmm28
    vptestnmd   k5,zmm29,zword ptr [rcx]
    vptestnmd   k5,zmm29,zword ptr [rax+r14*8+0x123]
    vptestnmd   k5,zmm29,dword ptr [rcx]{1to16}
    vptestnmd   k5,zmm29,zword ptr [rdx+0x1fc0]
    vptestnmd   k5,zmm29,zword ptr [rdx+0x2000]
    vptestnmd   k5,zmm29,zword ptr [rdx-0x2000]
    vptestnmd   k5,zmm29,zword ptr [rdx-0x2040]
    vptestnmd   k5,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx+0x200]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx-0x200]{1to16}
    vptestnmd   k5,zmm29,dword ptr [rdx-0x204]{1to16}
    vptestnmq   k5,zmm29,zmm28
    vptestnmq   k5{k7},zmm29,zmm28
    vptestnmq   k5,zmm29,zword ptr [rcx]
    vptestnmq   k5,zmm29,zword ptr [rax+r14*8+0x123]
    vptestnmq   k5,zmm29,qword ptr [rcx]{1to8}
    vptestnmq   k5,zmm29,zword ptr [rdx+0x1fc0]
    vptestnmq   k5,zmm29,zword ptr [rdx+0x2000]
    vptestnmq   k5,zmm29,zword ptr [rdx-0x2000]
    vptestnmq   k5,zmm29,zword ptr [rdx-0x2040]
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

    vexp2ps zmm30,zmm29
    vexp2ps zmm30,zword ptr [rcx]
    vexp2ps zmm30,zword ptr [rax+r14*8+0x123]
    vexp2ps zmm30,dword ptr [rcx]{1to16}
    vexp2ps zmm30,zword ptr [rdx+0x1fc0]
    vexp2ps zmm30,zword ptr [rdx+0x2000]
    vexp2ps zmm30,zword ptr [rdx-0x2000]
    vexp2ps zmm30,zword ptr [rdx-0x2040]
    vexp2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vexp2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vexp2pd zmm30,zmm29
    vexp2pd zmm30,zword ptr [rcx]
    vexp2pd zmm30,zword ptr [rax+r14*8+0x123]
    vexp2pd zmm30,qword ptr [rcx]{1to8}
    vexp2pd zmm30,zword ptr [rdx+0x1fc0]
    vexp2pd zmm30,zword ptr [rdx+0x2000]
    vexp2pd zmm30,zword ptr [rdx-0x2000]
    vexp2pd zmm30,zword ptr [rdx-0x2040]
    vexp2pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vexp2pd zmm30,qword ptr [rdx+0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp28ps zmm30,zmm29
    vrcp28ps zmm30{k7},zmm29
    vrcp28ps zmm30{k7}{z},zmm29
    vrcp28ps zmm30,zword ptr [rcx]
    vrcp28ps zmm30,zword ptr [rax+r14*8+0x123]
    vrcp28ps zmm30,dword ptr [rcx]{1to16}
    vrcp28ps zmm30,zword ptr [rdx+0x1fc0]
    vrcp28ps zmm30,zword ptr [rdx+0x2000]
    vrcp28ps zmm30,zword ptr [rdx-0x2000]
    vrcp28ps zmm30,zword ptr [rdx-0x2040]
    vrcp28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrcp28pd zmm30,zmm29
    vrcp28pd zmm30{k7},zmm29
    vrcp28pd zmm30{k7}{z},zmm29
    vrcp28pd zmm30,zword ptr [rcx]
    vrcp28pd zmm30,zword ptr [rax+r14*8+0x123]
    vrcp28pd zmm30,qword ptr [rcx]{1to8}
    vrcp28pd zmm30,zword ptr [rdx+0x1fc0]
    vrcp28pd zmm30,zword ptr [rdx+0x2000]
    vrcp28pd zmm30,zword ptr [rdx-0x2000]
    vrcp28pd zmm30,zword ptr [rdx-0x2040]
    vrcp28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp28ss xmm30{k7},xmm29,xmm28
    vrcp28ss xmm30{k7}{z},xmm29,xmm28
    vrcp28ss xmm30{k7},xmm29,dword ptr [rcx]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vrcp28sd xmm30{k7},xmm29,xmm28
    vrcp28sd xmm30{k7}{z},xmm29,xmm28
    vrcp28sd xmm30{k7},xmm29,qword ptr [rcx]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt28ps zmm30,zmm29
    vrsqrt28ps zmm30{k7},zmm29
    vrsqrt28ps zmm30{k7}{z},zmm29
    vrsqrt28ps zmm30,zword ptr [rcx]
    vrsqrt28ps zmm30,zword ptr [rax+r14*8+0x123]
    vrsqrt28ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt28ps zmm30,zword ptr [rdx+0x1fc0]
    vrsqrt28ps zmm30,zword ptr [rdx+0x2000]
    vrsqrt28ps zmm30,zword ptr [rdx-0x2000]
    vrsqrt28ps zmm30,zword ptr [rdx-0x2040]
    vrsqrt28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrsqrt28pd zmm30,zmm29
    vrsqrt28pd zmm30{k7},zmm29
    vrsqrt28pd zmm30{k7}{z},zmm29
    vrsqrt28pd zmm30,zword ptr [rcx]
    vrsqrt28pd zmm30,zword ptr [rax+r14*8+0x123]
    vrsqrt28pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt28pd zmm30,zword ptr [rdx+0x1fc0]
    vrsqrt28pd zmm30,zword ptr [rdx+0x2000]
    vrsqrt28pd zmm30,zword ptr [rdx-0x2000]
    vrsqrt28pd zmm30,zword ptr [rdx-0x2040]
    vrsqrt28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x408]{1to8}
    vrsqrt28ss xmm30{k7},xmm29,xmm28
    vrsqrt28ss xmm30{k7}{z},xmm29,xmm28
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rcx]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vrsqrt28sd xmm30{k7},xmm29,xmm28
    vrsqrt28sd xmm30{k7}{z},xmm29,xmm28
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rcx]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt14ps zmm1,zmm2
    vrsqrt14ps zmm1,[rax]
    vrsqrt14ps zmm30,zmm29
    vrsqrt14ps zmm30{k7},zmm29
    vrsqrt14ps zmm30{k7}{z},zmm29
    vrsqrt14ps zmm30,zword ptr [rcx]
    vrsqrt14ps zmm30,zword ptr [rax+r14*8+0x123]
    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,zword ptr [rdx+0x1fc0]
    vrsqrt14ps zmm30,zword ptr [rdx+0x2000]
    vrsqrt14ps zmm30,zword ptr [rdx-0x2000]
    vrsqrt14ps zmm30,zword ptr [rdx-0x2040]
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrsqrt14pd zmm30,zmm29
    vrsqrt14pd zmm30{k7},zmm29
    vrsqrt14pd zmm30{k7}{z},zmm29
    vrsqrt14pd zmm30,zword ptr [rcx]
    vrsqrt14pd zmm30,zword ptr [rax+r14*8+0x123]
    vrsqrt14pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt14pd zmm30,zword ptr [rdx+0x1fc0]
    vrsqrt14pd zmm30,zword ptr [rdx+0x2000]
    vrsqrt14pd zmm30,zword ptr [rdx-0x2000]
    vrsqrt14pd zmm30,zword ptr [rdx-0x2040]
    vrsqrt14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x408]{1to8}
    vrsqrt14ps zmm30,zmm29
    vrsqrt14ps zmm30{k7},zmm29
    vrsqrt14ps zmm30{k7}{z},zmm29
    vrsqrt14ps zmm30,zword ptr [rcx]
    vrsqrt14ps zmm30,zword ptr [rax+r14*8+0x123]
    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,zword ptr [rdx+0x1fc0]
    vrsqrt14ps zmm30,zword ptr [rdx+0x2000]
    vrsqrt14ps zmm30,zword ptr [rdx-0x2000]
    vrsqrt14ps zmm30,zword ptr [rdx-0x2040]
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrsqrt14sd xmm30{k7},xmm29,xmm28
    vrsqrt14sd xmm30{k7}{z},xmm29,xmm28
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rcx]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt14ss xmm1,xmm2,xmm3
    vrsqrt14ss xmm1,xmm2,[rax]
    vrsqrt14ss xmm30,xmm29,xmm3
    vrsqrt14ss xmm30{k7},xmm29,xmm3
    vrsqrt14ss xmm30{k7}{z},xmm29,xmm3
    vrsqrt14ss xmm30,xmm3,dword ptr [rcx]
    vrsqrt14ss xmm30,xmm3,dword ptr [rax+r14*8+0x123]
    vrsqrt14ss xmm30,xmm3,dword ptr [rcx]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x1fc0]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x2000]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x2000]
    vrsqrt14ss xmm30,xmm3,xmmword ptr [rdx-0x2040]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x1fc]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x200]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x200]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x204]

    vrsqrt14ss xmm30{k7},xmm29,xmm28
    vrsqrt14ss xmm30{k7}{z},xmm29,xmm28
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rcx]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vmovdqa32 xmm1{k1}{z},xmm2
    vmovdqa32 xmm2{k1}{z},xmm1
    vmovdqa32 ymm1{k1}{z},ymm2
    vmovdqa32 ymm2{k1}{z},ymm1
    vmovdqa32 zmm1{k1}{z},zmm2
    vmovdqa32 zmm2{k1}{z},zmm1

    vmovdqa32 xmm1{k1}{z},[rcx]
    vmovdqa32 [rcx], xmm1
    vmovdqa32 ymm1{k1}{z},[rcx]
    vmovdqa32 [rcx],ymm1
    vmovdqa32 zmm1{k1}{z},[rcx]
    vmovdqa32 [rcx], zmm1

    vmovdqa64 xmm1{k1}{z},xmm2
    vmovdqa64 xmm2{k1}{z},xmm1
    vmovdqa64 ymm1{k1}{z},ymm2
    vmovdqa64 ymm2{k1}{z},ymm1
    vmovdqa64 zmm1{k1}{z},zmm2
    vmovdqa64 zmm2{k1}{z},zmm1

    vmovdqa64 xmm1{k1}{z},[rcx]
    vmovdqa64 [rcx], xmm1
    vmovdqa64 ymm1{k1}{z},[rcx]
    vmovdqa64 [rcx],ymm1
    vmovdqa64 zmm1{k1}{z},[rcx]
    vmovdqa64 [rcx], zmm1

    vmovdqu8 xmm1{k1}{z},xmm2
    vmovdqu8 xmm2{k1}{z},xmm1
    vmovdqu8 ymm1{k1}{z},ymm2
    vmovdqu8 ymm2{k1}{z},ymm1
    vmovdqu8 zmm1{k1}{z},zmm2
    vmovdqu8 zmm2{k1}{z},zmm1

    vmovdqu8 xmm1{k1}{z},[rax]
    vmovdqu8 [rax],xmm1
    vmovdqu8 ymm1{k1}{z},[rax]
    vmovdqu8 [rax],ymm1
    vmovdqu8 zmm1{k1}{z},[rax]
    vmovdqu8 [rax],zmm1

    vmovdqu16 xmm1{k1}{z},xmm2
    vmovdqu16 xmm2{k1}{z},xmm1
    vmovdqu16 ymm1{k1}{z},ymm2
    vmovdqu16 ymm2{k1}{z},ymm1
    vmovdqu16 zmm1{k1}{z},zmm2
    vmovdqu16 zmm2{k1}{z},zmm1

    vmovdqu16 xmm1{k1}{z},[rax]
    vmovdqu16 [rax],xmm1
    vmovdqu16 ymm1{k1}{z},[rax]
    vmovdqu16 [rax],ymm1
    vmovdqu16 zmm1{k1}{z},[rax]
    vmovdqu16 [rax],zmm1

    vmovdqu32 xmm1{k1}{z},xmm2
    vmovdqu32 xmm2{k1}{z},xmm1
    vmovdqu32 ymm1{k1}{z},ymm2
    vmovdqu32 ymm2{k1}{z},ymm1
    vmovdqu32 zmm1{k1}{z},zmm2
    vmovdqu32 zmm2{k1}{z},zmm1

    vmovdqu32 xmm1{k1}{z},[rax]
    vmovdqu32 [rax],xmm1
    vmovdqu32 ymm1{k1}{z},[rax]
    vmovdqu32 [rax],ymm1
    vmovdqu32 zmm1{k1}{z},[rax]
    vmovdqu32 [rax],zmm1

    vmovdqu64 xmm1{k1}{z},xmm2
    vmovdqu64 xmm2{k1}{z},xmm1
    vmovdqu64 ymm1{k1}{z},ymm2
    vmovdqu64 ymm2{k1}{z},ymm1
    vmovdqu64 zmm1{k1}{z},zmm2
    vmovdqu64 zmm2{k1}{z},zmm1

    vmovdqu64 xmm1{k1}{z},[rax]
    vmovdqu64 [rax],xmm1
    vmovdqu64 ymm1{k1}{z},[rax]
    vmovdqu64 [rax],ymm1
    vmovdqu64 zmm1{k1}{z},[rax]
    vmovdqu64 [rax],zmm1

    vbroadcastf32x2 ymm1{k1}{z},xmm2
    vbroadcastf32x2 zmm1{k1}{z},xmm2
    vbroadcastf32x2 ymm1,[rax]
    vbroadcastf32x2 zmm1,[rax]
    vbroadcastf32x2 ymm1,qword ptr [rax]
    vbroadcastf32x2 zmm1,qword ptr [rax]

    vbroadcastf32x4 ymm1{k1}{z},[rax]
    vbroadcastf32x4 zmm1{k1}{z},[rax]
    vbroadcastf32x8 zmm1{k1}{z},[rax]
    vbroadcastf64x2 ymm1{k1}{z},[rax]
    vbroadcastf64x2 zmm1{k1}{z},[rax]
    vbroadcastf64x4 zmm1{k1}{z},[rax]

    vbroadcastf32x4 ymm1,oword ptr [rax]
    vbroadcastf32x4 zmm1,oword ptr [rax]
    vbroadcastf32x8 zmm1,yword ptr [rax]
    vbroadcastf64x2 ymm1,oword ptr [rax]
    vbroadcastf64x2 zmm1,oword ptr [rax]
    vbroadcastf64x4 zmm1,yword ptr [rax]

    vcompresspd xmm1,xmm2
    vcompresspd [rcx],xmm2
    vcompresspd ymm1,ymm2
    vcompresspd [rcx],ymm2
    vcompressps zmm1,zmm2
    vcompressps [rcx],zmm2

    vcompresspd zmm1,zmm2
    vcompresspd [rcx],zmm2
    vcompresspd zword ptr [rcx],zmm30
    vcompresspd zword ptr [rcx]{k7},zmm30
    vcompresspd zword ptr [rax+r14*8+0x123],zmm30
    vcompresspd zword ptr [rdx+0x3f8],zmm30
    vcompresspd zword ptr [rdx+0x400],zmm30
    vcompresspd zword ptr [rdx-0x400],zmm30
    vcompresspd zword ptr [rdx-0x408],zmm30
    vcompresspd zmm30,zmm29
    vcompresspd zmm30{k7},zmm29
    vcompresspd zmm30{k7}{z},zmm29

    vcompressps zword ptr [rcx],zmm30
    vcompressps zword ptr [rcx]{k7},zmm30
    vcompressps zword ptr [rax+r14*8+0x123],zmm30
    vcompressps zword ptr [rdx+0x1fc],zmm30
    vcompressps zword ptr [rdx+0x200],zmm30
    vcompressps zword ptr [rdx-0x200],zmm30
    vcompressps zword ptr [rdx-0x204],zmm30
    vcompressps zmm30,zmm29
    vcompressps zmm30{k7},zmm29
    vcompressps zmm30{k7}{z},zmm29

    vcvtpd2qq xmm1{k1}{z},xmm2
    vcvtpd2qq ymm1{k1}{z},ymm2
    vcvtpd2qq zmm1{k1}{z},zmm2
    vcvtpd2qq xmm1,[rax]
    vcvtpd2qq ymm1,[rax]
    vcvtpd2qq zmm1,[rax]
    vcvtpd2qq xmm1,oword ptr [rax]
    vcvtpd2qq ymm1,yword ptr [rax]
    vcvtpd2qq zmm1,zword ptr [rax]

    vcvtpd2qq xmm16,xmm20
    vcvtpd2qq ymm16,ymm20
    vcvtpd2qq zmm16,zmm20

    vcvtps2qq xmm1{k1}{z},xmm2
    vcvtps2qq ymm1{k1}{z},xmm2
    vcvtps2qq zmm1{k1}{z},ymm2
    vcvtps2qq xmm1,[rax]
    vcvtps2qq ymm1,[rax]
    vcvtps2qq zmm1,[rax]
    vcvtps2qq xmm1,qword ptr [rax]
    vcvtps2qq ymm1,oword ptr [rax]
    vcvtps2qq zmm1,yword ptr [rax]

    vcvtps2qq xmm16,[rax]
    vcvtps2qq ymm16,[rax]
    vcvtps2qq zmm16,[rax]

    vcvtpd2udq xmm1{k1}{z},xmm2
    vcvtpd2udq xmm1{k1}{z},ymm2
    vcvtpd2udq ymm1{k1}{z},zmm2
    vcvtpd2udq xmm1,oword ptr [rax]
    vcvtpd2udq xmm1,yword ptr [rax]
    vcvtpd2udq ymm1,zword ptr [rax]

    vcvtps2udq xmm1{k1}{z},xmm2
    vcvtps2udq ymm1{k1}{z},ymm2
    vcvtps2udq zmm1{k1}{z},zmm2
    vcvtps2udq xmm1,[rax]
    vcvtps2udq ymm1,[rax]
    vcvtps2udq zmm1,[rax]

    vcvtpd2uqq xmm1 {k1}{z}, xmm2
    vcvtpd2uqq ymm1 {k1}{z}, ymm2
    vcvtpd2uqq zmm1 {k1}{z}, zmm2
    vcvtpd2uqq xmm1, oword ptr [rax]
    vcvtpd2uqq ymm1, yword ptr [rax]
    vcvtpd2uqq zmm1, zword ptr [rax]
    vcvtpd2uqq xmm1, [rax]
    vcvtpd2uqq ymm1, [rax]
    vcvtpd2uqq zmm1, [rax]

    vcvtps2uqq xmm1 {k1}{z}, xmm2
    vcvtps2uqq ymm1 {k1}{z}, xmm2
    vcvtps2uqq zmm1 {k1}{z}, ymm2
    vcvtps2uqq xmm1, qword ptr [rax]
    vcvtps2uqq ymm1, oword ptr [rax]
    vcvtps2uqq zmm1, yword ptr [rax]
    vcvtps2uqq xmm1, [rax]
    vcvtps2uqq ymm1, [rax]
    vcvtps2uqq zmm1, [rax]

    vcvtph2ps xmm1{k1}{z},xmm2 ; vex
    vcvtph2ps ymm1{k1}{z},xmm2
    vcvtph2ps zmm1{k1}{z},ymm2 ; evex
    vcvtph2ps xmm1,qword ptr [rax]
    vcvtph2ps ymm1,oword ptr [rax]
    vcvtph2ps zmm1,yword ptr [rax]
    vcvtph2ps xmm1,[rax]
    vcvtph2ps ymm1,[rax]
    vcvtph2ps zmm1,[rax]

    vcvtps2ph xmm1{k1}{z},ymm2,3
    vcvtps2ph xmm1{k1}{z},xmm2,3
    vcvtps2ph ymm1{k1}{z},zmm2,3

    vcvtps2ph qword ptr [rax],xmm2,3
    vcvtps2ph oword ptr [rax],ymm2,3
    vcvtps2ph yword ptr [rax],zmm2,3

    vcvtps2ph [rax],ymm2,3
    vcvtps2ph [rax],xmm2,3
    vcvtps2ph [rax],zmm2,3

    vcvtqq2pd xmm1{k1}{z},xmm2
    vcvtqq2pd ymm1{k1}{z},ymm2
    vcvtqq2pd zmm1{k1}{z},zmm2
    vcvtqq2pd xmm1,oword ptr [rax]
    vcvtqq2pd ymm1,yword ptr [rax]
    vcvtqq2pd zmm1,zword ptr [rax]
    vcvtqq2pd xmm1,[rax]
    vcvtqq2pd ymm1,[rax]
    vcvtqq2pd zmm1,[rax]

    vcvtqq2ps xmm1{k1}{z},xmm2
    vcvtqq2ps xmm1{k1}{z},ymm2
    vcvtqq2ps ymm1{k1}{z},zmm2
    vcvtqq2ps xmm1,oword ptr [rax]
    vcvtqq2ps xmm1,yword ptr [rax]
    vcvtqq2ps ymm1,zword ptr [rax]

    vcvttpd2qq xmm1{k1}{z},xmm2
    vcvttpd2qq ymm1{k1}{z},ymm2
    vcvttpd2qq zmm1{k1}{z},zmm2
    vcvttpd2qq xmm1,[rax]
    vcvttpd2qq ymm1,[rax]
    vcvttpd2qq zmm1,[rax]

    vcvttps2qq xmm1{k1}{z},xmm2
    vcvttps2qq ymm1{k1}{z},xmm2
    vcvttps2qq zmm1{k1}{z},ymm2
    vcvttps2qq xmm1,qword ptr [rax]
    vcvttps2qq ymm1,oword ptr [rax]
    vcvttps2qq zmm1,yword ptr [rax]

    vcvttps2udq xmm1{k1}{z},xmm2
    vcvttps2udq ymm1{k1}{z},ymm2
    vcvttps2udq zmm1{k1}{z},zmm2
    vcvttps2udq xmm1,[rax]
    vcvttps2udq ymm1,[rax]
    vcvttps2udq zmm1,[rax]

    vcvttpd2udq xmm1{k1}{z},xmm2
    vcvttpd2udq xmm1{k1}{z},ymm2
    vcvttpd2udq ymm1{k1}{z},zmm2
    vcvttpd2udq xmm1,oword ptr [rax]
    vcvttpd2udq xmm1,yword ptr [rax]
    vcvttpd2udq ymm1,zword ptr [rax]

    vcvttpd2uqq xmm1{k1}{z},xmm2
    vcvttpd2uqq ymm1{k1}{z},ymm2
    vcvttpd2uqq zmm1{k1}{z},zmm2
    vcvttpd2uqq xmm1,[rax]
    vcvttpd2uqq ymm1,[rax]
    vcvttpd2uqq zmm1,[rax]

    vcvttps2uqq xmm1{k1}{z},xmm2
    vcvttps2uqq ymm1{k1}{z},xmm2
    vcvttps2uqq zmm1{k1}{z},ymm2
    vcvttps2uqq xmm1,qword ptr [rax]
    vcvttps2uqq ymm1,oword ptr [rax]
    vcvttps2uqq zmm1,yword ptr [rax]

    vcvtudq2pd xmm1{k1}{z},xmm2
    vcvtudq2pd ymm1{k1}{z},xmm2
    vcvtudq2pd zmm1{k1}{z},ymm2
    vcvtudq2pd xmm1,qword ptr [rax]
    vcvtudq2pd ymm1,oword ptr [rax]
    vcvtudq2pd zmm1,yword ptr [rax]

    vcvtuqq2pd xmm1{k1}{z},xmm2
    vcvtuqq2pd ymm1{k1}{z},ymm2
    vcvtuqq2pd zmm1{k1}{z},zmm2
    vcvtuqq2pd xmm1,[rax]
    vcvtuqq2pd ymm1,[rax]
    vcvtuqq2pd zmm1,[rax]

    vcvtudq2ps xmm1{k1}{z},xmm2
    vcvtudq2ps ymm1{k1}{z},ymm2
    vcvtudq2ps zmm1{k1}{z},zmm2
    vcvtudq2ps xmm1,[rax]
    vcvtudq2ps ymm1,[rax]
    vcvtudq2ps zmm1,[rax]

    vcvtuqq2ps xmm1{k1}{z},xmm2
    vcvtuqq2ps xmm1{k1}{z},ymm2
    vcvtuqq2ps ymm1{k1}{z},zmm2
    vcvtuqq2ps xmm1,oword ptr [rax]
    vcvtuqq2ps xmm1,yword ptr [rax]
    vcvtuqq2ps ymm1,zword ptr [rax]

    vexpandpd xmm1{k1}{z},xmm2
    vexpandpd ymm1{k1}{z},ymm2
    vexpandpd zmm1{k1}{z},zmm2
    vexpandpd xmm1,[rax]
    vexpandpd ymm1,[rax]
    vexpandpd zmm1,[rax]

    vexpandps xmm1{k1}{z},xmm2
    vexpandps ymm1{k1}{z},ymm2
    vexpandps zmm1{k1}{z},zmm2
    vexpandps xmm1,[rax]
    vexpandps ymm1,[rax]
    vexpandps zmm1,[rax]

    vextractf32x4 xmm1{k1}{z},ymm2,3
    vextractf32x4 xmm1{k1}{z},zmm2,3
    vextractf32x4 oword ptr [rax],ymm2,3
    vextractf32x4 oword ptr [rax],zmm2,3
    vextractf64x2 xmm1{k1}{z},ymm2,3
    vextractf64x2 xmm1{k1}{z},zmm2,3
    vextractf64x2 oword ptr [rax],ymm2,3
    vextractf64x2 oword ptr [rax],zmm2,3
    vextractf32x8 ymm1{k1}{z},zmm2,3
    vextractf32x8 yword ptr [rax],zmm2,3
    vextractf64x4 ymm1{k1}{z},zmm2,3
    vextractf64x4 yword ptr [rax],zmm2,3
    vextracti32x4 xmm1{k1}{z},ymm2,3
    vextracti32x4 xmm1{k1}{z},zmm2,3
    vextracti32x4 oword ptr [rax],ymm2,3
    vextracti32x4 oword ptr [rax],zmm2,3
    vextracti64x2 xmm1{k1}{z},ymm2,3
    vextracti64x2 xmm1{k1}{z},zmm2,3
    vextracti64x2 oword ptr [rax],ymm2,3
    vextracti64x2 oword ptr [rax],zmm2,3
    vextracti32x8 ymm1{k1}{z},zmm2,3
    vextracti32x8 yword ptr [rax],zmm2,3
    vextracti64x4 ymm1{k1}{z},zmm2,3
    vextracti64x4 yword ptr [rax],zmm2,3

    vfpclasspd k2{k1},xmm2,3
    vfpclasspd k2{k1},ymm2,3
    vfpclasspd k2{k1},zmm2,3
    vfpclasspd k2,oword ptr [rax],3
    vfpclasspd k2,yword ptr [rax],3
    vfpclasspd k2,zword ptr [rax],3

    vfpclassps k2{k1},xmm2,3
    vfpclassps k2{k1},ymm2,3
    vfpclassps k2{k1},zmm2,3
    vfpclassps k2,oword ptr [rax],3
    vfpclassps k2,yword ptr [rax],3
    vfpclassps k2,zword ptr [rax],3

    vgatherdpd xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherqpd xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherdpd ymm1,qword ptr [rbp+xmm7*2+0x0],ymm2
    vgatherqpd ymm1,qword ptr [rbp+ymm7*2+0x0],ymm2
    vgatherdpd ymm6,dword ptr [xmm4*1+0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1-0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1+0x0],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1+0x298],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8-0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x0],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x298],ymm5
    vgatherdps xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherqps xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherdps ymm1,dword ptr [rbp+ymm7*2+0x0],ymm2
    vgatherqps xmm1,dword ptr [rbp+ymm7*2+0x0],xmm2
    vgatherdps xmm6,dword ptr [xmm4*1+0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1-0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1+0x0],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1+0x298],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8-0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x0],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x298],xmm5

    vpgatherdd xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherqd xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherdd ymm1,dword ptr [rbp+ymm7*2+0x0],ymm2
    vpgatherqd xmm1,dword ptr [rbp+ymm7*2+0x0],xmm2
    vpgatherdd xmm6,dword ptr [xmm4*1+0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1-0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1+0x0],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1+0x298],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8-0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x0],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x298],xmm5
    vpgatherdq xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherqq xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherdq ymm1,qword ptr [rbp+xmm7*2+0x0],ymm2
    vpgatherqq ymm1,qword ptr [rbp+ymm7*2+0x0],ymm2
    vpgatherdq ymm6,qword ptr [xmm4*1+0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1-0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1+0x0],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1+0x298],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8-0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x0],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x298],ymm5

    vgatherpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf0dpd  [r9+ymm31*1+0x100]{k1}
    vgatherpf0dpd  [rcx+ymm31*4+0x400]{k1}
    vgatherpf0dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0dps  [r9+zmm31*1+0x100]{k1}
    vgatherpf0dps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qpd  [r9+zmm31*1+0x100]{k1}
    vgatherpf0qpd  [rcx+zmm31*4+0x400]{k1}
    vgatherpf0qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qps  [r9+zmm31*1+0x100]{k1}
    vgatherpf0qps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf1dpd  [r9+ymm31*1+0x100]{k1}
    vgatherpf1dpd  [rcx+ymm31*4+0x400]{k1}
    vgatherpf1dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1dps  [r9+zmm31*1+0x100]{k1}
    vgatherpf1dps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qpd  [r9+zmm31*1+0x100]{k1}
    vgatherpf1qpd  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qps  [r9+zmm31*1+0x100]{k1}
    vgatherpf1qps  [rcx+zmm31*4+0x400]{k1}

    vscatterpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf0dpd  [r9+ymm31*1+0x100]{k1}
    vscatterpf0dpd  [rcx+ymm31*4+0x400]{k1}
    vscatterpf0dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0dps  [r9+zmm31*1+0x100]{k1}
    vscatterpf0dps  [rcx+zmm31*4+0x400]{k1}
    vscatterpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qpd  [r9+zmm31*1+0x100]{k1}
    vscatterpf0qpd  [rcx+zmm31*4+0x400]{k1}
    vscatterpf0qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qps  [r9+zmm31*1+0x100]{k1}
    vscatterpf0qps  [rcx+zmm31*4+0x400]{k1}

    vscatterpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf1dpd  [r9+ymm31*1+0x100]{k1}
    vscatterpf1dpd  [rcx+ymm31*4+0x400]{k1}
    vscatterpf1dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1dps  [r9+zmm31*1+0x100]{k1}
    vscatterpf1dps  [rcx+zmm31*4+0x400]{k1}
    vscatterpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qpd  [r9+zmm31*1+0x100]{k1}
    vscatterpf1qpd  [rcx+zmm31*4+0x400]{k1}
    vscatterpf1qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qps  [r9+zmm31*1+0x100]{k1}
    vscatterpf1qps  [rcx+zmm31*4+0x400]{k1}

    vscatterdpd  [r14+ymm31*8+0x7b]{k1},zmm30
    vscatterdpd  [r14+ymm31*8+0x7b]{k1},zmm30
    vscatterdpd  [r9+ymm31*1+0x100]{k1},zmm30
    vscatterdpd  [rcx+ymm31*4+0x400]{k1},zmm30
    vscatterdps  [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterdps  [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterdps  [r9+zmm31*1+0x100]{k1},zmm30
    vscatterdps  [rcx+zmm31*4+0x400]{k1},zmm30
    vscatterqpd  [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterqpd  [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterqpd  [r9+zmm31*1+0x100]{k1},zmm30
    vscatterqpd  [rcx+zmm31*4+0x400]{k1},zmm30

    vpscatterdd  [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterdd  [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterdd  [r9+zmm31*1+0x100]{k1},zmm30
    vpscatterdd  [rcx+zmm31*4+0x400]{k1},zmm30
    vpscatterdq  [r14+ymm31*8+0x7b]{k1},zmm30
    vpscatterdq  [r14+ymm31*8+0x7b]{k1},zmm30
    vpscatterdq  [r9+ymm31*1+0x100]{k1},zmm30
    vpscatterdq  [rcx+ymm31*4+0x400]{k1},zmm30
    vpscatterqq  [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterqq  [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterqq  [r9+zmm31*1+0x100]{k1},zmm30
    vpscatterqq  [rcx+zmm31*4+0x400]{k1},zmm30

    vgetexppd zmm30,zmm29
    vgetexppd zmm30{k7},zmm29
    vgetexppd zmm30{k7}{z},zmm29
    vgetexppd zmm30,zword ptr [rcx]
    vgetexppd zmm30,zword ptr [rax+r14*8+0x123]
    vgetexppd zmm30,qword ptr [rcx]{1to8}
    vgetexppd zmm30,zword ptr [rdx+0x1fc0]
    vgetexppd zmm30,zword ptr [rdx+0x2000]
    vgetexppd zmm30,zword ptr [rdx-0x2000]
    vgetexppd zmm30,zword ptr [rdx-0x2040]
    vgetexppd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vgetexppd zmm30,qword ptr [rdx+0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x408]{1to8}
    vgetexpps zmm30,zmm29
    vgetexpps zmm30{k7},zmm29
    vgetexpps zmm30{k7}{z},zmm29
    vgetexpps zmm30,zword ptr [rcx]
    vgetexpps zmm30,zword ptr [rax+r14*8+0x123]
    vgetexpps zmm30,dword ptr [rcx]{1to16}
    vgetexpps zmm30,zword ptr [rdx+0x1fc0]
    vgetexpps zmm30,zword ptr [rdx+0x2000]
    vgetexpps zmm30,zword ptr [rdx-0x2000]
    vgetexpps zmm30,zword ptr [rdx-0x2040]
    vgetexpps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vgetexpps zmm30,dword ptr [rdx+0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x204]{1to16}
    vgetexpsd xmm30{k7},xmm29,xmm28
    vgetexpsd xmm30{k7}{z},xmm29,xmm28
    vgetexpsd xmm30{k7},xmm29,qword ptr [rcx]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vgetexpss xmm30{k7},xmm29,xmm28
    vgetexpss xmm30{k7}{z},xmm29,xmm28
    vgetexpss xmm30{k7},xmm29,dword ptr [rcx]
    vgetexpss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vpcompressd zword ptr [rcx],zmm30
    vpcompressd zword ptr [rcx]{k7},zmm30
    vpcompressd zword ptr [rax+r14*8+0x123],zmm30
    vpcompressd zword ptr [rdx+0x1fc],zmm30
    vpcompressd zword ptr [rdx+0x200],zmm30
    vpcompressd zword ptr [rdx-0x200],zmm30
    vpcompressd zword ptr [rdx-0x204],zmm30
    vpcompressd zmm30,zmm29
    vpcompressd zmm30{k7},zmm29
    vpcompressd zmm30{k7}{z},zmm29

    vpcompressq zword ptr [rcx],zmm30
    vpcompressq zword ptr [rcx]{k7},zmm30
    vpcompressq zword ptr [rax+r14*8+0x123],zmm30
    vpcompressq zword ptr [rdx+0x3f8],zmm30
    vpcompressq zword ptr [rdx+0x400],zmm30
    vpcompressq zword ptr [rdx-0x400],zmm30
    vpcompressq zword ptr [rdx-0x408],zmm30
    vpcompressq zmm30,zmm29
    vpcompressq zmm30{k7},zmm29
    vpcompressq zmm30{k7}{z},zmm29

    vbroadcastf32x2  ymm1 {k1}{z}, xmm2
    vbroadcastf32x2  zmm1 {k1}{z}, xmm2
    vbroadcastf32x4  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcastf32x4  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcastf32x8  zmm1 {k1}{z}, yword ptr [rax]
    vbroadcastf64x2  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcastf64x2  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcastf64x4  zmm1 {k1}{z}, yword ptr [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, xmm2
    vbroadcasti32x2  ymm1 {k1}{z}, xmm2
    vbroadcasti32x2  zmm1 {k1}{z}, xmm2
    vbroadcasti32x4  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcasti32x4  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcasti32x8  zmm1 {k1}{z}, yword ptr [rax]
    vbroadcasti64x2  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcasti64x2  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcasti64x4  zmm1 {k1}{z}, yword ptr [rax]

    vbroadcastf32x2  ymm1 {k1}{z}, qword ptr [rax]
    vbroadcastf32x2  zmm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  ymm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  zmm1 {k1}{z}, qword ptr [rax]

    vbroadcastf32x2  ymm1 {k1}{z}, [rax]
    vbroadcastf32x2  zmm1 {k1}{z}, [rax]
    vbroadcastf32x4  ymm1 {k1}{z}, [rax]
    vbroadcastf32x4  zmm1 {k1}{z}, [rax]
    vbroadcastf32x8  zmm1 {k1}{z}, [rax]
    vbroadcastf64x2  ymm1 {k1}{z}, [rax]
    vbroadcastf64x2  zmm1 {k1}{z}, [rax]
    vbroadcastf64x4  zmm1 {k1}{z}, [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, [rax]
    vbroadcasti32x2  ymm1 {k1}{z}, [rax]
    vbroadcasti32x2  zmm1 {k1}{z}, [rax]
    vbroadcasti32x4  ymm1 {k1}{z}, [rax]
    vbroadcasti32x4  zmm1 {k1}{z}, [rax]
    vbroadcasti32x8  zmm1 {k1}{z}, [rax]
    vbroadcasti64x2  ymm1 {k1}{z}, [rax]
    vbroadcasti64x2  zmm1 {k1}{z}, [rax]
    vbroadcasti64x4  zmm1 {k1}{z}, [rax]

    vpexpandd zmm30,zword ptr [rcx]
    vpexpandd zmm30{k7},zword ptr [rcx]
    vpexpandd zmm30{k7}{z},zword ptr [rcx]
    vpexpandd zmm30,zword ptr [rax+r14*8+0x123]
    vpexpandd zmm30,zword ptr [rdx+0x1fc]
    vpexpandd zmm30,zword ptr [rdx+0x200]
    vpexpandd zmm30,zword ptr [rdx-0x200]
    vpexpandd zmm30,zword ptr [rdx-0x204]
    vpexpandd zmm30,zmm29
    vpexpandd zmm30{k7},zmm29
    vpexpandd zmm30{k7}{z},zmm29
    vpexpandq zmm30,zword ptr [rcx]
    vpexpandq zmm30{k7},zword ptr [rcx]
    vpexpandq zmm30{k7}{z},zword ptr [rcx]
    vpexpandq zmm30,zword ptr [rax+r14*8+0x123]
    vpexpandq zmm30,zword ptr [rdx+0x3f8]
    vpexpandq zmm30,zword ptr [rdx+0x400]
    vpexpandq zmm30,zword ptr [rdx-0x400]
    vpexpandq zmm30,zword ptr [rdx-0x408]
    vpexpandq zmm30,zmm29
    vpexpandq zmm30{k7},zmm29
    vpexpandq zmm30{k7}{z},zmm29

    vrcp14pd zmm30,zmm29
    vrcp14pd zmm30{k7},zmm29
    vrcp14pd zmm30{k7}{z},zmm29
    vrcp14pd zmm30,zword ptr [rcx]
    vrcp14pd zmm30,zword ptr [rax+r14*8+0x123]
    vrcp14pd zmm30,qword ptr [rcx]{1to8}
    vrcp14pd zmm30,zword ptr [rdx+0x1fc0]
    vrcp14pd zmm30,zword ptr [rdx+0x2000]
    vrcp14pd zmm30,zword ptr [rdx-0x2000]
    vrcp14pd zmm30,zword ptr [rdx-0x2040]
    vrcp14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x408]{1to8}
    vrcp14ps zmm30,zmm29
    vrcp14ps zmm30{k7},zmm29
    vrcp14ps zmm30{k7}{z},zmm29
    vrcp14ps zmm30,zword ptr [rcx]
    vrcp14ps zmm30,zword ptr [rax+r14*8+0x123]
    vrcp14ps zmm30,dword ptr [rcx]{1to16}
    vrcp14ps zmm30,zword ptr [rdx+0x1fc0]
    vrcp14ps zmm30,zword ptr [rdx+0x2000]
    vrcp14ps zmm30,zword ptr [rdx-0x2000]
    vrcp14ps zmm30,zword ptr [rdx-0x2040]
    vrcp14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrcp14sd xmm30{k7},xmm29,xmm28
    vrcp14sd xmm30{k7}{z},xmm29,xmm28
    vrcp14sd xmm30{k7},xmm29,qword ptr [rcx]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vrcp14ss xmm30{k7},xmm29,xmm28
    vrcp14ss xmm30{k7}{z},xmm29,xmm28
    vrcp14ss xmm30{k7},xmm29,dword ptr [rcx]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vreducepd xmm1{k1}{z},xmm2,3
    vreducepd ymm1{k1}{z},ymm2,3
    vreducepd zmm1{k1}{z},zmm2,3
    vreduceps xmm1{k1}{z},xmm2,3
    vreduceps ymm1{k1}{z},ymm2,3
    vreduceps zmm1{k1}{z},zmm2,3
    vreducesd xmm1{k1}{z},xmm2,xmm3,3
    vreducess xmm1{k1}{z},xmm2,xmm3,3
    vreducepd xmm1,[rax],3
    vreducepd ymm1,[rax],3
    vreducepd zmm1,[rax],3
    vreduceps xmm1,[rax],3
    vreduceps ymm1,[rax],3
    vreduceps zmm1,[rax],3
    vreducesd xmm1,xmm2,[rax],3
    vreducess xmm1,xmm2,[rax],3
    vreducepd xmm1,qword ptr [rax],3
    vreducepd ymm1,qword ptr [rax],3
    vreducepd zmm1,qword ptr [rax],3
    vreduceps xmm1,dword ptr [rax],3
    vreduceps ymm1,dword ptr [rax],3
    vreduceps zmm1,dword ptr [rax],3
    vreducesd xmm1,xmm2,qword ptr [rax],3
    vreducess xmm1,xmm2,dword ptr [rax],3

    vrndscalepd xmm1{k1}{z},xmm2,7
    vrndscalepd ymm1{k1}{z},ymm2,7
    vrndscalepd zmm1{k1}{z},zmm2,7
    vrndscaleps xmm1{k1}{z},xmm2,7
    vrndscaleps ymm1{k1}{z},ymm2,7
    vrndscaleps zmm1{k1}{z},zmm2,7
    vrndscalesd xmm1{k1}{z},xmm2,xmm3,7
    vrndscaless xmm1{k1}{z},xmm2,xmm3,3
    vrndscalepd xmm1,[rax],7
    vrndscalepd ymm1,[rax],7
    vrndscalepd zmm1,[rax],7
    vrndscaleps xmm1,[rax],7
    vrndscaleps ymm1,[rax],7
    vrndscaleps zmm1,[rax],7
    vrndscalesd xmm1,xmm2,[rax],7
    vrndscaless xmm1,xmm2,[rax],3
    vrndscalepd xmm1,qword ptr [rax],7
    vrndscalepd ymm1,qword ptr [rax],7
    vrndscalepd zmm1,qword ptr [rax],7
    vrndscaleps xmm1,dword ptr [rax],7
    vrndscaleps ymm1,dword ptr [rax],7
    vrndscaleps zmm1,dword ptr [rax],7
    vrndscalesd xmm1,xmm2,qword ptr [rax],7
    vrndscaless xmm1,xmm2,dword ptr [rax],3

    vpmovb2m k1,xmm1
    vpmovb2m k1,ymm1
    vpmovb2m k1,zmm1
    vpmovd2m k1,xmm1
    vpmovd2m k1,ymm1
    vpmovd2m k1,zmm1
    vpmovw2m k1,xmm1
    vpmovw2m k1,ymm1
    vpmovw2m k1,zmm1
    vpmovq2m k1,xmm1
    vpmovq2m k1,ymm1
    vpmovq2m k1,zmm1

    vpmovm2b xmm1,k1
    vpmovm2b ymm1,k1
    vpmovm2b zmm1,k1
    vpmovm2d xmm1,k1
    vpmovm2d ymm1,k1
    vpmovm2d zmm1,k1
    vpmovm2q xmm1,k1
    vpmovm2q ymm1,k1
    vpmovm2q zmm1,k1
    vpmovm2w xmm1,k1
    vpmovm2w ymm1,k1
    vpmovm2w zmm1,k1

    vpmovdb xmm1{k1}{z},zmm2
    vpmovdb xmm1{k1}{z},xmm2
    vpmovdb xmm1{k1}{z},ymm2
    vpmovdw xmm1{k1}{z},ymm2
    vpmovdw xmm1{k1}{z},xmm2
    vpmovdw ymm1{k1}{z},zmm2
    vpmovqb xmm1{k1}{z},xmm2
    vpmovqb xmm1{k1}{z},ymm2
    vpmovqb xmm1{k1}{z},zmm2
    vpmovqd xmm1{k1}{z},xmm2
    vpmovqd xmm1{k1}{z},ymm2
    vpmovqd ymm1{k1}{z},zmm2
    vpmovqw xmm1{k1}{z},zmm2
    vpmovqw xmm1{k1}{z},xmm2
    vpmovqw xmm1{k1}{z},ymm2
    vpmovdb [rax],zmm2
    vpmovdb [rax],xmm2
    vpmovdb [rax],ymm2
    vpmovdw [rax],ymm2
    vpmovdw [rax],xmm2
    vpmovdw [rax],zmm2
    vpmovqb [rax],xmm2
    vpmovqb [rax],ymm2
    vpmovqb [rax],zmm2
    vpmovqd [rax],xmm2
    vpmovqd [rax],ymm2
    vpmovqd [rax],zmm2
    vpmovqw [rax],zmm2
    vpmovqw [rax],xmm2
    vpmovqw [rax],ymm2
    vpmovdb oword ptr [rax],zmm2
    vpmovdb dword ptr [rax],xmm2
    vpmovdb qword ptr [rax],ymm2
    vpmovdw oword ptr [rax],ymm2
    vpmovdw qword ptr [rax],xmm2
    vpmovdw yword ptr [rax],zmm2
    vpmovqb word ptr [rax],xmm2
    vpmovqb dword ptr [rax],ymm2
    vpmovqb qword ptr [rax],zmm2
    vpmovqd oword ptr [rax],ymm2
    vpmovqd yword ptr [rax],zmm2
    vpmovqw oword ptr [rax],zmm2
    vpmovqw dword ptr [rax],xmm2
    vpmovqw qword ptr [rax],ymm2

    vpmovwb xmm1{k1}{z},ymm2
    vpmovwb xmm1{k1}{z},xmm2
    vpmovwb ymm1{k1}{z},zmm2
    vpmovwb [rax],ymm2
    vpmovwb [rax],xmm2
    vpmovwb [rax],zmm2
    vpmovwb oword ptr [rax],ymm2
    vpmovwb qword ptr [rax],xmm2
    vpmovwb yword ptr [rax],zmm2

    vpmovsdb xmm30{k7},zmm29
    vpmovsdb xmm30{k7}{z},zmm29
    vpmovsdb oword ptr [rcx],zmm30
    vpmovsdb oword ptr [rcx]{k7},zmm30
    vpmovsdb oword ptr [rax+r14*8+0x123],zmm30
    vpmovsdb oword ptr [rdx+0x7f0],zmm30
    vpmovsdb oword ptr [rdx+0x800],zmm30
    vpmovsdb oword ptr [rdx-0x800],zmm30
    vpmovsdb oword ptr [rdx-0x810],zmm30

    vpmovsdw ymm30{k7},zmm29
    vpmovsdw ymm30{k7}{z},zmm29
    vpmovsdw yword ptr [rcx],zmm30
    vpmovsdw yword ptr [rcx]{k7},zmm30
    vpmovsdw yword ptr [rax+r14*8+0x123],zmm30
    vpmovsdw yword ptr [rdx+0xfe0],zmm30
    vpmovsdw yword ptr [rdx+0x1000],zmm30
    vpmovsdw yword ptr [rdx-0x1000],zmm30
    vpmovsdw yword ptr [rdx-0x1020],zmm30

    vpmovsqb xmm30{k7},zmm29
    vpmovsqb xmm30{k7}{z},zmm29
    vpmovsqb qword ptr [rcx],zmm30
    vpmovsqb qword ptr [rcx]{k7},zmm30
    vpmovsqb qword ptr [rax+r14*8+0x123],zmm30
    vpmovsqb qword ptr [rdx+0x3f8],zmm30
    vpmovsqb qword ptr [rdx+0x400],zmm30
    vpmovsqb qword ptr [rdx-0x400],zmm30
    vpmovsqb qword ptr [rdx-0x408],zmm30

    vpmovsqd ymm30{k7},zmm29
    vpmovsqd ymm30{k7}{z},zmm29
    vpmovsqd yword ptr [rcx],zmm30
    vpmovsqd yword ptr [rcx]{k7},zmm30
    vpmovsqd yword ptr [rax+r14*8+0x123],zmm30
    vpmovsqd yword ptr [rdx+0xfe0],zmm30
    vpmovsqd yword ptr [rdx+0x1000],zmm30
    vpmovsqd yword ptr [rdx-0x1000],zmm30
    vpmovsqd yword ptr [rdx-0x1020],zmm30

    vpmovsqw xmm30{k7},zmm29
    vpmovsqw xmm30{k7}{z},zmm29
    vpmovsqw oword ptr [rcx],zmm30
    vpmovsqw oword ptr [rcx]{k7},zmm30
    vpmovsqw oword ptr [rax+r14*8+0x123],zmm30
    vpmovsqw oword ptr [rdx+0x7f0],zmm30
    vpmovsqw oword ptr [rdx+0x800],zmm30
    vpmovsqw oword ptr [rdx-0x800],zmm30
    vpmovsqw oword ptr [rdx-0x810],zmm30

    vpmovswb xmm1{k1}{z},ymm2
    vpmovswb xmm1{k1}{z},xmm2
    vpmovswb ymm1{k1}{z},zmm2
    vpmovswb [rax],ymm2
    vpmovswb [rax],xmm2
    vpmovswb [rax],zmm2
    vpmovswb oword ptr [rax],ymm2
    vpmovswb qword ptr [rax],xmm2
    vpmovswb yword ptr [rax],zmm2

    vpmovusdb xmm30{k7},zmm29
    vpmovusdb xmm30{k7}{z},zmm29
    vpmovusdb oword ptr [rcx],zmm30
    vpmovusdb oword ptr [rcx]{k7},zmm30
    vpmovusdb oword ptr [rax+r14*8+0x123],zmm30
    vpmovusdb oword ptr [rdx+0x7f0],zmm30
    vpmovusdb oword ptr [rdx+0x800],zmm30
    vpmovusdb oword ptr [rdx-0x800],zmm30
    vpmovusdb oword ptr [rdx-0x810],zmm30

    vpmovusdw ymm30{k7},zmm29
    vpmovusdw ymm30{k7}{z},zmm29
    vpmovusdw yword ptr [rcx],zmm30
    vpmovusdw yword ptr [rcx]{k7},zmm30
    vpmovusdw yword ptr [rax+r14*8+0x123],zmm30
    vpmovusdw yword ptr [rdx+0xfe0],zmm30
    vpmovusdw yword ptr [rdx+0x1000],zmm30
    vpmovusdw yword ptr [rdx-0x1000],zmm30
    vpmovusdw yword ptr [rdx-0x1020],zmm30

    vpmovusqb xmm30{k7},zmm29
    vpmovusqb xmm30{k7}{z},zmm29
    vpmovusqb qword ptr [rcx],zmm30
    vpmovusqb qword ptr [rcx]{k7},zmm30
    vpmovusqb qword ptr [rax+r14*8+0x123],zmm30
    vpmovusqb qword ptr [rdx+0x3f8],zmm30
    vpmovusqb qword ptr [rdx+0x400],zmm30
    vpmovusqb qword ptr [rdx-0x400],zmm30
    vpmovusqb qword ptr [rdx-0x408],zmm30

    vpmovusqd ymm30{k7},zmm29
    vpmovusqd ymm30{k7}{z},zmm29
    vpmovusqd yword ptr [rcx],zmm30
    vpmovusqd yword ptr [rcx]{k7},zmm30
    vpmovusqd yword ptr [rax+r14*8+0x123],zmm30
    vpmovusqd yword ptr [rdx+0xfe0],zmm30
    vpmovusqd yword ptr [rdx+0x1000],zmm30
    vpmovusqd yword ptr [rdx-0x1000],zmm30
    vpmovusqd yword ptr [rdx-0x1020],zmm30

    vpmovusqw xmm30{k7},zmm29
    vpmovusqw xmm30{k7}{z},zmm29
    vpmovusqw oword ptr [rcx],zmm30
    vpmovusqw oword ptr [rcx]{k7},zmm30
    vpmovusqw oword ptr [rax+r14*8+0x123],zmm30
    vpmovusqw oword ptr [rdx+0x7f0],zmm30
    vpmovusqw oword ptr [rdx+0x800],zmm30
    vpmovusqw oword ptr [rdx-0x800],zmm30
    vpmovusqw oword ptr [rdx-0x810],zmm30

    vpmovuswb xmm1{k1}{z},ymm2
    vpmovuswb xmm1{k1}{z},xmm2
    vpmovuswb ymm1{k1}{z},zmm2
    vpmovuswb [rax],ymm2
    vpmovuswb [rax],xmm2
    vpmovuswb [rax],zmm2
    vpmovuswb oword ptr [rax],ymm2
    vpmovuswb qword ptr [rax],xmm2
    vpmovuswb yword ptr [rax],zmm2

    end
