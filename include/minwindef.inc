ifndef _MINWINDEF_
_MINWINDEF_ equ <>

include specstrings.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef NO_STRICT
ifndef STRICT
STRICT			equ 1
endif
endif

ifdef _MAC
ifndef _WIN32
_WIN32 equ 1
endif
endif

ifndef WIN32
WIN32 equ 1
endif

ifndef BASETYPES
BASETYPES equ <>
ULONG			typedef dword
PULONG			typedef ptr dword
USHORT			typedef word
PUSHORT			typedef ptr word
UCHAR			typedef byte
PUCHAR			typedef ptr byte
PSZ			typedef ptr sbyte
endif

MAX_PATH		equ 260

ifndef NULL
NULL			equ 0
endif

ifndef FALSE
FALSE			equ 0
endif

ifndef TRUE
TRUE			equ 1
endif
if 0
ifndef IN
IN equ 1
endif

ifndef OUT
OUT equ 1
endif

ifndef
 equ 1
endif

undef far
undef near
undef pascal

far equ 1
near equ 1

if ( NOT defined(_MAC)) AND ((_MSC_VER GE 800) OR defined(_STDCALL_SUPPORTED))
pascal			equ __stdcall
else
pascal equ 1
endif

if defined(DOSWIN32) OR defined(_MAC)
cdecl			equ _cdecl
ifndef CDECL
CDECL			equ _cdecl
endif
else
cdecl equ 1
ifndef CDECL
CDECL equ 1
endif
endif

ifdef _MAC
CALLBACK		equ PASCA
WINAPI			equ CDEC
WINAPIV			equ CDEC
APIENTRY		equ WINAPI
APIPRIVATE		equ CDEC
ifdef _68K_
PASCAL			equ __pascal
else
PASCAL equ 1
endif
elif (_MSC_VER GE 800) OR defined(_STDCALL_SUPPORTED)
CALLBACK		equ __stdcall
WINAPI			equ __stdcall
WINAPIV			equ __cdecl
APIENTRY		equ WINAPI
APIPRIVATE		equ __stdcall
PASCAL			equ __stdcall
else
CALLBACK equ 1
WINAPI equ 1
WINAPIV equ 1
APIENTRY		equ WINAPI
APIPRIVATE equ 1
PASCAL			equ pascal
endif

ifndef _M_CEE_PURE
ifndef WINAPI_INLINE
WINAPI_INLINE		equ WINAPI
endif
endif

undef FAR
undef  NEAR
FAR			equ far
NEAR			equ near
ifndef CONST
CONST			equ const
endif

endif ; if 0

;DWORD			 typedef DWORD
endif ; if 0
BOOL			typedef sdword
;BYTE			 typedef unsigned char
;WORD			 typedef unsigned short
FLOAT			typedef real4
PFLOAT			typedef ptr FLOAT
PBOOL			typedef ptr BOOL
LPBOOL			typedef ptr BOOL
PBYTE			typedef ptr BYTE
LPBYTE			typedef ptr BYTE
PINT			typedef ptr SDWORD
LPINT			typedef ptr SDWORD
PWORD			typedef ptr WORD
LPWORD			typedef ptr WORD
LPLONG			typedef ptr SDWORD
PDWORD			typedef ptr DWORD
LPDWORD			typedef ptr DWORD
LPVOID			typedef ptr
LPCVOID			typedef ptr

;INT			 typedef SDWORD
UINT			typedef DWORD
PUINT			typedef ptr DWORD


ifndef NT_INCLUDED
include winnt.inc
endif

WPARAM			typedef UINT_PTR
LPARAM			typedef LONG_PTR
LRESULT			typedef LONG_PTR

if 0
ifndef NOMINMAX

ifndef max
max macro a,b
	exitm<(((a) GT (b)) ? (a) : (b))>
	endm
endif

ifndef min
min macro a,b
	exitm<(((a) LT (b)) ? (a) : (b))>
	endm
endif

endif  ;; NOMINMAX
endif

MAKEWORD macro a, b
	exitm<((((((DWORD_PTR)(a)) AND 0xff)) OR (((((DWORD_PTR)(b)) AND 0xff))) SHL 8))>
	endm
MAKELONG macro a, b
	exitm<((LONG)(((((DWORD_PTR)(a)) AND 0xffff)) OR (((((DWORD_PTR)(b)) AND 0xffff))) SHL 16))>
	endm
LOWORD macro l
	exitm<((((DWORD_PTR)(l)) AND 0xffff))>
	endm
HIWORD macro l
	exitm<(((((DWORD_PTR)(l)) SHR 16) AND 0xffff))>
	endm
LOBYTE macro w
	exitm<((((DWORD_PTR)(w)) AND 0xff))>
	endm
HIBYTE macro w
	exitm<(((((DWORD_PTR)(w)) SHR 8) AND 0xff))>
	endm

SPHANDLE		typedef ptr HANDLE
LPHANDLE		typedef ptr HANDLE
HGLOBAL			typedef HANDLE
HLOCAL			typedef HANDLE
GLOBALHANDLE		typedef HANDLE
LOCALHANDLE		typedef HANDLE
ifndef _MANAGED
ifndef _MAC
ifdef _WIN64
;    FARPROC		 proc :	   NEARPROC	       proc :	 PROC		     proc :
else
;    FARPROC		 proc :	   NEARPROC	       proc :	 PROC		     proc :
endif  ;; _WIN64
else
;    FARPROC		 proc :	   NEARPROC	       proc :	 PROC		     proc :
endif
else
;    FARPROC		 proc :void    NEARPROC		   proc :void	 PROC		     proc :voidendif

;			typedef WORD		    ATOM; BUGBUG - might want to remove this from minwin

DECLARE_HANDLE(HKEY);
PHKEY			typedef ptr HKEY
DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HINSTANCE);
HMODULE			typedef HINSTANCE
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HSPRITE);
DECLARE_HANDLE(HLSURF);
DECLARE_HANDLE(HSTR);
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HWINSTA);
DECLARE_HANDLE(HKL);

ifndef _MAC
HFILE			typedef SDWORD
else
HFILE			typedef SWORD
endif

FILETIME		STRUC
dwLowDateTime		dd ?
dwHighDateTime		dd ?
FILETIME		ENDS
PFILETIME		typedef ptr FILETIME
LPFILETIME		typedef ptr FILETIME
_FILETIME_ equ 1

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif ;; _MINWINDEF_

