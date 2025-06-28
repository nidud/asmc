ifndef _MINWINDEF_
define _MINWINDEF_

include specstrings.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef NO_STRICT
ifndef STRICT
define STRICT
endif
endif

ifdef _MAC
ifndef _WIN32
define _WIN32
endif
endif

ifndef WIN32
define WIN32
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

define MAX_PATH 260

ifndef NULL
define NULL 0
endif
ifndef FALSE
define FALSE 0
endif
ifndef TRUE
define TRUE 1
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
ifndef UINT
UINT	typedef DWORD
endif
PUINT	typedef ptr DWORD

ifndef _WINNT_
include winnt.inc
endif

WPARAM	typedef UINT_PTR
LPARAM	typedef LONG_PTR
LRESULT typedef LONG_PTR

LOADARGTYPEAX macro a
  local func,t
    t textequ typeid(a)
    ifidn t,<imm>
	t textequ <dword>
    elseifidn @SubStr(%t, 1, 3),<ptr>
	t textequ <ptr>
    elseifidn t,<near>
	t textequ <ptr>
    endif
    func proto watcall :t {}
    func(a)
    retm<rax>
    endm

LOADARGPTRAX macro a
  local func
    func proto watcall :ptr {}
    func(a)
    retm<rax>
    endm

LOADARGPTRDX macro a
  local func
    func proto fastcall :abs, :ptr {}
    func(0, a)
    retm<rdx>
    endm

LOADARGPTRCX macro a
  local func
    func proto fastcall :ptr {}
    func(a)
    retm<rcx>
    endm

LOADARGS_2 macro a, b, t1, t2, r1, r2
  local func
    ifidn t1,<imm>
	t1 textequ t2
    elseifidn t2,<imm>
	t2 textequ t1
    endif
    ifidn @SubStr(%t1, 1, 3),<ptr>
	t1 textequ t2
    elseifidn @SubStr(%t2, 1, 3),<ptr>
	t2 textequ t1
    endif
    ifidn t1,<near>
	t1 textequ t2
    elseifidn t2,<near>
	t2 textequ t1
    endif
    func proto watcall :t1, :t2 {
    ifnb <r1>
	r1 equ <_1>
	r2 equ <_2>
    endif
	}
    func(a, b)
    exitm<>
    endm

LOADTYPES_2 macro a, b, t1, t2
    t1 textequ typeid(a)
    t2 textequ typeid(b)
    ifidn t1,<imm>
     ifidn t2,<imm>
	exitm<1>
     endif
    endif
    exitm<0>
    endm


ifndef NOMINMAX

ifndef max
max macro a, b
  local reg, src
    if ( ( (OPATTR a) and 4 ) and ( (OPATTR b) and 4 ) )
    if (a) gt (b)
	exitm<a>
    else
	exitm<b>
    endif
    endif
    if ( (OPATTR a) and 4 )
	reg textequ @Reg(eax,TYPEOF(b))
    else
	reg textequ @Reg(eax,TYPEOF(a))
    endif
    ifdif reg,<a>
	mov reg,a
    endif
    cmp reg,b
    if ( (OPATTR b) and 4 )
	src textequ @Reg(edx,TYPEOF(a))
	mov edx,b
    else
	src textequ <b>
    endif
    if ( ( (OPATTR a) and 0x8000 ) or ( (OPATTR b) and 0x8000 ) )
	cmovl reg,src
    else
	cmovb reg,src
    endif
%   exitm<reg>
    endm
endif

ifndef min
min macro a, b
  local reg, src
    if ( ( (OPATTR a) and 4 ) and ( (OPATTR b) and 4 ) )
    if (a) lt (b)
	exitm<a>
    else
	exitm<b>
    endif
    endif
    if ( (OPATTR a) and 4 )
	reg textequ @Reg(eax,TYPEOF(b))
    else
	reg textequ @Reg(eax,TYPEOF(a))
    endif
    ifdif reg,<a>
	mov reg,a
    endif
    cmp reg,b
    if ( (OPATTR b) and 4 )
	src textequ @Reg(edx,TYPEOF(a))
	mov edx,b
    else
	src textequ <b>
    endif
    if ( ( (OPATTR a) and 0x8000 ) or ( (OPATTR b) and 0x8000 ) )
	cmovg reg,src
    else
	cmova reg,src
    endif
%   exitm<reg>
    endm
endif

endif ; NOMINMAX

ifndef MAKEWORD
MAKEWORD macro a, b
	local ta,tb
	if LOADTYPES_2(a, b, ta, tb)
	exitm<(((a) AND 0xff) OR (((b) AND 0xff) SHL 8))>
	endif
	LOADARGS_2(a,b,ta,tb)
	mov	ah,dl
	retm	<ax>
	endm
endif

MAKELONG macro a, b, reg:=<eax>
	local ta,tb
    if ( ( (OPATTR a) and 4 ) and ( (OPATTR b) and 4 ) )
	exitm<(((a) AND 0xffff) OR (((b) AND 0xffff) SHL 16))>
    endif
	ta textequ <dword>
	tb textequ <dword>
	LOADARGS_2(a,b,ta,tb)
	shl	eax,16
	shrd	eax,edx,16
%	ifdif <reg>,<eax>
	if ( TYPEOF(reg) eq 8 )
	movsxd	reg,eax
	else
	mov	reg,eax
	endif
	endif
	retm	<reg>
	endm

define LOWORD_sdword <LOWORD_dword>
define LOWORD_sqword <LOWORD_qword>
LOWORD_qword proto watcall l:qword {
	movsx	eax,ax
	retm	<ax>
	}
LOWORD_dword proto watcall l:dword {
	movsx	eax,ax
	retm	<ax>
	}
LOWORD macro l
	ifidn typeid(l),<imm>
	exitm<((l) AND 0xffff)>
	endif
%	exitm<typeid(LOWORD_,l)(l)>
	endm

define HIWORD_sdword <HIWORD_dword>
define HIWORD_sqword <HIWORD_qword>
HIWORD_qword proto watcall l:qword {
	sar	eax,16
	retm	<ax>
	}
HIWORD_dword proto watcall l:dword {
	sar	eax,16
	retm	<ax>
	}
HIWORD macro l
	ifidn typeid(l),<imm>
	exitm<(((l) SHR 16) AND 0xffff)>
	endif
%	exitm<typeid(HIWORD_,l)(l)>
	endm

define LOBYTE_sdword <LOBYTE_dword>
define LOBYTE_sqword <LOBYTE_qword>
LOBYTE_qword proto watcall w:qword {
	movsx	eax,al
	retm	<al>
	}
LOBYTE_dword proto watcall w:dword {
	movsx	eax,al
	retm	<al>
	}
LOBYTE macro w
	ifidn typeid(w),<imm>
	exitm<((w) AND 0xff)>
	endif
%	exitm<typeid(LOBYTE_,w)(w)>
	endm

define HIBYTE_sdword <HIBYTE_dword>
define HIBYTE_sqword <HIBYTE_qword>
HIBYTE_qword proto watcall w:qword {
	movsx	eax,ah
	retm	<al>
	}
HIBYTE_dword proto watcall w:dword {
	movsx	eax,ah
	retm	<al>
	}
HIBYTE macro w
	ifidn typeid(w),<imm>
	exitm<(((w) SHR 8) AND 0xff)>
	endif
%	exitm<typeid(HIBYTE_,w)(w)>
	endm

SPHANDLE	typedef ptr HANDLE
LPHANDLE	typedef ptr HANDLE
HGLOBAL		typedef HANDLE
HLOCAL		typedef HANDLE
GLOBALHANDLE	typedef HANDLE
LOCALHANDLE	typedef HANDLE

WPROC_T		typedef PROTO WINAPI
FARPROC		typedef PTR WPROC_T
NEARPROC	typedef PTR WPROC_T

ATOM		typedef WORD

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
