;
; USER procedure declarations, constant definitions and macros
;
include stdarg.inc
ifndef _WINBASE_
 include winbase.inc
endif

.xlist

ifndef _WINUSER_
_WINUSER_ equ 1

;;
;; Define API decoration for direct importing of DLL references.
;;

ifdef __PE__
option	dllimport:<user32>
endif

ifndef WINVER
WINVER	equ 0x0500	;; version 5.0
endif
ifndef _WIN32_WINDOWS
_WIN32_WINDOWS equ WINVER
endif
ifndef _WIN32_WINNT
_WIN32_WINNT equ _WIN32_WINDOWS
endif

ifndef NOUSER

HDWP			typedef HANDLE
MENUTEMPLATEA		equ <>
MENUTEMPLATEW		equ <>
ifdef _UNICODE
MENUTEMPLATE		typedef MENUTEMPLATEW
else
MENUTEMPLATE		typedef MENUTEMPLATEA
endif ;; UNICODE
LPMENUTEMPLATEA		typedef PVOID
LPMENUTEMPLATEW		typedef PVOID
ifdef _UNICODE
LPMENUTEMPLATE		typedef LPMENUTEMPLATEW
else
LPMENUTEMPLATE		typedef LPMENUTEMPLATEA
endif ;; UNICODE

WNDPROC_T typedef proto \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
WNDPROC typedef ptr WNDPROC_T

ifdef STRICT

DLGPROC_T typedef proto \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
DLGPROC typedef ptr DLGPROC_T
TIMERPROC_T typedef proto \
		      : HWND,
		      : UINT,
		      : UINT,
		      : DWORD
TIMERPROC typedef ptr TIMERPROC_T
GRAYSTRINGPROC_T typedef proto \
		      : HDC,
		      : LPARAM,
		      : SINT
GRAYSTRINGPROC typedef ptr GRAYSTRINGPROC_T
WNDENUMPROC_T typedef proto \
		      : HWND,
		      : LPARAM
WNDENUMPROC typedef ptr WNDENUMPROC_T
HOOKPROC_T typedef proto \
		  code: SINT,
		wParam: WPARAM,
		lParam: LPARAM
HOOKPROC typedef ptr HOOKPROC_T
SENDASYNCPROC_T typedef proto \
		      : HWND,
		      : UINT,
		      : DWORD,
		      : LRESULT
SENDASYNCPROC typedef ptr SENDASYNCPROC_T

PROPENUMPROCA_T typedef proto \
		      : HWND,
		      : LPCSTR,
		      : HANDLE
PROPENUMPROCA typedef ptr PROPENUMPROCA_T
PROPENUMPROCW_T typedef proto \
		      : HWND,
		      : LPCWSTR,
		      : HANDLE
PROPENUMPROCW typedef ptr PROPENUMPROCW_T

PROPENUMPROCEXA_T typedef proto \
		      : HWND,
		      : LPSTR,
		      : HANDLE,
		      : DWORD
PROPENUMPROCEXA typedef ptr PROPENUMPROCEXA_T
PROPENUMPROCEXW_T typedef proto \
		      : HWND,
		      : LPWSTR,
		      : HANDLE,
		      : DWORD
PROPENUMPROCEXW typedef ptr PROPENUMPROCEXW_T

EDITWORDBREAKPROCA_T typedef proto \
		  lpch: LPSTR,
	    ichCurrent: SINT,
		   cch: SINT,
		  code: SINT
EDITWORDBREAKPROCA typedef ptr EDITWORDBREAKPROCA_T
EDITWORDBREAKPROCW_T typedef proto \
		  lpch: LPWSTR,
	    ichCurrent: SINT,
		   cch: SINT,
		  code: SINT
EDITWORDBREAKPROCW typedef ptr EDITWORDBREAKPROCW_T

if(WINVER GE 0x0400)
DRAWSTATEPROC_T typedef proto \
		   hdc: HDC,
		 lData: LPARAM,
		 wData: WPARAM,
		     x: SINT,
		    cy: SINT
DRAWSTATEPROC typedef ptr DRAWSTATEPROC_T
endif ;; WINVER GE 0x0400
else ;; NOT STRICT

DLGPROC			typedef FARPROC
TIMERPROC		typedef FARPROC
GRAYSTRINGPROC		typedef FARPROC
WNDENUMPROC		typedef FARPROC
HOOKPROC		typedef FARPROC
SENDASYNCPROC		typedef FARPROC

EDITWORDBREAKPROCA	typedef FARPROC
EDITWORDBREAKPROCW	typedef FARPROC

PROPENUMPROCA		typedef FARPROC
PROPENUMPROCW		typedef FARPROC

PROPENUMPROCEXA		typedef FARPROC
PROPENUMPROCEXW		typedef FARPROC

if(WINVER GE 0x0400)
DRAWSTATEPROC		typedef FARPROC
endif ;; WINVER GE 0x0400
endif ;; NOT STRICT

ifdef _UNICODE
PROPENUMPROC		typedef PROPENUMPROCW
PROPENUMPROCEX		typedef PROPENUMPROCEXW
EDITWORDBREAKPROC	typedef EDITWORDBREAKPROCW
else  ;; NOT UNICODE
PROPENUMPROC		typedef PROPENUMPROCA
PROPENUMPROCEX		typedef PROPENUMPROCEXA
EDITWORDBREAKPROC	typedef EDITWORDBREAKPROCA
endif ;; UNICODE

ifdef STRICT

NAMEENUMPROCA_T typedef proto \
		      : LPSTR,
		      : LPARAM
NAMEENUMPROCA typedef ptr NAMEENUMPROCA_T
NAMEENUMPROCW_T typedef proto \
		      : LPWSTR,
		      : LPARAM
NAMEENUMPROCW typedef ptr NAMEENUMPROCW_T

WINSTAENUMPROCA		typedef NAMEENUMPROCA
DESKTOPENUMPROCA	typedef NAMEENUMPROCA
WINSTAENUMPROCW		typedef NAMEENUMPROCW
DESKTOPENUMPROCW	typedef NAMEENUMPROCW


else ;; NOT STRICT

NAMEENUMPROCA		typedef FARPROC
NAMEENUMPROCW		typedef FARPROC
WINSTAENUMPROCA		typedef FARPROC
DESKTOPENUMPROCA	typedef FARPROC
WINSTAENUMPROCW		typedef FARPROC
DESKTOPENUMPROCW	typedef FARPROC


endif ;; NOT STRICT

ifdef _UNICODE
WINSTAENUMPROC		typedef WINSTAENUMPROCW
DESKTOPENUMPROC		typedef DESKTOPENUMPROCW


else  ;; NOT UNICODE
WINSTAENUMPROC		typedef WINSTAENUMPROCA
DESKTOPENUMPROC		typedef DESKTOPENUMPROCA

endif ;; UNICODE

MAKEINTRESOURCEA macro i
	exitm<i>
	endm
MAKEINTRESOURCEW macro i
	exitm<i>
	endm
ifdef _UNICODE
MAKEINTRESOURCE		equ MAKEINTRESOURCEW
else
MAKEINTRESOURCE		equ MAKEINTRESOURCEA
endif ;; NOT UNICODE

ifndef NORESOURCE

;;
;; Predefined Resource Types
;;
RT_CURSOR		equ MAKEINTRESOURCE(1)
RT_BITMAP		equ MAKEINTRESOURCE(2)
RT_ICON			equ MAKEINTRESOURCE(3)
RT_MENU			equ MAKEINTRESOURCE(4)
RT_DIALOG		equ MAKEINTRESOURCE(5)
RT_STRING		equ MAKEINTRESOURCE(6)
RT_FONTDIR		equ MAKEINTRESOURCE(7)
RT_FONT			equ MAKEINTRESOURCE(8)
RT_ACCELERATOR		equ MAKEINTRESOURCE(9)
RT_RCDATA		equ MAKEINTRESOURCE(10)
RT_MESSAGETABLE		equ MAKEINTRESOURCE(11)

DIFFERENCE		equ 11
RT_GROUP_CURSOR		equ MAKEINTRESOURCE(RT_CURSOR + DIFFERENCE)
RT_GROUP_ICON		equ MAKEINTRESOURCE(RT_ICON + DIFFERENCE)
RT_VERSION		equ MAKEINTRESOURCE(16)
RT_DLGINCLUDE		equ MAKEINTRESOURCE(17)
if(WINVER GE 0x0400)
RT_PLUGPLAY		equ MAKEINTRESOURCE(19)
RT_VXD			equ MAKEINTRESOURCE(20)
RT_ANICURSOR		equ MAKEINTRESOURCE(21)
RT_ANIICON		equ MAKEINTRESOURCE(22)
endif ;; WINVER GE 0x0400
RT_HTML			equ MAKEINTRESOURCE(23)

endif ;; NOT NORESOURCE

;int
wvsprintfA proto _CType \
		      : LPSTR,
		      : LPCSTR,
	       arglist: PVOID
;int
wvsprintfW proto _CType \
		      : LPWSTR,
		      : LPCWSTR,
	       arglist: PVOID
ifdef _UNICODE
wvsprintf		equ <wvsprintfW>
else
wvsprintf		equ <wvsprintfA>
endif ;; NOT UNICODE

;int
wsprintfA proto _CDecl \
		      : LPSTR,
		      : LPCSTR,
		      : VARARG
;int
wsprintfW proto _CDecl \
		      : LPWSTR,
		      : LPCWSTR,
		      : VARARG
ifdef _UNICODE
wsprintf		equ <wsprintfW>
else
wsprintf		equ <wsprintfA>
endif ;; NOT UNICODE

ifndef NOSCROLL

;;
;; Scroll Bar Constants
;;
SB_HORZ			equ 0
SB_VERT			equ 1
SB_CTL			equ 2
SB_BOTH			equ 3

;;
;; Scroll Bar Commands
;;
SB_LINEUP		equ 0
SB_LINELEFT		equ 0
SB_LINEDOWN		equ 1
SB_LINERIGHT		equ 1
SB_PAGEUP		equ 2
SB_PAGELEFT		equ 2
SB_PAGEDOWN		equ 3
SB_PAGERIGHT		equ 3
SB_THUMBPOSITION	equ 4
SB_THUMBTRACK		equ 5
SB_TOP			equ 6
SB_LEFT			equ 6
SB_BOTTOM		equ 7
SB_RIGHT		equ 7
SB_ENDSCROLL		equ 8

endif ;; NOT NOSCROLL

ifndef NOSHOWWINDOW

;; begin_r_winuser

;;
;; ShowWindow() Commands
;;
SW_HIDE			equ 0
SW_SHOWNORMAL		equ 1
SW_NORMAL		equ 1
SW_SHOWMINIMIZED	equ 2
SW_SHOWMAXIMIZED	equ 3
SW_MAXIMIZE		equ 3
SW_SHOWNOACTIVATE	equ 4
SW_SHOW			equ 5
SW_MINIMIZE		equ 6
SW_SHOWMINNOACTIVE	equ 7
SW_SHOWNA		equ 8
SW_RESTORE		equ 9
SW_SHOWDEFAULT		equ 10
SW_FORCEMINIMIZE	equ 11
SW_MAX			equ 11

;;
;; Old ShowWindow() Commands
;;
HIDE_WINDOW		equ 0
SHOW_OPENWINDOW		equ 1
SHOW_ICONWINDOW		equ 2
SHOW_FULLSCREEN		equ 3
SHOW_OPENNOACTIVATE	equ 4

;;
;; Identifiers for the WM_SHOWWINDOW message
;;
SW_PARENTCLOSING	equ 1
SW_OTHERZOOM		equ 2
SW_PARENTOPENING	equ 3
SW_OTHERUNZOOM		equ 4

;; end_r_winuser

endif ;; NOT NOSHOWWINDOW

if(WINVER GE 0x0500)
;;
;; AnimateWindow() Commands
;;
AW_HOR_POSITIVE		equ 0x00000001
AW_HOR_NEGATIVE		equ 0x00000002
AW_VER_POSITIVE		equ 0x00000004
AW_VER_NEGATIVE		equ 0x00000008
AW_CENTER		equ 0x00000010
AW_HIDE			equ 0x00010000
AW_ACTIVATE		equ 0x00020000
AW_SLIDE		equ 0x00040000
AW_BLEND		equ 0x00080000

endif ;; WINVER GE 0x0500

;;
;; WM_KEYUP/DOWN/CHAR HIWORD(lParam) flags
;;
KF_EXTENDED		equ 0x0100
KF_DLGMODE		equ 0x0800
KF_MENUMODE		equ 0x1000
KF_ALTDOWN		equ 0x2000
KF_REPEAT		equ 0x4000
KF_UP			equ 0x8000

ifndef NOVIRTUALKEYCODES

;; begin_r_winuser

;;
;; Virtual Keys, Standard Set
;;
VK_LBUTTON		equ 0x01
VK_RBUTTON		equ 0x02
VK_CANCEL		equ 0x03
VK_MBUTTON		equ 0x04 ;; NOT contiguous with L AND RBUTTON
if(_WIN32_WINNT GE 0x0500)
VK_XBUTTON1		equ 0x05 ;; NOT contiguous with L & RBUTTON
VK_XBUTTON2		equ 0x06 ;; NOT contiguous with L & RBUTTON
endif ;; _WIN32_WINNT >= 0x0500

VK_BACK			equ 0x08
VK_TAB			equ 0x09

VK_CLEAR		equ 0x0C
VK_RETURN		equ 0x0D

VK_SHIFT		equ 0x10
VK_CONTROL		equ 0x11
VK_MENU			equ 0x12
VK_PAUSE		equ 0x13
VK_CAPITAL		equ 0x14

VK_KANA			equ 0x15
VK_HANGEUL		equ 0x15  ;; old name - should be here for compatibility
VK_HANGUL		equ 0x15
VK_JUNJA		equ 0x17
VK_FINAL		equ 0x18
VK_HANJA		equ 0x19
VK_KANJI		equ 0x19

VK_ESCAPE		equ 0x1B

VK_CONVERT		equ 0x1C
VK_NONCONVERT		equ 0x1D
VK_ACCEPT		equ 0x1E
VK_MODECHANGE		equ 0x1F

VK_SPACE		equ 0x20
VK_PRIOR		equ 0x21
VK_NEXT			equ 0x22
VK_END			equ 0x23
VK_HOME			equ 0x24
VK_LEFT			equ 0x25
VK_UP			equ 0x26
VK_RIGHT		equ 0x27
VK_DOWN			equ 0x28
VK_SELECT		equ 0x29
VK_PRINT		equ 0x2A
VK_EXECUTE		equ 0x2B
VK_SNAPSHOT		equ 0x2C
VK_INSERT		equ 0x2D
VK_DELETE		equ 0x2E
VK_HELP			equ 0x2F

;; VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39)
;; VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)

VK_LWIN			equ 0x5B
VK_RWIN			equ 0x5C
VK_APPS			equ 0x5D

VK_NUMPAD0		equ 0x60
VK_NUMPAD1		equ 0x61
VK_NUMPAD2		equ 0x62
VK_NUMPAD3		equ 0x63
VK_NUMPAD4		equ 0x64
VK_NUMPAD5		equ 0x65
VK_NUMPAD6		equ 0x66
VK_NUMPAD7		equ 0x67
VK_NUMPAD8		equ 0x68
VK_NUMPAD9		equ 0x69
VK_MULTIPLY		equ 0x6A
VK_ADD			equ 0x6B
VK_SEPARATOR		equ 0x6C
VK_SUBTRACT		equ 0x6D
VK_DECIMAL		equ 0x6E
VK_DIVIDE		equ 0x6F
VK_F1			equ 0x70
VK_F2			equ 0x71
VK_F3			equ 0x72
VK_F4			equ 0x73
VK_F5			equ 0x74
VK_F6			equ 0x75
VK_F7			equ 0x76
VK_F8			equ 0x77
VK_F9			equ 0x78
VK_F10			equ 0x79
VK_F11			equ 0x7A
VK_F12			equ 0x7B
VK_F13			equ 0x7C
VK_F14			equ 0x7D
VK_F15			equ 0x7E
VK_F16			equ 0x7F
VK_F17			equ 0x80
VK_F18			equ 0x81
VK_F19			equ 0x82
VK_F20			equ 0x83
VK_F21			equ 0x84
VK_F22			equ 0x85
VK_F23			equ 0x86
VK_F24			equ 0x87

;;
;; 0x88 - 0x8F : unassigned
;;

VK_NUMLOCK		equ 0x90
VK_SCROLL		equ 0x91

;;
;; NEC PC-9800 kbd definitions
;;
VK_OEM_NEC_EQUAL	equ 0x92   ;; '=' key on numpad

;;
;; Fujitsu/OASYS kbd definitions
;;
VK_OEM_FJ_JISHO		equ 0x92   ;; 'Dictionary' key
VK_OEM_FJ_MASSHOU	equ 0x93   ;; 'Unregister word' key
VK_OEM_FJ_TOUROKU	equ 0x94   ;; 'Register word' key
VK_OEM_FJ_LOYA		equ 0x95   ;; 'Left OYAYUBI' key
VK_OEM_FJ_ROYA		equ 0x96   ;; 'Right OYAYUBI' key

;;
;; 0x97 - 0x9F : unassigned
;;

;;
;; VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
;; Used only as parameters to GetAsyncKeyState() and GetKeyState().
;; No other API or message will distinguish left and right keys in this way.
;;
VK_LSHIFT		equ 0xA0
VK_RSHIFT		equ 0xA1
VK_LCONTROL		equ 0xA2
VK_RCONTROL		equ 0xA3
VK_LMENU		equ 0xA4
VK_RMENU		equ 0xA5
if(_WIN32_WINNT GE 0x0500)
VK_BROWSER_BACK		equ 0xA6
VK_BROWSER_FORWARD	equ 0xA7
VK_BROWSER_REFRESH	equ 0xA8
VK_BROWSER_STOP		equ 0xA9
VK_BROWSER_SEARCH	equ 0xAA
VK_BROWSER_FAVORITES	equ 0xAB
VK_BROWSER_HOME		equ 0xAC

VK_VOLUME_MUTE		equ 0xAD
VK_VOLUME_DOWN		equ 0xAE
VK_VOLUME_UP		equ 0xAF
VK_MEDIA_NEXT_TRACK	equ 0xB0
VK_MEDIA_PREV_TRACK	equ 0xB1
VK_MEDIA_STOP		equ 0xB2
VK_MEDIA_PLAY_PAUSE	equ 0xB3
VK_LAUNCH_MAIL		equ 0xB4
VK_LAUNCH_MEDIA_SELECT	equ 0xB5
VK_LAUNCH_APP1		equ 0xB6
VK_LAUNCH_APP2		equ 0xB7
endif ;; _WIN32_WINNT >= 0x0500

;;
;; 0xB8 - 0xB9 : reserved
;;

VK_OEM_1		equ 0xBA   ;; ';:' for US
VK_OEM_PLUS		equ 0xBB   ;; '+' any country
VK_OEM_COMMA		equ 0xBC   ;; ',' any country
VK_OEM_MINUS		equ 0xBD   ;; '-' any country
VK_OEM_PERIOD		equ 0xBE   ;; '.' any country
VK_OEM_2		equ 0xBF   ;; '/?' for US
VK_OEM_3		equ 0xC0   ;; '` NOT ' for US

;;
;; 0xC1 - 0xD7 : reserved
;;

;;
;; 0xD8 - 0xDA : unassigned
;;

VK_OEM_4		equ 0xDB  ;;  '[{' for US
VK_OEM_5		equ 0xDC  ;;  '\ OR ' for US
VK_OEM_6		equ 0xDD  ;;  ']}' for US
VK_OEM_7		equ 0xDE  ;;  ''"' for US
VK_OEM_8		equ 0xDF

;;
;; 0xE0 : reserved
;;

;;
;; Various extended or enhanced keyboards
;;
VK_OEM_AX		equ 0xE1  ;;  'AX' key on Japanese AX kbd
VK_OEM_102		equ 0xE2  ;;  " LT GT " or "\ OR " on RT 102-key kbd.
VK_ICO_HELP		equ 0xE3  ;;  Help key on ICO
VK_ICO_00		equ 0xE4  ;;  00 key on ICO

if(WINVER GE 0x0400)
VK_PROCESSKEY		equ 0xE5
endif ;; WINVER GE 0x0400
VK_ICO_CLEAR		equ 0xE6
if(_WIN32_WINNT GE 0x0500)
VK_PACKET		equ 0xE7
endif ;; _WIN32_WINNT GE 0x0500

;;
;; 0xE8 : unassigned
;;

;;
;; Nokia/Ericsson definitions
;;
VK_OEM_RESET		equ 0xE9
VK_OEM_JUMP		equ 0xEA
VK_OEM_PA1		equ 0xEB
VK_OEM_PA2		equ 0xEC
VK_OEM_PA3		equ 0xED
VK_OEM_WSCTRL		equ 0xEE
VK_OEM_CUSEL		equ 0xEF
VK_OEM_ATTN		equ 0xF0
VK_OEM_FINISH		equ 0xF1
VK_OEM_COPY		equ 0xF2
VK_OEM_AUTO		equ 0xF3
VK_OEM_ENLW		equ 0xF4
VK_OEM_BACKTAB		equ 0xF5

VK_ATTN			equ 0xF6
VK_CRSEL		equ 0xF7
VK_EXSEL		equ 0xF8
VK_EREOF		equ 0xF9
VK_PLAY			equ 0xFA
VK_ZOOM			equ 0xFB
VK_NONAME		equ 0xFC
VK_PA1			equ 0xFD
VK_OEM_CLEAR		equ 0xFE

;;
;; 0xFF : reserved
;;

;; end_r_winuser

endif ;; NOT NOVIRTUALKEYCODES

ifndef NOWH

;;
;; SetWindowsHook() codes
;;
WH_MIN			equ (-1)
WH_MSGFILTER		equ (-1)
WH_JOURNALRECORD	equ 0
WH_JOURNALPLAYBACK	equ 1
WH_KEYBOARD		equ 2
WH_GETMESSAGE		equ 3
WH_CALLWNDPROC		equ 4
WH_CBT			equ 5
WH_SYSMSGFILTER		equ 6
WH_MOUSE		equ 7
ifdef _WIN32_WINDOWS
WH_HARDWARE		equ 8
endif
WH_DEBUG		equ 9
WH_SHELL		equ 10
WH_FOREGROUNDIDLE	equ 11
if(WINVER GE 0x0400)
WH_CALLWNDPROCRET	equ 12
endif ;; WINVER GE 0x0400

if (_WIN32_WINNT GE 0x0400)
WH_KEYBOARD_LL		equ 13
WH_MOUSE_LL		equ 14
endif ;; (_WIN32_WINNT GE 0x0400)

if(WINVER GE 0x0400)
if (_WIN32_WINNT GE 0x0400)
WH_MAX			equ 14
else
WH_MAX			equ 12
endif ;; (_WIN32_WINNT GE 0x0400)
else
WH_MAX			equ 11
endif

WH_MINHOOK		equ WH_MIN
WH_MAXHOOK		equ WH_MAX

;;
;; Hook Codes
;;
HC_ACTION		equ 0
HC_GETNEXT		equ 1
HC_SKIP			equ 2
HC_NOREMOVE		equ 3
HC_NOREM		equ HC_NOREMOVE
HC_SYSMODALON		equ 4
HC_SYSMODALOFF		equ 5

;;
;; CBT Hook Codes
;;
HCBT_MOVESIZE		equ 0
HCBT_MINMAX		equ 1
HCBT_QS			equ 2
HCBT_CREATEWND		equ 3
HCBT_DESTROYWND		equ 4
HCBT_ACTIVATE		equ 5
HCBT_CLICKSKIPPED	equ 6
HCBT_KEYSKIPPED		equ 7
HCBT_SYSCOMMAND		equ 8
HCBT_SETFOCUS		equ 9

;;
;; HCBT_CREATEWND parameters pointed to by lParam
;;
CBT_CREATEWNDA		STRUC
lpcs			PVOID ?
hwndInsertAfter		HWND ?
CBT_CREATEWNDA		ENDS
LPCBT_CREATEWNDA	typedef ptr CBT_CREATEWNDA
;;
;; HCBT_CREATEWND parameters pointed to by lParam
;;
CBT_CREATEWNDW		STRUC
lpcs			PVOID ?
hwndInsertAfter		HWND ?
CBT_CREATEWNDW		ENDS
LPCBT_CREATEWNDW	typedef ptr CBT_CREATEWNDW
ifdef _UNICODE
CBT_CREATEWND		typedef CBT_CREATEWNDW
LPCBT_CREATEWND		typedef LPCBT_CREATEWNDW
else
CBT_CREATEWND		typedef CBT_CREATEWNDA
LPCBT_CREATEWND		typedef LPCBT_CREATEWNDA
endif ;; UNICODE

;;
;; HCBT_ACTIVATE structure pointed to by lParam
;;
CBTACTIVATESTRUCT	STRUC
fMouse			BOOL ?
hWndActive		HWND ?
CBTACTIVATESTRUCT	ENDS
LPCBTACTIVATESTRUCT	typedef ptr CBTACTIVATESTRUCT

if(_WIN32_WINNT GE 0x0501)
;;
;; WTSSESSION_NOTIFICATION struct pointed by lParam, for WM_WTSSESSION_CHANGE
;;
WTSSESSION_NOTIFICATION STRUC
cbSize			dd ?
dwSessionId		dd ?
WTSSESSION_NOTIFICATION ENDS
PWTSSESSION_NOTIFICATION typedef ptr WTSSESSION_NOTIFICATION

;;
;; codes passed in WPARAM for WM_WTSSESSION_CHANGE
;;

WTS_CONSOLE_CONNECT	equ 0x1
WTS_CONSOLE_DISCONNECT	equ 0x2
WTS_REMOTE_CONNECT	equ 0x3
WTS_REMOTE_DISCONNECT	equ 0x4
WTS_SESSION_LOGON	equ 0x5
WTS_SESSION_LOGOFF	equ 0x6
WTS_SESSION_LOCK	equ 0x7
WTS_SESSION_UNLOCK	equ 0x8
WTS_SESSION_REMOTE_CONTROL equ 0x9

endif ;; _WIN32_WINNT GE 0x0501
;;
;; WH_MSGFILTER Filter Proc Codes
;;
MSGF_DIALOGBOX		equ 0
MSGF_MESSAGEBOX		equ 1
MSGF_MENU		equ 2
MSGF_SCROLLBAR		equ 5
MSGF_NEXTWINDOW		equ 6
MSGF_MAX		equ 8 ;; unused
MSGF_USER		equ 4096

;;
;; Shell support
;;
HSHELL_WINDOWCREATED	equ 1
HSHELL_WINDOWDESTROYED	equ 2
HSHELL_ACTIVATESHELLWINDOW equ 3

if(WINVER GE 0x0400)
HSHELL_WINDOWACTIVATED	equ 4
HSHELL_GETMINRECT	equ 5
HSHELL_REDRAW		equ 6
HSHELL_TASKMAN		equ 7
HSHELL_LANGUAGE		equ 8
HSHELL_SYSMENU		equ 9
HSHELL_ENDTASK		equ 10
endif ;; WINVER GE 0x0400
if(_WIN32_WINNT GE 0x0500)
HSHELL_ACCESSIBILITYSTATE equ 11
HSHELL_APPCOMMAND	equ 12
endif ;; _WIN32_WINNT GE 0x0500
if(_WIN32_WINNT GE 0x0501)
HSHELL_WINDOWREPLACED	equ 13
HSHELL_WINDOWREPLACING	equ 14
endif ;; _WIN32_WINNT GE 0x0501

HSHELL_HIGHBIT		equ 0x8000
HSHELL_FLASH		equ (HSHELL_REDRAW OR HSHELL_HIGHBIT)
HSHELL_RUDEAPPACTIVATED equ (HSHELL_WINDOWACTIVATED OR HSHELL_HIGHBIT)

if(_WIN32_WINNT GE 0x0500)
;; cmd for HSHELL_APPCOMMAND and WM_APPCOMMAND
APPCOMMAND_BROWSER_BACKWARD equ 1
APPCOMMAND_BROWSER_FORWARD equ 2
APPCOMMAND_BROWSER_REFRESH equ 3
APPCOMMAND_BROWSER_STOP equ 4
APPCOMMAND_BROWSER_SEARCH equ 5
APPCOMMAND_BROWSER_FAVORITES equ 6
APPCOMMAND_BROWSER_HOME equ 7
APPCOMMAND_VOLUME_MUTE	equ 8
APPCOMMAND_VOLUME_DOWN	equ 9
APPCOMMAND_VOLUME_UP	equ 10
APPCOMMAND_MEDIA_NEXTTRACK equ 11
APPCOMMAND_MEDIA_PREVIOUSTRACK equ 12
APPCOMMAND_MEDIA_STOP	equ 13
APPCOMMAND_MEDIA_PLAY_PAUSE equ 14
APPCOMMAND_LAUNCH_MAIL	equ 15
APPCOMMAND_LAUNCH_MEDIA_SELECT equ 16
APPCOMMAND_LAUNCH_APP1	equ 17
APPCOMMAND_LAUNCH_APP2	equ 18
APPCOMMAND_BASS_DOWN	equ 19
APPCOMMAND_BASS_BOOST	equ 20
APPCOMMAND_BASS_UP	equ 21
APPCOMMAND_TREBLE_DOWN	equ 22
APPCOMMAND_TREBLE_UP	equ 23
if(_WIN32_WINNT GE 0x0501)
APPCOMMAND_MICROPHONE_VOLUME_MUTE equ 24
APPCOMMAND_MICROPHONE_VOLUME_DOWN equ 25
APPCOMMAND_MICROPHONE_VOLUME_UP equ 26
APPCOMMAND_HELP		equ 27
APPCOMMAND_FIND		equ 28
APPCOMMAND_NEW		equ 29
APPCOMMAND_OPEN		equ 30
APPCOMMAND_CLOSE	equ 31
APPCOMMAND_SAVE		equ 32
APPCOMMAND_PRINT	equ 33
APPCOMMAND_UNDO		equ 34
APPCOMMAND_REDO		equ 35
APPCOMMAND_COPY		equ 36
APPCOMMAND_CUT		equ 37
APPCOMMAND_PASTE	equ 38
APPCOMMAND_REPLY_TO_MAIL equ 39
APPCOMMAND_FORWARD_MAIL equ 40
APPCOMMAND_SEND_MAIL	equ 41
APPCOMMAND_SPELL_CHECK	equ 42
APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE equ 43
APPCOMMAND_MIC_ON_OFF_TOGGLE equ 44
APPCOMMAND_CORRECTION_LIST equ 45
APPCOMMAND_MEDIA_PLAY	equ 46
APPCOMMAND_MEDIA_PAUSE	equ 47
APPCOMMAND_MEDIA_RECORD equ 48
APPCOMMAND_MEDIA_FAST_FORWARD equ 49
APPCOMMAND_MEDIA_REWIND equ 50
APPCOMMAND_MEDIA_CHANNEL_UP equ 51
APPCOMMAND_MEDIA_CHANNEL_DOWN equ 52
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0600)
APPCOMMAND_DELETE	equ 53
APPCOMMAND_DWM_FLIP3D	equ 54
endif ;; _WIN32_WINNT GE 0x0600

FAPPCOMMAND_MOUSE	equ 0x8000
FAPPCOMMAND_KEY		equ 0
FAPPCOMMAND_OEM		equ 0x1000
FAPPCOMMAND_MASK	equ 0xF000

GET_APPCOMMAND_LPARAM macro lParam
	exitm<HIWORD(lParam) AND NOT FAPPCOMMAND_MASK>
	endm
GET_DEVICE_LPARAM macro lParam
	exitm<HIWORD(lParam) AND FAPPCOMMAND_MASK>
	endm
GET_MOUSEORKEY_LPARAM	equ GET_DEVICE_LPARAM
GET_FLAGS_LPARAM macro lParam
	exitm<LOWORD(lParam)>
	endm
GET_KEYSTATE_LPARAM macro lParam
	exitm<GET_FLAGS_LPARAM(lParam)>
	endm
endif ;; _WIN32_WINNT GE 0x0500

SHELLHOOKINFO		STRUC
hwnd			HWND ?
rc			RECT <>
SHELLHOOKINFO		ENDS
LPSHELLHOOKINFO		typedef ptr SHELLHOOKINFO

;;
;; Message Structure used in Journaling
;;
EVENTMSG		STRUC
message			UINT ?
paramL			UINT ?
paramH			UINT ?
time			dd ?
hwnd			HWND ?
EVENTMSG		ENDS
PEVENTMSGMSG		typedef ptr EVENTMSG
NPEVENTMSGMSG		typedef ptr EVENTMSG
LPEVENTMSGMSG		typedef ptr EVENTMSG
PEVENTMSG		typedef ptr EVENTMSG
NPEVENTMSG		typedef ptr EVENTMSG
LPEVENTMSG		typedef ptr EVENTMSG

;;
;; Message structure used by WH_CALLWNDPROC
;;
CWPSTRUCT		STRUC
lParam			LPARAM ?
wParam			WPARAM ?
message			UINT ?
hwnd			HWND ?
CWPSTRUCT		ENDS
PCWPSTRUCT		typedef ptr CWPSTRUCT
NPCWPSTRUCT		typedef ptr CWPSTRUCT
LPCWPSTRUCT		typedef ptr CWPSTRUCT

if(WINVER GE 0x0400)
;;
;; Message structure used by WH_CALLWNDPROCRET
;;
CWPRETSTRUCT		STRUC
lResult			LRESULT ?
lParam			LPARAM ?
wParam			WPARAM ?
message			UINT ?
hwnd			HWND ?
CWPRETSTRUCT		ENDS
PCWPRETSTRUCT		typedef ptr CWPRETSTRUCT
NPCWPRETSTRUCT		typedef ptr CWPRETSTRUCT
LPCWPRETSTRUCT		typedef ptr CWPRETSTRUCT

endif ;; WINVER GE 0x0400

if (_WIN32_WINNT GE 0x0400)
;;
;; Low level hook flags
;;
LLKHF_EXTENDED		equ 0x00000001
LLKHF_INJECTED		equ 0x00000010
LLKHF_ALTDOWN		equ 0x00000020
LLKHF_UP		equ 0x00000080

LLMHF_INJECTED		equ 0x00000001

;;
;; Structure used by WH_KEYBOARD_LL
;;
KBDLLHOOKSTRUCT		STRUC
vkCode			dd ?
scanCode		dd ?
flags			dd ?
time			dd ?
dwExtraInfo		dd ?
KBDLLHOOKSTRUCT		ENDS
LPKBDLLHOOKSTRUCT	typedef ptr KBDLLHOOKSTRUCT
PKBDLLHOOKSTRUCT	typedef ptr KBDLLHOOKSTRUCT

;;
;; Structure used by WH_MOUSE_LL
;;
MSLLHOOKSTRUCT		STRUC
pt			POINT <>
mouseData		dd ?
flags			dd ?
time			dd ?
dwExtraInfo		dd ?
MSLLHOOKSTRUCT		ENDS
LPMSLLHOOKSTRUCT	typedef ptr MSLLHOOKSTRUCT
PMSLLHOOKSTRUCT		typedef ptr MSLLHOOKSTRUCT

endif ;; (_WIN32_WINNT GE 0x0400)

;;
;; Structure used by WH_DEBUG
;;
DEBUGHOOKINFO		STRUC
idThread		dd ?
idThreadInstaller	dd ?
lParam			LPARAM ?
wParam			WPARAM ?
code			SINT ?
DEBUGHOOKINFO		ENDS
PDEBUGHOOKINFO		typedef ptr DEBUGHOOKINFO
NPDEBUGHOOKINFO		typedef ptr DEBUGHOOKINFO
LPDEBUGHOOKINFO		typedef ptr DEBUGHOOKINFO

;;
;; Structure used by WH_MOUSE
;;
MOUSEHOOKSTRUCT		STRUC
pt			POINT <>
hwnd			HWND ?
wHitTestCode		UINT ?
dwExtraInfo		dd ?
MOUSEHOOKSTRUCT		ENDS
LPMOUSEHOOKSTRUCT	typedef ptr MOUSEHOOKSTRUCT
PMOUSEHOOKSTRUCT	typedef ptr MOUSEHOOKSTRUCT
if(WINVER GE 0x0400)
;;
;; Structure used by WH_HARDWARE
;;
HARDWAREHOOKSTRUCT	STRUC
hwnd			HWND ?
message			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
HARDWAREHOOKSTRUCT	ENDS
LPHARDWAREHOOKSTRUCT	typedef ptr HARDWAREHOOKSTRUCT
PHARDWAREHOOKSTRUCT	typedef ptr HARDWAREHOOKSTRUCT
endif ;; WINVER GE 0x0400
endif ;; NOT NOWH

;;
;; Keyboard Layout API
;;
HKL_PREV		equ 0
HKL_NEXT		equ 1


KLF_ACTIVATE		equ 0x00000001
KLF_SUBSTITUTE_OK	equ 0x00000002
KLF_UNLOADPREVIOUS	equ 0x00000004
KLF_REORDER		equ 0x00000008
if(WINVER GE 0x0400)
KLF_REPLACELANG		equ 0x00000010
KLF_NOTELLSHELL		equ 0x00000080
endif ;; WINVER GE 0x0400
KLF_SETFORPROCESS	equ 0x00000100
if(_WIN32_WINNT GE 0x0500)
KLF_SHIFTLOCK		equ 0x00010000
KLF_RESET		equ 0x40000000
endif ;; _WIN32_WINNT GE 0x0500


if(WINVER GE 0x0500)
;;
;; Bits in wParam of WM_INPUTLANGCHANGEREQUEST message
;;
INPUTLANGCHANGE_SYSCHARSET equ 0x0001
INPUTLANGCHANGE_FORWARD	   equ 0x0002
INPUTLANGCHANGE_BACKWARD   equ 0x0004
endif ;; WINVER GE 0x0500


;;
;; Size of KeyboardLayoutName (number of characters), including nul terminator
;;
KL_NAMELENGTH		equ 9

;HKL
LoadKeyboardLayoutA proto _CType \
	      pwszKLID: LPCSTR,
		 Flags: UINT
;HKL
LoadKeyboardLayoutW proto _CType \
	      pwszKLID: LPCWSTR,
		 Flags: UINT
ifdef _UNICODE
LoadKeyboardLayout	equ <LoadKeyboardayoutW>
else
LoadKeyboardLayout	equ <LoadKeyboardayoutA>
endif ;; NOT UNICODE


if(WINVER GE 0x0400)
;HKL
ActivateKeyboardLayout proto _CType \
		   hkl: HKL,
		 Flags: UINT
else
;BOOL
ActivateKeyboardLayout proto _CType \
		   hkl: HKL,
		 Flags: UINT
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0400)
;int
ToUnicodeEx proto _CType \
	      wVirtKey: UINT,
	     wScanCode: UINT,
	    lpKeyState: PBYTE,
	      pwszBuff: LPWSTR,
	       cchBuff: SINT,
		wFlags: UINT,
		 dwhkl: HKL
endif ;; WINVER GE 0x0400

;BOOL
UnloadKeyboardLayout proto _CType \
		   hkl: HKL

;BOOL
GetKeyboardLayoutNameA proto _CType \
	      pwszKLID: LPSTR
;BOOL
GetKeyboardLayoutNameW proto _CType \
	      pwszKLID: LPWSTR
ifdef _UNICODE
GetKeyboardLayoutName	equ <GetKeyboardayoutNameW>
else
GetKeyboardLayoutName	equ <GetKeyboardayoutNameA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;int
GetKeyboardLayoutList proto _CType \
		 nBuff: SINT,
		lpList: ptr HKL

;HKL
GetKeyboardLayout proto _CType \
	     dwLayout : DWORD
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0500)
MOUSEMOVEPOINT		STRUC
x			SINT ?
y			SINT ?
time			dd ?
dwExtraInfo		dd ?
MOUSEMOVEPOINT		ENDS
PMOUSEMOVEPOINT		typedef ptr MOUSEMOVEPOINT
LPMOUSEMOVEPOINT	typedef ptr MOUSEMOVEPOINT

;;
;; Values for resolution parameter of GetMouseMovePoints
;;
GMMP_USE_DISPLAY_POINTS equ 1
GMMP_USE_DRIVER_POINTS	equ 2

;int
GetMouseMovePoints proto _CType \
		cbSize: UINT,
		  lppt: LPMOUSEMOVEPOINT,
	       lpptBuf: LPMOUSEMOVEPOINT,
	    nBufPoints: SINT,
	   resolution : DWORD

;int
GetMouseMovePointsEx proto _CType \
		cbSize: UINT,
		  lppt: LPMOUSEMOVEPOINT,
	       lpptBuf: LPMOUSEMOVEPOINT,
	    nBufPoints: SINT,
	   resolution : DWORD
endif ;; WINVER GE 0x0500

ifndef NODESKTOP
;;
;; Desktop-specific access flags
;;
DESKTOP_READOBJECTS	equ 0x0001
DESKTOP_CREATEWINDOW	equ 0x0002
DESKTOP_CREATEMENU	equ 0x0004
DESKTOP_HOOKCONTROL	equ 0x0008
DESKTOP_JOURNALRECORD	equ 0x0010
DESKTOP_JOURNALPLAYBACK equ 0x0020
DESKTOP_ENUMERATE	equ 0x0040
DESKTOP_WRITEOBJECTS	equ 0x0080
DESKTOP_SWITCHDESKTOP	equ 0x0100

;;
;; Desktop-specific control flags
;;
DF_ALLOWOTHERACCOUNTHOOK equ 0x0001

ifdef _WINGDI_
ifndef NOGDI

;HDESK
CreateDesktopA proto _CType \
	   lpszDesktop: LPSTR,
	    lpszDevice: LPSTR,
	      pDevmode: LPDEVMODEA,
	       dwFlags: DWORD,
       dwDesiredAccess: ACCESS_MASK,
		  lpsa: LPSECURITY_ATTRIBUTES
CreateDesktopW proto _CType \
	   lpszDesktop: LPWSTR,
	    lpszDevice: LPWSTR,
	      pDevmode: LPDEVMODEW,
	       dwFlags: DWORD,
       dwDesiredAccess: ACCESS_MASK,
		  lpsa: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateDesktop		equ <CreateDesktopW>
else
CreateDesktop		equ <CreateDesktopA>
endif ;; NOT UNICODE

endif ;; NOGDI
endif ;; _WINGDI_

;HDESK
OpenDesktopA proto _CType \
	   lpszDesktop: LPSTR,
	       dwFlags: DWORD,
	      fInherit: BOOL,
       dwDesiredAccess: ACCESS_MASK
;HDESK
OpenDesktopW proto _CType \
	   lpszDesktop: LPWSTR,
	       dwFlags: DWORD,
	      fInherit: BOOL,
       dwDesiredAccess: ACCESS_MASK
ifdef _UNICODE
OpenDesktop		equ <OpenDesktopW>
else
OpenDesktop		equ <OpenDesktopA>
endif ;; NOT UNICODE

;HDESK
OpenInputDesktop proto _CType \
	       dwFlags: DWORD,
	      fInherit: BOOL,
       dwDesiredAccess: ACCESS_MASK

;BOOL
EnumDesktopsA proto _CType \
	       hwinsta: HWINSTA,
	    lpEnumFunc: DESKTOPENUMPROCA,
		lParam: LPARAM
;BOOL
EnumDesktopsW proto _CType \
	       hwinsta: HWINSTA,
	    lpEnumFunc: DESKTOPENUMPROCW,
		lParam: LPARAM
ifdef _UNICODE
EnumDesktops		equ <EnumDesktopsW>
else
EnumDesktops		equ <EnumDesktopsA>
endif ;; NOT UNICODE

;BOOL
EnumDesktopWindows proto _CType \
	      hDesktop: HDESK,
		  lpfn: WNDENUMPROC,
		lParam: LPARAM

;BOOL
SwitchDesktop proto _CType \
	      hDesktop: HDESK

;BOOL
SetThreadDesktop proto _CType \
	      hDesktop: HDESK

;BOOL
CloseDesktop proto _CType \
	      hDesktop: HDESK

;HDESK
GetThreadDesktop proto _CType \
	    dwThreadId: DWORD
endif  ;; NOT NODESKTOP


ifndef NOWINDOWSTATION
;;
;; Windowstation-specific access flags
;;
WINSTA_ENUMDESKTOPS	equ 0x0001
WINSTA_READATTRIBUTES	equ 0x0002
WINSTA_ACCESSCLIPBOARD	equ 0x0004
WINSTA_CREATEDESKTOP	equ 0x0008
WINSTA_WRITEATTRIBUTES	equ 0x0010
WINSTA_ACCESSGLOBALATOMS equ 0x0020
WINSTA_EXITWINDOWS	equ 0x0040
WINSTA_ENUMERATE	equ 0x0100
WINSTA_READSCREEN	equ 0x0200

;;
;; Windowstation-specific attribute flags
;;
WSF_VISIBLE		equ 0x0001

;HWINSTA
CreateWindowStationA proto _CType \
	      lpwinsta: LPSTR,
	    dwReserved: DWORD,
       dwDesiredAccess: ACCESS_MASK,
		  lpsa: LPSECURITY_ATTRIBUTES
;HWINSTA
CreateWindowStationW proto _CType \
	      lpwinsta: LPWSTR,
	    dwReserved: DWORD,
       dwDesiredAccess: ACCESS_MASK,
		  lpsa: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
CreateWindowStation	equ <CreateWindowStationW>
else
CreateWindowStation	equ <CreateWindowStationA>
endif ;; NOT UNICODE

;HWINSTA
OpenWindowStationA proto _CType \
	    lpszWinSta: LPSTR,
	      fInherit: BOOL,
       dwDesiredAccess: ACCESS_MASK
;HWINSTA
OpenWindowStationW proto _CType \
	    lpszWinSta: LPWSTR,
	      fInherit: BOOL,
       dwDesiredAccess: ACCESS_MASK
ifdef _UNICODE
OpenWindowStation	equ <OpenWindowStationW>
else
OpenWindowStation	equ <OpenWindowStationA>
endif ;; NOT UNICODE

;BOOL
EnumWindowStationsA proto _CType \
	    lpEnumFunc: WINSTAENUMPROCA,
		lParam: LPARAM
;BOOL
EnumWindowStationsW proto _CType \
	    lpEnumFunc: WINSTAENUMPROCW,
		lParam: LPARAM
ifdef _UNICODE
EnumWindowStations	equ <EnumWindowStationsW>
else
EnumWindowStations	equ <EnumWindowStationsA>
endif ;; NOT UNICODE


;BOOL
CloseWindowStation proto _CType \
	       hWinSta: HWINSTA

;BOOL
SetProcessWindowStation proto _CType \
	       hWinSta: HWINSTA

;HWINSTA
GetProcessWindowStation proto _CType
endif  ;; NOT NOWINDOWSTATION

ifndef NOSECURITY

;BOOL
SetUserObjectSecurity proto _CType \
		  hObj: HANDLE,
	  pSIRequested: PSECURITY_INFORMATION,
		  pSID: PSECURITY_DESCRIPTOR

;BOOL
GetUserObjectSecurity proto _CType \
		  hObj: HANDLE,
	  pSIRequested: PSECURITY_INFORMATION,
		  pSID: PSECURITY_DESCRIPTOR,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD

UOI_FLAGS		equ 1
UOI_NAME		equ 2
UOI_TYPE		equ 3
UOI_USER_SID		equ 4
if(WINVER GE 0x0600)
UOI_HEAPSIZE		equ 5
UOI_IO			equ 6
endif ;; WINVER GE 0x0600

USEROBJECTFLAGS		STRUC
fInherit		BOOL ?
fReserved		BOOL ?
dwFlags			dd ?
USEROBJECTFLAGS		ENDS
PUSEROBJECTFLAGS	typedef ptr USEROBJECTFLAGS

;BOOL
GetUserObjectInformationA proto _CType \
		  hObj: HANDLE,
		nIndex: SINT,
		pvInfo: PVOID,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD
;BOOL
GetUserObjectInformationW proto _CType \
		  hObj: HANDLE,
		nIndex: SINT,
		pvInfo: PVOID,
	       nLength: DWORD,
       lpnLengthNeeded: LPDWORD
ifdef _UNICODE
GetUserObjectInformation equ <GetUserObjectInformationW>
else
GetUserObjectInformation equ <GetUserObjectInformationA>
endif ;; NOT UNICODE

;BOOL
SetUserObjectInformationA proto _CType \
		  hObj: HANDLE,
		nIndex: SINT,
		pvInfo: PVOID,
	       nLength: DWORD
;BOOL
SetUserObjectInformationW proto _CType \
		  hObj: HANDLE,
		nIndex: SINT,
		pvInfo: PVOID,
	       nLength: DWORD
ifdef _UNICODE
SetUserObjectInformation equ <SetUserObjectInformationW>
else
SetUserObjectInformation equ <SetUserObjectInformationA>
endif ;; NOT UNICODE

endif  ;; NOT NOSECURITY

if(WINVER GE 0x0400)
WNDCLASSEXA		STRUC
cbSize			UINT ?
;; Win 3.x
style			UINT ?
lpfnWndProc		WNDPROC ?
cbClsExtra		SINT ?
cbWndExtra		SINT ?
hInstance		HINSTANCE ?
hIcon			HICON ?
hCursor			HCURSOR ?
hbrBackground		HBRUSH ?
lpszMenuName		LPCSTR ?
lpszClassName		LPCSTR ?
;; Win 4.0
hIconSm			HICON ?
WNDCLASSEXA		ENDS
PWNDCLASSEXA		typedef ptr WNDCLASSEXA
NPWNDCLASSEXA		typedef ptr WNDCLASSEXA
LPWNDCLASSEXA		typedef ptr WNDCLASSEXA
WNDCLASSEXW		STRUC
cbSize			UINT ?
;; Win 3.x
style			UINT ?
lpfnWndProc		WNDPROC ?
cbClsExtra		SINT ?
cbWndExtra		SINT ?
hInstance		HINSTANCE ?
hIcon			HICON ?
hCursor			HCURSOR ?
hbrBackground		HBRUSH ?
lpszMenuName		LPCWSTR ?
lpszClassName		LPCWSTR ?
;; Win 4.0
hIconSm			HICON ?
WNDCLASSEXW		ENDS
PWNDCLASSEXW		typedef ptr WNDCLASSEXW
NPWNDCLASSEXW		typedef ptr WNDCLASSEXW
LPWNDCLASSEXW		typedef ptr WNDCLASSEXW
ifdef _UNICODE
WNDCLASSEX		typedef WNDCLASSEXW
PWNDCLASSEX		typedef PWNDCLASSEXW
NPWNDCLASSEX		typedef NPWNDCLASSEXW
LPWNDCLASSEX		typedef LPWNDCLASSEXW
else
WNDCLASSEX		typedef WNDCLASSEXA
PWNDCLASSEX		typedef PWNDCLASSEXA
NPWNDCLASSEX		typedef NPWNDCLASSEXA
LPWNDCLASSEX		typedef LPWNDCLASSEXA
endif ;; UNICODE
endif ;; WINVER GE 0x0400

WNDCLASSA		STRUC
style			UINT ?
lpfnWndProc		WNDPROC ?
cbClsExtra		SINT ?
cbWndExtra		SINT ?
hInstance		HINSTANCE ?
hIcon			HICON ?
hCursor			HCURSOR ?
hbrBackground		HBRUSH ?
lpszMenuName		LPCSTR ?
lpszClassName		LPCSTR ?
WNDCLASSA		ENDS
PWNDCLASSA		typedef ptr WNDCLASSA
NPWNDCLASSA		typedef ptr WNDCLASSA
LPWNDCLASSA		typedef ptr WNDCLASSA
WNDCLASSW		STRUC
style			UINT ?
lpfnWndProc		WNDPROC ?
cbClsExtra		SINT ?
cbWndExtra		SINT ?
hInstance		HINSTANCE ?
hIcon			HICON ?
hCursor			HCURSOR ?
hbrBackground		HBRUSH ?
lpszMenuName		LPCWSTR ?
lpszClassName		LPCWSTR ?
WNDCLASSW		ENDS
PWNDCLASSW		typedef ptr WNDCLASSW
NPWNDCLASSW		typedef ptr WNDCLASSW
LPWNDCLASSW		typedef ptr WNDCLASSW
ifdef _UNICODE
WNDCLASS		typedef WNDCLASSW
PWNDCLASS		typedef PWNDCLASSW
NPWNDCLASS		typedef NPWNDCLASSW
LPWNDCLASS		typedef LPWNDCLASSW
else
WNDCLASS		typedef WNDCLASSA
PWNDCLASS		typedef PWNDCLASSA
NPWNDCLASS		typedef NPWNDCLASSA
LPWNDCLASS		typedef LPWNDCLASSA
endif ;; UNICODE

;WINUSERAPI
;BOOL
IsHungAppWindow proto _CType \
		hwnd: HWND

if (WINVER GE 0x0501)
;WINUSERAPI
;VOID
DisableProcessWindowsGhosting proto _CType
endif ;; WINVER GE 0x0501

ifndef NOMSG

;;
;; Message structure
;;
MSG			STRUC
hwnd			HWND ?
message			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
time			dd ?
pt			POINT <>
MSG			ENDS
PMSG			typedef ptr MSG
NPMSG			typedef ptr MSG
LPMSG			typedef ptr MSG

POINTSTOPOINT macro pt, pts
	movzx	eax,word ptr pts
	mov	pt.x,ax
	movzx	eax,word ptr pts[2]
	mov	pt.y,ax
	endm
POINTTOPOINTS macro pt
	exitm<(MAKEONG(((pt).x), ((pt).y)))>
	endm
MAKEWPARAM macro l,h
	exitm<MAKEONG(l, h)>
	endm
MAKELPARAM macro l,h
	exitm<MAKEONG(l, h)>
	endm
MAKELRESULT macro l,h
	exitm<MAKEONG(l, h)>
	endm


endif ;; NOT NOMSG

ifndef NOWINOFFSETS

;;
;; Window field offsets for GetWindowLong()
;;
ifndef _WIN64
GWL_WNDPROC		equ (-4)
GWL_HINSTANCE		equ (-6)
GWL_HWNDPARENT		equ (-8)
endif
GWL_STYLE		equ (-16)
GWL_EXSTYLE		equ (-20)
ifndef _WIN64
GWL_USERDATA		equ (-21)
endif
GWL_ID			equ (-12)

;;
;; Class field offsets for GetClassLong()
;;
ifndef _WIN64
GCL_MENUNAME		equ (-8)
GCL_HBRBACKGROUND	equ (-10)
GCL_HCURSOR		equ (-12)
GCL_HICON		equ (-14)
GCL_HMODULE		equ (-16)
endif
GCL_CBWNDEXTRA		equ (-18)
GCL_CBCLSEXTRA		equ (-20)
ifndef _WIN64
GCL_WNDPROC		equ (-24)
endif
GCL_STYLE		equ (-26)
GCW_ATOM		equ (-32)
if(WINVER GE 0x0400)
ifndef _WIN64
GCL_HICONSM		equ (-34)
endif
endif ;; WINVER GE 0x0400
endif ;; NOT NOWINOFFSETS

ifndef NOWINMESSAGES

;; begin_r_winuser

;;
;; Window Messages
;;

WM_NULL			equ 0x0000
WM_CREATE		equ 0x0001
WM_DESTROY		equ 0x0002
WM_MOVE			equ 0x0003
WM_SIZE			equ 0x0005

WM_ACTIVATE		equ 0x0006
;;
;; WM_ACTIVATE state values
;;
WA_INACTIVE		equ 0
WA_ACTIVE		equ 1
WA_CLICKACTIVE		equ 2

WM_SETFOCUS		equ 0x0007
WM_KILLFOCUS		equ 0x0008
WM_ENABLE		equ 0x000A
WM_SETREDRAW		equ 0x000B
WM_SETTEXT		equ 0x000C
WM_GETTEXT		equ 0x000D
WM_GETTEXTLENGTH	equ 0x000E
WM_PAINT		equ 0x000F
WM_CLOSE		equ 0x0010
WM_QUERYENDSESSION	equ 0x0011
WM_QUIT			equ 0x0012
WM_QUERYOPEN		equ 0x0013
WM_ERASEBKGND		equ 0x0014
WM_SYSCOLORCHANGE	equ 0x0015
WM_ENDSESSION		equ 0x0016
WM_SHOWWINDOW		equ 0x0018
WM_WININICHANGE		equ 0x001A
if(WINVER GE 0x0400)
WM_SETTINGCHANGE	equ WM_WININICHANGE
endif ;; WINVER GE 0x0400


WM_DEVMODECHANGE	equ 0x001B
WM_ACTIVATEAPP		equ 0x001C
WM_FONTCHANGE		equ 0x001D
WM_TIMECHANGE		equ 0x001E
WM_CANCELMODE		equ 0x001F
WM_SETCURSOR		equ 0x0020
WM_MOUSEACTIVATE	equ 0x0021
WM_CHILDACTIVATE	equ 0x0022
WM_QUEUESYNC		equ 0x0023

WM_GETMINMAXINFO	equ 0x0024
;; end_r_winuser
;;
;; Struct pointed to by WM_GETMINMAXINFO lParam
;;
MINMAXINFO		STRUC
ptReserved		POINT <>
ptMaxSize		POINT <>
ptMaxPosition		POINT <>
ptMinTrackSize		POINT <>
ptMaxTrackSize		POINT <>
MINMAXINFO		ENDS
PMINMAXINFO		typedef ptr MINMAXINFO
LPMINMAXINFO		typedef ptr MINMAXINFO

;; begin_r_winuser
WM_PAINTICON		equ 0x0026
WM_ICONERASEBKGND	equ 0x0027
WM_NEXTDLGCTL		equ 0x0028
WM_SPOOLERSTATUS	equ 0x002A
WM_DRAWITEM		equ 0x002B
WM_MEASUREITEM		equ 0x002C
WM_DELETEITEM		equ 0x002D
WM_VKEYTOITEM		equ 0x002E
WM_CHARTOITEM		equ 0x002F
WM_SETFONT		equ 0x0030
WM_GETFONT		equ 0x0031
WM_SETHOTKEY		equ 0x0032
WM_GETHOTKEY		equ 0x0033
WM_QUERYDRAGICON	equ 0x0037
WM_COMPAREITEM		equ 0x0039
if(WINVER GE 0x0500)
ifndef _WIN32_WCE
WM_GETOBJECT		equ 0x003D
endif
endif ;; WINVER GE 0x0500
WM_COMPACTING		equ 0x0041
WM_COMMNOTIFY		equ 0x0044  ;; no longer suported
WM_WINDOWPOSCHANGING	equ 0x0046
WM_WINDOWPOSCHANGED	equ 0x0047

WM_POWER		equ 0x0048
;;
;; wParam for WM_POWER window message and DRV_POWER driver notification
;;
PWR_OK			equ 1
PWR_FAIL		equ (-1)
PWR_SUSPENDREQUEST	equ 1
PWR_SUSPENDRESUME	equ 2
PWR_CRITICALRESUME	equ 3

WM_COPYDATA		equ 0x004A
WM_CANCELJOURNAL	equ 0x004B

;; end_r_winuser

;;
;; lParam of WM_COPYDATA message points to...
;;
COPYDATASTRUCT		STRUC
dwData			dd ?
cbData			dd ?
lpData			PVOID ?
COPYDATASTRUCT		ENDS
PCOPYDATASTRUCT		typedef ptr COPYDATASTRUCT

;; begin_r_winuser

if(WINVER GE 0x0400)
WM_NOTIFY		equ 0x004E
WM_INPUTLANGCHANGEREQUEST equ 0x0050
WM_INPUTLANGCHANGE	equ 0x0051
WM_TCARD		equ 0x0052
WM_HELP			equ 0x0053
WM_USERCHANGED		equ 0x0054
WM_NOTIFYFORMAT		equ 0x0055

NFR_ANSI		equ 1
NFR_UNICODE		equ 2
NF_QUERY		equ 3
NF_REQUERY		equ 4

WM_CONTEXTMENU		equ 0x007B
WM_STYLECHANGING	equ 0x007C
WM_STYLECHANGED		equ 0x007D
WM_DISPLAYCHANGE	equ 0x007E
WM_GETICON		equ 0x007F
WM_SETICON		equ 0x0080
endif ;; WINVER GE 0x0400

WM_NCCREATE		equ 0x0081
WM_NCDESTROY		equ 0x0082
WM_NCCALCSIZE		equ 0x0083
WM_NCHITTEST		equ 0x0084
WM_NCPAINT		equ 0x0085
WM_NCACTIVATE		equ 0x0086
WM_GETDLGCODE		equ 0x0087
WM_SYNCPAINT		equ 0x0088
WM_NCMOUSEMOVE		equ 0x00A0
WM_NCLBUTTONDOWN	equ 0x00A1
WM_NCLBUTTONUP		equ 0x00A2
WM_NCLBUTTONDBLCLK	equ 0x00A3
WM_NCRBUTTONDOWN	equ 0x00A4
WM_NCRBUTTONUP		equ 0x00A5
WM_NCRBUTTONDBLCLK	equ 0x00A6
WM_NCMBUTTONDOWN	equ 0x00A7
WM_NCMBUTTONUP		equ 0x00A8
WM_NCMBUTTONDBLCLK	equ 0x00A9
if(_WIN32_WINNT GE 0x0500)
WM_NCXBUTTONDOWN	equ 0x00AB
WM_NCXBUTTONUP		equ 0x00AC
WM_NCXBUTTONDBLCLK	equ 0x00AD
endif ;; _WIN32_WINNT GE 0x0500
if(_WIN32_WINNT GE 0x0501)
WM_INPUT_DEVICE_CHANGE	equ 0x00FE
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0501)
WM_INPUT		equ 0x00FF
endif ;; _WIN32_WINNT GE 0x0501

WM_KEYFIRST		equ 0x0100
WM_KEYDOWN		equ 0x0100
WM_KEYUP		equ 0x0101
WM_CHAR			equ 0x0102
WM_DEADCHAR		equ 0x0103
WM_SYSKEYDOWN		equ 0x0104
WM_SYSKEYUP		equ 0x0105
WM_SYSCHAR		equ 0x0106
WM_SYSDEADCHAR		equ 0x0107
if(_WIN32_WINNT GE 0x0501)
WM_UNICHAR		equ 0x0109
WM_KEYLAST		equ 0x0109
UNICODE_NOCHAR		equ 0xFFFF
else
WM_KEYLAST		equ 0x0108
endif ;; _WIN32_WINNT GE 0x0501

if(WINVER GE 0x0400)
WM_IME_STARTCOMPOSITION equ 0x010D
WM_IME_ENDCOMPOSITION	equ 0x010E
WM_IME_COMPOSITION	equ 0x010F
WM_IME_KEYLAST		equ 0x010F
endif ;; WINVER GE 0x0400

WM_INITDIALOG		equ 0x0110
WM_COMMAND		equ 0x0111
WM_SYSCOMMAND		equ 0x0112
WM_TIMER		equ 0x0113
WM_HSCROLL		equ 0x0114
WM_VSCROLL		equ 0x0115
WM_INITMENU		equ 0x0116
WM_INITMENUPOPUP	equ 0x0117
if(WINVER GE 0x0601)
WM_GESTURE		equ 0x0119
WM_GESTURENOTIFY	equ 0x011A
endif ;; WINVER GE 0x0601
WM_MENUSELECT		equ 0x011F
WM_MENUCHAR		equ 0x0120
WM_ENTERIDLE		equ 0x0121
if(WINVER GE 0x0500)
ifndef _WIN32_WCE
WM_MENURBUTTONUP	equ 0x0122
WM_MENUDRAG		equ 0x0123
WM_MENUGETOBJECT	equ 0x0124
WM_UNINITMENUPOPUP	equ 0x0125
WM_MENUCOMMAND		equ 0x0126
if(_WIN32_WINNT GE 0x0500)
WM_CHANGEUISTATE	equ 0x0127
WM_UPDATEUISTATE	equ 0x0128
WM_QUERYUISTATE		equ 0x0129
;;
;; LOWORD(wParam) values in WM_*UISTATE*
;;
UIS_SET			equ 1
UIS_CLEAR		equ 2
UIS_INITIALIZE		equ 3
;;
;; HIWORD(wParam) values in WM_*UISTATE*
;;
UISF_HIDEFOCUS		equ 0x1
UISF_HIDEACCEL		equ 0x2
if(_WIN32_WINNT GE 0x0501)
UISF_ACTIVE		equ 0x4
endif ;; _WIN32_WINNT GE 0x0501
endif ;; _WIN32_WINNT GE 0x0500
endif ;; NOT _WIN32_WCE
endif ;; WINVER GE 0x0500


WM_CTLCOLORMSGBOX	equ 0x0132
WM_CTLCOLOREDIT		equ 0x0133
WM_CTLCOLORLISTBOX	equ 0x0134
WM_CTLCOLORBTN		equ 0x0135
WM_CTLCOLORDLG		equ 0x0136
WM_CTLCOLORSCROLLBAR	equ 0x0137
WM_CTLCOLORSTATIC	equ 0x0138
MN_GETHMENU		equ 0x01E1


WM_MOUSEFIRST		equ 0x0200
WM_MOUSEMOVE		equ 0x0200
WM_LBUTTONDOWN		equ 0x0201
WM_LBUTTONUP		equ 0x0202
WM_LBUTTONDBLCLK	equ 0x0203
WM_RBUTTONDOWN		equ 0x0204
WM_RBUTTONUP		equ 0x0205
WM_RBUTTONDBLCLK	equ 0x0206
WM_MBUTTONDOWN		equ 0x0207
WM_MBUTTONUP		equ 0x0208
WM_MBUTTONDBLCLK	equ 0x0209
if (_WIN32_WINNT GE 0x0600)
WM_MOUSEHWHEEL		equ 0x020E
elseif (_WIN32_WINNT GE 0x0400) OR (_WIN32_WINDOWS GT 0x0400)
WM_MOUSEWHEEL		equ 0x020A
endif
if (_WIN32_WINNT GE 0x0500)
WM_XBUTTONDOWN		equ 0x020B
WM_XBUTTONUP		equ 0x020C
WM_XBUTTONDBLCLK	equ 0x020D
endif
if (_WIN32_WINNT GE 0x0600)
WM_MOUSELAST		equ 0x020E
elseif (_WIN32_WINNT GE 0x0500)
WM_MOUSELAST		equ 0x020D
elseif (_WIN32_WINNT GE 0x0400) OR (_WIN32_WINDOWS GT 0x0400)
WM_MOUSELAST		equ 0x020A
else
WM_MOUSELAST		equ 0x0209
endif ;; (_WIN32_WINNT GE 0x0600)

if(_WIN32_WINNT GE 0x0400)
WHEEL_DELTA		equ 120	    ;; Value for rolling one detent
endif ;; _WIN32_WINNT GE 0x0400
if(_WIN32_WINNT GE 0x0400)
WHEEL_PAGESCROLL	equ (UINT_MAX) ;; Scroll one page
endif ;; _WIN32_WINNT GE 0x0400

WM_PARENTNOTIFY		equ 0x0210
WM_ENTERMENULOOP	equ 0x0211
WM_EXITMENULOOP		equ 0x0212

if(WINVER GE 0x0400)
WM_NEXTMENU		equ 0x0213
;; end_r_winuser

MDINEXTMENU		STRUC
hmenuIn			HMENU ?
hmenuNext		HMENU ?
hwndNext		HWND ?
MDINEXTMENU		ENDS
PMDINEXTMENU		typedef ptr MDINEXTMENU
LPMDINEXTMENU		typedef ptr MDINEXTMENU

;; begin_r_winuser
WM_SIZING		equ 0x0214
WM_CAPTURECHANGED	equ 0x0215
WM_MOVING		equ 0x0216
;; end_r_winuser
WM_POWERBROADCAST	equ 0x0218	;; r_winuser pbt
;; begin_pbt

PBT_APMQUERYSUSPEND	equ 0x0000
PBT_APMQUERYSTANDBY	equ 0x0001

PBT_APMQUERYSUSPENDFAILED equ 0x0002
PBT_APMQUERYSTANDBYFAILED equ 0x0003

PBT_APMSUSPEND		equ 0x0004
PBT_APMSTANDBY		equ 0x0005

PBT_APMRESUMECRITICAL	equ 0x0006
PBT_APMRESUMESUSPEND	equ 0x0007
PBT_APMRESUMESTANDBY	equ 0x0008

PBTF_APMRESUMEFROMFAILURE equ 0x00000001

PBT_APMBATTERYLOW	equ 0x0009
PBT_APMPOWERSTATUSCHANGE equ 0x000A

PBT_APMOEMEVENT		equ 0x000B
PBT_APMRESUMEAUTOMATIC	equ 0x0012
if (_WIN32_WINNT GE 0x0502)
ifndef PBT_POWERSETTINGCHANGE
PBT_POWERSETTINGCHANGE	equ 0x8013
POWERBROADCAST_SETTING	STRUC
PowerSetting		GUID <>
DataLength		dd ?
Data			db ?
POWERBROADCAST_SETTING	ENDS
PPOWERBROADCAST_SETTING typedef ptr POWERBROADCAST_SETTING
endif ;; PBT_POWERSETTINGCHANGE
endif ;; (_WIN32_WINNT GE 0x0502)

;; end_pbt

;; begin_r_winuser
WM_DEVICECHANGE		equ 0x0219

endif ;; WINVER GE 0x0400

WM_MDICREATE		equ 0x0220
WM_MDIDESTROY		equ 0x0221
WM_MDIACTIVATE		equ 0x0222
WM_MDIRESTORE		equ 0x0223
WM_MDINEXT		equ 0x0224
WM_MDIMAXIMIZE		equ 0x0225
WM_MDITILE		equ 0x0226
WM_MDICASCADE		equ 0x0227
WM_MDIICONARRANGE	equ 0x0228
WM_MDIGETACTIVE		equ 0x0229


WM_MDISETMENU		equ 0x0230
WM_ENTERSIZEMOVE	equ 0x0231
WM_EXITSIZEMOVE		equ 0x0232
WM_DROPFILES		equ 0x0233
WM_MDIREFRESHMENU	equ 0x0234
if(WINVER GE 0x0601)
WM_TOUCH		equ 0x0240
endif ;; WINVER GE 0x0601
if(WINVER GE 0x0400)
WM_IME_SETCONTEXT	equ 0x0281
WM_IME_NOTIFY		equ 0x0282
WM_IME_CONTROL		equ 0x0283
WM_IME_COMPOSITIONFULL	equ 0x0284
WM_IME_SELECT		equ 0x0285
WM_IME_CHAR		equ 0x0286
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0500)
WM_IME_REQUEST		equ 0x0288
endif ;; WINVER GE 0x0500
if(WINVER GE 0x0400)
WM_IME_KEYDOWN		equ 0x0290
WM_IME_KEYUP		equ 0x0291
endif ;; WINVER GE 0x0400
if(_WIN32_WINNT GE 0x0400)
WM_MOUSEHOVER		equ 0x02A1
WM_MOUSELEAVE		equ 0x02A3
endif ;; _WIN32_WINNT GE 0x0400
if(WINVER GE 0x0500)
WM_NCMOUSEHOVER		equ 0x02A0
WM_NCMOUSELEAVE		equ 0x02A2
endif ;; WINVER GE 0x0500
if(_WIN32_WINNT GE 0x0501)
WM_WTSSESSION_CHANGE	equ 0x02B1
WM_TABLET_FIRST		equ 0x02c0
WM_TABLET_LAST		equ 0x02df
endif ;; _WIN32_WINNT GE 0x0501

WM_CUT			equ 0x0300
WM_COPY			equ 0x0301
WM_PASTE		equ 0x0302
WM_CLEAR		equ 0x0303
WM_UNDO			equ 0x0304
WM_RENDERFORMAT		equ 0x0305
WM_RENDERALLFORMATS	equ 0x0306
WM_DESTROYCLIPBOARD	equ 0x0307
WM_DRAWCLIPBOARD	equ 0x0308
WM_PAINTCLIPBOARD	equ 0x0309
WM_VSCROLLCLIPBOARD	equ 0x030A
WM_SIZECLIPBOARD	equ 0x030B
WM_ASKCBFORMATNAME	equ 0x030C
WM_CHANGECBCHAIN	equ 0x030D
WM_HSCROLLCLIPBOARD	equ 0x030E
WM_QUERYNEWPALETTE	equ 0x030F
WM_PALETTEISCHANGING	equ 0x0310
WM_PALETTECHANGED	equ 0x0311
WM_HOTKEY		equ 0x0312

if(WINVER GE 0x0400)
WM_PRINT		equ 0x0317
WM_PRINTCLIENT		equ 0x0318
endif ;; WINVER GE 0x0400
if(_WIN32_WINNT GE 0x0500)
WM_APPCOMMAND		equ 0x0319
endif ;; _WIN32_WINNT GE 0x0500
if(_WIN32_WINNT GE 0x0501)
WM_THEMECHANGED		equ 0x031A
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0501)
WM_CLIPBOARDUPDATE	equ 0x031D
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0600)
WM_DWMCOMPOSITIONCHANGED equ 0x031E
WM_DWMNCRENDERINGCHANGED equ 0x031F
WM_DWMCOLORIZATIONCOLORCHANGED equ 0x0320
WM_DWMWINDOWMAXIMIZEDCHANGE equ 0x0321
endif ;; _WIN32_WINNT GE 0x0600
if(_WIN32_WINNT GE 0x0601)
WM_DWMSENDICONICTHUMBNAIL equ 0x0323
WM_DWMSENDICONICLIVEPREVIEWBITMAP equ 0x0326
endif ;; _WIN32_WINNT GE 0x0601
if(WINVER GE 0x0600)
WM_GETTITLEBARINFOEX	equ 0x033F
endif ;; WINVER GE 0x0600
if(WINVER GE 0x0400)
WM_HANDHELDFIRST	equ 0x0358
WM_HANDHELDLAST		equ 0x035F
WM_AFXFIRST		equ 0x0360
WM_AFXLAST		equ 0x037F
endif ;; WINVER GE 0x0400
WM_PENWINFIRST		equ 0x0380
WM_PENWINLAST		equ 0x038F
if(WINVER GE 0x0400)
WM_APP			equ 0x8000
endif ;; WINVER GE 0x0400

;;
;; NOTE: All Message Numbers below 0x0400 are RESERVED.
;;
;; Private Window Messages Start Here:
;;
WM_USER			equ 0x0400

if(WINVER GE 0x0400)

;;  wParam for WM_SIZING message
WMSZ_LEFT		equ 1
WMSZ_RIGHT		equ 2
WMSZ_TOP		equ 3
WMSZ_TOPLEFT		equ 4
WMSZ_TOPRIGHT		equ 5
WMSZ_BOTTOM		equ 6
WMSZ_BOTTOMLEFT		equ 7
WMSZ_BOTTOMRIGHT	equ 8
endif ;; WINVER GE 0x0400

ifndef NONCMESSAGES

;;
;; WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
;;
HTERROR			equ (-2)
HTTRANSPARENT		equ (-1)
HTNOWHERE		equ 0
HTCLIENT		equ 1
HTCAPTION		equ 2
HTSYSMENU		equ 3
HTGROWBOX		equ 4
HTSIZE			equ HTGROWBOX
HTMENU			equ 5
HTHSCROLL		equ 6
HTVSCROLL		equ 7
HTMINBUTTON		equ 8
HTMAXBUTTON		equ 9
HTLEFT			equ 10
HTRIGHT			equ 11
HTTOP			equ 12
HTTOPLEFT		equ 13
HTTOPRIGHT		equ 14
HTBOTTOM		equ 15
HTBOTTOMLEFT		equ 16
HTBOTTOMRIGHT		equ 17
HTBORDER		equ 18
HTREDUCE		equ HTMINBUTTON
HTZOOM			equ HTMAXBUTTON
HTSIZEFIRST		equ HTLEFT
HTSIZELAST		equ HTBOTTOMRIGHT
if(WINVER GE 0x0400)
HTOBJECT		equ 19
HTCLOSE			equ 20
HTHELP			equ 21
endif ;; WINVER GE 0x0400

;;
;; SendMessageTimeout values
;;
SMTO_NORMAL		equ 0x0000
SMTO_BLOCK		equ 0x0001
SMTO_ABORTIFHUNG	equ 0x0002
if(WINVER GE 0x0500)
SMTO_NOTIMEOUTIFNOTHUNG equ 0x0008
endif ;; WINVER GE 0x0500
if(WINVER GE 0x0600)
SMTO_ERRORONEXIT	equ 0x0020
endif ;; WINVER GE 0x0600

endif ;; NOT NONCMESSAGES

;;
;; WM_MOUSEACTIVATE Return Codes
;;
MA_ACTIVATE		equ 1
MA_ACTIVATEANDEAT	equ 2
MA_NOACTIVATE		equ 3
MA_NOACTIVATEANDEAT	equ 4

;;
;; WM_SETICON / WM_GETICON Type Codes
;;
ICON_SMALL		equ 0
ICON_BIG		equ 1

;; end_r_winuser

;UINT
RegisterWindowMessageA proto _CType \
	      lpString: LPCSTR
;UINT
RegisterWindowMessageW proto _CType \
	      lpString: LPCWSTR
ifdef _UNICODE
RegisterWindowMessage	equ <RegisterWindowMessageW>
else
RegisterWindowMessage	equ <RegisterWindowMessageA>
endif ;; NOT UNICODE

;; begin_r_winuser

;;
;; WM_SIZE message wParam values
;;
SIZE_RESTORED		equ 0
SIZE_MINIMIZED		equ 1
SIZE_MAXIMIZED		equ 2
SIZE_MAXSHOW		equ 3
SIZE_MAXHIDE		equ 4

;;
;; Obsolete constant names
;;
SIZENORMAL		equ SIZE_RESTORED
SIZEICONIC		equ SIZE_MINIMIZED
SIZEFULLSCREEN		equ SIZE_MAXIMIZED
SIZEZOOMSHOW		equ SIZE_MAXSHOW
SIZEZOOMHIDE		equ SIZE_MAXHIDE

;; end_r_winuser
;;
;; WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
;;
WINDOWPOS		STRUC
hwnd			HWND ?
hwndInsertAfter		HWND ?
x			SINT ?
y			SINT ?
_cx			SINT ?
cy			SINT ?
flags			UINT ?
WINDOWPOS		ENDS
LPWINDOWPOS		typedef ptr WINDOWPOS
PWINDOWPOS		typedef ptr WINDOWPOS

;;
;; WM_NCCALCSIZE parameter structure
;;
NCCALCSIZE_PARAMS	STRUC
rgrc			RECT 3 dup(<>)
lppos			PWINDOWPOS ?
NCCALCSIZE_PARAMS	ENDS
LPNCCALCSIZE_PARAMS	typedef ptr NCCALCSIZE_PARAMS

;; begin_r_winuser
;;
;; WM_NCCALCSIZE "window valid rect" return values
;;
WVR_ALIGNTOP		equ 0x0010
WVR_ALIGNLEFT		equ 0x0020
WVR_ALIGNBOTTOM		equ 0x0040
WVR_ALIGNRIGHT		equ 0x0080
WVR_HREDRAW		equ 0x0100
WVR_VREDRAW		equ 0x0200
WVR_REDRAW		equ (WVR_HREDRAW OR \
WVR_VALIDRECTS		equ 0x0400


ifndef NOKEYSTATES

;;
;; Key State Masks for Mouse Messages
;;
MK_LBUTTON		equ 0x0001
MK_RBUTTON		equ 0x0002
MK_SHIFT		equ 0x0004
MK_CONTROL		equ 0x0008
MK_MBUTTON		equ 0x0010
if(_WIN32_WINNT GE 0x0500)
MK_XBUTTON1		equ 0x0020
MK_XBUTTON2		equ 0x0040
endif ;; _WIN32_WINNT GE 0x0500
endif ;; NOT NOKEYSTATES

if(_WIN32_WINNT GE 0x0400)
ifndef NOTRACKMOUSEEVENT

TME_HOVER		equ 0x00000001
TME_LEAVE		equ 0x00000002
if(WINVER GE 0x0500)
TME_NONCLIENT		equ 0x00000010
endif ;; WINVER GE 0x0500
TME_QUERY		equ 0x40000000
TME_CANCEL		equ 0x80000000

HOVER_DEFAULT		equ 0xFFFFFFFF
;; end_r_winuser

TRACKMOUSEEVENT		STRUC
cbSize			dd ?
dwFlags			dd ?
hwndTrack		HWND ?
dwHoverTime		dd ?
TRACKMOUSEEVENT		ENDS
LPTRACKMOUSEEVENT	typedef ptr TRACKMOUSEEVENT

;BOOL
TrackMouseEvent proto _CType \
	  lpEventTrack: LPTRACKMOUSEEVENT

;; begin_r_winuser

endif ;; NOT NOTRACKMOUSEEVENT
endif ;; _WIN32_WINNT GE 0x0400

;; end_r_winuser

endif ;; NOT NOWINMESSAGES

ifndef NOWINSTYLES

;; begin_r_winuser

;;
;; Window Styles
;;
WS_OVERLAPPED		equ 0x00000000
WS_POPUP		equ 0x80000000
WS_CHILD		equ 0x40000000
WS_MINIMIZE		equ 0x20000000
WS_VISIBLE		equ 0x10000000
WS_DISABLED		equ 0x08000000
WS_CLIPSIBLINGS		equ 0x04000000
WS_CLIPCHILDREN		equ 0x02000000
WS_MAXIMIZE		equ 0x01000000
WS_CAPTION		equ 0x00C00000L	    ;; WS_BORDER OR WS_DGFRAME
WS_BORDER		equ 0x00800000
WS_DLGFRAME		equ 0x00400000
WS_VSCROLL		equ 0x00200000
WS_HSCROLL		equ 0x00100000
WS_SYSMENU		equ 0x00080000
WS_THICKFRAME		equ 0x00040000
WS_GROUP		equ 0x00020000
WS_TABSTOP		equ 0x00010000

WS_MINIMIZEBOX		equ 0x00020000
WS_MAXIMIZEBOX		equ 0x00010000


WS_TILED		equ WS_OVERLAPPED
WS_ICONIC		equ WS_MINIMIZE
WS_SIZEBOX		equ WS_THICKFRAME
WS_TILEDWINDOW		equ WS_OVERLAPPEDWINDOW

;;
;; Common Window Styles
;;
WS_OVERLAPPEDWINDOW	equ WS_OVERLAPPED OR WS_CAPTION OR WS_SYSMENU OR \
			WS_THICKFRAME OR WS_MINIMIZEBOX
WS_POPUPWINDOW		equ WS_POPUP OR WS_BORDER
WS_CHILDWINDOW		equ WS_CHILD

;;
;; Extended Window Styles
;;
WS_EX_DLGMODALFRAME	equ 0x00000001
WS_EX_NOPARENTNOTIFY	equ 0x00000004
WS_EX_TOPMOST		equ 0x00000008
WS_EX_ACCEPTFILES	equ 0x00000010
WS_EX_TRANSPARENT	equ 0x00000020
if(WINVER GE 0x0400)
WS_EX_MDICHILD		equ 0x00000040
WS_EX_TOOLWINDOW	equ 0x00000080
WS_EX_WINDOWEDGE	equ 0x00000100
WS_EX_CLIENTEDGE	equ 0x00000200
WS_EX_CONTEXTHELP	equ 0x00000400

WS_EX_RIGHT		equ 0x00001000
WS_EX_LEFT		equ 0x00000000
WS_EX_RTLREADING	equ 0x00002000
WS_EX_LTRREADING	equ 0x00000000
WS_EX_LEFTSCROLLBAR	equ 0x00004000
WS_EX_RIGHTSCROLLBAR	equ 0x00000000

WS_EX_CONTROLPARENT	equ 0x00010000
WS_EX_STATICEDGE	equ 0x00020000
WS_EX_APPWINDOW		equ 0x00040000


WS_EX_OVERLAPPEDWINDOW	equ WS_EX_WINDOWEDGE OR WS_EX_CIENTEDGE
WS_EX_PALETTEWINDOW	equ WS_EX_WINDOWEDGE OR WS_EX_TOOLWINDOW OR WS_EX_TOPMOST

endif ;; WINVER GE 0x0400

if(_WIN32_WINNT GE 0x0500)
WS_EX_LAYERED		equ 0x00080000
endif ;; _WIN32_WINNT GE 0x0500

if(WINVER GE 0x0500)
WS_EX_NOINHERITLAYOUT	equ 0x00100000 ;; Disable inheritence of mirroring by children
WS_EX_LAYOUTRTL		equ 0x00400000 ;; Right to left mirroring
endif ;; WINVER GE 0x0500

if(_WIN32_WINNT GE 0x0501)
WS_EX_COMPOSITED	equ 0x02000000
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0500)
WS_EX_NOACTIVATE	equ 0x08000000
endif ;; _WIN32_WINNT GE 0x0500

;;
;; Class styles
;;
CS_VREDRAW		equ 0x0001
CS_HREDRAW		equ 0x0002
CS_DBLCLKS		equ 0x0008
CS_OWNDC		equ 0x0020
CS_CLASSDC		equ 0x0040
CS_PARENTDC		equ 0x0080
CS_NOCLOSE		equ 0x0200
CS_SAVEBITS		equ 0x0800
CS_BYTEALIGNCLIENT	equ 0x1000
CS_BYTEALIGNWINDOW	equ 0x2000
CS_GLOBALCLASS		equ 0x4000

CS_IME			equ 0x00010000
if(_WIN32_WINNT GE 0x0501)
CS_DROPSHADOW		equ 0x00020000
endif ;; _WIN32_WINNT GE 0x0501


;; end_r_winuser

endif ;; NOT NOWINSTYLES
if(WINVER GE 0x0400)
;; WM_PRINT flags
PRF_CHECKVISIBLE	equ 0x00000001
PRF_NONCLIENT		equ 0x00000002
PRF_CLIENT		equ 0x00000004
PRF_ERASEBKGND		equ 0x00000008
PRF_CHILDREN		equ 0x00000010
PRF_OWNED		equ 0x00000020

;; 3D border styles
BDR_RAISEDOUTER		equ 0x0001
BDR_SUNKENOUTER		equ 0x0002
BDR_RAISEDINNER		equ 0x0004
BDR_SUNKENINNER		equ 0x0008

BDR_OUTER		equ 0x0003
BDR_INNER		equ 0x000c

EDGE_RAISED		equ BDR_RAISEDOUTER OR BDR_RAISEDINNER
EDGE_SUNKEN		equ BDR_SUNKENOUTER OR BDR_SUNKENINNER
EDGE_ETCHED		equ BDR_SUNKENOUTER OR BDR_RAISEDINNER
EDGE_BUMP		equ BDR_RAISEDOUTER OR BDR_SUNKENINNER

;; Border flags
BF_LEFT			equ 0x0001
BF_TOP			equ 0x0002
BF_RIGHT		equ 0x0004
BF_BOTTOM		equ 0x0008

BF_TOPLEFT		equ BF_TOP OR BF_LEFT
BF_TOPRIGHT		equ BF_TOP OR BF_RIGHT
BF_BOTTOMLEFT		equ BF_BOTTOM OR BF_LEFT
BF_BOTTOMRIGHT		equ BF_BOTTOM OR BF_RIGHT
BF_RECT			equ BF_LEFT OR BF_TOP OR BF_RIGHT OR BF_BOTTOM

BF_DIAGONAL		equ 0x0010

;; For diagonal lines, the BF_RECT flags specify the end point of the
;; vector bounded by the rectangle parameter.
BF_DIAGONAL_ENDTOPRIGHT equ (BF_DIAGONA OR BF_TOP OR BF_RIGHT)
BF_DIAGONAL_ENDTOPLEFT	equ (BF_DIAGONAL OR BF_TOP OR BF_LEFT)
BF_DIAGONAL_ENDBOTTOMLEFT equ (BF_DIAGONAL OR BF_BOTTOM OR BF_LEFT)
BF_DIAGONAL_ENDBOTTOMRIGHT equ (BF_DIAGONA OR BF_BOTTOM OR BF_RIGHT)


BF_MIDDLE		equ 0x0800  ;; Fill in the middle
BF_SOFT			equ 0x1000  ;; For softer buttons
BF_ADJUST		equ 0x2000  ;; Calculate the space left over
BF_FLAT			equ 0x4000  ;; For flat rather than 3D borders
BF_MONO			equ 0x8000  ;; For monochrome borders


;BOOL
DrawEdge proto _CType \
		   hdc: HDC,
		   qrc: LPRECT,
		  edge: UINT,
	      grfFlags: UINT

;; flags for DrawFrameControl

DFC_CAPTION		equ 1
DFC_MENU		equ 2
DFC_SCROLL		equ 3
DFC_BUTTON		equ 4
if(WINVER GE 0x0500)
DFC_POPUPMENU		equ 5
endif ;; WINVER GE 0x0500

DFCS_CAPTIONCLOSE	equ 0x0000
DFCS_CAPTIONMIN		equ 0x0001
DFCS_CAPTIONMAX		equ 0x0002
DFCS_CAPTIONRESTORE	equ 0x0003
DFCS_CAPTIONHELP	equ 0x0004

DFCS_MENUARROW		equ 0x0000
DFCS_MENUCHECK		equ 0x0001
DFCS_MENUBULLET		equ 0x0002
DFCS_MENUARROWRIGHT	equ 0x0004
DFCS_SCROLLUP		equ 0x0000
DFCS_SCROLLDOWN		equ 0x0001
DFCS_SCROLLLEFT		equ 0x0002
DFCS_SCROLLRIGHT	equ 0x0003
DFCS_SCROLLCOMBOBOX	equ 0x0005
DFCS_SCROLLSIZEGRIP	equ 0x0008
DFCS_SCROLLSIZEGRIPRIGHT equ 0x0010

DFCS_BUTTONCHECK	equ 0x0000
DFCS_BUTTONRADIOIMAGE	equ 0x0001
DFCS_BUTTONRADIOMASK	equ 0x0002
DFCS_BUTTONRADIO	equ 0x0004
DFCS_BUTTON3STATE	equ 0x0008
DFCS_BUTTONPUSH		equ 0x0010

DFCS_INACTIVE		equ 0x0100
DFCS_PUSHED		equ 0x0200
DFCS_CHECKED		equ 0x0400

if(WINVER GE 0x0500)
DFCS_TRANSPARENT	equ 0x0800
DFCS_HOT		equ 0x1000
endif ;; WINVER GE 0x0500

DFCS_ADJUSTRECT		equ 0x2000
DFCS_FLAT		equ 0x4000
DFCS_MONO		equ 0x8000

;BOOL
DrawFrameControl proto _CType \
		      : HDC,
		      : LPRECT,
		      : UINT,
		      : UINT


;; flags for DrawCaption
DC_ACTIVE		equ 0x0001
DC_SMALLCAP		equ 0x0002
DC_ICON			equ 0x0004
DC_TEXT			equ 0x0008
DC_INBUTTON		equ 0x0010
if(WINVER GE 0x0500)
DC_GRADIENT		equ 0x0020
endif ;; WINVER GE 0x0500
if(_WIN32_WINNT GE 0x0501)
DC_BUTTONS		equ 0x1000
endif ;; _WIN32_WINNT GE 0x0501

;BOOL
DrawCaption proto _CType \
		      : HWND,
		      : HDC,
		      : LPRECT,
		      : UINT


IDANI_OPEN		equ 1
IDANI_CLOSE		equ 2
IDANI_CAPTION		equ 3

;BOOL
DrawAnimatedRects proto _CType \
		  hwnd: HWND,
		 idAni: SINT,
	      lprcFrom: LPRECT,
		lprcTo: LPRECT

endif ;; WINVER GE 0x0400

ifndef NOCLIPBOARD

;; begin_r_winuser

;;
;; Predefined Clipboard Formats
;;
CF_TEXT			equ 1
CF_BITMAP		equ 2
CF_METAFILEPICT		equ 3
CF_SYLK			equ 4
CF_DIF			equ 5
CF_TIFF			equ 6
CF_OEMTEXT		equ 7
CF_DIB			equ 8
CF_PALETTE		equ 9
CF_PENDATA		equ 10
CF_RIFF			equ 11
CF_WAVE			equ 12
CF_UNICODETEXT		equ 13
CF_ENHMETAFILE		equ 14
if (WINVER GE 0x0400)
CF_HDROP		equ 15
CF_LOCALE		equ 16
endif ;; WINVER GE 0x0400
if (WINVER GE 0x0500)
CF_DIBV5		equ 17
endif ;; WINVER GE 0x0500
if (WINVER GE 0x0500)
CF_MAX			equ 18
elseif (WINVER GE 0x0400)
CF_MAX			equ 17
else
CF_MAX			equ 15
endif

CF_OWNERDISPLAY		equ 0x0080
CF_DSPTEXT		equ 0x0081
CF_DSPBITMAP		equ 0x0082
CF_DSPMETAFILEPICT	equ 0x0083
CF_DSPENHMETAFILE	equ 0x008E

;;
;; "Private" formats don't get GlobalFree()'d
;;
CF_PRIVATEFIRST		equ 0x0200
CF_PRIVATELAST		equ 0x02FF

;;
;; "GDIOBJ" formats do get DeleteObject()'d
;;
CF_GDIOBJFIRST		equ 0x0300
CF_GDIOBJLAST		equ 0x03FF

;; end_r_winuser

endif ;; NOT NOCLIPBOARD

;;
;; Defines for the fVirt field of the Accelerator table structure.
;;
FVIRTKEY		equ TRUE	  ;; Assumed to be EQ TRUE
FNOINVERT		equ 0x02
FSHIFT			equ 0x04
FCONTROL		equ 0x08
FALT			equ 0x10

ACCEL			STRUC
ifndef _MAC
fVirt			db ?	;; Also called the flags field
key			dw ?
cmd			dw ?
else
fVirt			dw ?	;; Also called the flags field
key			dw ?
cmd			dd ?
endif
ACCEL			ENDS
LPACCEL			typedef ptr ACCEL

PAINTSTRUCT		STRUC
hdc			HDC ?
fErase			BOOL ?
rcPaint			RECT <>
fRestore		BOOL ?
fIncUpdate		BOOL ?
rgbReserved		db 32 dup(?)
PAINTSTRUCT		ENDS
PPAINTSTRUCT		typedef ptr PAINTSTRUCT
NPPAINTSTRUCT		typedef ptr PAINTSTRUCT
LPPAINTSTRUCT		typedef ptr PAINTSTRUCT

CREATESTRUCTA		STRUC
lpCreateParams		LPVOID ?
hInstance		HINSTANCE ?
hMenu			HMENU ?
hwndParent		HWND ?
cy			SINT ?
_cx			SINT ?
y			SINT ?
x			SINT ?
style			LONG ?
lpszName		LPCSTR ?
lpszClass		LPCSTR ?
dwExStyle		dd ?
CREATESTRUCTA		ENDS
LPCREATESTRUCTA		typedef ptr CREATESTRUCTA
CREATESTRUCTW		STRUC
lpCreateParams		LPVOID ?
hInstance		HINSTANCE ?
hMenu			HMENU ?
hwndParent		HWND ?
cy			SINT ?
_cx			SINT ?
y			SINT ?
x			SINT ?
style			LONG ?
lpszName		LPCWSTR ?
lpszClass		LPCWSTR ?
dwExStyle		dd ?
CREATESTRUCTW		ENDS
LPCREATESTRUCTW		typedef ptr CREATESTRUCTW
ifdef _UNICODE
CREATESTRUCT		typedef CREATESTRUCTW
LPCREATESTRUCT		typedef LPCREATESTRUCTW
else
CREATESTRUCT		typedef CREATESTRUCTA
LPCREATESTRUCT		typedef LPCREATESTRUCTA
endif ;; UNICODE

WINDOWPLACEMENT		STRUC
_length			UINT ?
flags			UINT ?
showCmd			UINT ?
ptMinPosition		POINT <>
ptMaxPosition		POINT <>
rcNormalPosition	RECT <>
ifdef _MAC
rcDevice		RECT <>
endif
WINDOWPLACEMENT		ENDS
LPWINDOWPLACEMENT	typedef ptr WINDOWPLACEMENT
PWINDOWPLACEMENT	typedef ptr WINDOWPLACEMENT

WPF_SETMINPOSITION	equ 0x0001
WPF_RESTORETOMAXIMIZED	equ 0x0002
if(WINVER GE 0x0400)
NMHDR			STRUC
hwndFrom		HWND ?
idFrom			UINT ?
code			UINT ?	;; NM_ code
NMHDR			ENDS
LPNMHDR			typedef ptr NMHDR

STYLESTRUCT		STRUC
styleOld		dd ?
styleNew		dd ?
STYLESTRUCT		ENDS
LPSTYLESTRUCT		typedef ptr STYLESTRUCT
endif ;; WINVER GE 0x0400


;;
;; Owner draw control types
;;
ODT_MENU		equ 1
ODT_LISTBOX		equ 2
ODT_COMBOBOX		equ 3
ODT_BUTTON		equ 4
if(WINVER GE 0x0400)
ODT_STATIC		equ 5
endif ;; WINVER GE 0x0400

;;
;; Owner draw actions
;;
ODA_DRAWENTIRE		equ 0x0001
ODA_SELECT		equ 0x0002
ODA_FOCUS		equ 0x0004

;;
;; Owner draw state
;;
ODS_SELECTED		equ 0x0001
ODS_GRAYED		equ 0x0002
ODS_DISABLED		equ 0x0004
ODS_CHECKED		equ 0x0008
ODS_FOCUS		equ 0x0010
if(WINVER GE 0x0400)
ODS_DEFAULT		equ 0x0020
ODS_COMBOBOXEDIT	equ 0x1000
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0500)
ODS_HOTLIGHT		equ 0x0040
ODS_INACTIVE		equ 0x0080
if(_WIN32_WINNT GE 0x0500)
ODS_NOACCEL		equ 0x0100
ODS_NOFOCUSRECT		equ 0x0200
endif ;; _WIN32_WINNT GE 0x0500
endif ;; WINVER GE 0x0500

;;
;; MEASUREITEMSTRUCT for ownerdraw
;;
MEASUREITEMSTRUCT	STRUC
CtlType			UINT ?
CtlID			UINT ?
itemID			UINT ?
itemWidth		UINT ?
itemHeight		UINT ?
itemData		PVOID ?
MEASUREITEMSTRUCT	ENDS
PMEASUREITEMSTRUCT	typedef ptr MEASUREITEMSTRUCT
LPMEASUREITEMSTRUCT	typedef ptr MEASUREITEMSTRUCT


;;
;; DRAWITEMSTRUCT for ownerdraw
;;
DRAWITEMSTRUCT		STRUC
CtlType			UINT ?
CtlID			UINT ?
itemID			UINT ?
itemAction		UINT ?
itemState		UINT ?
hwndItem		HWND ?
hDC			HDC ?
rcItem			RECT <>
itemData		PVOID ?
DRAWITEMSTRUCT		ENDS
PDRAWITEMSTRUCT		typedef ptr DRAWITEMSTRUCT
LPDRAWITEMSTRUCT	typedef ptr DRAWITEMSTRUCT

;;
;; DELETEITEMSTRUCT for ownerdraw
;;
DELETEITEMSTRUCT	STRUC
CtlType			UINT ?
CtlID			UINT ?
itemID			UINT ?
hwndItem		HWND ?
itemData		PVOID ?
DELETEITEMSTRUCT	ENDS
PDELETEITEMSTRUCT	typedef ptr DELETEITEMSTRUCT
LPDELETEITEMSTRUCT	typedef ptr DELETEITEMSTRUCT

;;
;; COMPAREITEMSTUCT for ownerdraw sorting
;;
COMPAREITEMSTRUCT	STRUC
CtlType			UINT ?
CtlID			UINT ?
hwndItem		HWND ?
itemID1			UINT ?
itemData1		PVOID ?
itemID2			UINT ?
itemData2		PVOID ?
dwLocaleId		dd ?
COMPAREITEMSTRUCT	ENDS
PCOMPAREITEMSTRUCT	typedef ptr COMPAREITEMSTRUCT
LPCOMPAREITEMSTRUCT	typedef ptr COMPAREITEMSTRUCT

ifndef NOMSG

;;
;; Message Function Templates
;;

;BOOL
GetMessageA proto _CType \
		 lpMsg: LPMSG,
		 hWnd : HWND,
	 wMsgFilterMin: UINT,
	 wMsgFilterMax: UINT
;BOOL
GetMessageW proto _CType \
		 lpMsg: LPMSG,
		 hWnd : HWND,
	 wMsgFilterMin: UINT,
	 wMsgFilterMax: UINT
ifdef _UNICODE
GetMessage		equ <GetMessageW>
else
GetMessage		equ <GetMessageA>
endif ;; NOT UNICODE

;BOOL
TranslateMessage proto _CType \
		 lpMsg: ptr MSG

;LONG
DispatchMessageA proto _CType \
		 lpMsg: ptr MSG
;LONG
DispatchMessageW proto _CType \
		 lpMsg: ptr MSG
ifdef _UNICODE
DispatchMessage		equ <DispatchMessageW>
else
DispatchMessage		equ <DispatchMessageA>
endif ;; NOT UNICODE


;BOOL
SetMessageQueue proto _CType \
	  cMessagesMax: SINT

;BOOL
PeekMessageA proto _CType \
		 lpMsg: LPMSG,
		 hWnd : HWND,
	 wMsgFilterMin: UINT,
	 wMsgFilterMax: UINT,
	    wRemoveMsg: UINT
;BOOL
PeekMessageW proto _CType \
		 lpMsg: LPMSG,
		 hWnd : HWND,
	 wMsgFilterMin: UINT,
	 wMsgFilterMax: UINT,
	    wRemoveMsg: UINT
ifdef _UNICODE
PeekMessage		equ <PeekMessageW>
else
PeekMessage		equ <PeekMessageA>
endif ;; NOT UNICODE

;;
;; PeekMessage() Options
;;
PM_NOREMOVE		equ 0x0000
PM_REMOVE		equ 0x0001
PM_NOYIELD		equ 0x0002
if(WINVER GE 0x0500)
PM_QS_INPUT		equ (QS_INPUT SHL 16)
PM_QS_POSTMESSAGE	equ ((QS_POSTMESSAGE OR QS_HOTKEY OR QS_TIMER) SHL 16)
PM_QS_PAINT		equ (QS_PAINT SHL 16)
PM_QS_SENDMESSAGE	equ (QS_SENDMESSAGE SHL 16)
endif ;; WINVER GE 0x0500

endif ;; NOT NOMSG

;BOOL
RegisterHotKey proto _CType \
		 hWnd : HWND,
		    id: SINT,
	   fsModifiers: UINT,
		    vk: UINT

;BOOL
UnregisterHotKey proto _CType \
		  hWnd: HWND,
		    id: SINT

MOD_ALT			equ 0x0001
MOD_CONTROL		equ 0x0002
MOD_SHIFT		equ 0x0004
MOD_WIN			equ 0x0008
if(WINVER GE 0x0601)
MOD_NOREPEAT		equ 0x4000
endif ;; WINVER GE 0x0601

IDHOT_SNAPWINDOW	equ (-1)    ;; SHIFT-PRINTSCRN
IDHOT_SNAPDESKTOP	equ (-2)    ;; PRINTSCRN

ifdef WIN_INTERNAL
ifndef LSTRING
NOLSTRING equ 1
endif ;; LSTRING
ifndef LFILEIO
NOLFILEIO equ 1
endif ;; LFILEIO
endif ;; WIN_INTERNAL

if(WINVER GE 0x0400)

ENDSESSION_LOGOFF	equ 0x80000000
endif ;; WINVER GE 0x0400

EWX_LOGOFF		equ 0
EWX_SHUTDOWN		equ 0x00000001
EWX_REBOOT		equ 0x00000002
EWX_FORCE		equ 0x00000004
EWX_POWEROFF		equ 0x00000008
if(_WIN32_WINNT GE 0x0500)
EWX_FORCEIFHUNG		equ 0x00000010
endif ;; _WIN32_WINNT GE 0x0500
EWX_QUICKRESOLVE	equ 0x00000020
if(_WIN32_WINNT GE 0x0600)
EWX_RESTARTAPPS		equ 0x00000040
endif ;; _WIN32_WINNT GE 0x0600


ExitWindows macro dwReserved, Code
	exitm<ExitWindowsEx(EWX_LOGOFF, 0xFFFFFFFF)>
	endm

;BOOL
ExitWindowsEx proto _CType \
		uFlags: UINT,
	    dwReserved: DWORD

;BOOL
SwapMouseButton proto _CType \
		 fSwap: BOOL

;DWORD
GetMessagePos proto _CType

;LONG
GetMessageTime proto _CType

;LONG
GetMessageExtraInfo proto _CType

if(_WIN32_WINNT GE 0x0501)
;BOOL
IsWow64Message proto _CType
endif ;; _WIN32_WINNT GE 0x0501

if(WINVER GE 0x0400)
;LPARAM
SetMessageExtraInfo proto _CType \
		lParam: LPARAM
endif ;; WINVER GE 0x0400

;LRESULT
SendMessageA proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;LRESULT
SendMessageW proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
SendMessage		equ <SendMessageW>
else
SendMessage		equ <SendMessageA>
endif ;; NOT UNICODE

;LRESULT
SendMessageTimeoutA proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
	       fuFlags: UINT,
	      uTimeout: UINT,
	    lpdwResult: LPDWORD
;LRESULT
SendMessageTimeoutW proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
	       fuFlags: UINT,
	      uTimeout: UINT,
	    lpdwResult: LPDWORD
ifdef _UNICODE
SendMessageTimeout	equ <SendMessageTimeoutW>
else
SendMessageTimeout	equ <SendMessageTimeoutA>
endif ;; NOT UNICODE

;BOOL
SendNotifyMessageA proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;BOOL
SendNotifyMessageW proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
SendNotifyMessage	equ <SendNotifyMessageW>
else
SendNotifyMessage	equ <SendNotifyMessageA>
endif ;; NOT UNICODE

;BOOL
SendMessageCallbackA proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
      lpResultCallBack: SENDASYNCPROC,
		dwData: DWORD
SendMessageCallbackW proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
      lpResultCallBack: SENDASYNCPROC,
		dwData: DWORD
ifdef _UNICODE
SendMessageCallback	equ <SendMessageCallbackW>
else
SendMessageCallback	equ <SendMessageCallbackA>
endif ;; NOT UNICODE

if(_WIN32_WINNT GE 0x0501)
BSMINFO			STRUC
cbSize			UINT ?
hdesk			HDESK ?
hwnd			HWND ?
luid			LUID <>
BSMINFO			ENDS
PBSMINFO		typedef ptr BSMINFO

;WINUSERAPI
;long
BroadcastSystemMessageExA proto _CType \
		 flags: DWORD,
		lpInfo: LPDWORD,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
	      pbsmInfo: PBSMINFO
BroadcastSystemMessageExW proto _CType \
		 flags: DWORD,
		lpInfo: LPDWORD,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM,
	      pbsmInfo: PBSMINFO
ifdef _UNICODE
BroadcastSystemMessageEx equ <BroadcastSystemMessageExW>
else
BroadcastSystemMessageEx equ <BroadcastSystemMessageExA>
endif ;; NOT UNICODE
endif ;; _WIN32_WINNT GE 0x0501

if(WINVER GE 0x0400)

ifdef _WIN32_WINNT
;long
BroadcastSystemMessageA proto _CType \
		      : DWORD,
		      : LPDWORD,
		      : UINT,
		      : WPARAM,
		      : LPARAM
;long
BroadcastSystemMessageW proto _CType \
		      : DWORD,
		      : LPDWORD,
		      : UINT,
		      : WPARAM,
		      : LPARAM
ifdef _UNICODE
BroadcastSystemMessage	equ <BroadcastSystemMessageW>
else
BroadcastSystemMessage	equ <BroadcastSystemMessageA>
endif ;; NOT UNICODE
elseifdef _WIN32_WINDOWS
;; The Win95 version isn't A/W decorated
;long
BroadcastSystemMessage proto _CType \
		      : DWORD,
		      : LPDWORD,
		      : UINT,
		      : WPARAM,
		      : LPARAM
endif

;;Broadcast Special Message Recipient list
BSM_ALLCOMPONENTS	equ 0x00000000
BSM_VXDS		equ 0x00000001
BSM_NETDRIVER		equ 0x00000002
BSM_INSTALLABLEDRIVERS	equ 0x00000004
BSM_APPLICATIONS	equ 0x00000008
BSM_ALLDESKTOPS		equ 0x00000010

;;Broadcast Special Message Flags
BSF_QUERY		equ 0x00000001
BSF_IGNORECURRENTTASK	equ 0x00000002
BSF_FLUSHDISK		equ 0x00000004
BSF_NOHANG		equ 0x00000008
BSF_POSTMESSAGE		equ 0x00000010
BSF_FORCEIFHUNG		equ 0x00000020
BSF_NOTIMEOUTIFNOTHUNG	equ 0x00000040
if(_WIN32_WINNT GE 0x0500)
BSF_ALLOWSFW		equ 0x00000080
BSF_SENDNOTIFYMESSAGE	equ 0x00000100
endif ;; _WIN32_WINNT GE 0x0500
if(_WIN32_WINNT GE 0x0501)
BSF_RETURNHDESK		equ 0x00000200
BSF_LUID		equ 0x00000400
endif ;; _WIN32_WINNT GE 0x0501
BROADCAST_QUERY_DENY	equ 0x424D5144	;; Return this value to deny a query.
endif ;; WINVER GE 0x0400

;; RegisterDeviceNotification

if(WINVER GE 0x0500)
HDEVNOTIFY	typedef PVOID
PHDEVNOTIFY	typedef ptr HDEVNOTIFY

DEVICE_NOTIFY_WINDOW_HANDLE  equ 0x00000000
DEVICE_NOTIFY_SERVICE_HANDLE equ 0x00000001
if(_WIN32_WINNT GE 0x0501)
DEVICE_NOTIFY_ALL_INTERFACE_CLASSES equ 0x00000004
endif ;; _WIN32_WINNT GE 0x0501
;HDEVNOTIFY
RegisterDeviceNotificationA proto _CType \
	      hRecipient: HANDLE,
      NotificationFilter: LPVOID,
		  Flags : DWORD
RegisterDeviceNotificationW proto _CType \
	      hRecipient: HANDLE,
      NotificationFilter: LPVOID,
		  Flags : DWORD
ifdef _UNICODE
RegisterDeviceNotification equ <RegisterDeviceNotificationW>
else
RegisterDeviceNotification equ <RegisterDeviceNotificationA>
endif ;; NOT UNICODE

;BOOL
UnregisterDeviceNotification proto _CType \
	      Handle : HDEVNOTIFY

if (_WIN32_WINNT GE 0x0502)
ifndef _HPOWERNOTIFY_DEF_
_HPOWERNOTIFY_DEF_	equ 1
HPOWERNOTIFY	typedef PVOID
PHPOWERNOTIFY	typedef ptr HPOWERNOTIFY
endif

LPCGUID			typedef ptr GUID
;WINUSERAPI
;HPOWERNOTIFY
RegisterPowerSettingNotification proto _CType \
	    hRecipient: HANDLE,
      PowerSettingGuid: LPCGUID,
		 Flags: DWORD

;BOOL
UnregisterPowerSettingNotification proto _CType \
		Handle: HPOWERNOTIFY
endif ;; (_WIN32_WINNT GE 0x0502)

endif ;; WINVER GE 0x0500
endif ;; WINVER GE 0x0500


;BOOL
PostMessageA proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;BOOL
PostMessageW proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
PostMessage		equ <PostMessageW>
else
PostMessage		equ <PostMessageA>
endif ;; NOT UNICODE

;BOOL
PostThreadMessageA proto _CType \
	      idThread: DWORD,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;BOOL
PostThreadMessageW proto _CType \
	      idThread: DWORD,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
PostThreadMessage	equ <PostThreadMessageW>
else
PostThreadMessage	equ <PostThreadMessageA>
endif ;; NOT UNICODE

PostAppMessageA macro idThread,wMsg,wParam,lParam
	exitm <PostThreadMessageA(idThread,wMsg,wParam,lParam)>
	endm
PostAppMessageW macro idThread,wMsg,wParam,lParam
	exitm <PostThreadMessageW(idThread,wMsg,wParam,lParam)>
	endm
ifdef _UNICODE
PostAppMessage		equ <PostAppMessageW>
else
PostAppMessage		equ <PostAppMessageA>
endif ;; NOT UNICODE

;;
;; Special HWND value for use with PostMessage() and SendMessage()
;;
HWND_BROADCAST		equ 0xffff

if(WINVER GE 0x0500)
HWND_MESSAGE		equ (-3)
endif ;; WINVER GE 0x0500

;BOOL
AttachThreadInput proto _CType \
	      idAttach: DWORD,
	    idAttachTo: DWORD,
	       fAttach: BOOL
;BOOL
ReplyMessage proto _CType \
	       lResult: LRESULT
;BOOL
WaitMessage proto _CType
;DWORD
WaitForInputIdle proto _CType \
	      hProcess: HANDLE,
	dwMilliseconds: DWORD

;LRESULT
;CALLBACK
DefWindowProcA typedef proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
DefWindowProcW typedef proto _CType \
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
DefWindowProc  typedef	ptr DefWindowProcW
else
DefWindowProc  typedef	ptr DefWindowProcA
endif ;; !UNICODE

;VOID
PostQuitMessage proto _CType \
	     nExitCode: SINT

ifdef STRICT

;LRESULT
CallWindowProcA proto _CType \
	 lpPrevWndFunc: WNDPROC,
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;LRESULT
CallWindowProcW proto _CType \
	 lpPrevWndFunc: WNDPROC,
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
CallWindowProc		equ <CallWindowProcW>
else
CallWindowProc		equ <CallWindowProcA>
endif ;; NOT UNICODE

else ;; NOT STRICT

;LRESULT
CallWindowProcA proto _CType \
	 lpPrevWndFunc: FARPROC,
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;LRESULT
CallWindowProcW proto _CType \
	 lpPrevWndFunc: FARPROC,
		  hWnd: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
CallWindowProc		equ <CallWindowProcW>
else
CallWindowProc		equ <CallWindowProcA>
endif ;; NOT UNICODE

endif ;; NOT STRICT

;BOOL
InSendMessage proto _CType

if(WINVER GE 0x0500)
;DWORD
InSendMessageEx proto _CType \
	    lpReserved: LPVOID

;;
;; InSendMessageEx return value
;;
ISMEX_NOSEND		equ 0x00000000
ISMEX_SEND		equ 0x00000001
ISMEX_NOTIFY		equ 0x00000002
ISMEX_CALLBACK		equ 0x00000004
ISMEX_REPLIED		equ 0x00000008
endif ;; WINVER GE 0x0500

;UINT
GetDoubleClickTime proto _CType

;BOOL
SetDoubleClickTime proto _CType \
		      : UINT

;ATOM
RegisterClassA proto _CType \
	    lpWndClass: ptr WNDCLASSA
;ATOM
RegisterClassW proto _CType \
	    lpWndClass: ptr WNDCLASSA
ifdef _UNICODE
RegisterClass		equ <RegisterClassW>
else
RegisterClass		equ <RegisterClassA>
endif ;; NOT UNICODE

;BOOL
UnregisterClassA proto _CType \
	   lpClassName: LPCSTR,
	     hInstance: HINSTANCE
;BOOL
UnregisterClassW proto _CType \
	   lpClassName: LPCWSTR,
	     hInstance: HINSTANCE
ifdef _UNICODE
UnregisterClass		equ <UnregisterClassW>
else
UnregisterClass		equ <UnregisterClassA>
endif ;; NOT UNICODE

;BOOL
GetClassInfoA proto _CType \
	    hInstance : HINSTANCE,
	   lpClassName: LPCSTR,
	    lpWndClass: LPWNDCLASSA
;BOOL
GetClassInfoW proto _CType \
	    hInstance : HINSTANCE,
	   lpClassName: LPCWSTR,
	    lpWndClass: LPWNDCLASSW
ifdef _UNICODE
GetClassInfo		equ <GetClassInfoW>
else
GetClassInfo		equ <GetClassInfoA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;ATOM
RegisterClassExA proto _CType \
		      : ptr WNDCLASSEXA
RegisterClassExW proto _CType \
		      : ptr WNDCLASSEXW
ifdef _UNICODE
RegisterClassEx		equ <RegisterClassExW>
else
RegisterClassEx		equ <RegisterClassExA>
endif ;; NOT UNICODE

;BOOL
GetClassInfoExA proto _CType \
		      : HINSTANCE,
		      : LPCSTR,
		      : LPWNDCLASSEXA
GetClassInfoExW proto _CType \
		      : HINSTANCE,
		      : LPCWSTR,
		      : LPWNDCLASSEXW
ifdef _UNICODE
GetClassInfoEx		equ <GetClassInfoExW>
else
GetClassInfoEx		equ <GetClassInfoExA>
endif ;; NOT UNICODE

endif ;; WINVER GE 0x0400

CW_USEDEFAULT		equ 0x80000000

;;
;; Special value for CreateWindow, et al.
;;
HWND_DESKTOP		equ 0
if(_WIN32_WINNT GE 0x0501)
PREGISTERCLASSNAMEW_T typedef proto \
		      : LPCWSTR
PREGISTERCLASSNAMEW typedef ptr PREGISTERCLASSNAMEW_T
endif ;; _WIN32_WINNT GE 0x0501

;HWND
CreateWindowExA proto _CType \
	     dwExStyle: DWORD,
	   lpClassName: LPCSTR,
	  lpWindowName: LPCSTR,
	       dwStyle: DWORD,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	    hWndParent: HWND,
		 hMenu: HMENU,
	     hInstance: HINSTANCE,
	       lpParam: LPVOID
;HWND
CreateWindowExW proto _CType \
	     dwExStyle: DWORD,
	   lpClassName: LPCWSTR,
	  lpWindowName: LPCWSTR,
	       dwStyle: DWORD,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	    hWndParent: HWND,
		 hMenu: HMENU,
	     hInstance: HINSTANCE,
	       lpParam: LPVOID
ifdef _UNICODE
CreateWindowEx		equ <CreateWindowExW>
else
CreateWindowEx		equ <CreateWindowExA>
endif ;; NOT UNICODE

CreateWindowA macro lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam
	exitm<CreateWindowExA(0, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)>
	endm

CreateWindowW macro lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam
	exitm<CreateWindowExW(0, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)>
	endm

ifdef _UNICODE
CreateWindow		equ <CreateWindowW>
else
CreateWindow		equ <CreateWindowA>
endif ;; NOT UNICODE

;BOOL
IsWindow proto _CType \
		  hWnd: HWND

;BOOL
IsMenu proto _CType \
		 hMenu: HMENU

;BOOL
IsChild proto _CType \
	    hWndParent: HWND,
		  hWnd: HWND

;BOOL
DestroyWindow proto _CType \
		  hWnd: HWND

;BOOL
ShowWindow proto _CType \
		  hWnd: HWND,
	      nCmdShow: SINT

if(WINVER GE 0x0500)
;BOOL
AnimateWindow proto _CType \
		  hWnd: HWND,
		dwTime: DWORD,
	       dwFlags: DWORD
endif ;; WINVER GE 0x0500

if(_WIN32_WINNT GE 0x0500)
if defined(_WINGDI_) AND NOT defined(NOGDI)

;BOOL
UpdateLayeredWindow proto _CType \
		  hWnd: HWND,
		hdcDst: HDC,
		pptDst: ptr POINT,
		 psize: ptr POINT,
		hdcSrc: HDC,
		pptSrc: ptr POINT,
		 crKey: COLORREF,
		pblend: ptr BLENDFUNCTION,
	       dwFlags: DWORD

LPBLENDFUNCTION		typedef ptr BLENDFUNCTION
;;
;; Layered Window Update information
;;
UPDATELAYEREDWINDOWINFO STRUC
cbSize			DWORD ?
hdcDst			HDC ?
pptDst			LPPOINT ?
psize			LPPOINT ?
hdcSrc			HDC ?
pptSrc			LPPOINT ?
crKey			COLORREF ?
pblend			LPBLENDFUNCTION ?
dwFlags			DWORD ?
prcDirty		LPRECT ?
UPDATELAYEREDWINDOWINFO ENDS
PUPDATELAYEREDWINDOWINFO typedef ptr UPDATELAYEREDWINDOWINFO


if (_WIN32_WINNT LT 0x0502)
;WINUSERAPI
;BOOL
;WINAPI
UpdateLayeredWindowIndirect_T typedef proto _CType \
		  hWnd: HWND,
	      pULWInfo: ptr UPDATELAYEREDWINDOWINFO
UpdateLayeredWindowIndirect typedef ptr UpdateLayeredWindowIndirect_T
else
UpdateLayeredWindowIndirect proto _CType \
		  hWnd: HWND,
	      pULWInfo: ptr UPDATELAYEREDWINDOWINFO
endif

endif ;; defined(_WINGDI_) AND NOT defined(NOGDI)

if(_WIN32_WINNT GE 0x0501)
;WINUSERAPI
;BOOL
GetLayeredWindowAttributes proto _CType \
		  hwnd: HWND,
		pcrKey: ptr COLORREF,
	       pbAlpha: ptr BYTE,
	      pdwFlags: ptr DWORD

PW_CLIENTONLY		equ 0x00000001

;BOOL
PrintWindow proto _CType \
		  hwnd: HWND,
		hdcBlt: HDC,
		nFlags: UINT
endif ;; _WIN32_WINNT GE 0x0501

if(WINVER GE 0x0400)
;BOOL
ShowWindowAsync proto _CType \
		  hWnd: HWND,
	      nCmdShow: SINT
endif ;; WINVER GE 0x0400

;BOOL
if(WINVER GE 0x0500)
FlashWindow proto _CType \
		  hWnd: HWND,
	       dwFlags: DWORD
else
FlashWindow proto _CType \
		  hWnd: HWND,
	       bInvert: BOOL
endif

if(WINVER GE 0x0500)
FLASHW_STOP		equ 0
FLASHW_CAPTION		equ 0x00000001
FLASHW_TRAY		equ 0x00000002
FLASHW_ALL		equ (FLASHW_CAPTION OR FASHW_TRAY)
FLASHW_TIMER		equ 0x00000004
FLASHW_TIMERNOFG	equ 0x0000000C
endif ;; WINVER GE 0x0500

;BOOL
ShowOwnedPopups proto _CType \
		  hWnd: HWND,
		 fShow: BOOL

;BOOL
OpenIcon proto _CType \
		  hWnd: HWND

;BOOL
CloseWindow proto _CType \
		  hWnd: HWND

;BOOL
MoveWindow proto _CType \
		  hWnd: HWND,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	      bRepaint: BOOL

if(WINVER GE 0x0500)
;BOOL
SetWindowPos proto _CType \
		  hWnd: HWND,
       hWndInsertAfter: HWND,
		     X: SINT,
		     Y: SINT,
		   _cx: SINT,
		    cy: SINT,
		uFlags: UINT
else
SetWindowPos_P	typedef proto _CType \
		  hWnd: HWND,
       hWndInsertAfter: HWND,
		     X: SINT,
		     Y: SINT,
		   _cx: SINT,
		    cy: SINT,
		uFlags: UINT
SetWindowPos_T	typedef ptr SetWindowPos_P
externdef	SetWindowPos:SetWindowPos_T
endif

;BOOL
GetWindowPlacement proto _CType \
		  hWnd: HWND,
	       lpwndpl: ptr WINDOWPLACEMENT

;BOOL
SetWindowPlacement proto _CType \
		  hWnd: HWND,
	       lpwndpl: ptr WINDOWPLACEMENT

if(_WIN32_WINNT GE 0x0601)
WDA_NONE		equ 0x00000000
WDA_MONITOR		equ 0x00000001
;BOOL
GetWindowDisplayAffinity proto _CType \
		  hWnd: HWND,
	   pdwAffinity: LPDWORD
;BOOL
SetWindowDisplayAffinity proto _CType \
		  hWnd: HWND,
	    dwAffinity: DWORD
endif ;; _WIN32_WINNT GE 0x0601

ifndef NODEFERWINDOWPOS

;HDWP
BeginDeferWindowPos proto _CType \
	   nNumWindows: SINT

;HDWP
DeferWindowPos proto _CType \
	   hWinPosInfo: HDWP,
		  hWnd: HWND,
      hWndInsertAfter : HWND,
		     x: SINT,
		     y: SINT,
		   _cx: SINT,
		    cy: SINT,
		uFlags: UINT

;BOOL
EndDeferWindowPos proto _CType \
	   hWinPosInfo: HDWP

endif ;; NOT NODEFERWINDOWPOS

;BOOL
IsWindowVisible proto _CType \
		  hWnd: HWND

;BOOL
IsIconic proto _CType \
		  hWnd: HWND

;BOOL
AnyPopup proto _CType

;BOOL
BringWindowToTop proto _CType \
		  hWnd: HWND

;BOOL
IsZoomed proto _CType \
		  hWnd: HWND

;;
;; SetWindowPos Flags
;;
SWP_NOSIZE		equ 0x0001
SWP_NOMOVE		equ 0x0002
SWP_NOZORDER		equ 0x0004
SWP_NOREDRAW		equ 0x0008
SWP_NOACTIVATE		equ 0x0010
SWP_FRAMECHANGED	equ 0x0020  ;; The frame changed: send WM_NCCACSIZE
SWP_SHOWWINDOW		equ 0x0040
SWP_HIDEWINDOW		equ 0x0080
SWP_NOCOPYBITS		equ 0x0100
SWP_NOOWNERZORDER	equ 0x0200  ;; Don't do owner Z ordering
SWP_NOSENDCHANGING	equ 0x0400  ;; Don't send WM_WINDOWPOSCHANGING

SWP_DRAWFRAME		equ SWP_FRAMECHANGED
SWP_NOREPOSITION	equ SWP_NOOWNERZORDER

if(WINVER GE 0x0400)
SWP_DEFERERASE		equ 0x2000
SWP_ASYNCWINDOWPOS	equ 0x4000
endif ;; WINVER GE 0x0400


HWND_TOP		equ ((HWND)0)
HWND_BOTTOM		equ ((HWND)1)
HWND_TOPMOST		equ ((HWND)-1)
HWND_NOTOPMOST		equ ((HWND)-2)

ifndef NOCTLMGR

;;
;; WARNING:
;; The following structures must NOT be DWORD padded because they are
;; followed by strings, etc that do not have to be DWORD aligned.
;;

;include pshpack2.inc

;;
;; original NT 32 bit dialog template:
;;
DLGTEMPLATE		STRUC WORD
style			dd ?
dwExtendedStyle		dd ?
cdit			dw ?
x			dw ?
y			dw ?
_cx			dw ?
cy			dw ?
DLGTEMPLATE		ENDS
LPDLGTEMPLATEA		typedef ptr DLGTEMPLATE
LPDLGTEMPLATEW		typedef ptr DLGTEMPLATE
ifdef _UNICODE
LPDLGTEMPLATE		typedef LPDLGTEMPLATEW
else
LPDLGTEMPLATE		typedef LPDLGTEMPLATEA
endif ;; UNICODE
LPCDLGTEMPLATEA		typedef ptr DLGTEMPLATE
LPCDLGTEMPLATEW		typedef ptr DLGTEMPLATE
ifdef _UNICODE
LPCDLGTEMPLATE		typedef LPCDLGTEMPLATEW
else
LPCDLGTEMPLATE		typedef LPCDLGTEMPLATEA
endif ;; UNICODE

;;
;; 32 bit Dialog item template.
;;
DLGITEMTEMPLATE		STRUC WORD
style			dd ?
dwExtendedStyle		dd ?
x			dw ?
y			dw ?
_cx			dw ?
cy			dw ?
id			dw ?
DLGITEMTEMPLATE		ENDS
PDLGITEMTEMPLATEA	typedef ptr DLGITEMTEMPLATE
PDLGITEMTEMPLATEW	typedef ptr DLGITEMTEMPLATE
ifdef _UNICODE
PDLGITEMTEMPLATE	typedef PDLGITEMTEMPLATEW
else
PDLGITEMTEMPLATE	typedef PDLGITEMTEMPLATEA
endif ;; UNICODE
LPDLGITEMTEMPLATEA	typedef ptr DLGITEMTEMPLATE
LPDLGITEMTEMPLATEW	typedef ptr DLGITEMTEMPLATE
ifdef _UNICODE
LPDLGITEMTEMPLATE	typedef LPDLGITEMTEMPLATEW
else
LPDLGITEMTEMPLATE	typedef LPDLGITEMTEMPLATEA
endif ;; UNICODE

;include poppack.inc ;; Resume normal packing

;HWND
CreateDialogParamA proto _CType \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCSTR,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
;HWND
CreateDialogParamW proto _CType \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCWSTR,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
ifdef _UNICODE
CreateDialogParam	equ <CreateDialogParamW>
else
CreateDialogParam	equ <CreateDialogParamA>
endif ;; NOT UNICODE

;HWND
CreateDialogIndirectParamA proto _CType \
	     hInstance: HINSTANCE,
	    lpTemplate: LPCDLGTEMPLATEA,
	    hWndParent: HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
;HWND
CreateDialogIndirectParamW proto _CType \
	     hInstance: HINSTANCE,
	    lpTemplate: LPCDLGTEMPLATEW,
	    hWndParent: HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
ifdef _UNICODE
CreateDialogIndirectParam equ <CreateDialogIndirectParamW>
else
CreateDialogIndirectParam equ <CreateDialogIndirectParamA>
endif ;; NOT UNICODE

CreateDialogA macro hInstance,lpName,hWndParent,lpDialogFunc
	exitm<CreateDialogParamA(hInstance, lpName, hWndParent, lpDialogFunc, 0)>
	endm

CreateDialogW macro hInstance,lpName,hWndParent,lpDialogFunc
	exitm<CreateDialogParamW(hInstance, lpName, hWndParent, lpDialogFunc, 0)>
	endm

ifdef _UNICODE
CreateDialog		equ <CreateDialogW>
else
CreateDialog		equ <CreateDialogA>
endif ;; NOT UNICODE

CreateDialogIndirectA macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm

CreateDialogIndirectW macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm
ifdef _UNICODE
CreateDialogIndirect	equ <CreateDialogIndirectW>
else
CreateDialogIndirect	equ <CreateDialogIndirectA>
endif ;; NOT UNICODE

;int
DialogBoxParamA proto _CType \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCSTR,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
;int
DialogBoxParamW proto _CType \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCWSTR,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
ifdef _UNICODE
DialogBoxParam		equ <DialogBoxParamW>
else
DialogBoxParam		equ <DialogBoxParamA>
endif ;; NOT UNICODE

;int
DialogBoxIndirectParamA proto _CType \
	     hInstance: HINSTANCE,
       hDialogTemplate: LPCDLGTEMPLATEA,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
;int
DialogBoxIndirectParamW proto _CType \
	     hInstance: HINSTANCE,
       hDialogTemplate: LPCDLGTEMPLATEW,
	   hWndParent : HWND,
	  lpDialogFunc: DLGPROC,
	   dwInitParam: LPARAM
ifdef _UNICODE
DialogBoxIndirectParam	equ <DialogBoxIndirectParamW>
else
DialogBoxIndirectParam	equ <DialogBoxIndirectParamA>
endif ;; NOT UNICODE

DialogBoxA macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<DialogBoxParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm
DialogBoxW macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<DialogBoxParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm
ifdef _UNICODE
DialogBox		equ <DialogBoxW>
else
DialogBox		equ <DialogBoxA>
endif ;; NOT UNICODE

DialogBoxIndirectA macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<DialogBoxIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm
DialogBoxIndirectW macro hInstance, lpTemplate, hWndParent, lpDialogFunc
	exitm<DialogBoxIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0)>
	endm
ifdef _UNICODE
DialogBoxIndirect	equ <DialogBoxIndirectW>
else
DialogBoxIndirect	equ <DialogBoxIndirectA>
endif ;; NOT UNICODE

;BOOL
EndDialog proto _CType \
		  hDlg: HWND,
	       nResult: SINT

;HWND
GetDlgItem proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT

;BOOL
SetDlgItemInt proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
		uValue: UINT,
	       bSigned: BOOL

;UINT
GetDlgItemInt proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
	  lpTranslated: LPBOOL,
	       bSigned: BOOL

;BOOL
SetDlgItemTextA proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
	      lpString: LPCSTR
;BOOL
SetDlgItemTextW proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
	      lpString: LPCWSTR
ifdef _UNICODE
SetDlgItemText		equ <SetDlgItemTextW>
else
SetDlgItemText		equ <SetDlgItemTextA>
endif ;; NOT UNICODE

;UINT
GetDlgItemTextA proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
	      lpString: LPSTR,
	     nMaxCount: SINT
;UINT
GetDlgItemTextW proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
	      lpString: LPWSTR,
	     nMaxCount: SINT
ifdef _UNICODE
GetDlgItemText		equ <GetDlgItemTextW>
else
GetDlgItemText		equ <GetDlgItemTextA>
endif ;; NOT UNICODE

;BOOL
CheckDlgButton proto _CType \
		  hDlg: HWND,
	     nIDButton: SINT,
		uCheck: UINT

;BOOL
CheckRadioButton proto _CType \
		  hDlg: HWND,
	nIDFirstButton: SINT,
	 nIDLastButton: SINT,
	nIDCheckButton: SINT

;UINT
IsDlgButtonChecked proto _CType \
		  hDlg: HWND,
	     nIDButton: SINT

;LONG
SendDlgItemMessageA proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;LONG
SendDlgItemMessageW proto _CType \
		  hDlg: HWND,
	    nIDDlgItem: SINT,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
SendDlgItemMessage	equ <SendDlgItemMessageW>
else
SendDlgItemMessage	equ <SendDlgItemMessageA>
endif ;; NOT UNICODE

;HWND
GetNextDlgGroupItem proto _CType \
		  hDlg: HWND,
		  hCtl: HWND,
	     bPrevious: BOOL

;HWND
GetNextDlgTabItem proto _CType \
		  hDlg: HWND,
		  hCtl: HWND,
	     bPrevious: BOOL

;int
GetDlgCtrlID proto _CType \
		  hWnd: HWND

;long
GetDialogBaseUnits proto _CType

DefDlgProcA typedef proto _CType \
		  hDlg: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
DefDlgProcW typedef proto _CType \
		  hDlg: HWND,
		   Msg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
DefDlgProc		typedef ptr DefDlgProcW
else
DefDlgProc		typedef ptr DefDlgProcA
endif ;; NOT UNICODE

;;
;; Window extra byted needed for private dialog classes.
;;
ifndef _MAC
DLGWINDOWEXTRA		equ 30
else
DLGWINDOWEXTRA		equ 48
endif

endif ;; NOT NOCTLMGR

ifndef NOMSG

;BOOL
CallMsgFilterA proto _CType \
		 lpMsg: LPMSG,
		 nCode: SINT
;BOOL
CallMsgFilterW proto _CType \
		 lpMsg: LPMSG,
		 nCode: SINT
ifdef _UNICODE
CallMsgFilter		equ <CallMsgFilterW>
else
CallMsgFilter		equ <CallMsgFilterA>
endif ;; NOT UNICODE

endif ;; NOT NOMSG

ifndef NOCLIPBOARD

;;
;; Clipboard Manager Functions
;;

;BOOL
OpenClipboard proto _CType \
	  hWndNewOwner: HWND

;BOOL
CloseClipboard proto _CType


if(WINVER GE 0x0500)
;DWORD
GetClipboardSequenceNumber proto _CType
endif ;; WINVER GE 0x0500

;HWND
GetClipboardOwner proto _CType

;HWND
SetClipboardViewer proto _CType \
	 hWndNewViewer: HWND

;HWND
GetClipboardViewer proto _CType

;BOOL
ChangeClipboardChain proto _CType \
	    hWndRemove: HWND,
	   hWndNewNext: HWND

;HANDLE
SetClipboardData proto _CType \
	       uFormat: UINT,
		  hMem: HANDLE

;HANDLE
GetClipboardData proto _CType \
	       uFormat: UINT

;UINT
RegisterClipboardFormatA proto _CType \
	    lpszFormat: LPCSTR
;UINT
RegisterClipboardFormatW proto _CType \
	    lpszFormat: LPCWSTR
ifdef _UNICODE
RegisterClipboardFormat equ <RegisterClipboardFormatW>
else
RegisterClipboardFormat equ <RegisterClipboardFormatA>
endif ;; NOT UNICODE

;int
CountClipboardFormats proto _CType

;UINT
EnumClipboardFormats proto _CType \
		format: UINT

;int
GetClipboardFormatNameA proto _CType \
		format: UINT,
	lpszFormatName: LPSTR,
	   cchMaxCount: SINT
;int
GetClipboardFormatNameW proto _CType \
		format: UINT,
	lpszFormatName: LPWSTR,
	   cchMaxCount: SINT
ifdef _UNICODE
GetClipboardFormatName	equ <GetClipboardFormatNameW>
else
GetClipboardFormatName	equ <GetClipboardFormatNameA>
endif ;; NOT UNICODE

;BOOL
EmptyClipboard proto _CType

;BOOL
IsClipboardFormatAvailable proto _CType \
		format: UINT

;int
GetPriorityClipboardFormat proto _CType \
  paFormatPriorityList: ptr UINT,
	      cFormats: SINT

;HWND
GetOpenClipboardWindow proto _CType

if(WINVER GE 0x0600)

;BOOL
AddClipboardFormatListener proto _CType \
		  hwnd: HWND
;BOOL
RemoveClipboardFormatListener proto _CType \
		  hwnd: HWND
;BOOL
GetUpdatedClipboardFormats proto _CType \
	  lpuiFormats: PUINT,
	     cFormats: UINT,
	 pcFormatsOut: PUINT

endif ;; WINVER GE 0x0600
endif ;; NOT NOCLIPBOARD

;;
;; Character Translation Routines
;;

;BOOL
CharToOemA proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPSTR
;BOOL
CharToOemW proto _CType \
	       lpszSrc: LPCWSTR,
	       lpszDst: LPSTR
ifdef _UNICODE
CharToOem		equ <CharToOemW>
else
CharToOem		equ <CharToOemA>
endif ;; NOT UNICODE

;BOOL
OemToCharA proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPSTR
;BOOL
OemToCharW proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPWSTR
ifdef _UNICODE
OemToChar		equ <OemToCharW>
else
OemToChar		equ <OemToCharA>
endif ;; NOT UNICODE

;BOOL
CharToOemBuffA proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPSTR,
	  cchDstLength: DWORD
;BOOL
CharToOemBuffW proto _CType \
	       lpszSrc: LPCWSTR,
	       lpszDst: LPSTR,
	  cchDstLength: DWORD
ifdef _UNICODE
CharToOemBuff		equ <CharToOemBuffW>
else
CharToOemBuff		equ <CharToOemBuffA>
endif ;; NOT UNICODE

;BOOL
OemToCharBuffA proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPSTR,
	  cchDstLength: DWORD
;BOOL
OemToCharBuffW proto _CType \
	       lpszSrc: LPCSTR,
	       lpszDst: LPWSTR,
	  cchDstLength: DWORD
ifdef _UNICODE
OemToCharBuff		equ <OemToCharBuffW>
else
OemToCharBuff		equ <OemToCharBuffA>
endif ;; NOT UNICODE

;LPSTR
CharUpperA proto _CType \
		  lpsz: LPSTR
;LPWSTR
CharUpperW proto _CType \
		  lpsz: LPWSTR
ifdef _UNICODE
CharUpper		equ <CharUpperW>
else
CharUpper		equ <CharUpperA>
endif ;; NOT UNICODE

;DWORD
CharUpperBuffA proto _CType \
		  lpsz: LPSTR,
	     cchLength: DWORD
;DWORD
CharUpperBuffW proto _CType \
		  lpsz: LPWSTR,
	     cchLength: DWORD
ifdef _UNICODE
CharUpperBuff		equ <CharUpperBuffW>
else
CharUpperBuff		equ <CharUpperBuffA>
endif ;; NOT UNICODE

;LPSTR
CharLowerA proto _CType \
		  lpsz: LPSTR
;LPWSTR
CharLowerW proto _CType \
		  lpsz: LPWSTR
ifdef _UNICODE
CharLower		equ <CharLowerW>
else
CharLower		equ <CharLowerA>
endif ;; NOT UNICODE

;DWORD
CharLowerBuffA proto _CType \
		  lpsz: LPSTR,
	     cchLength: DWORD
;DWORD
CharLowerBuffW proto _CType \
		  lpsz: LPWSTR,
	     cchLength: DWORD
ifdef _UNICODE
CharLowerBuff		equ <CharLowerBuffW>
else
CharLowerBuff		equ <CharLowerBuffA>
endif ;; NOT UNICODE

;LPSTR
CharNextA proto _CType \
		  lpsz: LPCSTR
;LPWSTR
CharNextW proto _CType \
		  lpsz: LPCWSTR
ifdef _UNICODE
CharNext		equ <CharNextW>
else
CharNext		equ <CharNextA>
endif ;; NOT UNICODE

;LPSTR
CharPrevA proto _CType \
	     lpszStart: LPCSTR,
	   lpszCurrent: LPCSTR
;LPWSTR
CharPrevW proto _CType \
	     lpszStart: LPCWSTR,
	   lpszCurrent: LPCWSTR
ifdef _UNICODE
CharPrev		equ <CharPrevW>
else
CharPrev		equ <CharPrevA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;LPSTR
CharNextExA proto _CType \
	      CodePage: WORD,
	 lpCurrentChar: LPCSTR,
	       dwFlags: DWORD

;LPSTR
CharPrevExA proto _CType \
	      CodePage: WORD,
	       lpStart: LPCSTR,
	 lpCurrentChar: LPCSTR,
	       dwFlags: DWORD
endif ;; WINVER GE 0x0400

;;
;; Compatibility defines for character translation routines
;;
AnsiToOem		equ <CharToOemA>
OemToAnsi		equ <OemToCharA>
AnsiToOemBuff		equ <CharToOemBuffA>
OemToAnsiBuff		equ <OemToCharBuffA>
AnsiUpper		equ <CharUpperA>
AnsiUpperBuff		equ <CharUpperBuffA>
AnsiLower		equ <CharLowerA>
AnsiLowerBuff		equ <CharLowerBuffA>
AnsiNext		equ <CharNextA>
AnsiPrev		equ <CharPrevA>

ifndef	NOLANGUAGE
;;
;; Language dependent Routines
;;

;BOOL
IsCharAlphaA proto _CType \
		      : CHAR
;BOOL
IsCharAlphaW proto _CType \
		      : WCHAR
ifdef _UNICODE
IsCharAlpha		equ <IsCharAlphaW>
else
IsCharAlpha		equ <IsCharAlphaA>
endif ;; NOT UNICODE

;BOOL
IsCharAlphaNumericA proto _CType \
		      : CHAR
;BOOL
IsCharAlphaNumericW proto _CType \
		      : WCHAR
ifdef _UNICODE
IsCharAlphaNumeric	equ <IsCharAlphaNumericW>
else
IsCharAlphaNumeric	equ <IsCharAlphaNumericA>
endif ;; NOT UNICODE

;BOOL
IsCharUpperA proto _CType \
		      : CHAR
;BOOL
IsCharUpperW proto _CType \
		      : WCHAR
ifdef _UNICODE
IsCharUpper		equ <IsCharUpperW>
else
IsCharUpper		equ <IsCharUpperA>
endif ;; NOT UNICODE

;BOOL
IsCharLowerA proto _CType \
		      : CHAR
;BOOL
IsCharLowerW proto _CType \
		      : WCHAR
ifdef _UNICODE
IsCharLower		equ <IsCharLowerW>
else
IsCharLower		equ <IsCharLowerA>
endif ;; NOT UNICODE

endif  ;; NOT NOLANGUAGE

;HWND
SetFocus proto _CType \
		  hWnd: HWND

;HWND
GetActiveWindow proto _CType

;HWND
GetFocus proto _CType

;UINT
GetKBCodePage proto _CType

if (WINVER GE 0x0500)
;SHORT
GetKeyState proto _CType \
	      nVirtKey: SINT
else
GetKeyState_P typedef proto _CType \
	      nVirtKey: SINT
GetKeyState_T	typedef ptr GetKeyState_P
externdef	GetKeyState:GetKeyState_T
endif

;SHORT
GetAsyncKeyState proto _CType \
		  vKey: SINT

;BOOL
GetKeyboardState proto _CType \
	    lpKeyState: PBYTE

;BOOL
SetKeyboardState proto _CType \
	    lpKeyState: LPBYTE

;int
GetKeyNameTextA proto _CType \
		lParam: LONG,
	      lpString: LPSTR,
		nSize : SINT
;int
GetKeyNameTextW proto _CType \
		lParam: LONG,
	      lpString: LPWSTR,
		nSize : SINT
ifdef _UNICODE
GetKeyNameText		equ <GetKeyNameTextW>
else
GetKeyNameText		equ <GetKeyNameTextA>
endif ;; NOT UNICODE

;int
GetKeyboardType proto _CType \
	     nTypeFlag: SINT

;int
ToAscii proto _CType \
	      uVirtKey: UINT,
	     uScanCode: UINT,
	    lpKeyState: PBYTE,
		lpChar: LPWORD,
		uFlags: UINT

if(WINVER GE 0x0400)
;int
ToAsciiEx proto _CType \
	      uVirtKey: UINT,
	     uScanCode: UINT,
	    lpKeyState: PBYTE,
		lpChar: LPWORD,
		uFlags: UINT,
		 dwhkl: HKL
endif ;; WINVER GE 0x0400

;int
ToUnicode proto _CType \
	      wVirtKey: UINT,
	     wScanCode: UINT,
	    lpKeyState: PBYTE,
	      pwszBuff: LPWSTR,
	       cchBuff: SINT,
		wFlags: UINT

;DWORD
OemKeyScan proto _CType \
	      wOemChar: WORD

;SHORT
VkKeyScanA proto _CType \
		      : CHAR
;SHORT
VkKeyScanW proto _CType \
		      : WCHAR
ifdef _UNICODE
VkKeyScan		equ <VkKeyScanW>
else
VkKeyScan		equ <VkKeyScanA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;SHORT
VkKeyScanExA proto _CType \
		      : CHAR,
		 dwhkl: HKL
;SHORT
VkKeyScanExW proto _CType \
		      : WCHAR,
		 dwhkl: HKL
ifdef _UNICODE
VkKeyScanEx		equ <VkKeyScanExW>
else
VkKeyScanEx		equ <VkKeyScanExA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400
KEYEVENTF_EXTENDEDKEY	equ 0x0001
KEYEVENTF_KEYUP		equ 0x0002
if(_WIN32_WINNT GE 0x0500)
KEYEVENTF_UNICODE	equ 0x0004
KEYEVENTF_SCANCODE	equ 0x0008
endif ;; _WIN32_WINNT GE 0x0500

;VOID
keybd_event proto _CType \
		   bVk: BYTE,
		 bScan: BYTE,
	       dwFlags: DWORD,
	   dwExtraInfo: DWORD

MOUSEEVENTF_MOVE	equ 0x0001 ;; mouse move
MOUSEEVENTF_LEFTDOWN	equ 0x0002 ;; left button down
MOUSEEVENTF_LEFTUP	equ 0x0004 ;; left button up
MOUSEEVENTF_RIGHTDOWN	equ 0x0008 ;; right button down
MOUSEEVENTF_RIGHTUP	equ 0x0010 ;; right button up
MOUSEEVENTF_MIDDLEDOWN	equ 0x0020 ;; middle button down
MOUSEEVENTF_MIDDLEUP	equ 0x0040 ;; middle button up
MOUSEEVENTF_WHEEL	equ 0x0800 ;; wheel button rolled
if (_WIN32_WINNT GE 0x0600)
MOUSEEVENTF_HWHEEL	equ 0x01000 ;; hwheel button rolled
endif
if(WINVER GE 0x0600)
MOUSEEVENTF_MOVE_NOCOALESCE equ 0x2000 ;; do not coalesce mouse moves
endif ;; WINVER GE 0x0600
MOUSEEVENTF_ABSOLUTE	equ 0x8000 ;; absolute move

;VOID
mouse_event proto _CType \
	       dwFlags: DWORD,
		     x: DWORD,
		    dy: DWORD,
		dwData: DWORD,
	   dwExtraInfo: DWORD

if (_WIN32_WINNT GT 0x0400)

MOUSEINPUT		STRUC
_dx			LONG ?
dy			LONG ?
mouseData		dd ?
dwFlags			dd ?
time			dd ?
dwExtraInfo		dd ?
MOUSEINPUT		ENDS
PMOUSEINPUT		typedef ptr MOUSEINPUT
LPMOUSEINPUT		typedef ptr MOUSEINPUT

KEYBDINPUT		STRUC
wVk			dw ?
wScan			dw ?
dwFlags			dd ?
time			dd ?
dwExtraInfo		dd ?
KEYBDINPUT		ENDS
PKEYBDINPUT		typedef ptr KEYBDINPUT
LPKEYBDINPUT		typedef ptr KEYBDINPUT

HARDWAREINPUT		STRUC
uMsg			dd ?
wParamL			dw ?
wParamH			dw ?
HARDWAREINPUT		ENDS
PHARDWAREINPUT		typedef ptr HARDWAREINPUT
LPHARDWAREINPUT		typedef ptr HARDWAREINPUT

INPUT_MOUSE		equ 0
INPUT_KEYBOARD		equ 1
INPUT_HARDWARE		equ 2

INPUT			STRUC
_type			dd ?
UNION
  mi			MOUSEINPUT <>
  ki			KEYBDINPUT <>
  hi			HARDWAREINPUT <>
ENDS
INPUT			ENDS
PINPUT			typedef ptr INPUT
LPINPUT			typedef ptr INPUT

;UINT
SendInput proto _CType \
	       cInputs: UINT,	;; number of input in the array
	       pInputs: LPINPUT,;; array of inputs
		cbSize: SINT	;; sizeof(INPUT)

endif ;; (_WIN32_WINNT GT 0x0400)

if(WINVER GE 0x0601)

;;
;; Touch Input defines and functions
;;

;;
;; Touch input handle
;;
HTOUCHINPUT		typedef HANDLE ; DECLARE_HANDLE(HTOUCHINPUT);

TOUCHINPUT		STRUC
x			LONG ?
y			LONG ?
hSource			HANDLE ?
dwID			dd ?
dwFlags			dd ?
dwMask			dd ?
dwTime			dd ?
dwExtraInfo		SIZE_T ?
cxContact		dd ?
cyContact		dd ?
TOUCHINPUT		ENDS
PTOUCHINPUT		typedef ptr TOUCHINPUT
PCTOUCHINPUT		typedef ptr TOUCHINPUT


;;
;; Conversion of touch input coordinates to pixels
;;
TOUCH_COORD_TO_PIXEL macro l
	exitm<((l) / 100)>
	endm

;;
;; Touch input flag values (TOUCHINPUT.dwFlags)
;;
TOUCHEVENTF_MOVE	equ 0x0001
TOUCHEVENTF_DOWN	equ 0x0002
TOUCHEVENTF_UP		equ 0x0004
TOUCHEVENTF_INRANGE	equ 0x0008
TOUCHEVENTF_PRIMARY	equ 0x0010
TOUCHEVENTF_NOCOALESCE	equ 0x0020
TOUCHEVENTF_PEN		equ 0x0040
TOUCHEVENTF_PALM	equ 0x0080

;;
;; Touch input mask values (TOUCHINPUT.dwMask)
;;
TOUCHINPUTMASKF_TIMEFROMSYSTEM equ 0x0001 ;; the dwTime field contains a system generated value
TOUCHINPUTMASKF_EXTRAINFO      equ 0x0002 ;; the dwExtraInfo field is valid
TOUCHINPUTMASKF_CONTACTAREA    equ 0x0004 ;; the cxContact and cyContact fields are valid

;WINUSERAPI
;BOOL
GetTouchInputInfo proto _CType \
	   hTouchInput: HTOUCHINPUT,
	       cInputs: UINT,
	       pInputs: PTOUCHINPUT,
		cbSize: SINT ;; sizeof(TOUCHINPUT)

;BOOL
CloseTouchInputHandle proto _CType \
	   hTouchInput: HTOUCHINPUT



;;
;; RegisterTouchWindow flag values
;;
TWF_FINETOUCH		equ 0x00000001
TWF_WANTPALM		equ 0x00000002

;BOOL
RegisterTouchWindow proto _CType \
		  hwnd: HWND,
	       ulFlags: ULONG

;BOOL
UnregisterTouchWindow proto _CType \
		  hwnd: HWND

;BOOL
IsTouchWindow proto _CType \
		  hwnd: HWND,
	      pulFlags: PULONG

endif ;; WINVER GE 0x0601

if(_WIN32_WINNT GE 0x0500)
LASTINPUTINFO		STRUC
cbSize			UINT ?
dwTime			dd ?
LASTINPUTINFO		ENDS
PLASTINPUTINFO		typedef ptr LASTINPUTINFO

;BOOL
GetLastInputInfo proto _CType \
		  plii: PLASTINPUTINFO
endif ;; _WIN32_WINNT GE 0x0500

;UINT
MapVirtualKeyA proto _CType \
		 uCode: UINT,
	      uMapType: UINT
;UINT
MapVirtualKeyW proto _CType \
		 uCode: UINT,
	      uMapType: UINT
ifdef _UNICODE
MapVirtualKey		equ <MapVirtualKeyW>
else
MapVirtualKey		equ <MapVirtualKeyA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;UINT
MapVirtualKeyExA proto _CType \
		 uCode: UINT,
	      uMapType: UINT,
		 dwhkl: HKL
;UINT
MapVirtualKeyExW proto _CType \
		 uCode: UINT,
	      uMapType: UINT,
		 dwhkl: HKL
ifdef _UNICODE
MapVirtualKeyEx		equ <MapVirtualKeyExW>
else
MapVirtualKeyEx		equ <MapVirtualKeyExA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400

MAPVK_VK_TO_VSC		equ 0
MAPVK_VSC_TO_VK		equ 1
MAPVK_VK_TO_CHAR	equ 2
MAPVK_VSC_TO_VK_EX	equ 3
if(WINVER GE 0x0600)
MAPVK_VK_TO_VSC_EX	equ 4
endif ;; WINVER GE 0x0600

;BOOL
GetInputState proto _CType

;DWORD
GetQueueStatus proto _CType \
		 flags: UINT

;HWND
GetCapture proto _CType

;HWND
SetCapture proto _CType \
		  hWnd: HWND

;BOOL
ReleaseCapture proto _CType

;DWORD
MsgWaitForMultipleObjects proto _CType \
		nCount: DWORD,
	      pHandles: LPHANDLE,
	      fWaitAll: BOOL,
	dwMilliseconds: DWORD,
	    dwWakeMask: DWORD

;DWORD
MsgWaitForMultipleObjectsEx proto _CType \
		nCount: DWORD,
	      pHandles: LPHANDLE,
	dwMilliseconds: DWORD,
	    dwWakeMask: DWORD,
	       dwFlags: DWORD

MWMO_WAITALL		equ 0x0001
MWMO_ALERTABLE		equ 0x0002
MWMO_INPUTAVAILABLE	equ 0x0004

;;
;; Queue status flags for GetQueueStatus() and MsgWaitForMultipleObjects()
;;
QS_KEY			equ 0x0001
QS_MOUSEMOVE		equ 0x0002
QS_MOUSEBUTTON		equ 0x0004
QS_POSTMESSAGE		equ 0x0008
QS_TIMER		equ 0x0010
QS_PAINT		equ 0x0020
QS_SENDMESSAGE		equ 0x0040
QS_HOTKEY		equ 0x0080
QS_ALLPOSTMESSAGE	equ 0x0100
if(_WIN32_WINNT GE 0x0501)
QS_RAWINPUT		equ 0x0400
endif ;; _WIN32_WINNT GE 0x0501

QS_MOUSE		equ QS_MOUSEMOVE OR QS_MOUSEBUTTON
if (_WIN32_WINNT GE 0x0501)
QS_INPUT		equ QS_MOUSE or QS_KEY or QS_RAWINPUT
else
QS_INPUT		equ QS_MOUSE or QS_KEY
endif ;; (_WIN32_WINNT >= 0x0501)
QS_ALLEVENTS		equ QS_INPUT OR QS_POSTMESSAGE OR \
			QS_TIMER OR QS_PAINT OR QS_HOTKEY
QS_ALLINPUT		equ QS_INPUT OR QS_POSTMESSAGE OR \
			QS_TIMER OR QS_PAINT OR QS_HOTKEY OR \
			QS_SENDMESSAGE

;;
;; Windows Functions
;;

;UINT
SetTimer proto _CType \
		 hWnd : HWND,
	      nIDEvent: UINT,
	       uElapse: UINT,
	   lpTimerFunc: TIMERPROC

;BOOL
KillTimer proto _CType \
		  hWnd: HWND,
	      uIDEvent: UINT

;BOOL
IsWindowUnicode proto _CType \
		  hWnd: HWND

;BOOL
EnableWindow proto _CType \
		  hWnd: HWND,
	       bEnable: BOOL

;BOOL
IsWindowEnabled proto _CType \
		  hWnd: HWND

;HACCEL
LoadAcceleratorsA proto _CType \
	     hInstance: HINSTANCE,
	   lpTableName: LPCSTR
;HACCEL
LoadAcceleratorsW proto _CType \
	     hInstance: HINSTANCE,
	   lpTableName: LPCWSTR
ifdef _UNICODE
LoadAccelerators	equ <LoadAcceleratorsW>
else
LoadAccelerators	equ <LoadAcceleratorsA>
endif ;; NOT UNICODE

;HACCEL
CreateAcceleratorTableA proto _CType \
		      : LPACCEL,
		      : SINT
;HACCEL
CreateAcceleratorTableW proto _CType \
		      : LPACCEL,
		      : SINT
ifdef _UNICODE
CreateAcceleratorTable	equ <CreateAcceleratorTableW>
else
CreateAcceleratorTable	equ <CreateAcceleratorTableA>
endif ;; NOT UNICODE

;BOOL
DestroyAcceleratorTable proto _CType \
		hAccel: HACCEL

;int
CopyAcceleratorTableA proto _CType \
	     hAccelSrc: HACCEL,
	    lpAccelDst: LPACCEL,
	 cAccelEntries: SINT
;int
CopyAcceleratorTableW proto _CType \
	     hAccelSrc: HACCEL,
	    lpAccelDst: LPACCEL,
	 cAccelEntries: SINT
ifdef _UNICODE
CopyAcceleratorTable	equ <CopyAcceleratorTableW>
else
CopyAcceleratorTable	equ <CopyAcceleratorTableA>
endif ;; NOT UNICODE

ifndef NOMSG

;int
TranslateAcceleratorA proto _CType \
		  hWnd: HWND,
	     hAccTable: HACCEL,
		 lpMsg: LPMSG
;int
TranslateAcceleratorW proto _CType \
		  hWnd: HWND,
	     hAccTable: HACCEL,
		 lpMsg: LPMSG
ifdef _UNICODE
TranslateAccelerator	equ <TranslateAcceleratorW>
else
TranslateAccelerator	equ <TranslateAcceleratorA>
endif ;; NOT UNICODE

endif ;; NOT NOMSG

ifndef NOSYSMETRICS

;;
;; GetSystemMetrics() codes
;;

SM_CXSCREEN		equ 0
SM_CYSCREEN		equ 1
SM_CXVSCROLL		equ 2
SM_CYHSCROLL		equ 3
SM_CYCAPTION		equ 4
SM_CXBORDER		equ 5
SM_CYBORDER		equ 6
SM_CXDLGFRAME		equ 7
SM_CYDLGFRAME		equ 8
SM_CYVTHUMB		equ 9
SM_CXHTHUMB		equ 10
SM_CXICON		equ 11
SM_CYICON		equ 12
SM_CXCURSOR		equ 13
SM_CYCURSOR		equ 14
SM_CYMENU		equ 15
SM_CXFULLSCREEN		equ 16
SM_CYFULLSCREEN		equ 17
SM_CYKANJIWINDOW	equ 18
SM_MOUSEPRESENT		equ 19
SM_CYVSCROLL		equ 20
SM_CXHSCROLL		equ 21
SM_DEBUG		equ 22
SM_SWAPBUTTON		equ 23
SM_RESERVED1		equ 24
SM_RESERVED2		equ 25
SM_RESERVED3		equ 26
SM_RESERVED4		equ 27
SM_CXMIN		equ 28
SM_CYMIN		equ 29
SM_CXSIZE		equ 30
SM_CYSIZE		equ 31
SM_CXFRAME		equ 32
SM_CYFRAME		equ 33
SM_CXMINTRACK		equ 34
SM_CYMINTRACK		equ 35
SM_CXDOUBLECLK		equ 36
SM_CYDOUBLECLK		equ 37
SM_CXICONSPACING	equ 38
SM_CYICONSPACING	equ 39
SM_MENUDROPALIGNMENT	equ 40
SM_PENWINDOWS		equ 41
SM_DBCSENABLED		equ 42
SM_CMOUSEBUTTONS	equ 43

if(WINVER GE 0x0400)
SM_CXFIXEDFRAME		equ SM_CXDGFRAME  ;; ;win40 name change
SM_CYFIXEDFRAME		equ SM_CYDGFRAME  ;; ;win40 name change
SM_CXSIZEFRAME		equ SM_CXFRAME	   ;; ;win40 name change
SM_CYSIZEFRAME		equ SM_CYFRAME	   ;; ;win40 name change

SM_SECURE		equ 44
SM_CXEDGE		equ 45
SM_CYEDGE		equ 46
SM_CXMINSPACING		equ 47
SM_CYMINSPACING		equ 48
SM_CXSMICON		equ 49
SM_CYSMICON		equ 50
SM_CYSMCAPTION		equ 51
SM_CXSMSIZE		equ 52
SM_CYSMSIZE		equ 53
SM_CXMENUSIZE		equ 54
SM_CYMENUSIZE		equ 55
SM_ARRANGE		equ 56
SM_CXMINIMIZED		equ 57
SM_CYMINIMIZED		equ 58
SM_CXMAXTRACK		equ 59
SM_CYMAXTRACK		equ 60
SM_CXMAXIMIZED		equ 61
SM_CYMAXIMIZED		equ 62
SM_NETWORK		equ 63
SM_CLEANBOOT		equ 67
SM_CXDRAG		equ 68
SM_CYDRAG		equ 69
endif ;; WINVER GE 0x0400
SM_SHOWSOUNDS		equ 70
if(WINVER GE 0x0400)
SM_CXMENUCHECK		equ 71	 ;; Use instead of GetMenuCheckMarkDimensions() NOT
SM_CYMENUCHECK		equ 72
SM_SLOWMACHINE		equ 73
SM_MIDEASTENABLED	equ 74
endif ;; WINVER GE 0x0400
if (WINVER GE 0x0500) OR (_WIN32_WINNT GE 0x0400)
SM_MOUSEWHEELPRESENT	equ 75
endif
if(WINVER GE 0x0500)
SM_XVIRTUALSCREEN	equ 76
SM_YVIRTUALSCREEN	equ 77
SM_CXVIRTUALSCREEN	equ 78
SM_CYVIRTUALSCREEN	equ 79
SM_CMONITORS		equ 80
SM_SAMEDISPLAYFORMAT	equ 81
endif ;; WINVER GE 0x0500
if(_WIN32_WINNT GE 0x0500)
SM_IMMENABLED		equ 82
endif ;; _WIN32_WINNT GE 0x0500

if(_WIN32_WINNT GE 0x0501)
SM_CXFOCUSBORDER	equ 83
SM_CYFOCUSBORDER	equ 84
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0501)
SM_TABLETPC		equ 86
SM_MEDIACENTER		equ 87
SM_STARTER		equ 88
SM_SERVERR2		equ 89
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0600)
SM_MOUSEHORIZONTALWHEELPRESENT equ 91
SM_CXPADDEDBORDER	equ 92
endif ;; _WIN32_WINNT GE 0x0600

if(WINVER GE 0x0601)
SM_DIGITIZER		equ 94
SM_MAXIMUMTOUCHES	equ 95
endif ;; WINVER GE 0x0601

if (WINVER LT 0x0500) AND ( NOT defined(_WIN32_WINNT) OR (_WIN32_WINNT LT 0x0400))
SM_CMETRICS		equ 76
elseif WINVER EQ 0x500
SM_CMETRICS		equ 83
elseif WINVER EQ 0x501
SM_CMETRICS		equ 91
elseif WINVER EQ 0x600
SM_CMETRICS		equ 93
else
SM_CMETRICS		equ 97
endif

if(WINVER GE 0x0500)
SM_REMOTESESSION	equ 0x1000
if(_WIN32_WINNT GE 0x0501)
SM_SHUTTINGDOWN		equ 0x2000
endif ;; _WIN32_WINNT GE 0x0501
if(WINVER GE 0x0501)
SM_REMOTECONTROL	equ 0x2001
endif ;; WINVER GE 0x0501
if(WINVER GE 0x0501)
SM_CARETBLINKINGENABLED equ 0x2002
endif ;; WINVER GE 0x0501
endif ;; WINVER GE 0x0500

;int
GetSystemMetrics proto _CType \
		nIndex: SINT

endif ;; NOT NOSYSMETRICS

ifndef NOMENUS

;HMENU
LoadMenuA proto _CType \
	     hInstance: HINSTANCE,
	    lpMenuName: LPCSTR
;HMENU
LoadMenuW proto _CType \
	     hInstance: HINSTANCE,
	    lpMenuName: LPCWSTR
ifdef _UNICODE
LoadMenu		equ <LoadMenuW>
else
LoadMenu		equ <LoadMenuA>
endif ;; NOT UNICODE

;HMENU
LoadMenuIndirectA proto _CType \
	lpMenuTemplate: ptr MENUTEMPLATEA
;HMENU
LoadMenuIndirectW proto _CType \
	lpMenuTemplate: ptr MENUTEMPLATEA
ifdef _UNICODE
LoadMenuIndirect	equ <LoadMenuIndirectW>
else
LoadMenuIndirect	equ <LoadMenuIndirectA>
endif ;; NOT UNICODE

;HMENU
GetMenu proto _CType \
		  hWnd: HWND

;BOOL
SetMenu proto _CType \
		  hWnd: HWND,
		 hMenu: HMENU

;BOOL
ChangeMenuA proto _CType \
		 hMenu: HMENU,
		   cmd: UINT,
	   lpszNewItem: LPCSTR,
	     cmdInsert: UINT,
		 flags: UINT
;BOOL
ChangeMenuW proto _CType \
		 hMenu: HMENU,
		   cmd: UINT,
	   lpszNewItem: LPCWSTR,
	     cmdInsert: UINT,
		 flags: UINT
ifdef _UNICODE
ChangeMenu		equ <ChangeMenuW>
else
ChangeMenu		equ <ChangeMenuA>
endif ;; NOT UNICODE

;BOOL
HiliteMenuItem proto _CType \
		  hWnd: HWND,
		 hMenu: HMENU,
	 uIDHiliteItem: UINT,
	       uHilite: UINT

;int
GetMenuStringA proto _CType \
		 hMenu: HMENU,
	       uIDItem: UINT,
	      lpString: LPSTR,
	     nMaxCount: SINT,
		 uFlag: UINT
;int
GetMenuStringW proto _CType \
		 hMenu: HMENU,
	       uIDItem: UINT,
	      lpString: LPWSTR,
	     nMaxCount: SINT,
		 uFlag: UINT
ifdef _UNICODE
GetMenuString		equ <GetMenuStringW>
else
GetMenuString		equ <GetMenuStringA>
endif ;; NOT UNICODE

;UINT
GetMenuState proto _CType \
		 hMenu: HMENU,
		   uId: UINT,
		uFlags: UINT

;BOOL
DrawMenuBar proto _CType \
		  hWnd: HWND

if(_WIN32_WINNT GE 0x0501)
PMB_ACTIVE		equ 0x00000001
endif ;; _WIN32_WINNT GE 0x0501
;HMENU
GetSystemMenu proto _CType \
		  hWnd: HWND,
	       bRevert: BOOL

;HMENU
CreateMenu proto _CType

;HMENU
CreatePopupMenu proto _CType

;BOOL
DestroyMenu proto _CType \
		 hMenu: HMENU

;DWORD
CheckMenuItem proto _CType \
		 hMenu: HMENU,
	  uIDCheckItem: UINT,
		uCheck: UINT

;BOOL
EnableMenuItem proto _CType \
		 hMenu: HMENU,
	 uIDEnableItem: UINT,
	       uEnable: UINT

;HMENU
GetSubMenu proto _CType \
		 hMenu: HMENU,
		  nPos: SINT

;UINT
GetMenuItemID proto _CType \
		 hMenu: HMENU,
		  nPos: SINT

;int
GetMenuItemCount proto _CType \
		 hMenu: HMENU

;BOOL
InsertMenuA proto _CType \
		 hMenu: HMENU,
	     uPosition: UINT,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCSTR
;BOOL
InsertMenuW proto _CType \
		 hMenu: HMENU,
	     uPosition: UINT,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCWSTR
ifdef _UNICODE
InsertMenu		equ <InsertMenuW>
else
InsertMenu		equ <InsertMenuA>
endif ;; NOT UNICODE

;BOOL
AppendMenuA proto _CType \
		 hMenu: HMENU,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCSTR
;BOOL
AppendMenuW proto _CType \
		 hMenu: HMENU,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCWSTR
ifdef _UNICODE
AppendMenu		equ <AppendMenuW>
else
AppendMenu		equ <AppendMenuA>
endif ;; NOT UNICODE

;BOOL
ModifyMenuA proto _CType \
		  hMnu: HMENU,
	     uPosition: UINT,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCSTR
;BOOL
ModifyMenuW proto _CType \
		  hMnu: HMENU,
	     uPosition: UINT,
		uFlags: UINT,
	    uIDNewItem: UINT,
	    lpNewItem : LPCWSTR
ifdef _UNICODE
ModifyMenu		equ <ModifyMenuW>
else
ModifyMenu		equ <ModifyMenuA>
endif ;; NOT UNICODE

;BOOL
RemoveMenu proto _CType \
		 hMenu: HMENU,
	     uPosition: UINT,
		uFlags: UINT

;BOOL
DeleteMenu proto _CType \
		 hMenu: HMENU,
	     uPosition: UINT,
		uFlags: UINT

;BOOL
SetMenuItemBitmaps proto _CType \
		 hMenu: HMENU,
	     uPosition: UINT,
		uFlags: UINT,
      hBitmapUnchecked: HBITMAP,
	hBitmapChecked: HBITMAP

;LONG
GetMenuCheckMarkDimensions proto _CType

;BOOL
TrackPopupMenu proto _CType \
		 hMenu: HMENU,
		uFlags: UINT,
		     x: SINT,
		     y: SINT,
	     nReserved: SINT,
		  hWnd: HWND,
	       prcRect: LPRECT

if(WINVER GE 0x0400)
;; return codes for WM_MENUCHAR
MNC_IGNORE		equ 0
MNC_CLOSE		equ 1
MNC_EXECUTE		equ 2
MNC_SELECT		equ 3

TPMPARAMS		STRUC
cbSize			UINT ?	;; Size of structure
rcExclude		RECT <> ;; Screen coordinates of rectangle to exclude when positioning
TPMPARAMS		ENDS
LPTPMPARAMS		typedef ptr TPMPARAMS

;BOOL
TrackPopupMenuEx proto _CType \
		      : HMENU,
		      : UINT,
		      : SINT,
		      : SINT,
		      : HWND,
		      : LPTPMPARAMS
endif ;; WINVER GE 0x0400

if(_WIN32_WINNT GE 0x0601)
;BOOL
CalculatePopupWindowPosition proto _CType \
	   anchorPoint: ptr POINT,
	    windowSize: ptr POINT,
		 flags: UINT,
	   excludeRect: ptr RECT,
   popupWindowPosition: ptr RECT
endif ;; _WIN32_WINNT GE 0x0601

if(WINVER GE 0x0500)
MNS_NOCHECK		equ 0x80000000
MNS_MODELESS		equ 0x40000000
MNS_DRAGDROP		equ 0x20000000
MNS_AUTODISMISS		equ 0x10000000
MNS_NOTIFYBYPOS		equ 0x08000000
MNS_CHECKORBMP		equ 0x04000000

MIM_MAXHEIGHT		equ 0x00000001
MIM_BACKGROUND		equ 0x00000002
MIM_HELPID		equ 0x00000004
MIM_MENUDATA		equ 0x00000008
MIM_STYLE		equ 0x00000010
MIM_APPLYTOSUBMENUS	equ 0x80000000

MENUINFO		STRUC
cbSize			dd ?
fMask			dd ?
dwStyle			dd ?
cyMax			UINT ?
hbrBack			HBRUSH ?
dwContextHelpID		dd ?
dwMenuData		dd ?
MENUINFO		ENDS
LPMENUINFO		typedef ptr MENUINFO
LPCMENUINFO		typedef ptr MENUINFO

;BOOL
GetMenuInfo proto _CType \
		      : HMENU,
		      : LPMENUINFO

;BOOL
SetMenuInfo proto _CType \
		      : HMENU,
		      : LPCMENUINFO

;BOOL
EndMenu proto _CType

;;
;; WM_MENUDRAG return values.
;;
MND_CONTINUE		equ 0
MND_ENDMENU		equ 1

MENUGETOBJECTINFO	STRUC
dwFlags			dd ?
uPos			UINT ?
hmenu			HMENU ?
riid			PVOID ?
pvObj			PVOID ?
MENUGETOBJECTINFO	ENDS
PMENUGETOBJECTINFO	typedef ptr MENUGETOBJECTINFO

;;
;; MENUGETOBJECTINFO dwFlags values
;;
MNGOF_GAP		equ 0x00000003

;;
;; WM_MENUGETOBJECT return values
;;
MNGO_NOINTERFACE	equ 0x00000000
MNGO_NOERROR		equ 0x00000001
endif ;; WINVER GE 0x0500

if(WINVER GE 0x0400)
MIIM_STATE		equ 0x00000001
MIIM_ID			equ 0x00000002
MIIM_SUBMENU		equ 0x00000004
MIIM_CHECKMARKS		equ 0x00000008
MIIM_TYPE		equ 0x00000010
MIIM_DATA		equ 0x00000020
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0500)
MIIM_STRING		equ 0x00000040
MIIM_BITMAP		equ 0x00000080
MIIM_FTYPE		equ 0x00000100

HBMMENU_CALLBACK	equ (-1)
HBMMENU_SYSTEM		equ (1)
HBMMENU_MBAR_RESTORE	equ (2)
HBMMENU_MBAR_MINIMIZE	equ (3)
HBMMENU_MBAR_CLOSE	equ (5)
HBMMENU_MBAR_CLOSE_D	equ (6)
HBMMENU_MBAR_MINIMIZE_D equ (7)
HBMMENU_POPUP_CLOSE	equ (8)
HBMMENU_POPUP_RESTORE	equ (9)
HBMMENU_POPUP_MAXIMIZE	equ (10)
HBMMENU_POPUP_MINIMIZE	equ (11)
endif ;; WINVER GE 0x0500

if(WINVER GE 0x0400)
MENUITEMINFOA		STRUC
cbSize			UINT ?
fMask			UINT ?
fType			UINT ?	;; used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
fState			UINT ?	;; used if MIIM_STATE
wID			UINT ?	;; used if MIIM_ID
hSubMenu		HMENU ? ;; used if MIIM_SUBMENU
hbmpChecked		HBITMAP ?	;; used if MIIM_CHECKMARKS
hbmpUnchecked		HBITMAP ?	;; used if MIIM_CHECKMARKS
dwItemData		dd ?	;; used if MIIM_DATA
dwTypeData		LPSTR ? ;; used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
cch			UINT ?	;; used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
if (_WIN32_WINNT GE 0x0500)
hbmpItem		HBITMAP ?	;; used if MIIM_BITMAP
endif
MENUITEMINFOA		ENDS
LPMENUITEMINFOA		typedef ptr MENUITEMINFOA
MENUITEMINFOW		STRUC
cbSize			UINT ?
fMask			UINT ?
fType			UINT ?	;; used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
fState			UINT ?	;; used if MIIM_STATE
wID			UINT ?	;; used if MIIM_ID
hSubMenu		HMENU ? ;; used if MIIM_SUBMENU
hbmpChecked		HBITMAP ?	;; used if MIIM_CHECKMARKS
hbmpUnchecked		HBITMAP ?	;; used if MIIM_CHECKMARKS
dwItemData		dd ?	;; used if MIIM_DATA
dwTypeData		LPWSTR ?	;; used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
cch			UINT ?	;; used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
if (_WIN32_WINNT GE 0x0500)
hbmpItem		HBITMAP ?	;; used if MIIM_BITMAP
endif
MENUITEMINFOW		ENDS
LPMENUITEMINFOW		typedef ptr MENUITEMINFOW
ifdef _UNICODE
MENUITEMINFO		typedef MENUITEMINFOW
LPMENUITEMINFO		typedef LPMENUITEMINFOW
else
MENUITEMINFO		typedef MENUITEMINFOA
LPMENUITEMINFO		typedef LPMENUITEMINFOA
endif ;; UNICODE
LPCMENUITEMINFOA	typedef ptr MENUITEMINFOA
LPCMENUITEMINFOW	typedef ptr MENUITEMINFOW
ifdef _UNICODE
LPCMENUITEMINFO		typedef LPCMENUITEMINFOW
else
LPCMENUITEMINFO		typedef LPCMENUITEMINFOA
endif ;; UNICODE

;BOOL
InsertMenuItemA proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPCMENUITEMINFOA
;BOOL
InsertMenuItemW proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPCMENUITEMINFOW
ifdef _UNICODE
InsertMenuItem		equ <InsertMenuItemW>
else
InsertMenuItem		equ <InsertMenuItemA>
endif ;; NOT UNICODE

;BOOL
GetMenuItemInfoA proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPMENUITEMINFOA
;BOOL
GetMenuItemInfoW proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPMENUITEMINFOW
ifdef _UNICODE
GetMenuItemInfo		equ <GetMenuItemInfoW>
else
GetMenuItemInfo		equ <GetMenuItemInfoA>
endif ;; NOT UNICODE

;BOOL
SetMenuItemInfoA proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPCMENUITEMINFOA
;BOOL
SetMenuItemInfoW proto _CType \
		      : HMENU,
		      : UINT,
		      : BOOL,
		      : LPCMENUITEMINFOW
ifdef _UNICODE
SetMenuItemInfo		equ <SetMenuItemInfoW>
else
SetMenuItemInfo		equ <SetMenuItemInfoA>
endif ;; NOT UNICODE


GMDI_USEDISABLED	equ 0x0001
GMDI_GOINTOPOPUPS	equ 0x0002

;UINT
GetMenuDefaultItem proto _CType \
		 hMenu: HMENU,
		fByPos: UINT,
	     gmdiFlags: UINT
;BOOL
SetMenuDefaultItem proto _CType \
		 hMenu: HMENU,
		 uItem: UINT,
		fByPos: UINT

;BOOL
GetMenuItemRect proto _CType \
		  hWnd: HWND,
		 hMenu: HMENU,
		 uItem: UINT,
	      lprcItem: LPRECT
;int
MenuItemFromPoint proto _CType \
		  hWnd: HWND,
		 hMenu: HMENU,
	      ptScreen: POINT
endif ;; WINVER GE 0x0400

;;
;; Flags for TrackPopupMenu
;;
TPM_LEFTBUTTON		equ 0x0000
TPM_RIGHTBUTTON		equ 0x0002
TPM_LEFTALIGN		equ 0x0000
TPM_CENTERALIGN		equ 0x0004
TPM_RIGHTALIGN		equ 0x0008
if(WINVER GE 0x0400)
TPM_TOPALIGN		equ 0x0000
TPM_VCENTERALIGN	equ 0x0010
TPM_BOTTOMALIGN		equ 0x0020

TPM_HORIZONTAL		equ 0x0000     ;; Horz alignment matters more
TPM_VERTICAL		equ 0x0040     ;; Vert alignment matters more
TPM_NONOTIFY		equ 0x0080     ;; Don't send any notification msgs
TPM_RETURNCMD		equ 0x0100
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0500)
TPM_RECURSE		equ 0x0001
TPM_HORPOSANIMATION	equ 0x0400
TPM_HORNEGANIMATION	equ 0x0800
TPM_VERPOSANIMATION	equ 0x1000
TPM_VERNEGANIMATION	equ 0x2000
if(_WIN32_WINNT GE 0x0500)
TPM_NOANIMATION		equ 0x4000
endif ;; _WIN32_WINNT GE 0x0500
if(_WIN32_WINNT GE 0x0501)
TPM_LAYOUTRTL		equ 0x8000
endif ;; _WIN32_WINNT GE 0x0501
endif ;; WINVER GE 0x0500
if(_WIN32_WINNT GE 0x0601)
TPM_WORKAREA		equ 0x10000
endif ;; _WIN32_WINNT GE 0x0601
endif ;; WINVER GE 0x0500

endif ;; NOT NOMENUS

if(WINVER GE 0x0400)
;;
;; Drag-and-drop support
;;

DROPSTRUCT		STRUC
hwndSource		HWND ?
hwndSink		HWND ?
wFmt			dd ?
dwData			dd ?
ptDrop			POINT <>
dwControlData		dd ?
DROPSTRUCT		ENDS
PDROPSTRUCT		typedef ptr DROPSTRUCT
LPDROPSTRUCT		typedef ptr DROPSTRUCT

DOF_EXECUTABLE		equ 0x8001	;; wFmt flags
DOF_DOCUMENT		equ 0x8002
DOF_DIRECTORY		equ 0x8003
DOF_MULTIPLE		equ 0x8004
DOF_PROGMAN		equ 0x0001
DOF_SHELLDATA		equ 0x0002

DO_DROPFILE		equ 0x454C4946
DO_PRINTFILE		equ 0x544E5250

;DWORD
DragObject proto _CType \
		      : HWND,
		      : HWND,
		      : UINT,
		      : DWORD,
		      : HCURSOR

;BOOL
DragDetect proto _CType \
		      : HWND,
		      : POINT
endif ;; WINVER GE 0x0400

;BOOL
DrawIcon proto _CType \
		   hDC: HDC,
		     X: SINT,
		     Y: SINT,
		 hIcon: HICON

ifndef NODRAWTEXT

;;
;; DrawText() Format Flags
;;
DT_TOP			equ 0x00000000
DT_LEFT			equ 0x00000000
DT_CENTER		equ 0x00000001
DT_RIGHT		equ 0x00000002
DT_VCENTER		equ 0x00000004
DT_BOTTOM		equ 0x00000008
DT_WORDBREAK		equ 0x00000010
DT_SINGLELINE		equ 0x00000020
DT_EXPANDTABS		equ 0x00000040
DT_TABSTOP		equ 0x00000080
DT_NOCLIP		equ 0x00000100
DT_EXTERNALLEADING	equ 0x00000200
DT_CALCRECT		equ 0x00000400
DT_NOPREFIX		equ 0x00000800
DT_INTERNAL		equ 0x00001000

if(WINVER GE 0x0400)
DT_EDITCONTROL		equ 0x00002000
DT_PATH_ELLIPSIS	equ 0x00004000
DT_END_ELLIPSIS		equ 0x00008000
DT_MODIFYSTRING		equ 0x00010000
DT_RTLREADING		equ 0x00020000
DT_WORD_ELLIPSIS	equ 0x00040000
if(WINVER GE 0x0500)
DT_NOFULLWIDTHCHARBREAK equ 0x00080000
if(_WIN32_WINNT GE 0x0500)
DT_HIDEPREFIX		equ 0x00100000
DT_PREFIXONLY		equ 0x00200000
endif ;; _WIN32_WINNT GE 0x0500
endif ;; WINVER GE 0x0500


DRAWTEXTPARAMS		STRUC
cbSize			UINT ?
iTabLength		SINT ?
iLeftMargin		SINT ?
iRightMargin		SINT ?
uiLengthDrawn		UINT ?
DRAWTEXTPARAMS		ENDS
LPDRAWTEXTPARAMS	typedef ptr DRAWTEXTPARAMS
endif ;; WINVER GE 0x0400


;int
DrawTextA proto _CType \
		   hDC: HDC,
	      lpString: LPCSTR,
		nCount: SINT,
		lpRect: LPRECT,
	       uFormat: UINT
;int
DrawTextW proto _CType \
		   hDC: HDC,
	      lpString: LPCWSTR,
		nCount: SINT,
		lpRect: LPRECT,
	       uFormat: UINT
ifdef _UNICODE
DrawText		equ <DrawTextW>
else
DrawText		equ <DrawTextA>
endif ;; NOT UNICODE


if(WINVER GE 0x0400)
;int
DrawTextExA proto _CType \
		      : HDC,
		      : LPSTR,
		      : SINT,
		      : LPRECT,
		      : UINT,
		      : LPDRAWTEXTPARAMS
;int
DrawTextExW proto _CType \
		      : HDC,
		      : LPWSTR,
		      : SINT,
		      : LPRECT,
		      : UINT,
		      : LPDRAWTEXTPARAMS
ifdef _UNICODE
DrawTextEx		equ <DrawTextExW>
else
DrawTextEx		equ <DrawTextExA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400

endif ;; NOT NODRAWTEXT

;BOOL
GrayStringA proto _CType \
		   hDC: HDC,
		hBrush: HBRUSH,
	  lpOutputFunc: GRAYSTRINGPROC,
		lpData: LPARAM,
		nCount: SINT,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT
;BOOL
GrayStringW proto _CType \
		   hDC: HDC,
		hBrush: HBRUSH,
	  lpOutputFunc: GRAYSTRINGPROC,
		lpData: LPARAM,
		nCount: SINT,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT
ifdef _UNICODE
GrayString		equ <GrayStringW>
else
GrayString		equ <GrayStringA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;; Monolithic state-drawing routine
;; Image type
DST_COMPLEX		equ 0x0000
DST_TEXT		equ 0x0001
DST_PREFIXTEXT		equ 0x0002
DST_ICON		equ 0x0003
DST_BITMAP		equ 0x0004

;; State type
DSS_NORMAL		equ 0x0000
DSS_UNION		equ 0x0010  ;; Gray string appearance
DSS_DISABLED		equ 0x0020
DSS_MONO		equ 0x0080
DSS_RIGHT		equ 0x8000
if(_WIN32_WINNT GE 0x0500)
DSS_HIDEPREFIX		equ 0x0200
DSS_PREFIXONLY		equ 0x0400
endif ;; _WIN32_WINNT GE 0x0500

;BOOL
DrawStateA proto _CType \
		      : HDC,
		      : HBRUSH,
		      : DRAWSTATEPROC,
		      : LPARAM,
		      : WPARAM,
		      : SINT,
		      : SINT,
		      : SINT,
		      : SINT,
		      : UINT
;BOOL
DrawStateW proto _CType \
		      : HDC,
		      : HBRUSH,
		      : DRAWSTATEPROC,
		      : LPARAM,
		      : WPARAM,
		      : SINT,
		      : SINT,
		      : SINT,
		      : SINT,
		      : UINT
ifdef _UNICODE
DrawState		equ <DrawStateW>
else
DrawState		equ <DrawStateA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400

;LONG
TabbedTextOutA proto _CType \
		   hDC: HDC,
		     X: SINT,
		     Y: SINT,
	      lpString: LPCSTR,
		nCount: SINT,
	 nTabPositions: SINT,
   lpnTabStopPositions: LPINT,
	    nTabOrigin: SINT
;LONG
TabbedTextOutW proto _CType \
		   hDC: HDC,
		     X: SINT,
		     Y: SINT,
	      lpString: LPCWSTR,
		nCount: SINT,
	 nTabPositions: SINT,
   lpnTabStopPositions: LPINT,
	    nTabOrigin: SINT
ifdef _UNICODE
TabbedTextOut		equ <TabbedTextOutW>
else
TabbedTextOut		equ <TabbedTextOutA>
endif ;; NOT UNICODE

;DWORD
GetTabbedTextExtentA proto _CType \
		   hDC: HDC,
	      lpString: LPCSTR,
		nCount: SINT,
	 nTabPositions: SINT,
   lpnTabStopPositions: LPINT
;DWORD
GetTabbedTextExtentW proto _CType \
		   hDC: HDC,
	      lpString: LPCWSTR,
		nCount: SINT,
	 nTabPositions: SINT,
   lpnTabStopPositions: LPINT
ifdef _UNICODE
GetTabbedTextExtent	equ <GetTabbedTextExtentW>
else
GetTabbedTextExtent	equ <GetTabbedTextExtentA>
endif ;; NOT UNICODE

;BOOL
UpdateWindow proto _CType \
		  hWnd: HWND

;HWND
SetActiveWindow proto _CType \
		  hWnd: HWND

if (_WIN32_WINNT GE 0x0500)
;HWND
GetForegroundWindow	proto _CType
else
GetForegroundWindow_P	typedef proto _CType
GetForegroundWindow_T	typedef ptr GetForegroundWindow_P
externdef		GetForegroundWindow:GetForegroundWindow_T
endif

if(WINVER GE 0x0400)
;BOOL
PaintDesktop proto _CType \
		   hdc: HDC

endif ;; WINVER GE 0x0400

;BOOL
SetForegroundWindow proto _CType \
		  hWnd: HWND

if(_WIN32_WINNT GE 0x0500)
;BOOL
AllowSetForegroundWindow proto _CType \
	   dwProcessId: DWORD

ASFW_ANY		equ (-1)

;BOOL
LockSetForegroundWindow proto _CType \
	     uLockCode: UINT

LSFW_LOCK		equ 1
LSFW_UNLOCK		equ 2
endif ;; _WIN32_WINNT GE 0x0500

;HWND
WindowFromDC proto _CType \
		   hDC: HDC

;HDC
GetDC proto _CType \
		  hWnd: HWND

;HDC
GetDCEx proto _CType \
		 hWnd : HWND,
	      hrgnClip: HRGN,
		 flags: DWORD

;;
;; GetDCEx() flags
;;
DCX_WINDOW		equ 0x00000001
DCX_CACHE		equ 0x00000002
DCX_NORESETATTRS	equ 0x00000004
DCX_CLIPCHILDREN	equ 0x00000008
DCX_CLIPSIBLINGS	equ 0x00000010
DCX_PARENTCLIP		equ 0x00000020
DCX_EXCLUDERGN		equ 0x00000040
DCX_INTERSECTRGN	equ 0x00000080
DCX_EXCLUDEUPDATE	equ 0x00000100
DCX_INTERSECTUPDATE	equ 0x00000200
DCX_LOCKWINDOWUPDATE	equ 0x00000400
DCX_VALIDATE		equ 0x00200000

;BOOL
AlignRects proto _CType \
		   arc: LPRECT,
		cCount: DWORD,
	      iPrimary: DWORD,
	       dwFlags: DWORD

;;
;; AlignRects flags
;;

CUDR_NORMAL		equ 0x0000
CUDR_NOSNAPTOGRID	equ 0x0001
CUDR_NORESOLVEPOSITIONS equ 0x0002
CUDR_NOCLOSEGAPS	equ 0x0004
CUDR_NEGATIVECOORDS	equ 0x0008
CUDR_NOPRIMARY		equ 0x0010


;HDC
GetWindowDC proto _CType \
		  hWnd: HWND

;int
ReleaseDC proto _CType \
		  hWnd: HWND,
		   hDC: HDC

;HDC
BeginPaint proto _CType \
		  hWnd: HWND,
	       lpPaint: LPPAINTSTRUCT

;BOOL
EndPaint proto _CType \
		  hWnd: HWND,
	       lpPaint: ptr PAINTSTRUCT

;BOOL
GetUpdateRect proto _CType \
		  hWnd: HWND,
		lpRect: LPRECT,
		bErase: BOOL

;int
GetUpdateRgn proto _CType \
		  hWnd: HWND,
		  hRgn: HRGN,
		bErase: BOOL

;int
SetWindowRgn proto _CType \
		  hWnd: HWND,
		  hRgn: HRGN,
	       bRedraw: BOOL

;int
GetWindowRgn proto _CType \
		  hWnd: HWND,
		  hRgn: HRGN
if(_WIN32_WINNT GE 0x0501)
;int
GetWindowRgnBox proto _CType \
		  hWnd: HWND,
		  lprc: LPRECT
endif ;; _WIN32_WINNT GE 0x0501

;int
ExcludeUpdateRgn proto _CType \
		   hDC: HDC,
		  hWnd: HWND

;BOOL
InvalidateRect proto _CType \
		 hWnd : HWND,
		lpRect: LPRECT,
		bErase: BOOL

;BOOL
ValidateRect proto _CType \
		 hWnd : HWND,
		lpRect: LPRECT

;BOOL
InvalidateRgn proto _CType \
		  hWnd: HWND,
		  hRgn: HRGN,
		bErase: BOOL

;BOOL
ValidateRgn proto _CType \
		  hWnd: HWND,
		  hRgn: HRGN


;BOOL
RedrawWindow proto _CType \
		  hWnd: HWND,
	    lprcUpdate: LPRECT,
	    hrgnUpdate: HRGN,
		 flags: UINT

;;
;; RedrawWindow() flags
;;
RDW_INVALIDATE		equ 0x0001
RDW_INTERNALPAINT	equ 0x0002
RDW_ERASE		equ 0x0004

RDW_VALIDATE		equ 0x0008
RDW_NOINTERNALPAINT	equ 0x0010
RDW_NOERASE		equ 0x0020

RDW_NOCHILDREN		equ 0x0040
RDW_ALLCHILDREN		equ 0x0080

RDW_UPDATENOW		equ 0x0100
RDW_ERASENOW		equ 0x0200

RDW_FRAME		equ 0x0400
RDW_NOFRAME		equ 0x0800


;;
;; LockWindowUpdate API
;;

;BOOL
LockWindowUpdate proto _CType \
	      hWndLock: HWND

;BOOL
ScrollWindow proto _CType \
		  hWnd: HWND,
	       XAmount: SINT,
	       YAmount: SINT,
		lpRect: LPRECT,
	    lpClipRect: LPRECT

;BOOL
ScrollDC proto _CType \
		   hDC: HDC,
		   _dx: SINT,
		    dy: SINT,
	    lprcScroll: LPRECT,
	     lprcClip : LPRECT,
	    hrgnUpdate: HRGN,
	    lprcUpdate: LPRECT

;int
ScrollWindowEx proto _CType \
		  hWnd: HWND,
		   _dx: SINT,
		    dy: SINT,
	     prcScroll: LPRECT,
	      prcClip : LPRECT,
	    hrgnUpdate: HRGN,
	     prcUpdate: LPRECT,
		 flags: UINT

SW_SCROLLCHILDREN	equ 0x0001  ;; Scroll children within *lprcScroll.
SW_INVALIDATE		equ 0x0002  ;; Invalidate after scrolling
SW_ERASE		equ 0x0004  ;; If SW_INVAIDATE, don't send WM_ERASEBACKGROUND
if(WINVER GE 0x0500)
SW_SMOOTHSCROLL		equ 0x0010  ;; Use smooth scrolling
endif ;; WINVER GE 0x0500

ifndef NOSCROLL

;int
SetScrollPos proto _CType \
		  hWnd: HWND,
		  nBar: SINT,
		  nPos: SINT,
	       bRedraw: BOOL

;int
GetScrollPos proto _CType \
		  hWnd: HWND,
		  nBar: SINT

;BOOL
SetScrollRange proto _CType \
		  hWnd: HWND,
		  nBar: SINT,
	       nMinPos: SINT,
	       nMaxPos: SINT,
	       bRedraw: BOOL

;BOOL
GetScrollRange proto _CType \
		  hWnd: HWND,
		  nBar: SINT,
	      lpMinPos: LPINT,
	      lpMaxPos: LPINT

;BOOL
ShowScrollBar proto _CType \
		  hWnd: HWND,
		  wBar: SINT,
		 bShow: BOOL

;BOOL
EnableScrollBar proto _CType \
		  hWnd: HWND,
	      wSBflags: UINT,
	       wArrows: UINT


;;
;; EnableScrollBar() flags
;;
ESB_ENABLE_BOTH		equ 0x0000
ESB_DISABLE_BOTH	equ 0x0003

ESB_DISABLE_LEFT	equ 0x0001
ESB_DISABLE_RIGHT	equ 0x0002

ESB_DISABLE_UP		equ 0x0001
ESB_DISABLE_DOWN	equ 0x0002

ESB_DISABLE_LTUP	equ ESB_DISABLE_LEFT
ESB_DISABLE_RTDN	equ ESB_DISABE_RIGHT


endif  ;; NOT NOSCROLL

;BOOL
SetPropA proto _CType \
		  hWnd: HWND,
	      lpString: LPCSTR,
		 hData: HANDLE
;BOOL
SetPropW proto _CType \
		  hWnd: HWND,
	      lpString: LPCWSTR,
		 hData: HANDLE
ifdef _UNICODE
SetProp			equ <SetPropW>
else
SetProp			equ <SetPropA>
endif ;; NOT UNICODE

;HANDLE
GetPropA proto _CType \
		  hWnd: HWND,
	      lpString: LPCSTR
;HANDLE
GetPropW proto _CType \
		  hWnd: HWND,
	      lpString: LPCWSTR
ifdef _UNICODE
GetProp			equ <GetPropW>
else
GetProp			equ <GetPropA>
endif ;; NOT UNICODE

;HANDLE
RemovePropA proto _CType \
		  hWnd: HWND,
	      lpString: LPCSTR
;HANDLE
RemovePropW proto _CType \
		  hWnd: HWND,
	      lpString: LPCWSTR
ifdef _UNICODE
RemoveProp		equ <RemovePropW>
else
RemoveProp		equ <RemovePropA>
endif ;; NOT UNICODE

;int
EnumPropsExA proto _CType \
		  hWnd: HWND,
	    lpEnumFunc: PROPENUMPROCEXA,
		lParam: LPARAM
;int
EnumPropsExW proto _CType \
		  hWnd: HWND,
	    lpEnumFunc: PROPENUMPROCEXW,
		lParam: LPARAM
ifdef _UNICODE
EnumPropsEx		equ <EnumPropsExW>
else
EnumPropsEx		equ <EnumPropsExA>
endif ;; NOT UNICODE

;int
EnumPropsA proto _CType \
		  hWnd: HWND,
	    lpEnumFunc: PROPENUMPROCA
;int
EnumPropsW proto _CType \
		  hWnd: HWND,
	    lpEnumFunc: PROPENUMPROCW
ifdef _UNICODE
EnumProps		equ <EnumPropsW>
else
EnumProps		equ <EnumPropsA>
endif ;; NOT UNICODE

;BOOL
SetWindowTextA proto _CType \
		  hWnd: HWND,
	      lpString: LPCSTR
;BOOL
SetWindowTextW proto _CType \
		  hWnd: HWND,
	      lpString: LPCWSTR
ifdef _UNICODE
SetWindowText		equ <SetWindowTextW>
else
SetWindowText		equ <SetWindowTextA>
endif ;; NOT UNICODE

;int
GetWindowTextA proto _CType \
		  hWnd: HWND,
	      lpString: LPSTR,
	     nMaxCount: SINT
;int
GetWindowTextW proto _CType \
		  hWnd: HWND,
	      lpString: LPWSTR,
	     nMaxCount: SINT
ifdef _UNICODE
GetWindowText		equ <GetWindowTextW>
else
GetWindowText		equ <GetWindowTextA>
endif ;; NOT UNICODE

;int
GetWindowTextLengthA proto _CType \
		  hWnd: HWND
;int
GetWindowTextLengthW proto _CType \
		  hWnd: HWND
ifdef _UNICODE
GetWindowTextLength	equ <GetWindowTextLengthW>
else
GetWindowTextLength	equ <GetWindowTextLengthA>
endif ;; NOT UNICODE

;BOOL
GetClientRect proto _CType \
		  hWnd: HWND,
		lpRect: LPRECT

;BOOL
GetWindowRect proto _CType \
		  hWnd: HWND,
		lpRect: LPRECT

;BOOL
AdjustWindowRect proto _CType \
		lpRect: LPRECT,
	       dwStyle: DWORD,
		 bMenu: BOOL

;BOOL
AdjustWindowRectEx proto _CType \
		lpRect: LPRECT,
	       dwStyle: DWORD,
		 bMenu: BOOL,
	     dwExStyle: DWORD

if(WINVER GE 0x0400)
HELPINFO_WINDOW		equ 0x0001
HELPINFO_MENUITEM	equ 0x0002
HELPINFO		STRUC	;; Structure pointed to by lParam of WM_HELP
cbSize			UINT ?	;; Size in bytes of this struct
iContextType		SINT ?	;; Either HELPINFO_WINDOW or HELPINFO_MENUITEM
iCtrlId			SINT ?	;; Control Id or a Menu item Id.
hItemHandle		HANDLE ?	;; hWnd of control or hMenu.
dwContextId		dd ?	;; Context Id associated with this item
MousePos		POINT <> ;; Mouse Position in screen co-ordinates
HELPINFO		ENDS
LPHELPINFO		typedef ptr HELPINFO

;BOOL
  SetWindowContextHelpId proto _CType \
		      : HWND,
		      : DWORD
;DWORD
 GetWindowContextHelpId proto _CType \
		      : HWND
;BOOL
  SetMenuContextHelpId proto _CType \
		      : HMENU,
		      : DWORD
;DWORD
 GetMenuContextHelpId proto _CType \
		      : HMENU

endif ;; WINVER GE 0x0400


ifndef NOMB

;;
;; MessageBox() Flags
;;
MB_OK			equ 0x00000000
MB_OKCANCEL		equ 0x00000001
MB_ABORTRETRYIGNORE	equ 0x00000002
MB_YESNOCANCEL		equ 0x00000003
MB_YESNO		equ 0x00000004
MB_RETRYCANCEL		equ 0x00000005
if(WINVER GE 0x0500)
MB_CANCELTRYCONTINUE	equ 0x00000006
endif ;; WINVER GE 0x0500

MB_ICONHAND		equ 0x00000010
MB_ICONQUESTION		equ 0x00000020
MB_ICONEXCLAMATION	equ 0x00000030
MB_ICONASTERISK		equ 0x00000040

if(WINVER GE 0x0400)
MB_USERICON		equ 0x00000080
MB_ICONWARNING		equ MB_ICONEXCAMATION
MB_ICONERROR		equ MB_ICONHAND
endif ;; WINVER GE 0x0400

MB_ICONINFORMATION	equ MB_ICONASTERISK
MB_ICONSTOP		equ MB_ICONHAND

MB_DEFBUTTON1		equ 0x00000000
MB_DEFBUTTON2		equ 0x00000100
MB_DEFBUTTON3		equ 0x00000200
if(WINVER GE 0x0400)
MB_DEFBUTTON4		equ 0x00000300
endif ;; WINVER GE 0x0400

MB_APPLMODAL		equ 0x00000000
MB_SYSTEMMODAL		equ 0x00001000
MB_TASKMODAL		equ 0x00002000
if(WINVER GE 0x0400)
MB_HELP			equ 0x00004000 ;; Help Button
endif ;; WINVER GE 0x0400

MB_NOFOCUS		equ 0x00008000
MB_SETFOREGROUND	equ 0x00010000
MB_DEFAULT_DESKTOP_ONLY equ 0x00020000

if(WINVER GE 0x0400)
MB_TOPMOST		equ 0x00040000
MB_RIGHT		equ 0x00080000
MB_RTLREADING		equ 0x00100000


endif ;; WINVER GE 0x0400

ifdef _WIN32_WINNT
if (_WIN32_WINNT GE 0x0400)
MB_SERVICE_NOTIFICATION equ 0x00200000
else
MB_SERVICE_NOTIFICATION equ 0x00040000
endif
MB_SERVICE_NOTIFICATION_NT3X equ 0x00040000
endif

MB_TYPEMASK		equ 0x0000000F
MB_ICONMASK		equ 0x000000F0
MB_DEFMASK		equ 0x00000F00
MB_MODEMASK		equ 0x00003000
MB_MISCMASK		equ 0x0000C000

;int
MessageBoxA proto _CType \
		 hWnd : HWND,
		lpText: LPCSTR,
	     lpCaption: LPCSTR,
		 uType: UINT
;int
MessageBoxW proto _CType \
		 hWnd : HWND,
		lpText: LPCWSTR,
	     lpCaption: LPCWSTR,
		 uType: UINT
ifdef _UNICODE
MessageBox		equ <MessageBoxW>
else
MessageBox		equ <MessageBoxA>
endif ;; NOT UNICODE

;int
MessageBoxExA proto _CType \
		 hWnd : HWND,
		lpText: LPCSTR,
	     lpCaption: LPCSTR,
		 uType: UINT,
	   wLanguageId: WORD
;int
MessageBoxExW proto _CType \
		 hWnd : HWND,
		lpText: LPCWSTR,
	     lpCaption: LPCWSTR,
		 uType: UINT,
	   wLanguageId: WORD
ifdef _UNICODE
MessageBoxEx		equ <MessageBoxExW>
else
MessageBoxEx		equ <MessageBoxExA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)

MSGBOXCALLBACK_T	typedef proto _CType lpHelpInfo:LPHELPINFO
MSGBOXCALLBACK		typedef ptr MSGBOXCALLBACK_T

MSGBOXPARAMSA		STRUC
cbSize			UINT ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
lpszText		LPCSTR ?
lpszCaption		LPCSTR ?
dwStyle			dd ?
lpszIcon		LPCSTR ?
dwContextHelpId		dd ?
lpfnMsgBoxCallback	MSGBOXCALLBACK ?
dwLanguageId		dd ?
MSGBOXPARAMSA		ENDS
PMSGBOXPARAMSA		typedef ptr MSGBOXPARAMSA
LPMSGBOXPARAMSA		typedef ptr MSGBOXPARAMSA
MSGBOXPARAMSW		STRUC
cbSize			UINT ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
lpszText		LPCWSTR ?
lpszCaption		LPCWSTR ?
dwStyle			dd ?
lpszIcon		LPCWSTR ?
dwContextHelpId		dd ?
lpfnMsgBoxCallback	MSGBOXCALLBACK ?
dwLanguageId		dd ?
MSGBOXPARAMSW		ENDS
PMSGBOXPARAMSW		typedef ptr MSGBOXPARAMSW
LPMSGBOXPARAMSW		typedef ptr MSGBOXPARAMSW
ifdef _UNICODE
MSGBOXPARAMS		typedef MSGBOXPARAMSW
PMSGBOXPARAMS		typedef PMSGBOXPARAMSW
LPMSGBOXPARAMS		typedef LPMSGBOXPARAMSW
else
MSGBOXPARAMS		typedef MSGBOXPARAMSA
PMSGBOXPARAMS		typedef PMSGBOXPARAMSA
LPMSGBOXPARAMS		typedef LPMSGBOXPARAMSA
endif ;; UNICODE


;int
MessageBoxIndirectA proto _CType \
		      : LPMSGBOXPARAMSA
;int
MessageBoxIndirectW proto _CType \
		      : LPMSGBOXPARAMSW
ifdef _UNICODE
MessageBoxIndirect	equ <MessageBoxIndirectW>
else
MessageBoxIndirect	equ <MessageBoxIndirectA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400



;BOOL
MessageBeep proto _CType \
		 uType: UINT

endif ;; NOT NOMB

;int
ShowCursor proto _CType \
		 bShow: BOOL

;BOOL
SetCursorPos proto _CType \
		     X: SINT,
		     Y: SINT
if(WINVER GE 0x0600)
;BOOL
SetPhysicalCursorPos proto _CType \
		     X: SINT,
		     Y: SINT
endif ;; WINVER GE 0x0600

;HCURSOR
SetCursor proto _CType \
	       hCursor: HCURSOR

;BOOL
GetCursorPos proto _CType \
	       lpPoint: LPPOINT

if(WINVER GE 0x0600)
;BOOL
GetPhysicalCursorPos proto _CType \
	       lpPoint: LPPOINT
endif ;; WINVER GE 0x0600

;BOOL
ClipCursor proto _CType \
		lpRect: LPRECT

;BOOL
GetClipCursor proto _CType \
		lpRect: LPRECT

;HCURSOR
GetCursor proto _CType

;BOOL
CreateCaret proto _CType \
		  hWnd: HWND,
	      hBitmap : HBITMAP,
		nWidth: SINT,
	       nHeight: SINT

;UINT
GetCaretBlinkTime proto _CType

;BOOL
SetCaretBlinkTime proto _CType \
	     uMSeconds: UINT

;BOOL
DestroyCaret proto _CType

;BOOL
HideCaret proto _CType \
		  hWnd: HWND

;BOOL
ShowCaret proto _CType \
		  hWnd: HWND

;BOOL
SetCaretPos proto _CType \
		     X: SINT,
		     Y: SINT

;BOOL
GetCaretPos proto _CType \
	       lpPoint: LPPOINT

;BOOL
ClientToScreen proto _CType \
		  hWnd: HWND,
	       lpPoint: LPPOINT

;BOOL
ScreenToClient proto _CType \
		  hWnd: HWND,
	       lpPoint: LPPOINT

if(WINVER GE 0x0600)
;BOOL
LogicalToPhysicalPoint proto _CType \
		  hWnd: HWND,
	       lpPoint: LPPOINT
;BOOL
PhysicalToLogicalPoint proto _CType \
		  hWnd: HWND,
	       lpPoint: LPPOINT
endif ;; WINVER GE 0x0600

;int
MapWindowPoints proto _CType \
	      hWndFrom: HWND,
		hWndTo: HWND,
	      lpPoints: LPPOINT,
	       cPoints: UINT

;HWND
WindowFromPoint proto _CType \
		 Point: POINT

if(WINVER GE 0x0600)
;HWND
WindowFromPhysicalPoint proto _CType \
		 Point: POINT
endif ;; WINVER GE 0x0600

;HWND
ChildWindowFromPoint proto _CType \
	    hWndParent: HWND,
		 Point: POINT

if(WINVER GE 0x0400)
CWP_ALL			equ 0x0000
CWP_SKIPINVISIBLE	equ 0x0001
CWP_SKIPDISABLED	equ 0x0002
CWP_SKIPTRANSPARENT	equ 0x0004

;HWND
ChildWindowFromPointEx proto _CType \
		      : HWND,
		      : POINT,
		      : UINT
endif ;; WINVER GE 0x0400

ifndef NOCOLOR

;;
;; Color Types
;;
CTLCOLOR_MSGBOX		equ 0
CTLCOLOR_EDIT		equ 1
CTLCOLOR_LISTBOX	equ 2
CTLCOLOR_BTN		equ 3
CTLCOLOR_DLG		equ 4
CTLCOLOR_SCROLLBAR	equ 5
CTLCOLOR_STATIC		equ 6
CTLCOLOR_MAX		equ 7

COLOR_SCROLLBAR		equ 0
COLOR_BACKGROUND	equ 1
COLOR_ACTIVECAPTION	equ 2
COLOR_INACTIVECAPTION	equ 3
COLOR_MENU		equ 4
COLOR_WINDOW		equ 5
COLOR_WINDOWFRAME	equ 6
COLOR_MENUTEXT		equ 7
COLOR_WINDOWTEXT	equ 8
COLOR_CAPTIONTEXT	equ 9
COLOR_ACTIVEBORDER	equ 10
COLOR_INACTIVEBORDER	equ 11
COLOR_APPWORKSPACE	equ 12
COLOR_HIGHLIGHT		equ 13
COLOR_HIGHLIGHTTEXT	equ 14
COLOR_BTNFACE		equ 15
COLOR_BTNSHADOW		equ 16
COLOR_GRAYTEXT		equ 17
COLOR_BTNTEXT		equ 18
COLOR_INACTIVECAPTIONTEXT equ 19
COLOR_BTNHIGHLIGHT	equ 20

if(WINVER GE 0x0400)
COLOR_3DDKSHADOW	equ 21
COLOR_3DLIGHT		equ 22
COLOR_INFOTEXT		equ 23
COLOR_INFOBK		equ 24
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0500)
COLOR_HOTLIGHT		equ 26
COLOR_GRADIENTACTIVECAPTION equ 27
COLOR_GRADIENTINACTIVECAPTION equ 28
if(WINVER GE 0x0501)
COLOR_MENUHILIGHT	equ 29
COLOR_MENUBAR		equ 30
endif ;; WINVER GE 0x0501
endif ;; WINVER GE 0x0500

if(WINVER GE 0x0400)
COLOR_DESKTOP		equ COLOR_BACKGROUND
COLOR_3DFACE		equ COLOR_BTNFACE
COLOR_3DSHADOW		equ COLOR_BTNSHADOW
COLOR_3DHIGHLIGHT	equ COLOR_BTNHIGHLIGHT
COLOR_3DHILIGHT		equ COLOR_BTNHIGHLIGHT
COLOR_BTNHILIGHT	equ COLOR_BTNHIGHLIGHT
endif ;; WINVER GE 0x0400


;DWORD
GetSysColor proto _CType \
		nIndex: SINT

if(WINVER GE 0x0400)
;HBRUSH
GetSysColorBrush proto _CType \
		nIndex: SINT


endif ;; WINVER GE 0x0400

;BOOL
SetSysColors proto _CType \
	     cElements: SINT,
	   lpaElements: ptr,
	  lpaRgbValues: ptr COLORREF

endif ;; NOT NOCOLOR

;BOOL
DrawFocusRect proto _CType \
		   hDC: HDC,
		  lprc: LPRECT

;int
FillRect proto _CType \
		   hDC: HDC,
		  lprc: LPRECT,
		   hbr: HBRUSH

;int
FrameRect proto _CType \
		   hDC: HDC,
		  lprc: LPRECT,
		   hbr: HBRUSH

;BOOL
InvertRect proto _CType \
		   hDC: HDC,
		  lprc: LPRECT

;BOOL
SetRect proto _CType \
		  lprc: LPRECT,
		 xLeft: SINT,
		  yTop: SINT,
		xRight: SINT,
	       yBottom: SINT

;BOOL
SetRectEmpty proto _CType \
		  lprc: LPRECT

;BOOL
CopyRect proto _CType \
	       lprcDst: LPRECT,
	       lprcSrc: LPRECT

;BOOL
InflateRect proto _CType \
		  lprc: LPRECT,
		   _dx: SINT,
		    dy: SINT

;BOOL
IntersectRect proto _CType \
	       lprcDst: LPRECT,
	      lprcSrc1: LPRECT,
	      lprcSrc2: LPRECT

;BOOL
UnionRect proto _CType \
	       lprcDst: LPRECT,
	      lprcSrc1: LPRECT,
	      lprcSrc2: LPRECT

;BOOL
SubtractRect proto _CType \
	       lprcDst: LPRECT,
	      lprcSrc1: LPRECT,
	      lprcSrc2: LPRECT

;BOOL
OffsetRect proto _CType \
		  lprc: LPRECT,
		   _dx: SINT,
		    dy: SINT

;BOOL
IsRectEmpty proto _CType \
		  lprc: LPRECT

;BOOL
EqualRect proto _CType \
		  lprc1: LPRECT,
		  lprc2: LPRECT

;BOOL
PtInRect proto _CType \
		  lprc: LPRECT,
		    pt: POINT

ifndef NOWINOFFSETS

;WORD
GetWindowWord proto _CType \
		  hWnd: HWND,
		nIndex: SINT

;WORD
SetWindowWord proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	      wNewWord: WORD

;LONG
GetWindowLongA proto _CType \
		  hWnd: HWND,
		nIndex: SINT
;LONG
GetWindowLongW proto _CType \
		  hWnd: HWND,
		nIndex: SINT
ifdef _UNICODE
GetWindowLong		equ <GetWindowLongW>
else
GetWindowLong		equ <GetWindowLongA>
endif ;; NOT UNICODE

;LONG
SetWindowLongA proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: LONG
;LONG
SetWindowLongW proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: LONG
ifdef _UNICODE
SetWindowLong		equ <SetWindowLongW>
else
SetWindowLong		equ <SetWindowLongA>
endif ;; NOT UNICODE

;WORD
GetClassWord proto _CType \
		  hWnd: HWND,
		nIndex: SINT

;WORD
SetClassWord proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	      wNewWord: WORD

;DWORD
GetClassLongA proto _CType \
		  hWnd: HWND,
		nIndex: SINT
;DWORD
GetClassLongW proto _CType \
		  hWnd: HWND,
		nIndex: SINT
ifdef _UNICODE
GetClassLong		equ <GetClassLongW>
else
GetClassLong		equ <GetClassLongA>
endif ;; NOT UNICODE

;DWORD
SetClassLongA proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: LONG
;DWORD
SetClassLongW proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: LONG
ifdef _UNICODE
SetClassLong		equ <SetClassLongW>
else
SetClassLong		equ <SetClassLongA>
endif ;; NOT UNICODE

endif ;; NOT NOWINOFFSETS


ifdef _WIN64

;LONG_PTR
GetWindowLongPtrA proto _CType \
		  hWnd: HWND,
		nIndex: SINT
GetWindowLongPtrW proto _CType \
		  hWnd: HWND,
		nIndex: SINT
ifdef _UNICODE
GetWindowLongPtr	equ <GetWindowLongPtrW>
else
GetWindowLongPtr	equ <GetWindowLongPtrA>
endif ;; NOT UNICODE

;LONG_PTR
SetWindowLongPtrA proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: PLONG
SetWindowLongPtrW proto _CType \
		  hWnd: HWND,
		nIndex: SINT,
	     dwNewLong: PLONG
ifdef _UNICODE
SetWindowLongPtr	equ <SetWindowLongPtrW>
else
SetWindowLongPtr	equ <SetWindowLongPtrA>
endif ;; NOT UNICODE

else  ;; _WIN64

GetWindowLongPtrA	equ <GetWindowLongA>
GetWindowLongPtrW	equ <GetWindowLongW>
ifdef _UNICODE
GetWindowLongPtr	equ <GetWindowLongPtrW>
else
GetWindowLongPtr	equ <GetWindowLongPtrA>
endif ;; NOT UNICODE
SetWindowLongPtrA	equ <SetWindowLongA>
SetWindowLongPtrW	equ <SetWindowLongW>
ifdef _UNICODE
SetWindowLongPtr	equ <SetWindowLongPtrW>
else
SetWindowLongPtr	equ <SetWindowLongPtrA>
endif ;; NOT UNICODE
endif ;; _WIN64

;HWND
GetDesktopWindow proto _CType


;HWND
GetParent proto _CType \
		  hWnd: HWND

;HWND
SetParent proto _CType \
	     hWndChild: HWND,
	 hWndNewParent: HWND

;BOOL
EnumChildWindows proto _CType \
	    hWndParent: HWND,
	    lpEnumFunc: WNDENUMPROC,
		lParam: LPARAM

;HWND
FindWindowA proto _CType \
	  lpClassName : LPCSTR,
	  lpWindowName: LPCSTR
;HWND
FindWindowW proto _CType \
	  lpClassName : LPCWSTR,
	  lpWindowName: LPCWSTR
ifdef _UNICODE
FindWindow		equ <FindWindowW>
else
FindWindow		equ <FindWindowA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;HWND
FindWindowExA proto _CType \
		      : HWND,
		      : HWND,
		      : LPCSTR,
		      : LPCSTR
;HWND
FindWindowExW proto _CType \
		      : HWND,
		      : HWND,
		      : LPCWSTR,
		      : LPCWSTR
ifdef _UNICODE
FindWindowEx		equ <FindWindowExW>
else
FindWindowEx		equ <FindWindowExA>
endif ;; NOT UNICODE

endif ;; WINVER GE 0x0400


;BOOL
EnumWindows proto _CType \
	    lpEnumFunc: WNDENUMPROC,
		lParam: LPARAM

;BOOL
EnumThreadWindows proto _CType \
	    dwThreadId: DWORD,
		  lpfn: WNDENUMPROC,
		lParam: LPARAM

EnumTaskWindows equ <EnumThreadWindows>

;int
GetClassNameA proto _CType \
		  hWnd: HWND,
	   lpClassName: LPSTR,
	     nMaxCount: SINT
;int
GetClassNameW proto _CType \
		  hWnd: HWND,
	   lpClassName: LPWSTR,
	     nMaxCount: SINT
ifdef _UNICODE
GetClassName		equ <GetClassNameW>
else
GetClassName		equ <GetClassNameA>
endif ;; NOT UNICODE

;HWND
GetTopWindow proto _CType \
		  hWnd: HWND

GetNextWindow macro hWnd, wCmd
	exitm<GetWindow(hWnd, wCmd)>
	endm
GetSysModalWindow macro
	exitm<(NULL)>
	endm
SetSysModalWindow macro hWnd
	exitm<(NULL)>
	endm

;DWORD
GetWindowThreadProcessId proto _CType \
		  hWnd: HWND,
	 lpdwProcessId: LPDWORD

GetWindowTask macro hWnd
	exitm<GetWindowThreadProcessId(hWnd, NULL)>
	endm

;HWND
GetLastActivePopup proto _CType \
		  hWnd: HWND

;;
;; GetWindow() Constants
;;
GW_HWNDFIRST		equ 0
GW_HWNDLAST		equ 1
GW_HWNDNEXT		equ 2
GW_HWNDPREV		equ 3
GW_OWNER		equ 4
GW_CHILD		equ 5
if (_WIN32_WINNT LE 0x0400)
GW_MAX			equ 5
else
GW_ENABLEDPOPUP		equ 6
GW_MAX			equ 6
endif

;HWND
GetWindow proto _CType \
		  hWnd: HWND,
		  uCmd: UINT

ifndef NOWH
ifdef STRICT

;HHOOK
SetWindowsHookA proto _CType \
	   nFilterType: SINT,
	 pfnFilterProc: HOOKPROC
;HHOOK
SetWindowsHookW proto _CType \
	   nFilterType: SINT,
	 pfnFilterProc: HOOKPROC
ifdef _UNICODE
SetWindowsHook		equ <SetWindowsHookW>
else
SetWindowsHook		equ <SetWindowsHookA>
endif ;; NOT UNICODE

else ;; NOT STRICT

;HOOKPROC
SetWindowsHookA proto _CType \
	   nFilterType: SINT,
	 pfnFilterProc: HOOKPROC
;HOOKPROC
SetWindowsHookW proto _CType \
	   nFilterType: SINT,
	 pfnFilterProc: HOOKPROC
ifdef _UNICODE
SetWindowsHook		equ <SetWindowsHookW>
else
SetWindowsHook		equ <SetWindowsHookA>
endif ;; NOT UNICODE

endif ;; NOT STRICT

;BOOL
UnhookWindowsHook proto _CType \
		 nCode: SINT,
	 pfnFilterProc: HOOKPROC

;HHOOK
SetWindowsHookExA proto _CType \
		idHook: SINT,
		  lpfn: HOOKPROC,
		  hmod: HINSTANCE,
	    dwThreadId: DWORD
;HHOOK
SetWindowsHookExW proto _CType \
		idHook: SINT,
		  lpfn: HOOKPROC,
		  hmod: HINSTANCE,
	    dwThreadId: DWORD
ifdef _UNICODE
SetWindowsHookEx	equ <SetWindowsHookExW>
else
SetWindowsHookEx	equ <SetWindowsHookExA>
endif ;; NOT UNICODE

;BOOL
UnhookWindowsHookEx proto _CType \
		   hhk: HHOOK

;LRESULT
CallNextHookEx proto _CType \
		   hhk: HHOOK,
		 nCode: SINT,
		wParam: WPARAM,
		lParam: LPARAM

;;
;; Macros for source-level compatibility with old functions.
;;
ifdef STRICT
DefHookProc macro nCode, wParam, lParam, phhk
	exitm<CallNextHookEx(phhk, nCode, wParam, lParam)>
	endm

else
DefHookProc macro nCode, wParam, lParam, phhk
	exitm<CallNextHookEx(phhk, nCode, wParam, lParam)>
	endm

endif ;; STRICT

endif ;; NOT NOWH

ifndef NOMENUS

;; begin_r_winuser

;; ;win40  -- A lot of MF_* flags have been renamed as MFT_* and MFS_* flags
;;
;; Menu flags for Add/Check/EnableMenuItem()
;;
MF_INSERT		equ 0x00000000
MF_CHANGE		equ 0x00000080
MF_APPEND		equ 0x00000100
MF_DELETE		equ 0x00000200
MF_REMOVE		equ 0x00001000

MF_BYCOMMAND		equ 0x00000000
MF_BYPOSITION		equ 0x00000400

MF_SEPARATOR		equ 0x00000800

MF_ENABLED		equ 0x00000000
MF_GRAYED		equ 0x00000001
MF_DISABLED		equ 0x00000002

MF_UNCHECKED		equ 0x00000000
MF_CHECKED		equ 0x00000008
MF_USECHECKBITMAPS	equ 0x00000200

MF_STRING		equ 0x00000000
MF_BITMAP		equ 0x00000004
MF_OWNERDRAW		equ 0x00000100

MF_POPUP		equ 0x00000010
MF_MENUBARBREAK		equ 0x00000020
MF_MENUBREAK		equ 0x00000040

MF_UNHILITE		equ 0x00000000
MF_HILITE		equ 0x00000080

if(WINVER GE 0x0400)
MF_DEFAULT		equ 0x00001000
endif ;; WINVER GE 0x0400
MF_SYSMENU		equ 0x00002000
MF_HELP			equ 0x00004000
if(WINVER GE 0x0400)
MF_RIGHTJUSTIFY		equ 0x00004000
endif ;; WINVER GE 0x0400

MF_MOUSESELECT		equ 0x00008000
if(WINVER GE 0x0400)
MF_END			equ 0x00000080	;; Obsolete -- only used by old RES files
endif ;; WINVER GE 0x0400


if(WINVER GE 0x0400)
MFT_STRING		equ MF_STRING
MFT_BITMAP		equ MF_BITMAP
MFT_MENUBARBREAK	equ MF_MENUBARBREAK
MFT_MENUBREAK		equ MF_MENUBREAK
MFT_OWNERDRAW		equ MF_OWNERDRAW
MFT_RADIOCHECK		equ 0x00000200
MFT_SEPARATOR		equ MF_SEPARATOR
MFT_RIGHTORDER		equ 0x00002000
MFT_RIGHTJUSTIFY	equ MF_RIGHTJUSTIFY

;; Menu flags for Add/Check/EnableMenuItem()
MFS_GRAYED		equ 0x00000003
MFS_DISABLED		equ MFS_GRAYED
MFS_CHECKED		equ MF_CHECKED
MFS_HILITE		equ MF_HILITE
MFS_ENABLED		equ MF_ENABED
MFS_UNCHECKED		equ MF_UNCHECKED
MFS_UNHILITE		equ MF_UNHILITE
MFS_DEFAULT		equ MF_DEFAULT
if(WINVER GE 0x0500)
MFS_MASK		equ 0x0000108B
MFS_HOTTRACKDRAWN	equ 0x10000000
MFS_CACHEDBMP		equ 0x20000000
MFS_BOTTOMGAPDROP	equ 0x40000000
MFS_TOPGAPDROP		equ 0x80000000
MFS_GAPDROP		equ 0xC0000000
endif ;; WINVER GE 0x0500

endif ;; WINVER GE 0x0400

;; end_r_winuser

if(WINVER GE 0x0400)

;BOOL
CheckMenuRadioItem proto _CType \
		      : HMENU,
		      : UINT,
		      : UINT,
		      : UINT,
		      : UINT
endif ;; WINVER GE 0x0400

;;
;; Menu item resource format
;;
MENUITEMTEMPLATEHEADER	STRUC
versionNumber		dw ?
_offset			dw ?
MENUITEMTEMPLATEHEADER	ENDS
PMENUITEMTEMPLATEHEADER typedef ptr MENUITEMTEMPLATEHEADER

MENUITEMTEMPLATE	STRUC
mtOption		dw ?
mtID			dw ?
mtString		WCHAR ?
MENUITEMTEMPLATE	ENDS
PMENUITEMTEMPLATE	typedef ptr MENUITEMTEMPLATE
MF_END			equ 0x00000080		;; r_winuser

endif ;; NOT NOMENUS

ifndef NOSYSCOMMANDS

;; begin_r_winuser
;;
;; System Menu Command Values
;;
SC_SIZE			equ 0xF000
SC_MOVE			equ 0xF010
SC_MINIMIZE		equ 0xF020
SC_MAXIMIZE		equ 0xF030
SC_NEXTWINDOW		equ 0xF040
SC_PREVWINDOW		equ 0xF050
SC_CLOSE		equ 0xF060
SC_VSCROLL		equ 0xF070
SC_HSCROLL		equ 0xF080
SC_MOUSEMENU		equ 0xF090
SC_KEYMENU		equ 0xF100
SC_ARRANGE		equ 0xF110
SC_RESTORE		equ 0xF120
SC_TASKLIST		equ 0xF130
SC_SCREENSAVE		equ 0xF140
SC_HOTKEY		equ 0xF150
if(WINVER GE 0x0400)
SC_DEFAULT		equ 0xF160
SC_MONITORPOWER		equ 0xF170
SC_CONTEXTHELP		equ 0xF180
SC_SEPARATOR		equ 0xF00F
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0600)
SCF_ISSECURE		equ 0x00000001
endif ;; WINVER GE 0x0600

GET_SC_WPARAM macro wParam
	exitm<(wParam AND 0xFFF0)>
	endm
;;
;; Obsolete names
;;
SC_ICON			equ SC_MINIMIZE
SC_ZOOM			equ SC_MAXIMIZE

;; end_r_winuser
endif ;; NOT NOSYSCOMMANDS

;;
;; Resource Loading Routines
;;

;HBITMAP
LoadBitmapA proto _CType \
	     hInstance: HINSTANCE,
	  lpBitmapName: LPCSTR
;HBITMAP
LoadBitmapW proto _CType \
	     hInstance: HINSTANCE,
	  lpBitmapName: LPCWSTR
ifdef _UNICODE
LoadBitmap		equ <LoadBitmapW>
else
LoadBitmap		equ <LoadBitmapA>
endif ;; NOT UNICODE

;HCURSOR
LoadCursorA proto _CType \
	     hInstance: HINSTANCE,
	  lpCursorName: LPCSTR
;HCURSOR
LoadCursorW proto _CType \
	     hInstance: HINSTANCE,
	  lpCursorName: LPCWSTR
ifdef _UNICODE
LoadCursor		equ <LoadCursorW>
else
LoadCursor		equ <LoadCursorA>
endif ;; NOT UNICODE

;HCURSOR
LoadCursorFromFileA proto _CType \
	    lpFileName: LPCSTR
;HCURSOR
LoadCursorFromFileW proto _CType \
	    lpFileName: LPCWSTR
ifdef _UNICODE
LoadCursorFromFile	equ <LoadCursorFromFileW>
else
LoadCursorFromFile	equ <LoadCursorFromFileA>
endif ;; NOT UNICODE

;HCURSOR
CreateCursor proto _CType \
		 hInst: HINSTANCE,
	      xHotSpot: SINT,
	      yHotSpot: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	    pvANDPlane: PVOID,
	    pvXORPlane: PVOID

;BOOL
DestroyCursor proto _CType \
	       hCursor: HCURSOR

ifndef _MAC
CopyCursor macro pcur
	exitm<CopyIcon(pcur)>
	endm
else
;HCURSOR
CopyCursor proto _CType \
	       hCursor: HCURSOR
endif

;;
;; Standard Cursor IDs
;;
IDC_ARROW		equ MAKEINTRESOURCE(32512)
IDC_IBEAM		equ MAKEINTRESOURCE(32513)
IDC_WAIT		equ MAKEINTRESOURCE(32514)
IDC_CROSS		equ MAKEINTRESOURCE(32515)
IDC_UPARROW		equ MAKEINTRESOURCE(32516)
IDC_SIZE		equ MAKEINTRESOURCE(32640) ;; OBSOLETE: use IDC_SIZEALL
IDC_ICON		equ MAKEINTRESOURCE(32641) ;; OBSOLETE: use IDC_ARROW
IDC_SIZENWSE		equ MAKEINTRESOURCE(32642)
IDC_SIZENESW		equ MAKEINTRESOURCE(32643)
IDC_SIZEWE		equ MAKEINTRESOURCE(32644)
IDC_SIZENS		equ MAKEINTRESOURCE(32645)
IDC_SIZEALL		equ MAKEINTRESOURCE(32646)
IDC_NO			equ MAKEINTRESOURCE(32648) ;; not in win3.1
if(WINVER GE 0x0500)
IDC_HAND		equ MAKEINTRESOURCE(32649)
endif ;; WINVER GE 0x0500
IDC_APPSTARTING		equ MAKEINTRESOURCE(32650) ;; not in win3.1
if(WINVER GE 0x0400)
IDC_HELP		equ MAKEINTRESOURCE(32651)
endif ;; WINVER GE 0x0400

;BOOL
SetSystemCursor proto _CType \
		  hcur: HCURSOR,
		    id: DWORD

ICONINFO		STRUC
fIcon			BOOL ?
xHotspot		dd ?
yHotspot		dd ?
hbmMask			HBITMAP ?
hbmColor		HBITMAP ?
ICONINFO		ENDS
PICONINFO		typedef ptr ICONINFO

;HICON
LoadIconA proto _CType \
	     hInstance: HINSTANCE,
	    lpIconName: LPCSTR
;HICON
LoadIconW proto _CType \
	     hInstance: HINSTANCE,
	    lpIconName: LPCWSTR
ifdef _UNICODE
LoadIcon		equ <LoadIconW>
else
LoadIcon		equ <LoadIconA>
endif ;; NOT UNICODE


;HICON
CreateIcon proto _CType \
	     hInstance: HINSTANCE,
		nWidth: SINT,
	       nHeight: SINT,
	       cPlanes: BYTE,
	    cBitsPixel: BYTE,
	    lpbANDbits: PBYTE,
	    lpbXORbits: PBYTE

;BOOL
DestroyIcon proto _CType \
		 hIcon: HICON

;int
LookupIconIdFromDirectory proto _CType \
	      presbits: PBYTE,
		 fIcon: BOOL

if(WINVER GE 0x0400)
;int
LookupIconIdFromDirectoryEx proto _CType \
	      presbits: PBYTE,
		 fIcon: BOOL,
	     cxDesired: SINT,
	     cyDesired: SINT,
		 Flags: UINT
endif ;; WINVER GE 0x0400

;HICON
CreateIconFromResource proto _CType \
	      presbits: PBYTE,
	     dwResSize: DWORD,
		 fIcon: BOOL,
		 dwVer: DWORD

if(WINVER GE 0x0400)
;HICON
CreateIconFromResourceEx proto _CType \
	      presbits: PBYTE,
	     dwResSize: DWORD,
		 fIcon: BOOL,
		 dwVer: DWORD,
	     cxDesired: SINT,
	     cyDesired: SINT,
		 Flags: UINT

;; Icon/Cursor header
CURSORSHAPE		STRUC
xHotSpot		SINT ?
yHotSpot		SINT ?
_cx			SINT ?
cy			SINT ?
cbWidth			SINT ?
Planes			db ?
BitsPixel		db ?
CURSORSHAPE		ENDS
LPCURSORSHAPE		typedef ptr CURSORSHAPE
endif ;; WINVER GE 0x0400

IMAGE_BITMAP		equ 0
IMAGE_ICON		equ 1
IMAGE_CURSOR		equ 2
if(WINVER GE 0x0400)
IMAGE_ENHMETAFILE	equ 3

LR_DEFAULTCOLOR		equ 0x0000
LR_MONOCHROME		equ 0x0001
LR_COLOR		equ 0x0002
LR_COPYRETURNORG	equ 0x0004
LR_COPYDELETEORG	equ 0x0008
LR_LOADFROMFILE		equ 0x0010
LR_LOADTRANSPARENT	equ 0x0020
LR_DEFAULTSIZE		equ 0x0040
LR_VGACOLOR		equ 0x0080
LR_LOADMAP3DCOLORS	equ 0x1000
LR_CREATEDIBSECTION	equ 0x2000
LR_COPYFROMRESOURCE	equ 0x4000
LR_SHARED		equ 0x8000

;HANDLE
LoadImageA proto _CType \
		      : HINSTANCE,
		      : LPCSTR,
		      : UINT,
		      : SINT,
		      : SINT,
		      : UINT
;HANDLE
LoadImageW proto _CType \
		      : HINSTANCE,
		      : LPCWSTR,
		      : UINT,
		      : SINT,
		      : SINT,
		      : UINT
ifdef _UNICODE
LoadImage		equ <LoadImageW>
else
LoadImage		equ <LoadImageA>
endif ;; NOT UNICODE

;HANDLE
CopyImage proto _CType \
		      : HANDLE,
		      : UINT,
		      : SINT,
		      : SINT,
		      : UINT

DI_MASK			equ 0x0001
DI_IMAGE		equ 0x0002
DI_NORMAL		equ 0x0003
DI_COMPAT		equ 0x0004
DI_DEFAULTSIZE		equ 0x0008
if(_WIN32_WINNT GE 0x0501)
DI_NOMIRROR		equ 0x0010
endif ;; _WIN32_WINNT GE 0x0501

;BOOL
DrawIconEx proto _CType \
		   hdc: HDC,
		 xLeft: SINT,
		  yTop: SINT,
		 hIcon: HICON,
	       cxWidth: SINT,
	       cyWidth: SINT,
	 istepIfAniCur: UINT,
    hbrFlickerFreeDraw: HBRUSH,
	       diFlags: UINT
endif ;; WINVER GE 0x0400

;HICON
CreateIconIndirect proto _CType \
	     piconinfo: PICONINFO

;HICON
CopyIcon proto _CType \
		 hIcon: HICON

;BOOL
GetIconInfo proto _CType \
		 hIcon: HICON,
	     piconinfo: PICONINFO

if(_WIN32_WINNT GE 0x0600)
ICONINFOEXA		STRUC
cbSize			dd ?
fIcon			BOOL ?
xHotspot		dd ?
yHotspot		dd ?
hbmMask			HBITMAP ?
hbmColor		HBITMAP ?
wResID			dw ?
szModName		db MAX_PATH dup(?)
szResName		db MAX_PATH dup(?)
ICONINFOEXA		ENDS
PICONINFOEXA		typedef ptr ICONINFOEXA
ICONINFOEXW		STRUC
cbSize			dd ?
fIcon			BOOL ?
xHotspot		dd ?
yHotspot		dd ?
hbmMask			HBITMAP ?
hbmColor		HBITMAP ?
wResID			dw ?
szModName		dw MAX_PATH dup(?)
szResName		dw MAX_PATH dup(?)
ICONINFOEXW		ENDS
PICONINFOEXW		typedef ptr ICONINFOEXW
ifdef _UNICODE
ICONINFOEX		typedef ICONINFOEXW
PICONINFOEX		typedef PICONINFOEXW
else
ICONINFOEX		typedef ICONINFOEXA
PICONINFOEX		typedef PICONINFOEXA
endif ;; UNICODE
;BOOL
GetIconInfoExA proto _CType \
		 hicon: HICON,
	     piconinfo: PICONINFOEXA
GetIconInfoExW proto _CType \
		 hicon: HICON,
	     piconinfo: PICONINFOEXW
ifdef _UNICODE
GetIconInfoEx		equ <GetIconInfoExW>
else
GetIconInfoEx		equ <GetIconInfoExA>
endif ;; NOT UNICODE
endif ;; _WIN32_WINNT GE 0x0600

if(WINVER GE 0x0400)
RES_ICON		equ 1
RES_CURSOR		equ 2
endif ;; WINVER GE 0x0400

ifdef OEMRESOURCE

;; begin_r_winuser

;;
;; OEM Resource Ordinal Numbers
;;
OBM_CLOSE		equ 32754
OBM_UPARROW		equ 32753
OBM_DNARROW		equ 32752
OBM_RGARROW		equ 32751
OBM_LFARROW		equ 32750
OBM_REDUCE		equ 32749
OBM_ZOOM		equ 32748
OBM_RESTORE		equ 32747
OBM_REDUCED		equ 32746
OBM_ZOOMD		equ 32745
OBM_RESTORED		equ 32744
OBM_UPARROWD		equ 32743
OBM_DNARROWD		equ 32742
OBM_RGARROWD		equ 32741
OBM_LFARROWD		equ 32740
OBM_MNARROW		equ 32739
OBM_COMBO		equ 32738
OBM_UPARROWI		equ 32737
OBM_DNARROWI		equ 32736
OBM_RGARROWI		equ 32735
OBM_LFARROWI		equ 32734

OBM_OLD_CLOSE		equ 32767
OBM_SIZE		equ 32766
OBM_OLD_UPARROW		equ 32765
OBM_OLD_DNARROW		equ 32764
OBM_OLD_RGARROW		equ 32763
OBM_OLD_LFARROW		equ 32762
OBM_BTSIZE		equ 32761
OBM_CHECK		equ 32760
OBM_CHECKBOXES		equ 32759
OBM_BTNCORNERS		equ 32758
OBM_OLD_REDUCE		equ 32757
OBM_OLD_ZOOM		equ 32756
OBM_OLD_RESTORE		equ 32755


OCR_NORMAL		equ 32512
OCR_IBEAM		equ 32513
OCR_WAIT		equ 32514
OCR_CROSS		equ 32515
OCR_UP			equ 32516
OCR_SIZE		equ 32640   ;; OBSOLETE: use OCR_SIZEALL
OCR_ICON		equ 32641   ;; OBSOLETE: use OCR_NORMA
OCR_SIZENWSE		equ 32642
OCR_SIZENESW		equ 32643
OCR_SIZEWE		equ 32644
OCR_SIZENS		equ 32645
OCR_SIZEALL		equ 32646
OCR_ICOCUR		equ 32647   ;; OBSOLETE: use OIC_WINLOGO
OCR_NO			equ 32648
if(WINVER GE 0x0500)
OCR_HAND		equ 32649
endif ;; WINVER GE 0x0500
if(WINVER GE 0x0400)
OCR_APPSTARTING		equ 32650
endif ;; WINVER GE 0x0400

OIC_SAMPLE		equ 32512
OIC_HAND		equ 32513
OIC_QUES		equ 32514
OIC_BANG		equ 32515
OIC_NOTE		equ 32516
if(WINVER GE 0x0400)
OIC_WINLOGO		equ 32517
OIC_WARNING		equ OIC_BANG
OIC_ERROR		equ OIC_HAND
OIC_INFORMATION		equ OIC_NOTE
endif ;; WINVER GE 0x0400


;; end_r_winuser

endif ;; OEMRESOURCE

ORD_LANGDRIVER		equ 1	  ;; The ordinal number for the entry point of
;;* language drivers.
;;

ifndef NOICONS

;; begin_r_winuser
;;
;; Standard Icon IDs
;;
ifdef RC_INVOKED
IDI_APPLICATION		equ 32512
IDI_HAND		equ 32513
IDI_QUESTION		equ 32514
IDI_EXCLAMATION		equ 32515
IDI_ASTERISK		equ 32516
if(WINVER GE 0x0400)
IDI_WINLOGO		equ 32517
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0600)
IDI_SHIELD		equ 32518
endif ;; WINVER GE 0x0600
else ;; RC_INVOKED
IDI_APPLICATION		equ MAKEINTRESOURCE(32512)
IDI_HAND		equ MAKEINTRESOURCE(32513)
IDI_QUESTION		equ MAKEINTRESOURCE(32514)
IDI_EXCLAMATION		equ MAKEINTRESOURCE(32515)
IDI_ASTERISK		equ MAKEINTRESOURCE(32516)
if(WINVER GE 0x0400)
IDI_WINLOGO		equ MAKEINTRESOURCE(32517)
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0600)
IDI_SHIELD		equ MAKEINTRESOURCE(32518)
endif ;; WINVER GE 0x0600
endif ;; RC_INVOKED

if(WINVER GE 0x0400)
IDI_WARNING		equ IDI_EXCAMATION
IDI_ERROR		equ IDI_HAND
IDI_INFORMATION		equ IDI_ASTERISK
endif ;; WINVER GE 0x0400

;; end_r_winuser

endif ;; NOT NOICONS

;int
LoadStringA proto _CType \
	     hInstance: HINSTANCE,
		   uID: UINT,
	      lpBuffer: LPSTR,
	    nBufferMax: SINT
;int
LoadStringW proto _CType \
	     hInstance: HINSTANCE,
		   uID: UINT,
	      lpBuffer: LPWSTR,
	    nBufferMax: SINT
ifdef _UNICODE
LoadString		equ <LoadStringW>
else
LoadString		equ <LoadStringA>
endif ;; NOT UNICODE

;; begin_r_winuser

;;
;; Dialog Box Command IDs
;;
IDOK			equ 1
IDCANCEL		equ 2
IDABORT			equ 3
IDRETRY			equ 4
IDIGNORE		equ 5
IDYES			equ 6
IDNO			equ 7
if(WINVER GE 0x0400)
IDCLOSE			equ 8
IDHELP			equ 9
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0500)
IDTRYAGAIN		equ 10
IDCONTINUE		equ 11
endif ;; WINVER GE 0x0500
if(WINVER GE 0x0501)
ifndef IDTIMEOUT
IDTIMEOUT		equ 32000
endif
endif ;; WINVER GE 0x0501

;; end_r_winuser

ifndef NOCTLMGR

;;
;; Control Manager Structures and Definitions
;;

ifndef NOWINSTYLES

;; begin_r_winuser

;;
;; Edit Control Styles
;;
ES_LEFT			equ 0x0000
ES_CENTER		equ 0x0001
ES_RIGHT		equ 0x0002
ES_MULTILINE		equ 0x0004
ES_UPPERCASE		equ 0x0008
ES_LOWERCASE		equ 0x0010
ES_PASSWORD		equ 0x0020
ES_AUTOVSCROLL		equ 0x0040
ES_AUTOHSCROLL		equ 0x0080
ES_NOHIDESEL		equ 0x0100
ES_OEMCONVERT		equ 0x0400
ES_READONLY		equ 0x0800
ES_WANTRETURN		equ 0x1000
if(WINVER GE 0x0400)
ES_NUMBER		equ 0x2000
endif ;; WINVER GE 0x0400

;; end_r_winuser

endif ;; NOT NOWINSTYLES

;;
;; Edit Control Notification Codes
;;
EN_SETFOCUS		equ 0x0100
EN_KILLFOCUS		equ 0x0200
EN_CHANGE		equ 0x0300
EN_UPDATE		equ 0x0400
EN_ERRSPACE		equ 0x0500
EN_MAXTEXT		equ 0x0501
EN_HSCROLL		equ 0x0601
EN_VSCROLL		equ 0x0602

if(_WIN32_WINNT GE 0x0500)
EN_ALIGN_LTR_EC		equ 0x0700
EN_ALIGN_RTL_EC		equ 0x0701
endif ;; _WIN32_WINNT GE 0x0500

if(WINVER GE 0x0400)
;; Edit control EM_SETMARGIN parameters
EC_LEFTMARGIN		equ 0x0001
EC_RIGHTMARGIN		equ 0x0002
EC_USEFONTINFO		equ 0xffff
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0500)
;; wParam of EM_GET/SETIMESTATUS
EMSIS_COMPOSITIONSTRING equ 0x0001

;; lParam for EMSIS_COMPOSITIONSTRING
EIMES_GETCOMPSTRATONCE	equ 0x0001
EIMES_CANCELCOMPSTRINFOCUS equ 0x0002
EIMES_COMPLETECOMPSTRKILLFOCUS equ 0x0004
endif ;; WINVER GE 0x0500

ifndef NOWINMESSAGES

;; begin_r_winuser

;;
;; Edit Control Messages
;;
EM_GETSEL		equ 0x00B0
EM_SETSEL		equ 0x00B1
EM_GETRECT		equ 0x00B2
EM_SETRECT		equ 0x00B3
EM_SETRECTNP		equ 0x00B4
EM_SCROLL		equ 0x00B5
EM_LINESCROLL		equ 0x00B6
EM_SCROLLCARET		equ 0x00B7
EM_GETMODIFY		equ 0x00B8
EM_SETMODIFY		equ 0x00B9
EM_GETLINECOUNT		equ 0x00BA
EM_LINEINDEX		equ 0x00BB
EM_SETHANDLE		equ 0x00BC
EM_GETHANDLE		equ 0x00BD
EM_GETTHUMB		equ 0x00BE
EM_LINELENGTH		equ 0x00C1
EM_REPLACESEL		equ 0x00C2
EM_GETLINE		equ 0x00C4
EM_LIMITTEXT		equ 0x00C5
EM_CANUNDO		equ 0x00C6
EM_UNDO			equ 0x00C7
EM_FMTLINES		equ 0x00C8
EM_LINEFROMCHAR		equ 0x00C9
EM_SETTABSTOPS		equ 0x00CB
EM_SETPASSWORDCHAR	equ 0x00CC
EM_EMPTYUNDOBUFFER	equ 0x00CD
EM_GETFIRSTVISIBLELINE	equ 0x00CE
EM_SETREADONLY		equ 0x00CF
EM_SETWORDBREAKPROC	equ 0x00D0
EM_GETWORDBREAKPROC	equ 0x00D1
EM_GETPASSWORDCHAR	equ 0x00D2
if(WINVER GE 0x0400)
EM_SETMARGINS		equ 0x00D3
EM_GETMARGINS		equ 0x00D4
EM_SETLIMITTEXT		equ EM_LIMITTEXT   ;; ;win40 Name change
EM_GETLIMITTEXT		equ 0x00D5
EM_POSFROMCHAR		equ 0x00D6
EM_CHARFROMPOS		equ 0x00D7
endif ;; WINVER GE 0x0400

if(WINVER GE 0x0500)
EM_SETIMESTATUS		equ 0x00D8
EM_GETIMESTATUS		equ 0x00D9
endif ;; WINVER GE 0x0500


;; end_r_winuser
endif ;; NOT NOWINMESSAGES

;;
;; EDITWORDBREAKPROC code values
;;
WB_LEFT			equ 0
WB_RIGHT		equ 1
WB_ISDELIMITER		equ 2

;; begin_r_winuser

;;
;; Button Control Styles
;;
BS_PUSHBUTTON		equ 0x00000000
BS_DEFPUSHBUTTON	equ 0x00000001
BS_CHECKBOX		equ 0x00000002
BS_AUTOCHECKBOX		equ 0x00000003
BS_RADIOBUTTON		equ 0x00000004
BS_3STATE		equ 0x00000005
BS_AUTO3STATE		equ 0x00000006
BS_GROUPBOX		equ 0x00000007
BS_USERBUTTON		equ 0x00000008
BS_AUTORADIOBUTTON	equ 0x00000009
BS_OWNERDRAW		equ 0x0000000B
BS_LEFTTEXT		equ 0x00000020
if(WINVER GE 0x0400)
BS_TEXT			equ 0x00000000
BS_ICON			equ 0x00000040
BS_BITMAP		equ 0x00000080
BS_LEFT			equ 0x00000100
BS_RIGHT		equ 0x00000200
BS_CENTER		equ 0x00000300
BS_TOP			equ 0x00000400
BS_BOTTOM		equ 0x00000800
BS_VCENTER		equ 0x00000C00
BS_PUSHLIKE		equ 0x00001000
BS_MULTILINE		equ 0x00002000
BS_NOTIFY		equ 0x00004000
BS_FLAT			equ 0x00008000
BS_RIGHTBUTTON		equ BS_LEFTTEXT
endif ;; WINVER GE 0x0400

;;
;; User Button Notification Codes
;;
BN_CLICKED		equ 0
BN_PAINT		equ 1
BN_HILITE		equ 2
BN_UNHILITE		equ 3
BN_DISABLE		equ 4
BN_DOUBLECLICKED	equ 5
if(WINVER GE 0x0400)
BN_PUSHED		equ BN_HILITE
BN_UNPUSHED		equ BN_UNHILITE
BN_DBLCLK		equ BN_DOUBLECICKED
BN_SETFOCUS		equ 6
BN_KILLFOCUS		equ 7
endif ;; WINVER GE 0x0400

;;
;; Button Control Messages
;;
BM_GETCHECK		equ 0x00F0
BM_SETCHECK		equ 0x00F1
BM_GETSTATE		equ 0x00F2
BM_SETSTATE		equ 0x00F3
BM_SETSTYLE		equ 0x00F4
if(WINVER GE 0x0400)
BM_CLICK		equ 0x00F5
BM_GETIMAGE		equ 0x00F6
BM_SETIMAGE		equ 0x00F7
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0600)
BM_SETDONTCLICK		equ 0x00F8
endif ;; WINVER GE 0x0600
if(WINVER GE 0x0400)
BST_UNCHECKED		equ 0x0000
BST_CHECKED		equ 0x0001
BST_INDETERMINATE	equ 0x0002
BST_PUSHED		equ 0x0004
BST_FOCUS		equ 0x0008
endif ;; WINVER GE 0x0400

;;
;; Static Control Constants
;;
SS_LEFT			equ 0x00000000
SS_CENTER		equ 0x00000001
SS_RIGHT		equ 0x00000002
SS_ICON			equ 0x00000003
SS_BLACKRECT		equ 0x00000004
SS_GRAYRECT		equ 0x00000005
SS_WHITERECT		equ 0x00000006
SS_BLACKFRAME		equ 0x00000007
SS_GRAYFRAME		equ 0x00000008
SS_WHITEFRAME		equ 0x00000009
SS_USERITEM		equ 0x0000000A
SS_SIMPLE		equ 0x0000000B
SS_LEFTNOWORDWRAP	equ 0x0000000C
if(WINVER GE 0x0400)
SS_OWNERDRAW		equ 0x0000000D
SS_BITMAP		equ 0x0000000E
SS_ENHMETAFILE		equ 0x0000000F
SS_ETCHEDHORZ		equ 0x00000010
SS_ETCHEDVERT		equ 0x00000011
SS_ETCHEDFRAME		equ 0x00000012
SS_TYPEMASK		equ 0x0000001F
endif ;; WINVER GE 0x0400
if(WINVER GE 0x0501)
SS_REALSIZECONTROL	equ 0x00000040
endif ;; WINVER GE 0x0501
SS_NOPREFIX		equ 0x00000080 ;; Don't do " AND " character translation
if(WINVER GE 0x0400)
SS_NOTIFY		equ 0x00000100
SS_CENTERIMAGE		equ 0x00000200
SS_RIGHTJUST		equ 0x00000400
SS_REALSIZEIMAGE	equ 0x00000800
SS_SUNKEN		equ 0x00001000
SS_ENDELLIPSIS		equ 0x00004000
SS_PATHELLIPSIS		equ 0x00008000
SS_WORDELLIPSIS		equ 0x0000C000
SS_ELLIPSISMASK		equ 0x0000C000
endif ;; WINVER GE 0x0400

;; end_r_winuser

ifndef NOWINMESSAGES
;;
;; Static Control Mesages
;;
STM_SETICON		equ 0x0170
STM_GETICON		equ 0x0171
if(WINVER GE 0x0400)
STM_SETIMAGE		equ 0x0172
STM_GETIMAGE		equ 0x0173
STN_CLICKED		equ 0
STN_DBLCLK		equ 1
STN_ENABLE		equ 2
STN_DISABLE		equ 3
endif ;; WINVER GE 0x0400
STM_MSGMAX		equ 0x0174
endif ;; NOT NOWINMESSAGES

;;
;; Dialog window class
;;
WC_DIALOG		equ (MAKEINTATOM(0x8002))

;;
;; Get/SetWindowWord/Long offsets for use with WC_DIALOG windows
;;
DWL_MSGRESULT		equ 0
DWL_DLGPROC		equ 4
DWL_USER		equ 8

;;
;; Dialog Manager Routines
;;

ifndef NOMSG

;BOOL
IsDialogMessageA proto _CType \
		  hDlg: HWND,
		 lpMsg: LPMSG
;BOOL
IsDialogMessageW proto _CType \
		  hDlg: HWND,
		 lpMsg: LPMSG
ifdef _UNICODE
IsDialogMessage		equ <IsDialogMessageW>
else
IsDialogMessage		equ <IsDialogMessageA>
endif ;; NOT UNICODE

endif ;; NOT NOMSG

;BOOL
MapDialogRect proto _CType \
		  hDlg: HWND,
		lpRect: LPRECT

;int
DlgDirListA proto _CType \
		  hDlg: HWND,
	    lpPathSpec: LPSTR,
	    nIDListBox: SINT,
	 nIDStaticPath: SINT,
	     uFileType: UINT
;int
DlgDirListW proto _CType \
		  hDlg: HWND,
	    lpPathSpec: LPWSTR,
	    nIDListBox: SINT,
	 nIDStaticPath: SINT,
	     uFileType: UINT
ifdef _UNICODE
DlgDirList		equ <DlgDirListW>
else
DlgDirList		equ <DlgDirListA>
endif ;; NOT UNICODE

;;
;; DlgDirList, DlgDirListComboBox flags values
;;
DDL_READWRITE		equ 0x0000
DDL_READONLY		equ 0x0001
DDL_HIDDEN		equ 0x0002
DDL_SYSTEM		equ 0x0004
DDL_DIRECTORY		equ 0x0010
DDL_ARCHIVE		equ 0x0020

DDL_POSTMSGS		equ 0x2000
DDL_DRIVES		equ 0x4000
DDL_EXCLUSIVE		equ 0x8000

;BOOL
DlgDirSelectExA proto _CType \
		  hDlg: HWND,
	      lpString: LPSTR,
		nCount: SINT,
	    nIDListBox: SINT
;BOOL
DlgDirSelectExW proto _CType \
		  hDlg: HWND,
	      lpString: LPWSTR,
		nCount: SINT,
	    nIDListBox: SINT
ifdef _UNICODE
DlgDirSelectEx		equ <DlgDirSelectExW>
else
DlgDirSelectEx		equ <DlgDirSelectExA>
endif ;; NOT UNICODE

;int
DlgDirListComboBoxA proto _CType \
		  hDlg: HWND,
	    lpPathSpec: LPSTR,
	   nIDComboBox: SINT,
	 nIDStaticPath: SINT,
	     uFiletype: UINT
;int
DlgDirListComboBoxW proto _CType \
		  hDlg: HWND,
	    lpPathSpec: LPWSTR,
	   nIDComboBox: SINT,
	 nIDStaticPath: SINT,
	     uFiletype: UINT
ifdef _UNICODE
DlgDirListComboBox	equ <DlgDirListComboBoxW>
else
DlgDirListComboBox	equ <DlgDirListComboBoxA>
endif ;; NOT UNICODE

;BOOL
DlgDirSelectComboBoxExA proto _CType \
		  hDlg: HWND,
	      lpString: LPSTR,
		nCount: SINT,
	   nIDComboBox: SINT
;BOOL
DlgDirSelectComboBoxExW proto _CType \
		  hDlg: HWND,
	      lpString: LPWSTR,
		nCount: SINT,
	   nIDComboBox: SINT
ifdef _UNICODE
DlgDirSelectComboBoxEx	equ <DlgDirSelectComboBoxExW>
else
DlgDirSelectComboBoxEx	equ <DlgDirSelectComboBoxExA>
endif ;; NOT UNICODE


;; begin_r_winuser

;;
;; Dialog Styles
;;
DS_ABSALIGN		equ 0x01
DS_SYSMODAL		equ 0x02
DS_LOCALEDIT		equ 0x20   ;; Edit items get Local storage.
DS_SETFONT		equ 0x40   ;; User specified font for Dlg controls
DS_MODALFRAME		equ 0x80   ;; Can be combined with WS_CAPTION
DS_NOIDLEMSG		equ 0x100  ;; WM_ENTERIDE message will not be sent
DS_SETFOREGROUND	equ 0x200  ;; not in win3.1


if(WINVER GE 0x0400)
DS_3DLOOK		equ 0x0004
DS_FIXEDSYS		equ 0x0008
DS_NOFAILCREATE		equ 0x0010
DS_CONTROL		equ 0x0400
DS_CENTER		equ 0x0800
DS_CENTERMOUSE		equ 0x1000
DS_CONTEXTHELP		equ 0x2000
DS_SHELLFONT		equ (DS_SETFONT OR DS_FIXEDSYS)
endif ;; WINVER GE 0x0400

;; end_r_winuser

DM_GETDEFID		equ (WM_USER+0)
DM_SETDEFID		equ (WM_USER+1)

if(WINVER GE 0x0400)
DM_REPOSITION		equ (WM_USER+2)
endif ;; WINVER GE 0x0400
;;
;; Returned in HIWORD() of DM_GETDEFID result if msg is supported
;;
DC_HASDEFID		equ 0x534B

;;
;; Dialog Codes
;;
DLGC_WANTARROWS		equ 0x0001 ;; Control wants arrow keys
DLGC_WANTTAB		equ 0x0002 ;; Control wants tab keys
DLGC_WANTALLKEYS	equ 0x0004 ;; Control wants all keys
DLGC_WANTMESSAGE	equ 0x0004 ;; Pass message to control
DLGC_HASSETSEL		equ 0x0008 ;; Understands EM_SETSE message
DLGC_DEFPUSHBUTTON	equ 0x0010 ;; Default pushbutton
DLGC_UNDEFPUSHBUTTON	equ 0x0020 ;; Non-default pushbutton
DLGC_RADIOBUTTON	equ 0x0040 ;; Radio button
DLGC_WANTCHARS		equ 0x0080 ;; Want WM_CHAR messages
DLGC_STATIC		equ 0x0100 ;; Static item: don't include
DLGC_BUTTON		equ 0x2000 ;; Button item: can be checked

LB_CTLCODE		equ 0

;;
;; Listbox Return Values
;;
LB_OKAY			equ 0
LB_ERR			equ (-1)
LB_ERRSPACE		equ (-2)

;;
;;*  The idStaticPath parameter to DlgDirList can have the following values
;;*  ORed if the list box should show other details of the files along with
;;*  the name of the files;
;;
;; all other details also will be returned


;;
;; Listbox Notification Codes
;;
LBN_ERRSPACE		equ (-2)
LBN_SELCHANGE		equ 1
LBN_DBLCLK		equ 2
LBN_SELCANCEL		equ 3
LBN_SETFOCUS		equ 4
LBN_KILLFOCUS		equ 5



ifndef NOWINMESSAGES

;;
;; Listbox messages
;;
LB_ADDSTRING		equ 0x0180
LB_INSERTSTRING		equ 0x0181
LB_DELETESTRING		equ 0x0182
LB_SELITEMRANGEEX	equ 0x0183
LB_RESETCONTENT		equ 0x0184
LB_SETSEL		equ 0x0185
LB_SETCURSEL		equ 0x0186
LB_GETSEL		equ 0x0187
LB_GETCURSEL		equ 0x0188
LB_GETTEXT		equ 0x0189
LB_GETTEXTLEN		equ 0x018A
LB_GETCOUNT		equ 0x018B
LB_SELECTSTRING		equ 0x018C
LB_DIR			equ 0x018D
LB_GETTOPINDEX		equ 0x018E
LB_FINDSTRING		equ 0x018F
LB_GETSELCOUNT		equ 0x0190
LB_GETSELITEMS		equ 0x0191
LB_SETTABSTOPS		equ 0x0192
LB_GETHORIZONTALEXTENT	equ 0x0193
LB_SETHORIZONTALEXTENT	equ 0x0194
LB_SETCOLUMNWIDTH	equ 0x0195
LB_ADDFILE		equ 0x0196
LB_SETTOPINDEX		equ 0x0197
LB_GETITEMRECT		equ 0x0198
LB_GETITEMDATA		equ 0x0199
LB_SETITEMDATA		equ 0x019A
LB_SELITEMRANGE		equ 0x019B
LB_SETANCHORINDEX	equ 0x019C
LB_GETANCHORINDEX	equ 0x019D
LB_SETCARETINDEX	equ 0x019E
LB_GETCARETINDEX	equ 0x019F
LB_SETITEMHEIGHT	equ 0x01A0
LB_GETITEMHEIGHT	equ 0x01A1
LB_FINDSTRINGEXACT	equ 0x01A2
LB_SETLOCALE		equ 0x01A5
LB_GETLOCALE		equ 0x01A6
LB_SETCOUNT		equ 0x01A7
if(WINVER GE 0x0400)
LB_INITSTORAGE		equ 0x01A8
LB_ITEMFROMPOINT	equ 0x01A9
endif ;; WINVER GE 0x0400

if(_WIN32_WINNT GE 0x0501)
LB_GETLISTBOXINFO	equ 0x01B2
endif ;; _WIN32_WINNT GE 0x0501
if(_WIN32_WINNT GE 0x0501)
LB_MSGMAX		equ 0x01B3
elseif(_WIN32_WCE GE 0x0400)
LB_MSGMAX		equ 0x01B1
elseif(WINVER GE 0x0400)
LB_MSGMAX		equ 0x01B0
else
LB_MSGMAX		equ 0x01A8
endif

endif ;; NOT NOWINMESSAGES

ifndef NOWINSTYLES

;; begin_r_winuser

;;
;; Listbox Styles
;;
LBS_NOTIFY		equ 0x0001
LBS_SORT		equ 0x0002
LBS_NOREDRAW		equ 0x0004
LBS_MULTIPLESEL		equ 0x0008
LBS_OWNERDRAWFIXED	equ 0x0010
LBS_OWNERDRAWVARIABLE	equ 0x0020
LBS_HASSTRINGS		equ 0x0040
LBS_USETABSTOPS		equ 0x0080
LBS_NOINTEGRALHEIGHT	equ 0x0100
LBS_MULTICOLUMN		equ 0x0200
LBS_WANTKEYBOARDINPUT	equ 0x0400
LBS_EXTENDEDSEL		equ 0x0800
LBS_DISABLENOSCROLL	equ 0x1000
LBS_NODATA		equ 0x2000
if(WINVER GE 0x0400)
LBS_NOSEL		equ 0x4000
endif ;; WINVER GE 0x0400
LBS_STANDARD		equ (LBS_NOTIFY OR LBS_SORT OR WS_VSCROLL OR WS_BORDER)

;; end_r_winuser

endif ;; NOT NOWINSTYLES


;;
;; Combo Box return Values
;;
CB_OKAY			equ 0
CB_ERR			equ (-1)
CB_ERRSPACE		equ (-2)


;;
;; Combo Box Notification Codes
;;
CBN_ERRSPACE		equ (-1)
CBN_SELCHANGE		equ 1
CBN_DBLCLK		equ 2
CBN_SETFOCUS		equ 3
CBN_KILLFOCUS		equ 4
CBN_EDITCHANGE		equ 5
CBN_EDITUPDATE		equ 6
CBN_DROPDOWN		equ 7
CBN_CLOSEUP		equ 8
CBN_SELENDOK		equ 9
CBN_SELENDCANCEL	equ 10

ifndef NOWINSTYLES
;; begin_r_winuser

;;
;; Combo Box styles
;;
CBS_SIMPLE		equ 0x0001
CBS_DROPDOWN		equ 0x0002
CBS_DROPDOWNLIST	equ 0x0003
CBS_OWNERDRAWFIXED	equ 0x0010
CBS_OWNERDRAWVARIABLE	equ 0x0020
CBS_AUTOHSCROLL		equ 0x0040
CBS_OEMCONVERT		equ 0x0080
CBS_SORT		equ 0x0100
CBS_HASSTRINGS		equ 0x0200
CBS_NOINTEGRALHEIGHT	equ 0x0400
CBS_DISABLENOSCROLL	equ 0x0800
if(WINVER GE 0x0400)
CBS_UPPERCASE		equ 0x2000
CBS_LOWERCASE		equ 0x4000
endif ;; WINVER GE 0x0400

;; end_r_winuser
endif  ;; NOT NOWINSTYLES


;;
;; Combo Box messages
;;
ifndef NOWINMESSAGES
CB_GETEDITSEL		equ 0x0140
CB_LIMITTEXT		equ 0x0141
CB_SETEDITSEL		equ 0x0142
CB_ADDSTRING		equ 0x0143
CB_DELETESTRING		equ 0x0144
CB_DIR			equ 0x0145
CB_GETCOUNT		equ 0x0146
CB_GETCURSEL		equ 0x0147
CB_GETLBTEXT		equ 0x0148
CB_GETLBTEXTLEN		equ 0x0149
CB_INSERTSTRING		equ 0x014A
CB_RESETCONTENT		equ 0x014B
CB_FINDSTRING		equ 0x014C
CB_SELECTSTRING		equ 0x014D
CB_SETCURSEL		equ 0x014E
CB_SHOWDROPDOWN		equ 0x014F
CB_GETITEMDATA		equ 0x0150
CB_SETITEMDATA		equ 0x0151
CB_GETDROPPEDCONTROLRECT equ 0x0152
CB_SETITEMHEIGHT	equ 0x0153
CB_GETITEMHEIGHT	equ 0x0154
CB_SETEXTENDEDUI	equ 0x0155
CB_GETEXTENDEDUI	equ 0x0156
CB_GETDROPPEDSTATE	equ 0x0157
CB_FINDSTRINGEXACT	equ 0x0158
CB_SETLOCALE		equ 0x0159
CB_GETLOCALE		equ 0x015A
if(WINVER GE 0x0400)
CB_GETTOPINDEX		equ 0x015b
CB_SETTOPINDEX		equ 0x015c
CB_GETHORIZONTALEXTENT	equ 0x015d
CB_SETHORIZONTALEXTENT	equ 0x015e
CB_GETDROPPEDWIDTH	equ 0x015f
CB_SETDROPPEDWIDTH	equ 0x0160
CB_INITSTORAGE		equ 0x0161
endif ;; WINVER GE 0x0400

if(_WIN32_WINNT GE 0x0501)
CB_GETCOMBOBOXINFO	equ 0x0164
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0501)
CB_MSGMAX		equ 0x0165
elseif(_WIN32_WCE GE 0x0400)
CB_MSGMAX		equ 0x0163
elseif(WINVER GE 0x0400)
CB_MSGMAX		equ 0x0162
else
CB_MSGMAX		equ 0x015B
endif

endif  ;; NOT NOWINMESSAGES


ifndef NOWINSTYLES

;; begin_r_winuser

;;
;; Scroll Bar Styles
;;
SBS_HORZ		equ 0x0000
SBS_VERT		equ 0x0001
SBS_TOPALIGN		equ 0x0002
SBS_LEFTALIGN		equ 0x0002
SBS_BOTTOMALIGN		equ 0x0004
SBS_RIGHTALIGN		equ 0x0004
SBS_SIZEBOXTOPLEFTALIGN equ 0x0002
SBS_SIZEBOXBOTTOMRIGHTALIGN equ 0x0004
SBS_SIZEBOX		equ 0x0008
if(WINVER GE 0x0400)
SBS_SIZEGRIP		equ 0x0010
endif ;; WINVER GE 0x0400

;; end_r_winuser

endif ;; NOT NOWINSTYLES

;;
;; Scroll bar messages
;;
ifndef NOWINMESSAGES
SBM_SETPOS		equ 0x00E0 ;;not in win3.1
SBM_GETPOS		equ 0x00E1 ;;not in win3.1
SBM_SETRANGE		equ 0x00E2 ;;not in win3.1
SBM_SETRANGEREDRAW	equ 0x00E6 ;;not in win3.1
SBM_GETRANGE		equ 0x00E3 ;;not in win3.1
SBM_ENABLE_ARROWS	equ 0x00E4 ;;not in win3.1
if(WINVER GE 0x0400)
SBM_SETSCROLLINFO	equ 0x00E9
SBM_GETSCROLLINFO	equ 0x00EA
endif ;; WINVER GE 0x0400
if(_WIN32_WINNT GE 0x0501)
SBM_GETSCROLLBARINFO	equ 0x00EB
endif ;; _WIN32_WINNT GE 0x0501
if(WINVER GE 0x0400)
SIF_RANGE		equ 0x0001
SIF_PAGE		equ 0x0002
SIF_POS			equ 0x0004
SIF_DISABLENOSCROLL	equ 0x0008
SIF_TRACKPOS		equ 0x0010
SIF_ALL			equ (SIF_RANGE OR SIF_PAGE OR SIF_POS OR SIF_TRACKPOS)

SCROLLINFO		STRUC
cbSize			UINT ?
fMask			UINT ?
nMin			SINT ?
nMax			SINT ?
nPage			UINT ?
nPos			SINT ?
nTrackPos		SINT ?
SCROLLINFO		ENDS
LPSCROLLINFO		typedef ptr SCROLLINFO
LPCSCROLLINFO		typedef ptr SCROLLINFO

;int
SetScrollInfo proto _CType \
		      : HWND,
		      : SINT,
		      : LPCSCROLLINFO,
		      : BOOL
;BOOL
GetScrollInfo proto _CType \
		      : HWND,
		      : SINT,
		      : LPSCROLLINFO
endif ;; WINVER GE 0x0400
endif ;; NOT NOWINMESSAGES
endif ;; NOT NOCTLMGR

ifndef NOMDI

;;
;; MDI client style bits
;;
MDIS_ALLCHILDSTYLES	equ 0x0001

;;
;; wParam Flags for WM_MDITILE and WM_MDICASCADE messages.
;;
MDITILE_VERTICAL	equ 0x0000 ;;not in win3.1
MDITILE_HORIZONTAL	equ 0x0001 ;;not in win3.1
MDITILE_SKIPDISABLED	equ 0x0002 ;;not in win3.1
if(_WIN32_WINNT GE 0x0500)
MDITILE_ZORDER		equ 0x0004
endif ;; _WIN32_WINNT GE 0x0500

MDICREATESTRUCTA	STRUC
szClass			LPCSTR ?
szTitle			LPCSTR ?
hOwner			HANDLE ?
x			SINT ?
y			SINT ?
_cx			SINT ?
cy			SINT ?
style			dd ?
lParam			LPARAM ?	;; app-defined stuff
MDICREATESTRUCTA	ENDS
LPMDICREATESTRUCTA	typedef ptr MDICREATESTRUCTA
MDICREATESTRUCTW	STRUC
szClass			LPCWSTR ?
szTitle			LPCWSTR ?
hOwner			HANDLE ?
x			SINT ?
y			SINT ?
_cx			SINT ?
cy			SINT ?
style			dd ?
lParam			LPARAM ?	;; app-defined stuff
MDICREATESTRUCTW	ENDS
LPMDICREATESTRUCTW	typedef ptr MDICREATESTRUCTW
ifdef _UNICODE
MDICREATESTRUCT		typedef MDICREATESTRUCTW
LPMDICREATESTRUCT	typedef LPMDICREATESTRUCTW
else
MDICREATESTRUCT		typedef MDICREATESTRUCTA
LPMDICREATESTRUCT	typedef LPMDICREATESTRUCTA
endif ;; UNICODE

CLIENTCREATESTRUCT	STRUC
hWindowMenu		HANDLE ?
idFirstChild		UINT ?
CLIENTCREATESTRUCT	ENDS
LPCLIENTCREATESTRUCT	typedef ptr CLIENTCREATESTRUCT

;LRESULT
DefFrameProcA proto _CType \
		  hWnd: HWND,
	 hWndMDIClient: HWND,
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
;LRESULT
DefFrameProcW proto _CType \
		  hWnd: HWND,
	 hWndMDIClient: HWND,
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
DefFrameProc		equ <DefFrameProcW>
else
DefFrameProc		equ <DefFrameProcA>
endif ;; NOT UNICODE

DefMDIChildProcA typedef proto _CType \
		  hWnd: HWND,
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
DefMDIChildProcW typedef proto _CType \
		  hWnd: HWND,
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM
ifdef _UNICODE
DefMDIChildProc typedef ptr DefMDIChildProcW
else
DefMDIChildProc typedef ptr DefMDIChildProcA
endif ;; NOT UNICODE

ifndef NOMSG

;BOOL
TranslateMDISysAccel proto _CType \
	    hWndClient: HWND,
		 lpMsg: LPMSG

endif ;; NOT NOMSG

;UINT
ArrangeIconicWindows proto _CType \
		  hWnd: HWND

;HWND
CreateMDIWindowA proto _CType \
	   lpClassName: LPSTR,
	  lpWindowName: LPSTR,
	       dwStyle: DWORD,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	    hWndParent: HWND,
	     hInstance: HINSTANCE,
	       lParam : LPARAM
;HWND
CreateMDIWindowW proto _CType \
	   lpClassName: LPWSTR,
	  lpWindowName: LPWSTR,
	       dwStyle: DWORD,
		     X: SINT,
		     Y: SINT,
		nWidth: SINT,
	       nHeight: SINT,
	    hWndParent: HWND,
	     hInstance: HINSTANCE,
	       lParam : LPARAM
ifdef _UNICODE
CreateMDIWindow		equ <CreateMDIWindowW>
else
CreateMDIWindow		equ <CreateMDIWindowA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
;WORD
TileWindows proto _CType \
	    hwndParent: HWND,
		  wHow: UINT,
		lpRect: LPRECT,
		 cKids: UINT,
		lpKids: ptr HWND
;WORD
CascadeWindows proto _CType \
	    hwndParent: HWND,
		  wHow: UINT,
		lpRect: LPRECT,
		 cKids: UINT,
		lpKids: ptr HWND
endif ;; WINVER GE 0x0400
endif ;; NOT NOMDI

endif ;; NOT NOUSER

;;***** Help support *******************************************************

ifndef NOHELP

HELPPOLY		typedef DWORD
MULTIKEYHELPA		STRUC
mkSize			dd ?
mkKeylist		CHAR ?
szKeyphrase		CHAR ?
MULTIKEYHELPA		ENDS
PMULTIKEYHELPA		typedef ptr MULTIKEYHELPA
LPMULTIKEYHELPA		typedef ptr MULTIKEYHELPA
MULTIKEYHELPW		STRUC
mkSize			dd ?
mkKeylist		WCHAR ?
szKeyphrase		WCHAR ?
MULTIKEYHELPW		ENDS
PMULTIKEYHELPW		typedef ptr MULTIKEYHELPW
LPMULTIKEYHELPW		typedef ptr MULTIKEYHELPW
ifdef _UNICODE
MULTIKEYHELP		typedef MULTIKEYHELPW
PMULTIKEYHELP		typedef PMULTIKEYHELPW
LPMULTIKEYHELP		typedef LPMULTIKEYHELPW
else
MULTIKEYHELP		typedef MULTIKEYHELPA
PMULTIKEYHELP		typedef PMULTIKEYHELPA
LPMULTIKEYHELP		typedef LPMULTIKEYHELPA
endif ;; UNICODE

HELPWININFOA		STRUC
wStructSize		SINT ?
x			SINT ?
y			SINT ?
_dx			SINT ?
dy			SINT ?
wMax			SINT ?
rgchMember		CHAR 2 dup(?)
HELPWININFOA		ENDS
PHELPWININFOA		typedef ptr HELPWININFOA
LPHELPWININFOA		typedef ptr HELPWININFOA
HELPWININFOW		STRUC
wStructSize		SINT ?
x			SINT ?
y			SINT ?
_dx			SINT ?
dy			SINT ?
wMax			SINT ?
rgchMember		WCHAR 2 dup(?)
HELPWININFOW		ENDS
PHELPWININFOW		typedef ptr HELPWININFOW
LPHELPWININFOW		typedef ptr HELPWININFOW
ifdef _UNICODE
HELPWININFO		typedef HELPWININFOW
PHELPWININFO		typedef PHELPWININFOW
LPHELPWININFO		typedef LPHELPWININFOW
else
HELPWININFO		typedef HELPWININFOA
PHELPWININFO		typedef PHELPWININFOA
LPHELPWININFO		typedef LPHELPWININFOA
endif ;; UNICODE

;; begin_r_winuser

;;
;; Commands to pass to WinHelp()
;;
HELP_CONTEXT		equ 0x0001  ;; Display topic in ulTopic
HELP_QUIT		equ 0x0002  ;; Terminate help
HELP_INDEX		equ 0x0003  ;; Display index
HELP_CONTENTS		equ 0x0003
HELP_HELPONHELP		equ 0x0004  ;; Display help on using help
HELP_SETINDEX		equ 0x0005  ;; Set current Index for multi index help
HELP_SETCONTENTS	equ 0x0005
HELP_CONTEXTPOPUP	equ 0x0008
HELP_FORCEFILE		equ 0x0009
HELP_KEY		equ 0x0101  ;; Display topic for keyword in offabData
HELP_COMMAND		equ 0x0102
HELP_PARTIALKEY		equ 0x0105
HELP_MULTIKEY		equ 0x0201
HELP_SETWINPOS		equ 0x0203
if(WINVER GE 0x0400)
HELP_CONTEXTMENU	equ 0x000a
HELP_FINDER		equ 0x000b
HELP_WM_HELP		equ 0x000c
HELP_SETPOPUP_POS	equ 0x000d

HELP_TCARD		equ 0x8000
HELP_TCARD_DATA		equ 0x0010
HELP_TCARD_OTHER_CALLER equ 0x0011

;; These are in winhelp.h in Win95.
IDH_NO_HELP		equ 28440
IDH_MISSING_CONTEXT	equ 28441 ;; Control doesn't have matching help context
IDH_GENERIC_HELP_BUTTON equ 28442 ;; Property sheet help button
IDH_OK			equ 28443
IDH_CANCEL		equ 28444
IDH_HELP		equ 28445

endif ;; WINVER GE 0x0400

;; end_r_winuser


;BOOL
WinHelpA proto _CType \
	      hWndMain: HWND,
	      lpszHelp: LPCSTR,
	      uCommand: UINT,
	       dwData : DWORD
;BOOL
WinHelpW proto _CType \
	      hWndMain: HWND,
	      lpszHelp: LPCWSTR,
	      uCommand: UINT,
	       dwData : DWORD
ifdef _UNICODE
WinHelp			equ <WinHelpW>
else
WinHelp			equ <WinHelpA>
endif ;; NOT UNICODE

endif ;; NOT NOHELP

if(WINVER GE 0x0500)
GR_GDIOBJECTS		equ 0	    ;; Count of GDI objects
GR_USEROBJECTS		equ 1	    ;; Count of USER objects
if(WINVER GE 0x0601)
GR_GDIOBJECTS_PEAK	equ 2	    ;; Peak count of GDI objects
GR_USEROBJECTS_PEAK	equ 4	    ;; Peak count of USER objects
endif ;; WINVER GE 0x0601
if(WINVER GE 0x0601)
GR_GLOBAL		equ (-2)
endif ;; WINVER GE 0x0601
endif ;; WINVER GE 0x0500

if(WINVER GE 0x0500)
;DWORD
GetGuiResources proto _CType \
	      hProcess: HANDLE,
	       uiFlags: DWORD
endif ;; WINVER GE 0x0500

ifndef NOSYSPARAMSINFO

;;
;; Parameter for SystemParametersInfo()
;;

SPI_GETBEEP		equ 1
SPI_SETBEEP		equ 2
SPI_GETMOUSE		equ 3
SPI_SETMOUSE		equ 4
SPI_GETBORDER		equ 5
SPI_SETBORDER		equ 6
SPI_GETKEYBOARDSPEED	equ 10
SPI_SETKEYBOARDSPEED	equ 11
SPI_LANGDRIVER		equ 12
SPI_ICONHORIZONTALSPACING equ 13
SPI_GETSCREENSAVETIMEOUT equ 14
SPI_SETSCREENSAVETIMEOUT equ 15
SPI_GETSCREENSAVEACTIVE equ 16
SPI_SETSCREENSAVEACTIVE equ 17
SPI_GETGRIDGRANULARITY	equ 18
SPI_SETGRIDGRANULARITY	equ 19
SPI_SETDESKWALLPAPER	equ 20
SPI_SETDESKPATTERN	equ 21
SPI_GETKEYBOARDDELAY	equ 22
SPI_SETKEYBOARDDELAY	equ 23
SPI_ICONVERTICALSPACING equ 24
SPI_GETICONTITLEWRAP	equ 25
SPI_SETICONTITLEWRAP	equ 26
SPI_GETMENUDROPALIGNMENT equ 27
SPI_SETMENUDROPALIGNMENT equ 28
SPI_SETDOUBLECLKWIDTH	equ 29
SPI_SETDOUBLECLKHEIGHT	equ 30
SPI_GETICONTITLELOGFONT equ 31
SPI_SETDOUBLECLICKTIME	equ 32
SPI_SETMOUSEBUTTONSWAP	equ 33
SPI_SETICONTITLELOGFONT equ 34
SPI_GETFASTTASKSWITCH	equ 35
SPI_SETFASTTASKSWITCH	equ 36
if(WINVER GE 0x0400)
SPI_SETDRAGFULLWINDOWS	equ 37
SPI_GETDRAGFULLWINDOWS	equ 38
SPI_GETNONCLIENTMETRICS equ 41
SPI_SETNONCLIENTMETRICS equ 42
SPI_GETMINIMIZEDMETRICS equ 43
SPI_SETMINIMIZEDMETRICS equ 44
SPI_GETICONMETRICS	equ 45
SPI_SETICONMETRICS	equ 46
SPI_SETWORKAREA		equ 47
SPI_GETWORKAREA		equ 48
SPI_SETPENWINDOWS	equ 49

SPI_GETHIGHCONTRAST	equ 66
SPI_SETHIGHCONTRAST	equ 67
SPI_GETKEYBOARDPREF	equ 68
SPI_SETKEYBOARDPREF	equ 69
SPI_GETSCREENREADER	equ 70
SPI_SETSCREENREADER	equ 71
SPI_GETANIMATION	equ 72
SPI_SETANIMATION	equ 73
SPI_GETFONTSMOOTHING	equ 74
SPI_SETFONTSMOOTHING	equ 75
SPI_SETDRAGWIDTH	equ 76
SPI_SETDRAGHEIGHT	equ 77
SPI_SETHANDHELD		equ 78
SPI_GETLOWPOWERTIMEOUT	equ 79
SPI_GETPOWEROFFTIMEOUT	equ 80
SPI_SETLOWPOWERTIMEOUT	equ 81
SPI_SETPOWEROFFTIMEOUT	equ 82
SPI_GETLOWPOWERACTIVE	equ 83
SPI_GETPOWEROFFACTIVE	equ 84
SPI_SETLOWPOWERACTIVE	equ 85
SPI_SETPOWEROFFACTIVE	equ 86
SPI_SETCURSORS		equ 87
SPI_SETICONS		equ 88
SPI_GETDEFAULTINPUTLANG equ 89
SPI_SETDEFAULTINPUTLANG equ 90
SPI_SETLANGTOGGLE	equ 91
SPI_GETWINDOWSEXTENSION equ 92
SPI_SETMOUSETRAILS	equ 93
SPI_GETMOUSETRAILS	equ 94
SPI_SETSCREENSAVERRUNNING equ 97
SPI_SCREENSAVERRUNNING	equ SPI_SETSCREENSAVERRUNNING
endif ;; WINVER GE 0x0400
SPI_GETFILTERKEYS	equ 0x0032
SPI_SETFILTERKEYS	equ 0x0033
SPI_GETTOGGLEKEYS	equ 0x0034
SPI_SETTOGGLEKEYS	equ 0x0035
SPI_GETMOUSEKEYS	equ 0x0036
SPI_SETMOUSEKEYS	equ 0x0037
SPI_GETSHOWSOUNDS	equ 0x0038
SPI_SETSHOWSOUNDS	equ 0x0039
SPI_GETSTICKYKEYS	equ 0x003A
SPI_SETSTICKYKEYS	equ 0x003B
SPI_GETACCESSTIMEOUT	equ 0x003C
SPI_SETACCESSTIMEOUT	equ 0x003D
if(WINVER GE 0x0400)
SPI_GETSERIALKEYS	equ 0x003E
SPI_SETSERIALKEYS	equ 0x003F
endif ;; WINVER GE 0x0400
SPI_GETSOUNDSENTRY	equ 0x0040
SPI_SETSOUNDSENTRY	equ 0x0041
if(_WIN32_WINNT GE 0x0400)
SPI_GETSNAPTODEFBUTTON	equ 0x005F
SPI_SETSNAPTODEFBUTTON	equ 0x0060
endif ;; _WIN32_WINNT GE 0x0400

if (_WIN32_WINNT GE 0x0400) OR (_WIN32_WINDOWS GT 0x0400)
SPI_GETMOUSEHOVERWIDTH	equ 0x0062
SPI_SETMOUSEHOVERWIDTH	equ 0x0063
SPI_GETMOUSEHOVERHEIGHT equ 0x0064
SPI_SETMOUSEHOVERHEIGHT equ 0x0065
SPI_GETMOUSEHOVERTIME	equ 0x0066
SPI_SETMOUSEHOVERTIME	equ 0x0067
SPI_GETWHEELSCROLLLINES equ 0x0068
SPI_SETWHEELSCROLLLINES equ 0x0069
SPI_GETMENUSHOWDELAY	equ 0x006A
SPI_SETMENUSHOWDELAY	equ 0x006B
if (_WIN32_WINNT GE 0x0600)
SPI_GETWHEELSCROLLCHARS equ 0x006C
SPI_SETWHEELSCROLLCHARS equ 0x006D
endif
SPI_GETSHOWIMEUI	equ 0x006E
SPI_SETSHOWIMEUI	equ 0x006F
endif

if(WINVER GE 0x0500)
SPI_GETMOUSESPEED	equ 0x0070
SPI_SETMOUSESPEED	equ 0x0071
SPI_GETSCREENSAVERRUNNING equ 0x0072
SPI_GETDESKWALLPAPER	equ 0x0073
endif ;; WINVER GE 0x0500

if(WINVER GE 0x0600)
SPI_GETAUDIODESCRIPTION equ 0x0074
SPI_SETAUDIODESCRIPTION equ 0x0075
SPI_GETSCREENSAVESECURE equ 0x0076
SPI_SETSCREENSAVESECURE equ 0x0077
endif ;; WINVER GE 0x0600

if(_WIN32_WINNT GE 0x0601)
SPI_GETHUNGAPPTIMEOUT	equ 0x0078
SPI_SETHUNGAPPTIMEOUT	equ 0x0079
SPI_GETWAITTOKILLTIMEOUT equ 0x007A
SPI_SETWAITTOKILLTIMEOUT equ 0x007B
SPI_GETWAITTOKILLSERVICETIMEOUT equ 0x007C
SPI_SETWAITTOKILLSERVICETIMEOUT equ 0x007D
SPI_GETMOUSEDOCKTHRESHOLD equ 0x007E
SPI_SETMOUSEDOCKTHRESHOLD equ 0x007F
SPI_GETPENDOCKTHRESHOLD equ 0x0080
SPI_SETPENDOCKTHRESHOLD equ 0x0081
SPI_GETWINARRANGING	equ 0x0082
SPI_SETWINARRANGING	equ 0x0083
SPI_GETMOUSEDRAGOUTTHRESHOLD equ 0x0084
SPI_SETMOUSEDRAGOUTTHRESHOLD equ 0x0085
SPI_GETPENDRAGOUTTHRESHOLD equ 0x0086
SPI_SETPENDRAGOUTTHRESHOLD equ 0x0087
SPI_GETMOUSESIDEMOVETHRESHOLD equ 0x0088
SPI_SETMOUSESIDEMOVETHRESHOLD equ 0x0089
SPI_GETPENSIDEMOVETHRESHOLD equ 0x008A
SPI_SETPENSIDEMOVETHRESHOLD equ 0x008B
SPI_GETDRAGFROMMAXIMIZE equ 0x008C
SPI_SETDRAGFROMMAXIMIZE equ 0x008D
SPI_GETSNAPSIZING	equ 0x008E
SPI_SETSNAPSIZING	equ 0x008F
SPI_GETDOCKMOVING	equ 0x0090
SPI_SETDOCKMOVING	equ 0x0091
endif ;; _WIN32_WINNT GE 0x0601

if(WINVER GE 0x0500)
SPI_GETACTIVEWINDOWTRACKING equ 0x1000
SPI_SETACTIVEWINDOWTRACKING equ 0x1001
SPI_GETMENUANIMATION	equ 0x1002
SPI_SETMENUANIMATION	equ 0x1003
SPI_GETCOMBOBOXANIMATION equ 0x1004
SPI_SETCOMBOBOXANIMATION equ 0x1005
SPI_GETLISTBOXSMOOTHSCROLLING equ 0x1006
SPI_SETLISTBOXSMOOTHSCROLLING equ 0x1007
SPI_GETGRADIENTCAPTIONS equ 0x1008
SPI_SETGRADIENTCAPTIONS equ 0x1009
SPI_GETKEYBOARDCUES	equ 0x100A
SPI_SETKEYBOARDCUES	equ 0x100B
SPI_GETMENUUNDERLINES	equ SPI_GETKEYBOARDCUES
SPI_SETMENUUNDERLINES	equ SPI_SETKEYBOARDCUES
SPI_GETACTIVEWNDTRKZORDER equ 0x100C
SPI_SETACTIVEWNDTRKZORDER equ 0x100D
SPI_GETHOTTRACKING	equ 0x100E
SPI_SETHOTTRACKING	equ 0x100F
SPI_GETMENUFADE		equ 0x1012
SPI_SETMENUFADE		equ 0x1013
SPI_GETSELECTIONFADE	equ 0x1014
SPI_SETSELECTIONFADE	equ 0x1015
SPI_GETTOOLTIPANIMATION equ 0x1016
SPI_SETTOOLTIPANIMATION equ 0x1017
SPI_GETTOOLTIPFADE	equ 0x1018
SPI_SETTOOLTIPFADE	equ 0x1019
SPI_GETCURSORSHADOW	equ 0x101A
SPI_SETCURSORSHADOW	equ 0x101B
if(_WIN32_WINNT GE 0x0501)
SPI_GETMOUSESONAR	equ 0x101C
SPI_SETMOUSESONAR	equ 0x101D
SPI_GETMOUSECLICKLOCK	equ 0x101E
SPI_SETMOUSECLICKLOCK	equ 0x101F
SPI_GETMOUSEVANISH	equ 0x1020
SPI_SETMOUSEVANISH	equ 0x1021
SPI_GETFLATMENU		equ 0x1022
SPI_SETFLATMENU		equ 0x1023
SPI_GETDROPSHADOW	equ 0x1024
SPI_SETDROPSHADOW	equ 0x1025
SPI_GETBLOCKSENDINPUTRESETS equ 0x1026
SPI_SETBLOCKSENDINPUTRESETS equ 0x1027
endif ;; _WIN32_WINNT GE 0x0501

SPI_GETUIEFFECTS	equ 0x103E
SPI_SETUIEFFECTS	equ 0x103F

if(_WIN32_WINNT GE 0x0600)
SPI_GETDISABLEOVERLAPPEDCONTENT equ 0x1040
SPI_SETDISABLEOVERLAPPEDCONTENT equ 0x1041
SPI_GETCLIENTAREAANIMATION equ 0x1042
SPI_SETCLIENTAREAANIMATION equ 0x1043
SPI_GETCLEARTYPE	equ 0x1048
SPI_SETCLEARTYPE	equ 0x1049
SPI_GETSPEECHRECOGNITION equ 0x104A
SPI_SETSPEECHRECOGNITION equ 0x104B
endif ;; _WIN32_WINNT GE 0x0600

SPI_GETFOREGROUNDLOCKTIMEOUT equ 0x2000
SPI_SETFOREGROUNDLOCKTIMEOUT equ 0x2001
SPI_GETACTIVEWNDTRKTIMEOUT equ 0x2002
SPI_SETACTIVEWNDTRKTIMEOUT equ 0x2003
SPI_GETFOREGROUNDFLASHCOUNT equ 0x2004
SPI_SETFOREGROUNDFLASHCOUNT equ 0x2005
SPI_GETCARETWIDTH	equ 0x2006
SPI_SETCARETWIDTH	equ 0x2007

if(_WIN32_WINNT GE 0x0501)
SPI_GETMOUSECLICKLOCKTIME equ 0x2008
SPI_SETMOUSECLICKLOCKTIME equ 0x2009
SPI_GETFONTSMOOTHINGTYPE equ 0x200A
SPI_SETFONTSMOOTHINGTYPE equ 0x200B

;; constants for SPI_GETFONTSMOOTHINGTYPE and SPI_SETFONTSMOOTHINGTYPE:
FE_FONTSMOOTHINGSTANDARD equ 0x0001
FE_FONTSMOOTHINGCLEARTYPE equ 0x0002

SPI_GETFONTSMOOTHINGCONTRAST equ 0x200C
SPI_SETFONTSMOOTHINGCONTRAST equ 0x200D

SPI_GETFOCUSBORDERWIDTH equ 0x200E
SPI_SETFOCUSBORDERWIDTH equ 0x200F
SPI_GETFOCUSBORDERHEIGHT equ 0x2010
SPI_SETFOCUSBORDERHEIGHT equ 0x2011

SPI_GETFONTSMOOTHINGORIENTATION equ 0x2012
SPI_SETFONTSMOOTHINGORIENTATION equ 0x2013

;; constants for SPI_GETFONTSMOOTHINGORIENTATION and SPI_SETFONTSMOOTHINGORIENTATION:
FE_FONTSMOOTHINGORIENTATIONBGR equ 0x0000
FE_FONTSMOOTHINGORIENTATIONRGB equ 0x0001
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0600)
SPI_GETMINIMUMHITRADIUS equ 0x2014
SPI_SETMINIMUMHITRADIUS equ 0x2015
SPI_GETMESSAGEDURATION	equ 0x2016
SPI_SETMESSAGEDURATION	equ 0x2017
endif ;; _WIN32_WINNT GE 0x0600

endif ;; WINVER GE 0x0500

;;
;; Flags
;;
SPIF_UPDATEINIFILE	equ 0x0001
SPIF_SENDWININICHANGE	equ 0x0002
SPIF_SENDCHANGE		equ SPIF_SENDWININICHANGE


METRICS_USEDEFAULT	equ -1
ifdef _WINGDI_
ifndef NOGDI
NONCLIENTMETRICSA	STRUC
cbSize			UINT ?
iBorderWidth		SINT ?
iScrollWidth		SINT ?
iScrollHeight		SINT ?
iCaptionWidth		SINT ?
iCaptionHeight		SINT ?
lfCaptionFont		LOGFONTA <>
iSmCaptionWidth		SINT ?
iSmCaptionHeight	SINT ?
lfSmCaptionFont		LOGFONTA <>
iMenuWidth		SINT ?
iMenuHeight		SINT ?
lfMenuFont		LOGFONTA <>
lfStatusFont		LOGFONTA <>
lfMessageFont		LOGFONTA <>
if(WINVER GE 0x0600)
iPaddedBorderWidth	SINT ?
endif ;; WINVER GE 0x0600
NONCLIENTMETRICSA	ENDS
PNONCLIENTMETRICSA	typedef ptr NONCLIENTMETRICSA
LPNONCLIENTMETRICSA	typedef ptr NONCLIENTMETRICSA
NONCLIENTMETRICSW	STRUC
cbSize			UINT ?
iBorderWidth		SINT ?
iScrollWidth		SINT ?
iScrollHeight		SINT ?
iCaptionWidth		SINT ?
iCaptionHeight		SINT ?
lfCaptionFont		LOGFONTW <>
iSmCaptionWidth		SINT ?
iSmCaptionHeight	SINT ?
lfSmCaptionFont		LOGFONTW <>
iMenuWidth		SINT ?
iMenuHeight		SINT ?
lfMenuFont		LOGFONTW <>
lfStatusFont		LOGFONTW <>
lfMessageFont		LOGFONTW <>
if(WINVER GE 0x0600)
iPaddedBorderWidth	SINT ?
endif ;; WINVER GE 0x0600
NONCLIENTMETRICSW	ENDS
PNONCLIENTMETRICSW	typedef ptr NONCLIENTMETRICSW
LPNONCLIENTMETRICSW	typedef ptr NONCLIENTMETRICSW
ifdef _UNICODE
NONCLIENTMETRICS	typedef NONCLIENTMETRICSW
PNONCLIENTMETRICS	typedef PNONCLIENTMETRICSW
LPNONCLIENTMETRICS	typedef LPNONCLIENTMETRICSW
else
NONCLIENTMETRICS	typedef NONCLIENTMETRICSA
PNONCLIENTMETRICS	typedef PNONCLIENTMETRICSA
LPNONCLIENTMETRICS	typedef LPNONCLIENTMETRICSA
endif ;; UNICODE
endif ;; NOGDI
endif ;; _WINGDI_

ARW_BOTTOMLEFT		equ 0x0000
ARW_BOTTOMRIGHT		equ 0x0001
ARW_TOPLEFT		equ 0x0002
ARW_TOPRIGHT		equ 0x0003
ARW_STARTMASK		equ 0x0003
ARW_STARTRIGHT		equ 0x0001
ARW_STARTTOP		equ 0x0002

ARW_LEFT		equ 0x0000
ARW_RIGHT		equ 0x0000
ARW_UP			equ 0x0004
ARW_DOWN		equ 0x0004
ARW_HIDE		equ 0x0008

MINIMIZEDMETRICS	STRUC
cbSize			UINT ?
iWidth			SINT ?
iHorzGap		SINT ?
iVertGap		SINT ?
iArrange		SINT ?
MINIMIZEDMETRICS	ENDS
PMINIMIZEDMETRICS	typedef ptr MINIMIZEDMETRICS
LPMINIMIZEDMETRICS	typedef ptr MINIMIZEDMETRICS

ifdef _WINGDI_
ifndef NOGDI
ICONMETRICSA		STRUC
cbSize			UINT ?
iHorzSpacing		SINT ?
iVertSpacing		SINT ?
iTitleWrap		SINT ?
lfFont			LOGFONTA <>
ICONMETRICSA		ENDS
PICONMETRICSA		typedef ptr ICONMETRICSA
LPICONMETRICSA		typedef ptr ICONMETRICSA
ICONMETRICSW		STRUC
cbSize			UINT ?
iHorzSpacing		SINT ?
iVertSpacing		SINT ?
iTitleWrap		SINT ?
lfFont			LOGFONTW <>
ICONMETRICSW		ENDS
PICONMETRICSW		typedef ptr ICONMETRICSW
LPICONMETRICSW		typedef ptr ICONMETRICSW
ifdef _UNICODE
ICONMETRICS		typedef ICONMETRICSW
PICONMETRICS		typedef PICONMETRICSW
LPICONMETRICS		typedef LPICONMETRICSW
else
ICONMETRICS		typedef ICONMETRICSA
PICONMETRICS		typedef PICONMETRICSA
LPICONMETRICS		typedef LPICONMETRICSA
endif ;; UNICODE
endif ;; NOGDI
endif ;; _WINGDI_

ANIMATIONINFO		STRUC
cbSize			UINT ?
iMinAnimate		SINT ?
ANIMATIONINFO		ENDS
LPANIMATIONINFO		typedef ptr ANIMATIONINFO

SERIALKEYSA		STRUC
cbSize			UINT ?
dwFlags			dd ?
lpszActivePort		LPSTR ?
lpszPort		LPSTR ?
iBaudRate		UINT ?
iPortState		UINT ?
iActive			UINT ?
SERIALKEYSA		ENDS
LPSERIALKEYSA		typedef ptr SERIALKEYSA
SERIALKEYSW		STRUC
cbSize			UINT ?
dwFlags			dd ?
lpszActivePort		LPWSTR ?
lpszPort		LPWSTR ?
iBaudRate		UINT ?
iPortState		UINT ?
iActive			UINT ?
SERIALKEYSW		ENDS
LPSERIALKEYSW		typedef ptr SERIALKEYSW
ifdef _UNICODE
SERIALKEYS		typedef SERIALKEYSW
LPSERIALKEYS		typedef LPSERIALKEYSW
else
SERIALKEYS		typedef SERIALKEYSA
LPSERIALKEYS		typedef LPSERIALKEYSA
endif ;; UNICODE

;; flags for SERIALKEYS dwFlags field
SERKF_SERIALKEYSON	equ 0x00000001
SERKF_AVAILABLE		equ 0x00000002
SERKF_INDICATOR		equ 0x00000004


HIGHCONTRASTA		STRUC
cbSize			UINT ?
dwFlags			dd ?
lpszDefaultScheme	LPSTR ?
HIGHCONTRASTA		ENDS
LPHIGHCONTRASTA		typedef ptr HIGHCONTRASTA
HIGHCONTRASTW		STRUC
cbSize			UINT ?
dwFlags			dd ?
lpszDefaultScheme	LPWSTR ?
HIGHCONTRASTW		ENDS
LPHIGHCONTRASTW		typedef ptr HIGHCONTRASTW
ifdef _UNICODE
HIGHCONTRAST		typedef HIGHCONTRASTW
LPHIGHCONTRAST		typedef LPHIGHCONTRASTW
else
HIGHCONTRAST		typedef HIGHCONTRASTA
LPHIGHCONTRAST		typedef LPHIGHCONTRASTA
endif ;; UNICODE

;; flags for HIGHCONTRAST dwFlags field
HCF_HIGHCONTRASTON	equ 0x00000001
HCF_AVAILABLE		equ 0x00000002
HCF_HOTKEYACTIVE	equ 0x00000004
HCF_CONFIRMHOTKEY	equ 0x00000008
HCF_HOTKEYSOUND		equ 0x00000010
HCF_INDICATOR		equ 0x00000020
HCF_HOTKEYAVAILABLE	equ 0x00000040
HCF_LOGONDESKTOP	equ 0x00000100
HCF_DEFAULTDESKTOP	equ 0x00000200

;; Flags for ChangeDisplaySettings
CDS_UPDATEREGISTRY	equ 0x00000001
CDS_TEST		equ 0x00000002
CDS_FULLSCREEN		equ 0x00000004
CDS_GLOBAL		equ 0x00000008
CDS_SET_PRIMARY		equ 0x00000010
CDS_VIDEOPARAMETERS	equ 0x00000020
if(WINVER GE 0x0600)
CDS_ENABLE_UNSAFE_MODES equ 0x00000100
CDS_DISABLE_UNSAFE_MODES equ 0x00000200
endif ;; WINVER GE 0x0600
CDS_RESET		equ 0x40000000
CDS_SETRECT		equ 0x20000000
CDS_NORESET		equ 0x10000000

include tvout.inc

;; Return values for ChangeDisplaySettings
DISP_CHANGE_SUCCESSFUL	equ 0
DISP_CHANGE_RESTART	equ 1
DISP_CHANGE_FAILED	equ -1
DISP_CHANGE_BADMODE	equ -2
DISP_CHANGE_NOTUPDATED	equ -3
DISP_CHANGE_BADFLAGS	equ -4
DISP_CHANGE_BADPARAM	equ -5
if(_WIN32_WINNT GE 0x0501)
DISP_CHANGE_BADDUALVIEW equ -6
endif ;; _WIN32_WINNT GE 0x0501

ifdef _WINGDI_
ifndef NOGDI

;LONG
ChangeDisplaySettingsA proto _CType \
	     lpDevMode: LPDEVMODEA,
	       dwFlags: DWORD
;LONG
ChangeDisplaySettingsW proto _CType \
	     lpDevMode: LPDEVMODEW,
	       dwFlags: DWORD
ifdef _UNICODE
ChangeDisplaySettings	equ <ChangeDisplaySettingsW>
else
ChangeDisplaySettings	equ <ChangeDisplaySettingsA>
endif ;; NOT UNICODE

;LONG
ChangeDisplaySettingsExA proto _CType \
	lpszDeviceName: LPCSTR,
	     lpDevMode: LPDEVMODEA,
		  hwnd: HWND,
	       dwflags: DWORD,
		lParam: LPVOID
;LONG
ChangeDisplaySettingsExW proto _CType \
	lpszDeviceName: LPCWSTR,
	     lpDevMode: LPDEVMODEW,
		  hwnd: HWND,
	       dwflags: DWORD,
		lParam: LPVOID
ifdef _UNICODE
ChangeDisplaySettingsEx equ <ChangeDisplaySettingsExW>
else
ChangeDisplaySettingsEx equ <ChangeDisplaySettingsExA>
endif ;; NOT UNICODE

ENUM_CURRENT_SETTINGS	equ (-1)
ENUM_REGISTRY_SETTINGS	equ (-2)

;BOOL
EnumDisplaySettingsA proto _CType \
	lpszDeviceName: LPCSTR,
	      iModeNum: DWORD,
	     lpDevMode: LPDEVMODEA
;BOOL
EnumDisplaySettingsW proto _CType \
	lpszDeviceName: LPCWSTR,
	      iModeNum: DWORD,
	     lpDevMode: LPDEVMODEW
ifdef _UNICODE
EnumDisplaySettings	equ <EnumDisplaySettingsW>
else
EnumDisplaySettings	equ <EnumDisplaySettingsA>
endif ;; NOT UNICODE

if(WINVER GE 0x0500)
;BOOL
EnumDisplaySettingsExA proto _CType \
	lpszDeviceName: LPCSTR,
	      iModeNum: DWORD,
	     lpDevMode: LPDEVMODEA,
	       dwFlags: DWORD
EnumDisplaySettingsExW proto _CType \
	lpszDeviceName: LPCWSTR,
	      iModeNum: DWORD,
	     lpDevMode: LPDEVMODEA,
	       dwFlags: DWORD
ifdef _UNICODE
EnumDisplaySettingsEx	equ <EnumDisplaySettingsExW>
else
EnumDisplaySettingsEx	equ <EnumDisplaySettingsExA>
endif ;; NOT UNICODE

;; Flags for EnumDisplaySettingsEx
EDS_RAWMODE		equ 0x00000002
EDS_ROTATEDMODE		equ 0x00000004

;BOOL
EnumDisplayDevicesA proto _CType \
		Unused: PVOID,
	       iDevNum: DWORD,
       lpDisplayDevice: PDISPLAY_DEVICEA,
	       dwFlags: DWORD
;BOOL
EnumDisplayDevicesW proto _CType \
		Unused: PVOID,
	       iDevNum: DWORD,
       lpDisplayDevice: PDISPLAY_DEVICEW,
	       dwFlags: DWORD
ifdef _UNICODE
EnumDisplayDevices	equ <EnumDisplayDevicesW>
else
EnumDisplayDevices	equ <EnumDisplayDevicesA>
endif ;; NOT UNICODE

;; Flags for EnumDisplayDevices
EDD_GET_DEVICE_INTERFACE_NAME equ 0x00000001

endif ;; WINVER GE 0x0500

if(WINVER GE 0x0601)

;LONG
GetDisplayConfigBufferSizes proto _CType \
		 flags: UINT,
  numPathArrayElements: ptr UINT,
numModeInfoArrayElements: ptr UINT

;LONG
SetDisplayConfig proto _CType \
	     pathArray: ptr DISPLAYCONFIG_PATH_INFO,
  numPathArrayElements: UINT,
	 modeInfoArray: ptr DISPLAYCONFIG_MODE_INFO,
		 flags: UINT

;LONG
QueryDisplayConfig proto _CType \
		 flags: UINT,
  numPathArrayElements: ptr UINT,
	     pathArray: ptr DISPLAYCONFIG_PATH_INFO,
	 modeInfoArray: ptr DISPLAYCONFIG_MODE_INFO,
     currentTopologyId: ptr DISPLAYCONFIG_TOPOLOGY_ID

;LONG
DisplayConfigGetDeviceInfo proto _CType \
	 requestPacket: ptr DISPLAYCONFIG_DEVICE_INFO_HEADER

;LONG
DisplayConfigSetDeviceInfo proto _CType \
	     setPacket: ptr DISPLAYCONFIG_DEVICE_INFO_HEADER

endif ;; WINVER GE 0x0601

endif ;; NOGDI
endif ;; _WINGDI_


;BOOL
SystemParametersInfoA proto _CType \
	      uiAction: UINT,
	       uiParam: UINT,
	       pvParam: PVOID,
	       fWinIni: UINT
;BOOL
SystemParametersInfoW proto _CType \
	      uiAction: UINT,
	       uiParam: UINT,
	       pvParam: PVOID,
	       fWinIni: UINT
ifdef _UNICODE
SystemParametersInfo	equ <SystemParametersInfoW>
else
SystemParametersInfo	equ <SystemParametersInfoA>
endif ;; NOT UNICODE

endif  ;; NOT NOSYSPARAMSINFO

;;
;; Accessibility support
;;
FILTERKEYS		STRUC
cbSize			UINT ?
dwFlags			dd ?
iWaitMSec		dd ?	;; Acceptance Delay
iDelayMSec		dd ?	;; Delay Until Repeat
iRepeatMSec		dd ?	;; Repeat Rate
iBounceMSec		dd ?	;; Debounce Time
FILTERKEYS		ENDS
LPFILTERKEYS		typedef ptr FILTERKEYS

;;
;; FILTERKEYS dwFlags field
;;
FKF_FILTERKEYSON	equ 0x00000001
FKF_AVAILABLE		equ 0x00000002
FKF_HOTKEYACTIVE	equ 0x00000004
FKF_CONFIRMHOTKEY	equ 0x00000008
FKF_HOTKEYSOUND		equ 0x00000010
FKF_INDICATOR		equ 0x00000020
FKF_CLICKON		equ 0x00000040

STICKYKEYS		STRUC
cbSize			UINT ?
dwFlags			dd ?
STICKYKEYS		ENDS
LPSTICKYKEYS		typedef ptr STICKYKEYS

;;
;; STICKYKEYS dwFlags field
;;
SKF_STICKYKEYSON	equ 0x00000001
SKF_AVAILABLE		equ 0x00000002
SKF_HOTKEYACTIVE	equ 0x00000004
SKF_CONFIRMHOTKEY	equ 0x00000008
SKF_HOTKEYSOUND		equ 0x00000010
SKF_INDICATOR		equ 0x00000020
SKF_AUDIBLEFEEDBACK	equ 0x00000040
SKF_TRISTATE		equ 0x00000080
SKF_TWOKEYSOFF		equ 0x00000100
if(_WIN32_WINNT GE 0x0500)
SKF_LALTLATCHED		equ 0x10000000
SKF_LCTLLATCHED		equ 0x04000000
SKF_LSHIFTLATCHED	equ 0x01000000
SKF_RALTLATCHED		equ 0x20000000
SKF_RCTLLATCHED		equ 0x08000000
SKF_RSHIFTLATCHED	equ 0x02000000
SKF_LWINLATCHED		equ 0x40000000
SKF_RWINLATCHED		equ 0x80000000
SKF_LALTLOCKED		equ 0x00100000
SKF_LCTLLOCKED		equ 0x00040000
SKF_LSHIFTLOCKED	equ 0x00010000
SKF_RALTLOCKED		equ 0x00200000
SKF_RCTLLOCKED		equ 0x00080000
SKF_RSHIFTLOCKED	equ 0x00020000
SKF_LWINLOCKED		equ 0x00400000
SKF_RWINLOCKED		equ 0x00800000
endif ;; _WIN32_WINNT GE 0x0500

MOUSEKEYS		STRUC
cbSize			UINT ?
dwFlags			dd ?
iMaxSpeed		dd ?
iTimeToMaxSpeed		dd ?
iCtrlSpeed		dd ?
dwReserved1		dd ?
dwReserved2		dd ?
MOUSEKEYS		ENDS
LPMOUSEKEYS		typedef ptr MOUSEKEYS

;;
;; MOUSEKEYS dwFlags field
;;
MKF_MOUSEKEYSON		equ 0x00000001
MKF_AVAILABLE		equ 0x00000002
MKF_HOTKEYACTIVE	equ 0x00000004
MKF_CONFIRMHOTKEY	equ 0x00000008
MKF_HOTKEYSOUND		equ 0x00000010
MKF_INDICATOR		equ 0x00000020
MKF_MODIFIERS		equ 0x00000040
MKF_REPLACENUMBERS	equ 0x00000080
if(_WIN32_WINNT GE 0x0500)
MKF_LEFTBUTTONSEL	equ 0x10000000
MKF_RIGHTBUTTONSEL	equ 0x20000000
MKF_LEFTBUTTONDOWN	equ 0x01000000
MKF_RIGHTBUTTONDOWN	equ 0x02000000
MKF_MOUSEMODE		equ 0x80000000
endif ;; _WIN32_WINNT GE 0x0500

ACCESSTIMEOUT		STRUC
cbSize			UINT ?
dwFlags			dd ?
iTimeOutMSec		dd ?
ACCESSTIMEOUT		ENDS
LPACCESSTIMEOUT		typedef ptr ACCESSTIMEOUT

;;
;; ACCESSTIMEOUT dwFlags field
;;
ATF_TIMEOUTON		equ 0x00000001
ATF_ONOFFFEEDBACK	equ 0x00000002

;; values for SOUNDSENTRY iFSGrafEffect field
SSGF_NONE		equ 0
SSGF_DISPLAY		equ 3

;; values for SOUNDSENTRY iFSTextEffect field
SSTF_NONE		equ 0
SSTF_CHARS		equ 1
SSTF_BORDER		equ 2
SSTF_DISPLAY		equ 3

;; values for SOUNDSENTRY iWindowsEffect field
SSWF_NONE		equ 0
SSWF_TITLE		equ 1
SSWF_WINDOW		equ 2
SSWF_DISPLAY		equ 3
SSWF_CUSTOM		equ 4

SOUNDSENTRYA		STRUC
cbSize			UINT ?
dwFlags			dd ?
iFSTextEffect		dd ?
iFSTextEffectMSec	dd ?
iFSTextEffectColorBits	dd ?
iFSGrafEffect		dd ?
iFSGrafEffectMSec	dd ?
iFSGrafEffectColor	dd ?
iWindowsEffect		dd ?
iWindowsEffectMSec	dd ?
lpszWindowsEffectDLL	LPSTR ?
iWindowsEffectOrdinal	dd ?
SOUNDSENTRYA		ENDS
LPSOUNDSENTRYA		typedef ptr SOUNDSENTRYA
SOUNDSENTRYW		STRUC
cbSize			UINT ?
dwFlags			dd ?
iFSTextEffect		dd ?
iFSTextEffectMSec	dd ?
iFSTextEffectColorBits	dd ?
iFSGrafEffect		dd ?
iFSGrafEffectMSec	dd ?
iFSGrafEffectColor	dd ?
iWindowsEffect		dd ?
iWindowsEffectMSec	dd ?
lpszWindowsEffectDLL	LPWSTR ?
iWindowsEffectOrdinal	dd ?
SOUNDSENTRYW		ENDS
LPSOUNDSENTRYW		typedef ptr SOUNDSENTRYW
ifdef _UNICODE
SOUNDSENTRY		typedef SOUNDSENTRYW
LPSOUNDSENTRY		typedef LPSOUNDSENTRYW
else
SOUNDSENTRY		typedef SOUNDSENTRYA
LPSOUNDSENTRY		typedef LPSOUNDSENTRYA
endif ;; UNICODE

;;
;; SOUNDSENTRY dwFlags field
;;
SSF_SOUNDSENTRYON	equ 0x00000001
SSF_AVAILABLE		equ 0x00000002
SSF_INDICATOR		equ 0x00000004

if(_WIN32_WINNT GE 0x0600)
;BOOL
SoundSentry proto _CType
endif ;; _WIN32_WINNT GE 0x0600

TOGGLEKEYS		STRUC
cbSize			UINT ?
dwFlags			dd ?
TOGGLEKEYS		ENDS
LPTOGGLEKEYS		typedef ptr TOGGLEKEYS

;;
;; TOGGLEKEYS dwFlags field
;;
TKF_TOGGLEKEYSON	equ 0x00000001
TKF_AVAILABLE		equ 0x00000002
TKF_HOTKEYACTIVE	equ 0x00000004
TKF_CONFIRMHOTKEY	equ 0x00000008
TKF_HOTKEYSOUND		equ 0x00000010
TKF_INDICATOR		equ 0x00000020

if(_WIN32_WINNT GE 0x0600)
AUDIODESCRIPTION	STRUC
cbSize			UINT ?	;; sizeof(AudioDescriptionType)
Enabled			BOOL ?	;; On/Off
Locale			LCID ?	;; locale ID for language
AUDIODESCRIPTION	ENDS
LPAUDIODESCRIPTION	typedef ptr AUDIODESCRIPTION
endif ;; _WIN32_WINNT GE 0x0600

;;
;; Set debug level
;;

;VOID
SetDebugErrorLevel proto _CType \
	      dwLevel : DWORD

;;
;; SetLastErrorEx() types.
;;

SLE_ERROR		equ 0x00000001
SLE_MINORERROR		equ 0x00000002
SLE_WARNING		equ 0x00000003

;VOID
SetLastErrorEx proto _CType \
	     dwErrCode: DWORD,
	       dwType : DWORD


if(WINVER GE 0x0500)
;;
;; Multimonitor API.
;;

MONITOR_DEFAULTTONULL	equ 0x00000000
MONITOR_DEFAULTTOPRIMARY equ 0x00000001
MONITOR_DEFAULTTONEAREST equ 0x00000002

;HMONITOR
MonitorFromPoint proto _CType \
		    pt: POINT,
	       dwFlags: DWORD

;HMONITOR
MonitorFromRect proto _CType \
		  lprc: LPCRECT,
	       dwFlags: DWORD

;HMONITOR
MonitorFromWindow proto _CType \
		  hwnd: HWND,
	       dwFlags: DWORD

MONITORINFOF_PRIMARY	equ 0x00000001

ifndef CCHDEVICENAME
CCHDEVICENAME		equ 32
endif

MONITORINFO		STRUC
cbSize			dd ?
rcMonitor		RECT <>
rcWork			RECT <>
dwFlags			dd ?
MONITORINFO		ENDS
LPMONITORINFO		typedef ptr MONITORINFO

MONITORINFOEXA		STRUC
szDevice		db CCHDEVICENAME dup(?)
MONITORINFOEXA		ENDS
LPMONITORINFOEXA	typedef ptr MONITORINFOEXA
MONITORINFOEXW		STRUC
szDevice		dw CCHDEVICENAME dup(?)
MONITORINFOEXW		ENDS
LPMONITORINFOEXW	typedef ptr MONITORINFOEXW
ifdef _UNICODE
MONITORINFOEX		typedef MONITORINFOEXW
LPMONITORINFOEX		typedef LPMONITORINFOEXW
else
MONITORINFOEX		typedef MONITORINFOEXA
LPMONITORINFOEX		typedef LPMONITORINFOEXA
endif ;; UNICODE

;BOOL
GetMonitorInfoA proto _CType \
	      hMonitor: HMONITOR,
		  lpmi: LPMONITORINFO
;BOOL
GetMonitorInfoW proto _CType \
	      hMonitor: HMONITOR,
		  lpmi: LPMONITORINFO
ifdef _UNICODE
GetMonitorInfo		equ <GetMonitorInfoW>
else
GetMonitorInfo		equ <GetMonitorInfoA>
endif ;; NOT UNICODE

MONITORENUMPROC_T typedef proto \
		      : HMONITOR,
		      : HDC,
		      : LPRECT,
		      : LPARAM
MONITORENUMPROC typedef ptr MONITORENUMPROC_T

;BOOL
EnumDisplayMonitors proto _CType \
		   hdc: HDC,
	      lprcClip: LPCRECT,
	      lpfnEnum: MONITORENUMPROC,
		dwData: LPARAM


ifndef NOWINABLE

;;
;; WinEvents - Active Accessibility hooks
;;

;VOID
NotifyWinEvent proto _CType \
		 event: DWORD,
		  hwnd: HWND,
	      idObject: LONG,
	       idChild: LONG

WINEVENTPROC_T typedef proto _CType \
	 hWinEventHook: HWINEVENTHOOK,
		 event: DWORD,
		  hwnd: HWND,
	      idObject: LONG,
	       idChild: LONG,
	 idEventThread: DWORD,
	 dwmsEventTime: DWORD

WINEVENTPROC typedef ptr WINEVENTPROC_T

if(_WIN32_WINNT GE 0x0501)
;BOOL
IsWinEventHookInstalled proto _CType \
		 event: DWORD

endif ;; _WIN32_WINNT GE 0x0501

;;
;; dwFlags for SetWinEventHook
;;
WINEVENT_OUTOFCONTEXT	equ 0x0000  ;; Events are ASYNC
WINEVENT_SKIPOWNTHREAD	equ 0x0001  ;; Don't call back for events on installer's thread
WINEVENT_SKIPOWNPROCESS equ 0x0002  ;; Don't call back for events on installer's process
WINEVENT_INCONTEXT	equ 0x0004  ;; Events are SYNC, this causes your dll to be injected into every process

;BOOL
UnhookWinEvent proto _CType \
	 hWinEventHook: HWINEVENTHOOK

;;
;; idObject values for WinEventProc and NotifyWinEvent
;;

;;
;; hwnd + idObject can be used with OLEACC.DLL's OleGetObjectFromWindow()
;; to get an interface pointer to the container.  indexChild is the item
;; within the container in question.  Setup a VARIANT with vt VT_I4 and
;; lVal the indexChild and pass that in to all methods.	 Then you
;; are raring to go.
;;


;;
;; Common object IDs (cookies, only for sending WM_GETOBJECT to get at the
;; thing in question).	Positive IDs are reserved for apps (app specific),
;; negative IDs are system things and are global, 0 means "just little old
;; me".
;;
CHILDID_SELF		equ 0
INDEXID_OBJECT		equ 0
INDEXID_CONTAINER	equ 0

;;
;; Reserved IDs for system objects
;;
OBJID_WINDOW		equ 0x00000000
OBJID_SYSMENU		equ 0xFFFFFFFF
OBJID_TITLEBAR		equ 0xFFFFFFFE
OBJID_MENU		equ 0xFFFFFFFD
OBJID_CLIENT		equ 0xFFFFFFFC
OBJID_VSCROLL		equ 0xFFFFFFFB
OBJID_HSCROLL		equ 0xFFFFFFFA
OBJID_SIZEGRIP		equ 0xFFFFFFF9
OBJID_CARET		equ 0xFFFFFFF8
OBJID_CURSOR		equ 0xFFFFFFF7
OBJID_ALERT		equ 0xFFFFFFF6
OBJID_SOUND		equ 0xFFFFFFF5

;;
;; EVENT DEFINITION
;;
EVENT_MIN		equ 0x00000001
EVENT_MAX		equ 0x7FFFFFFF


;;
;;  EVENT_SYSTEM_SOUND
;;  Sent when a sound is played.  Currently nothing is generating this, we
;;  this event when a system sound (for menus, etc) is played.	Apps
;;  generate this, if accessible, when a private sound is played.  For
;;  example, if Mail plays a "New Mail" sound.
;;
;;  System Sounds:
;;  (Generated by PlaySoundEvent in USER itself)
;;	hwnd		is NULL
;;	idObject	is OBJID_SOUND
;;	idChild		is sound child ID if one
;;  App Sounds:
;;  (PlaySoundEvent won't generate notification; up to app)
;;	hwnd + idObject gets interface pointer to Sound object
;;	idChild identifies the sound in question
;;  are going to be cleaning up the SOUNDSENTRY feature in the control panel
;;  and will use this at that time.  Applications implementing WinEvents
;;  are perfectly welcome to use it.  Clients of IAccessible* will simply
;;  turn around and get back a non-visual object that describes the sound.
;;
EVENT_SYSTEM_SOUND	equ 0x0001

;;
;; EVENT_SYSTEM_ALERT
;; System Alerts:
;; (Generated by MessageBox() calls for example)
;;	hwnd		is hwndMessageBox
;;	idObject	is OBJID_ALERT
;; App Alerts:
;; (Generated whenever)
;;	hwnd+idObject gets interface pointer to Alert
;;
EVENT_SYSTEM_ALERT	equ 0x0002

;;
;; EVENT_SYSTEM_FOREGROUND
;; Sent when the foreground (active) window changes, even if it is changing
;; to another window in the same thread as the previous one.
;;	hwnd		is hwndNewForeground
;;	idObject	is OBJID_WINDOW
;;	idChild	   is INDEXID_OBJECT
;;
EVENT_SYSTEM_FOREGROUND equ 0x0003

;;
;; Menu
;;	hwnd		is window (top level window or popup menu window)
;;	idObject	is ID of control (OBJID_MENU, OBJID_SYSMENU, OBJID_SELF for popup)
;;	idChild		is CHILDID_SELF
;;
;; EVENT_SYSTEM_MENUSTART
;; EVENT_SYSTEM_MENUEND
;; For MENUSTART, hwnd+idObject+idChild refers to the control with the menu bar,
;;  or the control bringing up the context menu.
;;
;; Sent when entering into and leaving from menu mode (system, app bar, and
;; track popups).
;;
EVENT_SYSTEM_MENUSTART	equ 0x0004
EVENT_SYSTEM_MENUEND	equ 0x0005

;;
;; EVENT_SYSTEM_MENUPOPUPSTART
;; EVENT_SYSTEM_MENUPOPUPEND
;; Sent when a menu popup comes up and just before it is taken down.  Note
;; that for a call to TrackPopupMenu(), a client will see EVENT_SYSTEM_MENUSTART
;; followed almost immediately by EVENT_SYSTEM_MENUPOPUPSTART for the popup
;; being shown.
;;
;; For MENUPOPUP, hwnd+idObject+idChild refers to the NEW popup coming up, not the
;; parent item which is hierarchical.  You can get the parent menu/popup by
;; asking for the accParent object.
;;
EVENT_SYSTEM_MENUPOPUPSTART equ 0x0006
EVENT_SYSTEM_MENUPOPUPEND equ 0x0007


;;
;; EVENT_SYSTEM_CAPTURESTART
;; EVENT_SYSTEM_CAPTUREEND
;; Sent when a window takes the capture and releases the capture.
;;
EVENT_SYSTEM_CAPTURESTART equ 0x0008
EVENT_SYSTEM_CAPTUREEND equ 0x0009

;;
;; Move Size
;; EVENT_SYSTEM_MOVESIZESTART
;; EVENT_SYSTEM_MOVESIZEEND
;; Sent when a window enters and leaves move-size dragging mode.
;;
EVENT_SYSTEM_MOVESIZESTART equ 0x000A
EVENT_SYSTEM_MOVESIZEEND equ 0x000B

;;
;; Context Help
;; EVENT_SYSTEM_CONTEXTHELPSTART
;; EVENT_SYSTEM_CONTEXTHELPEND
;; Sent when a window enters and leaves context sensitive help mode.
;;
EVENT_SYSTEM_CONTEXTHELPSTART equ 0x000C
EVENT_SYSTEM_CONTEXTHELPEND equ 0x000D

;;
;; Drag & Drop
;; EVENT_SYSTEM_DRAGDROPSTART
;; EVENT_SYSTEM_DRAGDROPEND
;; Send the START notification just before going into drag&drop loop.  Send
;; the END notification just after canceling out.
;; Note that it is up to apps and OLE to generate this, since the system
;; doesn't know.  Like EVENT_SYSTEM_SOUND, it will be a while before this
;; is prevalent.
;;
EVENT_SYSTEM_DRAGDROPSTART equ 0x000E
EVENT_SYSTEM_DRAGDROPEND equ 0x000F

;;
;; Dialog
;; Send the START notification right after the dialog is completely
;;  initialized and visible.  Send the END right before the dialog
;;  is hidden and goes away.
;; EVENT_SYSTEM_DIALOGSTART
;; EVENT_SYSTEM_DIALOGEND
;;
EVENT_SYSTEM_DIALOGSTART equ 0x0010
EVENT_SYSTEM_DIALOGEND	equ 0x0011

;;
;; EVENT_SYSTEM_SCROLLING
;; EVENT_SYSTEM_SCROLLINGSTART
;; EVENT_SYSTEM_SCROLLINGEND
;; Sent when beginning and ending the tracking of a scrollbar in a window,
;; and also for scrollbar controls.
;;
EVENT_SYSTEM_SCROLLINGSTART equ 0x0012
EVENT_SYSTEM_SCROLLINGEND equ 0x0013

;;
;; Alt-Tab Window
;; Send the START notification right after the switch window is initialized
;; and visible.	 Send the END right before it is hidden and goes away.
;; EVENT_SYSTEM_SWITCHSTART
;; EVENT_SYSTEM_SWITCHEND
;;
EVENT_SYSTEM_SWITCHSTART equ 0x0014
EVENT_SYSTEM_SWITCHEND	equ 0x0015

;;
;; EVENT_SYSTEM_MINIMIZESTART
;; EVENT_SYSTEM_MINIMIZEEND
;; Sent when a window minimizes and just before it restores.
;;
EVENT_SYSTEM_MINIMIZESTART equ 0x0016
EVENT_SYSTEM_MINIMIZEEND equ 0x0017

if(_WIN32_WINNT GE 0x0600)
EVENT_SYSTEM_DESKTOPSWITCH equ 0x0020
endif ;; _WIN32_WINNT GE 0x0600

if(_WIN32_WINNT GE 0x0601)
EVENT_SYSTEM_END	equ 0x00FF

EVENT_OEM_DEFINED_START equ 0x0101
EVENT_OEM_DEFINED_END	equ 0x01FF

EVENT_UIA_EVENTID_START equ 0x4E00
EVENT_UIA_EVENTID_END	equ 0x4EFF

EVENT_UIA_PROPID_START	equ 0x7500
EVENT_UIA_PROPID_END	equ 0x75FF
endif ;; _WIN32_WINNT GE 0x0601

if(_WIN32_WINNT GE 0x0501)
EVENT_CONSOLE_CARET	equ 0x4001
EVENT_CONSOLE_UPDATE_REGION equ 0x4002
EVENT_CONSOLE_UPDATE_SIMPLE equ 0x4003
EVENT_CONSOLE_UPDATE_SCROLL equ 0x4004
EVENT_CONSOLE_LAYOUT	equ 0x4005
EVENT_CONSOLE_START_APPLICATION equ 0x4006
EVENT_CONSOLE_END_APPLICATION equ 0x4007
;;
;; Flags for EVENT_CONSOLE_START/END_APPLICATION.
;;
ifdef _WIN64
CONSOLE_APPLICATION_16BIT equ 0x0000
else
CONSOLE_APPLICATION_16BIT equ 0x0001
endif
;;
;; Flags for EVENT_CONSOLE_CARET
;;
CONSOLE_CARET_SELECTION equ 0x0001
CONSOLE_CARET_VISIBLE	equ 0x0002
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0601)
EVENT_CONSOLE_END	equ 0x40FF
endif ;; _WIN32_WINNT GE 0x0601

;;
;; Object events
;;
;; The system AND apps generate these.	The system generates these for
;; real windows.  Apps generate these for objects within their window which
;; act like a separate control, e.g. an item in a list view.
;;
;; When the system generate them, dwParam2 is always WMOBJID_SELF.  When
;; apps generate them, apps put the has-meaning-to-the-app-only ID value
;; in dwParam2.
;; For all events, if you want detailed accessibility information, callers
;; should
;;	* Call AccessibleObjectFromWindow() with the hwnd, idObject parameters
;;	    of the event, and IID_IAccessible as the REFIID, to get back an
;;	    IAccessible* to talk to
;;	* Initialize and fill in a VARIANT as VT_I4 with lVal the idChild
;;	    parameter of the event.
;;	* If idChild isn't zero, call get_accChild() in the container to see
;;	    if the child is an object in its own right.	 If so, you will get
;;	    back an IDispatch* object for the child.  You should release the
;;	    parent, and call QueryInterface() on the child object to get its
;;	    IAccessible*.  Then you talk directly to the child.	 Otherwise,
;;	    if get_accChild() returns you nothing, you should continue to
;;	    use the child VARIANT.  You will ask the container for the properties
;;	    of the child identified by the VARIANT.  In other words, the
;;	    child in this case is accessible but not a full-blown object.
;;	    Like a button on a titlebar which is 'small' and has no children.
;;

;;
;; For all EVENT_OBJECT events,
;;	hwnd is the dude to Send the WM_GETOBJECT message to (unless NULL,
;;	    see above for system things)
;;	idObject is the ID of the object that can resolve any queries a
;;	    client might have.	It's a way to deal with windowless controls,
;;	    controls that are just drawn on the screen in some larger parent
;;	    window (like SDM), or standard frame elements of a window.
;;	idChild is the piece inside of the object that is affected.  This
;;	    allows clients to access things that are too small to have full
;;	    blown objects in their own right.  Like the thumb of a scrollbar.
;;	    The hwnd/idObject pair gets you to the container, the dude you
;;	    probably want to talk to most of the time anyway.  The idChild
;;	    can then be passed into the acc properties to get the name/value
;;	    of it as needed.
;;
;; Example #1:
;;	System propagating a listbox selection change
;;	EVENT_OBJECT_SELECTION
;;	    hwnd == listbox hwnd
;;	    idObject == OBJID_WINDOW
;;	    idChild == new selected item, or CHILDID_SELF if
;;		nothing now selected within container.
;;	Word '97 propagating a listbox selection change
;;	    hwnd == SDM window
;;	    idObject == SDM ID to get at listbox 'control'
;;	    idChild == new selected item, or CHILDID_SELF if
;;		nothing
;;
;; Example #2:
;;	System propagating a menu item selection on the menu bar
;;	EVENT_OBJECT_SELECTION
;;	    hwnd == top level window
;;	    idObject == OBJID_MENU
;;	    idChild == ID of child menu bar item selected
;;
;; Example #3:
;;	System propagating a dropdown coming off of said menu bar item
;;	EVENT_OBJECT_CREATE
;;	    hwnd == popup item
;;	    idObject == OBJID_WINDOW
;;	    idChild == CHILDID_SELF
;;
;; Example #4:
;;
;; For EVENT_OBJECT_REORDER, the object referred to by hwnd/idObject is the
;; PARENT container in which the zorder is occurring.  This is because if
;; one child is zordering, all of them are changing their relative zorder.
;;
EVENT_OBJECT_CREATE	equ 0x8000  ;; hwnd + ID + idChild is created item
EVENT_OBJECT_DESTROY	equ 0x8001  ;; hwnd + ID + idChild is destroyed item
EVENT_OBJECT_SHOW	equ 0x8002  ;; hwnd + ID + idChild is shown item
EVENT_OBJECT_HIDE	equ 0x8003  ;; hwnd + ID + idChild is hidden item
EVENT_OBJECT_REORDER	equ 0x8004  ;; hwnd + ID + idChild is parent of zordering children
;;
;; NOTE:
;; Minimize the number of notifications!
;;
;; When you are hiding a parent object, obviously all child objects are no
;; longer visible on screen.  They still have the same "visible" status,
;; but are not truly visible.  Hence do not send HIDE notifications for the
;; children also.  One implies all.  The same goes for SHOW.
;;


EVENT_OBJECT_FOCUS	equ 0x8005  ;; hwnd + ID + idChild is focused item
EVENT_OBJECT_SELECTION	equ 0x8006  ;; hwnd + ID + idChild is selected item (if only one), or idChild is OBJID_WINDOW if complex
EVENT_OBJECT_SELECTIONADD equ 0x8007  ;; hwnd + ID + idChild is item added
EVENT_OBJECT_SELECTIONREMOVE equ 0x8008	 ;; hwnd + ID + idChild is item removed
EVENT_OBJECT_SELECTIONWITHIN equ 0x8009	 ;; hwnd + ID + idChild is parent of changed selected items

;;
;; NOTES:
;; There is only one "focused" child item in a parent.	This is the place
;; keystrokes are going at a given moment.  Hence only send a notification
;; about where the NEW focus is going.	A NEW item getting the focus already
;; implies that the OLD item is losing it.
;;
;; SELECTION however can be multiple.  Hence the different SELECTION
;; notifications.  Here's when to use each:
;;
;; (1) Send a SELECTION notification in the simple single selection
;;     case (like the focus) when the item with the selection is
;;     merely moving to a different item within a container.  hwnd + ID
;;     is the container control, idChildItem is the new child with the
;;     selection.
;;
;; (2) Send a SELECTIONADD notification when a new item has simply been added
;;     to the selection within a container.  This is appropriate when the
;;     number of newly selected items is very small.  hwnd + ID is the
;;     container control, idChildItem is the new child added to the selection.
;;
;; (3) Send a SELECTIONREMOVE notification when a new item has simply been
;;     removed from the selection within a container.  This is appropriate
;;     when the number of newly selected items is very small, just like
;;     SELECTIONADD.  hwnd + ID is the container control, idChildItem is the
;;     new child removed from the selection.
;;
;; (4) Send a SELECTIONWITHIN notification when the selected items within a
;;     control have changed substantially.  Rather than propagate a large
;;     number of changes to reflect removal for some items, addition of
;;     others, just tell somebody who cares that a lot happened.  It will
;;     be faster an easier for somebody watching to just turn around and
;;     query the container control what the new bunch of selected items
;;     are.
;;

EVENT_OBJECT_STATECHANGE equ 0x800A  ;; hwnd + ID + idChild is item w/ state change
;;
;; Examples of when to send an EVENT_OBJECT_STATECHANGE include
;;	* It is being enabled/disabled (USER does for windows)
;;	* It is being pressed/released (USER does for buttons)
;;	* It is being checked/unchecked (USER does for radio/check buttons)
;;
EVENT_OBJECT_LOCATIONCHANGE equ 0x800B	;; hwnd + ID + idChild is moved/sized item

;;
;; Note:
;; A LOCATIONCHANGE is not sent for every child object when the parent
;; changes shape/moves.	 Send one notification for the topmost object
;; that is changing.  For example, if the user resizes a top level window,
;; USER will generate a LOCATIONCHANGE for it, but not for the menu bar,
;; title bar, scrollbars, etc.	that are also changing shape/moving.
;;
;; In other words, it only generates LOCATIONCHANGE notifications for
;; real windows that are moving/sizing.	 It will not generate a LOCATIONCHANGE
;; for every non-floating child window when the parent moves (the children are
;; logically moving also on screen, but not relative to the parent).
;;
;; Now, if the app itself resizes child windows as a result of being
;; sized, USER will generate LOCATIONCHANGEs for those dudes also because
;; it doesn't know better.
;;
;; Note also that USER will generate LOCATIONCHANGE notifications for two
;; non-window sys objects:
;;	(1) System caret
;;	(2) Cursor
;;

EVENT_OBJECT_NAMECHANGE equ 0x800C  ;; hwnd + ID + idChild is item w/ name change
EVENT_OBJECT_DESCRIPTIONCHANGE equ 0x800D  ;; hwnd + ID + idChild is item w/ desc change
EVENT_OBJECT_VALUECHANGE equ 0x800E  ;; hwnd + ID + idChild is item w/ value change
EVENT_OBJECT_PARENTCHANGE equ 0x800F  ;; hwnd + ID + idChild is item w/ new parent
EVENT_OBJECT_HELPCHANGE equ 0x8010  ;; hwnd + ID + idChild is item w/ help change
EVENT_OBJECT_DEFACTIONCHANGE equ 0x8011	 ;; hwnd + ID + idChild is item w/ def action change
EVENT_OBJECT_ACCELERATORCHANGE equ 0x8012  ;; hwnd + ID + idChild is item w/ keybd accel change

if(_WIN32_WINNT GE 0x0600)
EVENT_OBJECT_INVOKED	equ 0x8013  ;; hwnd + ID + idChild is item invoked
EVENT_OBJECT_TEXTSELECTIONCHANGED equ 0x8014  ;; hwnd + ID + idChild is item w? test selection change
;;
;; EVENT_OBJECT_CONTENTSCROLLED
;; Sent when ending the scrolling of a window object.
;;
;; Unlike the similar event (EVENT_SYSTEM_SCROLLEND), this event will be
;; associated with the scrolling window itself. There is no difference
;; between horizontal or vertical scrolling.
;;
;; This event should be posted whenever scroll action is completed, including
;; when it is scrolled by scroll bars, mouse wheel, or keyboard navigations.
;;
;;   example:
;;	    hwnd == window that is scrolling
;;	    idObject == OBJID_CLIENT
;;	    idChild == CHILDID_SELF
;;
EVENT_OBJECT_CONTENTSCROLLED equ 0x8015
endif ;; _WIN32_WINNT GE 0x0600

if(_WIN32_WINNT GE 0x0601)
EVENT_SYSTEM_ARRANGMENTPREVIEW equ 0x8016
endif ;; _WIN32_WINNT GE 0x0601

if(_WIN32_WINNT GE 0x0601)
EVENT_OBJECT_END	equ 0x80FF

EVENT_AIA_START		equ 0xA000
EVENT_AIA_END		equ 0xAFFF
endif ;; _WIN32_WINNT GE 0x0601

;;
;; Child IDs
;;

;;
;; System Sounds (idChild of system SOUND notification)
;;
SOUND_SYSTEM_STARTUP	equ 1
SOUND_SYSTEM_SHUTDOWN	equ 2
SOUND_SYSTEM_BEEP	equ 3
SOUND_SYSTEM_ERROR	equ 4
SOUND_SYSTEM_QUESTION	equ 5
SOUND_SYSTEM_WARNING	equ 6
SOUND_SYSTEM_INFORMATION equ 7
SOUND_SYSTEM_MAXIMIZE	equ 8
SOUND_SYSTEM_MINIMIZE	equ 9
SOUND_SYSTEM_RESTOREUP	equ 10
SOUND_SYSTEM_RESTOREDOWN equ 11
SOUND_SYSTEM_APPSTART	equ 12
SOUND_SYSTEM_FAULT	equ 13
SOUND_SYSTEM_APPEND	equ 14
SOUND_SYSTEM_MENUCOMMAND equ 15
SOUND_SYSTEM_MENUPOPUP	equ 16
CSOUND_SYSTEM		equ 16

;;
;; System Alerts (indexChild of system ALERT notification)
;;
ALERT_SYSTEM_INFORMATIONAL equ 1       ;; MB_INFORMATION
ALERT_SYSTEM_WARNING	equ 2	    ;; MB_WARNING
ALERT_SYSTEM_ERROR	equ 3	    ;; MB_ERROR
ALERT_SYSTEM_QUERY	equ 4	    ;; MB_QUESTION
ALERT_SYSTEM_CRITICAL	equ 5	    ;; HardSysErrBox
CALERT_SYSTEM		equ 6

;HWINEVENTHOOK
SetWinEventHook proto _CType \
	      eventMin: DWORD,
	      eventMax: DWORD,
      hmodWinEventProc: HMODULE,
       pfnWinEventProc: WINEVENTPROC,
	     idProcess: DWORD,
	      idThread: DWORD,
	       dwFlags: DWORD

;BOOL
UnhookWinEvent proto _CType \
	 hWinEventHook: HWINEVENTHOOK

;;
;; dwFlags for SetWinEventHook
;;
WINEVENT_OUTOFCONTEXT	equ 0x0000  ;; Events are ASYNC
WINEVENT_SKIPOWNTHREAD	equ 0x0001  ;; Don't call back for events on installer's thread
WINEVENT_SKIPOWNPROCESS equ 0x0002  ;; Don't call back for events on installer's process
WINEVENT_INCONTEXT	equ 0x0004  ;; Events are SYNC, this causes your dll to be injected into every process

GUITHREADINFO		STRUC
cbSize			dd ?
flags			dd ?
hwndActive		HWND ?
hwndFocus		HWND ?
hwndCapture		HWND ?
hwndMenuOwner		HWND ?
hwndMoveSize		HWND ?
hwndCaret		HWND ?
rcCaret			RECT <>
GUITHREADINFO		ENDS
PGUITHREADINFO		typedef ptr GUITHREADINFO

GUI_CARETBLINKING	equ 0x00000001
GUI_INMOVESIZE		equ 0x00000002
GUI_INMENUMODE		equ 0x00000004
GUI_SYSTEMMENUMODE	equ 0x00000008
GUI_POPUPMENUMODE	equ 0x00000010
if(_WIN32_WINNT GE 0x0501)
ifdef _WIN64
GUI_16BITTASK		equ 0x00000000
else
GUI_16BITTASK		equ 0x00000020
endif
endif ;; _WIN32_WINNT GE 0x0501

if(_WIN32_WINNT GE 0x0600)
USER_DEFAULT_SCREEN_DPI equ 96
;BOOL
SetProcessDPIAware proto _CType
;BOOL
IsProcessDPIAware proto _CType
endif ;; _WIN32_WINNT GE 0x0600

;BOOL
GetGUIThreadInfo proto _CType \
	      idThread: DWORD,
		  pgui: PGUITHREADINFO
;BOOL
BlockInput proto _CType \
	      fBlockIt: BOOL


;UINT
GetWindowModuleFileNameA proto _CType \
		  hwnd: HWND,
	   pszFileName: LPSTR,
	cchFileNameMax: UINT
;UINT
GetWindowModuleFileNameW proto _CType \
		  hwnd: HWND,
	   pszFileName: LPWSTR,
	cchFileNameMax: UINT
ifdef _UNICODE
GetWindowModuleFileName equ <GetWindowModuleFileNameW>
else
GetWindowModuleFileName equ <GetWindowModuleFileNameA>
endif ;; NOT UNICODE


STATE_SYSTEM_UNAVAILABLE equ 0x00000001	 ;; Disabled
STATE_SYSTEM_SELECTED	equ 0x00000002
STATE_SYSTEM_FOCUSED	equ 0x00000004
STATE_SYSTEM_PRESSED	equ 0x00000008
STATE_SYSTEM_CHECKED	equ 0x00000010
STATE_SYSTEM_MIXED	equ 0x00000020	;; 3-state checkbox or toolbar button
STATE_SYSTEM_READONLY	equ 0x00000040
STATE_SYSTEM_HOTTRACKED equ 0x00000080
STATE_SYSTEM_DEFAULT	equ 0x00000100
STATE_SYSTEM_EXPANDED	equ 0x00000200
STATE_SYSTEM_COLLAPSED	equ 0x00000400
STATE_SYSTEM_BUSY	equ 0x00000800
STATE_SYSTEM_FLOATING	equ 0x00001000	;; Children "owned" not "contained" by parent
STATE_SYSTEM_MARQUEED	equ 0x00002000
STATE_SYSTEM_ANIMATED	equ 0x00004000
STATE_SYSTEM_INVISIBLE	equ 0x00008000
STATE_SYSTEM_OFFSCREEN	equ 0x00010000
STATE_SYSTEM_SIZEABLE	equ 0x00020000
STATE_SYSTEM_MOVEABLE	equ 0x00040000
STATE_SYSTEM_SELFVOICING equ 0x00080000
STATE_SYSTEM_FOCUSABLE	equ 0x00100000
STATE_SYSTEM_SELECTABLE equ 0x00200000
STATE_SYSTEM_LINKED	equ 0x00400000
STATE_SYSTEM_TRAVERSED	equ 0x00800000
STATE_SYSTEM_MULTISELECTABLE equ 0x01000000  ;; Supports multiple selection
STATE_SYSTEM_EXTSELECTABLE equ 0x02000000  ;; Supports extended selection
STATE_SYSTEM_ALERT_LOW	equ 0x04000000	;; This information is of low priority
STATE_SYSTEM_ALERT_MEDIUM equ 0x08000000  ;; This information is of medium priority
STATE_SYSTEM_ALERT_HIGH equ 0x10000000	;; This information is of high priority
STATE_SYSTEM_VALID	equ 0x1FFFFFFF

CCHILDREN_TITLEBAR	equ 5
CCHILDREN_SCROLLBAR	equ 5

;;
;; Information about the global cursor.
;;
CURSORINFO		STRUC
cbSize			dd ?
flags			dd ?
hCursor			HCURSOR ?
ptScreenPos		POINT <>
CURSORINFO		ENDS
PCURSORINFO		typedef ptr CURSORINFO
LPCURSORINFO		typedef ptr CURSORINFO

CURSOR_SHOWING		equ 0x00000001

;BOOL
GetCursorInfo proto _CType \
		  pci : PCURSORINFO

;;
;; Window information snapshot
;;
WINDOWINFO		STRUC
cbSize			dd ?
rcWindow		RECT <>
rcClient		RECT <>
dwStyle			dd ?
dwExStyle		dd ?
dwOtherStuff		dd ?
cxWindowBorders		UINT ?
cyWindowBorders		UINT ?
atomWindowType		ATOM ?
wCreatorVersion		dw ?
WINDOWINFO		ENDS
PWINDOWINFO		typedef ptr WINDOWINFO
LPWINDOWINFO		typedef ptr WINDOWINFO

WS_ACTIVECAPTION	equ 0x0001

;BOOL
GetWindowInfo proto _CType \
		  hwnd: HWND,
		  pwi : PWINDOWINFO

;;
;; Titlebar information.
;;
TITLEBARINFO		STRUC
cbSize			dd ?
rcTitleBar		RECT <>
rgstate			dd CCHILDREN_TITLEBAR+1 dup(?)
TITLEBARINFO		ENDS
PTITLEBARINFO		typedef ptr TITLEBARINFO
LPTITLEBARINFO		typedef ptr TITLEBARINFO

;BOOL
GetTitleBarInfo proto _CType \
		  hwnd: HWND,
		   pti: PTITLEBARINFO

if(WINVER GE 0x0600)
TITLEBARINFOEX		STRUC
cbSize			dd ?
rcTitleBar		RECT <>
rgstate			dd CCHILDREN_TITLEBAR + 1 dup(?)
rgrect			RECT CCHILDREN_TITLEBAR + 1 dup(<>)
TITLEBARINFOEX		ENDS
PTITLEBARINFOEX		typedef ptr TITLEBARINFOEX
LPTITLEBARINFOEX	typedef ptr TITLEBARINFOEX
endif ;; WINVER GE 0x0600
;;
;; Menubar information
;;
MENUBARINFO		STRUC
cbSize			dd ?
rcBar			RECT <> ;; rect of bar, popup, item
hMenu			HMENU ? ;; real menu handle of bar, popup
hwndMenu		HWND ?	;; hwnd of item submenu if one
MENUBARINFO_R0		RECORD \
 fBarFocused:	1,	;; bar, popup has the focus
 fFocused:	1	;; item has the focus
r0			MENUBARINFO_R0 <>
MENUBARINFO		ENDS
PMENUBARINFO		typedef ptr MENUBARINFO
LPMENUBARINFO		typedef ptr MENUBARINFO

;BOOL
GetMenuBarInfo proto _CType \
		  hwnd: HWND,
	      idObject: LONG,
		idItem: LONG,
		  pmbi: PMENUBARINFO

;;
;; Scrollbar information
;;
SCROLLBARINFO		STRUC
cbSize			dd ?
rcScrollBar		RECT <>
dxyLineButton		SINT ?
xyThumbTop		SINT ?
xyThumbBottom		SINT ?
bogus			SINT ?
rgstate			dd CCHILDREN_SCROLLBAR+1 dup(?)
SCROLLBARINFO		ENDS
PSCROLLBARINFO		typedef ptr SCROLLBARINFO
LPSCROLLBARINFO		typedef ptr SCROLLBARINFO

;BOOL
GetScrollBarInfo proto _CType \
		  hwnd: HWND,
	      idObject: LONG,
		 psbi : PSCROLLBARINFO

;;
;; Combobox information
;;
COMBOBOXINFO		STRUC
cbSize			dd ?
rcItem			RECT <>
rcButton		RECT <>
stateButton		dd ?
hwndCombo		HWND ?
hwndItem		HWND ?
hwndList		HWND ?
COMBOBOXINFO		ENDS
PCOMBOBOXINFO		typedef ptr COMBOBOXINFO
LPCOMBOBOXINFO		typedef ptr COMBOBOXINFO

;BOOL
GetComboBoxInfo proto _CType \
	     hwndCombo: HWND,
		 pcbi : PCOMBOBOXINFO

;;
;; The "real" ancestor window
;;
GA_MIC			equ 1
GA_PARENT		equ 1
GA_ROOT			equ 2
GA_ROOTOWNER		equ 3
GA_MAC			equ 4

;HWND
GetAncestor proto _CType \
		  hwnd: HWND,
	      gaFlags : UINT


;;
;; This gets the REAL child window at the point.  If it is in the dead
;; space of a group box, it will try a sibling behind it.  But static
;; fields will get returned.  In other words, it is kind of a cross between
;; ChildWindowFromPointEx and WindowFromPoint.
;;
;HWND
RealChildWindowFromPoint proto _CType \
	    hwndParent: HWND,
 ptParentClientCoords : POINT


;;
;; This gets the name of the window TYPE, not class.  This allows us to
;; recognize ThunderButton32 et al.
;;
;UINT
RealGetWindowClassA proto _CType \
		  hwnd: HWND,
	       pszType: LPTSTR,
	      cchType : UINT
;;
;; This gets the name of the window TYPE, not class.  This allows us to
;; recognize ThunderButton32 et al.
;;
;UINT
RealGetWindowClassW proto _CType \
		  hwnd: HWND,
	       pszType: LPTSTR,
	      cchType : UINT
ifdef _UNICODE
RealGetWindowClass	equ <RealGetWindowClassW>
else
RealGetWindowClass	equ <RealGetWindowClassA>
endif ;; NOT UNICODE

;;
;; Alt-Tab Switch window information.
;;
ALTTABINFO		STRUC
cbSize			dd ?
cItems			SINT ?
cColumns		SINT ?
cRows			SINT ?
iColFocus		SINT ?
iRowFocus		SINT ?
cxItem			SINT ?
cyItem			SINT ?
ptStart			POINT <>
ALTTABINFO		ENDS
PALTTABINFO		typedef ptr ALTTABINFO
LPALTTABINFO		typedef ptr ALTTABINFO

;BOOL
GetAltTabInfoA proto _CType \
		  hwnd: HWND,
		 iItem: SINT,
		  pati: PALTTABINFO,
	   pszItemText: LPTSTR,
	  cchItemText : UINT
;BOOL
GetAltTabInfoW proto _CType \
		  hwnd: HWND,
		 iItem: SINT,
		  pati: PALTTABINFO,
	   pszItemText: LPTSTR,
	  cchItemText : UINT
ifdef _UNICODE
GetAltTabInfo		equ <GetAltTabInfoW>
else
GetAltTabInfo		equ <GetAltTabInfoA>
endif

;;
;; Listbox information.
;; Returns the number of items per row.
;;
;DWORD
GetListBoxInfo proto _CType \
		 hwnd : HWND

endif ;; NOWINABLE
endif ;; WINVER GE 0x0500


if(_WIN32_WINNT GE 0x0500)
;BOOL
LockWorkStation proto _CType
endif

if(_WIN32_WINNT GE 0x0500)

;BOOL
UserHandleGrantAccess proto _CType \
	   hUserHandle: HANDLE,
		  hJob: HANDLE

endif ;; _WIN32_WINNT GE 0x0500

if(_WIN32_WINNT GE 0x0501)

;;
;; Raw Input Messages.
;;

HRAWINPUT		typedef HANDLE

;;
;; WM_INPUT wParam
;;

;;
;; Use this macro to get the input code from wParam.
;;
GET_RAWINPUT_CODE_WPARAM macro wParam
	exitm<((wParam) AND 0xff)>
	endm

;;
;; The input is in the regular message flow,
;; the app is required to call DefWindowProc
;; so that the system can perform clean ups.
;;
RIM_INPUT		equ 0

;;
;; The input is sink only. The app is expected
;; to behave nicely.
;;
RIM_INPUTSINK		equ 1


;;
;; Raw Input data header
;;
RAWINPUTHEADER		STRUC
dwType			dd ?
dwSize			dd ?
hDevice			HANDLE ?
wParam			WPARAM ?
RAWINPUTHEADER		ENDS
PRAWINPUTHEADER		typedef ptr RAWINPUTHEADER
LPRAWINPUTHEADER	typedef ptr RAWINPUTHEADER

;;
;; Type of the raw input
;;
RIM_TYPEMOUSE		equ 0
RIM_TYPEKEYBOARD	equ 1
RIM_TYPEHID		equ 2

;;
;; Raw format of the mouse input
;;
RAWMOUSE		STRUC
usFlags			dw ?
UNION
 ulButtons		dd ?
 STRUC
  usButtonFlags		dw ?
  usButtonData		dw ?
 ENDS
ENDS
ulRawButtons		dd ?
lLastX			LONG ?
lLastY			LONG ?
ulExtraInformation	ULONG ?
RAWMOUSE		ENDS
PRAWMOUSE		typedef ptr RAWMOUSE
LPRAWMOUSE		typedef ptr RAWMOUSE

;;
;; Define the mouse button state indicators.
;;

RI_MOUSE_LEFT_BUTTON_DOWN   equ 0x0001	;; Left Button changed to down.
RI_MOUSE_LEFT_BUTTON_UP	    equ 0x0002	;; Left Button changed to up.
RI_MOUSE_RIGHT_BUTTON_DOWN  equ 0x0004	;; Right Button changed to down.
RI_MOUSE_RIGHT_BUTTON_UP    equ 0x0008	;; Right Button changed to up.
RI_MOUSE_MIDDLE_BUTTON_DOWN equ 0x0010	;; Middle Button changed to down.
RI_MOUSE_MIDDLE_BUTTON_UP   equ 0x0020	;; Middle Button changed to up.

RI_MOUSE_BUTTON_1_DOWN	equ RI_MOUSE_LEFT_BUTTON_DOWN
RI_MOUSE_BUTTON_1_UP	equ RI_MOUSE_LEFT_BUTTON_UP
RI_MOUSE_BUTTON_2_DOWN	equ RI_MOUSE_RIGHT_BUTTON_DOWN
RI_MOUSE_BUTTON_2_UP	equ RI_MOUSE_RIGHT_BUTTON_UP
RI_MOUSE_BUTTON_3_DOWN	equ RI_MOUSE_MIDDE_BUTTON_DOWN
RI_MOUSE_BUTTON_3_UP	equ RI_MOUSE_MIDDE_BUTTON_UP

RI_MOUSE_BUTTON_4_DOWN	equ 0x0040
RI_MOUSE_BUTTON_4_UP	equ 0x0080
RI_MOUSE_BUTTON_5_DOWN	equ 0x0100
RI_MOUSE_BUTTON_5_UP	equ 0x0200

;;
;; If usButtonFlags has RI_MOUSE_WHEEL, the wheel delta is stored in usButtonData.
;; Take it as a signed value.
;;
RI_MOUSE_WHEEL		equ 0x0400

;;
;; Define the mouse indicator flags.
;;
MOUSE_MOVE_RELATIVE	equ 0
MOUSE_MOVE_ABSOLUTE	equ 1
MOUSE_VIRTUAL_DESKTOP	equ 0x02  ;; the coordinates are mapped to the virtual desktop
MOUSE_ATTRIBUTES_CHANGED equ 0x04  ;; requery for mouse attributes
if(WINVER GE 0x0600)
MOUSE_MOVE_NOCOALESCE	equ 0x08  ;; do not coalesce mouse moves
endif ;; WINVER GE 0x0600

;;
;; Raw format of the keyboard input
;;
RAWKEYBOARD		STRUC
MakeCode		dw ?
Flags			dw ?
Reserved		dw ?
VKey			dw ?
Message			UINT ?
ExtraInformation	ULONG ?
RAWKEYBOARD		ENDS
PRAWKEYBOARD		typedef ptr RAWKEYBOARD
LPRAWKEYBOARD		typedef ptr RAWKEYBOARD

;;
;; Define the keyboard overrun MakeCode.
;;

KEYBOARD_OVERRUN_MAKE_CODE equ 0xFF

;;
;; Define the keyboard input data Flags.
;;
RI_KEY_MAKE		equ 0
RI_KEY_BREAK		equ 1
RI_KEY_E0		equ 2
RI_KEY_E1		equ 4
RI_KEY_TERMSRV_SET_LED	equ 8
RI_KEY_TERMSRV_SHADOW	equ 0x10


;;
;; Raw format of the input from Human Input Devices
;;
RAWHID			STRUC
dwSizeHid		dd ?	;; byte size of each report
dwCount			dd ?	;; number of input packed
bRawData		db ?
RAWHID			ENDS
PRAWHID			typedef ptr RAWHID
LPRAWHID		typedef ptr RAWHID

;;
;; RAWINPUT data structure.
;;
RAWINPUT		STRUC
header			RAWINPUTHEADER <>
UNION data
 mouse			RAWMOUSE <>
 keyboard		RAWKEYBOARD <>
 hid			RAWHID <>
ENDS
RAWINPUT		ENDS
PRAWINPUT		typedef ptr RAWINPUT
LPRAWINPUT		typedef ptr RAWINPUT

ifdef _WIN64
RAWINPUT_ALIGN macro x
	exitm<(((x) + sizeof(QWORD) - 1) AND NOT (sizeof(QWORD) - 1))>
	endm
else   ;; _WIN64
RAWINPUT_ALIGN macro x
	exitm<(((x) + sizeof(DWORD) - 1) AND NOT (sizeof(DWORD) - 1))>
	endm
endif  ;; _WIN64

NEXTRAWINPUTBLOCK macro p
	exitm<RAWINPUT_ALIGN(p + p.header.dwSize)>
	endm

;;
;; Flags for GetRawInputData
;;

RID_INPUT		equ 0x10000003
RID_HEADER		equ 0x10000005

;UINT
GetRawInputData proto _CType \
	     hRawInput: HRAWINPUT,
	     uiCommand: UINT,
		 pData: LPVOID,
	       pcbSize: PUINT,
	  cbSizeHeader: UINT

;;
;; Raw Input Device Information
;;
RIDI_PREPARSEDDATA	equ 0x20000005
RIDI_DEVICENAME		equ 0x20000007	;; the return valus is the character length, not the byte size
RIDI_DEVICEINFO		equ 0x2000000b

RID_DEVICE_INFO_MOUSE	STRUC
dwId			dd ?
dwNumberOfButtons	dd ?
dwSampleRate		dd ?
fHasHorizontalWheel	BOOL ?
RID_DEVICE_INFO_MOUSE	ENDS
PRID_DEVICE_INFO_MOUSE	typedef ptr RID_DEVICE_INFO_MOUSE

RID_DEVICE_INFO_KEYBOARD  STRUC
dwType			dd ?
dwSubType		dd ?
dwKeyboardMode		dd ?
dwNumberOfFunctionKeys	dd ?
dwNumberOfIndicators	dd ?
dwNumberOfKeysTotal	dd ?
RID_DEVICE_INFO_KEYBOARD ENDS
PRID_DEVICE_INFO_KEYBOARD typedef ptr RID_DEVICE_INFO_KEYBOARD

RID_DEVICE_INFO_HID	STRUC
dwVendorId		dd ?
dwProductId		dd ?
dwVersionNumber		dd ?
usUsagePage		dw ?
usUsage			dw ?
RID_DEVICE_INFO_HID	ENDS
PRID_DEVICE_INFO_HID	typedef ptr RID_DEVICE_INFO_HID

RID_DEVICE_INFO		STRUC
cbSize			dd ?
dwType			dd ?
UNION
 mouse			RID_DEVICE_INFO_MOUSE <>
 keyboard		RID_DEVICE_INFO_KEYBOARD <>
 hid			RID_DEVICE_INFO_HID <>
ENDS
RID_DEVICE_INFO		ENDS
PRID_DEVICE_INFO	typedef ptr RID_DEVICE_INFO
LPRID_DEVICE_INFO	typedef ptr RID_DEVICE_INFO

;UINT
GetRawInputDeviceInfoA proto _CType \
	       hDevice: HANDLE,
	     uiCommand: UINT,
		 pData: LPVOID,
	       pcbSize: PUINT
GetRawInputDeviceInfoW proto _CType \
	       hDevice: HANDLE,
	     uiCommand: UINT,
		 pData: LPVOID,
	       pcbSize: PUINT
ifdef _UNICODE
GetRawInputDeviceInfo	equ <GetRawInputDeviceInfoW>
else
GetRawInputDeviceInfo	equ <GetRawInputDeviceInfoA>
endif ;; NOT UNICODE


;UINT
GetRawInputBuffer proto _CType \
		 pData: PRAWINPUT,
	       pcbSize: PUINT,
	  cbSizeHeader: UINT

;;
;; Raw Input request APIs
;;
RAWINPUTDEVICE		STRUC
usUsagePage		dw ?	;; Toplevel collection UsagePage
usUsage			dw ?	;; Toplevel collection Usage
dwFlags			dd ?
hwndTarget		HWND ?	;; Target hwnd. NULL = follows keyboard focus
RAWINPUTDEVICE		ENDS
PRAWINPUTDEVICE		typedef ptr RAWINPUTDEVICE
LPRAWINPUTDEVICE	typedef ptr RAWINPUTDEVICE
PCRAWINPUTDEVICE	typedef ptr RAWINPUTDEVICE

RIDEV_REMOVE		equ 0x00000001
RIDEV_EXCLUDE		equ 0x00000010
RIDEV_PAGEONLY		equ 0x00000020
RIDEV_NOLEGACY		equ 0x00000030
RIDEV_INPUTSINK		equ 0x00000100
RIDEV_CAPTUREMOUSE	equ 0x00000200	;; effective when mouse nolegacy is specified, otherwise it would be an error
RIDEV_NOHOTKEYS		equ 0x00000200	;; effective for keyboard.
RIDEV_APPKEYS		equ 0x00000400	;; effective for keyboard.
if(_WIN32_WINNT GE 0x0501)
RIDEV_EXINPUTSINK	equ 0x00001000
RIDEV_DEVNOTIFY		equ 0x00002000
endif ;; _WIN32_WINNT GE 0x0501
RIDEV_EXMODEMASK	equ 0x000000F0

RIDEV_EXMODE macro m
	exitm<((m) AND RIDEV_EXMODEMASK)>
	endm

if(_WIN32_WINNT GE 0x0501)
;;
;; Flags for the WM_INPUT_DEVICE_CHANGE message.
;;
GIDC_ARRIVAL		equ 1
GIDC_REMOVAL		equ 2
endif ;; _WIN32_WINNT GE 0x0501

if (_WIN32_WINNT GE 0x0601)
GET_DEVICE_CHANGE_WPARAM macro wParam
	exitm<(LOWORD(wParam))>
	endm
elseif (_WIN32_WINNT GE 0x0501)
GET_DEVICE_CHANGE_LPARAM macro lParam
	exitm<(LOWORD(lParam))>
	endm
endif ;; (_WIN32_WINNT GE 0x0601)

;BOOL
RegisterRawInputDevices proto _CType \
      pRawInputDevices: PCRAWINPUTDEVICE,
	  uiNumDevices: UINT,
		cbSize: UINT
;UINT
GetRegisteredRawInputDevices proto _CType \
      pRawInputDevices: PCRAWINPUTDEVICE,
	 puiNumDevices: PUINT,
		cbSize: UINT

RAWINPUTDEVICELIST	STRUC
hDevice			HANDLE ?
dwType			dd ?
RAWINPUTDEVICELIST	ENDS
PRAWINPUTDEVICELIST	typedef ptr RAWINPUTDEVICELIST

;UINT
GetRawInputDeviceList proto _CType \
   pRawInputDeviceList: PRAWINPUTDEVICELIST,
	 puiNumDevices: PUINT,
		cbSize: UINT

;LRESULT
DefRawInputProc proto _CType \
	    paRawInput: ptr PRAWINPUT,
		nInput: SINT,
	  cbSizeHeader: UINT

endif ;; _WIN32_WINNT GE 0x0501


if(WINVER GE 0x0600)

;;
;; Message Filter
;;

MSGFLT_ADD		equ 1
MSGFLT_REMOVE		equ 2

;BOOL
ChangeWindowMessageFilter proto _CType \
	       message: UINT,
		dwFlag: DWORD


endif ;; WINVER GE 0x0600

if(WINVER GE 0x0601)

;;
;; Message filter info values (CHANGEFILTERSTRUCT.ExtStatus)
;;
MSGFLTINFO_NONE				equ 0
MSGFLTINFO_ALREADYALLOWED_FORWND	equ 1
MSGFLTINFO_ALREADYDISALLOWED_FORWND	equ 2
MSGFLTINFO_ALLOWED_HIGHER		equ 3

CHANGEFILTERSTRUCT	STRUC
cbSize			dd ?
ExtStatus		dd ?
CHANGEFILTERSTRUCT	ENDS
PCHANGEFILTERSTRUCT	typedef ptr CHANGEFILTERSTRUCT

;;
;; Message filter action values (action parameter to ChangeWindowMessageFilterEx)
;;
MSGFLT_RESET		equ 0
MSGFLT_ALLOW		equ 1
MSGFLT_DISALLOW		equ 2

;BOOL
ChangeWindowMessageFilterEx proto _CType \
		  hwnd: HWND,
	       message: UINT,
		action: DWORD,
   pChangeFilterStruct: PCHANGEFILTERSTRUCT


endif ;; WINVER GE 0x0601


if(WINVER GE 0x0601)

;;
;; Gesture defines and functions
;;

;;
;; Gesture information handle
;;
HGESTUREINFO		typedef HANDLE


;;
;; Gesture flags - GESTUREINFO.dwFlags
;;
GF_BEGIN		equ 0x00000001
GF_INERTIA		equ 0x00000002
GF_END			equ 0x00000004

;;
;; Gesture IDs
;;
GID_BEGIN		equ 1
GID_END			equ 2
GID_ZOOM		equ 3
GID_PAN			equ 4
GID_ROTATE		equ 5
GID_TWOFINGERTAP	equ 6
GID_PRESSANDTAP		equ 7
GID_ROLLOVER		equ GID_PRESSANDTAP

;;
;; Gesture information structure
;;   - Pass the HGESTUREINFO received in the WM_GESTURE message lParam into the
;;     GetGestureInfo function to retrieve this information.
;;   - If cbExtraArgs is non-zero, pass the HGESTUREINFO received in the WM_GESTURE
;;     message lParam into the GetGestureExtraArgs function to retrieve extended
;;     argument information.
;;
GESTUREINFO		STRUC
cbSize			UINT ?	;; size, in bytes, of this structure (including variable length Args field)
dwFlags			dd ?	;; see GF_* flags
dwID			dd ?	;; gesture ID, see GID_* defines
hwndTarget		HWND ?	;; handle to window targeted by this gesture
ptsLocation		POINTS <> ;; current location of this gesture
dwInstanceID		dd ?	;; internally used
dwSequenceID		dd ?	;; internally used
ullArguments		ULONGLONG ?	;; arguments for gestures whose arguments fit in 8 BYTES
cbExtraArgs		UINT ?	;; size, in bytes, of extra arguments, if any, that accompany this gesture
GESTUREINFO		ENDS
PGESTUREINFO		typedef ptr GESTUREINFO
PCGESTUREINFO		typedef ptr GESTUREINFO


;;
;; Gesture notification structure
;;   - The WM_GESTURENOTIFY message lParam contains a pointer to this structure.
;;   - The WM_GESTURENOTIFY message notifies a window that gesture recognition is
;;     in progress and a gesture will be generated if one is recognized under the
;;     current gesture settings.
;;
GESTURENOTIFYSTRUCT	STRUC
cbSize			UINT ?	;; size, in bytes, of this structure
dwFlags			dd ?	;; unused
hwndTarget		HWND ?	;; handle to window targeted by the gesture
ptsLocation		POINTS <> ;; starting location
dwInstanceID		dd ?	;; internally used
GESTURENOTIFYSTRUCT	ENDS
PGESTURENOTIFYSTRUCT	typedef ptr GESTURENOTIFYSTRUCT

;;
;; Gesture argument helpers
;;   - Angle should be a double in the range of -2pi to +2pi
;;   - Argument should be an unsigned 16-bit value
;;
GID_ROTATE_ANGLE_TO_ARGUMENT macro _arg_
	exitm<((((_arg_ + 2.0 * 3.14159265) / (4.0 * 3.14159265)) * 65535.0))>
	endm
GID_ROTATE_ANGLE_FROM_ARGUMENT macro _arg_
	exitm<(((_arg_ / 65535.0) * 4.0 * 3.14159265) - 2.0 * 3.14159265)>
	endm

;;
;; Gesture information retrieval
;;   - HGESTUREINFO is received by a window in the lParam of a WM_GESTURE message.
;;
;BOOL
GetGestureInfo proto _CType \
	  hGestureInfo: HGESTUREINFO,
	  pGestureInfo: PGESTUREINFO

;;
;; Gesture extra arguments retrieval
;;   - HGESTUREINFO is received by a window in the lParam of a WM_GESTURE message.
;;   - Size, in bytes, of the extra argument data is available in the cbExtraArgs
;;     field of the GESTUREINFO structure retrieved using the GetGestureInfo function.
;;
;BOOL
GetGestureExtraArgs proto _CType \
	  hGestureInfo: HGESTUREINFO,
	   cbExtraArgs: UINT,
	    pExtraArgs: PBYTE

;;
;; Gesture information handle management
;;   - If an application processes the WM_GESTURE message, then once it is done
;;     with the associated HGESTUREINFO, the application is responsible for
;;     closing the handle using this function. Failure to do so may result in
;;     process memory leaks.
;;   - If the message is instead passed to DefWindowProc, or is forwarded using
;;     one of the PostMessage or SendMessage class of API functions, the handle
;;     is transfered with the message and need not be closed by the application.
;;
;BOOL
CloseGestureInfoHandle proto _CType \
	  hGestureInfo: HGESTUREINFO



;;
;; Gesture configuration structure
;;   - Used in SetGestureConfig and GetGestureConfig
;;   - Note that any setting not included in either GESTURECONFIG.dwWant or
;;     GESTURECONFIG.dwBlock will use the parent window's preferences or
;;     system defaults.
;;
GESTURECONFIG		STRUC
dwID			dd ?	;; gesture ID
dwWant			dd ?	;; settings related to gesture ID that are to be turned on
dwBlock			dd ?	;; settings related to gesture ID that are to be turned off
GESTURECONFIG		ENDS
PGESTURECONFIG		typedef ptr GESTURECONFIG

;;
;; Gesture configuration flags - GESTURECONFIG.dwWant or GESTURECONFIG.dwBlock
;;

;;
;; Common gesture configuration flags - set GESTURECONFIG.dwID to zero
;;
GC_ALLGESTURES		equ 0x00000001

;;
;; Zoom gesture configuration flags - set GESTURECONFIG.dwID to GID_ZOOM
;;
GC_ZOOM			equ 0x00000001

;;
;; Pan gesture configuration flags - set GESTURECONFIG.dwID to GID_PAN
;;
GC_PAN			equ 0x00000001
GC_PAN_WITH_SINGLE_FINGER_VERTICALLY equ 0x00000002
GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY equ 0x00000004
GC_PAN_WITH_GUTTER	equ 0x00000008
GC_PAN_WITH_INERTIA	equ 0x00000010

;;
;; Rotate gesture configuration flags - set GESTURECONFIG.dwID to GID_ROTATE
;;
GC_ROTATE		equ 0x00000001

;;
;; Two finger tap gesture configuration flags - set GESTURECONFIG.dwID to GID_TWOFINGERTAP
;;
GC_TWOFINGERTAP		equ 0x00000001

;;
;; PressAndTap gesture configuration flags - set GESTURECONFIG.dwID to GID_PRESSANDTAP
;;
GC_PRESSANDTAP		equ 0x00000001
GC_ROLLOVER		equ GC_PRESSANDTAP

GESTURECONFIGMAXCOUNT	equ 256		    ;; Maximum number of gestures that can be included
							;; in a single call to SetGestureConfig / GetGestureConfig

;BOOL
SetGestureConfig proto _CType \
		  hwnd: HWND ,
	    dwReserved: DWORD,
		  cIDs: UINT,
	pGestureConfig: PGESTURECONFIG,
		cbSize: UINT

GCF_INCLUDE_ANCESTORS	equ 0x00000001	    ;; If specified, GetGestureConfig returns consolidated configuration
							;; for the specified window and it's parent window chain
;BOOL
GetGestureConfig proto _CType \
		 hwnd: HWND,
	   dwReserved: DWORD,
	      dwFlags: DWORD,
		pcIDs: PUINT,
       pGestureConfig: PGESTURECONFIG,
	       cbSize: UINT		;; sizeof(GESTURECONFIG)

endif ;; WINVER GE 0x0601

if(WINVER GE 0x0601)

;;
;; GetSystemMetrics(SM_DIGITIZER) flag values
;;
NID_INTEGRATED_TOUCH	equ 0x00000001
NID_EXTERNAL_TOUCH	equ 0x00000002
NID_INTEGRATED_PEN	equ 0x00000004
NID_EXTERNAL_PEN	equ 0x00000008
NID_MULTI_INPUT		equ 0x00000040
NID_READY		equ 0x00000080

endif ;; WINVER GE 0x0601


MAX_STR_BLOCKREASON	equ 256

;BOOL
ShutdownBlockReasonCreate proto _CType \
		  hWnd: HWND,
	    pwszReason: LPCWSTR

;BOOL
ShutdownBlockReasonQuery proto _CType \
		  hWnd: HWND,
	      pwszBuff: LPWSTR,
	      pcchBuff: ptr DWORD

;BOOL
ShutdownBlockReasonDestroy proto _CType \
		  hWnd: HWND

ifdef ISOLATION_AWARE_ENABLED
if ISOLATION_AWARE_ENABLED
include winuser.inl
endif ;; ISOLATION_AWARE_ENABLED

endif ;; NOT _WINUSER_

.list
