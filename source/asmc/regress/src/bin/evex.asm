
    .x64
    .model flat
    .code

    vmovd xmm20,eax
    vmovd xmm20,dword ptr [rax]
    vmovd eax,xmm20
    vmovd dword ptr [rax],xmm20
    vmovq xmm20,qword ptr [rax]
    vmovq qword ptr [rax],xmm20

    vmovss xmm20, xmm1, xmm2
    vmovss xmm20, dword ptr [rax]
    vmovss dword ptr [rax], xmm20
    vmovss xmm20, dword ptr [rbx]
    vmovss dword ptr [rbx], xmm20

    vmovsd xmm20, xmm1, xmm2
    vmovsd xmm20, qword ptr [rax]
    vmovsd qword ptr [rax], xmm20
    vmovsd xmm20, qword ptr [rbx]
    vmovsd qword ptr [rbx], xmm20

    vmovntdq  oword ptr [rax], xmm20
    vmovntdqa xmm20, oword ptr [rax]
    vmovntpd  oword ptr [rax], xmm20
    vmovntps  oword ptr [rax], xmm20

    vmovntdq  ymmword ptr [rax], ymm20
    vmovntdqa ymm20, ymmword ptr [rax]
    vmovntpd  ymmword ptr [rax], ymm20
    vmovntps  ymmword ptr [rax], ymm20

    vbroadcastss xmm20, dword ptr [rax]
    vbroadcastss ymm20, dword ptr [rax]
    vbroadcastsd ymm20, qword ptr [rax]

    vpermilpd xmm20, xmm1, xmm2
    vpermilpd xmm20, xmm1, oword ptr [rax]
    vpermilpd xmm20, xmm1, 1
    vpermilpd ymm20, ymm1, ymm2
    vpermilpd ymm20, ymm1, ymmword ptr [rax]
    vpermilpd ymm20, ymm1, 1

    vpermilps xmm20, xmm1, xmm2
    vpermilps xmm20, xmm1, oword ptr [rax]
    vpermilps xmm20, xmm1, 1
    vpermilps ymm20, ymm1, ymm2
    vpermilps ymm20, ymm1, ymmword ptr [rax]
    vpermilps ymm20, ymm1, 1

    vcomisd xmm17,xmm16
    vcomisd xmm16,xmm0
    vcomisd xmm16,[rax]
    vcomisd xmm0,xmm31
    vcomisd xmm0,xmm16
    vcomisd xmm31,xmm1
    vcomisd xmm16,xmm0

    vaddpd xmm16,xmm1,xmm2
    vaddpd xmm16,xmm31,xmm2
    vxorpd xmm17,xmm16,xmm16
    vxorpd xmm17,xmm16,[rax]

    vaddps xmm16,xmm1,xmm2
    vaddps xmm16,xmm1,[rax]
    vaddps ymm16,ymm1,ymm2
    vaddps ymm16,ymm1,[rax]
    vaddsd xmm16,xmm1,xmm2
    vaddsd xmm16,xmm1,[rax]
    vaddss xmm16,xmm1,xmm2
    vaddss xmm16,xmm1,[rax]

    vdivpd xmm16,xmm1,xmm2
    vdivpd xmm16,xmm1,[rax]
    vdivpd ymm16,ymm1,ymm2
    vdivpd ymm16,ymm1,[rax]

    vdivps xmm16,xmm1,xmm2
    vdivps xmm16,xmm1,[rax]
    vdivps ymm16,ymm1,ymm2
    vdivps ymm16,ymm1,[rax]

    vdivsd xmm20,xmm1,xmm2
    vdivsd xmm20,xmm1,[rax]
    vdivss xmm20,xmm1,xmm2
    vdivss xmm20,xmm1,[rax]

    vandpd xmm20,xmm1,xmm2
    vandpd ymm20,ymm1,ymm2
    vandps xmm20,xmm1,xmm2
    vandps ymm20,ymm1,ymm2

    vandnpd xmm20,xmm1,xmm2
    vandnpd ymm20,ymm1,ymm2
    vandnps xmm20,xmm1,xmm2
    vandnps ymm20,ymm1,ymm2

    vpsrlw xmm20,xmm1,xmm2
    vpsrlw xmm20,xmm1,[rax]
    vpsrld xmm20,xmm1,xmm2
    vpsrld xmm20,xmm1,[rax]
    vpsrlq xmm20,xmm1,xmm2
    vpsrlq xmm20,xmm1,[rax]
    vpsraw xmm20,xmm1,xmm2
    vpsraw xmm20,xmm1,[rax]
    vpsrad xmm20,xmm1,xmm2
    vpsrad xmm20,xmm1,[rax]
    vpsllw xmm20,xmm1,xmm2
    vpsllw xmm20,xmm1,[rax]
    vpslld xmm20,xmm1,xmm2
    vpslld xmm20,xmm1,[rax]
    vpsllq xmm20,xmm1,xmm2
    vpsllq xmm20,xmm1,[rax]

    vpslldq xmm20, xmm1, 1
    vpsrldq xmm20, xmm1, 2
    vpsrlw  xmm20, xmm1, 3
    vpsrld  xmm20, xmm1, 4
    vpsrlq  xmm20, xmm1, 5
    vpsraw  xmm20, xmm1, 6
    vpsrad  xmm20, xmm1, 7
    vpsllw  xmm20, xmm1, 8
    vpslld  xmm20, xmm1, 9
    vpsllq  xmm20, xmm1, 10

    vpsrlw  xmm20, xmm1, xmm2
    vpsrlw  xmm20, xmm1, [rax]
    vpsrld  xmm20, xmm1, xmm2
    vpsrld  xmm20, xmm1, [rax]
    vpsrlq  xmm20, xmm1, xmm2
    vpsrlq  xmm20, xmm1, [rax]
    vpsraw  xmm20, xmm1, xmm2
    vpsraw  xmm20, xmm1, [rax]
    vpsrad  xmm20, xmm1, xmm2
    vpsrad  xmm20, xmm1, [rax]
    vpsllw  xmm20, xmm1, xmm2
    vpsllw  xmm20, xmm1, [rax]
    vpslld  xmm20, xmm1, xmm2
    vpslld  xmm20, xmm1, [rax]
    vpsllq  xmm20, xmm1, xmm2
    vpsllq  xmm20, xmm1, [rax]

    vpabsb xmm20, xmm1
    vpabsb xmm20, [rax]
    vpabsw xmm20, xmm1
    vpabsw xmm20, [rax]
    vpabsd xmm20, xmm1
    vpabsd xmm20, [rax]

    vpmovzxbw xmm20, xmm1
    vpmovzxbd xmm20, xmm1
    vpmovzxbq xmm20, xmm1
    vpmovzxwd xmm20, xmm1
    vpmovzxwq xmm20, xmm1
    vpmovzxdq xmm20, xmm1
    vpmuldq   xmm20, xmm1, xmm2
    vpmulld   xmm20, xmm0, xmm1

    vpmovzxbw xmm20, qword ptr [rax]
    vpmovzxbd xmm20, dword ptr [rax]
    vpmovzxbq xmm20, word  ptr [rax]
    vpmovzxwd xmm20, qword ptr [rax]
    vpmovzxwq xmm20, dword ptr [rax]
    vpmovzxdq xmm20, qword ptr [rax]
    vpmuldq   xmm20, xmm1, oword ptr [rax]
    vpmulld   xmm20, xmm1, oword ptr [rax]

    vcomisd xmm20, xmm1
    vcomisd xmm20, [rax]
    vcomiss xmm20, xmm1
    vcomiss xmm20, [rax]
    vucomisd xmm20, xmm1
    vucomisd xmm20, [rax]
    vucomiss xmm20, xmm1
    vucomiss xmm20, [rax]

    vpmovsxbw xmm20, xmm1
    vpmovsxbw xmm20, [rax]
    vpmovsxbd xmm20, xmm1
    vpmovsxbd xmm20, [rax]
    vpmovsxbq xmm20, xmm1
    vpmovsxbq xmm20, [rax]
    vpmovsxwd xmm20, xmm1
    vpmovsxwd xmm20, [rax]
    vpmovsxwq xmm20, xmm1
    vpmovsxwq xmm20, [rax]
    vpmovsxdq xmm20, xmm1
    vpmovsxdq xmm20, [rax]

    vextractps eax, xmm21, 1
    vextractps [rax], xmm21, 1
    vinsertps xmm20, xmm1, xmm3, 0
    vinsertps xmm20, xmm1, [rax], 1

    vcvtdq2pd xmm20, xmm1
    vcvtdq2pd xmm20, [rax]
    vcvtdq2pd ymm20, xmm1
    vcvtdq2pd ymm20, [rax]

    vcvtdq2ps xmm20, xmm1
    vcvtdq2ps xmm20, [rax]
    vcvtdq2ps ymm20, ymm1
    vcvtdq2ps ymm20, [rax]

    vcvtpd2dq xmm20, xmm1
    vcvtpd2dq xmm20, xmmword ptr [rax]
    vcvtpd2dq xmm20, ymm1
    vcvtpd2dq xmm20, ymmword ptr [rax]

    vcvttpd2dq xmm20, xmm1
    vcvttpd2dq xmm20, xmmword ptr [rax]
    vcvttpd2dq xmm20, ymm1
    vcvttpd2dq xmm20, ymmword ptr [rax]

    vcvtpd2ps xmm20, xmm1
    vcvtpd2ps xmm20, xmmword ptr [rax]
    vcvtpd2ps xmm20, ymm1
    vcvtpd2ps xmm20, ymmword ptr [rax]

    vcvtps2dq xmm20, xmm1
    vcvtps2dq xmm20, xmmword ptr [rax]
    vcvtps2dq ymm20, ymm1
    vcvtps2dq ymm20, ymmword ptr [rax]

    vcvttps2dq xmm20, xmm1
    vcvttps2dq xmm20, xmmword ptr [rax]
    vcvttps2dq ymm20, ymm1
    vcvttps2dq ymm20, ymmword ptr [rax]

    vcvtps2pd xmm20, xmm1
    vcvtps2pd ymm20, xmm1

    vcvtsd2si eax, xmm21
    vcvtsd2si eax, [rax]

    vcvttsd2si eax, xmm21
    vcvttsd2si eax, [rax]

    vcvtsd2ss xmm20, xmm1, xmm2
    vcvtsd2ss xmm20, xmm1, [rax]

    vcvtsi2sd xmm20, xmm1, eax
    vcvtsi2sd xmm20, xmm1, dword ptr [rax]

    vcvtsi2ss xmm20, xmm1, eax
    vcvtsi2ss xmm20, xmm1, dword ptr [rax]

    vcvtss2sd xmm20, xmm1, xmm2
    vcvtss2sd xmm20, xmm1, dword ptr [rax]

    vcvtss2si eax, xmm21
    vcvtss2si eax, [rax]

    vcvttss2si eax, xmm21
    vcvttss2si eax, [rax]

    vmovapd xmm20, xmm1
    vmovapd xmm20, oword ptr [rax]
    vmovapd oword ptr [rax], xmm21
    vmovapd ymm20, ymm1
    vmovapd ymm20, ymmword ptr [rax]
    vmovapd ymmword ptr [rax], ymm21

    vmovaps xmm20, xmm1
    vmovaps xmm20, oword ptr [rax]
    vmovaps oword ptr [rax], xmm21
    vmovaps ymm20, ymm1
    vmovaps ymm20, ymmword ptr [rax]
    vmovaps ymmword ptr [rax], ymm21

    vmovupd xmm20, xmm1
    vmovupd xmm20, oword ptr [rax]
    vmovupd oword ptr [rax], xmm21
    vmovupd ymm20, ymm1
    vmovupd ymm20, ymmword ptr [rax]
    vmovupd ymmword ptr [rax], ymm21

    vmovups xmm20, xmm1
    vmovups xmm20, oword ptr [rax]
    vmovups oword ptr [rax], xmm21
    vmovups ymm20, ymm1
    vmovups ymm20, ymmword ptr [rax]
    vmovups ymmword ptr [rax], ymm21

    vmovhlps xmm20, xmm1, xmm2
    vmovlhps xmm20, xmm1, xmm2

    vmovhpd xmm20, xmm1, qword ptr [rax]
    vmovhpd qword ptr [rax], xmm21
    vmovhps xmm20, xmm1, qword ptr [rax]
    vmovhps qword ptr [rax], xmm21

    vmovlpd xmm20, xmm1, qword ptr [rax]
    vmovlpd qword ptr [rax], xmm21
    vmovlps xmm20, xmm1, qword ptr [rax]
    vmovlps qword ptr [rax], xmm21

    vpextrb eax, xmm21, 1
    vpextrb byte ptr [rax], xmm21, 1
    vpextrw eax, xmm21, 2
    vpextrw word ptr [rax], xmm21, 2
    vpextrd eax, xmm21, 3
    vpextrd dword ptr [rax], xmm21, 3

    vpextrq rax, xmm1, 4
    vpextrq qword ptr [rax], xmm21, 4

    vpinsrb xmm20, xmm1, eax, 1
    vpinsrb xmm20, xmm1, byte ptr [rax], 1
    vpinsrw xmm20, xmm1, eax, 2
    vpinsrw xmm20, xmm1, word ptr [rax], 2
    vpinsrd xmm20, xmm1, eax, 3
    vpinsrd xmm20, xmm1, dword ptr [rax], 3

    vpinsrq xmm20, xmm1, rax, 4
    vpinsrq xmm20, xmm1, qword ptr [rax], 4

    vmovddup xmm20, xmm1
    vmovddup xmm20, qword ptr [rax]
    vmovddup ymm20, ymm1
    vmovddup ymm20, ymmword ptr [rax]

    vpaddb   xmm20, xmm0, xmm1
    vpaddw   xmm20, xmm0, xmm1
    vpaddd   xmm20, xmm0, xmm1
    vpaddq   xmm20, xmm0, xmm1
    vpaddsb  xmm20, xmm0, xmm1
    vpaddsw  xmm20, xmm0, xmm1
    vpaddusb xmm20, xmm0, xmm1
    vpaddusw xmm20, xmm0, xmm1
    vpavgb   xmm20, xmm0, xmm1
    vpavgw   xmm20, xmm0, xmm1

    vpaddb   ymm20, ymm0, ymm1
    vpaddw   ymm20, ymm0, ymm1
    vpaddd   ymm20, ymm0, ymm1
    vpaddq   ymm20, ymm0, ymm1
    vpaddsb  ymm20, ymm0, ymm1
    vpaddsw  ymm20, ymm0, ymm1
    vpaddusb ymm20, ymm0, ymm1
    vpaddusw ymm20, ymm0, ymm1
    vpavgb   ymm20, ymm0, ymm1
    vpavgw   ymm20, ymm0, ymm1


    {evex} vmovntdq  oword ptr [rax], xmm0
    {evex} vmovntdqa xmm0, oword ptr [rax]
    {evex} vmovntpd  oword ptr [rax], xmm0
    {evex} vmovntps  oword ptr [rax], xmm0

    {evex} vmovntdq  ymmword ptr [rax], ymm0
    {evex} vmovntdqa ymm0, ymmword ptr [rax]
    {evex} vmovntpd  ymmword ptr [rax], ymm0
    {evex} vmovntps  ymmword ptr [rax], ymm0

    {evex} vbroadcastss xmm0, dword ptr [rax]
    {evex} vbroadcastss ymm0, dword ptr [rax]
    {evex} vbroadcastsd ymm0, qword ptr [rax]
    {evex} vpermilpd xmm0, xmm1, xmm2
    {evex} vpermilpd xmm0, xmm1, oword ptr [rax]
    {evex} vpermilpd xmm0, xmm1, 1
    {evex} vpermilpd ymm0, ymm1, ymm2
    {evex} vpermilpd ymm0, ymm1, ymmword ptr [rax]
    {evex} vpermilpd ymm0, ymm1, 1

    {evex} vpermilps xmm0, xmm1, xmm2
    {evex} vpermilps xmm0, xmm1, oword ptr [rax]
    {evex} vpermilps xmm0, xmm1, 1
    {evex} vpermilps ymm0, ymm1, ymm2
    {evex} vpermilps ymm0, ymm1, ymmword ptr [rax]
    {evex} vpermilps ymm0, ymm1, 1

    {evex} vcomisd xmm1,xmm0
    {evex} vcomisd xmm0,xmm0
    {evex} vcomisd xmm0,[rax]
    {evex} vcomisd xmm0,xmm1
    {evex} vcomisd xmm0,xmm0
    {evex} vcomisd xmm1,xmm1
    {evex} vcomisd xmm0,xmm0

    {evex} vaddpd xmm0,xmm1,xmm2
    {evex} vaddpd xmm0,xmm31,xmm2
    {evex} vxorpd xmm1,xmm0,xmm0
    {evex} vxorpd xmm1,xmm0,[rax]

    {evex} vaddps xmm0,xmm1,xmm2
    {evex} vaddps xmm0,xmm1,[rax]
    {evex} vaddps ymm0,ymm1,ymm2
    {evex} vaddps ymm0,ymm1,[rax]
    {evex} vaddsd xmm0,xmm1,xmm2
    {evex} vaddsd xmm0,xmm1,[rax]
    {evex} vaddss xmm0,xmm1,xmm2
    {evex} vaddss xmm0,xmm1,[rax]

    {evex} vdivpd xmm0,xmm1,xmm2
    {evex} vdivpd xmm0,xmm1,[rax]
    {evex} vdivpd ymm0,ymm1,ymm2
    {evex} vdivpd ymm0,ymm1,[rax]

    {evex} vdivps xmm0,xmm1,xmm2
    {evex} vdivps xmm0,xmm1,[rax]
    {evex} vdivps ymm0,ymm1,ymm2
    {evex} vdivps ymm0,ymm1,[rax]

    {evex} vdivsd xmm0,xmm1,xmm2
    {evex} vdivsd xmm0,xmm1,[rax]
    {evex} vdivss xmm0,xmm1,xmm2
    {evex} vdivss xmm0,xmm1,[rax]

    {evex} vandpd xmm0,xmm1,xmm2
    {evex} vandpd ymm0,ymm1,ymm2
    {evex} vandps xmm0,xmm1,xmm2
    {evex} vandps ymm0,ymm1,ymm2

    {evex} vandnpd xmm0,xmm1,xmm2
    {evex} vandnpd ymm0,ymm1,ymm2
    {evex} vandnps xmm0,xmm1,xmm2
    {evex} vandnps ymm0,ymm1,ymm2

    {evex} vpsrlw xmm0,xmm1,xmm2
    {evex} vpsrlw xmm0,xmm1,[rax]
    {evex} vpsrld xmm0,xmm1,xmm2
    {evex} vpsrld xmm0,xmm1,[rax]
    {evex} vpsrlq xmm0,xmm1,xmm2
    {evex} vpsrlq xmm0,xmm1,[rax]
    {evex} vpsraw xmm0,xmm1,xmm2
    {evex} vpsraw xmm0,xmm1,[rax]
    {evex} vpsrad xmm0,xmm1,xmm2
    {evex} vpsrad xmm0,xmm1,[rax]
    {evex} vpsllw xmm0,xmm1,xmm2
    {evex} vpsllw xmm0,xmm1,[rax]
    {evex} vpslld xmm0,xmm1,xmm2
    {evex} vpslld xmm0,xmm1,[rax]
    {evex} vpsllq xmm0,xmm1,xmm2
    {evex} vpsllq xmm0,xmm1,[rax]

    {evex} vpslldq xmm0, xmm1, 1
    {evex} vpsrldq xmm0, xmm1, 2
    {evex} vpsrlw  xmm0, xmm1, 3
    {evex} vpsrld  xmm0, xmm1, 4
    {evex} vpsrlq  xmm0, xmm1, 5
    {evex} vpsraw  xmm0, xmm1, 6
    {evex} vpsrad  xmm0, xmm1, 7
    {evex} vpsllw  xmm0, xmm1, 8
    {evex} vpslld  xmm0, xmm1, 9
    {evex} vpsllq  xmm0, xmm1, 10

    {evex} vpsrlw  xmm0, xmm1, xmm2
    {evex} vpsrlw  xmm0, xmm1, [rax]
    {evex} vpsrld  xmm0, xmm1, xmm2
    {evex} vpsrld  xmm0, xmm1, [rax]
    {evex} vpsrlq  xmm0, xmm1, xmm2
    {evex} vpsrlq  xmm0, xmm1, [rax]
    {evex} vpsraw  xmm0, xmm1, xmm2
    {evex} vpsraw  xmm0, xmm1, [rax]
    {evex} vpsrad  xmm0, xmm1, xmm2
    {evex} vpsrad  xmm0, xmm1, [rax]
    {evex} vpsllw  xmm0, xmm1, xmm2
    {evex} vpsllw  xmm0, xmm1, [rax]
    {evex} vpslld  xmm0, xmm1, xmm2
    {evex} vpslld  xmm0, xmm1, [rax]
    {evex} vpsllq  xmm0, xmm1, xmm2
    {evex} vpsllq  xmm0, xmm1, [rax]

    {evex} vpabsb xmm0, xmm1
    {evex} vpabsb xmm0, [rax]
    {evex} vpabsw xmm0, xmm1
    {evex} vpabsw xmm0, [rax]
    {evex} vpabsd xmm0, xmm1
    {evex} vpabsd xmm0, [rax]
    {evex} vcomisd xmm0, xmm1
    {evex} vcomisd xmm0, [rax]
    {evex} vcomiss xmm0, xmm1
    {evex} vcomiss xmm0, [rax]
    {evex} vucomisd xmm0, xmm1
    {evex} vucomisd xmm0, [rax]
    {evex} vucomiss xmm0, xmm1
    {evex} vucomiss xmm0, [rax]
    {evex} vpmovsxbw xmm0, xmm1
    {evex} vpmovsxbw xmm0, [rax]
    {evex} vpmovsxbd xmm0, xmm1
    {evex} vpmovsxbd xmm0, [rax]
    {evex} vpmovsxbq xmm0, xmm1
    {evex} vpmovsxbq xmm0, [rax]
    {evex} vpmovsxwd xmm0, xmm1
    {evex} vpmovsxwd xmm0, [rax]
    {evex} vpmovsxwq xmm0, xmm1
    {evex} vpmovsxwq xmm0, [rax]
    {evex} vpmovsxdq xmm0, xmm1
    {evex} vpmovsxdq xmm0, [rax]
    {evex} vextractps eax, xmm1, 1
    {evex} vextractps [rax], xmm1, 1
    {evex} vinsertps xmm0, xmm1, xmm3, 0
    {evex} vinsertps xmm0, xmm1, [rax], 1

    {evex} vcvtdq2pd xmm0, xmm1
    {evex} vcvtdq2pd xmm0, [rax]
    {evex} vcvtdq2pd ymm0, xmm1	  ;!
    {evex} vcvtdq2pd ymm0, [rax]   ;!

    {evex} vcvtdq2ps xmm0, xmm1
    {evex} vcvtdq2ps xmm0, [rax]
    {evex} vcvtdq2ps ymm0, ymm1
    {evex} vcvtdq2ps ymm0, [rax]

    {evex} vcvtpd2dq xmm0, xmm1
    {evex} vcvtpd2dq xmm0, xmmword ptr [rax]
    {evex} vcvtpd2dq xmm0, ymm1
    {evex} vcvtpd2dq xmm0, ymmword ptr [rax]   ;L bit set?

    {evex} vcvttpd2dq xmm0, xmm1
    {evex} vcvttpd2dq xmm0, xmmword ptr [rax]
    {evex} vcvttpd2dq xmm0, ymm1
    {evex} vcvttpd2dq xmm0, ymmword ptr [rax]  ;L bit set?

    {evex} vcvtpd2ps xmm0, xmm1
    {evex} vcvtpd2ps xmm0, xmmword ptr [rax]
    {evex} vcvtpd2ps xmm0, ymm1
    {evex} vcvtpd2ps xmm0, ymmword ptr [rax]   ;L bit set?

    {evex} vcvtps2dq xmm0, xmm1
    {evex} vcvtps2dq xmm0, xmmword ptr [rax]
    {evex} vcvtps2dq ymm0, ymm1
    {evex} vcvtps2dq ymm0, ymmword ptr [rax]

    {evex} vcvttps2dq xmm0, xmm1
    {evex} vcvttps2dq xmm0, xmmword ptr [rax]
    {evex} vcvttps2dq ymm0, ymm1
    {evex} vcvttps2dq ymm0, ymmword ptr [rax]

    {evex} vcvtps2pd xmm0, xmm1
    {evex} vcvtps2pd ymm0, xmm1	  ;!

    {evex} vcvtsd2si eax, xmm1
    {evex} vcvtsd2si eax, [rax]

    {evex} vcvttsd2si eax, xmm1
    {evex} vcvttsd2si eax, [rax]

    {evex} vcvtsd2ss xmm0, xmm1, xmm2
    {evex} vcvtsd2ss xmm0, xmm1, [rax]

    {evex} vcvtsi2sd xmm0, xmm1, eax
    {evex} vcvtsi2sd xmm0, xmm1, dword ptr [rax]

    {evex} vcvtsi2ss xmm0, xmm1, eax
    {evex} vcvtsi2ss xmm0, xmm1, dword ptr [rax]

    {evex} vcvtss2sd xmm0, xmm1, xmm2
    {evex} vcvtss2sd xmm0, xmm1, dword ptr [rax]

    {evex} vcvtss2si eax, xmm1
    {evex} vcvtss2si eax, [rax]

    {evex} vcvttss2si eax, xmm1
    {evex} vcvttss2si eax, [rax]

    {evex} vmovapd xmm0, xmm1
    {evex} vmovapd xmm0, oword ptr [rax]
    {evex} vmovapd oword ptr [rax], xmm1
    {evex} vmovapd ymm0, ymm1
    {evex} vmovapd ymm0, ymmword ptr [rax]
    {evex} vmovapd ymmword ptr [rax], ymm1

    {evex} vmovaps xmm0, xmm1
    {evex} vmovaps xmm0, oword ptr [rax]
    {evex} vmovaps oword ptr [rax], xmm1
    {evex} vmovaps ymm0, ymm1
    {evex} vmovaps ymm0, ymmword ptr [rax]
    {evex} vmovaps ymmword ptr [rax], ymm1

    {evex} vmovupd xmm0, xmm1
    {evex} vmovupd xmm0, oword ptr [rax]
    {evex} vmovupd oword ptr [rax], xmm1
    {evex} vmovupd ymm0, ymm1
    {evex} vmovupd ymm0, ymmword ptr [rax]
    {evex} vmovupd ymmword ptr [rax], ymm1

    {evex} vmovups xmm0, xmm1
    {evex} vmovups xmm0, oword ptr [rax]
    {evex} vmovups oword ptr [rax], xmm1
    {evex} vmovups ymm0, ymm1
    {evex} vmovups ymm0, ymmword ptr [rax]
    {evex} vmovups ymmword ptr [rax], ymm1

    {evex} vmovhlps xmm0, xmm1, xmm2
    {evex} vmovlhps xmm0, xmm1, xmm2

    {evex} vmovhpd xmm0, xmm1, qword ptr [rax]
    {evex} vmovhpd qword ptr [rax], xmm1
    {evex} vmovhps xmm0, xmm1, qword ptr [rax]
    {evex} vmovhps qword ptr [rax], xmm1

    {evex} vmovlpd xmm0, xmm1, qword ptr [rax]
    {evex} vmovlpd qword ptr [rax], xmm1
    {evex} vmovlps xmm0, xmm1, qword ptr [rax]
    {evex} vmovlps qword ptr [rax], xmm1

    {evex} vpextrb eax, xmm1, 1
    {evex} vpextrb byte ptr [rax], xmm1, 1

    {evex} vpextrw word ptr [rax], xmm1, 2
    {evex} vpextrd eax, xmm1, 3
    {evex} vpextrd dword ptr [rax], xmm1, 3

    {evex} vpextrq rax, xmm1, 4
    {evex} vpextrq qword ptr [rax], xmm1, 4

    {evex} vpinsrb xmm0, xmm1, eax, 1
    {evex} vpinsrb xmm0, xmm1, byte ptr [rax], 1
    {evex} vpinsrw xmm0, xmm1, eax, 2
    {evex} vpinsrw xmm0, xmm1, word ptr [rax], 2
    {evex} vpinsrd xmm0, xmm1, eax, 3
    {evex} vpinsrd xmm0, xmm1, dword ptr [rax], 3

    {evex} vpinsrq xmm0, xmm1, rax, 4
    {evex} vpinsrq xmm0, xmm1, qword ptr [rax], 4

    {evex} vmovddup xmm0, xmm1
    {evex} vmovddup xmm0, qword ptr [rax]
    {evex} vmovddup ymm0, ymm1
    {evex} vmovddup ymm0, ymmword ptr [rax]

    {evex} vpaddb   xmm0, xmm0, xmm1
    {evex} vpaddw   xmm0, xmm0, xmm1
    {evex} vpaddd   xmm0, xmm0, xmm1
    {evex} vpaddq   xmm0, xmm0, xmm1
    {evex} vpaddsb  xmm0, xmm0, xmm1
    {evex} vpaddsw  xmm0, xmm0, xmm1
    {evex} vpaddusb xmm0, xmm0, xmm1
    {evex} vpaddusw xmm0, xmm0, xmm1
    {evex} vpavgb   xmm0, xmm0, xmm1
    {evex} vpavgw   xmm0, xmm0, xmm1

    {evex} vpaddb   ymm0, ymm0, ymm1
    {evex} vpaddw   ymm0, ymm0, ymm1
    {evex} vpaddd   ymm0, ymm0, ymm1
    {evex} vpaddq   ymm0, ymm0, ymm1
    {evex} vpaddsb  ymm0, ymm0, ymm1
    {evex} vpaddsw  ymm0, ymm0, ymm1
    {evex} vpaddusb ymm0, ymm0, ymm1
    {evex} vpaddusw ymm0, ymm0, ymm1
    {evex} vpavgb   ymm0, ymm0, ymm1
    {evex} vpavgw   ymm0, ymm0, ymm1

    end
