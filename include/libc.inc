.pragma list(push, 0)
ifndef __LIBC_INC
;
; Master include file for the Asmc RTL library.
;
__LIBC_INC	equ 1
__STDC__	equ 1
__LIBC__	equ 232
ifdef __ASMC__
if ( __ASMC__ LT __LIBC__ )
  .err <incorrect version. Use the header that matches with the Asmc Assembler.>
endif
endif
;;
;; Architecture kinds:
;;     _WIN64 (#define symbols)
;;     _X86_
;;     _AMD64_
;;     _IA64_
;;
;; Machine Architectures:
;;     _M_IX86
;;     _M_AMD64
;;     _M_IA64
;;
ifdef _WIN64
_IA64_		equ <>
_M_X64		equ 100
_M_IA64		equ <>
elseifdef _AMD64
_AMD64_		equ <>
_M_AMD64	equ 100
else
_X86_		equ <>
_M_IX86		equ 600
endif

ifdef _LINUX
_CType	equ <syscall>
_CDecl	equ <syscall>
__cdecl equ <syscall>
elseifdef _STDCALL_SUPPORTED
_CDecl	equ <c>
_CType	equ <stdcall>
__cdecl equ <stdcall>
WINAPI	equ <stdcall>
endif

ifdef __PE__	; asmc /pe
ifndef _MSVCRT	; msvcrt.lib
_MSVCRT equ <>
endif
endif

ifndef _CDecl	; vararg (...) type
ifdef _WIN64
_CDecl equ <fastcall>
else
_CDecl equ <c>
endif
endif

ifndef __cdecl	; libc/msvcrt types
ifdef _WIN64
__cdecl equ <fastcall>
else
__cdecl equ <c>
endif
endif

ifndef _CType	; default (user) type
ifdef _WIN64
_CType equ <fastcall>
else
_CType equ <c>
endif
endif
;
; Set Windows version
;
include sdkddkver.inc

ifndef _MSC_VER
;;
;; _MSC_VER Defined as an integer literal that encodes the major and minor number
;; elements of the compiler's version number. The major number is the first
;; element of the period-delimited version number and the minor number is the
;; second element. For example, if the version number of the Visual C++ compiler
;; is 17.00.51106.1, the _MSC_VER macro evaluates to 1700. Enter cl /? at the
;; command line to view the compiler's version number. This macro is always defined.
;;
_MSC_VER	equ 1200 ;; Visual C++ version 12.0
endif

ifndef _MSC_FULL_VER
;;
;; _MSC_FULL_VER Defined as an integer literal that encodes the major, minor,
;; and build number elements of the compiler's version number. The major number
;; is the first element of the period-delimited version number, the minor number
;; is the second element, and the build number is the third element. For example,
;; if the version number of the Visual C++ compiler is 15.00.20706.01, the
;; _MSC_FULL_VER macro evaluates to 150020706. Enter cl /? at the command line
;; to view the compiler's version number. This macro is always defined.
;;
_MSC_FULL_VER	equ 120000000 ;; Visual C++ version 12.0
endif

ifndef _WIN32
_WIN32		equ <>	; default
endif

ifdef _WIN64
ifdef __PE__
if not (@cpu eq 0x0D5F) ; case -pe -win64
	.x64
	.model	flat, _CType
endif
endif
option	win64:3
option	frame:auto
SIZE_T	typedef QWORD
else
ifdef __AVX__
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
_WCHAR_T_DEFINED equ <>
wchar_t		typedef word
endif

ifndef _WCTYPE_T_DEFINED
_WCTYPE_T_DEFINED equ <>
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
endif

ifndef _TCHAR_DEFINED
_TCHAR_DEFINED	equ <>
ifdef _UNICODE
TCHAR		typedef wchar_t
PTCHAR		typedef ptr wchar_t
PTBYTE		typedef ptr wchar_t
LPTSTR		typedef ptr wchar_t
else
TCHAR		typedef sbyte
PTCHAR		typedef ptr sbyte
LPTSTR		typedef ptr sbyte
PTBYTE		typedef ptr byte
endif
endif

ifdef _WIN64
__fastcall	equ <fastcall>
else
__fastcall	equ <watcall>
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

uint8_t		typedef byte
uint16_t	typedef word
uint32_t	typedef dword
uint64_t	typedef qword

ifdef DEBUG
.template array_type
    base string_t ?
    argv string_t 7 dup(?)
.ends
.template warray_type
    base	wstring_t ?
    argv	wstring_t 7 dup(?)
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

TRUE		equ 1
FALSE		equ 0
NULL		equ 0

option		casemap:none
size_t		typedef SIZE_T
assert_exit	proto

ifndef _CALLBACK_DEFINED
_CALLBACK_DEFINED equ <>
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
.pragma list(pop)

