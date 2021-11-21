.code
Instruction proc uses rsi rdi rbx
mov rdi,rcx
mov rsi,rdx
for op1,<rcx,rdx,r8,r9,r10,r11,rax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
std
endm
endm
cld
ret
Instruction endp
end
