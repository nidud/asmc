ifndef _MINWINDEF_
_MINWINDEF_ equ <>

include specstrings.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef NO_STRICT
ifndef STRICT
STRICT equ 1
endif
endif

ifdef _MAC
ifndef _WIN32
_WIN32 equ 1
endif
endif

ifndef WIN32
WIN32  equ 1
endif

ifndef BASETYPES
BASETYPES equ <>
ULONG	typedef dword
PULONG	typedef ptr dword
USHORT	typedef word
PUSHORT typedef ptr word
UCHAR	typedef byte
PUCHAR	typedef ptr byte
PSZ	typedef ptr sbyte
endif

MAX_PATH equ 260

ifndef NULL
NULL	equ 0
endif
ifndef FALSE
FALSE	equ 0
endif
ifndef TRUE
TRUE	equ 1
endif

BOOL	typedef sdword
FLOAT	typedef real4
PFLOAT	typedef ptr FLOAT
PBOOL	typedef ptr BOOL
LPBOOL	typedef ptr BOOL
PBYTE	typedef ptr BYTE
LPBYTE	typedef ptr BYTE
PINT	typedef ptr SDWORD
LPINT	typedef ptr SDWORD
PWORD	typedef ptr WORD
LPWORD	typedef ptr WORD
LPLONG	typedef ptr SDWORD
PDWORD	typedef ptr DWORD
LPDWORD typedef ptr DWORD
LPVOID	typedef ptr
LPCVOID typedef ptr
UINT	typedef DWORD
PUINT	typedef ptr DWORD

ifndef _WINNT_
include winnt.inc
endif

WPARAM	typedef UINT_PTR
LPARAM	typedef LONG_PTR
LRESULT typedef LONG_PTR

ifndef NOMINMAX
ifndef max
max macro a, b
%   exitm<typeid(max, a)typeid(b)(a, b)>
    endm
maxIMM32IMM32 macro a,b
    if (a) GT (b)
	exitm<a>
    endif
    exitm<b>
    endm
endif
ifndef min
min macro a, b
%   exitm<typeid(min, a)typeid(b)(a, b)>
    endm
minIMM32IMMi32 macro a, b
    if (a) LT (b)
	exitm<a>
    endif
    exitm<b>
    endm
endif
endif  ;; NOMINMAX

MAKEWORD macro a, b
    exitm<(((a) AND 0xff) OR (((b) AND 0xff) SHL 8))>
    endm
MAKELONG macro a, b
    exitm<(((a) AND 0xffff) OR (((b) AND 0xffff) SHL 16))>
    endm
LOWORD macro l
    exitm<((((l)) AND 0xffff))>
    endm
HIWORD macro l
    exitm<(((((l)) SHR 16) AND 0xffff))>
    endm
LOBYTE macro w
    exitm<((((w)) AND 0xff))>
    endm
HIBYTE macro w
    exitm<(((((w)) SHR 8) AND 0xff))>
    endm

SPHANDLE	typedef ptr HANDLE
LPHANDLE	typedef ptr HANDLE
HGLOBAL		typedef HANDLE
HLOCAL		typedef HANDLE
GLOBALHANDLE	typedef HANDLE
LOCALHANDLE	typedef HANDLE

ifdef _MANAGED
DECLARE_HANDLE(HKEY)
PHKEY typedef ptr HKEY
DECLARE_HANDLE(HMETAFILE)
DECLARE_HANDLE(HINSTANCE)
HMODULE typedef HINSTANCE
DECLARE_HANDLE(HRGN)
DECLARE_HANDLE(HRSRC)
DECLARE_HANDLE(HSPRITE)
DECLARE_HANDLE(HLSURF)
DECLARE_HANDLE(HSTR)
DECLARE_HANDLE(HTASK)
DECLARE_HANDLE(HWINSTA)
DECLARE_HANDLE(HKL)
endif

ifndef _MAC
HFILE typedef SDWORD
else
HFILE typedef SWORD
endif

ifndef _FILETIME_
_FILETIME_ equ <>
FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
PFILETIME	typedef ptr FILETIME
LPFILETIME	typedef ptr FILETIME
endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif ;; _MINWINDEF_
