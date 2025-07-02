ifndef _INC_WINDOWSX
.pragma list(push, 0)
define _INC_WINDOWSX

ifndef SNDMSG
ifndef _MAC
SNDMSG equ <SendMessage>
else
SNDMSG equ <AfxSendMessage>
endif
endif

;;***** KERNEL Macro APIs ***************************************************

GetInstanceModule macro hInstance
	exitm<(hInstance)>
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
	exitm<GlobalLock(GlobalAlloc((flags), (cb)))>
	endm
else
GlobalAllocPtr macro flags, cb
	exitm<GlobalLock(GlobalAlloc((flags) or GMEM_PMODELOCKSTRATEGY, (cb)))>
	endm
endif
GlobalReAllocPtr macro lp, cbNew, flags
	exitm<GlobalUnlockPtr(lp), GlobalLock(GlobalReAlloc(GlobalPtrHandle(lp) , (cbNew), (flags)))>
	endm

GlobalFreePtr macro lp
	exitm<GlobalUnlockPtr(lp), GlobalFree(GlobalPtrHandle(lp))>
	endm

;;***** GDI Macro APIs ******************************************************

DeletePen macro hpen
	exitm<DeleteObject(hpen)>
	endm
SelectPen macro hdc, hpen
	exitm<SelectObject((hdc), (hpen))>
	endm
GetStockPen macro i
	exitm<GetStockObject(i)>
	endm

DeleteBrush macro hbr
	exitm<DeleteObject(hbr)>
	endm
SelectBrush macro hdc, hbr
	exitm<SelectObject((hdc), (hbr))>
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
	exitm<SelectObject((hdc), (hfont))>
	endm
GetStockFont macro i
	exitm<GetStockObject(i)>
	endm

DeleteBitmap macro hbm
	exitm<DeleteObject(hbm)>
	endm
SelectBitmap macro hdc, hbm
	exitm<SelectObject((hdc), (hbm))>
	endm

ifndef _MAC
InsetRect macro lprc, x, y
	exitm<InflateRect((lprc), -(x), -(y))>
	endm
else
AfxInsetRect macro lprc, x, y
	exitm<InflateRect((lprc), -(x), -(y))>
	endm
endif

;;***** USER Macro APIs *****************************************************

GetWindowInstance macro hwnd
	exitm<GetWindowLong(hwnd, GWL_HINSTANCE)>
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
	exitm<SetWindowLong(hwnd, GWL_WNDPROC, lpfn)>
	endm

IsMinimized macro hwnd
	exitm<IsIconic(hwnd)>
	endm
IsMaximized macro hwnd
	exitm<IsZoomed(hwnd)>
	endm
IsRestored macro hwnd
	exitm<((GetWindowStyle(hwnd) AND (WS_MINIMIZE OR WS_MAXIMIZE)) EQ 0)>
	endm

SetWindowFont macro hwnd, hfont, fRedraw
	exitm<FORWARD_WM_SETFONT((hwnd), (hfont), (fRedraw), SNDMSG)>
	endm

GetWindowFont macro hwnd
	exitm<FORWARD_WM_GETFONT((hwnd), SNDMSG)>
	endm
if (WINVER GE 0x030a)
MapWindowRect macro hwndFrom, hwndTo, lprc
	exitm<MapWindowPoints(hwndFrom, hwndTo, lprc, 2)>
	endm

endif
IsLButtonDown macro
	exitm<(GetKeyState(VK_LBUTTON) LT 0)>
	endm
IsRButtonDown macro
	exitm<(GetKeyState(VK_RBUTTON) LT 0)>
	endm
IsMButtonDown macro
	exitm<(GetKeyState(VK_MBUTTON) LT 0)>
	endm

SubclassDialog macro hwndDlg, lpfn
	exitm<SetWindowLong(hwndDlg, DWL_DLGPROC, lpfn)>
	endm


SetDlgMsgResult macro hwnd, msg, result
	if ((msg eq WM_CTLCOLORMSGBOX) or
	    (msg eq WM_CTLCOLOREDIT) or
	    (msg eq WM_CTLCOLORLISTBOX) or
	    (msg eq WM_CTLCOLORBTN) or
	    (msg eq WM_CTLCOLORDLG) or
	    (msg eq WM_CTLCOLORSCROLLBAR) or
	    (msg eq WM_CTLCOLORSTATIC) or
	    (msg eq WM_COMPAREITEM) or
	    (msg eq WM_VKEYTOITEM) or
	    (msg eq WM_CHARTOITEM) or
	    (msg eq WM_QUERYDRAGICON) or
	    (msg eq WM_INITDIALOG))
	   exitm<result>
	endif
	exitm<SetWindowLong(hwnd, DWL_MSGRESULT, result, TRUE)>
	endm

DefDlgProcEx macro hwnd, msg, wParam, lParam, pfRecursion
	mov [pfRecursion],TRUE
	exitm<DefDlgProc(hwnd, msg, wParam, lParam)>
	endm

CheckDefDlgRecursion macro pfRecursion
	mov eax,FALSE
	.if [pfRecursion] != eax
	    mov [pfRecursion],eax
	    .break
	.endif
	exitm<>
	endm

;;***** Message crackers ***************************************************

HANDLE_MSG macro hwnd, message, fn
	.case message
	HANDLE_&message&(hwnd, wParam, lParam, fn)
	.return
	exitm<>
	endm

HANDLE_WM_COPYDATA macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam)>
	endm

FORWARD_WM_COPYDATA macro hwnd, hwndFrom, pcds, fn
	exitm<fn(hwnd, WM_COPYDATA, hwndFrom, pcds)>
	endm

;; void Cls_OnCompacting(HWND hwnd, UINT compactRatio)
HANDLE_WM_COMPACTING macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_COMPACTING macro hwnd, compactRatio, fn
	exitm<fn(hwnd, WM_COMPACTING, compactRatio, 0)>
	endm

;; void Cls_OnWinIniChange(HWND hwnd, LPCTSTR lpszSectionName)
HANDLE_WM_WININICHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_WININICHANGE macro hwnd, lpszSectionName, fn
	exitm<fn(hwnd, WM_WININICHANGE, 0, lpszSectionName)>
	endm


;; void Cls_OnSysColorChange(HWND hwnd)
HANDLE_WM_SYSCOLORCHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_SYSCOLORCHANGE macro hwnd, fn
	exitm<fn(hwnd, WM_SYSCOLORCHANGE, 0, 0)>
	endm

;; BOOL Cls_OnQueryNewPalette(HWND hwnd)
HANDLE_WM_QUERYNEWPALETTE macro hwnd, wParam, lParam, fn
	exitm<MAKELRESULT(fn(hwnd, 0))>
	endm

FORWARD_WM_QUERYNEWPALETTE macro hwnd, fn
	exitm<fn(hwnd, WM_QUERYNEWPALETTE, 0, 0)>
	endm

;; void Cls_OnPaletteIsChanging(HWND hwnd, HWND hwndPaletteChange)
HANDLE_WM_PALETTEISCHANGING macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_PALETTEISCHANGING macro hwnd, hwndPaletteChange, fn
	exitm<fn(hwnd, WM_PALETTEISCHANGING, hwndPaletteChange, 0)>
	endm

;; void Cls_OnPaletteChanged(HWND hwnd, HWND hwndPaletteChange)
HANDLE_WM_PALETTECHANGED macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_PALETTECHANGED macro hwnd, hwndPaletteChange, fn
	exitm<fn(hwnd, WM_PALETTECHANGED, hwndPaletteChange, 0)>
	endm

;; void Cls_OnFontChange(HWND hwnd)
HANDLE_WM_FONTCHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_FONTCHANGE macro hwnd, fn
	exitm<fn(hwnd, WM_FONTCHANGE, 0, 0)>
	endm

;; void Cls_OnSpoolerStatus(HWND hwnd, UINT status, int cJobInQueue)
HANDLE_WM_SPOOLERSTATUS macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), 0)>
	endm

FORWARD_WM_SPOOLERSTATUS macro hwnd, status, cJobInQueue, fn
	exitm<fn(hwnd, WM_SPOOLERSTATUS, status, MAKELPARAM((cJobInQueue), 0))>
	endm

;; void Cls_OnDevModeChange(HWND hwnd, LPCTSTR lpszDeviceName)
HANDLE_WM_DEVMODECHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_DEVMODECHANGE macro hwnd, lpszDeviceName, fn
	exitm<fn(hwnd, WM_DEVMODECHANGE, 0, lpszDeviceName)>
	endm

;; void Cls_OnTimeChange(HWND hwnd)
HANDLE_WM_TIMECHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_TIMECHANGE macro hwnd, fn
	exitm<fn(hwnd, WM_TIMECHANGE, 0, 0)>
	endm

;; void Cls_OnPower(HWND hwnd, int code)
HANDLE_WM_POWER macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_POWER macro hwnd, code, fn
	exitm<fn(hwnd, WM_POWER, code, 0)>
	endm

;; BOOL Cls_OnQueryEndSession(HWND hwnd)
HANDLE_WM_QUERYENDSESSION macro hwnd, wParam, lParam, fn
	exitm<MAKELRESULT(fn(hwnd), 0)>
	endm

FORWARD_WM_QUERYENDSESSION macro hwnd, fn
	exitm<fn(hwnd, WM_QUERYENDSESSION, 0, 0)>
	endm

;; void Cls_OnEndSession(HWND hwnd, BOOL fEnding)
HANDLE_WM_ENDSESSION macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_ENDSESSION macro hwnd, fEnding, fn
	exitm<fn(hwnd, WM_ENDSESSION, fEnding, 0)>
	endm

;; void Cls_OnQuit(HWND hwnd, int exitCode)
HANDLE_WM_QUIT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_QUIT macro hwnd, exitCode, fn
	exitm<fn(hwnd, WM_QUIT, exitCode, 0)>
	endm

;; This message is in Windows 3.1 only
;; void Cls_OnSystemError(HWND hwnd, int errCode)
HANDLE_WM_SYSTEMERROR macro hwnd, wParam, lParam, fn
	exitm<0>
	endm
FORWARD_WM_SYSTEMERROR macro hwnd, errCode, fn
	exitm<0>
	endm

;; BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
HANDLE_WM_CREATE macro hwnd, wParam, lParam, fn
	.if fn(hwnd, lParam)
	    xor eax,eax
	.else
	    dec eax
	.endif
	exitm<>
	endm

FORWARD_WM_CREATE macro hwnd, lpCreateStruct, fn
	exitm<fn(hwnd, WM_CREATE, 0, lpCreateStruct)>
	endm


;; BOOL Cls_OnNCCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
HANDLE_WM_NCCREATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam)>
	endm

FORWARD_WM_NCCREATE macro hwnd, lpCreateStruct, fn
	exitm<fn(hwnd, WM_NCCREATE, 0, lpCreateStruct)>
	endm

;; void Cls_OnDestroy(HWND hwnd)
HANDLE_WM_DESTROY macro hwnd, wParam, lParam, fn
	fn(hwnd)
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_DESTROY macro hwnd, fn
	exitm<fn(hwnd, WM_DESTROY, 0, 0)>
	endm

;; void Cls_OnNCDestroy(HWND hwnd)
HANDLE_WM_NCDESTROY macro hwnd, wParam, lParam, fn
	fn(hwnd)
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_NCDESTROY macro hwnd, fn
	exitm<fn(hwnd, WM_NCDESTROY, 0, 0)>
	endm

;; void Cls_OnShowWindow(HWND hwnd, BOOL fShow, UINT status)
HANDLE_WM_SHOWWINDOW macro hwnd, wParam, lParam, fn
	fn(hwnd, wParam, lParam)
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_SHOWWINDOW macro hwnd, fShow, status, fn
	exitm<fn(hwnd, WM_SHOWWINDOW, fShow, status)>
	endm

;; void Cls_OnSetRedraw(HWND hwnd, BOOL fRedraw)
HANDLE_WM_SETREDRAW macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_SETREDRAW macro hwnd, fRedraw, fn
	exitm<fn(hwnd, WM_SETREDRAW, fRedraw, 0)>
	endm

;; void Cls_OnEnable(HWND hwnd, BOOL fEnable)
HANDLE_WM_ENABLE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_ENABLE macro hwnd, fEnable, fn
	exitm<fn(hwnd, WM_ENABLE, fEnable, 0)>
	endm

;; void Cls_OnSetText(HWND hwnd, LPCTSTR lpszText)
HANDLE_WM_SETTEXT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_SETTEXT macro hwnd, lpszText, fn
	exitm<fn(hwnd, WM_SETTEXT, 0, lpszText)>
	endm


;; INT Cls_OnGetText(HWND hwnd, int cchTextMax, LPTSTR lpszText)
HANDLE_WM_GETTEXT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam)>
	endm

FORWARD_WM_GETTEXT macro hwnd, cchTextMax, lpszText, fn
	exitm<fn(hwnd, WM_GETTEXT, cchTextMax, lpszText)>
	endm


;; INT Cls_OnGetTextLength(HWND hwnd)
HANDLE_WM_GETTEXTLENGTH macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd)>
	endm
FORWARD_WM_GETTEXTLENGTH macro hwnd, fn
	exitm<fn(hwnd, WM_GETTEXTLENGTH, 0, 0)>
	endm


;; BOOL Cls_OnWindowPosChanging(HWND hwnd, LPWINDOWPOS lpwpos)
HANDLE_WM_WINDOWPOSCHANGING macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam)>
	endm

FORWARD_WM_WINDOWPOSCHANGING macro hwnd, lpwpos, fn
	exitm<fn(hwnd, WM_WINDOWPOSCHANGING, 0, lpwpos)>
	endm

;; void Cls_OnWindowPosChanged(HWND hwnd, LPWINDOWPOS lpwpos)
HANDLE_WM_WINDOWPOSCHANGED macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_WINDOWPOSCHANGED macro hwnd, lpwpos, fn
	exitm<fn(hwnd, WM_WINDOWPOSCHANGED, 0, lpwpos)>
	endm

;; void Cls_OnMove(HWND hwnd, int x, int y)
HANDLE_WM_MOVE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_MOVE macro hwnd, x, y, fn
	exitm<fn(hwnd, WM_MOVE, 0, MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
HANDLE_WM_SIZE macro hwnd, wParam, lParam, fn
    ifdef _WIN64
	mov r9d,r8d
	shr r9d,16
	and r8d,0xFFFF
	fn(rcx, edx, r8d, r9d)
    else
	mov eax,lParam
	mov edx,eax
	shr edx,16
	and eax,0xFFFF
	fn(hwnd, wParam, eax, edx)
    endif
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_SIZE macro hwnd, state, x, y, fn
	exitm<fn(hwnd, WM_SIZE, state, MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnClose(HWND hwnd)
HANDLE_WM_CLOSE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd)>
	endm

FORWARD_WM_CLOSE macro hwnd, fn
	exitm<fn(hwnd, WM_CLOSE, 0, 0)>
	endm

;; BOOL Cls_OnQueryOpen(HWND hwnd)
HANDLE_WM_QUERYOPEN macro hwnd, wParam, lParam, fn
	exitm<MAKELRESULT(fn(hwnd), 0)>
	endm

FORWARD_WM_QUERYOPEN macro hwnd, fn
	exitm<fn(hwnd, WM_QUERYOPEN, 0, 0)>
	endm

;; void Cls_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
HANDLE_WM_GETMINMAXINFO macro hwnd, wParam, lParam, fn
	fn(hwnd, lParam)
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_GETMINMAXINFO macro hwnd, lpMinMaxInfo, fn
	exitm<fn(hwnd, WM_GETMINMAXINFO, 0, lpMinMaxInfo)>
	endm

;; void Cls_OnPaint(HWND hwnd)
HANDLE_WM_PAINT macro hwnd, wParam, lParam, fn
	fn(hwnd)
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_PAINT macro hwnd, fn
	exitm<fn(hwnd, WM_PAINT, 0, 0)>
	endm

;; BOOL Cls_OnEraseBkgnd(HWND hwnd, HDC hdc)
HANDLE_WM_ERASEBKGND macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam)>
	endm

FORWARD_WM_ERASEBKGND macro hwnd, hdc, fn
	exitm<fn(hwnd, WM_ERASEBKGND, hdc, 0)>
	endm

;; BOOL Cls_OnIconEraseBkgnd(HWND hwnd, HDC hdc)
HANDLE_WM_ICONERASEBKGND macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam)>
	endm

FORWARD_WM_ICONERASEBKGND macro hwnd, hdc, fn
	exitm<fn(hwnd, WM_ICONERASEBKGND, hdc, 0)>
	endm

;; void Cls_OnNCPaint(HWND hwnd, HRGN hrgn)
HANDLE_WM_NCPAINT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_NCPAINT macro hwnd, hrgn, fn
	exitm<fn(hwnd, WM_NCPAINT, hrgn, 0)>
	endm

;; UINT Cls_OnNCCalcSize(HWND hwnd, BOOL fCalcValidRects, NCCALCSIZE_PARAMS * lpcsp)
HANDLE_WM_NCCALCSIZE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0, lParam)>
	endm

FORWARD_WM_NCCALCSIZE macro hwnd, fCalcValidRects, lpcsp, fn
	exitm<fn(hwnd, WM_NCCALCSIZE, 0, lpcsp)>
	endm

;; UINT Cls_OnNCHitTest(HWND hwnd, int x, int y)
HANDLE_WM_NCHITTEST macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam))>
	endm

FORWARD_WM_NCHITTEST macro hwnd, x, y, fn
	exitm<fn(hwnd, WM_NCHITTEST, 0, MAKELPARAM((x), (y)))>
	endm

;; HICON Cls_OnQueryDragIcon(HWND hwnd)
HANDLE_WM_QUERYDRAGICON macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd)>
	endm
FORWARD_WM_QUERYDRAGICON macro hwnd, fn
	exitm<fn(hwnd, WM_QUERYDRAGICON, 0, 0)>
	endm


ifdef _INC_SHELLAPI
;; void Cls_OnDropFiles(HWND hwnd, HDROP hdrop)
HANDLE_WM_DROPFILES macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_DROPFILES macro hwnd, hdrop, fn
	exitm<fn(hwnd, WM_DROPFILES, hdrop, 0)>
	endm

endif  ;; _INC_SHELLAPI

;; void Cls_OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
HANDLE_WM_ACTIVATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(wParam), lParam, HIWORD(wParam), 0)>
	endm

FORWARD_WM_ACTIVATE macro hwnd, state, hwndActDeact, fMinimized, fn
	exitm<fn(hwnd, WM_ACTIVATE, MAKEWPARAM(state, fMinimized), hwndActDeact)>
	endm

;; void Cls_OnActivateApp(HWND hwnd, BOOL fActivate, DWORD dwThreadId)
HANDLE_WM_ACTIVATEAPP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, 0)>
	endm

FORWARD_WM_ACTIVATEAPP macro hwnd, fActivate, dwThreadId, fn
	exitm<fn(hwnd, WM_ACTIVATEAPP, fActivate, dwThreadId)>
	endm

;; BOOL Cls_OnNCActivate(HWND hwnd, BOOL fActive, HWND hwndActDeact, BOOL fMinimized)
HANDLE_WM_NCACTIVATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0, 0)>
	endm

FORWARD_WM_NCACTIVATE macro hwnd, fActive, hwndActDeact, fMinimized, fn
	exitm<fn(hwnd, WM_NCACTIVATE, fActive, 0)>
	endm

;; void Cls_OnSetFocus(HWND hwnd, HWND hwndOldFocus)
HANDLE_WM_SETFOCUS macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_SETFOCUS macro hwnd, hwndOldFocus, fn
	exitm<fn(hwnd, WM_SETFOCUS, hwndOldFocus, 0)>
	endm


;; void Cls_OnKillFocus(HWND hwnd, HWND hwndNewFocus)
HANDLE_WM_KILLFOCUS macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_KILLFOCUS macro hwnd, hwndNewFocus, fn
	exitm<fn(hwnd, WM_KILLFOCUS, hwndNewFocus, 0)>
	endm

;; void Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
HANDLE_WM_KEYDOWN macro hwnd, wParam, lParam, fn
	mov edx,dword ptr wParam
	mov r9,lParam
	mov rax,r9
	shr rax,32
	exitm<fn(hwnd, edx, TRUE, r9d, eax)>
	endm

FORWARD_WM_KEYDOWN macro hwnd, vk, cRepeat, flags, fn
	exitm<fn(hwnd, WM_KEYDOWN, vk, MAKELPARAM(cRepeat, flags))>
	endm

;; void Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
HANDLE_WM_KEYUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, FALSE, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_KEYUP macro hwnd, vk, cRepeat, flags, fn
	exitm<fn(hwnd, WM_KEYUP, vk, MAKELPARAM(cRepeat, flags))>
	endm

HANDLE_WM_CHAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), 0)>
	endm

FORWARD_WM_CHAR macro hwnd, h, cRepeat, fn
	exitm<fn(hwnd, WM_CHAR, h, MAKELPARAM(cRepeat, 0))>
	endm

HANDLE_WM_DEADCHAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), 0)>
	endm

FORWARD_WM_DEADCHAR macro hwnd, h, cRepeat, fn
	exitm<fn(hwnd, WM_DEADCHAR, h, MAKELPARAM(cRepeat, 0))>
	endm

;; void Cls_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
HANDLE_WM_SYSKEYDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, TRUE, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_SYSKEYDOWN macro hwnd, vk, cRepeat, flags, fn
	exitm<fn(hwnd, WM_SYSKEYDOWN, vk, MAKELPARAM(cRepeat, flags))>
	endm

;; void Cls_OnSysKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
HANDLE_WM_SYSKEYUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, FALSE, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_SYSKEYUP macro hwnd, vk, cRepeat, flags, fn
	exitm<fn(hwnd, WM_SYSKEYUP, vk, MAKELPARAM(cRepeat, flags))>
	endm

HANDLE_WM_SYSCHAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), 0)>
	endm

FORWARD_WM_SYSCHAR macro hwnd, h, cRepeat, fn
	exitm<fn(hwnd, WM_SYSCHAR, h, MAKELPARAM(cRepeat, 0))>
	endm

HANDLE_WM_SYSDEADCHAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), 0)>
	endm

FORWARD_WM_SYSDEADCHAR macro hwnd, h, cRepeat, fn
	exitm<fn(hwnd, WM_SYSDEADCHAR, h, MAKELPARAM(cRepeat, 0))>
	endm

;; void Cls_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
HANDLE_WM_MOUSEMOVE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), wParam, 0)>
	endm

FORWARD_WM_MOUSEMOVE macro hwnd, x, y, keyFlags, fn
	exitm<fn(hwnd, WM_MOUSEMOVE, keyFlags, MAKELPARAM(x, y))>
	endm

;; void Cls_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_LBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), wParam, 0)>
	endm

FORWARD_WM_LBUTTONDOWN macro hwnd, fDoubleClick, x, y, keyFlags, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN, keyFlags, MAKELPARAM((x), (y)))>
	endm


;; void Cls_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_LBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), wParam, 0)>
	endm

;; void Cls_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
HANDLE_WM_LBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), wParam, 0)>
	endm

FORWARD_WM_LBUTTONUP macro hwnd, x, y, keyFlags, fn
	exitm<fn(hwnd, WM_LBUTTONUP, keyFlags, MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_RBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_RBUTTONDOWN macro hwnd, fDoubleClick, x, y, keyFlags, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_RBUTTONDBLCLK : WM_RBUTTONDOWN, (keyFlags), MAKELPARAM((x), (y)))>
	endm


;; void Cls_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_RBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

;; void Cls_OnRButtonUp(HWND hwnd, int x, int y, UINT flags)
HANDLE_WM_RBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_RBUTTONUP macro hwnd, x, y, keyFlags, fn
	exitm<fn(hwnd, WM_RBUTTONUP, (keyFlags), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_MBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_MBUTTONDOWN macro hwnd, fDoubleClick, x, y, keyFlags, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_MBUTTONDBLCLK : WM_MBUTTONDOWN, (keyFlags), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
HANDLE_WM_MBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm


;; void Cls_OnMButtonUp(HWND hwnd, int x, int y, UINT flags)
HANDLE_WM_MBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_MBUTTONUP macro hwnd, x, y, keyFlags, fn
	exitm<fn(hwnd, WM_MBUTTONUP, (keyFlags), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnNCMouseMove(HWND hwnd, int x, int y, UINT codeHitTest)
HANDLE_WM_NCMOUSEMOVE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCMOUSEMOVE macro hwnd, x, y, codeHitTest, fn
	exitm<fn(hwnd, WM_NCMOUSEMOVE, (codeHitTest), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnNCLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCLBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCLBUTTONDOWN macro hwnd, fDoubleClick, x, y, codeHitTest, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_NCLBUTTONDBLCLK : WM_NCLBUTTONDOWN, (codeHitTest), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnNCLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCLBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

;; void Cls_OnNCLButtonUp(HWND hwnd, int x, int y, UINT codeHitTest)
HANDLE_WM_NCLBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCLBUTTONUP macro hwnd, x, y, codeHitTest, fn
	exitm<fn(hwnd, WM_NCLBUTTONUP, (codeHitTest), MAKELPARAM((x), (y)))>
	endm

;; void Cls_OnNCRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCRBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCRBUTTONDOWN macro hwnd, fDoubleClick, x, y, codeHitTest, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_NCRBUTTONDBLCLK : WM_NCRBUTTONDOWN, (codeHitTest), MAKELPARAM((x), (y)) )>
	endm

;; void Cls_OnNCRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCRBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

;; void Cls_OnNCRButtonUp(HWND hwnd, int x, int y, UINT codeHitTest)
HANDLE_WM_NCRBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCRBUTTONUP macro hwnd, x, y, codeHitTest, fn
	exitm<fn(hwnd, WM_NCRBUTTONUP, (codeHitTest), MAKELPARAM((x), (y)) )>
	endm

;; void Cls_OnNCMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCMBUTTONDOWN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, FALSE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCMBUTTONDOWN macro hwnd, fDoubleClick, x, y, codeHitTest, fn
	exitm<fn(hwnd, (fDoubleClick) ? WM_NCMBUTTONDBLCLK : WM_NCMBUTTONDOWN, (codeHitTest), MAKELPARAM((x), (y)) )>
	endm

;; void Cls_OnNCMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT codeHitTest)
HANDLE_WM_NCMBUTTONDBLCLK macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, TRUE, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

;; void Cls_OnNCMButtonUp(HWND hwnd, int x, int y, UINT codeHitTest)
HANDLE_WM_NCMBUTTONUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(lParam), HIWORD(lParam), (wParam), 0)>
	endm

FORWARD_WM_NCMBUTTONUP macro hwnd, x, y, codeHitTest, fn
	exitm<fn(hwnd, WM_NCMBUTTONUP, (codeHitTest), MAKELPARAM((x), (y)) )>
	endm

;; int Cls_OnMouseActivate(HWND hwnd, HWND hwndTopLevel, UINT codeHitTest, UINT msg)
HANDLE_WM_MOUSEACTIVATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), LOWORD(lParam), HIWORD(lParam))>
	endm

FORWARD_WM_MOUSEACTIVATE macro hwnd, hwndTopLevel, codeHitTest, msg, fn
	exitm<fn(hwnd, WM_MOUSEACTIVATE, (hwndTopLevel), MAKELPARAM((codeHitTest), (msg)))>
	endm

;; void Cls_OnCancelMode(HWND hwnd)
HANDLE_WM_CANCELMODE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_CANCELMODE macro hwnd, fn
	exitm<fn(hwnd, WM_CANCELMODE, 0, 0)>
	endm

;; void Cls_OnTimer(HWND hwnd, UINT id)
HANDLE_WM_TIMER macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), 0)>
	endm

FORWARD_WM_TIMER macro hwnd, id, fn
	exitm<fn(hwnd, WM_TIMER, (id), 0)>
	endm

;; void Cls_OnInitMenu(HWND hwnd, HMENU hMenu)
HANDLE_WM_INITMENU macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_INITMENU macro hwnd, hMenu, fn
	exitm<fn(hwnd, WM_INITMENU, hMenu, 0)>
	endm

;; void Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu)
HANDLE_WM_INITMENUPOPUP macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_INITMENUPOPUP macro hwnd, hMenu, item, fSystemMenu, fn
	exitm<fn(hwnd, WM_INITMENUPOPUP, hMenu, MAKELPARAM((item),(fSystemMenu)))>
	endm

;; void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
HANDLE_WM_MENUSELECT macro hwnd, wParam, lParam, fn
	exitm<>
	endm

FORWARD_WM_MENUSELECT macro hwnd, hmenu, item, hmenuPopup, flags, fn
	exitm<fn(hwnd, WM_MENUSELECT, MAKEWPARAM((item), (flags)), ((hmenu) ? (hmenu) : (hmenuPopup)))>
	endm

;; DWORD Cls_OnMenuChar(HWND hwnd, UINT ch, UINT flags, HMENU hmenu)
HANDLE_WM_MENUCHAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(wParam), HIWORD(wParam), lParam)>
	endm

FORWARD_WM_MENUCHAR macro hwnd, h, flags, hmenu, fn
	exitm<fn(hwnd, WM_MENUCHAR, MAKEWPARAM(flags, h), hmenu)>
	endm


;; void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
HANDLE_WM_COMMAND macro hwnd, wParam, lParam, fn
	movzx edx,word ptr wParam
	movzx eax,word ptr wParam[2]
	exitm<fn(hwnd, edx, lParam, eax)>
	endm

FORWARD_WM_COMMAND macro hwnd, id, hwndCtl, codeNotify, fn
	exitm<fn(hwnd, WM_COMMAND, MAKEWPARAM((id),(codeNotify)), (hwndCtl))>
	endm

;; void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
HANDLE_WM_HSCROLL macro hwnd, wParam, lParam, fn
    ifdef _WIN64
	mov rdx,r9
	mov r9d,r8d
	shr r9d,16
	and r8d,0xFFFF
	fn(rcx, rdx, r8d, r9d)
    else
	mov eax,wParam
	mov edx,eax
	shr edx,16
	and eax,0xFFFF
	fn(hwnd, lParam, eax, edx)
    endif
	xor eax,eax
	exitm<>
	endm

FORWARD_WM_HSCROLL macro hwnd, hwndCtl, cd, pos, fn
	exitm<fn(hwnd, WM_HSCROLL, MAKEWPARAM(cd, pos), hwndCtl)>
	endm

;; void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
HANDLE_WM_VSCROLL macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (lParam), (LOWORD(wParam),  HIWORD(wParam)), 0)>
	endm

FORWARD_WM_VSCROLL macro hwnd, hwndCtl, code, pos, fn
	exitm<fn(hwnd, WM_VSCROLL, MAKEWPARAM((code), (pos)), (hwndCtl))>
	endm

;; void Cls_OnCut(HWND hwnd)
HANDLE_WM_CUT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_CUT macro hwnd, fn
	exitm<fn(hwnd, WM_CUT, 0, 0)>
	endm

;; void Cls_OnCopy(HWND hwnd)
HANDLE_WM_COPY macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_COPY macro hwnd, fn
	exitm<fn(hwnd, WM_COPY, 0, 0)>
	endm

;; void Cls_OnPaste(HWND hwnd)
HANDLE_WM_PASTE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_PASTE macro hwnd, fn
	exitm<fn(hwnd, WM_PASTE, 0, 0)>
	endm

;; void Cls_OnClear(HWND hwnd)
HANDLE_WM_CLEAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_CLEAR macro hwnd, fn
	exitm<fn(hwnd, WM_CLEAR, 0, 0)>
	endm

;; void Cls_OnUndo(HWND hwnd)
HANDLE_WM_UNDO macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_UNDO macro hwnd, fn
	exitm<fn(hwnd, WM_UNDO, 0, 0)>
	endm

;; HANDLE Cls_OnRenderFormat(HWND hwnd, UINT fmt)
HANDLE_WM_RENDERFORMAT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam))>
	endm

FORWARD_WM_RENDERFORMAT macro hwnd, fmt, fn
	exitm<fn(hwnd, WM_RENDERFORMAT, (fmt), 0)>
	endm

;; void Cls_OnRenderAllFormats(HWND hwnd)
HANDLE_WM_RENDERALLFORMATS macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_RENDERALLFORMATS macro hwnd, fn
	exitm<fn(hwnd, WM_RENDERALLFORMATS, 0, 0)>
	endm

;; void Cls_OnDestroyClipboard(HWND hwnd)
HANDLE_WM_DESTROYCLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_DESTROYCLIPBOARD macro hwnd, fn
	exitm<fn(hwnd, WM_DESTROYCLIPBOARD, 0, 0)>
	endm

;; void Cls_OnDrawClipboard(HWND hwnd)
HANDLE_WM_DRAWCLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_DRAWCLIPBOARD macro hwnd, fn
	exitm<fn(hwnd, WM_DRAWCLIPBOARD, 0, 0)>
	endm

;; void Cls_OnPaintClipboard(HWND hwnd, HWND hwndCBViewer, LPPAINTSTRUCT lpPaintStruct)
HANDLE_WM_PAINTCLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), GlobalLock(lParam), GlobalUnlock(lParam), 0)>
	endm

FORWARD_WM_PAINTCLIPBOARD macro hwnd, hwndCBViewer, lpPaintStruct, fn
	exitm<fn(hwnd, WM_PAINTCLIPBOARD, (hwndCBViewer), lpPaintStruct)>
	endm

;; void Cls_OnSizeClipboard(HWND hwnd, HWND hwndCBViewer, LPRECT lprc)
HANDLE_WM_SIZECLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), GlobalLock(lParam), GlobalUnlock(lParam), 0)>
	endm

FORWARD_WM_SIZECLIPBOARD macro hwnd, hwndCBViewer, lprc, fn
	exitm<fn(hwnd, WM_SIZECLIPBOARD, hwndCBViewer, lprc)>
	endm

;; void Cls_OnVScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos)
HANDLE_WM_VSCROLLCLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_VSCROLLCLIPBOARD macro hwnd, hwndCBViewer, code, pos, fn
	exitm<fn(hwnd, WM_VSCROLLCLIPBOARD, hwndCBViewer, MAKELPARAM((code), (pos)))>
	endm

;; void Cls_OnHScrollClipboard(HWND hwnd, HWND hwndCBViewer, UINT code, int pos)
HANDLE_WM_HSCROLLCLIPBOARD macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_HSCROLLCLIPBOARD macro hwnd, hwndCBViewer, code, pos, fn
	exitm<fn(hwnd, WM_HSCROLLCLIPBOARD, hwndCBViewer, MAKELPARAM((code), (pos)))>
	endm

;; void Cls_OnAskCBFormatName(HWND hwnd, int cchMax, LPTSTR rgchName)
HANDLE_WM_ASKCBFORMATNAME macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, 0)>
	endm

FORWARD_WM_ASKCBFORMATNAME macro hwnd, cchMax, rgchName, fn
	exitm<fn(hwnd, WM_ASKCBFORMATNAME, cchMax, rgchName)>
	endm

;; void Cls_OnChangeCBChain(HWND hwnd, HWND hwndRemove, HWND hwndNext)
HANDLE_WM_CHANGECBCHAIN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, 0)>
	endm

FORWARD_WM_CHANGECBCHAIN macro hwnd, hwndRemove, hwndNext, fn
	exitm<fn(hwnd, WM_CHANGECBCHAIN, (hwndRemove), (hwndNext))>
	endm

;; BOOL Cls_OnSetCursor(HWND hwnd, HWND hwndCursor, UINT codeHitTest, UINT msg)
HANDLE_WM_SETCURSOR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), HIWORD(lParam))>
	endm

FORWARD_WM_SETCURSOR macro hwnd, hwndCursor, codeHitTest, msg, fn
	exitm<fn(hwnd, WM_SETCURSOR, (hwndCursor), MAKELPARAM((codeHitTest), (msg)))>
	endm

;; void Cls_OnSysCommand(HWND hwnd, UINT cmd, int x, int y)
HANDLE_WM_SYSCOMMAND macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_SYSCOMMAND macro hwnd, cmd, x, y, fn
	exitm<fn(hwnd, WM_SYSCOMMAND, (cmd), MAKELPARAM((x), (y)))>
	endm

;; HWND Cls_MDICreate(HWND hwnd, LPMDICREATESTRUCT lpmcs)
HANDLE_WM_MDICREATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam)>
	endm

FORWARD_WM_MDICREATE macro hwnd, lpmcs, fn
	exitm<fn(hwnd, WM_MDICREATE, 0, lpmcs)>
	endm

;; void Cls_MDIDestroy(HWND hwnd, HWND hwndDestroy)
HANDLE_WM_MDIDESTROY macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, 0)>
	endm

FORWARD_WM_MDIDESTROY macro hwnd, hwndDestroy, fn
	exitm<fn(hwnd, WM_MDIDESTROY, hwndDestroy, 0)>
	endm

;; NOTE: Usable only by MDI client windows
;; void Cls_MDIActivate(HWND hwnd, BOOL fActive, HWND hwndActivate, HWND hwndDeactivate)
HANDLE_WM_MDIACTIVATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (lParam == hwnd), (lParam), (wParam), 0)>
	endm

FORWARD_WM_MDIACTIVATE macro hwnd, fActive, hwndActivate, hwndDeactivate, fn
	exitm<fn(hwnd, WM_MDIACTIVATE, (hwndDeactivate), (hwndActivate))>
	endm

;; void Cls_MDIRestore(HWND hwnd, HWND hwndRestore)
HANDLE_WM_MDIRESTORE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), 0)>
	endm

FORWARD_WM_MDIRESTORE macro hwnd, hwndRestore, fn
	exitm<fn(hwnd, WM_MDIRESTORE, (hwndRestore), 0)>
	endm

;; HWND Cls_MDINext(HWND hwnd, HWND hwndCur, BOOL fPrev)
HANDLE_WM_MDINEXT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), lParam)>
	endm

FORWARD_WM_MDINEXT macro hwnd, hwndCur, fPrev, fn
	exitm<fn(hwnd ,WM_MDINEXT, (hwndCur), (fPrev))>
	endm

;; void Cls_MDIMaximize(HWND hwnd, HWND hwndMaximize)
HANDLE_WM_MDIMAXIMIZE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), 0)>
	endm

FORWARD_WM_MDIMAXIMIZE macro hwnd, hwndMaximize, fn
	exitm<fn(hwnd, WM_MDIMAXIMIZE, (hwndMaximize), 0)>
	endm

;; BOOL Cls_MDITile(HWND hwnd, UINT cmd)
HANDLE_WM_MDITILE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam))>
	endm

FORWARD_WM_MDITILE macro hwnd, cmd, fn
	exitm<fn(hwnd, WM_MDITILE, (cmd), 0)>
	endm

;; BOOL Cls_MDICascade(HWND hwnd, UINT cmd)
HANDLE_WM_MDICASCADE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam))>
	endm

FORWARD_WM_MDICASCADE macro hwnd, cmd, fn
	exitm<fn(hwnd, WM_MDICASCADE, (cmd), 0)>
	endm

;; void Cls_MDIIconArrange(HWND hwnd)
HANDLE_WM_MDIICONARRANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_MDIICONARRANGE macro hwnd, fn
	exitm<fn(hwnd, WM_MDIICONARRANGE, 0, 0)>
	endm

;; HWND Cls_MDIGetActive(HWND hwnd)
HANDLE_WM_MDIGETACTIVE macro hwnd, wParam, lParam, fn
	exitm<>
	endm
FORWARD_WM_MDIGETACTIVE macro hwnd, fn
	exitm<fn(hwnd, WM_MDIGETACTIVE, 0, 0)>
	endm

;; HMENU Cls_MDISetMenu(HWND hwnd, BOOL fRefresh, HMENU hmenuFrame, HMENU hmenuWindow)
HANDLE_WM_MDISETMENU macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), (wParam), (lParam))>
	endm

FORWARD_WM_MDISETMENU macro hwnd, fRefresh, hmenuFrame, hmenuWindow, fn
	exitm<fn(hwnd, WM_MDISETMENU, ((fRefresh) ? (hmenuFrame) : 0), (hmenuWindow))>
	endm

;; void Cls_OnChildActivate(HWND hwnd)
HANDLE_WM_CHILDACTIVATE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_CHILDACTIVATE macro hwnd, fn
	exitm<fn(hwnd, WM_CHILDACTIVATE, 0, 0)>
	endm

;; BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
HANDLE_WM_INITDIALOG macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), lParam)>
	endm

FORWARD_WM_INITDIALOG macro hwnd, hwndFocus, lParam, fn
	exitm<fn(hwnd, WM_INITDIALOG, (hwndFocus), (lParam))>
	endm

;; HWND Cls_OnNextDlgCtl(HWND hwnd, HWND hwndSetFocus, BOOL fNext)
HANDLE_WM_NEXTDLGCTL macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), (lParam))>
	endm

FORWARD_WM_NEXTDLGCTL macro hwnd, hwndSetFocus, fNext, fn
	exitm<fn(hwnd, WM_NEXTDLGCTL, (hwndSetFocus), (fNext))>
	endm

;; void Cls_OnParentNotify(HWND hwnd, UINT msg, HWND hwndChild, int idChild)
HANDLE_WM_PARENTNOTIFY macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(wParam), (lParam), HIWORD(wParam), 0)>
	endm

FORWARD_WM_PARENTNOTIFY macro hwnd, msg, hwndChild, idChild, fn
	exitm<fn(hwnd, WM_PARENTNOTIFY, MAKEWPARAM(msg, idChild), (hwndChild))>
	endm

;; void Cls_OnEnterIdle(HWND hwnd, UINT source, HWND hwndSource)
HANDLE_WM_ENTERIDLE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), (lParam), 0)>
	endm

FORWARD_WM_ENTERIDLE macro hwnd, source, hwndSource, fn
	exitm<fn(hwnd, WM_ENTERIDLE, (source), (hwndSource))>
	endm

;; UINT Cls_OnGetDlgCode(HWND hwnd, LPMSG lpmsg)
HANDLE_WM_GETDLGCODE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (lParam))>
	endm

FORWARD_WM_GETDLGCODE macro hwnd, lpmsg, fn
	exitm<fn(hwnd, WM_GETDLGCODE, (lpmsg ? lpmsg->wParam : 0), (lpmsg))>
	endm

;; HBRUSH Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type)
HANDLE_WM_CTLCOLORMSGBOX macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_MSGBOX)>
	endm

FORWARD_WM_CTLCOLORMSGBOX macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORMSGBOX, (hdc), (hwndChild))>
	endm

HANDLE_WM_CTLCOLOREDIT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_EDIT)>
	endm

FORWARD_WM_CTLCOLOREDIT macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLOREDIT, (hdc), (hwndChild))>
	endm

HANDLE_WM_CTLCOLORLISTBOX macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_LISTBOX)>
	endm

FORWARD_WM_CTLCOLORLISTBOX macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORLISTBOX, (hdc), (hwndChild))>
	endm

HANDLE_WM_CTLCOLORBTN macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_BTN)>
	endm

FORWARD_WM_CTLCOLORBTN macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORBTN, hdc, hwndChild)>
	endm

HANDLE_WM_CTLCOLORDLG macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_DLG)>
	endm

FORWARD_WM_CTLCOLORDLG macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORDLG, hdc, hwndChild)>
	endm

HANDLE_WM_CTLCOLORSCROLLBAR macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_SCROLLBAR)>
	endm

FORWARD_WM_CTLCOLORSCROLLBAR macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORSCROLLBAR, hdc, hwndChild)>
	endm

HANDLE_WM_CTLCOLORSTATIC macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, wParam, lParam, CTLCOLOR_STATIC)>
	endm

FORWARD_WM_CTLCOLORSTATIC macro hwnd, hdc, hwndChild, fn
	exitm<fn(hwnd, WM_CTLCOLORSTATIC, hdc, hwndChild)>
	endm

;; void Cls_OnSetFont(HWND hwndCtl, HFONT hfont, BOOL fRedraw)
HANDLE_WM_SETFONT macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), (lParam), 0)>
	endm

FORWARD_WM_SETFONT macro hwnd, hfont, fRedraw, fn
	exitm<fn(hwnd, WM_SETFONT, (hfont), (fRedraw))>
	endm

;; HFONT Cls_OnGetFont(HWND hwnd)
HANDLE_WM_GETFONT macro hwnd, wParam, lParam, fn
	exitm<>
	endm
FORWARD_WM_GETFONT macro hwnd, fn
	exitm<fn(hwnd, WM_GETFONT, 0, 0)>
	endm

;; void Cls_OnDrawItem(HWND hwnd, DRAWITEMSTRUCT * lpDrawItem)
HANDLE_WM_DRAWITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_DRAWITEM macro hwnd, lpDrawItem, fn
	exitm<fn(hwnd, WM_DRAWITEM, ((lpDrawItem).CtlID), lpDrawItem)>
	endm

;; void Cls_OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT * lpMeasureItem)
HANDLE_WM_MEASUREITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_MEASUREITEM macro hwnd, lpMeasureItem, fn
	exitm<fn(hwnd, WM_MEASUREITEM, lpMeasureItem.CtlID, lpMeasureItem)>
	endm

;; void Cls_OnDeleteItem(HWND hwnd, DELETEITEMSTRUCT * lpDeleteItem)
HANDLE_WM_DELETEITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam, 0)>
	endm

FORWARD_WM_DELETEITEM macro hwnd, lpDeleteItem, fn
	exitm<fn(hwnd, WM_DELETEITEM, lpDeleteItem.CtlID, lpDeleteItem)>
	endm

;; int Cls_OnCompareItem(HWND hwnd, COMPAREITEMSTRUCT * lpCompareItem)
HANDLE_WM_COMPAREITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, lParam)>
	endm

FORWARD_WM_COMPAREITEM macro hwnd, lpCompareItem, fn
	exitm<fn(hwnd, WM_COMPAREITEM, lpCompareItem.CtlID, lpCompareItem)>
	endm

;; int Cls_OnVkeyToItem(HWND hwnd, UINT vk, HWND hwndListbox, int iCaret)
HANDLE_WM_VKEYTOITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(wParam), (lParam), HIWORD(wParam))>
	endm

FORWARD_WM_VKEYTOITEM macro hwnd, vk, hwndListBox, iCaret, fn
	exitm<fn(hwnd, WM_VKEYTOITEM, MAKEWPARAM((vk), (iCaret)), (hwndListBox))>
	endm

;; int Cls_OnCharToItem(HWND hwnd, UINT ch, HWND hwndListbox, int iCaret)
HANDLE_WM_CHARTOITEM macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, LOWORD(wParam), (lParam), HIWORD(wParam))>
	endm

FORWARD_WM_CHARTOITEM macro hwnd, h, hwndListBox, iCaret, fn
	exitm<fn(hwnd, WM_CHARTOITEM, MAKEWPARAM((h), (iCaret)), (hwndListBox))>
	endm

;; void Cls_OnQueueSync(HWND hwnd)
HANDLE_WM_QUEUESYNC macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, 0)>
	endm

FORWARD_WM_QUEUESYNC macro hwnd, fn
	exitm<fn(hwnd, WM_QUEUESYNC, 0, 0)>
	endm

if (WINVER GE 0x030a)
;; void Cls_OnCommNotify(HWND hwnd, int cid, UINT flags)
HANDLE_WM_COMMNOTIFY macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), LOWORD(lParam), 0)>
	endm

FORWARD_WM_COMMNOTIFY macro hwnd, cid, flags, fn
	exitm<fn(hwnd, WM_COMMNOTIFY, (cid), MAKELPARAM((flags), 0))>
	endm
endif

;; void Cls_OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen)
HANDLE_WM_DISPLAYCHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), LOWORD(lParam), HIWORD(wParam), 0)>
	endm

FORWARD_WM_DISPLAYCHANGE macro hwnd, bitsPerPixel, cxScreen, cyScreen, fn
	exitm<fn(hwnd, WM_DISPLAYCHANGE, (bitsPerPixel), MAKELPARAM((cxScreen), (cyScreen)))>
	endm

;; BOOL Cls_OnDeviceChange(HWND hwnd, UINT uEvent, DWORD dwEventData)
HANDLE_WM_DEVICECHANGE macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), (wParam))>
	endm

FORWARD_WM_DEVICECHANGE macro hwnd, uEvent, dwEventData, fn
	exitm<fn(hwnd, WM_DEVICECHANGE, (uEvent), (dwEventData))>
	endm

;; void Cls_OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)
HANDLE_WM_CONTEXTMENU macro hwnd, wParam, lParam, fn
	exitm<fn(hwnd, (wParam), LOWORD(lParam), HIWORD(lParam), 0)>
	endm

FORWARD_WM_CONTEXTMENU macro hwnd, hwndContext, xPos, yPos, fn
	exitm<fn(hwnd, WM_CONTEXTMENU, (hwndContext), MAKELPARAM((xPos), (yPos)))>
	endm

;;***** Static control message APIs *****************************************

Static_Enable macro hwndCtl, fEnable
	exitm<EnableWindow((hwndCtl), (fEnable))>
	endm

Static_GetText macro hwndCtl, lpch, cchMax
	exitm<GetWindowText((hwndCtl), (lpch), (cchMax))>
	endm
Static_GetTextLength macro hwndCtl
	exitm<GetWindowTextLength(hwndCtl)>
	endm
Static_SetText macro hwndCtl, lpsz
	exitm<SetWindowText((hwndCtl), (lpsz))>
	endm

Static_SetIcon macro hwndCtl, hIcon
	exitm<(SNDMSG((hwndCtl), STM_SETICON, (hIcon), 0))>
	endm
Static_GetIcon macro hwndCtl, hIcon
	exitm<(SNDMSG((hwndCtl), STM_GETICON, 0, 0))>
	endm

;;***** Button control message APIs *****************************************

Button_Enable proto fastcall hwndCtl:HWND, fEnable:BOOL {
	EnableWindow(hwndCtl, fEnable)
	}

Button_GetText macro hwndCtl, lpch, cchMax
	exitm<GetWindowText((hwndCtl), (lpch), (cchMax))>
	endm
Button_GetTextLength proto fastcall hwndCtl:HWND {
	GetWindowTextLength(hwndCtl)
	}
Button_SetText proto fastcall hwndCtl:HWND, lpsz:abs {
	SetWindowText(hwndCtl, lpsz)
	}
Button_GetCheck proto fastcall hwndCtl:HWND {
	SNDMSG(hwndCtl, BM_GETCHECK, 0, 0)
	}
Button_SetCheck proto fastcall hwndCtl:HWND, check:abs {
	SNDMSG(hwndCtl, BM_SETCHECK, check, 0)
	}

Button_GetState macro hwndCtl
	exitm<(SNDMSG((hwndCtl), BM_GETSTATE, 0, 0))>
	endm
Button_SetState macro hwndCtl, state
	exitm<(SNDMSG((hwndCtl), BM_SETSTATE, (state), 0))>
	endm

Button_SetStyle macro hwndCtl, style, fRedraw
	exitm<(SNDMSG((hwndCtl), BM_SETSTYLE, LOWORD(style), MAKELPARAM(((fRedraw) ? TRUE : FALSE), 0)))>
	endm

;;***** Edit control message APIs *******************************************

Edit_Enable macro hwndCtl, fEnable
	exitm<EnableWindow((hwndCtl), (fEnable))>
	endm

Edit_GetText macro hwndCtl, lpch, cchMax
	exitm<GetWindowText((hwndCtl), (lpch), (cchMax))>
	endm
Edit_GetTextLength macro hwndCtl
	exitm<GetWindowTextLength(hwndCtl)>
	endm
Edit_SetText proto fastcall hwndCtl:HWND, lpsz:abs {
	SetWindowText(hwndCtl, lpsz)
	}

Edit_LimitText macro hwndCtl, cchMax
	exitm<(SNDMSG((hwndCtl), EM_LIMITTEXT, (cchMax), 0))>
	endm

Edit_GetLineCount macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_GETLINECOUNT, 0, 0))>
	endm
ifndef _MAC
Edit_GetLine macro hwndCtl, line, lpch, cchMax
	mov dword ptr lpch,cchMax
	exitm<SNDMSG((hwndCtl), EM_GETLINE, (line), (lpch))>
	endm
else
Edit_GetLine macro hwndCtl, line, lpch, cchMax
	mov word ptr lpch,cchMax
	exitm<SNDMSG((hwndCtl), EM_GETLINE, (line), (lpch))>
	endm
endif

Edit_GetRect macro hwndCtl, lprc
	exitm<(SNDMSG((hwndCtl), EM_GETRECT, 0, (lprc)))>
	endm
Edit_SetRect macro hwndCtl, lprc
	exitm<(SNDMSG((hwndCtl), EM_SETRECT, 0, (lprc)))>
	endm
Edit_SetRectNoPaint macro hwndCtl, lprc
	exitm<(SNDMSG((hwndCtl), EM_SETRECTNP, 0, (lprc)))>
	endm

Edit_GetSel macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_GETSEL, 0, 0))>
	endm
Edit_SetSel macro hwndCtl, ichStart, ichEnd
	exitm<(SNDMSG((hwndCtl), EM_SETSEL, (ichStart), (ichEnd)))>
	endm
Edit_ReplaceSel macro hwndCtl, lpszReplace
	exitm<(SNDMSG((hwndCtl), EM_REPLACESEL, 0, (lpszReplace)))>
	endm

Edit_GetModify macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_GETMODIFY, 0, 0))>
	endm
Edit_SetModify macro hwndCtl, fModified
	exitm<(SNDMSG((hwndCtl), EM_SETMODIFY, (fModified), 0))>
	endm

Edit_ScrollCaret macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_SCROLLCARET, 0, 0))>
	endm

Edit_LineFromChar macro hwndCtl, ich
	exitm<(SNDMSG((hwndCtl), EM_LINEFROMCHAR, (ich), 0))>
	endm
Edit_LineIndex macro hwndCtl, line
	exitm<(SNDMSG((hwndCtl), EM_LINEINDEX, (line), 0))>
	endm
Edit_LineLength macro hwndCtl, line
	exitm<(SNDMSG((hwndCtl), EM_LINELENGTH, (line), 0))>
	endm

Edit_Scroll macro hwndCtl, v, h
	exitm<(SNDMSG((hwndCtl), EM_LINESCROLL, (h), (v)))>
	endm

Edit_CanUndo macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_CANUNDO, 0, 0))>
	endm
Edit_Undo macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_UNDO, 0, 0))>
	endm
Edit_EmptyUndoBuffer macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_EMPTYUNDOBUFFER, 0, 0))>
	endm

Edit_SetPasswordChar macro hwndCtl, h
	exitm<(SNDMSG((hwndCtl), EM_SETPASSWORDCHAR, (h), 0))>
	endm

Edit_SetTabStops macro hwndCtl, cTabs, lpTabs
	exitm<(SNDMSG((hwndCtl), EM_SETTABSTOPS, (cTabs), (lpTabs)))>
	endm

Edit_FmtLines macro hwndCtl, fAddEOL
	exitm<(SNDMSG((hwndCtl), EM_FMTLINES, (fAddEOL), 0))>
	endm

Edit_GetHandle macro hwndCtl
	exitm<((HLOCAL)SNDMSG((hwndCtl), EM_GETHANDLE, 0, 0))>
	endm
Edit_SetHandle macro hwndCtl, h
	exitm<(SNDMSG((hwndCtl), EM_SETHANDLE, (h), 0))>
	endm

if (WINVER GE 0x030a)
Edit_GetFirstVisibleLine macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_GETFIRSTVISIBLELINE, 0, 0))>
	endm

Edit_SetReadOnly macro hwndCtl, fReadOnly
	exitm<(SNDMSG((hwndCtl), EM_SETREADONLY, (fReadOnly), 0))>
	endm

Edit_GetPasswordChar macro hwndCtl
	exitm<(SNDMSG((hwndCtl), EM_GETPASSWORDCHAR, 0, 0))>
	endm

Edit_SetWordBreakProc macro hwndCtl, lpfnWordBreak
	exitm<(SNDMSG((hwndCtl), EM_SETWORDBREAKPROC, 0, (lpfnWordBreak)))>
	endm
Edit_GetWordBreakProc macro hwndCtl
	exitm<SNDMSG((hwndCtl), EM_GETWORDBREAKPROC, 0, 0)>
	endm
endif ;; WINVER GE 0x030a

;;***** ScrollBar control message APIs **************************************

;; NOTE: flags parameter is a collection of ESB_* values, NOT a boolean!
ScrollBar_Enable macro hwndCtl, flags
	exitm<EnableScrollBar((hwndCtl), SB_CTL, (flags))>
	endm

ScrollBar_Show macro hwndCtl, fShow
	exitm<ShowWindow((hwndCtl), (fShow) ? SW_SHOWNORMAL : SW_HIDE)>
	endm

ScrollBar_SetPos macro hwndCtl, pos, fRedraw
	exitm<SetScrollPos((hwndCtl), SB_CTL, (pos), (fRedraw))>
	endm
ScrollBar_GetPos macro hwndCtl
	exitm<GetScrollPos((hwndCtl), SB_CTL)>
	endm

ScrollBar_SetRange macro hwndCtl, posMin, posMax, fRedraw
	exitm<SetScrollRange((hwndCtl), SB_CTL, (posMin), (posMax), (fRedraw))>
	endm
ScrollBar_GetRange macro hwndCtl, lpposMin, lpposMax
	exitm<GetScrollRange((hwndCtl), SB_CTL, (lpposMin), (lpposMax))>
	endm

;;***** ListBox control message APIs ****************************************

ListBox_Enable macro hwndCtl, fEnable
	exitm<EnableWindow((hwndCtl), (fEnable))>
	endm

ListBox_GetCount macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETCOUNT, 0, 0))>
	endm
ListBox_ResetContent macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_RESETCONTENT, 0, 0))>
	endm

ListBox_AddString macro hwndCtl, lpsz
	exitm<(SNDMSG((hwndCtl), LB_ADDSTRING, 0, (lpsz)))>
	endm
ListBox_InsertString macro hwndCtl, index, lpsz
	exitm<(SNDMSG((hwndCtl), LB_INSERTSTRING, (index), (lpsz)))>
	endm

ListBox_AddItemData macro hwndCtl, data
	exitm<(SNDMSG((hwndCtl), LB_ADDSTRING, 0, (data)))>
	endm
ListBox_InsertItemData macro hwndCtl, index, data
	exitm<(SNDMSG((hwndCtl), LB_INSERTSTRING, (index), (data)))>
	endm

ListBox_DeleteString macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_DELETESTRING, (index), 0))>
	endm

ListBox_GetTextLen macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_GETTEXTLEN, (index), 0))>
	endm
ListBox_GetText macro hwndCtl, index, lpszBuffer
	exitm<(SNDMSG((hwndCtl), LB_GETTEXT, (index), (lpszBuffer)))>
	endm

ListBox_GetItemData macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_GETITEMDATA, (index), 0))>
	endm
ListBox_SetItemData macro hwndCtl, index, data
	exitm<(SNDMSG((hwndCtl), LB_SETITEMDATA, (index), (data)))>
	endm

if (WINVER GE 0x030a)
ListBox_FindString macro hwndCtl, indexStart, lpszFind
	exitm<(SNDMSG((hwndCtl), LB_FINDSTRING, (indexStart), (lpszFind)))>
	endm
ListBox_FindItemData macro hwndCtl, indexStart, data
	exitm<(SNDMSG((hwndCtl), LB_FINDSTRING, (indexStart), (data)))>
	endm

ListBox_SetSel macro hwndCtl, fSelect, index
	exitm<(SNDMSG((hwndCtl), LB_SETSEL, (fSelect), (index)))>
	endm
ListBox_SelItemRange macro hwndCtl, fSelect, first, last
	exitm<(SNDMSG((hwndCtl), LB_SELITEMRANGE, (fSelect), MAKELPARAM((first), (last))))>
	endm

ListBox_GetCurSel macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETCURSEL, 0, 0))>
	endm
ListBox_SetCurSel macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_SETCURSEL, (index), 0))>
	endm

ListBox_SelectString macro hwndCtl, indexStart, lpszFind
	exitm<(SNDMSG((hwndCtl), LB_SELECTSTRING, (indexStart), (lpszFind)))>
	endm
ListBox_SelectItemData macro hwndCtl, indexStart, data
	exitm<(SNDMSG((hwndCtl), LB_SELECTSTRING, (indexStart), (data)))>
	endm

ListBox_GetSel macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_GETSEL, (index), 0))>
	endm
ListBox_GetSelCount macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETSELCOUNT, 0, 0))>
	endm
ListBox_GetTopIndex macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETTOPINDEX, 0, 0))>
	endm
ListBox_GetSelItems macro hwndCtl, cItems, lpItems
	exitm<(SNDMSG((hwndCtl), LB_GETSELITEMS, (cItems), (lpItems)))>
	endm

ListBox_SetTopIndex macro hwndCtl, indexTop
	exitm<(SNDMSG((hwndCtl), LB_SETTOPINDEX, (indexTop), 0))>
	endm

ListBox_SetColumnWidth macro hwndCtl, cxColumn
	exitm<(SNDMSG((hwndCtl), LB_SETCOLUMNWIDTH, (cxColumn), 0))>
	endm
ListBox_GetHorizontalExtent macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETHORIZONTALEXTENT, 0, 0))>
	endm
ListBox_SetHorizontalExtent macro hwndCtl, cxExtent
	exitm<(SNDMSG((hwndCtl), LB_SETHORIZONTALEXTENT, (cxExtent), 0))>
	endm

ListBox_SetTabStops macro hwndCtl, cTabs, lpTabs
	exitm<(SNDMSG((hwndCtl), LB_SETTABSTOPS, (cTabs), (lpTabs)))>
	endm

ListBox_GetItemRect macro hwndCtl, index, lprc
	exitm<(SNDMSG((hwndCtl), LB_GETITEMRECT, (index), (lprc)))>
	endm

ListBox_SetCaretIndex macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_SETCARETINDEX, (index), 0))>
	endm
ListBox_GetCaretIndex macro hwndCtl
	exitm<(SNDMSG((hwndCtl), LB_GETCARETINDEX, 0, 0))>
	endm

ListBox_FindStringExact macro hwndCtl, indexStart, lpszFind
	exitm<(SNDMSG((hwndCtl), LB_FINDSTRINGEXACT, (indexStart), (lpszFind)))>
	endm

ListBox_SetItemHeight macro hwndCtl, index, cy
	exitm<(SNDMSG((hwndCtl), LB_SETITEMHEIGHT, (index), MAKELPARAM((cy), 0)))>
	endm
ListBox_GetItemHeight macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), LB_GETITEMHEIGHT, (index), 0))>
	endm
endif  ;; WINVER GE 0x030a

ListBox_Dir macro hwndCtl, attrs, lpszFileSpec
	exitm<(SNDMSG((hwndCtl), LB_DIR, (attrs), (lpszFileSpec)))>
	endm

;;***** ComboBox control message APIs ***************************************

ComboBox_Enable macro hwndCtl, fEnable
	exitm<EnableWindow((hwndCtl), (fEnable))>
	endm

ComboBox_GetText macro hwndCtl, lpch, cchMax
	exitm<GetWindowText((hwndCtl), (lpch), (cchMax))>
	endm
ComboBox_GetTextLength macro hwndCtl
	exitm<GetWindowTextLength(hwndCtl)>
	endm
ComboBox_SetText macro hwndCtl, lpsz
	exitm<SetWindowText((hwndCtl), (lpsz))>
	endm

ComboBox_LimitText macro hwndCtl, cchLimit
	exitm<(SNDMSG((hwndCtl), CB_LIMITTEXT, (cchLimit), 0))>
	endm

ComboBox_GetEditSel macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETEDITSEL, 0, 0))>
	endm
ComboBox_SetEditSel macro hwndCtl, ichStart, ichEnd
	exitm<(SNDMSG((hwndCtl), CB_SETEDITSEL, 0, MAKELPARAM((ichStart), (ichEnd))))>
	endm

ComboBox_GetCount macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETCOUNT, 0, 0))>
	endm
ComboBox_ResetContent macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_RESETCONTENT, 0, 0))>
	endm

ComboBox_AddString macro hwndCtl, lpsz
	exitm<(SNDMSG((hwndCtl), CB_ADDSTRING, 0, (lpsz)))>
	endm
ComboBox_InsertString macro hwndCtl, index, lpsz
	exitm<(SNDMSG((hwndCtl), CB_INSERTSTRING, (index), (lpsz)))>
	endm

ComboBox_AddItemData macro hwndCtl, data
	exitm<(SNDMSG((hwndCtl), CB_ADDSTRING, 0, (data)))>
	endm
ComboBox_InsertItemData macro hwndCtl, index, data
	exitm<(SNDMSG((hwndCtl), CB_INSERTSTRING, (index), (data)))>
	endm

ComboBox_DeleteString macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), CB_DELETESTRING, (index), 0))>
	endm

ComboBox_GetLBTextLen macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), CB_GETLBTEXTLEN, (index), 0))>
	endm
ComboBox_GetLBText macro hwndCtl, index, lpszBuffer
	exitm<(SNDMSG((hwndCtl), CB_GETLBTEXT, (index), (lpszBuffer)))>
	endm

ComboBox_GetItemData macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), CB_GETITEMDATA, (index), 0))>
	endm
ComboBox_SetItemData macro hwndCtl, index, data
	exitm<(SNDMSG((hwndCtl), CB_SETITEMDATA, (index), (data)))>
	endm

ComboBox_FindString macro hwndCtl, indexStart, lpszFind
	exitm<(SNDMSG((hwndCtl), CB_FINDSTRING, (indexStart), (lpszFind)))>
	endm
ComboBox_FindItemData macro hwndCtl, indexStart, data
	exitm<(SNDMSG((hwndCtl), CB_FINDSTRING, (indexStart), (data)))>
	endm

ComboBox_GetCurSel macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETCURSEL, 0, 0))>
	endm
ComboBox_SetCurSel macro hwndCtl, index
	exitm<(SNDMSG((hwndCtl), CB_SETCURSEL, (index), 0))>
	endm

ComboBox_SelectString macro hwndCtl, indexStart, lpszSelect
	exitm<(SNDMSG((hwndCtl), CB_SELECTSTRING, (indexStart), (lpszSelect)))>
	endm
ComboBox_SelectItemData macro hwndCtl, indexStart, data
	exitm<(SNDMSG((hwndCtl), CB_SELECTSTRING, (indexStart), (data)))>
	endm

ComboBox_Dir macro hwndCtl, attrs, lpszFileSpec
	exitm<(SNDMSG((hwndCtl), CB_DIR, (attrs), (lpszFileSpec)))>
	endm

ComboBox_ShowDropdown macro hwndCtl, fShow
	exitm<(SNDMSG((hwndCtl), CB_SHOWDROPDOWN, (fShow), 0))>
	endm

if (WINVER GE 0x030a)
ComboBox_FindStringExact macro hwndCtl, indexStart, lpszFind
	exitm<(SNDMSG((hwndCtl), CB_FINDSTRINGEXACT, (indexStart), (lpszFind)))>
	endm

ComboBox_GetDroppedState macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETDROPPEDSTATE, 0, 0))>
	endm
ComboBox_GetDroppedControlRect macro hwndCtl, lprc
	exitm<(SNDMSG((hwndCtl), CB_GETDROPPEDCONTROLRECT, 0, (lprc)))>
	endm

ComboBox_GetItemHeight macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETITEMHEIGHT, 0, 0))>
	endm
ComboBox_SetItemHeight macro hwndCtl, index, cyItem
	exitm<(SNDMSG((hwndCtl), CB_SETITEMHEIGHT, (index), cyItem))>
	endm

ComboBox_GetExtendedUI macro hwndCtl
	exitm<(SNDMSG((hwndCtl), CB_GETEXTENDEDUI, 0, 0))>
	endm
ComboBox_SetExtendedUI macro hwndCtl, flags
	exitm<(SNDMSG((hwndCtl), CB_SETEXTENDEDUI, (flags), 0))>
	endm
endif  ;; WINVER GE 0x030a

;;***** Alternate porting layer macros ***************************************

;; USER MESSAGES:

GET_WPARAM macro wp, lp
	exitm<(wp)>
	endm
GET_LPARAM macro wp, lp
	exitm<(lp)>
	endm

GET_X_LPARAM proto watcall lp:LPARAM {
	LOWORD(eax)
	retm<eax>
	}

GET_Y_LPARAM proto watcall lp:LPARAM {
	HIWORD(eax)
	retm<eax>
	}

GET_WM_ACTIVATE_STATE macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_ACTIVATE_FMINIMIZED macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_ACTIVATE_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_ACTIVATE_MPS macro s, fmin, hwnd
	exitm<MAKELONG((s), (fmin)), (hwnd)>
	endm


GET_WM_CHARTOITEM_CHAR macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_CHARTOITEM_POS macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_CHARTOITEM_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_CHARTOITEM_MPS macro h, pos, hwnd
	exitm<MAKELONG((pos), (h)), (hwnd)>
	endm


GET_WM_COMMAND_ID macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_COMMAND_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_COMMAND_CMD macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_COMMAND_MPS macro id, hwnd, cmd
	exitm<MAKELONG(id, cmd), (hwnd)>
	endm


WM_CTLCOLOR		equ 0x0019

GET_WM_CTLCOLOR_HDC macro wp, lp, msg
	exitm<(wp)>
	endm
GET_WM_CTLCOLOR_HWND macro wp, lp, msg
	exitm<(lp)>
	endm
GET_WM_CTLCOLOR_TYPE macro wp, lp, msg
	exitm<(msg - WM_CTLCOLORMSGBOX)>
	endm
GET_WM_CTLCOLOR_MSG macro type
	exitm<(WM_CTLCOLORMSGBOX+(type))>
	endm
GET_WM_CTLCOLOR_MPS macro hdc, hwnd, type
	exitm<(hdc),(hwnd)>
	endm



GET_WM_MENUSELECT_CMD macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_MENUSELECT_FLAGS macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_MENUSELECT_HMENU macro wp, lp
	exitm<(lp)>
	endm
GET_WM_MENUSELECT_MPS macro cmd, f, hmenu
	exitm<MAKELONG(cmd,f), (hmenu)>
	endm


;; Note: the following are for interpreting MDIclient to MDI child messages.
GET_WM_MDIACTIVATE_FACTIVATE macro hwnd, wp, lp
	exitm<(lp EQ hwnd)>
	endm
GET_WM_MDIACTIVATE_HWNDDEACT macro wp, lp
	exitm<(wp)>
	endm
GET_WM_MDIACTIVATE_HWNDACTIVATE macro wp, lp
	exitm<(lp)>
	endm
;; Note: the following is for sending to the MDI client window.
GET_WM_MDIACTIVATE_MPS macro f, hwndD, hwndA
	exitm<(hwndA),0>
	endm


GET_WM_MDISETMENU_MPS macro hmenuF, hmenuW
	exitm<hmenuF, hmenuW>
	endm

GET_WM_MENUCHAR_CHAR macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_MENUCHAR_HMENU macro wp, lp
	exitm<(lp)>
	endm
GET_WM_MENUCHAR_FMENU macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_MENUCHAR_MPS macro h, hmenu, f
	exitm<MAKELONG(h,f), (hmenu)>
	endm


GET_WM_PARENTNOTIFY_MSG macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_PARENTNOTIFY_ID macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_PARENTNOTIFY_HWNDCHILD macro wp, lp
	exitm<(lp)>
	endm
GET_WM_PARENTNOTIFY_X macro wp, lp
	exitm<LOWORD(lp)>
	endm
GET_WM_PARENTNOTIFY_Y macro wp, lp
	exitm<HIWORD(lp)>
	endm
GET_WM_PARENTNOTIFY_MPS macro msg, id, hwnd
	exitm<MAKELONG(id, msg), (hwnd)>
	endm

GET_WM_PARENTNOTIFY2_MPS macro msg, x, y
	exitm<MAKELONG(0, msg), MAKELONG(x, y)>
	endm


GET_WM_VKEYTOITEM_CODE macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_VKEYTOITEM_ITEM macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_VKEYTOITEM_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_VKEYTOITEM_MPS macro code, item, hwnd
	exitm<MAKELONG(item,code), (hwnd)>
	endm


GET_EM_SETSEL_START macro wp, lp
	exitm<wp>
	endm
GET_EM_SETSEL_END macro wp, lp
	exitm<(lp)>
	endm
GET_EM_SETSEL_MPS macro iStart, iEnd
	exitm<(iStart), (iEnd)>
	endm


GET_EM_LINESCROLL_MPS macro vert, horz
	exitm<horz,vert>
	endm

GET_WM_CHANGECBCHAIN_HWNDNEXT macro wp, lp
	exitm<(lp)>
	endm

GET_WM_HSCROLL_CODE macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_HSCROLL_POS macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_HSCROLL_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_HSCROLL_MPS macro code, pos, hwnd
	exitm<MAKELONG(code, pos), (hwnd)>
	endm


GET_WM_VSCROLL_CODE macro wp, lp
	exitm<LOWORD(wp)>
	endm
GET_WM_VSCROLL_POS macro wp, lp
	exitm<HIWORD(wp)>
	endm
GET_WM_VSCROLL_HWND macro wp, lp
	exitm<(lp)>
	endm
GET_WM_VSCROLL_MPS macro code, pos, hwnd
	exitm<MAKELONG(code, pos), (hwnd)>
	endm


;;***** C runtime porting macros ***************************************

_ncalloc		equ <calloc>
_nexpand		equ <_expand>
_ffree			equ <free>
_fmalloc		equ <malloc>
_fmemccpy		equ <_memccpy>
_fmemchr		equ <memchr>
_fmemcmp		equ <memcmp>
_fmemcpy		equ <memcpy>
_fmemicmp		equ <_memicmp>
_fmemmove		equ <memmove>
_fmemset		equ <memset>
_fmsize			equ <_msize>
_frealloc		equ <realloc>
_fstrcat		equ <strcat>
_fstrchr		equ <strchr>
_fstrcmp		equ <strcmp>
_fstrcpy		equ <strcpy>
_fstrcspn		equ <strcspn>
_fstrdup		equ <_strdup>
_fstricmp		equ <_stricmp>
_fstrlen		equ <strlen>
_fstrlwr		equ <_strlwr>
_fstrncat		equ <strncat>
_fstrncmp		equ <strncmp>
_fstrncpy		equ <strncpy>
_fstrnicmp		equ <_strnicmp>
_fstrnset		equ <_strnset>
_fstrpbrk		equ <strpbrk>
_fstrrchr		equ <strrchr>
_fstrrev		equ <_strrev>
_fstrset		equ <_strset>
_fstrspn		equ <strspn>
_fstrstr		equ <strstr>
_fstrtok		equ <strtok>
_fstrupr		equ <_strupr>
_nfree			equ <free>
_nmalloc		equ <malloc>
_nmsize			equ <_msize>
_nrealloc		equ <realloc>
_nstrdup		equ <_strdup>
hmemcpy			equ <MoveMemory>

DECLARE_HANDLE32	equ DECLARE_HANDLE

.pragma list(pop)
endif
