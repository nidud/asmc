ifndef __LIBC_INC
 include libc.inc
endif
.xlist
.nocref
ifndef _WINDOWS_
_WINDOWS_ equ <>

if not defined(_68K_)	and \
   not defined(_MPPC_)	and \
   not defined(_X86_)	and \
   not defined(_IA64_)	and \
   not defined(_AMD64_) and defined(_M_IX86)
_X86_  equ <>
endif

if not defined(_68K_)	and \
   not defined(_MPPC_)	and \
   not defined(_X86_)	and \
   not defined(_IA64_)	and \
   not defined(_AMD64_) and defined(_M_AMD64)
_AMD64_ equ <>
endif

if not defined(_68K_)	and \
   not defined(_MPPC_)	and \
   not defined(_X86_)	and \
   not defined(_IA64_)	and \
   not defined(_AMD64_) and defined(_M_M68K)
_68K_  equ <>
endif

if not defined(_68K_)	and \
   not defined(_MPPC_)	and \
   not defined(_X86_)	and \
   not defined(_IA64_)	and \
   not defined(_AMD64_) and defined(_M_MPPC)
_MPPC_ equ <>
endif

if not defined(_68K_)	and \
   not defined(_MPPC_)	and \
   not defined(_X86_)	and \
   not defined(_M_IX86) and \
   not defined(_AMD64_) and defined(_M_IA64)
ifndef _IA64_
_IA64_ equ <>
endif
endif

ifndef _WIN32_WINNT
ifndef WINVER
_WIN32_WINNT	equ 0x0400
else
_WIN32_WINNT	equ WINVER
endif
endif
ifndef _WIN32_WINDOWS
ifndef WINVER
_WIN32_WINDOWS	equ 400h
else
_WIN32_WINDOWS	equ WINVER
endif
endif

ifndef _WIN32_FUSION
_WIN32_FUSION	equ 0
endif

ifndef _WIN32_WCE
_WIN32_WCE	equ 0
endif

ifndef ISOLATION_AWARE_ENABLED
ISOLATION_AWARE_ENABLED equ 0
endif

ifndef WINVER
WINVER equ 0x0400
else
if defined(_WIN32_WINNT) and (WINVER LT 0x0400) and (_WIN32_WINNT GT 0x0400)
.err <WINVER setting conflicts with _WIN32_WINNT setting>
endif
endif

ifndef SNDMSG
ifdef __cplusplus
ifndef _MAC
SNDMSG equ <::SendMessage>
else
SNDMSG equ <::AfxSendMessage>
endif
else
ifndef _MAC
SNDMSG equ <SendMessage>
else
SNDMSG equ <AfxSendMessage>
endif
endif
endif


GetInstanceModule macro hInstance
	exitm<hInstance>
	endm

GlobalPtrHandle macro lp
	exitm<GlobalHandle(lp)>
	endm

GlobalLockPtr macro lp
	exitm<GlobalLock(GlobalPtrHandle(lp))>
	endm

GlobalUnlockPtr macro lp
	exitm<GlobalUnlock(GlobalPtrHandle(lp))>
	endm

ifndef _MAC
GlobalAllocPtr macro flags, cb
	exitm<GlobalLock(GlobalAlloc(flags, cb))>
	endm
else
GlobalAllocPtr macro flags, cb
	exitm<GlobalLock(GlobalAlloc(flags OR GMEM_PMODELOCKSTRATEGY, cb))>
	endm
endif

GlobalReAllocPtr macro lp, cbNew, flags
	GlobalUnlockPtr(lp)
	exitm<GlobalLock(GlobalReAlloc(GlobalPtrHandle(lp), cbNew, flags))>
	endm

GlobalFreePtr macro lp
	GlobalUnlockPtr(lp)
	exitm<GlobalFree(GlobalPtrHandle(lp))>
	endm


DeletePen macro hpen
	exitm<DeleteObject(hpen)>
	endm

SelectPen macro hdc, hpen
	exitm<SelectObject(hdc, hpen)>
	endm

GetStockPen macro i
	exitm<GetStockObject(i)>
	endm

DeleteBrush macro hbr
	exitm<DeleteObject(hbr)>
	endm

SelectBrush macro hdc, hbr
	exitm<SelectObject(hdc, hbr)>
	endm

GetStockBrush macro i
	exitm<GetStockObject(i)>
	endm

DeleteRgn macro hrgn
	exitm<DeleteObject(hrgn)>
	endm

ifndef _MAC
CopyRgn macro hrgnDst, hrgnSrc
	exitm<CombineRgn(hrgnDst, hrgnSrc, 0, RGN_COPY)>
	endm
else
AfxCopyRgn macro hrgnDst, hrgnSrc
	exitm<CombineRgn(hrgnDst, hrgnSrc, 0, RGN_COPY)>
	endm
endif
IntersectRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_AND)>
	endm

SubtractRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_DIFF)>
	endm
ifndef _MAC
UnionRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_OR)>
	endm

XorRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_XOR)>
	endm
else
AfxUnionRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_OR)>
	endm

AfxXorRgn macro hrgnResult, hrgnA, hrgnB
	exitm<CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_XOR)>
	endm
endif

DeletePalette macro hpal
	exitm<DeleteObject(hpal)>
	endm

DeleteFont macro hfont
	exitm<DeleteObject(hfont)>
	endm

SelectFont macro hdc, hfont
	exitm<SelectObject(hdc, hfont)>
	endm

GetStockFont macro i
	exitm<GetStockObject(i)>
	endm

DeleteBitmap macro hbm
	exitm<DeleteObject(hbm)>
	endm

SelectBitmap macro hdc, hbm
	exitm<SelectObject(hdc, hbm)>
	endm

ifndef _MAC
InsetRect macro lprc, x, dy
	exitm<InflateRect(lprc, -x, -dy)>
	endm
else
AfxInsetRect macro lprc, x, dy
	exitm<InflateRect((lprc), -(x), -(dy))>
	endm
endif


GetWindowInstance macro hwnd
	exitm<GetWindowLongPtr(hwnd, GWLP_HINSTANCE)>
	endm

GetWindowStyle macro hwnd
	exitm<GetWindowLong(hwnd, GWL_STYLE)>
	endm

GetWindowExStyle macro hwnd
	exitm<GetWindowLong(hwnd, GWL_EXSTYLE)>
	endm

GetWindowOwner macro hwnd
	exitm<GetWindow(hwnd, GW_OWNER)>
	endm

GetFirstChild macro hwnd
	exitm<GetTopWindow(hwnd)>
	endm

GetFirstSibling macro hwnd
	exitm<GetWindow(hwnd, GW_HWNDFIRST)>
	endm

GetLastSibling macro hwnd
	exitm<GetWindow(hwnd, GW_HWNDLAST)>
	endm

GetNextSibling macro hwnd
	exitm<GetWindow(hwnd, GW_HWNDNEXT)>
	endm

GetPrevSibling macro hwnd
	exitm<GetWindow(hwnd, GW_HWNDPREV)>
	endm

GetWindowID macro hwnd
	exitm<GetDlgCtrlID(hwnd)>
	endm

SetWindowRedraw macro hwnd, fRedraw
	exitm<SNDMSG(hwnd, WM_SETREDRAW, fRedraw, 0)>
	endm

SubclassWindow macro hwnd, lpfn
	exitm<SetWindowLongPtr(hwnd, GWLP_WNDPROC, lpfn)>
	endm

IsMinimized macro hwnd
	exitm<IsIconic(hwnd)>
	endm

IsMaximized macro hwnd
	exitm<IsZoomed(hwnd)>
	endm

IsRestored macro hwnd
	and GetWindowStyle(hwnd),WS_MINIMIZE OR WS_MAXIMIZE
	.if eax
	    xor eax,eax
	.else
	    inc eax
	.endif
	exitm<eax>
	endm

SetWindowFont macro hwnd, hfont, fRedraw
	exitm<SendMessage(hwnd, WM_SETFONT, hfont, fRedraw)>
	endm

GetWindowFont macro hwnd
	exitm<SendMessage(hwnd, WM_GETFONT, 0, 0)>
	endm

if (WINVER GE 0x030a)
ifdef UNIX
MapWindowRect MwMapWindowRect
LONG MwMapWindowRect(HWND, HWND, RECT *);
else
MapWindowRect macro hwndFrom, hwndTo, lprc
	exitm<MapWindowPoints(hwndFrom, hwndTo, lprc, 2)>
	endm
endif
endif

IsLButtonDown macro
	exitm<GetKeyState(VK_LBUTTON) < 0)>
	endm

IsRButtonDown macro
	exitm<GetKeyState(VK_RBUTTON) < 0)>
	endm

IsMButtonDown macro
	exitm<GetKeyState(VK_MBUTTON) < 0)>
	endm

SubclassDialog macro hwndDlg, lpfn
	exitm<SetWindowLongPtr(hwndDlg, DWLP_DLGPROC, lpfn)>
	endm

SetDlgMsgResult macro hwnd, msg, result
	.switch msg
	  .case WM_CTLCOLORMSGBOX
	  .case WM_CTLCOLOREDIT
	  .case WM_CTLCOLORLISTBOX
	  .case WM_CTLCOLORBTN
	  .case WM_CTLCOLORDLG
	  .case WM_CTLCOLORSCROLLBAR
	  .case WM_CTLCOLORSTATIC
	  .case WM_COMPAREITEM
	  .case WM_VKEYTOITEM
	  .case WM_CHARTOITEM
	  .case WM_QUERYDRAGICON
	  .case WM_INITDIALOG
		mov eax,result
		.endc
	  .default
		SetWindowLongPtr(hwnd, DWLP_MSGRESULT, result)
		mov eax,TRUE
	.endsw
	exitm<eax>
	endm

DefDlgProcEx macro hwnd, msg, wParam, lParam, pfRecursion
	;exitm<*(pfRecursion) = TRUE, DefDlgProc(hwnd, msg, wParam, lParam))>
	endm

CheckDefDlgRecursion macro pfRecursion
	;if (*(pfRecursion)) { *(pfRecursion) = FALSE; return FALSE; }
	;exitm<>
	endm


Static_Enable macro hwndCtl, fEnable
	exitm<EnableWindow(hwndCtl, fEnable)>
	endm

Static_GetText macro hwndCtl, lpch, cchMax
	exitm<GetWindowText(hwndCtl, lpch, cchMax)>
	endm

Static_GetTextLength macro hwndCtl
	exitm<GetWindowTextLength(hwndCtl)>
	endm

Static_SetText macro hwndCtl, lpsz
	exitm<SetWindowText(hwndCtl, lpsz)>
	endm

Static_SetIcon macro hwndCtl, hIcon
	exitm<SNDMSG(hwndCtl, STM_SETICON, hIcon, 0)>
	endm

Static_GetIcon macro hwndCtl, hIcon
	exitm<SNDMSG(hwndCtl, STM_GETICON, 0, 0)>
	endm


_ncalloc    equ <calloc>
_nexpand    equ <_expand>
_ffree	    equ <free>
_fmalloc    equ <malloc>
_fmemccpy   equ <_memccpy>
_fmemchr    equ <memchr>
_fmemcmp    equ <memcmp>
_fmemcpy    equ <memcpy>
_fmemicmp   equ <_memicmp>
_fmemmove   equ <memmove>
_fmemset    equ <memset>
_fmsize	    equ <_msize>
_frealloc   equ <realloc>
_fstrcat    equ <strcat>
_fstrchr    equ <strchr>
_fstrcmp    equ <strcmp>
_fstrcpy    equ <strcpy>
_fstrcspn   equ <strcspn>
_fstrdup    equ <_strdup>
_fstricmp   equ <_stricmp>
_fstrlen    equ <strlen>
_fstrlwr    equ <_strlwr>
_fstrncat   equ <strncat>
_fstrncmp   equ <strncmp>
_fstrncpy   equ <strncpy>
_fstrnicmp  equ <_strnicmp>
_fstrnset   equ <_strnset>
_fstrpbrk   equ <strpbrk>
_fstrrchr   equ <strrchr>
_fstrrev    equ <_strrev>
_fstrset    equ <_strset>
_fstrspn    equ <strspn>
_fstrstr    equ <strstr>
_fstrtok    equ <strtok>
_fstrupr    equ <_strupr>
_nfree	    equ <free>
_nmalloc    equ <malloc>
_nmsize	    equ <_msize>
_nrealloc   equ <realloc>
_nstrdup    equ <_strdup>
hmemcpy	    equ <MoveMemory>

ifndef DECLARE_HANDLE32
DECLARE_HANDLE32    equ <DECLARE_HANDLE>
endif

ifndef _INC_WINDOWS
_INC_WINDOWS equ <>

include excpt.inc
include stdarg.inc

include windef.inc
include winbase.inc
include wingdi.inc
include winuser.inc

ifdef _WIN32NLS
include winnls.inc
endif

include wincon.inc
include winver.inc

ifdef _WIN32REG
include winreg.inc
endif

include winnetwk.inc


ifndef WIN32_LEAN_AND_MEAN
include cderr.inc
include dde.inc
include ddeml.inc
include dlgs.inc

include lzexpand.inc
include mmsystem.inc
include nb30.inc
include rpc.inc

include shellapi.inc

include winperf.inc

if _WIN32_WINNT GE 0x0400
include winsock2.inc
include mswsock.inc
else
include winsock.inc
endif

ifndef NOCRYPT
include wincrypt.inc
endif

ifndef NOGDI
include commdlg.inc
include winspool.inc
ifdef INC_OLE1
include ole.inc
else
include ole2.inc
endif
endif
endif ; WIN32_LEAN_AND_MEAN

ifdef INC_OLE2
include ole2.inc
endif

ifndef NOSERVICE
include winsvc.inc
endif

if WINVER GE 0x0400
ifndef NOMCX
include mcx.inc
endif
ifndef NOIME
include imm.inc
endif
endif ; WINVER >= 0x0400

endif ; _INC_WINDOWS
endif ; _WINDOWS_

.list
