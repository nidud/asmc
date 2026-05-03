;
; v2.27 -- VECTORCALL
;
;   .x64
;   .model flat, vectorcall
    .code

; No shadow stack space is allocated

p1  proc a1:byte, a2:byte, a3:byte, a4:byte, a5:byte, a6:byte
    mov al,a1
    mov al,a2
    mov al,a3
    mov al,a4
    mov al,a5
    mov al,a6
    ret
p1  endp

p2  proc a1:word, a2:word, a3:word, a4:word, a5:word, a6:word
    mov ax,a1
    mov ax,a2
    mov ax,a3
    mov ax,a4
    mov ax,a5
    mov ax,a6
    ret
p2  endp

p4  proc a1:dword, a2:dword, a3:dword, a4:dword, a5:dword, a6:dword
    mov eax,a1
    mov eax,a2
    mov eax,a3
    mov eax,a4
    mov eax,a5
    mov eax,a6
    ret
p4  endp

p8  proc a1:qword, a2:qword, a3:qword, a4:qword, a5:qword, a6:qword
    mov rax,a1
    mov rax,a2
    mov rax,a3
    mov rax,a4
    mov rax,a5
    mov rax,a6
    ret
p8  endp

f4  proc a1:REAL4, a2:REAL4, a3:REAL4, a4:REAL4, a5:REAL4, a6:REAL4
    movss xmm0,a1
    movss xmm1,a2
    movss xmm2,a3
    movss xmm3,a4
    movss xmm4,a5
    movss xmm5,a6
    ret
f4  endp

; The shadow stack space allocated for vector type arguments is fixed at
; 16 * 6 bytes.

    option win64:auto

f8  proc a1:REAL8, a2:REAL8, a3:REAL8, a4:REAL8, a5:REAL8, a6:REAL8
    movsd xmm0,a1
    movsd xmm1,a2
    movsd xmm2,a3
    movsd xmm3,a4
    movsd xmm4,a5
    movsd xmm5,a6
    ret
f8  endp


; If the /homeparams option applied or option save used as below the first six
; arguments are saved on the stack.

    option win64:save

f16 proc a1:REAL16, a2:REAL16, a3:REAL16, a4:REAL16, a5:REAL16, a6:REAL16
    movaps xmm0,a1
    movaps xmm1,a2
    movaps xmm2,a3
    movaps xmm3,a4
    movaps xmm4,a5
    movaps xmm5,a6
    ret
f16 endp

; Mixed bag of argument sizes, locals and user regs.

mix proc uses rsi rdi rbx a1:byte, a2:word, a3:dword, a4:qword, a5:real8, a6:real16

  local x:real16

    lea rax,x
    add al,a1
    add ax,a2
    add eax,a3
    add rax,a4
    addps xmm4,a5
    addps xmm5,a6
    ret
mix endp

pp  proc a1:ptr
  local b:dword
    mov b,eax
    mov rax,a1
    ret
pp  endp

main proc ; no @@ suffix added to "main"

    invoke f4, xmm0,xmm1,xmm2,xmm3,xmm4,xmm5
    invoke f8, xmm0,xmm1,xmm2,xmm3,xmm4,xmm5
    invoke f16,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5
    invoke mix,cl,dx,r8d,r9,xmm4,xmm5
    invoke p1, cl,dl,r8b,r9b,r10b,r11b
    invoke p2, cx,dx,r8w,r9w,r10w,r11w
    invoke p4, ecx,edx,r8d,r9d,r10d,r11d
    invoke p8, rcx,rdx,r8,r9,r10,r11
    invoke pp, addr pp

    invoke mix,cl,dx,r8d,r9,4.0,5.0
    ret

main endp

    end

