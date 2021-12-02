.code
Instruction proc uses rsi rdi rbx
mov rdi,rcx
mov rsi,rdx
I = 0
for op1,<xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6>
for op2,<xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm6,xmm5,xmm4,xmm3>
blendvpd op1,op2,xmm0
I = I + 1
endm
endm
ret
Instruction endp
end
