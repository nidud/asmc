;
; v2.34.58 avxencoding
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    {evex} vpdpbusd xmm1, xmm2, xmm3
    {evex} vpmaddwd xmm1, xmm2, xmm3

    option avxencoding:no_EVEX
    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    option avxencoding:prefer_VEX
    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    option avxencoding:prefer_VEX3
    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    option avxencoding:prefer_EVEX
    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    option avxencoding:prefer_first
    vpdpbusd xmm1, xmm2, xmm3
    vpmaddwd xmm1, xmm2, xmm3

    end
