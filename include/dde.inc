ifndef _DDEHEADER_INCLUDED_
.xlist
_DDEHEADER_INCLUDED_ equ 1

ifndef _WINDEF_
include windef.inc
.xlist
endif


WM_DDE_FIRST		equ 0x03E0
WM_DDE_INITIATE		equ WM_DDE_FIRST
WM_DDE_TERMINATE	equ WM_DDE_FIRST+1
WM_DDE_ADVISE		equ WM_DDE_FIRST+2
WM_DDE_UNADVISE		equ WM_DDE_FIRST+3
WM_DDE_ACK		equ WM_DDE_FIRST+4
WM_DDE_DATA		equ WM_DDE_FIRST+5
WM_DDE_REQUEST		equ WM_DDE_FIRST+6
WM_DDE_POKE		equ WM_DDE_FIRST+7
WM_DDE_EXECUTE		equ WM_DDE_FIRST+8
WM_DDE_LAST		equ WM_DDE_FIRST+8

DDEACK			STRUC
usFlags			dw ?
DDEACK			ENDS

DDEADVISE		STRUC
usFlags			dw ?
cfFormat		dw ?
DDEADVISE		ENDS

DDEDATA			STRUC
usFlags			dw ?
cfFormat		dw ?
Value			db ?
DDEDATA			ENDS

DDEPOKE			STRUC
usFlags			dw ?
cfFormat		dw ?
Value			db ?
DDEPOKE			ENDS

DDELN			STRUC
usFlags			dw ?
cfFormat		dw ?
DDELN			ENDS


DDEUP			STRUC
usFlags			dw ?
cfFormat		dw ?
rgb			db ?
DDEUP			ENDS


;BOOL
DdeSetQualityOfService proto WINAPI \
	    hwndClient: HWND,
	       pqosNew: PSECURITY_QUALITY_OF_SERVICE,
	      pqosPrev: PSECURITY_QUALITY_OF_SERVICE

;BOOL
ImpersonateDdeClientWindow proto WINAPI \
	    hWndClient: HWND,
	    hWndServer: HWND

;LONG
PackDDElParam proto WINAPI \
		   msg: UINT,
		  uiLo: UINT,
		  uiHi: UINT
;BOOL
UnpackDDElParam proto WINAPI \
		   msg: UINT,
		lParam: LONG,
		 puiLo: PUINT,
		 puiHi: PUINT
;BOOL
FreeDDElParam proto WINAPI \
		   msg: UINT,
		lParam: LONG
;LONG
ReuseDDElParam proto WINAPI \
		lParam: LONG,
		 msgIn: UINT,
		msgOut: UINT,
		  uiLo: UINT,
		  uiHi: UINT
.list
endif


