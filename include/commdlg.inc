ifndef _INC_COMMDLG
.xlist
_INC_COMMDLG equ 1
;;
;; This module defines the 32-Bit Common Dialog APIs
;;

;#include <pshpack1.h>	       ;; Assume byte packing throughout

if(WINVER GE 0x0400)
ifndef SNDMSG
SNDMSG			equ <AfxSendMessage>
endif ;; ifndef SNDMSG
endif ;; WINVER GE 0x0400

LPOFNHOOKPROC_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPOFNHOOKPROC	typedef ptr LPOFNHOOKPROC_T

OPENFILENAMEA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
lpstrFilter		LPCSTR ?
lpstrCustomFilter	LPSTR ?
nMaxCustFilter		dd ?
nFilterIndex		dd ?
lpstrFile		LPSTR ?
nMaxFile		dd ?
lpstrFileTitle		LPSTR ?
nMaxFileTitle		dd ?
lpstrInitialDir		LPCSTR ?
lpstrTitle		LPCSTR ?
Flags			dd ?
nFileOffset		dw ?
nFileExtension		dw ?
lpstrDefExt		LPCSTR ?
lCustData		LPARAM ?
lpfnHook		LPOFNHOOKPROC ?
lpTemplateName		LPCSTR ?
OPENFILENAMEA		ENDS
LPOPENFILENAMEA		typedef ptr OPENFILENAMEA

OPENFILENAMEW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
lpstrFilter		LPCWSTR ?
lpstrCustomFilter	LPWSTR ?
nMaxCustFilter		dd ?
nFilterIndex		dd ?
lpstrFile		LPWSTR ?
nMaxFile		dd ?
lpstrFileTitle		LPWSTR ?
nMaxFileTitle		dd ?
lpstrInitialDir		LPCWSTR ?
lpstrTitle		LPCWSTR ?
Flags			dd ?
nFileOffset		dw ?
nFileExtension		dw ?
lpstrDefExt		LPCWSTR ?
lCustData		LPARAM ?
lpfnHook		LPOFNHOOKPROC ?
lpTemplateName		LPCWSTR ?
OPENFILENAMEW		ENDS

LPOPENFILENAMEW		typedef ptr OPENFILENAMEW
ifdef _UNICODE
OPENFILENAME		typedef OPENFILENAMEW
LPOPENFILENAME		typedef LPOPENFILENAMEW
else
OPENFILENAME		typedef OPENFILENAMEA
LPOPENFILENAME		typedef LPOPENFILENAMEA
endif ;; UNICODE

;BOOL
;BOOL
ifdef _UNICODE
GetOpenFileName		equ <GetOpenFileNameW>
else
GetOpenFileName		equ <GetOpenFileNameA>
endif ;; NOT UNICODE
;BOOL
;BOOL
ifdef _UNICODE
GetSaveFileName		equ <GetSaveFileNameW>
else
GetSaveFileName		equ <GetSaveFileNameA>
endif ;; NOT UNICODE
;short
GetFileTitleA proto _CType \
		      : LPCSTR,
		      : LPSTR,
		      : WORD
GetFileTitleW proto _CType \
		      : LPCWSTR,
		      : LPWSTR,
		      : WORD
ifdef _UNICODE
GetFileTitle		equ <GetFileTitleW>
else
GetFileTitle		equ <GetFileTitleA>
endif ;; NOT UNICODE

OFN_READONLY		equ 0x00000001
OFN_OVERWRITEPROMPT	equ 0x00000002
OFN_HIDEREADONLY	equ 0x00000004
OFN_NOCHANGEDIR		equ 0x00000008
OFN_SHOWHELP		equ 0x00000010
OFN_ENABLEHOOK		equ 0x00000020
OFN_ENABLETEMPLATE	equ 0x00000040
OFN_ENABLETEMPLATEHANDLE equ 0x00000080
OFN_NOVALIDATE		equ 0x00000100
OFN_ALLOWMULTISELECT	equ 0x00000200
OFN_EXTENSIONDIFFERENT	equ 0x00000400
OFN_PATHMUSTEXIST	equ 0x00000800
OFN_FILEMUSTEXIST	equ 0x00001000
OFN_CREATEPROMPT	equ 0x00002000
OFN_SHAREAWARE		equ 0x00004000
OFN_NOREADONLYRETURN	equ 0x00008000
OFN_NOTESTFILECREATE	equ 0x00010000
OFN_NONETWORKBUTTON	equ 0x00020000
OFN_NOLONGNAMES		equ 0x00040000	    ;; force no long names for 4.x modules
if(WINVER GE 0x0400)
OFN_EXPLORER		equ 0x00080000	    ;; new look commdlg
OFN_NODEREFERENCELINKS	equ 0x00100000
OFN_LONGNAMES		equ 0x00200000	    ;; force long names for 3.x modules
OFN_ENABLEINCLUDENOTIFY equ 0x00400000	    ;; send include message to callback
OFN_ENABLESIZING	equ 0x00800000
endif ;; WINVER GE 0x0400

;; Return values for the registered message sent to the hook function
;; when a sharing violation occurs.  OFN_SHAREFALLTHROUGH allows the
;; filename to be accepted, OFN_SHARENOWARN rejects the name but puts
;; up no warning (returned when the app has already put up a warning
;; message), and OFN_SHAREWARN puts up the default warning message
;; for sharing violations.
;;
;; Note:  Undefined return values map to OFN_SHAREWARN, but are
;;	  reserved for future use.

OFN_SHAREFALLTHROUGH	equ 2
OFN_SHARENOWARN		equ 1
OFN_SHAREWARN		equ 0

;UINT
LPCCHOOKPROC_T typedef proto _CType \
			: HWND,
			: UINT,
			: WPARAM,
			: LPARAM
LPCCHOOKPROC typedef ptr LPCCHOOKPROC_T

if(WINVER GE 0x0400)
;; Structure used for all file based OpenFileName notifications
OFNOTIFYA		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEA ?
pszFile			LPSTR ? ;; May be NULL
OFNOTIFYA		ENDS
LPOFNOTIFYA		typedef ptr OFNOTIFYA
;; Structure used for all file based OpenFileName notifications
OFNOTIFYW		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEW ?
pszFile			LPWSTR ?	;; May be NULL
OFNOTIFYW		ENDS
LPOFNOTIFYW		typedef ptr OFNOTIFYW
ifdef _UNICODE
OFNOTIFY		typedef OFNOTIFYW
LPOFNOTIFY		typedef LPOFNOTIFYW
else
OFNOTIFY		typedef OFNOTIFYA
LPOFNOTIFY		typedef LPOFNOTIFYA
endif ;; UNICODE


;; Structure used for all object based OpenFileName notifications
OFNOTIFYEXA		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEA ?
psf			LPVOID ?
pidl			LPVOID ?	;; May be NULL
OFNOTIFYEXA		ENDS
LPOFNOTIFYEXA		typedef ptr OFNOTIFYEXA
;; Structure used for all object based OpenFileName notifications
OFNOTIFYEXW		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEW ?
psf			LPVOID ?
pidl			LPVOID ?	;; May be NULL
OFNOTIFYEXW		ENDS
LPOFNOTIFYEXW		typedef ptr OFNOTIFYEXW
ifdef _UNICODE
OFNOTIFYEX		typedef OFNOTIFYEXW
LPOFNOTIFYEX		typedef LPOFNOTIFYEXW
else
OFNOTIFYEX		typedef OFNOTIFYEXA
LPOFNOTIFYEX		typedef LPOFNOTIFYEXA
endif ;; UNICODE


CDN_FIRST		equ (0U-601U)
CDN_LAST		equ (0U-699U)

;; Notifications when Open or Save dialog status changes
CDN_INITDONE		equ (CDN_FIRST - 0x0000)
CDN_SELCHANGE		equ (CDN_FIRST - 0x0001)
CDN_FOLDERCHANGE	equ (CDN_FIRST - 0x0002)
CDN_SHAREVIOLATION	equ (CDN_FIRST - 0x0003)
CDN_HELP		equ (CDN_FIRST - 0x0004)
CDN_FILEOK		equ (CDN_FIRST - 0x0005)
CDN_TYPECHANGE		equ (CDN_FIRST - 0x0006)
CDN_INCLUDEITEM		equ (CDN_FIRST - 0x0007)

CDM_FIRST		equ (WM_USER + 100)
CDM_LAST		equ (WM_USER + 200)

;; Messages to query information from the Open or Save dialogs

;; lParam = pointer to text buffer that gets filled in
;; wParam = max number of characters of the text buffer (including NULL)
;; return = < 0 if error; number of characters needed (including NULL)
CDM_GETSPEC		equ (CDM_FIRST + 0x0000)
CommDlg_OpenSave_GetSpecA macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETSPEC, _cbmax, _psz)>
	endm

CommDlg_OpenSave_GetSpecW macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETSPEC, _cbmax, _psz)>
	endm

ifdef _UNICODE
CommDlg_OpenSave_GetSpec equ <CommDlg_OpenSave_GetSpecW>
else
CommDlg_OpenSave_GetSpec equ <CommDlg_OpenSave_GetSpecA>
endif ;; NOT UNICODE

;; lParam = pointer to text buffer that gets filled in
;; wParam = max number of characters of the text buffer (including NULL)
;; return = < 0 if error; number of characters needed (including NULL)
CDM_GETFILEPATH		equ (CDM_FIRST + 0x0001)
CommDlg_OpenSave_GetFilePathA macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFILEPATH, _cbmax, _psz)>
	endm

CommDlg_OpenSave_GetFilePathW macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFILEPATH, _cbmax, _psz)>
	endm

ifdef _UNICODE
CommDlg_OpenSave_GetFilePath equ <CommDlg_OpenSave_GetFilePathW>
else
CommDlg_OpenSave_GetFilePath equ <CommDlg_OpenSave_GetFilePathA>
endif ;; NOT UNICODE

;; lParam = pointer to text buffer that gets filled in
;; wParam = max number of characters of the text buffer (including NULL)
;; return = < 0 if error; number of characters needed (including NULL)
CDM_GETFOLDERPATH	equ (CDM_FIRST + 0x0002)
CommDlg_OpenSave_GetFolderPathA macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFOLDERPATH, _cbmax, _psz)>
	endm

CommDlg_OpenSave_GetFolderPathW macro _hdlg, _psz, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFOLDERPATH, _cbmax, _psz)>
	endm

ifdef _UNICODE
CommDlg_OpenSave_GetFolderPath equ <CommDlg_OpenSave_GetFolderPathW>
else
CommDlg_OpenSave_GetFolderPath equ <CommDlg_OpenSave_GetFolderPathA>
endif ;; NOT UNICODE

;; lParam = pointer to ITEMIDLIST buffer that gets filled in
;; wParam = size of the ITEMIDLIST buffer
;; return = < 0 if error; length of buffer needed
CDM_GETFOLDERIDLIST	equ (CDM_FIRST + 0x0003)
CommDlg_OpenSave_GetFolderIDList macro _hdlg, _pidl, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFOLDERIDLIST, _cbmax, _pidl)>
	endm

;; lParam = pointer to a string
;; wParam = ID of control to change
;; return = not used
CDM_SETCONTROLTEXT	equ (CDM_FIRST + 0x0004)
CommDlg_OpenSave_SetControlText macro _hdlg, _id, _text
	exitm<SNDMSG(_hdlg, CDM_SETCONTROLTEXT, _id, _text)>
	endm

;; lParam = not used
;; wParam = ID of control to change
;; return = not used
CDM_HIDECONTROL		equ (CDM_FIRST + 0x0005)
CommDlg_OpenSave_HideControl macro _hdlg, _id
	exitm<SNDMSG(_hdlg, CDM_HIDECONTROL, _id, 0)>
	endm

;; lParam = pointer to default extension (no dot)
;; wParam = not used
;; return = not used
CDM_SETDEFEXT		equ (CDM_FIRST + 0x0006)
CommDlg_OpenSave_SetDefExt macro _hdlg, _pszext
	exitm<SNDMSG(_hdlg, CDM_SETDEFEXT, 0, _pszext)>
	endm

endif ;; WINVER GE 0x0400

ifndef _MAC
CHOOSECOLORA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HWND ?
rgbResult		COLORREF ?
lpCustColors		PVOID ?;COLORREF ?
Flags			dd ?
lCustData		LPARAM ?
lpfnHook		LPCCHOOKPROC ?
lpTemplateName		LPCSTR ?
CHOOSECOLORA		ENDS
LPCHOOSECOLORA		typedef ptr CHOOSECOLORA
CHOOSECOLORW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HWND ?
rgbResult		COLORREF ?
lpCustColors		PVOID ?;COLORREF* ?
Flags			dd ?
lCustData		LPARAM ?
lpfnHook		LPCCHOOKPROC ?
lpTemplateName		LPCWSTR ?
CHOOSECOLORW		ENDS
LPCHOOSECOLORW		typedef ptr CHOOSECOLORW
ifdef _UNICODE
CHOOSECOLOR		typedef CHOOSECOLORW
LPCHOOSECOLOR		typedef LPCHOOSECOLORW
else
CHOOSECOLOR		typedef CHOOSECOLORA
LPCHOOSECOLOR		typedef LPCHOOSECOLORA
endif ;; UNICODE
else
CHOOSECOLORA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HWND ?
rgbResult		COLORREF ?
lpCustColors		COLORREF* ?
Flags			dd ?
lCustData		LPARAM ?
lpfnHook		LPCCHOOKPROC ?
lpTemplateName		LPCSTR ?
lpEditInfo		LPEDITMENU ?
CHOOSECOLORA		ENDS
LPCHOOSECOLORA		typedef ptr CHOOSECOLORA
CHOOSECOLORW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HWND ?
rgbResult		COLORREF ?
lpCustColors		COLORREF* ?
Flags			dd ?
lCustData		LPARAM ?
lpfnHook		LPCCHOOKPROC ?
lpTemplateName		LPCWSTR ?
lpEditInfo		LPEDITMENU ?
CHOOSECOLORW		ENDS
LPCHOOSECOLORW		typedef ptr CHOOSECOLORW
ifdef _UNICODE
CHOOSECOLOR		typedef CHOOSECOLORW
LPCHOOSECOLOR		typedef LPCHOOSECOLORW
else
CHOOSECOLOR		typedef CHOOSECOLORA
LPCHOOSECOLOR		typedef LPCHOOSECOLORA
endif ;; UNICODE
endif ;;_MAC

;BOOL
;BOOL
ifdef _UNICODE
ChooseColor		equ <ChooseColorW>
else
ChooseColor		equ <ChooseColorA>
endif ;; NOT UNICODE

CC_RGBINIT		equ 0x00000001
CC_FULLOPEN		equ 0x00000002
CC_PREVENTFULLOPEN	equ 0x00000004
CC_SHOWHELP		equ 0x00000008
CC_ENABLEHOOK		equ 0x00000010
CC_ENABLETEMPLATE	equ 0x00000020
CC_ENABLETEMPLATEHANDLE equ 0x00000040
if(WINVER GE 0x0400)
CC_SOLIDCOLOR		equ 0x00000080
CC_ANYCOLOR		equ 0x00000100
endif ;; WINVER GE 0x0400

;UINT
LPFRHOOKPROC_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPFRHOOKPROC typedef ptr LPFRHOOKPROC_T

FINDREPLACEA		STRUC
lStructSize		dd ?	;; size of this struct 0x20
hwndOwner		HWND ?	;; handle to owner's window
hInstance		HINSTANCE ?	;; instance handle of.EXE that
				;; contains cust. dlg. template
Flags			dd ?	;; one or more of the FR_??
lpstrFindWhat		LPSTR ? ;; ptr. to search string
lpstrReplaceWith	LPSTR ? ;; ptr. to replace string
wFindWhatLen		dw ?	;; size of find buffer
wReplaceWithLen		dw ?	;; size of replace buffer
lCustData		LPARAM ?	;; data passed to hook fn.
lpfnHook		LPFRHOOKPROC ?	;; ptr. to hook fn. or NULL
lpTemplateName		LPCSTR ?	;; custom template name
FINDREPLACEA		ENDS
LPFINDREPLACEA		typedef ptr FINDREPLACEA
FINDREPLACEW		STRUC
lStructSize		dd ?	;; size of this struct 0x20
hwndOwner		HWND ?	;; handle to owner's window
hInstance		HINSTANCE ?	;; instance handle of.EXE that
				;; contains cust. dlg. template
Flags			dd ?	;; one or more of the FR_??
lpstrFindWhat		LPWSTR ?	;; ptr. to search string
lpstrReplaceWith	LPWSTR ?	;; ptr. to replace string
wFindWhatLen		dw ?	;; size of find buffer
wReplaceWithLen		dw ?	;; size of replace buffer
lCustData		LPARAM ?	;; data passed to hook fn.
lpfnHook		LPFRHOOKPROC ?	;; ptr. to hook fn. or NULL
lpTemplateName		LPCWSTR ?	;; custom template name
FINDREPLACEW		ENDS
LPFINDREPLACEW		typedef ptr FINDREPLACEW
ifdef _UNICODE
FINDREPLACE		typedef FINDREPLACEW
LPFINDREPLACE		typedef LPFINDREPLACEW
else
FINDREPLACE		typedef FINDREPLACEA
LPFINDREPLACE		typedef LPFINDREPLACEA
endif ;; UNICODE

FR_DOWN			equ 0x00000001
FR_WHOLEWORD		equ 0x00000002
FR_MATCHCASE		equ 0x00000004
FR_FINDNEXT		equ 0x00000008
FR_REPLACE		equ 0x00000010
FR_REPLACEALL		equ 0x00000020
FR_DIALOGTERM		equ 0x00000040
FR_SHOWHELP		equ 0x00000080
FR_ENABLEHOOK		equ 0x00000100
FR_ENABLETEMPLATE	equ 0x00000200
FR_NOUPDOWN		equ 0x00000400
FR_NOMATCHCASE		equ 0x00000800
FR_NOWHOLEWORD		equ 0x00001000
FR_ENABLETEMPLATEHANDLE equ 0x00002000
FR_HIDEUPDOWN		equ 0x00004000
FR_HIDEMATCHCASE	equ 0x00008000
FR_HIDEWHOLEWORD	equ 0x00010000

;HWND
;HWND
ifdef _UNICODE
FindText		equ <FindTextW>
else
FindText		equ <FindTextA>
endif ;; NOT UNICODE
ifndef _MAC
;HWND
;HWND
ifdef _UNICODE
ReplaceText		equ <ReplaceTextW>
else
ReplaceText		equ <ReplaceTextA>
endif ;; NOT UNICODE
else
;HWND
;HWND
ifdef _UNICODE
AfxReplaceText		equ <AfxReplaceTextW>
else
AfxReplaceText		equ <AfxReplaceTextA>
endif ;; NOT UNICODE
endif

;UINT
LPCFHOOKPROC_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPCFHOOKPROC typedef ptr LPCFHOOKPROC_T

CHOOSEFONTA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?	;; caller's window handle
hDC			HDC ?	;; printer DC/IC or NULL
lpLogFont		LPLOGFONTA ?	;; ptr. to a LOGFONT struct
iPointSize		SINT ?	;; 10 * size in points of selected font
Flags			dd ?	;; enum. type flags
rgbColors		COLORREF ?	;; returned text color
lCustData		LPARAM ?	;; data passed to hook fn.
lpfnHook		LPCFHOOKPROC ?	;; ptr. to hook function
lpTemplateName		LPCSTR ?	;; custom template name
hInstance		HINSTANCE ?	;; instance handle of.EXE that
				;; contains cust. dlg. template
lpszStyle		LPSTR ? ;; return the style field here
				;; must be LF_FACESIZE or bigger
nFontType		dw ?	;; same value reported to the EnumFonts
				;; call back with the extra FONTTYPE_
				;; bits added
___MISSING_ALIGNMENT__	dw ?
nSizeMin		SINT ?	;; minimum pt size allowed &
nSizeMax		SINT ?	;; max pt size allowed if
				;; CF_LIMITSIZE is used
CHOOSEFONTA		ENDS
LPCHOOSEFONTA		typedef ptr CHOOSEFONTA
CHOOSEFONTW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?		;; caller's window handle
hDC			HDC ?		;; printer DC/IC or NULL
lpLogFont		LPLOGFONTW ?	;; ptr. to a LOGFONT struct
iPointSize		SINT ?		;; 10 * size in points of selected font
Flags			dd ?		;; enum. type flags
rgbColors		COLORREF ?	;; returned text color
lCustData		LPARAM ?	;; data passed to hook fn.
lpfnHook		LPCFHOOKPROC ?	;; ptr. to hook function
lpTemplateName		LPCWSTR ?	;; custom template name
hInstance		HINSTANCE ?	;; instance handle of.EXE that
					;; contains cust. dlg. template
lpszStyle		LPWSTR ?	;; return the style field here
					;; must be LF_FACESIZE or bigger
nFontType		dw ?		;; same value reported to the EnumFonts
					;; call back with the extra FONTTYPE_
					;; bits added
___MISSING_ALIGNMENT__	dw ?
nSizeMin		SINT ?	;; minimum pt size allowed &
nSizeMax		SINT ?	;; max pt size allowed if
				;; CF_LIMITSIZE is used
CHOOSEFONTW		ENDS
LPCHOOSEFONTW		typedef ptr CHOOSEFONTW
ifdef _UNICODE
CHOOSEFONT		typedef CHOOSEFONTW
LPCHOOSEFONT		typedef LPCHOOSEFONTW
else
CHOOSEFONT		typedef CHOOSEFONTA
LPCHOOSEFONT		typedef LPCHOOSEFONTA
endif ;; UNICODE

;BOOL
;BOOL
ifdef _UNICODE
ChooseFont		equ <ChooseFontW>
else
ChooseFont		equ <ChooseFontA>
endif ;; NOT UNICODE

CF_SCREENFONTS		equ 0x00000001
CF_PRINTERFONTS		equ 0x00000002
CF_BOTH			equ (CF_SCREENFONTS OR CF_PRINTERFONTS)
CF_SHOWHELP		equ 0x00000004
CF_ENABLEHOOK		equ 0x00000008
CF_ENABLETEMPLATE	equ 0x00000010
CF_ENABLETEMPLATEHANDLE equ 0x00000020
CF_INITTOLOGFONTSTRUCT	equ 0x00000040
CF_USESTYLE		equ 0x00000080
CF_EFFECTS		equ 0x00000100
CF_APPLY		equ 0x00000200
CF_ANSIONLY		equ 0x00000400
if(WINVER GE 0x0400)
CF_SCRIPTSONLY		equ CF_ANSIONLY
endif ;; WINVER GE 0x0400
CF_NOVECTORFONTS	equ 0x00000800
CF_NOOEMFONTS		equ CF_NOVECTORFONTS
CF_NOSIMULATIONS	equ 0x00001000
CF_LIMITSIZE		equ 0x00002000
CF_FIXEDPITCHONLY	equ 0x00004000
CF_WYSIWYG		equ 0x00008000 ;; must also have CF_SCREENFONTS AND CF_PRINTERFONTS
CF_FORCEFONTEXIST	equ 0x00010000
CF_SCALABLEONLY		equ 0x00020000
CF_TTONLY		equ 0x00040000
CF_NOFACESEL		equ 0x00080000
CF_NOSTYLESEL		equ 0x00100000
CF_NOSIZESEL		equ 0x00200000
if(WINVER GE 0x0400)
CF_SELECTSCRIPT		equ 0x00400000
CF_NOSCRIPTSEL		equ 0x00800000
CF_NOVERTFONTS		equ 0x01000000
endif ;; WINVER GE 0x0400

;; these are extra nFontType bits that are added to what is returned to the
;; EnumFonts callback routine

SIMULATED_FONTTYPE	equ 0x8000
PRINTER_FONTTYPE	equ 0x4000
SCREEN_FONTTYPE		equ 0x2000
BOLD_FONTTYPE		equ 0x0100
ITALIC_FONTTYPE		equ 0x0200
REGULAR_FONTTYPE	equ 0x0400

;; EnumFonts callback routine only uses these bits, so we can use the rest

;; #define RASTER_FONTTYPE     0x001
;; #define DEVICE_FONTTYPE     0x002
;; #define TRUETYPE_FONTTYPE   0x004

ifdef WINNT
OPENTYPE_FONTTYPE	equ 0x10000
TYPE1_FONTTYPE		equ 0x20000
DSIG_FONTTYPE		equ 0x40000
endif

WM_CHOOSEFONT_GETLOGFONT equ (WM_USER + 1)
WM_CHOOSEFONT_SETLOGFONT equ (WM_USER + 101)
WM_CHOOSEFONT_SETFLAGS	equ (WM_USER + 102)

;; strings used to obtain unique window message for communication
;; between dialog and caller

LBSELCHSTRINGA		equ <"commdlg_LBSelChangedNotify">
SHAREVISTRINGA		equ <"commdlg_ShareViolation">
FILEOKSTRINGA		equ <"commdlg_FileNameOK">
COLOROKSTRINGA		equ <"commdlg_ColorOK">
SETRGBSTRINGA		equ <"commdlg_SetRGBColor">
HELPMSGSTRINGA		equ <"commdlg_help">
FINDMSGSTRINGA		equ <"commdlg_FindReplace">

LBSELCHSTRINGW		equ <L"commdlg_LBSelChangedNotify">
SHAREVISTRINGW		equ <L"commdlg_ShareViolation">
FILEOKSTRINGW		equ <L"commdlg_FileNameOK">
COLOROKSTRINGW		equ <L"commdlg_ColorOK">
SETRGBSTRINGW		equ <L"commdlg_SetRGBColor">
HELPMSGSTRINGW		equ <L"commdlg_help">
FINDMSGSTRINGW		equ <L"commdlg_FindReplace">

ifdef _UNICODE
LBSELCHSTRING		equ LBSECHSTRINGW
SHAREVISTRING		equ SHAREVISTRINGW
FILEOKSTRING		equ FILEOKSTRINGW
COLOROKSTRING		equ COLOROKSTRINGW
SETRGBSTRING		equ SETRGBSTRINGW
HELPMSGSTRING		equ HEPMSGSTRINGW
FINDMSGSTRING		equ FINDMSGSTRINGW
else
LBSELCHSTRING		equ LBSECHSTRINGA
SHAREVISTRING		equ SHAREVISTRINGA
FILEOKSTRING		equ FILEOKSTRINGA
COLOROKSTRING		equ COLOROKSTRINGA
SETRGBSTRING		equ SETRGBSTRINGA
HELPMSGSTRING		equ HEPMSGSTRINGA
FINDMSGSTRING		equ FINDMSGSTRINGA
endif

;; HIWORD values for lParam of commdlg_LBSelChangeNotify message
CD_LBSELNOITEMS		equ -1
CD_LBSELCHANGE		equ 0
CD_LBSELSUB		equ 1
CD_LBSELADD		equ 2

;UINT
LPPRINTHOOKPROC_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPPRINTHOOKPROC typedef ptr LPPRINTHOOKPROC_T

LPSETUPHOOKPROC_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPSETUPHOOKPROC typedef ptr LPSETUPHOOKPROC_T

PRINTDLGA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
hDC			HDC ?
Flags			dd ?
nFromPage		dw ?
nToPage			dw ?
nMinPage		dw ?
nMaxPage		dw ?
nCopies			dw ?
hInstance		HINSTANCE ?
lCustData		LPARAM ?
lpfnPrintHook		LPPRINTHOOKPROC ?
lpfnSetupHook		LPSETUPHOOKPROC ?
lpPrintTemplateName	LPCSTR ?
lpSetupTemplateName	LPCSTR ?
hPrintTemplate		HGLOBAL ?
hSetupTemplate		HGLOBAL ?
PRINTDLGA		ENDS
LPPRINTDLGA		typedef ptr PRINTDLGA

PRINTDLGW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
hDC			HDC ?
Flags			dd ?
nFromPage		dw ?
nToPage			dw ?
nMinPage		dw ?
nMaxPage		dw ?
nCopies			dw ?
hInstance		HINSTANCE ?
lCustData		LPARAM ?
lpfnPrintHook		LPPRINTHOOKPROC ?
lpfnSetupHook		LPSETUPHOOKPROC ?
lpPrintTemplateName	LPCWSTR ?
lpSetupTemplateName	LPCWSTR ?
hPrintTemplate		HGLOBAL ?
hSetupTemplate		HGLOBAL ?
PRINTDLGW		ENDS
LPPRINTDLGW		typedef ptr PRINTDLGW
ifdef _UNICODE
PRINTDLG		typedef PRINTDLGW
LPPRINTDLG		typedef LPPRINTDLGW
else
PRINTDLG		typedef PRINTDLGA
LPPRINTDLG		typedef LPPRINTDLGA
endif ;; UNICODE

;BOOL
;BOOL
ifdef _UNICODE
PrintDlg		equ <PrintDlgW>
else
PrintDlg		equ <PrintDlgA>
endif ;; NOT UNICODE

PD_ALLPAGES		equ 0x00000000
PD_SELECTION		equ 0x00000001
PD_PAGENUMS		equ 0x00000002
PD_NOSELECTION		equ 0x00000004
PD_NOPAGENUMS		equ 0x00000008
PD_COLLATE		equ 0x00000010
PD_PRINTTOFILE		equ 0x00000020
PD_PRINTSETUP		equ 0x00000040
PD_NOWARNING		equ 0x00000080
PD_RETURNDC		equ 0x00000100
PD_RETURNIC		equ 0x00000200
PD_RETURNDEFAULT	equ 0x00000400
PD_SHOWHELP		equ 0x00000800
PD_ENABLEPRINTHOOK	equ 0x00001000
PD_ENABLESETUPHOOK	equ 0x00002000
PD_ENABLEPRINTTEMPLATE	equ 0x00004000
PD_ENABLESETUPTEMPLATE	equ 0x00008000
PD_ENABLEPRINTTEMPLATEHANDLE equ 0x00010000
PD_ENABLESETUPTEMPLATEHANDLE equ 0x00020000
PD_USEDEVMODECOPIES	equ 0x00040000
PD_USEDEVMODECOPIESANDCOLLATE equ 0x00040000
PD_DISABLEPRINTTOFILE	equ 0x00080000
PD_HIDEPRINTTOFILE	equ 0x00100000
PD_NONETWORKBUTTON	equ 0x00200000

DEVNAMES		STRUC
wDriverOffset		dw ?
wDeviceOffset		dw ?
wOutputOffset		dw ?
wDefault		dw ?
DEVNAMES		ENDS

LPDEVNAMES		typedef ptr DEVNAMES

DN_DEFAULTPRN		equ 0x0001


;DWORD

if(WINVER GE 0x0400)
WM_PSD_PAGESETUPDLG	equ (WM_USER  )
WM_PSD_FULLPAGERECT	equ (WM_USER+1)
WM_PSD_MINMARGINRECT	equ (WM_USER+2)
WM_PSD_MARGINRECT	equ (WM_USER+3)
WM_PSD_GREEKTEXTRECT	equ (WM_USER+4)
WM_PSD_ENVSTAMPRECT	equ (WM_USER+5)
WM_PSD_YAFULLPAGERECT	equ (WM_USER+6)

LPPAGEPAINTHOOK_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPPAGEPAINTHOOK		typedef ptr LPPAGEPAINTHOOK_T

LPPAGESETUPHOOK_T typedef proto _CType \
		      : HWND,
		      : UINT,
		      : WPARAM,
		      : LPARAM
LPPAGESETUPHOOK		typedef ptr LPPAGESETUPHOOK_T

PAGESETUPDLGA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
Flags			dd ?
ptPaperSize		POINT <>
rtMinMargin		RECT <>
rtMargin		RECT <>
hInstance		HINSTANCE ?
lCustData		LPARAM ?
lpfnPageSetupHook	LPPAGESETUPHOOK ?
lpfnPagePaintHook	LPPAGEPAINTHOOK ?
lpPageSetupTemplateName LPCSTR ?
hPageSetupTemplate	HGLOBAL ?
PAGESETUPDLGA		ENDS
LPPAGESETUPDLGA		typedef ptr PAGESETUPDLGA

PAGESETUPDLGW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
Flags			dd ?
ptPaperSize		POINT <>
rtMinMargin		RECT <>
rtMargin		RECT <>
hInstance		HINSTANCE ?
lCustData		LPARAM ?
lpfnPageSetupHook	LPPAGESETUPHOOK ?
lpfnPagePaintHook	LPPAGEPAINTHOOK ?
lpPageSetupTemplateName LPCWSTR ?
hPageSetupTemplate	HGLOBAL ?
PAGESETUPDLGW		ENDS
LPPAGESETUPDLGW		typedef ptr PAGESETUPDLGW

ifdef _UNICODE
PAGESETUPDLG		typedef PAGESETUPDLGW
LPPAGESETUPDLG		typedef LPPAGESETUPDLGW
else
PAGESETUPDLG		typedef PAGESETUPDLGA
LPPAGESETUPDLG		typedef LPPAGESETUPDLGA
endif ;; UNICODE

;BOOL
PageSetupDlgA proto _CType \
		      : LPPAGESETUPDLGA
;BOOL
PageSetupDlgW proto _CType \
		      : LPPAGESETUPDLGW
ifdef _UNICODE
PageSetupDlg		equ <PageSetupDlgW>
else
PageSetupDlg		equ <PageSetupDlgA>
endif ;; NOT UNICODE

PSD_DEFAULTMINMARGINS	equ 0x00000000 ;; default (printer's)
PSD_INWININIINTLMEASURE equ 0x00000000 ;; 1st of 4 possible

PSD_MINMARGINS		equ 0x00000001 ;; use caller's
PSD_MARGINS		equ 0x00000002 ;; use caller's
PSD_INTHOUSANDTHSOFINCHES equ 0x00000004 ;; 2nd of 4 possible
PSD_INHUNDREDTHSOFMILLIMETERS equ 0x00000008 ;; 3rd of 4 possible
PSD_DISABLEMARGINS	equ 0x00000010
PSD_DISABLEPRINTER	equ 0x00000020
PSD_NOWARNING		equ 0x00000080 ;; must be same as PD_*
PSD_DISABLEORIENTATION	equ 0x00000100
PSD_RETURNDEFAULT	equ 0x00000400 ;; must be same as PD_*
PSD_DISABLEPAPER	equ 0x00000200
PSD_SHOWHELP		equ 0x00000800 ;; must be same as PD_*
PSD_ENABLEPAGESETUPHOOK equ 0x00002000 ;; must be same as PD_*
PSD_ENABLEPAGESETUPTEMPLATE equ 0x00008000 ;; must be same as PD_*
PSD_ENABLEPAGESETUPTEMPLATEHANDLE equ 0x00020000 ;; must be same as PD_*
PSD_ENABLEPAGEPAINTHOOK equ 0x00040000
PSD_DISABLEPAGEPAINTING equ 0x00080000
PSD_NONETWORKBUTTON	equ 0x00200000 ;; must be same as PD_*
endif ;; WINVER GE 0x0400

;#include <poppack.h>
.list
endif	;; NOT _INC_COMMDLG

