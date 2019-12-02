.pragma list(push, 0)

ifndef __CRTL_INC
__CRTL_INC equ <>

ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc)

_EXEC_BAT	equ 1
_EXEC_COM	equ 2
_EXEC_EXE	equ 3
_EXEC_CMD	equ 4

externdef	OldErrorMode:dword

__isexec	proto __cdecl :string_t
__setenvp	proto __cdecl :string_t
__wsetenvp	proto __cdecl :wstring_t
__initialize	proto __cdecl :ptr, :ptr
__allocwpath	proto __cdecl :string_t
__coreleft	proto __cdecl

strfn		proto __cdecl :string_t
strext		proto __cdecl :string_t
strfcat		proto __cdecl :string_t, :string_t, :string_t
memxchg		proto __cdecl :string_t, :string_t, :size_t
__xtol		proto __cdecl :string_t
__xtoi64	proto __cdecl :string_t

; GCC

__divti3	proto __cdecl ; rdx::rcx / r9::r8
__modti3	proto __cdecl ; rdx::rcx % r9::r8
__udivti3	proto __cdecl ; rdx::rcx / r9::r8
__umodti3	proto __cdecl ; rdx::rcx % r9::r8

; Microsoft

_allshr		proto __cdecl ; edx:eax >> cl
_aullshr	proto __cdecl ; edx:eax >> cl | rdx:rax << cl
__ullshr	proto __cdecl ; edx:eax >> cl
_allshl		proto __cdecl ; edx:eax << cl | rdx:rax << cl
__llshl		proto __cdecl ; edx:eax << cl

; stdcall / no decoration | fastcall

__lldiv		proto __cdecl ;:qword, :qword
_alldiv		proto __cdecl ;:qword, :qword | rdx::rcx / r9::r8
__llmul		proto __cdecl ;:qword, :qword
_allmul		proto __cdecl ;:qword, :qword | rdx::rcx * r9::r8
_allrem		proto __cdecl ;:qword, :qword | rdx::rcx % r9::r8
_aulldiv	proto __cdecl ;:qword, :qword | rdx::rcx / r9::r8
__ullmod	proto __cdecl ;:qword, :qword
_aullrem	proto __cdecl ;:qword, :qword | rdx::rcx % r9::r8

; Watcom

_I8D		proto __cdecl ; edx:eax / ecx:ebx --> edx:eax.ecx
_U8D		proto __cdecl ; edx:eax / ecx:ebx --> edx:eax.ecx
_U8M		proto __cdecl ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8M		proto __cdecl ; edx:eax * ecx:ebx --> ecx:ebx:edx:eax
_I8RS		proto __cdecl ; edx:eax >> bl
_U8RS		proto __cdecl ; edx:eax >> bl
_I8LS		proto __cdecl ; edx:eax << bl
_U8LS		proto __cdecl ; edx:eax << bl
_FLDA		proto __cdecl ; long double[EBX] = long double[EAX] + long double[EDX]
_FLDS		proto __cdecl ; long double[EBX] = long double[EAX] - long double[EDX]
_FLDC		proto __cdecl ; CMP(long double[EAX], long double[EDX])
_FLDM		proto __cdecl ; long double[EBX] = long double[EAX] * long double[EDX]
_FLDD		proto __cdecl ; long double[EBX] = long double[EAX] / long double[EDX]
_iFDLD		proto __cdecl ; double[EAX] --> long double[EDX]
_iLDFD		proto __cdecl ; long double[EAX] --> double[EDX]
_U4LD		proto __cdecl ; DWORD [eax] to long double[edx]
_I4LD		proto __cdecl ; SDWORD [eax] to long double[edx]
_U8LD		proto __cdecl ; QWORD [eax] to long double[edx]
_I8LD		proto __cdecl ; SQWORD [eax] to long double[edx]

endif

.pragma list(pop)
