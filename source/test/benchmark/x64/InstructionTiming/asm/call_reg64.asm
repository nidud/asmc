.code
Instruction proc uses rsi rdi rbx
lea rdi,@F
for op1,<rcx,rdx,r8,r9,r10,r11,rax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
call rdi
endm
endm
ret
@@:
retn
Instruction endp
end
