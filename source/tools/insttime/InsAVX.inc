
    vbroadcasti128 reg256,mem128
    vbroadcastsd reg256,reg128
    vbroadcastss reg128,reg128
    vbroadcastss reg256,reg128
    vcvtsd2si reg32, mem64
    vcvtsd2si reg32, reg128
    vcvtsd2si reg64, mem64
    vcvtsd2si reg64, reg128
    vcvtss2si reg32, mem32
    vcvtss2si reg32, reg128
    vcvtss2si reg64, mem32
    vcvtss2si reg64, reg128
    vcvttsd2si reg32, mem64
    vcvttsd2si reg32, reg128
    vcvttsd2si reg64, mem64
    vcvttss2si reg32, mem32
    vcvttss2si reg32, reg128
    vcvttss2si reg64, mem32
    vcvttss2si reg64, reg128
    vextracti128 mem128,reg256,7
    vextracti128 reg128,reg256,7
    vinserti128 reg256,reg256,mem128,7
    vinserti128 reg256,reg256,reg128,7
    vmovd  reg32, reg128
    vmovd  mem32, reg128
    vmovd  mem64, reg128
    vmovd  reg64, reg128
    vmovd  reg128, reg32
    vmovd  reg128, mem32
    vmovd  reg128, mem64
    vmovd  reg128, reg64
    vmovntdqa reg256,mem256
    vmovq  mem64,reg128
    vmovq  reg128,mem64
    vmpsadbw reg256,reg256,reg256,7
    vmpsadbw reg256,reg256,mem256,7
    vpabsb reg256,mem256
    vpabsb reg256,reg256
    vpabsd reg256,mem256
    vpabsd reg256,reg256
    vpabsw reg256,mem256
    vpabsw reg256,reg256

    vpackssdw reg256,reg256,reg256
    vpackssdw reg256,reg256,mem256
    vpacksswb reg256,reg256,reg256
    vpacksswb reg256,reg256,mem256
    vpackusdw reg256,reg256,reg256
    vpackusdw reg256,reg256,mem256
    vpackuswb reg256,reg256,reg256
    vpackuswb reg256,reg256,mem256

    vpaddb reg256,reg256,reg256
    vpaddb reg256,reg256,mem256
    vpaddd reg256,reg256,reg256
    vpaddd reg256,reg256,mem256
    vpaddq reg256,reg256,reg256
    vpaddq reg256,reg256,mem256

    vpaddsb reg256,reg256,reg256
    vpaddsb reg256,reg256,mem256

    vpaddsw reg256,reg256,reg256
    vpaddsw reg256,reg256,mem256

    vpaddusb reg256,reg256,reg256
    vpaddusb reg256,reg256,mem256

    vpaddusw reg256,reg256,reg256
    vpaddusw reg256,reg256,mem256

    vpaddw reg256,reg256,reg256
    vpaddw reg256,reg256,mem256

    vpalignr reg256,reg256,reg256,7
    vpalignr reg256,reg256,mem256,7

    vpand reg256,reg256,reg256
    vpand reg256,reg256,mem256

    vpandn reg256,reg256,reg256
    vpandn reg256,reg256,mem256

    vpavgb reg256,reg256,reg256
    vpavgb reg256,reg256,mem256

    vpavgw reg256,reg256,reg256
    vpavgw reg256,reg256,mem256

    vpblendd reg128,reg128,mem128,7
    vpblendd reg128,reg128,reg128,7
    vpblendd reg256,reg256,reg256,7
    vpblendd reg256,reg256,mem256,7

    vpblendvb reg256,reg256,reg256,reg256
    vpblendvb reg256,reg256,mem256,reg256

    vpblendw reg256,reg256,reg256,7
    vpblendw reg256,reg256,mem256,7

    vpbroadcastb reg128,mem8
    vpbroadcastb reg128,reg128
    vpbroadcastb reg256,mem8
    vpbroadcastb reg256,reg128

    vpbroadcastd reg128,mem32
    vpbroadcastd reg128,reg128
    vpbroadcastd reg256,mem32
    vpbroadcastd reg256,reg128

    vpbroadcastq reg128,mem64
    vpbroadcastq reg128,reg128
    vpbroadcastq reg256,mem64
    vpbroadcastq reg256,reg128

    vpbroadcastw reg128,mem16
    vpbroadcastw reg128,reg128
    vpbroadcastw reg256,mem16
    vpbroadcastw reg256,reg128

    vpcmpeqb reg256,reg256,reg256
    vpcmpeqb reg256,reg256,mem256

    vpcmpeqd reg256,reg256,reg256
    vpcmpeqd reg256,reg256,mem256

    vpcmpeqq reg256,reg256,reg256
    vpcmpeqq reg256,reg256,mem256

    vpcmpeqw reg256,reg256,reg256
    vpcmpeqw reg256,reg256,mem256

    vpcmpgtb reg256,reg256,reg256
    vpcmpgtb reg256,reg256,mem256

    vpcmpgtd reg256,reg256,reg256
    vpcmpgtd reg256,reg256,mem256

    vpcmpgtq reg256,reg256,reg256
    vpcmpgtq reg256,reg256,mem256

    vpcmpgtw reg256,reg256,reg256
    vpcmpgtw reg256,reg256,mem256

    vperm2i128 reg256,reg256,reg256,7
    vperm2i128 reg256,reg256,mem256,7

    vpermd reg256,reg256,reg256
    vpermd reg256,reg256,mem256

    vpermpd reg256,reg256,7
    vpermpd reg256,mem256,7

    vpermps reg256,reg256,reg256
    vpermps reg256,reg256,mem256

    vpermq reg256,reg256,7
    vpermq reg256,mem256,7

    vpextrb reg32,reg128,1
    vpextrb mem8,reg128,1
    vpextrd reg32,reg128,3
    vpextrd mem32,reg128,3
    vpextrq mem64,reg128,4
    vpextrq reg64,reg128,4
    vpextrw reg32,reg128,2
    vpextrw mem16,reg128,2

    vphaddd reg256,reg256,reg256
    vphaddd reg256,reg256,mem256

    vphaddsw reg256,reg256,reg256
    vphaddsw reg256,reg256,mem256
    vphaddw reg256,reg256,reg256
    vphaddw reg256,reg256,mem256
    vphsubd reg256,reg256,reg256
    vphsubd reg256,reg256,mem256
    vphsubsw reg256,reg256,reg256
    vphsubsw reg256,reg256,mem256
    vphsubw reg256,reg256,reg256
    vphsubw reg256,reg256,mem256
    vpinsrb reg128,reg128,reg32,1
    vpinsrb reg128,reg128,mem8,1
    vpinsrd reg128,reg128,reg32,3
    vpinsrd reg128,reg128,mem32,3
    vpinsrq reg128,reg128,mem64,4
    vpinsrq reg128,reg128,reg64,4
    vpinsrw reg128,reg128,reg32,2
    vpinsrw reg128,reg128,mem16,2
    vpmaddubsw reg256,reg256,reg256
    vpmaddubsw reg256,reg256,mem256
    vpmaddwd reg256,reg256,reg256
    vpmaddwd reg256,reg256,mem256
    vpmaskmovd mem128,reg128,reg128
    vpmaskmovd reg128,reg128,mem128
    vpmaskmovd reg256,reg256,mem256
    vpmaskmovd mem256,reg256,reg256

    vpmaskmovq mem128,reg128,reg128
    vpmaskmovq reg128,reg128,mem128
    vpmaskmovq reg256,reg256,mem256
    vpmaskmovq mem256,reg256,reg256
    vpmaxsb reg256,reg256,reg256
    vpmaxsb reg256,reg256,mem256
    vpmaxsd reg256,reg256,reg256
    vpmaxsd reg256,reg256,mem256
    vpmaxsw reg256,reg256,reg256
    vpmaxsw reg256,reg256,mem256
    vpmaxub reg256,reg256,reg256
    vpmaxub reg256,reg256,mem256
    vpmaxud reg256,reg256,reg256
    vpmaxud reg256,reg256,mem256
    vpmaxuw reg256,reg256,reg256
    vpmaxuw reg256,reg256,mem256
    vpminsb reg256,reg256,reg256
    vpminsb reg256,reg256,mem256
    vpminsd reg256,reg256,reg256
    vpminsd reg256,reg256,mem256
    vpminsw reg256,reg256,reg256
    vpminsw reg256,reg256,mem256
    vpminub reg256,reg256,reg256
    vpminub reg256,reg256,mem256
    vpminud reg256,reg256,reg256
    vpminud reg256,reg256,mem256
    vpminuw reg256,reg256,reg256
    vpminuw reg256,reg256,mem256
    vpmovmskb reg32,reg128
    vpmovmskb reg32,reg256
    vpmovmskb reg64,reg128
    vpmovsxbd reg256,mem64
    vpmovsxbd reg256,reg128
    vpmovsxbq reg256,mem32
    vpmovsxbq reg256,reg128
    vpmovsxbw reg256,mem128
    vpmovsxbw reg256,reg128
    vpmovsxdq reg256,mem128
    vpmovsxdq reg256,reg128
    vpmovsxwd reg256,mem128
    vpmovsxwd reg256,reg128
    vpmovsxwq reg256,mem64
    vpmovsxwq reg256,reg128
    vpmovzxbd reg256,mem64
    vpmovzxbd reg256,reg128
    vpmovzxbq reg256,mem32
    vpmovzxbq reg256,reg128
    vpmovzxbw reg256,mem128
    vpmovzxbw reg256,reg128
    vpmovzxdq reg256,mem128
    vpmovzxdq reg256,reg128
    vpmovzxwd reg256,mem128
    vpmovzxwd reg256,reg128
    vpmovzxwq reg256,mem64
    vpmovzxwq reg256,reg128
    vpmuldq reg256,reg256,reg256
    vpmuldq reg256,reg256,mem256
    vpmulhrsw reg256,reg256,reg256
    vpmulhrsw reg256,reg256,mem256
    vpmulhuw reg256,reg256,reg256
    vpmulhuw reg256,reg256,mem256
    vpmulhw reg256,reg256,reg256
    vpmulhw reg256,reg256,mem256
    vpmulld reg256,reg256,reg256
    vpmulld reg256,reg256,mem256
    vpmullw reg256,reg256,reg256
    vpmullw reg256,reg256,mem256
    vpmuludq reg256,reg256,reg256
    vpmuludq reg256,reg256,mem256
    vpor reg256,reg256,reg256
    vpor reg256,reg256,mem256
    vpsadbw reg256,reg256,reg256
    vpsadbw reg256,reg256,mem256
    vpshufb reg256,reg256,reg256
    vpshufb reg256,reg256,mem256
    vpshufd reg256,reg256,7
    vpshufd reg256,mem256,7
    vpshufhw reg256,reg256,7
    vpshufhw reg256,mem256,7
    vpshuflw reg256,reg256,7
    vpshuflw reg256,mem256,7
    vpsignb reg256,reg256,reg256
    vpsignb reg256,reg256,mem256
    vpsignd reg256,reg256,reg256
    vpsignd reg256,reg256,mem256
    vpsignw reg256,reg256,reg256
    vpsignw reg256,reg256,mem256
    vpslld reg256,reg256,7
    vpslld reg256,reg256,mem128
    vpslld reg256,reg256,reg128
    vpslldq reg256,reg256,7
    vpsllq reg256,reg256,7
    vpsllq reg256,reg256,mem128
    vpsllq reg256,reg256,reg128

    vpsllvd reg128,reg128,reg128
    vpsllvd reg128,reg128,mem128
    vpsllvd reg256,reg256,reg256
    vpsllvd reg256,reg256,mem256

    vpsllvq reg128,reg128,reg128
    vpsllvq reg128,reg128,mem128
    vpsllvq reg256,reg256,reg256
    vpsllvq reg256,reg256,mem256

    vpsllw reg256,reg256,7
    vpsllw reg256,reg256,mem128
    vpsllw reg256,reg256,reg128
    vpsrad reg256,reg256,7
    vpsrad reg256,reg256,mem128
    vpsrad reg256,reg256,reg128
    vpsravd reg128,reg128,reg128
    vpsravd reg128,reg128,mem128
    vpsravd reg256,reg256,reg256
    vpsravd reg256,reg256,mem256
    vpsraw reg256,reg256,7
    vpsraw reg256,reg256,mem128
    vpsraw reg256,reg256,reg128
    vpsrld reg256,reg256,7
    vpsrld reg256,reg256,mem128
    vpsrld reg256,reg256,reg128
    vpsrldq reg256,reg256,7
    vpsrlq reg256,reg256,7
    vpsrlq reg256,reg256,mem128
    vpsrlq reg256,reg256,reg128
    vpsrlvd reg128,reg128,reg128
    vpsrlvd reg128,reg128,mem128
    vpsrlvd reg256,reg256,reg256
    vpsrlvd reg256,reg256,mem256

    vpsrlvq reg128,reg128,mem128
    vpsrlvq reg128,reg128,reg128
    vpsrlvq reg256,reg256,reg256
    vpsrlvq reg256,reg256,mem256

    vpsrlw reg256,reg256,7
    vpsrlw reg256,reg256,mem128
    vpsrlw reg256,reg256,reg128
    vpsubb reg256,reg256,reg256
    vpsubb reg256,reg256,mem256
    vpsubd reg256,reg256,reg256
    vpsubd reg256,reg256,mem256
    vpsubq reg256,reg256,reg256
    vpsubq reg256,reg256,mem256
    vpsubsb reg256,reg256,reg256
    vpsubsb reg256,reg256,mem256
    vpsubsw reg256,reg256,reg256
    vpsubsw reg256,reg256,mem256
    vpsubusb reg256,reg256,reg256
    vpsubusb reg256,reg256,mem256
    vpsubusw reg256,reg256,reg256
    vpsubusw reg256,reg256,mem256
    vpsubw reg256,reg256,reg256
    vpsubw reg256,reg256,mem256
    vpunpckhbw reg256,reg256,reg256
    vpunpckhbw reg256,reg256,mem256
    vpunpckhdq reg256,reg256,reg256
    vpunpckhdq reg256,reg256,mem256
    vpunpckhqdq reg256,reg256,reg256
    vpunpckhqdq reg256,reg256,mem256
    vpunpckhwd reg256,reg256,reg256
    vpunpckhwd reg256,reg256,mem256
    vpunpcklbw reg256,reg256,reg256
    vpunpcklbw reg256,reg256,mem256
    vpunpckldq reg256,reg256,reg256
    vpunpckldq reg256,reg256,mem256
    vpunpcklqdq reg256,reg256,reg256
    vpunpcklqdq reg256,reg256,mem256
    vpunpcklwd reg256,reg256,reg256
    vpunpcklwd reg256,reg256,mem256
    vpxor reg256,reg256,reg256
    vpxor reg256,reg256,mem256
