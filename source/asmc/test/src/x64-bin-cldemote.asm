; X64-BIN-CLDEMOTE.ASM--
;
; From GAS: cldemote-intel.d
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0x0f, 0x1c, 0x01>, <cldemote BYTE PTR [rcx]>
testcase <0x0f, 0x1c, 0x84, 0xf4, 0xc0, 0x1d, 0xfe, 0xff>, <cldemote BYTE PTR [rsp+rsi*8-0x1e240]>
end
