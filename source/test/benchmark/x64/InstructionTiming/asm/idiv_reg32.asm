.code
Instruction proc uses rsi rdi rbx
mov edi,2
mov eax,0xFFFFFFFF
for op1,<ecx,edx,r8d,r9d,r10d,r11d,eax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov edx,0
idiv edi
endm
endm
ret
Instruction endp
end
