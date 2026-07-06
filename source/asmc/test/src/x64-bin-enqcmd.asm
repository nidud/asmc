; X64-BIN-ENQCMD.ASM--
;
; v2.39.01: fixed encoding for ENQCMD, ENQCMDS, and MOVDIR64B
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0xf2, 0x0f, 0x38, 0xf8, 0x30>, <enqcmd rsi,[rax]>
testcase <0xf3, 0x0f, 0x38, 0xf8, 0x30>, <enqcmds rsi,[rax]>
testcase <0x66, 0x0f, 0x38, 0xf8, 0x30>, <movdir64b rsi,[rax]>
testcase <0x48, 0x0f, 0x38, 0xf9, 0x0e>, <movdiri [rsi],rcx>
end
