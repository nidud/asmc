;
; v2.27.30 - /Gv vectorcall 32-bit
;
    .686
    .xmm
    .model flat, vectorcall
    .code

p1  proc a1:byte, a2:byte, a3:byte, a4:byte, a5:byte, a6:byte
    mov eax,a1
    mov eax,a2
    mov al,a3
    mov al,a4
    mov al,a5
    mov al,a6
    ret
p1  endp

p2  proc a1:word, a2:word, a3:word, a4:word, a5:word, a6:word
    mov eax,a1
    mov eax,a2
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
    mov eax,dword ptr a1
    mov eax,dword ptr a2
    mov eax,dword ptr a3
    mov eax,dword ptr a4
    mov eax,dword ptr a5
    mov eax,dword ptr a6
    ret
p8  endp

pf  proc a1:REAL8, a2:REAL8, a3:REAL8, a4:REAL8, a5:REAL8, a6:REAL8
    movups xmm0,a1
    movups xmm1,a2
    movups xmm2,a3
    movups xmm3,a4
    movups xmm4,a5
    movups xmm5,a6
    ret
pf  endp

pp  proc a1:ptr
    local b:dword
    mov b,eax
    mov eax,a1
    ret
pp  endp

    invoke p1,cl,dl,al,bl,bl,bl
    invoke p2,cx,dx,ax,di,si,bx
    invoke p4,edx,ecx,eax,edi,esi,ebx
    invoke p8,1,2,3,4,5,6
    invoke p8,ecx::ecx,ecx::ecx,ecx::ecx,ecx::ecx,ecx::ecx,ecx::ecx
    invoke pf,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5
    invoke pf,xmm0,xmm0,xmm0,xmm0,xmm0,xmm0
    invoke pp,addr pp

    end

