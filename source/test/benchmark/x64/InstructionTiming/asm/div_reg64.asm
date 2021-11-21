.code
Instruction proc uses rsi rdi rbx
mov edi,2
mov eax,84*1000
for op1,<rcx,rdx,r8,r9,r10,r11,rax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov edx,0
div rdi
endm
endm
ret
Instruction endp
end
