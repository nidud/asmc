
;--- 128-bit <r64>::<r64> invoke arguments

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code
    option win64:3

f1  proc a1:oword, a2:word, a3:byte, a4:oword, a5:dword
    mov rax,qword ptr a1
    mov ax,a2
    mov al,a3
    mov rax,qword ptr a4
    mov eax,a5
    ret
f1  endp

f2  proc a1:qword, a2:dword, a3:oword, a4:oword, a5:dword
    mov rax,a1
    mov eax,a2
    mov rax,qword ptr a3
    mov rax,qword ptr a4
    mov eax,a5
    ret
f2  endp

f3  proc a1:word, a2:byte, a3:oword, a4:oword
    f2(rcx, edx, r9::r8, r11::r10, edi)
    f1([rcx], a1, a2, [rcx], 1)
    f1(a3, a1, a2, a4, 1)
    ret
f3  endp

    end
