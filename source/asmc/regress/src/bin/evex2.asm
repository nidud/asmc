;
; v2.26 - AVX2
;
    .x64
    .model flat
    .code

    vpmaskmovd xmm6,xmm4,OWORD PTR [rcx]
    vpmaskmovd OWORD PTR [rcx],xmm6,xmm4
    vpmaskmovq xmm6,xmm4,OWORD PTR [rcx]
    vpmaskmovq OWORD PTR [rcx],xmm6,xmm4

    vpsrlvq xmm2,xmm6,xmm4
    vpsrlvq xmm2,xmm6,OWORD PTR [rcx]

    vpmaskmovd ymm6,ymm4,YMMWORD PTR [rcx]
    vpmaskmovd YMMWORD PTR [rcx],ymm6,ymm4
    vpmaskmovq ymm6,ymm4,YMMWORD PTR [rcx]
    vpmaskmovq YMMWORD PTR [rcx],ymm6,ymm4

    vpermpd ymm2,ymm6,0x7
    vpermpd ymm6,YMMWORD PTR [rcx],0x7
    vpermq  ymm2,ymm6,0x7
    vpermq  ymm6,YMMWORD PTR [rcx],0x7
    vpermd  ymm2,ymm6,ymm4
    vpermd  ymm2,ymm6,YMMWORD PTR [rcx]
    vpermps ymm2,ymm6,ymm4
    vpermps ymm2,ymm6,YMMWORD PTR [rcx]
    vpsllvd ymm2,ymm6,ymm4
    vpsllvd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsllvq ymm2,ymm6,ymm4
    vpsllvq ymm2,ymm6,YMMWORD PTR [rcx]
    vpsravd ymm2,ymm6,ymm4
    vpsravd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsrlvd ymm2,ymm6,ymm4
    vpsrlvd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsrlvq ymm2,ymm6,ymm4
    vpsrlvq ymm2,ymm6,YMMWORD PTR [rcx]

    vpermpd ymm20,ymm6,0x7
    vpermpd ymm20,YMMWORD PTR [rcx],0x7
    vpermq  ymm20,ymm6,0x7
    vpermq  ymm20,YMMWORD PTR [rcx],0x7
    vpermd  ymm20,ymm6,ymm4
    vpermd  ymm20,ymm6,YMMWORD PTR [rcx]
    vpermps ymm20,ymm6,ymm4
    vpermps ymm20,ymm6,YMMWORD PTR [rcx]
    vpsllvd ymm20,ymm6,ymm4
    vpsllvd ymm20,ymm6,YMMWORD PTR [rcx]
    vpsllvq ymm20,ymm6,ymm4
    vpsllvq ymm20,ymm6,YMMWORD PTR [rcx]
    vpsravd ymm20,ymm6,ymm4
    vpsravd ymm20,ymm6,YMMWORD PTR [rcx]
    vpsrlvd ymm20,ymm6,ymm4
    vpsrlvd ymm20,ymm6,YMMWORD PTR [rcx]
    vpsrlvq ymm20,ymm6,ymm4
    vpsrlvq ymm20,ymm6,YMMWORD PTR [rcx]

    {evex} vpsrlvq xmm2,xmm6,xmm4
    {evex} vpsrlvq xmm2,xmm6,OWORD PTR [rcx]
    {evex} vpermpd ymm2,ymm6,0x7
    {evex} vpermpd ymm6,YMMWORD PTR [rcx],0x7
    {evex} vpermq  ymm2,ymm6,0x7
    {evex} vpermq  ymm6,YMMWORD PTR [rcx],0x7
    {evex} vpermd  ymm2,ymm6,ymm4
    {evex} vpermd  ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpermps ymm2,ymm6,ymm4
    {evex} vpermps ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsllvd ymm2,ymm6,ymm4
    {evex} vpsllvd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsllvq ymm2,ymm6,ymm4
    {evex} vpsllvq ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsravd ymm2,ymm6,ymm4
    {evex} vpsravd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsrlvd ymm2,ymm6,ymm4
    {evex} vpsrlvd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsrlvq ymm2,ymm6,ymm4
    {evex} vpsrlvq ymm2,ymm6,YMMWORD PTR [rcx]

    end
