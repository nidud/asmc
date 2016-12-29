ifndef __LIBC_INC
 include libc.inc
endif

.xlist

SIGINT		equ 2	; interrupt
SIGILL		equ 4	; illegal instruction - invalid function image
SIGFPE		equ 8	; floating point exception
SIGSEGV		equ 11	; segment violation
SIGTERM		equ 15	; Software termination signal from kill
SIGBREAK	equ 21	; Ctrl-Break sequence
SIGABRT		equ 22	; abnormal termination triggered by abort call
NSIG		equ 23	; maximum signal number + 1
;
; Exception disposition return values.
;
ExceptionContinueExecution	equ 0
ExceptionContinueSearch		equ 1
ExceptionNestedException	equ 2
ExceptionCollidedUnwind		equ 3

EXCEPTION_ACCESS_VIOLATION	equ 0xC0000005
EXCEPTION_ARRAY_BOUNDS_EXCEEDED equ 0xC000008C
EXCEPTION_BREAKPOINT		equ 0x80000003
EXCEPTION_DATATYPE_MISALIGNMENT equ 0x80000002
EXCEPTION_FLT_DENORMAL_OPERAND	equ 0xC000008D
EXCEPTION_FLT_DIVIDE_BY_ZERO	equ 0xC000008E
EXCEPTION_FLT_INEXACT_RESULT	equ 0xC000008F
EXCEPTION_FLT_INVALID_OPERATION equ 0xC0000090
EXCEPTION_FLT_OVERFLOW		equ 0xC0000091
EXCEPTION_FLT_STACK_CHECK	equ 0xC0000092
EXCEPTION_FLT_UNDERFLOW		equ 0xC0000093
EXCEPTION_ILLEGAL_INSTRUCTION	equ 0xC000001D
EXCEPTION_IN_PAGE_ERROR		equ 0xC0000006
EXCEPTION_INT_DIVIDE_BY_ZERO	equ 0xC0000094
EXCEPTION_INT_OVERFLOW		equ 0xC0000095
EXCEPTION_INVALID_DISPOSITION	equ 0xC0000026
EXCEPTION_NONCONTINUABLE_EXCEPTION equ 0xC0000025
EXCEPTION_PRIV_INSTRUCTION	equ 0xC0000096
EXCEPTION_SINGLE_STEP		equ 0x80000004
EXCEPTION_STACK_OVERFLOW	equ 0xC00000FD

EXCEPTION_EXECUTE_HANDLER	equ 1
EXCEPTION_CONTINUE_SEARCH	equ 0
EXCEPTION_CONTINUE_EXECUTION	equ -1

EXCEPTION_NONCONTINUABLE	equ 1	; Noncontinuable exception
EXCEPTION_MAXIMUM_PARAMETERS	equ 15	; maximum number of exception parameters

SIZE_OF_80387_REGISTERS		equ 80

EXCEPTION_RECORD	STRUC SIZE_T
ExceptionCode		DWORD ?
ExceptionFlags		DWORD ?
ExceptionRecord		PVOID ? ; S_EXC_RECORD *
ExceptionAddress	PVOID ?
NumberParameters	DWORD ?
ExceptionInformation	PVOID EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD	ENDS

FLOATING_SAVE_AREA	STRUC SIZE_T
ControlWord		dd ?
StatusWord		dd ?
TagWord			dd ?
ErrorOffset		dd ?
ErrorSelector		dd ?
DataOffset		dd ?
DataSelector		dd ?
RegisterArea		db SIZE_OF_80387_REGISTERS dup(?)
Cr0NpxState		dd ?
FLOATING_SAVE_AREA	ENDS

LEGACY_SAVE_AREA	STRUC
ControlWord		dw ?
Reserved0		dw ?
StatusWord		dw ?
Reserved1		dw ?
TagWord			dw ?
Reserved2		dw ?
ErrorOffset		dd ?
ErrorSelector		dw ?
ErrorOpcode		dw ?
DataOffset		dd ?
DataSelector		dw ?
Reserved3		dw ?
FloatRegisters		db 8*10 dup (?)
LEGACY_SAVE_AREA	ENDS

XMMREG	UNION
STRUC
x_dq_0	dq ?
x_dq_1	dq ?
ENDS
STRUC
x_dd_0	dd ?
x_dd_1	dd ?
x_dd_2	dd ?
x_dd_3	dd ?
ENDS
x_dw_0	dw ?
STRUC
x_db_0	db ?
x_db_1	db ?
ENDS
XMMREG	ENDS

EXCEPTION_CONTEXT STRUC SIZE_T
IFDEF _WIN64
 P1Home			dq ?
 P2Home			dq ?
 P3Home			dq ?
 P4Home			dq ?
 P5Home			dq ?
 P6Home			dq ?
 ContextFlags		dd ?
 MxCsr			dd ?
 SegCs			dw ?
 SegDs			dw ?
 SegEs			dw ?
 SegFs			dw ?
 SegGs			dw ?
 SegSs			dw ?
 EFlags			dd ?
 _Dr0			dq ?
 _Dr1			dq ?
 _Dr2			dq ?
 _Dr3			dq ?
 _Dr6			dq ?
 _Dr7			dq ?
 _Rax			dq ?
 _Rcx			dq ?
 _Rdx			dq ?
 _Rbx			dq ?
 _Rsp			dq ?
 _Rbp			dq ?
 _Rsi			dq ?
 _Rdi			dq ?
 _R8			dq ?
 _R9			dq ?
 _R10			dq ?
 _R11			dq ?
 _R12			dq ?
 _R13			dq ?
 _R14			dq ?
 _R15			dq ?
 _Rip			dq ?
 _Xmm0			XMMREG <>
 _Xmm1			XMMREG <>
 _Xmm2			XMMREG <>
 _Xmm3			XMMREG <>
 _Xmm4			XMMREG <>
 _Xmm5			XMMREG <>
 _Xmm6			XMMREG <>
 _Xmm7			XMMREG <>
 _Xmm8			XMMREG <>
 _Xmm9			XMMREG <>
 _Xmm10			XMMREG <>
 _Xmm11			XMMREG <>
 _Xmm12			XMMREG <>
 _Xmm13			XMMREG <>
 _Xmm14			XMMREG <>
 _Xmm15			XMMREG <>
 FltSave		LEGACY_SAVE_AREA <>
 Fill			dd ?
 DebugControl		dq ?
 LastBranchToRip	dq ?
 LastBranchFromRip	dq ?
 LastExceptionToRip	dq ?
 LastExceptionFromRip	dq ?
 Fill1			dq ?
ELSE
 ContextFlags		dd ?
 _Dr0			dd ?
 _Dr1			dd ?
 _Dr2			dd ?
 _Dr3			dd ?
 _Dr6			dd ?
 _Dr7			dd ?
 FloatSave		FLOATING_SAVE_AREA <>
 SegGs			dd ?
 SegFs			dd ?
 SegEs			dd ?
 SegDs			dd ?
 _Edi			dd ?
 _Esi			dd ?
 _Ebx			dd ?
 _Edx			dd ?
 _Ecx			dd ?
 _Eax			dd ?
 _Ebp			dd ?
 _Eip			dd ?
 SegCs			dd ?
 EFlags			dd ?
 _Esp			dd ?
 SegSs			dd ?
ENDIF
EXCEPTION_CONTEXT	ENDS

EXCEPTION_POINTERS	STRUC SIZE_T
ExceptionRecord		SIZE_T ?
ContextRecord		SIZE_T ?
EXCEPTION_POINTERS	ENDS

EXCEPTION_REGISTRATION	STRUC SIZE_T
prev			SIZE_T ?
handler			SIZE_T ?
EXCEPTION_REGISTRATION	ENDS

PEXCEPTION_RECORD	TYPEDEF PTR EXCEPTION_RECORD
PEXCEPTION_CONTEXT	TYPEDEF PTR EXCEPTION_CONTEXT
PEXCEPTION_POINTERS	TYPEDEF PTR EXCEPTION_POINTERS
PEXCEPTION_REGISTRATION TYPEDEF PTR EXCEPTION_REGISTRATION

externdef pCurrentException:PEXCEPTION_POINTERS
externdef pExceptionReg:PEXCEPTION_REGISTRATION

signal	proto :UINT, :PTR PROC
raise	proto :UINT

PrintContext proto \
	ContextRecord:	   PEXCEPTION_CONTEXT,
	ExceptionRecord:   PEXCEPTION_RECORD
IFDEF _WIN64
 ExceptionHandler proto \
	ExceptionRecord:   PEXCEPTION_RECORD,
	EstablisherFrame:  LPDWORD,
	ContextRecord:	   PEXCEPTION_CONTEXT,
	DispatcherContext: LPDWORD
ENDIF

.list
