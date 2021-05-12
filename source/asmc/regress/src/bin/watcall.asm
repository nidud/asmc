
    ; 2.31.33 WATCALL

    .486
    .model flat, watcall
    .code

p0  proc a1:dword, a2:dword, a3:dword, a4:dword
    mov edi,a1
    mov edi,a2
    mov edi,a3
    mov edi,a4
    ret
p0  endp
c0  proc
    p0(eax,edx,ebx,ecx)
    p0(eax,eax,ebx,ecx)
    p0(1,2,3,4)
    ret
c0  endp

p1  proc a1:qword, a2:qword
    ret
p1  endp
c1  proc
    p1(edx::eax,ecx::ebx)
    p1(eax::eax,ecx::ebx)
    p1(1,2)
    ret
c1  endp

p2  proc a1:byte, a2:byte, a3:byte, a4:byte, a5:byte, a6:byte
    mov al,a1
    mov al,a2
    mov al,a3
    mov al,a4
    mov al,a5
    mov al,a6
    ret
p2  endp
c2  proc
    p2(al,dl,bl,cl,1,2)
    p2(al,al,bl,cl,1,2)
    p2(0,0,0,0,5,6)
    ret
c2  endp

    end
