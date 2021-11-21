.code
Instruction proc uses rsi rdi rbx
mov edi,2
mov eax,0xFFFF
for op1,<cl,dl,r8b,r9b,r10b,r11b,cl>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov edx,0
idiv di
endm
endm
ret
Instruction endp
end
