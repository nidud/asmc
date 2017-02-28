;
; Master include file for the Asmc RTL library.
;
.xlist
ifndef __LIBC_INC
__LIBC_INC equ 1

;
; Version management functions, types, and definitions
;

TRUE	equ 1
FALSE	equ 0
NULL	equ 0

defined macro x
	ifdef x
	    exitm<1>
	else
	    exitm<0>
	endif
	endm

;;
;; _WIN32_WINNT version constants
;;
_WIN32_WINNT_NT4		equ 0x0400 ;; Windows NT 4.0
_WIN32_WINNT_WIN2K		equ 0x0500 ;; Windows 2000
_WIN32_WINNT_WINXP		equ 0x0501 ;; Windows XP
_WIN32_WINNT_WS03		equ 0x0502 ;; Windows Server 2003
_WIN32_WINNT_WIN6		equ 0x0600 ;; Windows Vista
_WIN32_WINNT_VISTA		equ 0x0600 ;; Windows Vista
_WIN32_WINNT_WS08		equ 0x0600 ;; Windows Server 2008
_WIN32_WINNT_LONGHORN		equ 0x0600 ;; Windows Vista
_WIN32_WINNT_WIN7		equ 0x0601 ;; Windows 7
_WIN32_WINNT_WIN8		equ 0x0602 ;; Windows 8
_WIN32_WINNT_WINBLUE		equ 0x0603 ;; Windows 8.1
_WIN32_WINNT_WINTHRESHOLD	equ 0x0A00 ;; Windows 10
_WIN32_WINNT_WIN10		equ 0x0A00 ;; Windows 10

ifndef WINVER
ifdef _WIN95
WINVER equ _WIN32_WINNT_NT4
else
WINVER equ _WIN32_WINNT_WS03
endif
endif

ifndef _WIN32_WINNT
_WIN32_WINNT equ WINVER
endif
ifndef __STDC__
__STDC__  equ 1
endif

ifdef _WIN64
ifdef __PE__		; For Asmc -pe
	.x64
	.model	FLAT, FASTCALL
endif	; __PE__
	option	WIN64:3		; Standard stack frame

else	;; !_WIN64

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
_WIN32	equ 1
endif	;; _WIN32


ifndef _WCHAR_T_DEFINED
wchar_t		typedef WORD
_WCHAR_T_DEFINED equ 1
endif
ifndef _WCTYPE_T_DEFINED
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
_WCTYPE_T_DEFINED equ 1
endif

SINT		typedef sdword
UINT		typedef dword
ULONG		typedef dword

ifdef _WIN64
SIZE_T		typedef qword
else
SIZE_T		typedef dword
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

PVOID		typedef ptr
HANDLE		typedef ptr
LPSTR		typedef ptr sbyte
LPWSTR		typedef ptr wchar_t
;LPTSTR		typedef ptr TCHAR
LPBYTE		typedef ptr byte
LPWORD		typedef ptr word
LPDWORD		typedef ptr dword
LPQWORD		typedef ptr qword

option		casemap:none
size_t		typedef SIZE_T

ifdef _WIN64
_CType		equ <>	; fastcall
_CDecl		equ <>	; fastcall
else
_CType		equ <STDCALL>
_CDecl		equ <C>
endif


ifdef	DEBUG
	assert_exit proto
	.assert:on
endif	;; DEBUG

endif	;; __LIBC_INC
.list
