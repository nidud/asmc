.pragma list(push, 0)

include libc.inc

ifdef _M_IX86

    _JBLEN  equ 16
    _JBTYPE equ <int_t>

    _JUMP_BUFFER	struct
	_Ebp		dd ?
	_Ebx		dd ?
	_Edi		dd ?
	_Esi		dd ?
	_Esp		dd ?
	_Eip		dd ?
	Registration	dd ?
	TryLevel	dd ?
	Cookie		dd ?
	UnwindFunc	dd ?
	UnwindData	dd 6 dup(?)
    _JUMP_BUFFER	ends

elseifdef _M_X64

    SETJMP_FLOAT128	struct
	Part		dq 2 dup(?)
    SETJMP_FLOAT128	ends

    _JBLEN  equ 16
    _JBTYPE typedef SETJMP_FLOAT128

    _JUMP_BUFFER	struct
	_Frame		dq ?
	_Rbx		dq ?
	_Rsp		dq ?
	_Rbp		dq ?
	_Rsi		dq ?
	_Rdi		dq ?
	_R12		dq ?
	_R13		dq ?
	_R14		dq ?
	_R15		dq ?
	_Rip		dq ?
	MxCsr		dq ?
	FpCsr		dq ?
	Spare		dq ?
	_Xmm6		SETJMP_FLOAT128 <>
	_Xmm7		SETJMP_FLOAT128 <>
	_Xmm8		SETJMP_FLOAT128 <>
	_Xmm9		SETJMP_FLOAT128 <>
	_Xmm10		SETJMP_FLOAT128 <>
	_Xmm11		SETJMP_FLOAT128 <>
	_Xmm12		SETJMP_FLOAT128 <>
	_Xmm13		SETJMP_FLOAT128 <>
	_Xmm14		SETJMP_FLOAT128 <>
	_Xmm15		SETJMP_FLOAT128 <>
    _JUMP_BUFFER	ends

endif

jmp_buf typedef ptr _JUMP_BUFFER

setjmp proto __cdecl :jmp_buf
_setjmp proto __cdecl :jmp_buf
longjmp proto __cdecl :jmp_buf, :int_t

.pragma list(pop)
