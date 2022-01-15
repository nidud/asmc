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

cmovrmx macro a, b, x
    cmp a,b
    cmov&x& a,b
    retm<a>
    endm

min_imm_imm macro a, b
if (a) LT (b)
    exitm<a>
endif
    exitm<b>
    endm

max_imm_imm macro a,b
if (a) GT (b)
    exitm<a>
endif
    exitm<b>
    endm

min_byte_byte		proto watcall :byte,   :byte   { cmovrmx(_1, _2, a) }
min_word_word		proto watcall :word,   :word   { cmovrmx(_1, _2, a) }
min_dword_dword		proto watcall :dword,  :dword  { cmovrmx(_1, _2, a) }
min_qword_qword		proto watcall :qword,  :qword  { cmovrmx(_1, _2, a) }
min_sbyte_sbyte		proto watcall :sbyte,  :sbyte  { cmovrmx(_1, _2, g) }
min_sword_sword		proto watcall :sword,  :sword  { cmovrmx(_1, _2, g) }
min_sdword_sdword	proto watcall :sdword, :sdword { cmovrmx(_1, _2, g) }
min_sqword_sqword	proto watcall :sqword, :sqword { cmovrmx(_1, _2, g) }
min_real4_real4		proto fastcall :real4, :real4  { minss _1, _2 }
min_real8_real8		proto fastcall :real8, :real8  { minsd _1, _2 }

max_byte_byte		proto watcall :byte,   :byte   { cmovrmx(_1, _2, b) }
max_word_word		proto watcall :word,   :word   { cmovrmx(_1, _2, b) }
max_dword_dword		proto watcall :dword,  :dword  { cmovrmx(_1, _2, b) }
max_qword_qword		proto watcall :qword,  :qword  { cmovrmx(_1, _2, b) }
max_sbyte_sbyte		proto watcall :sbyte,  :sbyte  { cmovrmx(_1, _2, l) }
max_sword_sword		proto watcall :sword,  :sword  { cmovrmx(_1, _2, l) }
max_sdword_sdword	proto watcall :sdword, :sdword { cmovrmx(_1, _2, l) }
max_sqword_sqword	proto watcall :sqword, :sqword { cmovrmx(_1, _2, l) }
max_real4_real4		proto fastcall :real4, :real4  { maxss _1, _2 }
max_real8_real8		proto fastcall :real8, :real8  { maxsd _1, _2 }

min_byte_imm macro a, b
    exitm<max_byte_byte(b, a)>
    endm
min_word_imm macro a, b
    exitm<max_word_word(b, a)>
    endm
min_dword_imm macro a, b
    exitm<max_dword_dword(b, a)>
    endm
min_qword_imm macro a, b
    exitm<max_qword_qword(b, a)>
    endm
min_sbyte_imm macro a, b
    exitm<max_sbyte_sbyte(b, a)>
    endm
min_sword_imm macro a, b
    exitm<max_sword_sword(b, a)>
    endm
min_sdword_imm macro a, b
    exitm<max_sdword_sdword(b, a)>
    endm
min_sqword_imm macro a, b
    exitm<max_sqword_sqword(b, a)>
    endm
min_qword_dword macro a, b
    exitm<min_dword_dword(eax, b)>
    endm
min_qword_sdword macro a, b
    exitm<min_dword_sdword(eax, b)>
    endm

max_byte_imm macro a, b
    exitm<min_byte_byte(b, a)>
    endm
max_word_imm macro a, b
    exitm<min_word_word(b, a)>
    endm
max_dword_imm macro a, b
    exitm<min_dword_dword(b, a)>
    endm
max_qword_imm macro a, b
    exitm<min_qword_qword(b, a)>
    endm
max_sbyte_imm macro a, b
    exitm<min_sbyte_sbyte(b, a)>
    endm
max_sword_imm macro a, b
    exitm<min_sword_sword(b, a)>
    endm
max_sdword_imm macro a, b
    exitm<min_sdword_sdword(b, a)>
    endm
max_sqword_imm macro a, b
    exitm<min_sqword_sqword(b, a)>
    endm
max_qword_dword macro a, b
    exitm<max_dword_dword(eax, b)>
    endm
max_qword_sdword macro a, b
    exitm<max_dword_sdword(eax, b)>
    endm

define max_imm_byte	<max_byte_byte>
define max_imm_word	<max_word_word>
define max_imm_dword	<max_dword_dword>
define max_imm_qword	<max_qword_qword>
define max_imm_sbyte	<max_sbyte_sbyte>
define max_imm_sword	<max_sword_sword>
define max_imm_sdword	<max_sdword_sdword>
define max_imm_sqword	<max_sqword_sqword>

define min_imm_byte	<min_byte_byte>
define min_imm_word	<min_word_word>
define min_imm_dword	<min_dword_dword>
define min_imm_qword	<min_qword_qword>
define min_imm_sbyte	<min_sbyte_sbyte>
define min_imm_sword	<min_sword_sword>
define min_imm_sdword	<min_sdword_sdword>
define min_imm_sqword	<min_sqword_sqword>

ifndef max
max proto a:abs, b:abs {
%   exitm<typeid(max_, a)typeid(_, b)(a, b)>
    }
endif
ifndef min
min proto a:abs, b:abs {
%   exitm<typeid(min_, a)typeid(_, b)(a, b)>
    }
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
