
; v2.31.15 -- INVOKE VECTORCALL YWORD, ZWORD

    .code

    y6 proto vectorcall :yword, :yword, :yword, :yword, :yword, :yword
    z6 proto vectorcall :zword, :zword, :zword, :zword, :zword, :zword

main proc
    y6(ymm0,ymm1,ymm2,ymm3,ymm4,ymm5)
    z6(zmm0,zmm1,zmm2,zmm3,zmm4,zmm5)
    ret
main endp

    end

