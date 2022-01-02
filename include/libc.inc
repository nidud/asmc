ifndef __LIBC_INC
define __LIBC_INC
;
; Master include file for the Asmc Run Time library.
;
define __STDC__
define __LIBC__ 232
ifdef __ASMC__
if ( __ASMC__ LT __LIBC__ )
.err <incorrect version. Use the header that matches with the Asmc Assembler.>
endif
endif
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
define _IA64_
define _M_X64 100
define _M_IA64
elseifdef _AMD64
define _AMD64_
define _M_AMD64 100
else
define _X86_
define _M_IX86 600
endif

ifdef _LINUX
define _CType  <syscall>
define _CDecl  <syscall>
define __cdecl <syscall>
elseifdef _STDCALL_SUPPORTED
define _CDecl  <c>
define _CType  <stdcall>
define __cdecl <stdcall>
define WINAPI  <stdcall>
endif

ifdef __PE__	; asmc /pe
ifndef _MSVCRT	; msvcrt.lib
define _MSVCRT
endif
endif

ifndef _CDecl	; vararg (...) type
ifdef _WIN64
define _CDecl <fastcall>
else
define _CDecl <c>
endif
endif

ifndef __cdecl	; libc/msvcrt types
ifdef _WIN64
define __cdecl <fastcall>
else
define __cdecl <c>
endif
endif

ifndef _CType	; default (user) type
ifdef _WIN64
define _CType <fastcall>
else
define _CType <c>
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
option	frame:auto
SIZE_T	typedef QWORD
else
ifdef __SSE__
.686
.xmm
else
.486
endif
ifdef _AMD64
.x64
endif
.model	flat, _CType
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

ptr_t		typedef ptr
char_t		typedef sbyte
short_t		typedef sword
int_t		typedef sdword
long_t		typedef sdword
uchar_t		typedef byte
ushort_t	typedef word
uint_t		typedef dword
ulong_t		typedef dword

string_t	typedef ptr sbyte
ustring_t	typedef ptr byte
wstring_t	typedef ptr word

int8_t		typedef sbyte
int16_t		typedef sword
int32_t		typedef sdword
int64_t		typedef sqword
int128_t	typedef oword

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

option casemap:none
size_t typedef SIZE_T
assert_exit proto

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
    ?&id& typedef proto WINAPI &arguments
    exitm <id typedef ptr ?&id&>
    endm
endif

endif
