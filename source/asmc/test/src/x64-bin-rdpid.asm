; X64-BIN-RDPID.ASM--
;
; From GAS: rdpid-intel.d
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0xf3, 0x0f, 0xc7, 0xf8>, <rdpid eax>
testcase <0xf3, 0x0f, 0xc7, 0xf9>, <rdpid ecx>
end
