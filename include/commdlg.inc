.pragma list(push, 0)
ifndef _INC_COMMDLG
define _INC_COMMDLG

if (WINVER GE 0x0500)
ifdef DEFINE_GUID
DEFINE_GUID(IID_IPrintDialogCallback, 0x5852a2c3, 0x6530, 0x11d1, 0xb6, 0xa3, 0x0, 0x0, 0xf8, 0x75, 0x7b, 0xf9)
DEFINE_GUID(IID_IPrintDialogServices, 0x509aaeda, 0x5639, 0x11d1, 0xb6, 0xa1, 0x0, 0x0, 0xf8, 0x75, 0x7b, 0xf9)
endif
endif

ifndef GUID_DEFS_ONLY

include prsht.inc

.pragma comment(lib, comdlg32)
ifndef _WIN64
.pragma pack(push, 1)
endif

if(WINVER GE 0x0400)
ifndef SNDMSG
SNDMSG equ <AfxSendMessage>
endif
endif

CALLBACK(LPOFNHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)

ifndef CDSIZEOF_STRUCT
CDSIZEOF_STRUCT macro structname, member
    exitm<structname.member + sizeof(structname.member)>
    endm
endif

OPENFILENAME_NT4A	STRUC
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
OPENFILENAME_NT4A	ENDS
LPOPENFILENAME_NT4A	typedef ptr OPENFILENAME_NT4A

OPENFILENAME_NT4W	STRUC
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
OPENFILENAME_NT4W	ENDS
LPOPENFILENAME_NT4W	typedef ptr OPENFILENAME_NT4W

ifdef _UNICODE
OPENFILENAME_NT4	typedef OPENFILENAME_NT4W
LPOPENFILENAME_NT4	typedef LPOPENFILENAME_NT4W
else
OPENFILENAME_NT4	typedef OPENFILENAME_NT4A
LPOPENFILENAME_NT4	typedef LPOPENFILENAME_NT4A
endif

OPENFILENAMEA		STRUC SIZE_T
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
ifdef _MAC
lpEditInfo		LPEDITMENU ?
lpstrPrompt		LPCSTR ?
endif
if (_WIN32_WINNT GE 0x0500)
pvReserved		PVOID ?
dwReserved		dd ?
FlagsEx			dd ?
endif
OPENFILENAMEA		ENDS
LPOPENFILENAMEA		typedef ptr OPENFILENAMEA

OPENFILENAMEW		STRUC SIZE_T
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
ifdef _MAC
lpEditInfo		LPEDITMENU ?
lpstrPrompt		LPCSTR ?
endif
if (_WIN32_WINNT GE 0x0500)
pvReserved		PVOID ?
dwReserved		dd ?
FlagsEx			dd ?
endif
OPENFILENAMEW		ENDS
LPOPENFILENAMEW		typedef ptr OPENFILENAMEW

ifdef _UNICODE
OPENFILENAME		typedef OPENFILENAMEW
LPOPENFILENAME		typedef LPOPENFILENAMEW
else
OPENFILENAME		typedef OPENFILENAMEA
LPOPENFILENAME		typedef LPOPENFILENAMEA
endif

;BOOL
GetOpenFileNameA proto WINAPI :LPOPENFILENAMEA
;BOOL
GetOpenFileNameW proto WINAPI :LPOPENFILENAMEW
ifdef _UNICODE
GetOpenFileName equ <GetOpenFileNameW>
else
GetOpenFileName equ <GetOpenFileNameA>
endif
;BOOL
GetSaveFileNameA proto WINAPI :LPOPENFILENAMEA
;BOOL
GetSaveFileNameW proto WINAPI :LPOPENFILENAMEW
ifdef _UNICODE
GetSaveFileName equ <GetSaveFileNameW>
else
GetSaveFileName equ <GetSaveFileNameA>
endif

GetFileTitleA proto WINAPI :LPCSTR, :LPSTR, :WORD
GetFileTitleW proto WINAPI :LPCWSTR, :LPWSTR, :WORD
ifdef _UNICODE
GetFileTitle		equ <GetFileTitleW>
else
GetFileTitle		equ <GetFileTitleA>
endif

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
OFN_NOLONGNAMES		equ 0x00040000
if(WINVER GE 0x0400)
OFN_EXPLORER		equ 0x00080000
OFN_NODEREFERENCELINKS	equ 0x00100000
OFN_LONGNAMES		equ 0x00200000
OFN_ENABLEINCLUDENOTIFY equ 0x00400000
OFN_ENABLESIZING	equ 0x00800000
endif
if (_WIN32_WINNT GE 0x0500)
OFN_DONTADDTORECENT	equ 0x02000000
OFN_FORCESHOWHIDDEN	equ 0x10000000
endif

if (_WIN32_WINNT GE 0x0500)
OFN_EX_NOPLACESBAR	equ 0x00000001
endif

OFN_SHAREFALLTHROUGH	equ 2
OFN_SHARENOWARN		equ 1
OFN_SHAREWARN		equ 0

CALLBACK(LPCCHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)

if(WINVER GE 0x0400)
OFNOTIFYA		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEA ?
pszFile			LPSTR ?
OFNOTIFYA		ENDS
LPOFNOTIFYA		typedef ptr OFNOTIFYA

OFNOTIFYW		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEW ?
pszFile			LPWSTR ?
OFNOTIFYW		ENDS
LPOFNOTIFYW		typedef ptr OFNOTIFYW

ifdef _UNICODE
OFNOTIFY		typedef OFNOTIFYW
LPOFNOTIFY		typedef LPOFNOTIFYW
else
OFNOTIFY		typedef OFNOTIFYA
LPOFNOTIFY		typedef LPOFNOTIFYA
endif

OFNOTIFYEXA		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEA ?
psf			LPVOID ?
pidl			LPVOID ?
OFNOTIFYEXA		ENDS
LPOFNOTIFYEXA		typedef ptr OFNOTIFYEXA

OFNOTIFYEXW		STRUC
hdr			NMHDR <>
lpOFN			LPOPENFILENAMEW ?
psf			LPVOID ?
pidl			LPVOID ?
OFNOTIFYEXW		ENDS
LPOFNOTIFYEXW		typedef ptr OFNOTIFYEXW

ifdef _UNICODE
OFNOTIFYEX		typedef OFNOTIFYEXW
LPOFNOTIFYEX		typedef LPOFNOTIFYEXW
else
OFNOTIFYEX		typedef OFNOTIFYEXA
LPOFNOTIFYEX		typedef LPOFNOTIFYEXA
endif

CDN_FIRST		equ (0-601)
CDN_LAST		equ (0-699)

CDN_INITDONE		equ (CDN_FIRST - 0x0000)
CDN_SELCHANGE		equ (CDN_FIRST - 0x0001)
CDN_FOLDERCHANGE	equ (CDN_FIRST - 0x0002)
CDN_SHAREVIOLATION	equ (CDN_FIRST - 0x0003)
CDN_HELP		equ (CDN_FIRST - 0x0004)
CDN_FILEOK		equ (CDN_FIRST - 0x0005)
CDN_TYPECHANGE		equ (CDN_FIRST - 0x0006)
CDN_INCLUDEITEM		equ (CDN_FIRST - 0x0007)
if (NTDDI_VERSION GE NTDDI_WIN2K)
CDN_INCLUDEITEM		equ (CDN_FIRST - 0x0007)
endif

CDM_FIRST		equ (WM_USER + 100)
CDM_LAST		equ (WM_USER + 200)

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
endif

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
endif

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
endif

CDM_GETFOLDERIDLIST	equ (CDM_FIRST + 0x0003)
CommDlg_OpenSave_GetFolderIDList macro _hdlg, _pidl, _cbmax
	exitm<SNDMSG(_hdlg, CDM_GETFOLDERIDLIST, _cbmax, _pidl)>
	endm

CDM_SETCONTROLTEXT	equ (CDM_FIRST + 0x0004)
CommDlg_OpenSave_SetControlText macro _hdlg, _id, _text
	exitm<SNDMSG(_hdlg, CDM_SETCONTROLTEXT, _id, _text)>
	endm

CDM_HIDECONTROL		equ (CDM_FIRST + 0x0005)
CommDlg_OpenSave_HideControl macro _hdlg, _id
	exitm<SNDMSG(_hdlg, CDM_HIDECONTROL, _id, 0)>
	endm

CDM_SETDEFEXT		equ (CDM_FIRST + 0x0006)
CommDlg_OpenSave_SetDefExt macro _hdlg, _pszext
	exitm<SNDMSG(_hdlg, CDM_SETDEFEXT, 0, _pszext)>
	endm

endif

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
endif
else
CHOOSECOLORA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HWND ?
rgbResult		COLORREF ?
lpCustColors		LPCOLORREF ?
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
lpCustColors		LPCOLORREF ?
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
endif
endif

;BOOL
ChooseColorA proto WINAPI :LPCHOOSECOLORA
;BOOL
ChooseColorW proto WINAPI :LPCHOOSECOLORW
ifdef _UNICODE
ChooseColor		equ <ChooseColorW>
else
ChooseColor		equ <ChooseColorA>
endif

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
endif

;UINT
CALLBACK(LPFRHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)

FINDREPLACEA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
Flags			dd ?
lpstrFindWhat		LPSTR ?
lpstrReplaceWith	LPSTR ?
wFindWhatLen		dw ?
wReplaceWithLen		dw ?
lCustData		LPARAM ?
lpfnHook		LPFRHOOKPROC ?
lpTemplateName		LPCSTR ?
FINDREPLACEA		ENDS
LPFINDREPLACEA		typedef ptr FINDREPLACEA
FINDREPLACEW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hInstance		HINSTANCE ?
Flags			dd ?
lpstrFindWhat		LPWSTR ?
lpstrReplaceWith	LPWSTR ?
wFindWhatLen		dw ?
wReplaceWithLen		dw ?
lCustData		LPARAM ?
lpfnHook		LPFRHOOKPROC ?
lpTemplateName		LPCWSTR ?
FINDREPLACEW		ENDS
LPFINDREPLACEW		typedef ptr FINDREPLACEW
ifdef _UNICODE
FINDREPLACE		typedef FINDREPLACEW
LPFINDREPLACE		typedef LPFINDREPLACEW
else
FINDREPLACE		typedef FINDREPLACEA
LPFINDREPLACE		typedef LPFINDREPLACEA
endif

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
if (NTDDI_VERSION GE NTDDI_WIN2K)
FR_RAW			equ 0x00020000
FR_MATCHDIAC		equ 0x20000000
FR_MATCHKASHIDA		equ 0x40000000
FR_MATCHALEFHAMZA	equ 0x80000000
endif

;HWND
FindTextA proto WINAPI :LPFINDREPLACEA
FindTextW proto WINAPI :LPFINDREPLACEW
ifdef _UNICODE
FindText equ <FindTextW>
else
FindText equ <FindTextA>
endif
ifndef _MAC
;HWND
ReplaceTextA proto WINAPI :LPFINDREPLACEA
ReplaceTextW proto WINAPI :LPFINDREPLACEW
ifdef _UNICODE
ReplaceText equ <ReplaceTextW>
else
ReplaceText equ <ReplaceTextA>
endif
else
;HWND
AfxReplaceTextA proto WINAPI :LPFINDREPLACEA
AfxReplaceTextW proto WINAPI :LPFINDREPLACEW
ifdef _UNICODE
AfxReplaceText equ <AfxReplaceTextW>
else
AfxReplaceText equ <AfxReplaceTextA>
endif
endif

;UINT
CALLBACK(LPCFHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)

CHOOSEFONTA		STRUC 4
lStructSize		dd ?
hwndOwner		HWND ?
hDC			HDC ?
lpLogFont		LPLOGFONTA ?
iPointSize		SINT ?
Flags			dd ?
rgbColors		COLORREF ?
lCustData		LPARAM ?
lpfnHook		LPCFHOOKPROC ?
lpTemplateName		LPCSTR ?
hInstance		HINSTANCE ?
lpszStyle		LPSTR ?
nFontType		dw ?
;___MISSING_ALIGNMENT__ dw ?
nSizeMin		SINT ?
nSizeMax		SINT ?
CHOOSEFONTA		ENDS
LPCHOOSEFONTA		typedef ptr CHOOSEFONTA

CHOOSEFONTW		STRUC 4
lStructSize		dd ?
hwndOwner		HWND ?
hDC			HDC ?
lpLogFont		LPLOGFONTW ?
iPointSize		SINT ?
Flags			dd ?
rgbColors		COLORREF ?
lCustData		LPARAM ?
lpfnHook		LPCFHOOKPROC ?
lpTemplateName		LPCWSTR ?
hInstance		HINSTANCE ?
lpszStyle		LPWSTR ?
nFontType		dw ?
;___MISSING_ALIGNMENT__ dw ?
nSizeMin		SINT ?
nSizeMax		SINT ?
CHOOSEFONTW		ENDS
LPCHOOSEFONTW		typedef ptr CHOOSEFONTW
ifdef _UNICODE
CHOOSEFONT		typedef CHOOSEFONTW
LPCHOOSEFONT		typedef LPCHOOSEFONTW
else
CHOOSEFONT		typedef CHOOSEFONTA
LPCHOOSEFONT		typedef LPCHOOSEFONTA
endif

;BOOL
ChooseFontA proto WINAPI lpcf:LPCHOOSEFONT
;BOOL
ChooseFontW proto WINAPI lpcf:LPCHOOSEFONT
ifdef _UNICODE
ChooseFont equ <ChooseFontW>
else
ChooseFont equ <ChooseFontA>
endif

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
endif
CF_NOVECTORFONTS	equ 0x00000800
CF_NOOEMFONTS		equ CF_NOVECTORFONTS
CF_NOSIMULATIONS	equ 0x00001000
CF_LIMITSIZE		equ 0x00002000
CF_FIXEDPITCHONLY	equ 0x00004000
CF_WYSIWYG		equ 0x00008000
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
endif
if(WINVER GE 0x0601)
CF_INACTIVEFONTS	equ 0x02000000
endif

SIMULATED_FONTTYPE	equ 0x8000
PRINTER_FONTTYPE	equ 0x4000
SCREEN_FONTTYPE		equ 0x2000
BOLD_FONTTYPE		equ 0x0100
ITALIC_FONTTYPE		equ 0x0200
REGULAR_FONTTYPE	equ 0x0400

ifdef WINNT
OPENTYPE_FONTTYPE	equ 0x10000
;TYPE1_FONTTYPE		equ 0x20000
DSIG_FONTTYPE		equ 0x40000
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
PS_OPENTYPE_FONTTYPE	equ 0x10000
TT_OPENTYPE_FONTTYPE	equ 0x20000
TYPE1_FONTTYPE		equ 0x40000
endif

if(WINVER GE 0x0601)
SYMBOL_FONTTYPE		equ 0x80000
endif

WM_CHOOSEFONT_GETLOGFONT equ (WM_USER + 1)
WM_CHOOSEFONT_SETLOGFONT equ (WM_USER + 101)
WM_CHOOSEFONT_SETFLAGS	equ (WM_USER + 102)

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

CD_LBSELNOITEMS		equ -1
CD_LBSELCHANGE		equ 0
CD_LBSELSUB		equ 1
CD_LBSELADD		equ 2

;UINT
CALLBACK(LPPRINTHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)
CALLBACK(LPSETUPHOOKPROC, :HWND, :UINT, :WPARAM, :LPARAM)

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
endif

;BOOL
ifdef _UNICODE
PrintDlg		equ <PrintDlgW>
else
PrintDlg		equ <PrintDlgA>
endif

if(WINVER GE 0x0500)

ifdef __IUnknown_INTERFACE_DEFINED__

.comdef IPrintDialogCallback : public IUnknown

    InitDone		proc
    SelectionChange	proc
    HandleMessage	proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM, pResult:ptr LRESULT
   .ends


.comdef IPrintDialogServices : public IUnknown

    GetCurrentDevMode	proc pDevMode:LPDEVMODE, pcbSize:ptr UINT
    GetCurrentPrinterName proc pPrinterName:LPWSTR, pcchSize:ptr UINT
    GetCurrentPortName	proc pPortName:LPWSTR, pcchSize:ptr UINT
   .ends


PRINTPAGERANGE		STRUC
nFromPage		dd ?
nToPage			dd ?
PRINTPAGERANGE		ENDS
LPPRINTPAGERANGE	typedef ptr PRINTPAGERANGE
PCPRINTPAGERANGE	typedef ptr PRINTPAGERANGE


PRINTDLGEXA		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
hDC			HDC ?
Flags			dd ?
Flags2			dd ?
ExclusionFlags		dd ?
nPageRanges		dd ?
nMaxPageRanges		dd ?
lpPageRanges		LPPRINTPAGERANGE ?
nMinPage		dd ?
nMaxPage		dd ?
nCopies			dd ?
hInstance		HINSTANCE ?
lpPrintTemplateName	LPCSTR ?
lpCallback		PVOID ?
nPropertyPages		dd ?
lphPropertyPages	HPROPSHEETPAGE ?
nStartPage		dd ?
dwResultAction		dd ?
PRINTDLGEXA		ENDS
LPPRINTDLGEXA		typedef ptr PRINTDLGEXA

PRINTDLGEXW		STRUC
lStructSize		dd ?
hwndOwner		HWND ?
hDevMode		HGLOBAL ?
hDevNames		HGLOBAL ?
hDC			HDC ?
Flags			dd ?
Flags2			dd ?
ExclusionFlags		dd ?
nPageRanges		dd ?
nMaxPageRanges		dd ?
lpPageRanges		LPPRINTPAGERANGE ?
nMinPage		dd ?
nMaxPage		dd ?
nCopies			dd ?
hInstance		HINSTANCE ?
lpPrintTemplateName	LPCWSTR ?
lpCallback		PVOID ?
nPropertyPages		dd ?
lphPropertyPages	HPROPSHEETPAGE ?
nStartPage		dd ?
dwResultAction		dd ?
PRINTDLGEXW		ENDS
LPPRINTDLGEXW		typedef ptr PRINTDLGEXW

ifdef _UNICODE
PRINTDLGEX		typedef PRINTDLGEXW
LPPRINTDLGEX		typedef LPPRINTDLGEXW
else
PRINTDLGEX		typedef PRINTDLGEXA
LPPRINTDLGEX		typedef LPPRINTDLGEXA
endif

PrintDlgExA proto WINAPI :LPPRINTDLGEXA
PrintDlgExW proto WINAPI :LPPRINTDLGEXW
ifdef _UNICODE
PrintDlgEx		equ <PrintDlgExW>
else
PrintDlgEx		equ <PrintDlgExA>
endif

endif
endif ;; (WINVER GE 0x0500)

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
if(WINVER GE 0x0500)
PD_CURRENTPAGE		equ 0x00400000
PD_NOCURRENTPAGE	equ 0x00800000
PD_EXCLUSIONFLAGS	equ 0x01000000
PD_USELARGETEMPLATE	equ 0x10000000
endif

if(WINVER GE 0x0500)
PD_EXCL_COPIESANDCOLLATE equ (DM_COPIES or DM_COLLATE)
START_PAGE_GENERAL	equ 0xffffffff
PD_RESULT_CANCEL	equ 0
PD_RESULT_PRINT		equ 1
PD_RESULT_APPLY		equ 2
endif

DEVNAMES		STRUC
wDriverOffset		dw ?
wDeviceOffset		dw ?
wOutputOffset		dw ?
wDefault		dw ?
DEVNAMES		ENDS
LPDEVNAMES		typedef ptr DEVNAMES

DN_DEFAULTPRN		equ 0x0001

if(WINVER GE 0x0400)
WM_PSD_PAGESETUPDLG	equ (WM_USER  )
WM_PSD_FULLPAGERECT	equ (WM_USER+1)
WM_PSD_MINMARGINRECT	equ (WM_USER+2)
WM_PSD_MARGINRECT	equ (WM_USER+3)
WM_PSD_GREEKTEXTRECT	equ (WM_USER+4)
WM_PSD_ENVSTAMPRECT	equ (WM_USER+5)
WM_PSD_YAFULLPAGERECT	equ (WM_USER+6)

CALLBACK(LPPAGEPAINTHOOK, :HWND, :UINT, :WPARAM, :LPARAM)
CALLBACK(LPPAGESETUPHOOK, :HWND, :UINT, :WPARAM, :LPARAM)

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
endif

;BOOL
PageSetupDlgA proto WINAPI :LPPAGESETUPDLGA
PageSetupDlgW proto WINAPI :LPPAGESETUPDLGW
ifdef _UNICODE
PageSetupDlg		equ <PageSetupDlgW>
else
PageSetupDlg		equ <PageSetupDlgA>
endif

PSD_DEFAULTMINMARGINS	equ 0x00000000
PSD_INWININIINTLMEASURE equ 0x00000000

PSD_MINMARGINS		equ 0x00000001
PSD_MARGINS		equ 0x00000002
PSD_INTHOUSANDTHSOFINCHES equ 0x00000004
PSD_INHUNDREDTHSOFMILLIMETERS equ 0x00000008
PSD_DISABLEMARGINS	equ 0x00000010
PSD_DISABLEPRINTER	equ 0x00000020
PSD_NOWARNING		equ 0x00000080
PSD_DISABLEORIENTATION	equ 0x00000100
PSD_RETURNDEFAULT	equ 0x00000400
PSD_DISABLEPAPER	equ 0x00000200
PSD_SHOWHELP		equ 0x00000800
PSD_ENABLEPAGESETUPHOOK equ 0x00002000
PSD_ENABLEPAGESETUPTEMPLATE equ 0x00008000
PSD_ENABLEPAGESETUPTEMPLATEHANDLE equ 0x00020000
PSD_ENABLEPAGEPAINTHOOK equ 0x00040000
PSD_DISABLEPAGEPAINTING equ 0x00080000
PSD_NONETWORKBUTTON	equ 0x00200000
endif

if defined(ISOLATION_AWARE_ENABLED) and (ISOLATION_AWARE_ENABLED NE 0)
include commdlg.inl
endif

ifndef _WIN64
.pragma pack(pop)
endif

endif ;; GUID_DEFS_ONLY
endif ;; _INC_COMMDLG
.pragma list(pop)

