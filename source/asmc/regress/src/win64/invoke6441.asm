
; v2.31.14 - 32/64 byte type as argument

    option win64:3

    y1 proto :yword
    y2 proto :yword, :yword
    y3 proto :yword, :yword, :yword
    y4 proto :yword, :yword, :yword, :yword

    z1 proto :zword
    z2 proto :zword, :zword
    z3 proto :zword, :zword, :zword
    z4 proto :zword, :zword, :zword, :zword

    .code

bar proc

  local z:zword
  local y:zword

    y1(ymm0)
    y2(ymm0,ymm1)
    y3(ymm0,ymm1,ymm2)
    y4(ymm0,ymm1,ymm2,ymm3)

    z1(zmm0)
    z2(zmm0,zmm1)
    z3(zmm0,zmm1,zmm2)
    z4(zmm0,zmm1,zmm2,zmm3)

    y2(ymm0,y1(ymm0))
    z2(zmm0,z1(zmm0))

    y4(ymm0,ymm0,ymm0,ymm0)
    z4(zmm0,zmm0,zmm0,zmm0)

    vmovaps ymm3,y1(ymm0)
    vmovaps zmm3,z1(zmm0)

    ret

bar endp

    end
