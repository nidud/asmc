; X64-BIN-PTWRITE.ASM--
;
; PTWRITE/CLFLUSH/CLFLUSHOPT
;
testcase macro B, S
 ifdef BIN
  db B
 else
  S
 endif
 endm
.code
testcase <0xf3, 0x0f, 0xae, 0x21>, <ptwrite DWORD PTR [rcx]>
testcase <0xf3, 0x0f, 0xae, 0xe1>, <ptwrite ecx>
testcase <0xf3, 0x0f, 0xae, 0x24, 0x3b>, <ptwrite DWORD PTR [rbx+rdi]>
testcase <0x0f, 0xae, 0x38>, <clflush BYTE PTR [rax]>
testcase <0x66, 0x0f, 0xae, 0x38>, <clflushopt BYTE PTR [rax]>
end
