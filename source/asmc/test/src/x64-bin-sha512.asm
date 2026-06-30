; X64-BIN-SHA512.ASM--
;
; From GAS: sha512-intel.d
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0xc4, 0xe2, 0x7f, 0xcc, 0xf5>, <vsha512msg1 ymm6,xmm5>
testcase <0xc4, 0xe2, 0x7f, 0xcd, 0xf5>, <vsha512msg2 ymm6,ymm5>
testcase <0xc4, 0xe2, 0x57, 0xcb, 0xf4>, <vsha512rnds2 ymm6,ymm5,xmm4>
end
