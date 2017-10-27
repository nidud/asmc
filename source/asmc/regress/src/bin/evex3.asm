;
; v2.26 - AVX512
;
    .x64
    .model flat
    .code

    vpermw  xmm1, xmm2, xmm3
    vpermw  ymm1, ymm2, ymm3
    vpermw  zmm1, zmm2, zmm3
    vpermw  zmm3, zmm2, zmm1

    vpsravw xmm1, xmm2, xmm3
    vpsravw ymm1, ymm2, ymm3
    vpsravw zmm1, zmm2, zmm3

    vpsravq xmm1, xmm2, xmm3
    vpsravq ymm1, ymm2, ymm3
    vpsravq zmm1, zmm2, zmm3

    vpsrlvw xmm1, xmm2, xmm3
    vpsrlvw ymm1, ymm2, ymm3
    vpsrlvw zmm1, zmm2, zmm3

    vpermw zmm1{k1},zmm2,zmm3
    vpermw zmm1{k1}{z},zmm2,zmm3
    vpermw zmm1{k2}{z},zmm2,zmm3
    vpermw zmm1{k3}{z},zmm2,zmm3
    vpermw zmm1{k4}{z},zmm2,zmm3
    vpermw zmm1{k5}{z},zmm2,zmm3
    vpermw zmm1{k6}{z},zmm2,zmm3
    vpermw zmm1{k7}{z},zmm2,zmm3

    vpermw xmm1,xmm2,[rax]
    vpermw xmm1{k1},xmm2,[rax]
    vpermw xmm1{k1}{z},xmm2,[rax]
    vpermw xmm1{k2}{z},xmm2,[rax]
    vpermw xmm1{k3}{z},xmm2,[rax]
    vpermw xmm1{k4}{z},xmm2,[rax]
    vpermw xmm1{k5}{z},xmm2,[rax]
    vpermw xmm1{k6}{z},xmm2,[rax]
    vpermw xmm1{k7}{z},xmm2,[rax]

    vpermw ymm1,ymm2,[rax]
    vpermw ymm1{k1},ymm2,[rax]
    vpermw ymm1{k1}{z},ymm2,[rax]
    vpermw ymm1{k2}{z},ymm2,[rax]
    vpermw ymm1{k3}{z},ymm2,[rax]
    vpermw ymm1{k4}{z},ymm2,[rax]
    vpermw ymm1{k5}{z},ymm2,[rax]
    vpermw ymm1{k6}{z},ymm2,[rax]
    vpermw ymm1{k7}{z},ymm2,[rax]

    vpermw zmm1,zmm2,[rax]
    vpermw zmm1{k1},zmm2,[rax]
    vpermw zmm1{k1}{z},zmm2,[rax]
    vpermw zmm1{k2}{z},zmm2,[rax]
    vpermw zmm1{k3}{z},zmm2,[rax]
    vpermw zmm1{k4}{z},zmm2,[rax]
    vpermw zmm1{k5}{z},zmm2,[rax]
    vpermw zmm1{k6}{z},zmm2,[rax]
    vpermw zmm1{k7}{z},zmm2,[rax]

    end
