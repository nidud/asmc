; SETJMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

.template _JUMP_BUFFER
ifdef _M_IX86
    _Ebp    dd ?
    _Ebx    dd ?
    _Edi    dd ?
    _Esi    dd ?
    _Esp    dd ?
    _Eip    dd ?
else
    _Rbx    dq ?
    _Rsp    dq ?
    _Rbp    dq ?
    _Rsi    dq ?
    _Rdi    dq ?
    _R12    dq ?
    _R13    dq ?
    _R14    dq ?
    _R15    dq ?
    _Rip    dq ?
endif
   .ends

.code

setjmp::
    xor eax,eax
ifdef _M_X64
ifdef __UNIX__
    mov rcx,rdi
endif
    mov [rcx]._JUMP_BUFFER._Rbp,rbp
    mov [rcx]._JUMP_BUFFER._Rbx,rbx
    mov [rcx]._JUMP_BUFFER._Rsp,rsp
    mov [rcx]._JUMP_BUFFER._Rsi,rsi
    mov [rcx]._JUMP_BUFFER._Rdi,rdi
    mov [rcx]._JUMP_BUFFER._R12,r12
    mov [rcx]._JUMP_BUFFER._R13,r13
    mov [rcx]._JUMP_BUFFER._R14,r14
    mov [rcx]._JUMP_BUFFER._R15,r15
    mov rdx,[rsp]
    mov [rcx]._JUMP_BUFFER._Rip,rdx
else
    mov [ecx]._JUMP_BUFFER._Ebp,ebp
    mov [ecx]._JUMP_BUFFER._Ebx,ebx
    mov [ecx]._JUMP_BUFFER._Esp,esp
    mov [ecx]._JUMP_BUFFER._Esi,esi
    mov [ecx]._JUMP_BUFFER._Edi,edi
    mov [ecx]._JUMP_BUFFER._Esi,esi
    mov [ecx]._JUMP_BUFFER._Edi,edi
    mov edx,[esp]
    mov [ecx]._JUMP_BUFFER._Eip,edx
endif
    ret

longjmp::
ifdef _M_X64
ifdef __UNIX__
    mov rcx,rdi
    mov eax,esi
else
    mov eax,edx
endif
    mov rbp,[rcx]._JUMP_BUFFER._Rbp
    mov rbx,[rcx]._JUMP_BUFFER._Rbx
    mov rsi,[rcx]._JUMP_BUFFER._Rsi
    mov rdi,[rcx]._JUMP_BUFFER._Rdi
    mov r12,[rcx]._JUMP_BUFFER._R12
    mov r13,[rcx]._JUMP_BUFFER._R13
    mov r14,[rcx]._JUMP_BUFFER._R14
    mov r15,[rcx]._JUMP_BUFFER._R15
    mov rsp,[rcx]._JUMP_BUFFER._Rsp
    mov rcx,[rcx]._JUMP_BUFFER._Rip
    jmp rcx
else
    mov ecx,[esp+4]
    mov eax,[esp+8]
    mov ebp,[ecx]._JUMP_BUFFER._Ebp
    mov ebx,[ecx]._JUMP_BUFFER._Ebx
    mov esi,[ecx]._JUMP_BUFFER._Esi
    mov edi,[ecx]._JUMP_BUFFER._Edi
    mov esp,[ecx]._JUMP_BUFFER._Esp
    mov ecx,[ecx]._JUMP_BUFFER._Eip
    jmp ecx
endif

    end
