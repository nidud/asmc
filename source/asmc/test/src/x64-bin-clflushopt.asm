; X64-BIN-CLFLUSHOPT.ASM--
;
; From GAS: clflushopt-intel.d
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0x66, 0x0f, 0xae, 0x39>, <clflushopt BYTE PTR [rcx]>
testcase <0x66, 0x0f, 0xae, 0xbc, 0xf4, 0xc0, 0x1d, 0xfe, 0xff>, <clflushopt BYTE PTR [rsp+rsi*8-0x1e240]>
end
