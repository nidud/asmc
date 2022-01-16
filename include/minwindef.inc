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
inl_maxmin macro a, b, x

  local ra,rb,ta,tb,signed

    if inl_loadtypes_2(a, b, ta, tb)
      if (a) &x&t (b)
	exitm<a>
      else
	exitm<b>
      endif
    endif
    inl_loadargs_2(a,b,ta,tb,ra,rb)
    cmp ra,rb
    if ( typeof(ra) lt 4 )
	ra textequ <eax>
	rb textequ <edx>
    endif
    ifidn @SubStr(%ta, 1, 1),<s>
	signed = 1
    elseifidn @SubStr(%tb, 1, 1),<s>
	signed = 1
    else
	signed = 0
    endif
    if signed
     ifidn <x>,<g>
	cmovl ra,rb
     else
	cmovg ra,rb
     endif
    else
     ifidn <x>,<g>
	cmovb ra,rb
     else
	cmova ra,rb
     endif
    endif
    retm<ra>
    endm
ifndef max
max macro a, b
%   retm<inl_maxmin(a, b, g)>
    endm
endif
ifndef min
min macro a, b
%   retm<inl_maxmin(a, b, l)>
    endm
endif
endif ; NOMINMAX

ifndef MAKEWORD
MAKEWORD macro a, b
	local ta,tb
	if inl_loadtypes_2(a, b, ta, tb)
	exitm<(((a) AND 0xff) OR (((b) AND 0xff) SHL 8))>
	endif
	inl_loadargs_2(a,b,ta,tb)
	mov	ah,dl
	retm	<ax>
	endm
endif

ifndef MAKELONG
MAKELONG macro a, b, reg:=<eax>
	local ta,tb
	ifidn typeid(a),<imm>
	ifidn typeid(b),<imm>
	exitm<(((a) AND 0xffff) OR (((b) AND 0xffff) SHL 16))>
	endif
	endif
	ta textequ <dword>
	tb textequ <dword>
	inl_loadargs_2(a,b,ta,tb)
	shl	eax,16
	shrd	eax,edx,16
	ifdif <eax>,<reg>
	mov	reg,eax
	endif
	retm	<reg>
	endm
endif

ifndef LOWORD
LOWORD_dword proto watcall l:dword {
	movzx	eax,ax
	retm	<ax>
	}
LOWORD macro l
	ifidn typeid(l),<imm>
	exitm<((l) AND 0xffff)>
	endif
	exitm<LOWORD_dword(l)>
	endm
endif

ifndef HIWORD
HIWORD_dword proto watcall l:dword {
	shr	eax,16
	retm	<ax>
	}
HIWORD macro l
	ifidn typeid(l),<imm>
	exitm<(((l) SHR 16) AND 0xffff)>
	endif
	exitm<HIWORD_dword(l)>
	endm
endif

ifndef LOBYTE
LOBYTE_dword proto watcall w:dword {
	movzx	eax,al
	retm	<al>
	}
LOBYTE macro w
	ifidn typeid(w),<imm>
	exitm<((w) AND 0xff)>
	endif
	exitm<LOBYTE_dword(w)>
	endm
endif

ifndef HIBYTE
HIBYTE_dword proto watcall w:dword {
	movzx	eax,ah
	retm	<al>
	}
HIBYTE macro w
	ifidn typeid(w),<imm>
	exitm<(((w) SHR 8) AND 0xff)>
	endif
	exitm<HIBYTE_dword(w)>
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
