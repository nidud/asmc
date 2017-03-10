ifndef _DDEHEADER_INCLUDED_
.xlist
;
; Dynamic Data Exchange structures and definitions
;
_DDEHEADER_INCLUDED_ equ 1

ifndef _WINDEF_
include windef.inc
.xlist
endif

;; DDE window messages

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

;;----------------------------------------------------------------------------
;;	 DDEACK structure
;;
;;	Structure of wStatus (LOWORD(lParam)) in WM_DDE_ACK message
;;	 sent in response to a WM_DDE_DATA, WM_DDE_REQUEST, WM_DDE_POKE,
;;	 WM_DDE_ADVISE, or WM_DDE_UNADVISE message.
;;
;;----------------------------------------------------------------------------

; RECORD
;	bAppReturnCode: 8,
;	reserved:	6,
;	fBusy:		1,
;	fAck:		1

DDEACK			STRUC
usFlags			dw ?
DDEACK			ENDS


;;----------------------------------------------------------------------------
;;	 DDEADVISE structure
;;
;;	WM_DDE_ADVISE parameter structure for hOptions (LOWORD(lParam))
;;
;;----------------------------------------------------------------------------

; RECORD
;	reserved:	14,
;	fDeferUpd:	1,
;	fAckReq:	1

DDEADVISE		STRUC
usFlags			dw ?
cfFormat		dw ?
DDEADVISE		ENDS


;;----------------------------------------------------------------------------
;;	 DDEDATA structure
;;
;;	 WM_DDE_DATA parameter structure for hData (LOWORD(lParam)).
;;	 The actual size of this structure depends on the size of
;;	 the Value array.
;;
;;----------------------------------------------------------------------------

; RECORD
;	unused:		12,
;	fResponse:	1,
;	fRelease:	1,
;	reserved:	1,
;	fAckReq:	1

DDEDATA			STRUC
usFlags			dw ?
cfFormat		dw ?
Value			db ?
DDEDATA			ENDS


;;----------------------------------------------------------------------------
;;	DDEPOKE structure
;;
;;	WM_DDE_POKE parameter structure for hData (LOWORD(lParam)).
;;	 The actual size of this structure depends on the size of
;;	 the Value array.
;;
;;----------------------------------------------------------------------------

; RECORD
;	unused:		13,  ;; Earlier versions of DDE.H incorrectly
;			     ;; 12 unused bits.
;	fRelease:	1,
;	fReserved:	2

DDEPOKE			STRUC
usFlags			dw ?
cfFormat		dw ?
Value			db ?	;; This member was named rgb[1] in previous
				;; versions of DDE.H
DDEPOKE			ENDS

;;------------------------------------------------------------------------------
;; The following typedef's were used in previous versions of the Windows SDK.
;; They are still valid.  The above typedef's define exactly the same structures
;; as those below.  The above typedef names are recommended, however, as they
;; are more meaningful.
;;
;; Note that the DDEPOKE structure typedef'ed in earlier versions of DDE.H did
;; not correctly define the bit positions.
;;------------------------------------------------------------------------------

; RECORD
;	unused:		13,
;	fRelease:	1,
;	fDeferUpd:	1,
;	fAckReq:	1

DDELN			STRUC
usFlags			dw ?
cfFormat		dw ?
DDELN			ENDS

; RECORD
;	unused:		12,
;	fAck:		1,
;	fRelease:	1,
;	fReserved:	1,
;	fAckReq:	1

DDEUP			STRUC
usFlags			dw ?
cfFormat		dw ?
rgb			db ?
DDEUP			ENDS

;;
;; DDE SECURITY
;;

;BOOL
DdeSetQualityOfService proto _CType \
	    hwndClient: HWND,
	       pqosNew: PSECURITY_QUALITY_OF_SERVICE,
	      pqosPrev: PSECURITY_QUALITY_OF_SERVICE

;BOOL
ImpersonateDdeClientWindow proto _CType \
	    hWndClient: HWND,
	    hWndServer: HWND

;;
;; DDE message packing APIs
;;
;LONG
PackDDElParam proto _CType \
		   msg: UINT,
		  uiLo: UINT,
		  uiHi: UINT
;BOOL
UnpackDDElParam proto _CType \
		   msg: UINT,
		lParam: LONG,
		 puiLo: PUINT,
		 puiHi: PUINT
;BOOL
FreeDDElParam proto _CType \
		   msg: UINT,
		lParam: LONG
;LONG
ReuseDDElParam proto _CType \
		lParam: LONG,
		 msgIn: UINT,
		msgOut: UINT,
		  uiLo: UINT,
		  uiHi: UINT
.list
endif ;; _DDEHEADER_INCLUDED_


