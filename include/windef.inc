ifndef _WINDEF_
define _WINDEF_
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
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

ifndef WINVER
WINVER equ 0x0500
endif

ifndef BASETYPES
define BASETYPES
ULONG		typedef dword
PULONG		typedef ptr ULONG
USHORT		typedef word
PUSHORT		typedef ptr USHORT
UCHAR		typedef byte
PUCHAR		typedef ptr UCHAR
PSZ		typedef ptr sbyte
endif

MAX_PATH	equ 260

ifndef NULL
NULL		equ 0
endif
ifndef FALSE
FALSE		equ 0
endif
ifndef TRUE
TRUE		equ 1
endif
ifndef OPTIONAL
OPTIONAL	equ <>
endif

if 0
if (not defined(_MAC)) and ((_MSC_VER ge 800) or defined(_STDCALL_SUPPORTED))
pascal equ <__stdcall>
else
pascal equ <>
endif
endif

if defined(DOSWIN32) or defined(_MAC)
cdecl	equ <_cdecl>
ifndef CDECL
CDECL	equ <_cdecl>
endif
else
cdecl	equ <>
ifndef CDECL
CDECL	equ <>
endif
endif

ifdef _MAC
;CALLBACK	equ <PASCAL>
;WINAPI		equ <CDECL>
WINAPIV		equ <CDECL>
APIENTRY	equ <WINAPI>
APIPRIVATE	equ <CDECL>
ifdef _68K_
;PASCAL		equ <__pascal>
else
;PASCAL		equ <>
endif
elseif (_MSC_VER ge 800) or defined(_STDCALL_SUPPORTED)
;CALLBACK	equ <stdcall>
;WINAPI		equ <stdcall>
WINAPIV		equ <c>
APIENTRY	equ <WINAPI>
APIPRIVATE	equ <stdcall>
;PASCAL		equ <stdcall>
else
;CALLBACK	equ <>
;WINAPI		equ <>
WINAPIV		equ <>
APIENTRY	equ <WINAPI>
APIPRIVATE	equ <>
;PASCAL		equ <pascal>
endif

ifdef _M_CEE_PURE
WINAPI_INLINE	equ <__clrcall>
else
WINAPI_INLINE	equ <WINAPI>
endif

BOOL		typedef sdword
FLOAT		typedef REAL4
PFLOAT		typedef ptr FLOAT
PBOOL		typedef ptr BOOL
LPBOOL		typedef ptr BOOL
PBYTE		typedef ptr BYTE
LPBYTE		typedef ptr BYTE
PINT		typedef ptr SINT
LPINT		typedef ptr SINT
PWORD		typedef ptr WORD
LPWORD		typedef ptr WORD
LPLONG		typedef ptr SDWORD
PDWORD		typedef ptr DWORD
LPDWORD		typedef ptr DWORD
LPVOID		typedef ptr
LPCVOID		typedef ptr

UINT		typedef dword
PUINT		typedef ptr dword

ifndef _WINNT_ ; NT_INCLUDED
include winnt.inc
endif

;include specstrings.inc

WPARAM		typedef UINT_PTR
LPARAM		typedef LONG_PTR
LRESULT		typedef LONG_PTR

ifndef inl_loadargs_2
inl_loadargs_2 macro a, b, t1, t2, r1, r2
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

inl_loadtypes_2 macro a, b, t1, t2
    t1 textequ typeid(a)
    t2 textequ typeid(b)
    ifidn t1,<imm>
     ifidn t2,<imm>
	exitm<1>
     endif
    endif
    exitm<0>
    endm
endif

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
%	ifdif <reg>,<eax>
	if ( typeof(reg) eq 8 )
	movsxd	reg,eax
	else
	mov	reg,eax
	endif
	endif
	retm	<reg>
	endm
endif

ifndef LOWORD
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
endif

ifndef HIWORD
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
endif

ifndef LOBYTE
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
endif

ifndef HIBYTE
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
endif

ifndef DECLARE_HANDLE
DECLARE_HANDLE macro name
	exitm<name typedef ptr>
	endm
endif

ifndef WIN_INTERNAL
DECLARE_HANDLE(HWND)
DECLARE_HANDLE(HHOOK)
ifdef WINABLE
DECLARE_HANDLE(HEVENT)
endif
endif

ATOM		typedef WORD

SPHANDLE	typedef PTR HANDLE
LPHANDLE	typedef PTR HANDLE
HGLOBAL		typedef HANDLE
HLOCAL		typedef HANDLE
GLOBALHANDLE	typedef HANDLE
LOCALHANDLE	typedef HANDLE

WPROC_T		typedef PROTO WINAPI
FARPROC		typedef PTR WPROC_T
NEARPROC	typedef PTR WPROC_T

ifndef GDI_INTERNAL
ifdef STRICT
HGDIOBJ		typedef ptr
else
HGDIOBJ		typedef HANDLE
endif
endif

ifndef WIN_INTERNAL
HACCEL		typedef HANDLE
endif
ifndef GDI_INTERNAL
HBITMAP		typedef HANDLE
HBRUSH		typedef HANDLE
endif
if WINVER GE 0x0400
HCOLORSPACE	typedef HANDLE
endif
ifndef GDI_INTERNAL
HDC		typedef HANDLE
endif
HGLRC		typedef HANDLE
HDESK		typedef HANDLE
HENHMETAFILE	typedef HANDLE
ifndef GDI_INTERNAL
HFONT		typedef HANDLE
endif
HICON		typedef HANDLE
ifndef WIN_INTERNAL
HMENU		typedef HANDLE
endif
HMETAFILE	typedef HANDLE
HINSTANCE	typedef HANDLE
HMODULE		typedef HINSTANCE	; HMODULEs can be used in place of HINSTANCEs
ifndef GDI_INTERNAL
HPALETTE	typedef HANDLE
HPEN		typedef HANDLE
endif
HRGN		typedef HANDLE
HRSRC		typedef HANDLE
HSTR		typedef HANDLE
HTASK		typedef HANDLE
HWINSTA		typedef HANDLE
HKL		typedef HANDLE
if WINVER GE 0x0500
HMONITOR	typedef HANDLE
HTERMINAL	typedef HANDLE
HWINEVENTHOOK	typedef HANDLE
endif

HFILE		typedef SINT
HCURSOR		typedef HICON ; HICONs & HCURSORs are polymorphic
COLORREF	typedef DWORD
LPCOLORREF	typedef PTR DWORD

HFILE_ERROR	equ -1

ifdef _WIN64

.template RECT

    left    SINT ?
    top	    SINT ?
    right   SINT ?
    bottom  SINT ?

    .inline RECT :vararg {
	ifidn typeid(this),<RECT>
	    this.Init_RECT(_1)
	else
	    [rcx].RECT.typeid(RECT_, this)(_1)
	endif
	}
    .inline RECT_imm :vararg {
      local rc
       .new rc:RECT
	rc.InitRECT(_1)
	lea rax,rc
	}

    .inline Init :vararg {
	ifidn typeid(this),<RECT>
	    this.Init_RECT(_1)
	else
	    [rcx].RECT.typeid(Init_, this)(_1)
	endif
	}

    .inline Init_RECT :abs, :abs, :abs, :abs, :vararg {
	ifnb <_1>
	    mov this.left,    _1
	endif
	ifnb <_2>
	    mov this.top,     _2
	endif
	ifnb <_3>
	    mov this.right,   _3
	endif
	ifnb <_4>
	    mov this.bottom,  _4
	endif
	}

    .inline Init_dword :abs, :abs, :abs, :abs {
	ifnb <_1>
	    mov [this].RECT.left,    _1
	endif
	ifnb <_2>
	    mov [this].RECT.top,     _2
	endif
	ifnb <_3>
	    mov [this].RECT.right,   _3
	endif
	ifnb <_4>
	    mov [this].RECT.bottom,  _4
	endif
	}

    .inline Init_ptrRECT :abs, :abs, :abs, :abs {
	[rcx].RECT.Init_qword(_1, _2, _3, _4)
	}

    .inline Width :abs=<eax> {
	ifidn typeid(this),<RECT>
	    mov _1,this.right
	    sub _1,this.left
	else
	    mov _1,[this].RECT.right
	    sub _1,[this].RECT.left
	endif
	}

    .inline Height :abs=<eax> {
	ifidn typeid(this),<RECT>
	    mov _1,this.bottom
	    sub _1,this.top
	else
	    mov _1,[this].RECT.bottom
	    sub _1,[this].RECT.top
	endif
	}

    .inline GetClient :HWND {
	xchg rcx,rdx
	GetClientRect(rcx, rdx)
	}

    .inline Clear {
	xor eax,eax
	mov [this],rax
	mov [this+8],rax
	}
    .ends

else

RECT		STRUC
left		sdword ?
top		sdword ?
right		sdword ?
bottom		sdword ?
RECT		ENDS

endif

PRECT		typedef ptr RECT
NPRECT		typedef ptr RECT
LPRECT		typedef ptr RECT
LPCRECT		typedef ptr RECT
RECTL		typedef RECT
PRECTL		typedef ptr RECT
LPRECTL		typedef ptr RECT
LPCRECTL	typedef ptr RECTL

POINT		STRUC
x		sdword ?
y		sdword ?
POINT		ENDS

PPOINT		typedef ptr POINT
NPPOINT		typedef ptr POINT
LPPOINT		typedef ptr POINT

POINTL		typedef POINT
PPOINTL		typedef ptr POINT

SIZE		STRUC
_cx		sdword ?
cy		sdword ?
SIZE		ENDS

tagSIZE		typedef SIZE
PSIZE		typedef ptr SIZE
LPSIZE		typedef ptr SIZE

SIZEL		typedef SIZE
PSIZEL		typedef ptr SIZE
LPSIZEL		typedef ptr SIZE

POINTS		STRUC
x		sword ?
y		sword ?
POINTS		ENDS

PPOINTS		typedef ptr POINTS
LPPOINTS	typedef ptr POINTS

DM_UPDATE	    equ 1
DM_COPY		    equ 2
DM_PROMPT	    equ 4
DM_MODIFY	    equ 8

DM_IN_BUFFER	    equ DM_MODIFY
DM_IN_PROMPT	    equ DM_PROMPT
DM_OUT_BUFFER	    equ DM_COPY
DM_OUT_DEFAULT	    equ DM_UPDATE

DC_FIELDS	    equ 1
DC_PAPERS	    equ 2
DC_PAPERSIZE	    equ 3
DC_MINEXTENT	    equ 4
DC_MAXEXTENT	    equ 5
DC_BINS		    equ 6
DC_DUPLEX	    equ 7
DC_SIZE		    equ 8
DC_EXTRA	    equ 9
DC_VERSION	    equ 10
DC_DRIVER	    equ 11
DC_BINNAMES	    equ 12
DC_ENUMRESOLUTIONS  equ 13
DC_FILEDEPENDENCIES equ 14
DC_TRUETYPE	    equ 15
DC_PAPERNAMES	    equ 16
DC_ORIENTATION	    equ 17
DC_COPIES	    equ 18

.pragma list(pop)
endif

