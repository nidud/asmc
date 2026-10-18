;
; v2.40 -- vector assignment
;
.code

 option comdat:on

 define RS 4.0
 define SD 2.0
 define PS <{ RS, RS, RS, RS }>
 define PD <{ SD, SD }>

 addpd      xmm0,PD
 addps      xmm0,PS
 addsd      xmm0,SD
 addss      xmm0,RS
 divpd      xmm0,PD
 divps      xmm0,PS
 divsd      xmm0,SD
 divss      xmm0,RS
 maxpd      xmm0,PD
 maxps      xmm0,PS
 maxsd      xmm0,SD
 maxss      xmm0,RS
 minpd      xmm0,PD
 minps      xmm0,PS
 minsd      xmm0,SD
 minss      xmm0,RS
 mulpd      xmm0,PD
 mulps      xmm0,PS
 mulsd      xmm0,SD
 mulss      xmm0,RS

 sqrtpd     xmm0,PD
 sqrtps     xmm0,PS
 sqrtsd     xmm0,SD
 sqrtss     xmm0,RS

 subpd      xmm0,PD
 subps      xmm0,PS
 subsd      xmm0,SD
 subss      xmm0,RS

 cmpss      xmm0,RS,1
 cmpsd      xmm0,SD,1
 cmppd      xmm0,PD,1
 cmpps      xmm0,PS,1

for cm,<eq,lt,le,unord,neq,nlt,nle,ord>
    cmp&cm&pd xmm0,PD
    endm
for cm,<eq,lt,le,unord,neq,nlt,nle,ord>
    cmp&cm&ps xmm0,PS
    endm
for cm,<eq,lt,le,unord,neq,nlt,nle,ord>
    cmp&cm&sd xmm0,SD
    endm
for cm,<eq,lt,le,unord,neq,nlt,nle,ord>
    cmp&cm&ss xmm0,RS
    endm

 andnpd     xmm0,PD
 andnps     xmm0,PS
 andpd      xmm0,PD
 andps      xmm0,PS
 orpd       xmm0,PD
 orps       xmm0,PS
 comisd     xmm0,SD
 comiss     xmm0,RS
 xorpd      xmm0,PD
 xorps      xmm0,PS

 movapd     xmm0,PD
 movaps     xmm0,PS
 movdqa     xmm0,PD
 movdqu     xmm0,PD
 movupd     xmm0,PD
 movups     xmm0,PS
 movhpd     xmm0,SD

 movlpd     xmm0,SD
 movss      xmm0,RS

 packssdw   xmm0,PS
 packsswb   xmm0,PS
 packuswb   xmm0,PS
 paddb      xmm0,PS
 paddw      xmm0,PS
 paddd      xmm0,PS
 paddq      xmm0,PD
 paddsb     xmm0,PS
 paddsw     xmm0,PS
 paddusb    xmm0,PS
 paddusw    xmm0,PS
 pand       xmm0,PS
 pandn      xmm0,PS
 pavgb      xmm0,PS
 pavgw      xmm0,PS

 pcmpeqb    xmm0,PS
 pcmpeqw    xmm0,PS
 pcmpeqd    xmm0,PS
 pcmpgtb    xmm0,PS
 pcmpgtw    xmm0,PS
 pcmpgtd    xmm0,PS

 pmaddwd    xmm0,PS
 pmaxsw     xmm0,PS
 pmaxub     xmm0,PS
 pminsw     xmm0,PS
 pminub     xmm0,PS

 pmulhuw    xmm0,PS
 pmulhw     xmm0,PS
 pmullw     xmm0,PS
 pmuludq    xmm0,PS
 por        xmm0,PS
 psadbw     xmm0,PS

 psubb      xmm0,PS
 psubw      xmm0,PS
 psubd      xmm0,PS
 psubq      xmm0,PD
 psubsb     xmm0,PS
 psubsw     xmm0,PS
 psubusb    xmm0,PS
 psubusw    xmm0,PS
 pxor       xmm0,PS

 punpckhbw  xmm0,PS
 punpckhwd  xmm0,PS
 punpckhdq  xmm0,PS
 punpcklbw  xmm0,PS
 punpcklwd  xmm0,PS
 punpckldq  xmm0,PS

 punpckhqdq xmm0,PD
 punpcklqdq xmm0,PD

 rcpps      xmm0,PS
 rcpss      xmm0,RS
 rsqrtps    xmm0,PS
 rsqrtss    xmm0,RS
 ucomisd    xmm0,SD
 ucomiss    xmm0,RS
 unpckhpd   xmm0,PD
 unpckhps   xmm0,PS
 unpcklpd   xmm0,PD
 unpcklps   xmm0,PS

 addsubpd   xmm0,PD
 addsubps   xmm0,PS
 haddpd     xmm0,PD
 haddps     xmm0,PS
 hsubpd     xmm0,PD
 hsubps     xmm0,PS
 movddup    xmm0,SD
 movshdup   xmm0,PS
 movsldup   xmm0,PS

 pabsb      xmm0,PS
 pabsd      xmm0,PS
 pabsw      xmm0,PS

 phaddd     xmm0,PS
 phaddsw    xmm0,PS
 phaddw     xmm0,PS
 phsubd     xmm0,PS
 phsubsw    xmm0,PS
 phsubw     xmm0,PS
 pmaddubsw  xmm0,PS
 pmulhrsw   xmm0,PS
 pshufb     xmm0,PS
 psignb     xmm0,PS
 psignd     xmm0,PS
 psignw     xmm0,PS

 pclmullqlqdq xmm0,PD
 pclmulhqlqdq xmm0,PD
 pclmullqhqdq xmm0,PD
 pclmulhqhqdq xmm0,PD

 pcmpeqq    xmm0,PD
 pcmpgtq    xmm0,PD

 vbroadcastss xmm0,RS
 vbroadcastss ymm0,RS
 vbroadcastss zmm0,RS
 vbroadcastsd ymm0,SD
 vbroadcastsd zmm0,SD
 vbroadcastf128 ymm0,PS
 vbroadcasti128 ymm0,PS
 vbroadcastf32x4 ymm0,PS
 vbroadcastf32x4 zmm0,PS
 vbroadcastf64x2 ymm0,PD
 vbroadcastf64x2 zmm0,PD

 vpermilpd  ymm0,ymm0,PD
 vcmppd     ymm0,ymm0,PD,1
 vcmpps     ymm0,ymm0,PS,1


 ; Pseudo-Op for VCMP*

 vcmpeqps   xmm0,xmm0,PS
 vcmpeqps   ymm0,ymm0,PS

 define ZD <{ RS, RS, RS, RS, RS, RS, RS, RS }>
 define ZS <{ RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS, RS }>

for cm,<eq,lt,le,unord,neq,nlt,nle,ord,eq_uq,nge,ngt,false,neq_oq,ge,
    gt,true,eq_os,lt_oq,le_oq,unord_s,neq_us,nlt_uq,nle_uq,
    ord_s,eq_us,nge_uq,ngt_uq,false_os,neq_os,ge_oq,gt_oq,true_us>
    vcmp&cm&ps k1,zmm0,ZS
    endm

for cm,<eq,lt,le,unord,neq,nlt,nle,ord,eq_uq,nge,ngt,false,neq_oq,ge,
    gt,true,eq_os,lt_oq,le_oq,unord_s,neq_us,nlt_uq,nle_uq,
    ord_s,eq_us,nge_uq,ngt_uq,false_os,neq_os,ge_oq,gt_oq,true_us>
    vcmp&cm&pd k1,zmm0,ZD
    endm

for cm,<eq,lt,le,unord,neq,nlt,nle,ord,eq_uq,nge,ngt,false,neq_oq,ge,
    gt,true,eq_os,lt_oq,le_oq,unord_s,neq_us,nlt_uq,nle_uq,
    ord_s,eq_us,nge_uq,ngt_uq,false_os,neq_os,ge_oq,gt_oq,true_us>
    vcmp&cm&ss k1,zmm0,RS
    endm

for cm,<eq,lt,le,unord,neq,nlt,nle,ord,eq_uq,nge,ngt,false,neq_oq,ge,
    gt,true,eq_os,lt_oq,le_oq,unord_s,neq_us,nlt_uq,nle_uq,
    ord_s,eq_us,nge_uq,ngt_uq,false_os,neq_os,ge_oq,gt_oq,true_us>
    vcmp&cm&sd k1,zmm0,RS
    endm

for cm,<gtb,gtw,gtd,gtq>
    vpcmp&cm& xmm0,xmm0,PS
    endm

for cm,<eq,lt,le,neq,nlt,nle,equ,ltu,leu,nequ,nltu,nleu>
    vpcmp&cm&b k1,zmm0,ZS
    endm

for cm,<eq,lt,le,neq,nlt,nle,equ,ltu,leu,nequ,nltu,nleu>
    vpcmp&cm&w k1,zmm0,ZS
    endm

for cm,<eq,lt,le,neq,nlt,nle,equ,ltu,leu,nequ,nltu,nleu>
    vpcmp&cm&d k1,zmm0,ZS
    endm

for cm,<eq,lt,le,neq,nlt,nle,equ,ltu,leu,nequ,nltu,nleu>
    vpcmp&cm&q k1,zmm0,ZS
    endm

 end
