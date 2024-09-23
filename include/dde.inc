ifndef _DDEHEADER_INCLUDED_
define _DDEHEADER_INCLUDED_

ifndef _WINDEF_
include windef.inc
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

DdeSetQualityOfService proto WINAPI :HWND, :PSECURITY_QUALITY_OF_SERVICE, :PSECURITY_QUALITY_OF_SERVICE
ImpersonateDdeClientWindow proto WINAPI :HWND, :HWND
PackDDElParam proto WINAPI :UINT, :UINT, :UINT
UnpackDDElParam proto WINAPI :UINT, :LONG, :PUINT, :PUINT
FreeDDElParam proto WINAPI :UINT, :LONG
ReuseDDElParam proto WINAPI :LONG, :UINT, :UINT, :UINT, :UINT
endif


