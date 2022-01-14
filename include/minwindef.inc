ifndef _MINWINDEF_
define _MINWINDEF_

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
define BASETYPES
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
define max_imm_dword   <max_sdword_sdword>
define max_imm_sdword  <max_sdword_sdword>
define max_dword_imm   <max_sdword_imm>
define max_dword_dword <max_sdword_sdword>
max_imm_imm macro a,b
if (a) GT (b)
	exitm<a>
endif
    exitm<b>
    endm
max_sdword_imm proto watcall a:sdword, b:abs {
    .ifs a < b
	mov a,b
    .endif
    }
max_sdword_sdword proto watcall a:sdword, b:abs {
    cmp	  a,b
    cmovl a,b
    }
max macro a, b
%   exitm<typeid(max_, a)typeid(_, b)(a, b)>
    endm
endif
ifndef min
define min_imm_dword   <min_sdword_sdword>
define min_imm_sdword  <min_sdword_sdword>
define min_dword_imm   <min_sdword_imm>
define min_dword_dword <min_sdword_sdword>
min_imm_imm macro a, b
if (a) LT (b)
    exitm<a>
endif
    exitm<b>
    endm
min_sdword_imm proto watcall a:sdword, b:abs {
    .ifs a > b
	mov a,b
    .endif
    }
min_sdword_sdword proto watcall a:sdword, b:abs {
    cmp	  a,b
    cmovg a,b
    }
min macro a, b
%   exitm<typeid(min_, a)typeid(_, b)(a, b)>
    endm
endif
endif ; NOMINMAX

ifndef MAKEWORD
define MAKEWORD_imm_dword     <MAKEWORD_dword_dword>
define MAKEWORD_imm_sdword    <MAKEWORD_dword_dword>
define MAKEWORD_dword_imm     <MAKEWORD_dword_dword>
define MAKEWORD_sdword_imm    <MAKEWORD_dword_dword>
define MAKEWORD_sdword_sdword <MAKEWORD_dword_dword>
MAKEWORD_imm_imm macro a, b
    exitm<(((a) AND 0xff) OR (((b) AND 0xff) SHL 8))>
    endm
MAKEWORD_dword_dword proto watcall a:dword, b:dword {
    mov ah,dl
    retm<ax>
    }
MAKEWORD macro a, b
%   exitm<typeid(MAKEWORD_, a)typeid(_, b)(a, b)>
    endm
endif

ifndef MAKELONG
define MAKELONG_imm_dword     <MAKELONG_dword_dword>
define MAKELONG_imm_sdword    <MAKELONG_dword_dword>
define MAKELONG_dword_imm     <MAKELONG_dword_dword>
define MAKELONG_sdword_imm    <MAKELONG_dword_dword>
define MAKELONG_sdword_sdword <MAKELONG_dword_dword>
MAKELONG_imm_imm macro a, b
    exitm<(((a) AND 0xffff) OR (((b) AND 0xffff) SHL 16))>
    endm
MAKELONG_dword_dword proto watcall a:dword, b:dword {
    xchg eax,edx
    shld eax,edx,16
    }
MAKELONG macro a, b
%   exitm<typeid(MAKELONG_, a)typeid(_, b)(a, b)>
    endm
endif

ifndef LOWORD
define LOWORD_sdword <LOWORD_dword>
LOWORD_imm macro l
    exitm<((((l)) AND 0xffff))>
    endm
LOWORD_dword proto watcall a:dword {
    movzx eax,ax
    retm<ax>
    }
LOWORD macro a, b
%   exitm<typeid(LOWORD_, a)(a)>
    endm
endif

ifndef HIWORD
define HIWORD_sdword <HIWORD_dword>
HIWORD_imm macro l
    exitm<(((((l)) SHR 16) AND 0xffff))>
    endm
HIWORD_dword proto watcall a:dword {
    shr eax,16
    retm<ax>
    }
HIWORD macro a, b
%   exitm<typeid(HIWORD_, a)(a)>
    endm
endif

ifndef LOBYTE
define LOBYTE_sdword <LOBYTE_dword>
LOBYTE_imm macro w
    exitm<((((w)) AND 0xff))>
    endm
LOBYTE_dword proto watcall a:dword {
    movzx eax,al
    retm<al>
    }
LOBYTE macro a, b
%   exitm<typeid(LOBYTE_, a)(a)>
    endm
endif

ifndef HIBYTE
define HIBYTE_sdword <HIBYTE_dword>
HIBYTE_imm macro w
    exitm<(((((w)) SHR 8) AND 0xff))>
    endm
HIBYTE_dword proto watcall a:dword {
    movzx eax,ah
    retm<al>
    }
HIBYTE macro a, b
%   exitm<typeid(HIBYTE_, a)(a)>
    endm
endif

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
define _FILETIME_
FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
PFILETIME	typedef ptr FILETIME
LPFILETIME	typedef ptr FILETIME
endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif ;; _MINWINDEF_
