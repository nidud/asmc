;
; v2.31.15 - ymm and zmm param
;

    .code

    option win64:auto

foo proto :yword,:yword,:yword,:yword,:yword,:yword,:yword,:yword
bar proto :zword,:zword,:zword,:zword,:zword,:zword,:zword,:zword

main proc
    foo(ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7)
    bar(zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6,zmm7)
    ret
main endp

    end
