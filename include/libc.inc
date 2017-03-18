ifndef __LIBC_INC
;
; Master include file for the Asmc RTL library.
;
.xlist
__LIBC_INC	equ 223	 ;; Asmc Version 2.23
__STDC__	equ 1

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

ifdef _WIN64
option	win64:3 ; Standard stack frame
 ifdef __PE__	; For Asmc -pe
	.x64
	.model	flat, fastcall
 endif
_CDecl	equ <>	; fastcall
_CType	equ <>	; fastcall
else
	.486
if defined(_MSVCRT) or defined(__PE__)
	.model	flat, c
else
	.model	flat, stdcall
endif
ifdef __SSE__
	.686
	.XMM
endif
_CDecl	equ <c>
_CType	equ <stdcall>
endif

ifndef _WIN32
_WIN32	equ <>
endif

ifdef _WIN64
_IA64_	equ <>
_M_IA64 equ <>
SIZE_T	typedef QWORD
else
_X86_	equ <>
_M_IX86 equ 300
SIZE_T	typedef DWORD
endif

ifndef _WCHAR_T_DEFINED
wchar_t		typedef WORD
_WCHAR_T_DEFINED equ 1
endif

ifndef _WCTYPE_T_DEFINED
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
_WCTYPE_T_DEFINED equ 1
endif

ifndef _TCHAR_DEFINED
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
_TCHAR_DEFINED	equ 1
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
ifdef DEBUG
assert_exit	proto
.assert:	on
endif	;; DEBUG

.list
endif	;; __LIBC_INC
