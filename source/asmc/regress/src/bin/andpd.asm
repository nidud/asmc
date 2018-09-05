;
; v2.28.05 -- HSE
;
    .x64
    .model flat

    .data
    m64 label qword

    .code

    andpd   xmm0,m64
    andnpd  xmm0,m64
    xorpd   xmm0,m64
    orpd    xmm0,m64

    end

