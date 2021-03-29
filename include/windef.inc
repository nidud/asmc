ifndef _WINDEF_
_WINDEF_ equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
ifndef NO_STRICT
ifndef STRICT
STRICT equ 1
endif
endif

ifdef _MAC
ifndef _WIN32
_WIN32 equ <>
endif
endif

ifndef WIN32
WIN32 equ <>
endif

ifndef WINVER
WINVER equ 0x0500
endif

ifndef BASETYPES
BASETYPES	equ 1
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

ifndef NOMINMAX
NOMINMAX equ <>
if 0
ifndef	max
max	macro a, b
	if a GT b
	  exitm <a>
	endif
	exitm <b>
	endm
endif
ifndef	min
min	macro a, b
	if a LT b
	  exitm <a>
	endif
	exitm <b>
	endm
endif
endif
endif

MAKEWORD macro a, b
     exitm<((a AND 0xff) OR ((b AND 0xff) SHL 8))>
     endm
MAKELONG macro a, b
     exitm<((a AND 0xffff) OR ((b AND 0xffff) SHL 16))>
     endm
LOWORD macro l
     exitm<(l AND 0xffff)>
     endm
HIWORD macro l
     exitm<((l SHR 16) AND 0xffff)>
     endm
LOBYTE macro w
     exitm<(w AND 0xff)>
     endm
HIBYTE macro w
     exitm<((w SHR 8) AND 0xff)>
     endm

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
	    this.InitRECT(_1)
	else
	    [rcx].RECT.typeid(RECT, this)(_1)
	endif
	}
    .inline RECTIMM32 :vararg {
      local rc
       .new rc:RECT
	rc.InitRECT(_1)
	lea rax,rc
	}

    .inline Init :vararg {
	ifidn typeid(this),<RECT>
	    this.InitRECT(_1)
	else
	    [rcx].RECT.typeid(Init, this)(_1)
	endif
	}

    .inline InitRECT :abs, :abs, :abs, :abs, :vararg {
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

    .inline InitREG64 :abs, :abs, :abs, :abs {
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

    .inline InitPRECT :abs, :abs, :abs, :abs {
	[rcx].RECT.InitREG64(_1, _2, _3, _4)
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

tagSIZE		typedef POINT
PSIZE		typedef ptr POINT
LPSIZE		typedef ptr POINT

SIZEL		typedef POINT
PSIZEL		typedef ptr POINT
LPSIZEL		typedef ptr POINT

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
