ifndef __CRTL_INC
__CRTL_INC equ <>

ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_EXEC_BAT	equ 1
_EXEC_COM	equ 2
_EXEC_EXE	equ 3
_EXEC_CMD	equ 4

externdef	OldErrorMode:dword

__isexec	proto :LPSTR
__setenvp	proto :LPSTR
__wsetenvp	proto :LPWSTR
__setargv	proto :SIZE_T, :PVOID, :LPSTR
__setwargv	proto :SIZE_T, :PVOID, :LPWSTR
__initialize	proto :PVOID, :PVOID
__allocwpath	proto :LPSTR

ifndef _WIN64

; Microsoft

_allshr		proto c ; edx:eax >> cl
_aullshr	proto c ; edx:eax >> cl
__ullshr	proto c ; edx:eax >> cl
_allshl		proto c ; edx:eax << cl
__llshl		proto c ; edx:eax << cl

; stdcall / no decoration

__lldiv		proto c ;:qword, :qword
_alldiv		proto c ;:qword, :qword
__llmul		proto c ;:qword, :qword
_allmul		proto c ;:qword, :qword
_allrem		proto c ;:qword, :qword
_aulldiv	proto c ;:qword, :qword
__ullmod	proto c ;:qword, :qword
_aullrem	proto c ;:qword, :qword

; Watcom

_I8D		proto c ; edx:eax / ecx:ebx --> edx:eax.ecx
_U8D		proto c ; edx:eax / ecx:ebx --> edx:eax.ecx
_U8M		proto c ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8M		proto c ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8RS		proto c ; edx:eax >> bl
_U8RS		proto c ; edx:eax >> bl
_I8LS		proto c ; edx:eax << bl
_U8LS		proto c ; edx:eax << bl
_FLDA		proto c ; long double[EBX] = long double[EAX] + long double[EDX]
_FLDS		proto c ; long double[EBX] = long double[EAX] - long double[EDX]
_FLDC		proto c ; CMP(long double[EAX], long double[EDX])
_FLDM		proto c ; long double[EBX] = long double[EAX] * long double[EDX]
_FLDD		proto c ; long double[EBX] = long double[EAX] / long double[EDX]
_iFDLD		proto c ; double[EAX] --> long double[EDX]
_iLDFD		proto c ; long double[EAX] --> double[EDX]
_U4LD		proto c ; DWORD [eax] to long double[edx]
_I4LD		proto c ; SDWORD [eax] to long double[edx]
_U8LD		proto c ; QWORD [eax] to long double[edx]
_I8LD		proto c ; SQWORD [eax] to long double[edx]

endif

SSE_MMX		equ 0x0001
SSE_SSE		equ 0x0002
SSE_SSE2	equ 0x0004
SSE_SSE3	equ 0x0008
SSE_SSSE3	equ 0x0010
SSE_SSE41	equ 0x0020
SSE_SSE42	equ 0x0040
SSE_XGETBV	equ 0x0080
SSE_AVX		equ 0x0100
SSE_AVX2	equ 0x0200
SSE_AVXOS	equ 0x0400

externdef	sselevel:DWORD
GetSSELevel	proto

pragma_init macro pp, priority, name:=<INIT>
_&name& segment para public '&name&'
	size_t pp
	size_t priority
_&name& ends
	endm

pragma_exit macro pp, priority
pragma_init pp, priority, EXIT
	endm

.list
endif ; __CRTL_INC
