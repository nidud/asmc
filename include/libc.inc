.pragma list(push, 0)
ifndef __LIBC_INC
define __LIBC_INC
;
; Master include file for the Asmc Run Time library.
;
define __STDC__
define __LIBC__ 236
ifdef __ASMC__
if ( __ASMC__ LT __LIBC__ )
.err <incorrect version. Use the header that matches with the Asmc Assembler.>
endif
endif
option casemap:none

;
; Architecture kinds:
;     _WIN64 (#define symbols)
;     _X86_
;     _AMD64_
;     _IA64_
;
; Machine Architectures:
;     _M_IX86
;     _M_AMD64
;     _M_IA64
;
ifdef _WIN64
ifdef _IA64_
define _M_IA64
else
define _AMD64_
define _M_AMD64 100
endif
define _M_X64	100
else
define _X86_
define _M_IX86	600
endif

ifdef _MT
define _CRTBLD
endif

ifndef _CRTIMP
if defined(__DLL__) or ( defined(CRTDLL) and defined(_CRTBLD) )
define _CRTIMP <export>
else
define _CRTIMP <>
endif
endif

ifdef __UNIX__
define __Ctype	<syscall>
define __Cdecl	<syscall>
define __cdecl	<syscall>
elseifdef _STDCALL_SUPPORTED
define __Cdecl	<c>
define __Ctype	<stdcall>
define __cdecl	<stdcall>
define WINAPI	<stdcall>
endif

ifdef __PE__	; asmc /pe
ifndef _MSVCRT	; msvcrt.lib
define _MSVCRT
endif
endif

ifndef __Cdecl	; vararg (...) type
ifdef _WIN64
define __Cdecl	<fastcall>
else
define __Cdecl	<c>
endif
endif

ifndef __cdecl	; libc/msvcrt types
ifdef _WIN64
define __cdecl	<fastcall>
else
define __cdecl	<c>
endif
endif

ifndef __Ctype	; default (user) type
ifdef _WIN64
define __Ctype	<fastcall>
else
define __Ctype	<c>
endif
endif
;
; Set Windows version
;
include sdkddkver.inc

ifndef _MSC_VER
;
; _MSC_VER Defined as an integer literal that encodes the major and minor number
; elements of the compiler's version number. The major number is the first
; element of the period-delimited version number and the minor number is the
; second element. For example, if the version number of the Visual C++ compiler
; is 17.00.51106.1, the _MSC_VER macro evaluates to 1700. Enter cl /? at the
; command line to view the compiler's version number. This macro is always defined.
;
define _MSC_VER 1200 ; Visual C++ version 12.0
endif

ifndef _MSC_FULL_VER
;
; _MSC_FULL_VER Defined as an integer literal that encodes the major, minor,
; and build number elements of the compiler's version number. The major number
; is the first element of the period-delimited version number, the minor number
; is the second element, and the build number is the third element. For example,
; if the version number of the Visual C++ compiler is 15.00.20706.01, the
; _MSC_FULL_VER macro evaluates to 150020706. Enter cl /? at the command line
; to view the compiler's version number. This macro is always defined.
;
define _MSC_FULL_VER 120000000 ; Visual C++ version 12.0
endif

ifndef _WIN32
define _WIN32 ; default
endif

ifdef _WIN64
option	win64:3
ifdef __UNIX__
option	cstack:on
else
option	frame:auto
endif
SIZE_T	typedef QWORD
else
ifdef __SSE__
.686
.xmm
elseifdef __P686__
.686
elseifdef __P586__
.586
else
.486
endif
ifdef _AMD64
.x64
endif
.model	flat, __Ctype
SIZE_T	typedef dword
endif

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t typedef word
endif

ifndef _WCTYPE_T_DEFINED
define _WCTYPE_T_DEFINED
wint_t typedef wchar_t
wctype_t typedef wchar_t
endif

ifndef _TCHAR_DEFINED
define _TCHAR_DEFINED
ifdef _UNICODE
TCHAR	typedef wchar_t
PTCHAR	typedef ptr wchar_t
PTBYTE	typedef ptr wchar_t
LPTSTR	typedef ptr wchar_t
else
TCHAR	typedef sbyte
PTCHAR	typedef ptr sbyte
LPTSTR	typedef ptr sbyte
PTBYTE	typedef ptr byte
endif
endif

ifndef _ERRNO_T_DEFINED
define _ERRNO_T_DEFINED
errno_t typedef sdword
endif

; the following should be set depending on the sizes of various types

ifndef LONGDOUBLE_IS_DOUBLE
define LONGDOUBLE_IS_DOUBLE 0
if defined(__UNIX__) and defined(_WIN64)
define LONG_IS_INT     0
else
define LONG_IS_INT     1
endif
define SHORT_IS_INT    0
ifdef _WIN64
define PTR_IS_INT      0
ifdef __UNIX__
define PTR_IS_LONG     1
else
define PTR_IS_LONG     0
endif
else
define PTR_IS_INT      1
define PTR_IS_LONG     1
endif
endif

ptr_t		typedef ptr
char_t		typedef sbyte
uchar_t		typedef byte
if SHORT_IS_INT
short_t		typedef sdword
ushort_t	typedef dword
else
short_t		typedef sword
ushort_t	typedef word
endif
int_t		typedef sdword
uint_t		typedef dword
if LONG_IS_INT
long_t		typedef sdword
ulong_t		typedef dword
else
long_t		typedef sqword
ulong_t		typedef qword
endif

half_t		typedef real2
float_t		typedef real4
double_t	typedef real8
if LONGDOUBLE_IS_DOUBLE
ldouble_t	typedef real8
else
ldouble_t	typedef real10
endif
qfloat_t	typedef real16

string_t	typedef ptr sbyte
ustring_t	typedef ptr byte
wstring_t	typedef ptr word

int8_t		typedef sbyte
int16_t		typedef sword
int32_t		typedef sdword
int64_t		typedef sqword
int128_t	typedef soword

uint8_t		typedef byte
uint16_t	typedef word
uint32_t	typedef dword
uint64_t	typedef qword
uint128_t	typedef oword

ifdef __DEBUG__
.template array_type
    base string_t ?
    argv string_t 7 dup(?)
   .ends
.template warray_type
    base wstring_t ?
    argv wstring_t 7 dup(?)
   .ends
array_t		typedef ptr array_type
warray_t	typedef ptr warray_type
else
array_t		typedef ptr ptr sbyte
warray_t	typedef ptr ptr word
endif
ifdef _UNICODE
tchar_t		typedef word
tarray_t	typedef warray_t
tstring_t	typedef ptr word
else
tchar_t		typedef sbyte
tarray_t	typedef array_t
tstring_t	typedef ptr sbyte
endif

ifndef _INTPTR_T_DEFINED
define _INTPTR_T_DEFINED
ifdef _WIN64
intptr_t	typedef sqword
else
intptr_t	typedef sdword
endif
endif

SINT		typedef sdword
UINT		typedef dword
ULONG		typedef dword
PVOID		typedef ptr
HANDLE		typedef ptr
LPSTR		typedef ptr sbyte
LPWSTR		typedef ptr wchar_t
LPBYTE		typedef ptr byte
LPWORD		typedef ptr word
LPDWORD		typedef ptr dword
LPQWORD		typedef ptr qword

define TRUE	1
define FALSE	0
define NULL	0

size_t typedef SIZE_T

bool	typedef sdword
define	true	1
define	false	0
define	nullptr 0

ifndef _REGS6432
define _REGS6432
ifndef _WIN64
define rax <eax>
define rdx <edx>
define rbx <ebx>
define rcx <ecx>
define rdi <edi>
define rsi <esi>
define rbp <ebp>
define rsp <esp>
endif
endif

ifndef UNREFERENCED_PARAMETER
define DBG_UNREFERENCED_PARAMETER <UNREFERENCED_PARAMETER>
define DBG_UNREFERENCED_LOCAL_VARIABLE <UNREFERENCED_PARAMETER>
UNREFERENCED_PARAMETER macro P
if defined(__DEBUG__) and defined(_WIN64)
    exitm<lea rax,P>
else
    exitm<>
endif
    endm
endif

ifndef _CALLBACK_DEFINED
define _CALLBACK_DEFINED
CALLBACKC macro id, arguments:VARARG
    ?&id& typedef proto __cdecl &arguments
    exitm <id typedef ptr ?&id&>
    endm
CALLBACK macro id, arguments:VARARG
ifdef _WIN64
    ?&id& typedef proto &arguments
else
    ?&id& typedef proto WINAPI &arguments
endif
    exitm <id typedef ptr ?&id&>
    endm
endif
endif
.pragma list(pop)

