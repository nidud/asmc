.pragma list(push, 0)
ifndef _WINDEF_
define _WINDEF_
ifndef __LIBC_INC
 include libc.inc
endif
include minwindef.inc
ifndef WINVER
define WINVER 0x0500
endif
ifndef _WINNT_
include winnt.inc
endif

ifndef WIN_INTERNAL
DECLARE_HANDLE(HWND)
DECLARE_HANDLE(HHOOK)
ifdef WINABLE
DECLARE_HANDLE(HEVENT)
endif
endif

ifndef GDI_INTERNAL
ifdef STRICT
HGDIOBJ typedef ptr
else
DECLARE_HANDLE(HGDIOBJ)
endif
endif

ifndef WIN_INTERNAL
DECLARE_HANDLE(HACCEL)
endif
ifndef GDI_INTERNAL
DECLARE_HANDLE(HBITMAP)
DECLARE_HANDLE(HBRUSH)
endif
if WINVER GE 0x0400
DECLARE_HANDLE(HCOLORSPACE)
endif
ifndef GDI_INTERNAL
DECLARE_HANDLE(HDC)
endif
DECLARE_HANDLE(HGLRC)
DECLARE_HANDLE(HDESK)
DECLARE_HANDLE(HENHMETAFILE)
ifndef GDI_INTERNAL
DECLARE_HANDLE(HFONT)
endif
DECLARE_HANDLE(HICON)
ifndef WIN_INTERNAL
DECLARE_HANDLE(HMENU)
endif
ifndef GDI_INTERNAL
DECLARE_HANDLE(HPALETTE)
DECLARE_HANDLE(HPEN)
endif
if (WINVER GE 0x0400)
DECLARE_HANDLE(HWINEVENTHOOK)
endif
if WINVER GE 0x0500
DECLARE_HANDLE(HMONITOR)
DECLARE_HANDLE(HUMPD)
endif

HCURSOR	   typedef HICON
COLORREF   typedef DWORD
LPCOLORREF typedef PTR DWORD

define HFILE_ERROR (-1)

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

tagSIZE		STRUC
_cx		sdword ?
cy		sdword ?
tagSIZE		ENDS
PSIZE		typedef ptr tagSIZE
LPSIZE		typedef ptr tagSIZE
SIZEL		typedef tagSIZE
PSIZEL		typedef ptr tagSIZE
LPSIZEL		typedef ptr tagSIZE

POINTS		STRUC
x		sword ?
y		sword ?
POINTS		ENDS
PPOINTS		typedef ptr POINTS
LPPOINTS	typedef ptr POINTS

define DM_UPDATE	   1
define DM_COPY		   2
define DM_PROMPT	   4
define DM_MODIFY	   8

define DM_IN_BUFFER	   DM_MODIFY
define DM_IN_PROMPT	   DM_PROMPT
define DM_OUT_BUFFER	   DM_COPY
define DM_OUT_DEFAULT	   DM_UPDATE

define DC_FIELDS	   1
define DC_PAPERS	   2
define DC_PAPERSIZE	   3
define DC_MINEXTENT	   4
define DC_MAXEXTENT	   5
define DC_BINS		   6
define DC_DUPLEX	   7
define DC_SIZE		   8
define DC_EXTRA		   9
define DC_VERSION	   10
define DC_DRIVER	   11
define DC_BINNAMES	   12
define DC_ENUMRESOLUTIONS  13
define DC_FILEDEPENDENCIES 14
define DC_TRUETYPE	   15
define DC_PAPERNAMES	   16
define DC_ORIENTATION	   17
define DC_COPIES	   18

endif
.pragma list(pop)

