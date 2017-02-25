ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif
.xlist
;
; Input Method Manager definitions
;
ifndef _IMM_
_IMM_ equ 1 ;; defined if IMM.H has been included

if (WINVER GE 0x40A)
HIMC			typedef HANDLE
HIMCC			typedef HANDLE
else
HIMC			typedef DWORD
HIMCC			typedef DWORD
endif

LPHKL			typedef ptr HKL
LPUINT			typedef ptr UINT


COMPOSITIONFORM		STRUC
dwStyle			dd ?
ptCurrentPos		POINT <>
rcArea			RECT <>
COMPOSITIONFORM		ENDS
PCOMPOSITIONFORM	typedef ptr COMPOSITIONFORM
NPCOMPOSITIONFORM	typedef ptr COMPOSITIONFORM
LPCOMPOSITIONFORM	typedef ptr COMPOSITIONFORM


CANDIDATEFORM		STRUC
dwIndex			dd ?
dwStyle			dd ?
ptCurrentPos		POINT <>
rcArea			RECT <>
CANDIDATEFORM		ENDS
PCANDIDATEFORM		typedef ptr CANDIDATEFORM
NPCANDIDATEFORM		typedef ptr CANDIDATEFORM
LPCANDIDATEFORM		typedef ptr CANDIDATEFORM


CANDIDATELIST		STRUC
dwSize			dd ?
dwStyle			dd ?
dwCount			dd ?
dwSelection		dd ?
dwPageStart		dd ?
dwPageSize		dd ?
dwOffset		dd ?
CANDIDATELIST		ENDS
PCANDIDATELIST		typedef ptr CANDIDATELIST
NPCANDIDATELIST		typedef ptr CANDIDATELIST
LPCANDIDATELIST		typedef ptr CANDIDATELIST

REGISTERWORDA		STRUC
lpReading		LPSTR ?
lpWord			LPSTR ?
REGISTERWORDA		ENDS
PREGISTERWORDA		typedef ptr REGISTERWORDA
NPREGISTERWORDA		typedef ptr REGISTERWORDA
LPREGISTERWORDA		typedef ptr REGISTERWORDA
REGISTERWORDW		STRUC
lpReading		LPWSTR ?
lpWord			LPWSTR ?
REGISTERWORDW		ENDS
PREGISTERWORDW		typedef ptr REGISTERWORDW
NPREGISTERWORDW		typedef ptr REGISTERWORDW
LPREGISTERWORDW		typedef ptr REGISTERWORDW
ifdef _UNICODE
REGISTERWORD		typedef REGISTERWORDW
PREGISTERWORD		typedef PREGISTERWORDW
NPREGISTERWORD		typedef NPREGISTERWORDW
LPREGISTERWORD		typedef LPREGISTERWORDW
else
REGISTERWORD		typedef REGISTERWORDA
PREGISTERWORD		typedef PREGISTERWORDA
NPREGISTERWORD		typedef NPREGISTERWORDA
LPREGISTERWORD		typedef LPREGISTERWORDA
endif ;; UNICODE


if(WINVER GE 0x040A)
RECONVERTSTRING		STRUC
dwSize			dd ?
dwVersion		dd ?
dwStrLen		dd ?
dwStrOffset		dd ?
dwCompStrLen		dd ?
dwCompStrOffset		dd ?
dwTargetStrLen		dd ?
dwTargetStrOffset	dd ?
RECONVERTSTRING		ENDS
PRECONVERTSTRING	typedef ptr RECONVERTSTRING
NPRECONVERTSTRING	typedef ptr RECONVERTSTRING
LPRECONVERTSTRING	typedef ptr RECONVERTSTRING
endif

STYLE_DESCRIPTION_SIZE	equ 32

STYLEBUFA		STRUC
dwStyle			dd ?
szDescription		db STYLE_DESCRIPTION_SIZE dup(?)
STYLEBUFA		ENDS
PSTYLEBUFA		typedef ptr STYLEBUFA
NPSTYLEBUFA		typedef ptr STYLEBUFA
LPSTYLEBUFA		typedef ptr STYLEBUFA
STYLEBUFW		STRUC
dwStyle			dd ?
szDescription		dw STYLE_DESCRIPTION_SIZE dup(?)
STYLEBUFW		ENDS
PSTYLEBUFW		typedef ptr STYLEBUFW
NPSTYLEBUFW		typedef ptr STYLEBUFW
LPSTYLEBUFW		typedef ptr STYLEBUFW
ifdef _UNICODE
STYLEBUF		typedef STYLEBUFW
PSTYLEBUF		typedef PSTYLEBUFW
NPSTYLEBUF		typedef NPSTYLEBUFW
LPSTYLEBUF		typedef LPSTYLEBUFW
else
STYLEBUF		typedef STYLEBUFA
PSTYLEBUF		typedef PSTYLEBUFA
NPSTYLEBUF		typedef NPSTYLEBUFA
LPSTYLEBUF		typedef LPSTYLEBUFA
endif ;; UNICODE


if(WINVER GE 0x040A)
IMEMENUITEM_STRING_SIZE equ 80

IMEMENUITEMINFOA	STRUC
cbSize			UINT ?
fType			UINT ?
fState			UINT ?
wID			UINT ?
hbmpChecked		HBITMAP ?
hbmpUnchecked		HBITMAP ?
dwItemData		dd ?
szString		db IMEMENUITEM_STRING_SIZE dup(?)
hbmpItem		HBITMAP ?
IMEMENUITEMINFOA	ENDS
PIMEMENUITEMINFOA	typedef ptr IMEMENUITEMINFOA
NPIMEMENUITEMINFOA	typedef ptr IMEMENUITEMINFOA
LPIMEMENUITEMINFOA	typedef ptr IMEMENUITEMINFOA
IMEMENUITEMINFOW	STRUC
cbSize			UINT ?
fType			UINT ?
fState			UINT ?
wID			UINT ?
hbmpChecked		HBITMAP ?
hbmpUnchecked		HBITMAP ?
dwItemData		dd ?
szString		dw IMEMENUITEM_STRING_SIZE dup(?)
hbmpItem		HBITMAP ?
IMEMENUITEMINFOW	ENDS
PIMEMENUITEMINFOW	typedef ptr IMEMENUITEMINFOW
NPIMEMENUITEMINFOW	typedef ptr IMEMENUITEMINFOW
LPIMEMENUITEMINFOW	typedef ptr IMEMENUITEMINFOW
ifdef _UNICODE
IMEMENUITEMINFO		typedef IMEMENUITEMINFOW
PIMEMENUITEMINFO	typedef PIMEMENUITEMINFOW
NPIMEMENUITEMINFO	typedef NPIMEMENUITEMINFOW
LPIMEMENUITEMINFO	typedef LPIMEMENUITEMINFOW
else
IMEMENUITEMINFO		typedef IMEMENUITEMINFOA
PIMEMENUITEMINFO	typedef PIMEMENUITEMINFOA
NPIMEMENUITEMINFO	typedef NPIMEMENUITEMINFOA
LPIMEMENUITEMINFO	typedef LPIMEMENUITEMINFOA
endif ;; UNICODE
endif  ;; WINVER GE 0x040A

;; prototype of IMM API

ImmInstallIMEA proto _CType \
       lpszIMEFileName: LPCSTR,
	lpszLayoutText: LPCSTR
ImmInstallIMEW proto _CType \
       lpszIMEFileName: LPCWSTR,
	lpszLayoutText: LPCWSTR
ifdef _UNICODE
ImmInstallIME		equ <ImmInstallIMEW>
else
ImmInstallIME		equ <ImmInstallIMEA>
endif ;; NOT UNICODE

;HWND
ImmGetDefaultIMEWnd proto _CType \
		      : HWND

;UINT
ImmGetDescriptionA proto _CType \
		      : HKL,
		      : LPSTR,
	       uBufLen: UINT
;UINT
ImmGetDescriptionW proto _CType \
		      : HKL,
		      : LPWSTR,
	       uBufLen: UINT
ifdef _UNICODE
ImmGetDescription	equ <ImmGetDescriptionW>
else
ImmGetDescription	equ <ImmGetDescriptionA>
endif ;; NOT UNICODE

;UINT
ImmGetIMEFileNameA proto _CType \
		      : HKL,
		      : LPSTR,
	       uBufLen: UINT
;UINT
ImmGetIMEFileNameW proto _CType \
		      : HKL,
		      : LPWSTR,
	       uBufLen: UINT
ifdef _UNICODE
ImmGetIMEFileName	equ <ImmGetIMEFileNameW>
else
ImmGetIMEFileName	equ <ImmGetIMEFileNameA>
endif ;; NOT UNICODE

;DWORD
ImmGetProperty proto _CType \
		      : HKL,
		      : DWORD

;BOOL
ImmIsIME proto _CType \
		      : HKL
;BOOL
ImmSimulateHotKey proto _CType \
		      : HWND,
		      : DWORD
;HIMC
ImmCreateContext proto _CType
;BOOL
ImmDestroyContext proto _CType \
			: HIMC
;HIMC
ImmGetContext proto _CType \
		      : HWND
;BOOL
ImmReleaseContext proto _CType \
		      : HWND,
		      : HIMC
;HIMC
ImmAssociateContext proto _CType \
		      : HWND,
		      : HIMC
if(WINVER GE 0x040A)
;BOOL
ImmAssociateContextEx proto _CType \
		      : HWND,
		      : HIMC,
		      : DWORD
endif ;; WINVER GE 0x040A

;LONG
ImmGetCompositionStringA proto _CType \
		      : HIMC,
		      : DWORD,
		      : LPVOID,
		      : DWORD
ImmGetCompositionStringW proto _CType \
		      : HIMC,
		      : DWORD,
		      : LPVOID,
		      : DWORD
ifdef _UNICODE
ImmGetCompositionString equ <ImmGetCompositionStringW>
else
ImmGetCompositionString equ <ImmGetCompositionStringA>
endif ;; NOT UNICODE

;BOOL
ImmSetCompositionStringA proto _CType \
		      : HIMC,
	       dwIndex: DWORD,
		lpComp: LPCVOID,
		      : DWORD,
		lpRead: LPCVOID,
		      : DWORD
ImmSetCompositionStringW proto _CType \
		      : HIMC,
	       dwIndex: DWORD,
		lpComp: LPCVOID,
		      : DWORD,
		lpRead: LPCVOID,
		      : DWORD
ifdef _UNICODE
ImmSetCompositionString equ <ImmSetCompositionStringW>
else
ImmSetCompositionString equ <ImmSetCompositionStringA>
endif ;; NOT UNICODE

;DWORD
ImmGetCandidateListCountA proto _CType \
		      : HIMC,
	 lpdwListCount: LPDWORD
ImmGetCandidateListCountW proto _CType \
		      : HIMC,
	 lpdwListCount: LPDWORD
ifdef _UNICODE
ImmGetCandidateListCount equ <ImmGetCandidateistCountW>
else
ImmGetCandidateListCount equ <ImmGetCandidateistCountA>
endif ;; NOT UNICODE

;DWORD
ImmGetCandidateListA proto _CType \
		      : HIMC,
	       deIndex: DWORD,
		      : LPCANDIDATELIST,
	      dwBufLen: DWORD
ImmGetCandidateListW proto _CType \
		      : HIMC,
	       deIndex: DWORD,
		      : LPCANDIDATELIST,
	      dwBufLen: DWORD
ifdef _UNICODE
ImmGetCandidateList	equ <ImmGetCandidateistW>
else
ImmGetCandidateList	equ <ImmGetCandidateistA>
endif ;; NOT UNICODE

;DWORD
ImmGetGuideLineA proto _CType \
		      : HIMC,
	       dwIndex: DWORD,
		      : LPSTR,
	      dwBufLen: DWORD
ImmGetGuideLineW proto _CType \
		      : HIMC,
	       dwIndex: DWORD,
		      : LPWSTR,
	      dwBufLen: DWORD
ifdef _UNICODE
ImmGetGuideLine		equ <ImmGetGuideineW>
else
ImmGetGuideLine		equ <ImmGetGuideineA>
endif ;; NOT UNICODE

;BOOL
ImmGetConversionStatus proto _CType \
		      : HIMC,
		      : LPDWORD,
		      : LPDWORD
;BOOL
ImmSetConversionStatus proto _CType \
		      : HIMC,
		      : DWORD,
		      : DWORD
;BOOL
ImmSetOpenStatus proto _CType \
		      : HIMC,
		      : BOOL

ifdef _WINGDI_
ifndef NOGDI
;BOOL
ImmGetCompositionFontA proto _CType \
		      : HIMC,
		      : LPLOGFONTA
ImmGetCompositionFontW proto _CType \
		      : HIMC,
		      : LPLOGFONTW
ifdef _UNICODE
ImmGetCompositionFont	equ <ImmGetCompositionFontW>
else
ImmGetCompositionFont	equ <ImmGetCompositionFontA>
endif ;; NOT UNICODE

;BOOL
ImmSetCompositionFontA proto _CType \
		      : HIMC,
		      : LPLOGFONTA
ImmSetCompositionFontW proto _CType \
		      : HIMC,
		      : LPLOGFONTW
ifdef _UNICODE
ImmSetCompositionFont	equ <ImmSetCompositionFontW>
else
ImmSetCompositionFont	equ <ImmSetCompositionFontA>
endif ;; NOT UNICODE
endif  ;; ifndef NOGDI
endif  ;; ifdef _WINGDI_

;BOOL
ImmConfigureIMEA proto _CType \
		      : HKL,
		      : HWND,
		      : DWORD,
		      : LPVOID
ImmConfigureIMEW proto _CType \
		      : HKL,
		      : HWND,
		      : DWORD,
		      : LPVOID
ifdef _UNICODE
ImmConfigureIME		equ <ImmConfigureIMEW>
else
ImmConfigureIME		equ <ImmConfigureIMEA>
endif ;; NOT UNICODE

;LRESULT
ImmEscapeA proto _CType \
		      : HKL,
		      : HIMC,
		      : UINT,
		      : LPVOID
ImmEscapeW proto _CType \
		      : HKL,
		      : HIMC,
		      : UINT,
		      : LPVOID
ifdef _UNICODE
ImmEscape		equ <ImmEscapeW>
else
ImmEscape		equ <ImmEscapeA>
endif ;; NOT UNICODE

;DWORD
ImmGetConversionListA proto _CType \
		      : HKL,
		      : HIMC,
		      : LPCSTR,
		      : LPCANDIDATELIST,
	      dwBufLen: DWORD,
		 uFlag: UINT
ImmGetConversionListW proto _CType \
		      : HKL,
		      : HIMC,
		      : LPCWSTR,
		      : LPCANDIDATELIST,
	      dwBufLen: DWORD,
		 uFlag: UINT
ifdef _UNICODE
ImmGetConversionList	equ <ImmGetConversionListW>
else
ImmGetConversionList	equ <ImmGetConversionListA>
endif ;; NOT UNICODE

;BOOL
ImmNotifyIME proto _CType \
		      : HIMC,
	      dwAction: DWORD,
	       dwIndex: DWORD,
	       dwValue: DWORD


;BOOL
ImmGetStatusWindowPos proto _CType \
		      : HIMC,
		      : LPPOINT
;BOOL
ImmSetStatusWindowPos proto _CType \
		      : HIMC,
		      : LPPOINT
;BOOL
ImmGetCompositionWindow proto _CType \
		      : HIMC,
		      : LPCOMPOSITIONFORM
;BOOL
ImmSetCompositionWindow proto _CType \
		      : HIMC,
		      : LPCOMPOSITIONFORM
;BOOL
ImmGetCandidateWindow proto _CType \
		      : HIMC,
		      : DWORD,
		      : LPCANDIDATEFORM
;BOOL
ImmSetCandidateWindow proto _CType \
		      : HIMC,
		      : LPCANDIDATEFORM

;BOOL
ImmIsUIMessageA proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
;BOOL
ImmIsUIMessageW proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
ifdef _UNICODE
ImmIsUIMessage		equ <ImmIsUIMessageW>
else
ImmIsUIMessage		equ <ImmIsUIMessageA>
endif ;; NOT UNICODE


;UINT

REGISTERWORDENUMPROCA_T typedef proto _CType \
	   lpszReading: LPCSTR,
		      : DWORD,
	  lpszRegister: LPCSTR,
		      : LPVOID
REGISTERWORDENUMPROCW_T typedef proto _CType \
	   lpszReading: LPCWSTR,
		      : DWORD,
	  lpszRegister: LPCWSTR,
		      : LPVOID

REGISTERWORDENUMPROCA typedef ptr REGISTERWORDENUMPROCA_T
REGISTERWORDENUMPROCW typedef ptr REGISTERWORDENUMPROCW_T


ifdef _UNICODE
REGISTERWORDENUMPROC	equ <<REGISTERWORDENUMPROCW>
else
REGISTERWORDENUMPROC	equ <<REGISTERWORDENUMPROCA>
endif ;; NOT UNICODE

;BOOL
ImmRegisterWordA proto _CType \
		      : HKL,
	   lpszReading: LPCSTR,
		      : DWORD,
	  lpszRegister: LPCSTR
ImmRegisterWordW proto _CType \
		      : HKL,
	   lpszReading: LPCWSTR,
		      : DWORD,
	  lpszRegister: LPCWSTR
ifdef _UNICODE
ImmRegisterWord		equ <ImmRegisterWordW>
else
ImmRegisterWord		equ <ImmRegisterWordA>
endif ;; NOT UNICODE

;BOOL
ImmUnregisterWordA proto _CType \
		      : HKL,
	   lpszReading: LPCSTR,
		      : DWORD,
	lpszUnregister: LPCSTR
;BOOL
ImmUnregisterWordW proto _CType \
		      : HKL,
	   lpszReading: LPCWSTR,
		      : DWORD,
	lpszUnregister: LPCWSTR
ifdef _UNICODE
ImmUnregisterWord	equ <ImmUnregisterWordW>
else
ImmUnregisterWord	equ <ImmUnregisterWordA>
endif ;; NOT UNICODE

;UINT
ImmGetRegisterWordStyleA proto _CType \
		      : HKL,
		 nItem: UINT,
		      : LPSTYLEBUFA
;UINT
ImmGetRegisterWordStyleW proto _CType \
		      : HKL,
		 nItem: UINT,
		      : LPSTYLEBUFW
ifdef _UNICODE
ImmGetRegisterWordStyle equ <ImmGetRegisterWordStyleW>
else
ImmGetRegisterWordStyle equ <ImmGetRegisterWordStyleA>
endif ;; NOT UNICODE

;UINT
ImmEnumRegisterWordA proto _CType \
		      : HKL,
		      : REGISTERWORDENUMPROCA,
	   lpszReading: LPCSTR,
		      : DWORD,
	  lpszRegister: LPCSTR,
		      : LPVOID
;UINT
ImmEnumRegisterWordW proto _CType \
		      : HKL,
		      : REGISTERWORDENUMPROCW,
	   lpszReading: LPCWSTR,
		      : DWORD,
	  lpszRegister: LPCWSTR,
		      : LPVOID
ifdef _UNICODE
ImmEnumRegisterWord	equ <ImmEnumRegisterWordW>
else
ImmEnumRegisterWord	equ <ImmEnumRegisterWordA>
endif ;; NOT UNICODE

if(WINVER GE 0x040A)
;BOOL
;DWORD
ImmGetImeMenuItemsA proto _CType \
		      : HIMC,
		      : DWORD,
		      : DWORD,
		      : LPIMEMENUITEMINFOA,
		      : LPIMEMENUITEMINFOA,
		      : DWORD
;DWORD
ImmGetImeMenuItemsW proto _CType \
		      : HIMC,
		      : DWORD,
		      : DWORD,
		      : LPIMEMENUITEMINFOW,
		      : LPIMEMENUITEMINFOW,
		      : DWORD
ifdef _UNICODE
ImmGetImeMenuItems	equ <ImmGetImeMenuItemsW>
else
ImmGetImeMenuItems	equ <ImmGetImeMenuItemsA>
endif ;; NOT UNICODE

endif ;; WINVER GE 0x040A



;; wParam for WM_IME_CONTROL
IMC_GETCANDIDATEPOS	equ 0x0007
IMC_SETCANDIDATEPOS	equ 0x0008
IMC_GETCOMPOSITIONFONT	equ 0x0009
IMC_SETCOMPOSITIONFONT	equ 0x000A
IMC_GETCOMPOSITIONWINDOW equ 0x000B
IMC_SETCOMPOSITIONWINDOW equ 0x000C
IMC_GETSTATUSWINDOWPOS	equ 0x000F
IMC_SETSTATUSWINDOWPOS	equ 0x0010
IMC_CLOSESTATUSWINDOW	equ 0x0021
IMC_OPENSTATUSWINDOW	equ 0x0022


;; dwAction for ImmNotifyIME
NI_OPENCANDIDATE	equ 0x0010
NI_CLOSECANDIDATE	equ 0x0011
NI_SELECTCANDIDATESTR	equ 0x0012
NI_CHANGECANDIDATELIST	equ 0x0013
NI_FINALIZECONVERSIONRESULT equ 0x0014
NI_COMPOSITIONSTR	equ 0x0015
NI_SETCANDIDATE_PAGESTART equ 0x0016
NI_SETCANDIDATE_PAGESIZE equ 0x0017
NI_IMEMENUSELECTED	equ 0x0018

;; lParam for WM_IME_SETCONTEXT
ISC_SHOWUICANDIDATEWINDOW equ 0x00000001
ISC_SHOWUICOMPOSITIONWINDOW equ 0x80000000
ISC_SHOWUIGUIDELINE	equ 0x40000000
ISC_SHOWUIALLCANDIDATEWINDOW equ 0x0000000F
ISC_SHOWUIALL		equ 0xC000000F


;; dwIndex for ImmNotifyIME/NI_COMPOSITIONSTR
CPS_COMPLETE		equ 0x0001
CPS_CONVERT		equ 0x0002
CPS_REVERT		equ 0x0003
CPS_CANCEL		equ 0x0004


;; the modifiers of hot key
MOD_ALT			equ 0x0001
MOD_CONTROL		equ 0x0002
MOD_SHIFT		equ 0x0004

MOD_LEFT		equ 0x8000
MOD_RIGHT		equ 0x4000

MOD_ON_KEYUP		equ 0x0800
MOD_IGNORE_ALL_MODIFIER equ 0x0400


;; Windows for Simplified Chinese Edition hot key ID from 0x10 - 0x2F
IME_CHOTKEY_IME_NONIME_TOGGLE equ 0x10
IME_CHOTKEY_SHAPE_TOGGLE equ 0x11
IME_CHOTKEY_SYMBOL_TOGGLE equ 0x12

;; Windows for Japanese Edition hot key ID from 0x30 - 0x4F
IME_JHOTKEY_CLOSE_OPEN	equ 0x30

;; Windows for Korean Edition hot key ID from 0x50 - 0x6F
IME_KHOTKEY_SHAPE_TOGGLE equ 0x50
IME_KHOTKEY_HANJACONVERT equ 0x51
IME_KHOTKEY_ENGLISH	equ 0x52

;; Windows for Traditional Chinese Edition hot key ID from 0x70 - 0x8F
IME_THOTKEY_IME_NONIME_TOGGLE equ 0x70
IME_THOTKEY_SHAPE_TOGGLE equ 0x71
IME_THOTKEY_SYMBOL_TOGGLE equ 0x72

;; direct switch hot key ID from 0x100 - 0x11F
IME_HOTKEY_DSWITCH_FIRST equ 0x100
IME_HOTKEY_DSWITCH_LAST equ 0x11F

;; IME private hot key from 0x200 - 0x21F
IME_HOTKEY_PRIVATE_FIRST equ 0x200
IME_ITHOTKEY_RESEND_RESULTSTR equ 0x200
IME_ITHOTKEY_PREVIOUS_COMPOSITION equ 0x201
IME_ITHOTKEY_UISTYLE_TOGGLE equ 0x202
IME_ITHOTKEY_RECONVERTSTRING equ 0x203
IME_HOTKEY_PRIVATE_LAST equ 0x21F


;; dwSystemInfoFlags bits

;; parameter of ImmGetCompositionString
GCS_COMPREADSTR		equ 0x0001
GCS_COMPREADATTR	equ 0x0002
GCS_COMPREADCLAUSE	equ 0x0004
GCS_COMPSTR		equ 0x0008
GCS_COMPATTR		equ 0x0010
GCS_COMPCLAUSE		equ 0x0020
GCS_CURSORPOS		equ 0x0080
GCS_DELTASTART		equ 0x0100
GCS_RESULTREADSTR	equ 0x0200
GCS_RESULTREADCLAUSE	equ 0x0400
GCS_RESULTSTR		equ 0x0800
GCS_RESULTCLAUSE	equ 0x1000

;; style bit flags for WM_IME_COMPOSITION
CS_INSERTCHAR		equ 0x2000
CS_NOMOVECARET		equ 0x4000


;; bits of fdwInit of INPUTCONTEXT
;; IME version constants
IMEVER_0310		equ 0x0003000A
IMEVER_0400		equ 0x00040000


;; IME property bits
IME_PROP_AT_CARET	equ 0x00010000
IME_PROP_SPECIAL_UI	equ 0x00020000
IME_PROP_CANDLIST_START_FROM_1 equ 0x00040000
IME_PROP_UNICODE	equ 0x00080000
IME_PROP_COMPLETE_ON_UNSELECT equ 0x00100000

;; IME UICapability bits
UI_CAP_2700		equ 0x00000001
UI_CAP_ROT90		equ 0x00000002
UI_CAP_ROTANY		equ 0x00000004

;; ImmSetCompositionString Capability bits
SCS_CAP_COMPSTR		equ 0x00000001
SCS_CAP_MAKEREAD	equ 0x00000002
SCS_CAP_SETRECONVERTSTRING equ 0x00000004

;; IME WM_IME_SELECT inheritance Capability bits
SELECT_CAP_CONVERSION	equ 0x00000001
SELECT_CAP_SENTENCE	equ 0x00000002

;; ID for deIndex of ImmGetGuideLine
GGL_LEVEL		equ 0x00000001
GGL_INDEX		equ 0x00000002
GGL_STRING		equ 0x00000003
GGL_PRIVATE		equ 0x00000004


;; ID for dwLevel of GUIDELINE Structure
GL_LEVEL_NOGUIDELINE	equ 0x00000000
GL_LEVEL_FATAL		equ 0x00000001
GL_LEVEL_ERROR		equ 0x00000002
GL_LEVEL_WARNING	equ 0x00000003
GL_LEVEL_INFORMATION	equ 0x00000004


;; ID for dwIndex of GUIDELINE Structure
GL_ID_UNKNOWN		equ 0x00000000
GL_ID_NOMODULE		equ 0x00000001
GL_ID_NODICTIONARY	equ 0x00000010
GL_ID_CANNOTSAVE	equ 0x00000011
GL_ID_NOCONVERT		equ 0x00000020
GL_ID_TYPINGERROR	equ 0x00000021
GL_ID_TOOMANYSTROKE	equ 0x00000022
GL_ID_READINGCONFLICT	equ 0x00000023
GL_ID_INPUTREADING	equ 0x00000024
GL_ID_INPUTRADICAL	equ 0x00000025
GL_ID_INPUTCODE		equ 0x00000026
GL_ID_INPUTSYMBOL	equ 0x00000027
GL_ID_CHOOSECANDIDATE	equ 0x00000028
GL_ID_REVERSECONVERSION equ 0x00000029
GL_ID_PRIVATE_FIRST	equ 0x00008000
GL_ID_PRIVATE_LAST	equ 0x0000FFFF


;; ID for dwIndex of ImmGetProperty
IGP_GETIMEVERSION	equ (-4)
IGP_PROPERTY		equ 0x00000004
IGP_CONVERSION		equ 0x00000008
IGP_SENTENCE		equ 0x0000000c
IGP_UI			equ 0x00000010
IGP_SETCOMPSTR		equ 0x00000014
IGP_SELECT		equ 0x00000018

;; dwIndex for ImmSetCompositionString API
SCS_SETSTR		equ (GCS_COMPREADSTR OR GCS_COMPSTR)
SCS_CHANGEATTR		equ (GCS_COMPREADATTR OR GCS_COMPATTR)
SCS_CHANGECLAUSE	equ (GCS_COMPREADCLAUSE OR GCS_COMPCAUSE)
SCS_SETRECONVERTSTRING	equ 0x00010000
SCS_QUERYRECONVERTSTRING equ 0x00020000


;; attribute for COMPOSITIONSTRING Structure
ATTR_INPUT		equ 0x00
ATTR_TARGET_CONVERTED	equ 0x01
ATTR_CONVERTED		equ 0x02
ATTR_TARGET_NOTCONVERTED equ 0x03
ATTR_INPUT_ERROR	equ 0x04
ATTR_FIXEDCONVERTED	equ 0x05


;; bit field for IMC_SETCOMPOSITIONWINDOW, IMC_SETCANDIDATEWINDOW
CFS_DEFAULT		equ 0x0000
CFS_RECT		equ 0x0001
CFS_POINT		equ 0x0002
CFS_FORCE_POSITION	equ 0x0020
CFS_CANDIDATEPOS	equ 0x0040
CFS_EXCLUDE		equ 0x0080


;; conversion direction for ImmGetConversionList
GCL_CONVERSION		equ 0x0001
GCL_REVERSECONVERSION	equ 0x0002
GCL_REVERSE_LENGTH	equ 0x0003


;; bit field for conversion mode
IME_CMODE_ALPHANUMERIC	equ 0x0000
IME_CMODE_NATIVE	equ 0x0001
IME_CMODE_CHINESE	equ IME_CMODE_NATIVE
;; IME_CMODE_HANGEUL is old name of IME_CMODE_HANGUL. It will be gone eventually.
IME_CMODE_HANGEUL	equ IME_CMODE_NATIVE
IME_CMODE_HANGUL	equ IME_CMODE_NATIVE
IME_CMODE_JAPANESE	equ IME_CMODE_NATIVE
IME_CMODE_KATAKANA	equ 0x0002  ;; only effect under IME_CMODE_NATIVE
IME_CMODE_LANGUAGE	equ 0x0003
IME_CMODE_FULLSHAPE	equ 0x0008
IME_CMODE_ROMAN		equ 0x0010
IME_CMODE_CHARCODE	equ 0x0020
IME_CMODE_HANJACONVERT	equ 0x0040
IME_CMODE_SOFTKBD	equ 0x0080
IME_CMODE_NOCONVERSION	equ 0x0100
IME_CMODE_EUDC		equ 0x0200
IME_CMODE_SYMBOL	equ 0x0400
IME_CMODE_FIXED		equ 0x0800

IME_SMODE_NONE		equ 0x0000
IME_SMODE_PLAURALCLAUSE equ 0x0001
IME_SMODE_SINGLECONVERT equ 0x0002
IME_SMODE_AUTOMATIC	equ 0x0004
IME_SMODE_PHRASEPREDICT equ 0x0008
IME_SMODE_CONVERSATION	equ 0x0010

;; style of candidate
IME_CAND_UNKNOWN	equ 0x0000
IME_CAND_READ		equ 0x0001
IME_CAND_CODE		equ 0x0002
IME_CAND_MEANING	equ 0x0003
IME_CAND_RADICAL	equ 0x0004
IME_CAND_STROKE		equ 0x0005


;; wParam of report message WM_IME_NOTIFY
IMN_CLOSESTATUSWINDOW	equ 0x0001
IMN_OPENSTATUSWINDOW	equ 0x0002
IMN_CHANGECANDIDATE	equ 0x0003
IMN_CLOSECANDIDATE	equ 0x0004
IMN_OPENCANDIDATE	equ 0x0005
IMN_SETCONVERSIONMODE	equ 0x0006
IMN_SETSENTENCEMODE	equ 0x0007
IMN_SETOPENSTATUS	equ 0x0008
IMN_SETCANDIDATEPOS	equ 0x0009
IMN_SETCOMPOSITIONFONT	equ 0x000A
IMN_SETCOMPOSITIONWINDOW equ 0x000B
IMN_SETSTATUSWINDOWPOS	equ 0x000C
IMN_GUIDELINE		equ 0x000D
IMN_PRIVATE		equ 0x000E

if(WINVER GE 0x040A)
;; wParam of report message WM_IME_REQUEST
IMR_COMPOSITIONWINDOW	equ 0x0001
IMR_CANDIDATEWINDOW	equ 0x0002
IMR_COMPOSITIONFONT	equ 0x0003
IMR_RECONVERTSTRING	equ 0x0004
IMR_CONFIRMRECONVERTSTRING equ 0x0005
endif

;; error code of ImmGetCompositionString
IMM_ERROR_NODATA	equ (-1)
IMM_ERROR_GENERAL	equ (-2)


;; dialog mode of ImmConfigureIME
IME_CONFIG_GENERAL	equ 1
IME_CONFIG_REGISTERWORD equ 2
IME_CONFIG_SELECTDICTIONARY equ 3


;; dialog mode of ImmEscape
IME_ESC_QUERY_SUPPORT	equ 0x0003
IME_ESC_RESERVED_FIRST	equ 0x0004
IME_ESC_RESERVED_LAST	equ 0x07FF
IME_ESC_PRIVATE_FIRST	equ 0x0800
IME_ESC_PRIVATE_LAST	equ 0x0FFF
IME_ESC_SEQUENCE_TO_INTERNAL equ 0x1001
IME_ESC_GET_EUDC_DICTIONARY equ 0x1003
IME_ESC_SET_EUDC_DICTIONARY equ 0x1004
IME_ESC_MAX_KEY		equ 0x1005
IME_ESC_IME_NAME	equ 0x1006
IME_ESC_SYNC_HOTKEY	equ 0x1007
IME_ESC_HANJA_MODE	equ 0x1008
IME_ESC_AUTOMATA	equ 0x1009
IME_ESC_PRIVATE_HOTKEY	equ 0x100a
IME_ESC_GETHELPFILENAME equ 0x100b

;; style of word registration
IME_REGWORD_STYLE_EUDC	equ 0x00000001
IME_REGWORD_STYLE_USER_FIRST equ 0x80000000
IME_REGWORD_STYLE_USER_LAST equ 0xFFFFFFFF


if(WINVER GE 0x040A)
;; dwFlags for ImmAssociateContextEx
IACE_CHILDREN		equ 0x0001
IACE_DEFAULT		equ 0x0010
IACE_IGNORENOCONTEXT	equ 0x0020

;; dwFlags for ImmGetImeMenuItems
IGIMIF_RIGHTMENU	equ 0x0001

;; dwType for ImmGetImeMenuItems
IGIMII_CMODE		equ 0x0001
IGIMII_SMODE		equ 0x0002
IGIMII_CONFIGURE	equ 0x0004
IGIMII_TOOLS		equ 0x0008
IGIMII_HELP		equ 0x0010
IGIMII_OTHER		equ 0x0020
IGIMII_INPUTTOOLS	equ 0x0040

;; fType of IMEMENUITEMINFO structure
IMFT_RADIOCHECK		equ 0x00001
IMFT_SEPARATOR		equ 0x00002
IMFT_SUBMENU		equ 0x00004

;; fState of IMEMENUITEMINFO structure
IMFS_GRAYED		equ MFS_GRAYED
IMFS_DISABLED		equ MFS_DISABED
IMFS_CHECKED		equ MFS_CHECKED
IMFS_HILITE		equ MFS_HILITE
IMFS_ENABLED		equ MFS_ENABED
IMFS_UNCHECKED		equ MFS_UNCHECKED
IMFS_UNHILITE		equ MFS_UNHILITE
IMFS_DEFAULT		equ MFS_DEFAULT
endif ;; WINVER GE 0x040A

;; type of soft keyboard
;; for Windows Tranditional Chinese Edition
SOFTKEYBOARD_TYPE_T1	equ 0x0001
;; for Windows Simplified Chinese Edition
SOFTKEYBOARD_TYPE_C1	equ 0x0002

endif  ;; _IMM_

.list
