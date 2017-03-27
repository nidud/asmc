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

_div64I		proto ; edx:eax / ecx:ebx --> edx:eax.ecx
_div64U		proto ; edx:eax / ecx:ebx --> edx:eax.ecx
_mul64		proto ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_shr64I		proto ; edx:eax >> cl
_shr64U		proto ; edx:eax >> cl

;
; long shift left
;
; signed and unsigned are same
;
_allshl		proto ; Microsoft - edx:eax << cl
__llshl		proto ;
_I8LS		proto ; Watcom	  - edx:eax << bl
_U8LS		proto ;

_addld		proto ; long double[EBX] = long double[EAX] + long double[EDX]
_subld		proto ; long double[EBX] = long double[EAX] - long double[EDX]
_cmpld		proto ; CMP(long double[EAX], long double[EDX])
_mulld		proto ; long double[EBX] = long double[EAX] * long double[EDX]
_divld		proto ; long double[EBX] = long double[EAX] / long double[EDX]
_fdtold		proto ; double[EAX] --> long double[EDX]
_fldtod		proto ; long double[EAX] --> double[EDX]
_u4told		proto ; DWORD [eax] to long double[edx]
_i4told		proto ; SDWORD [eax] to long double[edx]
_u8told		proto ; QWORD [eax] to long double[edx]
_i8told		proto ; SQWORD [eax] to long double[edx]

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
