.code
Instruction proc uses rsi rdi rbx
mov rsi,rsp
mov rdi,rbp
for op1,<rcx,rdx,r8,r9,r10,r11,rax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
enter 8,0
endm
endm
mov rsp,rsi
mov rbp,rdi
ret
Instruction endp
end
