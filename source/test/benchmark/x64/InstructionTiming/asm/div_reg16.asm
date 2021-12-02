.code
Instruction proc uses rsi rdi rbx
mov rdi,rcx
mov rsi,rdx
I = 0
for op1,<cx,dx,r8w,r9w,r10w,r11w,ax>
for op2,<rbx,r12,r13,r14,r15,rcx,rdx,r8,r9,r10,r11,rax>
mov edx,0
div di
I = I + 1
endm
endm
ret
Instruction endp
end
