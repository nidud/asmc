.code
Instruction proc uses rsi rdi rbx
mov ecx,8
mov rsi,rdx
I = 0
for op1,<cl,dl,r8b,r9b,r10b,r11b,al>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov eax,0
idiv cl
I = I + 1
endm
endm
ret
Instruction endp
end
