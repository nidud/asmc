; X64-BIN-SUFFIX.ASM--
;
; From GAS: suffix-intel.d
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0x0f, 0x01, 0xc8>, <monitor>
testcase <0x0f, 0x01, 0xc9>, <mwait>
testcase <0x0f, 0x01, 0xc1>, <vmcall>
testcase <0x0f, 0x01, 0xc2>, <vmlaunch>
testcase <0x0f, 0x01, 0xc3>, <vmresume>
testcase <0x0f, 0x01, 0xc4>, <vmxoff>
testcase <0xcf>, <iretd>
end
