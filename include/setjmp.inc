.pragma list(push, 0)
ifndef __SETJMP_INC
define __SETJMP_INC
ifndef _LIBC_
include libc.inc
endif

if not defined(_CRT_SETJMP) and defined(_CRTBLD)
define _CRT_SETJMP
endif

define setjump <_setjmp>

.template _JUMP_BUFFER
ifdef _M_IX86
    _Ebp            dd ?
    _Ebx            dd ?
    _Edi            dd ?
    _Esi            dd ?
    _Esp            dd ?
    _Eip            dd ?
ifdef _CRT_SETJMP
    Registration    dd ?
    TryLevel        dd ?
    Cookie          dd ?
    UnwindFunc      dd ?
    UnwindData      dd 6 dup(?)
endif
else
ifdef _CRT_SETJMP
    _Frame          dq ?
endif
    _Rbx            dq ?
    _Rsp            dq ?
    _Rbp            dq ?
ifndef __UNIX__
    _Rsi            dq ?
    _Rdi            dq ?
endif
    _R12            dq ?
    _R13            dq ?
    _R14            dq ?
    _R15            dq ?
    _Rip            dq ?
ifdef _CRT_SETJMP
    MxCsr           dq ?
    FpCsr           dq ?
    Spare           dq ?
    _Xmm6           xmmword ?
    _Xmm7           xmmword ?
    _Xmm8           xmmword ?
    _Xmm9           xmmword ?
    _Xmm10          xmmword ?
    _Xmm11          xmmword ?
    _Xmm12          xmmword ?
    _Xmm13          xmmword ?
    _Xmm14          xmmword ?
    _Xmm15          xmmword ?
endif
endif
   .ends
    jmp_buf typedef ptr _JUMP_BUFFER

define _JBLEN (_JUMP_BUFFER / size_t)
define _JBTYPE <size_t>

ifndef _CRT_SETJMP

_setjmp proto fastcall buf:jmp_buf {
    xor eax,eax
ifdef _M_X64
    mov [rcx]._JUMP_BUFFER._Rbp,rbp
    mov [rcx]._JUMP_BUFFER._Rbx,rbx
    mov [rcx]._JUMP_BUFFER._Rsp,rsp
ifndef __UNIX__
    mov [rcx]._JUMP_BUFFER._Rsi,rsi
    mov [rcx]._JUMP_BUFFER._Rdi,rdi
endif
    mov [rcx]._JUMP_BUFFER._R12,r12
    mov [rcx]._JUMP_BUFFER._R13,r13
    mov [rcx]._JUMP_BUFFER._R14,r14
    mov [rcx]._JUMP_BUFFER._R15,r15
    lea rdx,[rip+4]
    mov [rcx]._JUMP_BUFFER._Rip,rdx
else
    mov [ecx]._JUMP_BUFFER._Ebp,ebp
    mov [ecx]._JUMP_BUFFER._Ebx,ebx
    mov [ecx]._JUMP_BUFFER._Esp,esp
    mov [ecx]._JUMP_BUFFER._Esi,esi
    mov [ecx]._JUMP_BUFFER._Edi,edi
    mov [ecx]._JUMP_BUFFER._Esi,esi
    mov [ecx]._JUMP_BUFFER._Edi,edi
    lea edx,[$+9]
    mov [ecx]._JUMP_BUFFER._Eip,edx
endif
    }

longjmp proto fastcall buf:jmp_buf, retval:int_t {
ifdef _M_X64
    mov rbp,[rcx]._JUMP_BUFFER._Rbp
    mov rbx,[rcx]._JUMP_BUFFER._Rbx
ifndef __UNIX__
    mov rsi,[rcx]._JUMP_BUFFER._Rsi
    mov rdi,[rcx]._JUMP_BUFFER._Rdi
endif
    mov r12,[rcx]._JUMP_BUFFER._R12
    mov r13,[rcx]._JUMP_BUFFER._R13
    mov r14,[rcx]._JUMP_BUFFER._R14
    mov r15,[rcx]._JUMP_BUFFER._R15
    mov rsp,[rcx]._JUMP_BUFFER._Rsp
    mov rcx,[rcx]._JUMP_BUFFER._Rip
    mov eax,edx
    jmp rcx
else
    mov ebp,[ecx]._JUMP_BUFFER._Ebp
    mov ebx,[ecx]._JUMP_BUFFER._Ebx
    mov esi,[ecx]._JUMP_BUFFER._Esi
    mov edi,[ecx]._JUMP_BUFFER._Edi
    mov esp,[ecx]._JUMP_BUFFER._Esp
    mov ecx,[ecx]._JUMP_BUFFER._Eip
    mov eax,edx
    jmp ecx
endif
    }

else ; _CRT_SETJMP

.pragma comment(lib, libc, msvcrt)

_setjmp proto __cdecl :jmp_buf
longjmp proto __cdecl :jmp_buf, :int_t

endif

endif
.pragma list(pop)
