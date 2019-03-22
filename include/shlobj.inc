ifndef _SHLOBJ_H_
_SHLOBJ_H_ equ <>
.pragma list(push, 0)
.pragma comment(lib, shell32)

ifndef SNDMSG
SNDMSG	equ <SendMessage>
endif

include ole2.inc
ifndef _PRSHT_H_
include prsht.inc
endif
ifndef _INC_COMMCTRL
include commctrl.inc
endif
;ifndef INITGUID
include shlguid.inc
;endif
include shtypes.inc
include shobjidl.inc

;.pragma pack(push, 1)

;SHSTDAPI
SHGetMalloc proto WINAPI \
	      ppMalloc: ptr IMalloc

;SHSTDAPI
SHAlloc proto WINAPI \
		    cb: SIZE_T

;SHSTDAPI
SHFree proto WINAPI \
		    pv: PVOID


GIL_OPENICON		equ 0x0001
GIL_FORSHELL		equ 0x0002
GIL_ASYNC		equ 0x0020
GIL_DEFAULTICON		equ 0x0040
GIL_FORSHORTCUT		equ 0x0080
GIL_CHECKSHIELD		equ 0x0200


GIL_SIMULATEDOC		equ 0x0001
GIL_PERINSTANCE		equ 0x0002
GIL_PERCLASS		equ 0x0004
GIL_NOTFILENAME		equ 0x0008
GIL_DONTCACHE		equ 0x0010
GIL_SHIELD		equ 0x0200
GIL_FORCENOSHIELD	equ 0x0400

.comdef IExtractIconA
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetIconLocation	proc :UINT, :LPSTR, :UINT, :ptr, :ptr
    Extract		proc :LPCSTR, :UINT, :ptr, :ptr, :UINT
    .ends
LPEXTRACTICONA		typedef ptr IExtractIconA
.comdef IExtractIconW
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetIconLocation	proc :UINT, :LPWSTR, :UINT, :ptr, :ptr
    Extract		proc :LPCWSTR, :UINT, :ptr, :ptr, :UINT
    .ends
LPEXTRACTICONW		typedef ptr IExtractIconW
ifdef _UNICODE
IExtractIcon		equ <IExtractIconW>
LPEXTRACTICON		equ <LPEXTRACTICONW>
else
IExtractIcon		equ <IExtractIconA>
LPEXTRACTICON		equ <LPEXTRACTICONA>
endif

.comdef IShellIconOverlayIdentifier
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    IsMemberOf		proc :LPCWSTR, :DWORD
    GetOverlayInfo	proc :LPWSTR, :SINT, :ptr, :ptr
    GetPriority		proc :ptr
    .ends

ISIOI_ICONFILE		equ 0x00000001
ISIOI_ICONINDEX		equ 0x00000002

.comdef IShellIconOverlayManager
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFileOverlayInfo	proc :LPCWSTR, :DWORD, :ptr, :DWORD
    GetReservedOverlayInfo proc :LPCWSTR, :DWORD, :ptr, :DWORD, :SINT
    RefreshOverlayImages proc :DWORD
    LoadNonloadedOverlayIdentifiers proc
    OverlayIndexFromImageIndex proc :SINT, :ptr, :BOOL
    .ends

SIOM_OVERLAYINDEX	equ 1
SIOM_ICONINDEX		equ 2
SIOM_RESERVED_SHARED	equ 0
SIOM_RESERVED_LINK	equ 1
SIOM_RESERVED_SLOWFILE	equ 2
SIOM_RESERVED_DEFAULT	equ 3

.comdef IShellIconOverlay
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetOverlayIndex	proc :PCUITEMID_CHILD, :ptr
    GetOverlayIconIndex proc :PCUITEMID_CHILD, :ptr
    .ends

OI_DEFAULT		equ 0x00000000
OI_ASYNC		equ 0xFFFFEEEE

IDO_SHGIOI_SHARE	equ 0x0FFFFFFF
IDO_SHGIOI_LINK		equ 0x0FFFFFFE
IDO_SHGIOI_SLOWFILE	equ 0x0FFFFFFFD
IDO_SHGIOI_DEFAULT	equ 0x0FFFFFFFC
;SHSTDAPI
SHGetIconOverlayIndexA proto WINAPI \
	   pszIconPath: LPCSTR,
	    iIconIndex: SINT

;SHSTDAPI
SHGetIconOverlayIndexW proto WINAPI \
	   pszIconPath: LPCWSTR,
	    iIconIndex: SINT

ifdef _UNICODE
SHGetIconOverlayIndex	equ <SHGetIconOverlayIndexW>
else
SHGetIconOverlayIndex	equ <SHGetIconOverlayIndexA>
endif

if (_WIN32_IE GE 0x0400)

SHELL_LINK_DATA_FLAGS	typedef SDWORD
SLDF_DEFAULT		equ 0x00000000
SLDF_HAS_ID_LIST	equ 0x00000001
SLDF_HAS_LINK_INFO	equ 0x00000002
SLDF_HAS_NAME		equ 0x00000004
SLDF_HAS_RELPATH	equ 0x00000008
SLDF_HAS_WORKINGDIR	equ 0x00000010
SLDF_HAS_ARGS		equ 0x00000020
SLDF_HAS_ICONLOCATION	equ 0x00000040
SLDF_UNICODE		equ 0x00000080
SLDF_FORCE_NO_LINKINFO	equ 0x00000100
SLDF_HAS_EXP_SZ		equ 0x00000200
SLDF_RUN_IN_SEPARATE	equ 0x00000400
if (NTDDI_VERSION LT NTDDI_VISTA)
SLDF_HAS_LOGO3ID	equ 0x00000800
endif
SLDF_HAS_DARWINID	equ 0x00001000
SLDF_RUNAS_USER		equ 0x00002000
SLDF_HAS_EXP_ICON_SZ	equ 0x00004000
if (NTDDI_VERSION GT NTDDI_WINXP)
SLDF_NO_PIDL_ALIAS	equ 0x00008000
SLDF_FORCE_UNCNAME	equ 0x00010000
SLDF_RUN_WITH_SHIMLAYER equ 0x00020000
if (NTDDI_VERSION GT NTDDI_VISTA)
SLDF_FORCE_NO_LINKTRACK equ 0x00040000
SLDF_ENABLE_TARGET_METADATA equ 0x00080000
SLDF_DISABLE_LINK_PATH_TRACKING equ 0x00100000
SLDF_DISABLE_KNOWNFOLDER_RELATIVE_TRACKING equ 0x00200000
if (NTDDI_VERSION GT NTDDI_WIN7)
SLDF_NO_KF_ALIAS	equ 0x00400000
SLDF_ALLOW_LINK_TO_LINK equ 0x00800000
SLDF_UNALIAS_ON_SAVE	equ 0x01000000
SLDF_PREFER_ENVIRONMENT_PATH equ 0x02000000
SLDF_KEEP_LOCAL_IDLIST_FOR_UNC_TARGET equ 0x04000000
SLDF_VALID		equ 0x07FFF7FF
else
SLDF_VALID		equ 0x003FF7FF
endif
endif
SLDF_RESERVED		equ 0x80000000
endif

DEFINE_ENUM_FLAG_OPERATORS(SHELL_LINK_DATA_FLAGS)

DATABLOCK_HEADER	STRUC
cbSize			dd ?
dwSignature		dd ?
DATABLOCK_HEADER	ENDS
LPDATABLOCK_HEADER	typedef ptr DATABLOCK_HEADER
LPDBLIST		typedef ptr DATABLOCK_HEADER

ifdef LF_FACESIZE
NT_CONSOLE_PROPS	STRUC
dbh			DATABLOCK_HEADER <>
wFillAttribute		dw ?
wPopupFillAttribute	dw ?
dwScreenBufferSize	COORD <>
dwWindowSize		COORD <>
dwWindowOrigin		COORD <>
nFont			dd ?
nInputBufferSize	dd ?
dwFontSize		COORD <>
uFontFamily		UINT ?
uFontWeight		UINT ?
FaceName		WCHAR LF_FACESIZE dup(?)
uCursorSize		UINT ?
bFullScreen		BOOL ?
bQuickEdit		BOOL ?
bInsertMode		BOOL ?
bAutoPosition		BOOL ?
uHistoryBufferSize	UINT ?
uNumberOfHistoryBuffers UINT ?
bHistoryNoDup		BOOL ?
ColorTable		COLORREF  16  dup(?)
NT_CONSOLE_PROPS	ENDS
LPNT_CONSOLE_PROPS	typedef ptr NT_CONSOLE_PROPS
NT_CONSOLE_PROPS_SIG	equ 0xA0000002
endif

NT_FE_CONSOLE_PROPS	STRUC
dbh			DATABLOCK_HEADER <>
uCodePage		UINT ?
NT_FE_CONSOLE_PROPS	ENDS
LPNT_FE_CONSOLE_PROPS	typedef ptr NT_FE_CONSOLE_PROPS
NT_FE_CONSOLE_PROPS_SIG equ 0xA0000004

if (_WIN32_IE GE 0x0500)
EXP_DARWIN_LINK		STRUC
dbh			DATABLOCK_HEADER <>
szDarwinID		CHAR MAX_PATH dup(?)
szwDarwinID		WCHAR MAX_PATH dup(?)
EXP_DARWIN_LINK		ENDS
LPEXP_DARWIN_LINK	typedef ptr EXP_DARWIN_LINK
EXP_DARWIN_ID_SIG	equ 0xA0000006
endif

EXP_SPECIAL_FOLDER_SIG	equ 0xA0000005

EXP_SPECIAL_FOLDER	STRUC
cbSize			dd ?
dwSignature		dd ?
idSpecialFolder		dd ?
cbOffset		dd ?
EXP_SPECIAL_FOLDER	ENDS
LPEXP_SPECIAL_FOLDER	typedef ptr EXP_SPECIAL_FOLDER


EXP_SZ_LINK		STRUC
cbSize			dd ?
dwSignature		dd ?
szTarget		CHAR  MAX_PATH	dup(?)
swzTarget		WCHAR  MAX_PATH	 dup(?)
EXP_SZ_LINK		ENDS
LPEXP_SZ_LINK		typedef ptr EXP_SZ_LINK
EXP_SZ_LINK_SIG		equ 0xA0000001
EXP_SZ_ICON_SIG		equ 0xA0000007

if (NTDDI_VERSION GE NTDDI_VISTA)
EXP_PROPERTYSTORAGE	STRUC
cbSize			dd ?
dwSignature		dd ?
abPropertyStorage	db 1 dup(?)
EXP_PROPERTYSTORAGE	ENDS
EXP_PROPERTYSTORAGE_SIG equ 0xA0000009
endif

endif


ifdef _INC_SHELLAPI
.comdef IShellExecuteHookA
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Execute		proc :LPSHELLEXECUTEINFOA
    .ends
.comdef IShellExecuteHookW
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Execute		proc :LPSHELLEXECUTEINFOW
    .ends
ifdef _UNICODE
IShellExecuteHook	equ <IShellExecuteHookW>
else
IShellExecuteHook	equ <IShellExecuteHookA>
endif
endif


.comdef IURLSearchHook
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Translate		proc :LPWSTR, :DWORD
    .ends

.comdef ISearchContext
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSearchUrl	proc :ptr
    GetSearchText	proc :ptr
    GetSearchStyle	proc :ptr
    .ends

.comdef IURLSearchHook2
    TranslateWithSearchContext proc :LPWSTR, :DWORD, :ptr
    .ends


.comdef INewShortcutHookA
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetReferent		proc :LPCSTR, :HWND
    GetReferent		proc :LPSTR, :SINT
    SetFolder		proc :LPCSTR
    GetFolder		proc :LPSTR, :SINT
    GetName		proc :LPSTR, :SINT
    GetExtension	proc :LPSTR, :SINT
    .ends
.comdef INewShortcutHookW
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetReferent		proc :LPCWSTR, :HWND
    GetReferent		proc :LPWSTR, :SINT
    SetFolder		proc :LPCWSTR
    GetFolder		proc :LPWSTR, :SINT
    GetName		proc :LPWSTR, :SINT
    GetExtension	proc :LPWSTR, :SINT
    .ends
ifdef _UNICODE
INewShortcutHook	equ <INewShortcutHookW>
else
INewShortcutHook	equ <INewShortcutHookA>
endif

.comdef ICopyHookA
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CopyCallback	proc :HWND, :UINT, :UINT, :LPCSTR, :DWORD, :LPCSTR, :DWORD
    .ends
LPCOPYHOOKA		typedef ptr ICopyHookA
.comdef ICopyHookW
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CopyCallback	proc :HWND, :UINT, :UINT, :LPCWSTR, :DWORD, :LPCWSTR, :DWORD
    .ends
LPCOPYHOOKW		typedef ptr ICopyHookW
ifdef _UNICODE
ICopyHook		equ <ICopyHookW>
LPCOPYHOOK		equ <LPCOPYHOOKW>
else
ICopyHook		equ <ICopyHookA>
LPCOPYHOOK		equ <LPCOPYHOOKA>
endif

if (NTDDI_VERSION LT NTDDI_WIN2K)

.comdef IFileViewerSite
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPinnedWindow	proc :HWND
    GetPinnedWindow	proc :ptr
    .ends
LPFILEVIEWERSITE	typedef ptr IFileViewerSite

.pragma pack(push, 8)

FVSHOWINFO		STRUC
cbSize			dd ?
hwndOwner		HWND ?
iShow			SINT ?

dwFlags			dd ?
rect			RECT ?
punkRel			LPIUnknown ?

strNewFile		OLECHAR MAX_PATH dup(?)

FVSHOWINFO		ENDS
LPFVSHOWINFO		typedef ptr FVSHOWINFO

.pragma pack(pop)

FVSIF_RECT		equ 0x00000001
FVSIF_PINNED		equ 0x00000002

FVSIF_NEWFAILED		equ 0x08000000

FVSIF_NEWFILE		equ 0x80000000
FVSIF_CANVIEWIT		equ 0x40000000

.comdef IFileViewerA
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ShowInitialize	proc :LPFILEVIEWERSITE
    Show		proc :LPFVSHOWINFO
    PrintTo		proc :LPSTR, :BOOL
    .ends
LPFILEVIEWERA		typedef ptr IFileViewerA
.comdef IFileViewerW
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ShowInitialize	proc :LPFILEVIEWERSITE
    Show		proc :LPFVSHOWINFO
    PrintTo		proc :LPWSTR, :BOOL
    .ends
LPFILEVIEWERW		typedef ptr IFileViewerW
ifdef _UNICODE
IFileViewer		equ <IFileViewerW>
LPFILEVIEWER		equ <LPFILEVIEWERW>
else
IFileViewer		equ <IFileViewerA>
LPFILEVIEWER		equ <LPFILEVIEWERA>
endif

endif


FCIDM_SHVIEWFIRST	equ 0x0000
FCIDM_SHVIEWLAST	equ 0x7fff
FCIDM_BROWSERFIRST	equ 0xa000
FCIDM_BROWSERLAST	equ 0xbf00
FCIDM_GLOBALFIRST	equ 0x8000
FCIDM_GLOBALLAST	equ 0x9fff

FCIDM_MENU_FILE		equ (FCIDM_GLOBAFIRST+0x0000)
FCIDM_MENU_EDIT		equ (FCIDM_GLOBAFIRST+0x0040)
FCIDM_MENU_VIEW		equ (FCIDM_GLOBAFIRST+0x0080)
FCIDM_MENU_VIEW_SEP_OPTIONS equ (FCIDM_GLOBAFIRST+0x0081)
FCIDM_MENU_TOOLS	equ (FCIDM_GLOBAFIRST+0x00c0)
FCIDM_MENU_TOOLS_SEP_GOTO equ (FCIDM_GLOBAFIRST+0x00c1)
FCIDM_MENU_HELP		equ (FCIDM_GLOBAFIRST+0x0100)
FCIDM_MENU_FIND		equ (FCIDM_GLOBAFIRST+0x0140)
FCIDM_MENU_EXPLORE	equ (FCIDM_GLOBAFIRST+0x0150)
FCIDM_MENU_FAVORITES	equ (FCIDM_GLOBAFIRST+0x0170)


FCIDM_TOOLBAR		equ (FCIDM_BROWSERFIRST + 0)
FCIDM_STATUS		equ (FCIDM_BROWSERFIRST + 1)

if (_WIN32_IE GE 0x0400)
IDC_OFFLINE_HAND	equ 103
if (_WIN32_IE GE _WIN32_IE_IE70)
IDC_PANTOOL_HAND_OPEN	equ 104
IDC_PANTOOL_HAND_CLOSED equ 105
endif
endif


PANE_NONE		equ (-1)
PANE_ZONE		equ 1
PANE_OFFLINE		equ 2
PANE_PRINTER		equ 3
PANE_SSL		equ 4
PANE_NAVIGATION		equ 5
PANE_PROGRESS		equ 6
if (_WIN32_IE GE _WIN32_IE_IE60)
PANE_PRIVACY		equ 7
endif


;SHSTDAPI
ILClone proto WINAPI \
		  pidl: PCUIDLIST_RELATIVE

;SHSTDAPI
ILCloneFirst proto WINAPI \
		  pidl: PCUIDLIST_RELATIVE

;SHSTDAPI
ILCombine proto WINAPI \
		 pidl1: PCIDLIST_ABSOLUTE,
		 pidl2: PCUIDLIST_RELATIVE

;SHSTDAPI
ILFree proto WINAPI \
		  pidl: PIDLIST_RELATIVE

;SHSTDAPI
ILGetNext proto WINAPI \
		  pidl: PCUIDLIST_RELATIVE

;SHSTDAPI
ILGetSize proto WINAPI \
		  pidl: PCUIDLIST_RELATIVE

;SHSTDAPI
ILFindChild proto WINAPI \
	    pidlParent: PIDLIST_ABSOLUTE,
	     pidlChild: PCIDLIST_ABSOLUTE

;SHSTDAPI
ILFindLastID proto WINAPI \
		  pidl: PCUIDLIST_RELATIVE

;SHSTDAPI
ILRemoveLastID proto WINAPI \
		  pidl: PUIDLIST_RELATIVE

;SHSTDAPI
ILIsEqual proto WINAPI \
		 pidl1: PCIDLIST_ABSOLUTE,
		 pidl2: PCIDLIST_ABSOLUTE

;SHSTDAPI
ILIsParent proto WINAPI \
		 pidl1: PCIDLIST_ABSOLUTE,
		 pidl2: PCIDLIST_ABSOLUTE,
	    fImmediate: BOOL

;SHSTDAPI
ILSaveToStream proto WINAPI \
		  pstm: ptr IStream,
		  pidl: PCUIDLIST_RELATIVE

if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
ILLoadFromStreamEx proto WINAPI \
		  pstm: ptr IStream,
		  pidl: ptr PIDLIST_RELATIVE

endif

if (_WIN32_IE GE 0x0400)

;SHSTDAPI
ILCreateFromPathA proto WINAPI \
	       pszPath: LPCSTR

;SHSTDAPI
ILCreateFromPathW proto WINAPI \
	       pszPath: LPCWSTR


ifdef NO_WRAPPERS_FOR_ILCREATEFROMPATH
;SHSTDAPI
ILCreateFromPath proto WINAPI \
	       pszPath: LPCTSTR

else
ifdef _UNICODE
ILCreateFromPath	equ <ILCreateFromPathW>
else
ILCreateFromPath	equ <ILCreateFromPathA>
endif
endif

endif

;SHSTDAPI
SHILCreateFromPath proto WINAPI \
	       pszPath: LPCWSTR,
		 ppidl: ptr PIDLIST_ABSOLUTE,
	      rgfInOut: ptr DWORD


VOID_OFFSET macro pv, cb
	exitm<(pv+cb)>
	endm

ILCloneFull		equ <ILClone>
ILCloneChild		equ <ILCloneFirst>

ILSkip macro pidl, cb
	exitm<(VOID_OFFSET((pidl), (cb)))>
	endm
ILNext macro pidl
	exitm<ILSkip(pidl, (pidl)- GT mkid.cb)>
	endm

ILIsAligned macro pidl
	exitm<(((pidl) AND (sizeof(PVOID) - 1)) EQ 0)>
	endm

ILIsEmpty macro pidl
	exitm<((pidl) EQ NULL OR (pidl).mkid.cb EQ 0)>
	endm

ILIsChild macro pidl
	exitm<(ILIsEmpty(pidl) OR ILIsEmpty(ILNext(pidl)))>
	endm

;SHSTDAPI_(PIDLIST_RELATIVE)
ILAppendID proto WINAPI \
		  pidl: PIDLIST_RELATIVE,
		 pmkid: LPCSHITEMID,
	       fAppend: BOOL



if (NTDDI_VERSION GE NTDDI_VISTA)
tagGPFIDL_FLAGS		typedef SDWORD
GPFIDL_DEFAULT		equ 0x0000
GPFIDL_ALTNAME		equ 0x0001	; short file name
GPFIDL_UNCPRINTER	equ 0x0002	; include UNC printer names too (non file system item)
GPFIDL_FLAGS		typedef SINT

;SHSTDAPI
SHGetPathFromIDListEx proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
	       pszPath: PWSTR,
	       cchPath: DWORD,
		 uOpts: GPFIDL_FLAGS

endif

;SHSTDAPI
SHGetPathFromIDListA proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
	       pszPath: LPSTR


;SHSTDAPI
SHGetPathFromIDListW proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
	       pszPath: LPWSTR

ifdef _UNICODE
SHGetPathFromIDList	equ <SHGetPathFromIDistW>
else
SHGetPathFromIDList	equ <SHGetPathFromIDistA>
endif

;SHSTDAPI
SHCreateDirectory proto WINAPI \
		  hwnd: HWND,
	       pszPath: LPCWSTR

;SHSTDAPI
SHCreateDirectoryExA proto WINAPI \
		  hwnd: HWND,
	       pszPath: LPCSTR,
		   psa: ptr SECURITY_ATTRIBUTES

;SHSTDAPI
SHCreateDirectoryExW proto WINAPI \
		  hwnd: HWND,
	       pszPath: LPCWSTR,
		   psa: ptr SECURITY_ATTRIBUTES

ifdef _UNICODE
SHCreateDirectoryEx	equ <SHCreateDirectoryExW>
else
SHCreateDirectoryEx	equ <SHCreateDirectoryExA>
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
OFASI_EDIT		equ 0x0001
OFASI_OPENDESKTOP	equ 0x0002
endif

if (NTDDI_VERSION GE NTDDI_WINXP)

;SHSTDAPI
SHOpenFolderAndSelectItems proto WINAPI \
	    pidlFolder: PCIDLIST_ABSOLUTE,
		  cidl: UINT,
		 apidl: PCUITEMID_CHILD_ARRAY,
	       dwFlags: DWORD


;SHSTDAPI
SHCreateShellItem proto WINAPI \
	    pidlParent: PCIDLIST_ABSOLUTE,
	     psfParent: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
		  ppsi: ptr IShellItem


endif

REGSTR_PATH_SPECIAL_FOLDERS equ REGSTR_PATH_EXPLORER TEXT("\\Shell Folders")


CSIDL_DESKTOP		equ 0x0000
CSIDL_INTERNET		equ 0x0001
CSIDL_PROGRAMS		equ 0x0002
CSIDL_CONTROLS		equ 0x0003
CSIDL_PRINTERS		equ 0x0004
CSIDL_PERSONAL		equ 0x0005
CSIDL_FAVORITES		equ 0x0006
CSIDL_STARTUP		equ 0x0007
CSIDL_RECENT		equ 0x0008
CSIDL_SENDTO		equ 0x0009
CSIDL_BITBUCKET		equ 0x000a
CSIDL_STARTMENU		equ 0x000b
CSIDL_MYDOCUMENTS	equ CSIDL_PERSONA
CSIDL_MYMUSIC		equ 0x000d
CSIDL_MYVIDEO		equ 0x000e
CSIDL_DESKTOPDIRECTORY	equ 0x0010
CSIDL_DRIVES		equ 0x0011
CSIDL_NETWORK		equ 0x0012
CSIDL_NETHOOD		equ 0x0013
CSIDL_FONTS		equ 0x0014
CSIDL_TEMPLATES		equ 0x0015
CSIDL_COMMON_STARTMENU	equ 0x0016
CSIDL_COMMON_PROGRAMS	equ 0X0017
CSIDL_COMMON_STARTUP	equ 0x0018
CSIDL_COMMON_DESKTOPDIRECTORY equ 0x0019
CSIDL_APPDATA		equ 0x001a
CSIDL_PRINTHOOD		equ 0x001b

ifndef CSIDL_LOCAL_APPDATA
CSIDL_LOCAL_APPDATA	equ 0x001c
endif

CSIDL_ALTSTARTUP	equ 0x001d
CSIDL_COMMON_ALTSTARTUP equ 0x001e
CSIDL_COMMON_FAVORITES	equ 0x001f

ifndef _SHFOLDER_H_
CSIDL_INTERNET_CACHE	equ 0x0020
CSIDL_COOKIES		equ 0x0021
CSIDL_HISTORY		equ 0x0022
CSIDL_COMMON_APPDATA	equ 0x0023
CSIDL_WINDOWS		equ 0x0024
CSIDL_SYSTEM		equ 0x0025
CSIDL_PROGRAM_FILES	equ 0x0026
CSIDL_MYPICTURES	equ 0x0027
endif

CSIDL_PROFILE		equ 0x0028
CSIDL_SYSTEMX86		equ 0x0029
CSIDL_PROGRAM_FILESX86	equ 0x002a

ifndef _SHFOLDER_H_
CSIDL_PROGRAM_FILES_COMMON equ 0x002b
endif

CSIDL_PROGRAM_FILES_COMMONX86 equ 0x002c
CSIDL_COMMON_TEMPLATES	equ 0x002d

ifndef _SHFOLDER_H_
CSIDL_COMMON_DOCUMENTS	equ 0x002e
CSIDL_COMMON_ADMINTOOLS equ 0x002f
CSIDL_ADMINTOOLS	equ 0x0030
endif

CSIDL_CONNECTIONS	equ 0x0031
CSIDL_COMMON_MUSIC	equ 0x0035
CSIDL_COMMON_PICTURES	equ 0x0036
CSIDL_COMMON_VIDEO	equ 0x0037
CSIDL_RESOURCES		equ 0x0038

ifndef _SHFOLDER_H_
CSIDL_RESOURCES_LOCALIZED equ 0x0039
endif

CSIDL_COMMON_OEM_LINKS	equ 0x003a
CSIDL_CDBURN_AREA	equ 0x003b
CSIDL_COMPUTERSNEARME	equ 0x003d

ifndef _SHFOLDER_H_
CSIDL_FLAG_CREATE	equ 0x8000
endif

CSIDL_FLAG_DONT_VERIFY	equ 0x4000
CSIDL_FLAG_DONT_UNEXPAND equ 0x2000
if (NTDDI_VERSION GE NTDDI_WINXP)
CSIDL_FLAG_NO_ALIAS	equ 0x1000
CSIDL_FLAG_PER_USER_INIT equ 0x0800
endif
CSIDL_FLAG_MASK		equ 0xFF00

;SHSTDAPI
SHGetSpecialFolderLocation proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		 ppidl: ptr PIDLIST_ABSOLUTE


;SHSTDAPI
SHCloneSpecialIDList proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
	       fCreate: BOOL


;SHSTDAPI
SHGetSpecialFolderPathA proto WINAPI \
		  hwnd: HWND,
	       pszPath: LPSTR,
		 csidl: SINT,
	       fCreate: BOOL


;SHSTDAPI
SHGetSpecialFolderPathW proto WINAPI \
		  hwnd: HWND,
	       pszPath: LPWSTR,
		 csidl: SINT,
	       fCreate: BOOL

ifdef _UNICODE
SHGetSpecialFolderPath	equ <SHGetSpecialFolderPathW>
else
SHGetSpecialFolderPath	equ <SHGetSpecialFolderPathA>
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
;SHSTDAPI
SHFlushSFCache proto WINAPI

SHGFP_TYPE		typedef SDWORD
SHGFP_TYPE_CURRENT	equ 0
SHGFP_TYPE_DEFAULT	equ 1	; default value, may not exist

;SHFOLDERAPI
SHGetFolderPathA proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	       pszPath: LPSTR

;SHFOLDERAPI
SHGetFolderPathW proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	       pszPath: LPWSTR

ifdef _UNICODE
SHGetFolderPath		equ <SHGetFolderPathW>
else
SHGetFolderPath		equ <SHGetFolderPathA>
endif
;SHSTDAPI
SHGetFolderLocation proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
		 ppidl: ptr PIDLIST_ABSOLUTE

endif

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHSetFolderPathA proto WINAPI \
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	       pszPath: LPCSTR

;SHSTDAPI
SHSetFolderPathW proto WINAPI \
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	       pszPath: LPCWSTR

ifdef _UNICODE
SHSetFolderPath		equ <SHSetFolderPathW>
else
SHSetFolderPath		equ <SHSetFolderPathA>
endif
;SHSTDAPI
SHGetFolderPathAndSubDirA proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	     pszSubDir: LPCSTR,
	       pszPath: LPSTR

;SHSTDAPI
SHGetFolderPathAndSubDirW proto WINAPI \
		  hwnd: HWND,
		 csidl: SINT,
		hToken: HANDLE,
	       dwFlags: DWORD,
	     pszSubDir: LPCWSTR,
	       pszPath: LPWSTR

ifdef _UNICODE
SHGetFolderPathAndSubDir equ <SHGetFolderPathAndSubDirW>
else
SHGetFolderPathAndSubDir equ <SHGetFolderPathAndSubDirA>
endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)


KNOWN_FOLDER_FLAG	typedef SDWORD
KF_FLAG_DEFAULT		equ 0x00000000
KF_FLAG_CREATE		equ 0x00008000
KF_FLAG_DONT_VERIFY	equ 0x00004000
KF_FLAG_DONT_UNEXPAND	equ 0x00002000
KF_FLAG_NO_ALIAS	equ 0x00001000
KF_FLAG_INIT		equ 0x00000800
KF_FLAG_DEFAULT_PATH	equ 0x00000400
KF_FLAG_NOT_PARENT_RELATIVE equ 0x00000200
KF_FLAG_SIMPLE_IDLIST	equ 0x00000100
KF_FLAG_ALIAS_ONLY	equ 0x80000000


DEFINE_ENUM_FLAG_OPERATORS(KNOWN_FOLDER_FLAG)

;STDAPI
SHGetKnownFolderIDList proto WINAPI \
		  rfid: REFKNOWNFOLDERID,
	       dwFlags: DWORD,
		hToken: HANDLE,
		 ppidl: ptr PIDLIST_ABSOLUTE

;STDAPI
SHSetKnownFolderPath proto WINAPI \
		  rfid: REFKNOWNFOLDERID,
	       dwFlags: DWORD,
		hToken: HANDLE,
	       pszPath: PCWSTR

;STDAPI
SHGetKnownFolderPath proto WINAPI \
		  rfid: REFKNOWNFOLDERID,
	       dwFlags: DWORD,
		hToken: HANDLE,
	      ppszPath: ptr PWSTR

endif

if (NTDDI_VERSION GE NTDDI_WIN7)
;STDAPI
SHGetKnownFolderItem proto WINAPI \
		  rfid: REFKNOWNFOLDERID,
		 flags: KNOWN_FOLDER_FLAG,
		hToken: HANDLE,
		  riid: REFIID,
		   ppv: PVOID

endif

if (NTDDI_VERSION GE NTDDI_WIN2K)

FCS_READ		equ 0x00000001
FCS_FORCEWRITE		equ 0x00000002
FCS_WRITE		equ (FCS_READ OR FCS_FORCEWRITE)

FCS_FLAG_DRAGDROP	equ 2

FCSM_VIEWID		equ 0x00000001
FCSM_WEBVIEWTEMPLATE	equ 0x00000002
FCSM_INFOTIP		equ 0x00000004
FCSM_CLSID		equ 0x00000008
FCSM_ICONFILE		equ 0x00000010
FCSM_LOGO		equ 0x00000020
FCSM_FLAGS		equ 0x00000040

if (NTDDI_VERSION GE NTDDI_VISTA)

.pragma pack(push, 8)

LPSHELLVIEWID		typedef ptr SHELLVIEWID

SHFOLDERCUSTOMSETTINGS	STRUC 8
dwSize			dd ?
dwMask			dd ?
pvid			LPSHELLVIEWID ?
pszWebViewTemplate	LPWSTR ?
cchWebViewTemplate	dd ?
pszWebViewTemplateVersion LPWSTR ?
pszInfoTip		LPWSTR ?
cchInfoTip		dd ?
pclsid			LPCLSID ?
dwFlags			dd ?
pszIconFile		LPWSTR ?
cchIconFile		dd ?
iIconIndex		SINT ?
pszLogo			LPWSTR ?
cchLogo			dd ?
SHFOLDERCUSTOMSETTINGS	ENDS
LPSHFOLDERCUSTOMSETTINGS typedef ptr SHFOLDERCUSTOMSETTINGS

.pragma pack(pop)

;SHSTDAPI
SHGetSetFolderCustomSettings proto WINAPI \
		  pfcs: LPSHFOLDERCUSTOMSETTINGS,
	       pszPath: LPCWSTR,
	   dwReadWrite: DWORD


endif
endif


CALLBACK(BFFCALLBACK, :HWND, :UINT, :LPARAM, :LPARAM)

.pragma pack(push, 8)

BROWSEINFOA		STRUC
hwndOwner		HWND ?
pidlRoot		PCIDLIST_ABSOLUTE ?
pszDisplayName		LPSTR ?
lpszTitle		LPCSTR ?
ulFlags			UINT ?
lpfn			BFFCALLBACK ?
lParam			LPARAM ?
iImage			SINT ?
BROWSEINFOA		ENDS
PBROWSEINFOA		typedef ptr BROWSEINFOA
LPBROWSEINFOA		typedef ptr BROWSEINFOA

BROWSEINFOW		STRUC 8
hwndOwner		HWND ?
pidlRoot		PCIDLIST_ABSOLUTE ?
pszDisplayName		LPWSTR ?
lpszTitle		LPCWSTR ?
ulFlags			UINT ?
lpfn			BFFCALLBACK ?
lParam			LPARAM ?
iImage			SINT ?
BROWSEINFOW		ENDS
PBROWSEINFOW		typedef ptr BROWSEINFOW
LPBROWSEINFOW		typedef ptr BROWSEINFOW

.pragma pack(pop)

ifdef _UNICODE
BROWSEINFO		equ <BROWSEINFOW>
PBROWSEINFO		equ <PBROWSEINFOW>
LPBROWSEINFO		equ <LPBROWSEINFOW>
else
BROWSEINFO		equ <BROWSEINFOA>
PBROWSEINFO		equ <PBROWSEINFOA>
LPBROWSEINFO		equ <LPBROWSEINFOA>
endif

BIF_RETURNONLYFSDIRS	equ 0x00000001
BIF_DONTGOBELOWDOMAIN	equ 0x00000002
BIF_STATUSTEXT		equ 0x00000004
BIF_RETURNFSANCESTORS	equ 0x00000008
BIF_EDITBOX		equ 0x00000010
BIF_VALIDATE		equ 0x00000020

BIF_NEWDIALOGSTYLE	equ 0x00000040

BIF_USENEWUI		equ (BIF_NEWDIALOGSTYLE OR BIF_EDITBOX)

BIF_BROWSEINCLUDEURLS	equ 0x00000080
BIF_UAHINT		equ 0x00000100
BIF_NONEWFOLDERBUTTON	equ 0x00000200
BIF_NOTRANSLATETARGETS	equ 0x00000400

BIF_BROWSEFORCOMPUTER	equ 0x00001000
BIF_BROWSEFORPRINTER	equ 0x00002000
BIF_BROWSEINCLUDEFILES	equ 0x00004000
BIF_SHAREABLE		equ 0x00008000
BIF_BROWSEFILEJUNCTIONS equ 0x00010000

BFFM_INITIALIZED	equ 1
BFFM_SELCHANGED		equ 2
BFFM_VALIDATEFAILEDA	equ 3
BFFM_VALIDATEFAILEDW	equ 4
BFFM_IUNKNOWN		equ 5

BFFM_SETSTATUSTEXTA	equ (WM_USER + 100)
BFFM_ENABLEOK		equ (WM_USER + 101)
BFFM_SETSELECTIONA	equ (WM_USER + 102)
BFFM_SETSELECTIONW	equ (WM_USER + 103)
BFFM_SETSTATUSTEXTW	equ (WM_USER + 104)
BFFM_SETOKTEXT		equ (WM_USER + 105)
BFFM_SETEXPANDED	equ (WM_USER + 106)

;SHSTDAPI_(PIDLIST_ABSOLUTE)
SHBrowseForFolderA proto WINAPI \
		  lpbi: LPBROWSEINFOA

;SHSTDAPI_(PIDLIST_ABSOLUTE)
SHBrowseForFolderW proto WINAPI \
		  lpbi: LPBROWSEINFOW


ifdef _UNICODE
SHBrowseForFolder	equ <SHBrowseForFolderW>
BFFM_SETSTATUSTEXT	equ <BFFM_SETSTATUSTEXTW>
BFFM_SETSELECTION	equ <BFFM_SETSEECTIONW>

BFFM_VALIDATEFAILED	equ <BFFM_VALIDATEFAILEDW>
else
SHBrowseForFolder	equ <SHBrowseForFolderA>
BFFM_SETSTATUSTEXT	equ <BFFM_SETSTATUSTEXTA>
BFFM_SETSELECTION	equ <BFFM_SETSEECTIONA>

BFFM_VALIDATEFAILED	equ <BFFM_VALIDATEFAILEDA>
endif


;SHSTDAPI
SHLoadInProc proto WINAPI \
		rclsid: REFCLSID



if (_WIN32_IE GE _WIN32_IE_IE501)
ISHCUTCMDID_DOWNLOADICON	equ 0
ISHCUTCMDID_INTSHORTCUTCREATE	equ 1
if (_WIN32_IE GE _WIN32_IE_IE70)
ISHCUTCMDID_COMMITHISTORY	equ 2
ISHCUTCMDID_SETUSERAWURL	equ 3
endif
CMDID_INTSHORTCUTCREATE equ ISHCUTCMDID_INTSHORTCUTCREATE
endif


STR_PARSE_WITH_PROPERTIES equ <L"ParseWithProperties">

STR_PARSE_PARTIAL_IDLIST equ <L"ParseOriginalItem">


;SHSTDAPI
SHGetDesktopFolder proto WINAPI \
		 ppshf: ptr IShellFolder



.comdef IShellDetails
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDetailsOf	proc :PCUITEMID_CHILD, :UINT, :ptr
    ColumnClick		proc :UINT
    .ends

.comdef IObjMgr
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Append		proc :ptr
    Remove		proc :ptr
    .ends

.comdef ICurrentWorkingDirectory
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDirectory	proc :LPWSTR, :DWORD
    SetDirectory	proc :LPCWSTR
    .ends

.comdef IACList
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Expand		proc :LPCWSTR
    .ends


tagAUTOCOMPLETELISTOPTIONS typedef SDWORD
ACLO_NONE		equ 0
ACLO_CURRENTDIR		equ 1	; enumerate current directory
ACLO_MYCOMPUTER		equ 2	; enumerate MyComputer
ACLO_DESKTOP		equ 4	; enumerate Desktop Folder
ACLO_FAVORITES		equ 8	; enumerate Favorites Folder
ACLO_FILESYSONLY	equ 16	; enumerate only the file system
if (_WIN32_IE GE _WIN32_IE_IE60)
ACLO_FILESYSDIRS	equ 32	; enumerate only the file system dirs, UNC shares, and UNC servers.
endif
if (_WIN32_IE GE _WIN32_IE_IE70)
ACLO_VIRTUALNAMESPACE	equ 64	; enumereate on the virual namespace
endif

.comdef IACList2
    SetOptions		proc :DWORD
    GetOptions		proc :ptr
    .ends


PROGDLG_NORMAL		equ 0x00000000
PROGDLG_MODAL		equ 0x00000001
PROGDLG_AUTOTIME	equ 0x00000002
PROGDLG_NOTIME		equ 0x00000004
PROGDLG_NOMINIMIZE	equ 0x00000008
PROGDLG_NOPROGRESSBAR	equ 0x00000010
if (_WIN32_IE GE _WIN32_IE_IE70)
PROGDLG_MARQUEEPROGRESS equ 0x00000020
PROGDLG_NOCANCEL	equ 0x00000040
endif

PDTIMER_RESET		equ 0x00000001
if (_WIN32_IE GE _WIN32_IE_IE70)
PDTIMER_PAUSE		equ 0x00000002
PDTIMER_RESUME		equ 0x00000003
endif

.comdef IProgressDialog
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    StartProgressDialog proc :HWND, :ptr, :DWORD, :LPCVOID
    StopProgressDialog	proc
    SetTitle		proc :LPCWSTR
    SetAnimation	proc :HINSTANCE, :UINT
    HasUserCancelled	proc
    SetProgress		proc :DWORD, :DWORD
    SetProgress64	proc :ULONGLONG, :ULONGLONG
    SetLine		proc :DWORD, :LPCWSTR, :BOOL, :LPCVOID
    SetCancelMsg	proc :LPCWSTR, :LPCVOID
    Timer		proc :DWORD, :LPCVOID
    .ends


.comdef IDockingWindowSite
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow		proc :ptr
    ContextSensitiveHelp proc :BOOL
    GetBorderDW		proc :ptr, :LPRECT
    RequestBorderSpaceDW proc :ptr, :LPCBORDERWIDTHS
    SetBorderSpaceDW	proc :ptr, :LPCBORDERWIDTHS
    .ends

DWFRF_NORMAL		equ 0x0000
DWFRF_DELETECONFIGDATA	equ 0x0001


DWFAF_HIDDEN		equ 0x0001
DWFAF_GROUP1		equ 0x0002
DWFAF_GROUP2		equ 0x0004
DWFAF_AUTOHIDE		equ 0x0010

.comdef IDockingWindowFrame
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow		proc :ptr
    ContextSensitiveHelp proc :BOOL
    AddToolbar		proc :ptr, :LPCWSTR, :DWORD
    RemoveToolbar	proc :ptr, :DWORD
    FindToolbar		proc :LPCWSTR, :REFIID, :ptr
    .ends

if (_WIN32_IE GE 0x0400)


.comdef IThumbnailCapture
    CaptureThumbnail	proc :ptr, :ptr, :ptr
    .ends
LPTHUMBNAILCAPTURE	typedef ptr IThumbnailCapture

endif


if (NTDDI_VERSION GE NTDDI_WIN2K AND NTDDI_VERSION LT NTDDI_VISTA)

.pragma pack(push, 8)

EnumImageStoreDATAtag	STRUC
szPath			WCHAR MAX_PATH dup(?)
ftTimeStamp		FILETIME ?
ENUMSHELLIMAGESTOREDATA ENDS
PENUMSHELLIMAGESTOREDATA typedef ptr ENUMSHELLIMAGESTOREDATA

.pragma pack(pop)

.comdef IEnumShellImageStore
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Reset		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Clone		proc :ptr
    .ends
LPENUMSHELLIMAGESTORE	typedef ptr IEnumShellImageStore


SHIMSTCAPFLAG_LOCKABLE	equ 0x0001
SHIMSTCAPFLAG_PURGEABLE equ 0x0002

.comdef IShellImageStore
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Open		proc :DWORD, :ptr
    Create		proc :DWORD, :ptr
    ReleaseLock		proc :ptr
    Close		proc :ptr
    Commit		proc :ptr
    IsLocked		proc
    GetMode		proc :ptr
    GetCapabilities	proc :ptr
    AddEntry		proc :LPCWSTR, :ptr, :DWORD, :HBITMAP
    GetEntry		proc :LPCWSTR, :DWORD, :ptr
    DeleteEntry		proc :LPCWSTR
    IsEntryInStore	proc :LPCWSTR, :ptr
    Enum		proc :ptr
    .ends
LPSHELLIMAGESTORE	typedef ptr IShellImageStore

endif

if (_WIN32_IE GE 0x0400)


ISFB_MASK_STATE		equ 0x00000001
ISFB_MASK_BKCOLOR	equ 0x00000002
ISFB_MASK_VIEWMODE	equ 0x00000004
ISFB_MASK_SHELLFOLDER	equ 0x00000008
ISFB_MASK_IDLIST	equ 0x00000010
ISFB_MASK_COLORS	equ 0x00000020

ISFB_STATE_DEFAULT	equ 0x00000000
ISFB_STATE_DEBOSSED	equ 0x00000001
ISFB_STATE_ALLOWRENAME	equ 0x00000002
ISFB_STATE_NOSHOWTEXT	equ 0x00000004
ISFB_STATE_CHANNELBAR	equ 0x00000010
ISFB_STATE_QLINKSMODE	equ 0x00000020
ISFB_STATE_FULLOPEN	equ 0x00000040
ISFB_STATE_NONAMESORT	equ 0x00000080
ISFB_STATE_BTNMINSIZE	equ 0x00000100

ISFBVIEWMODE_SMALLICONS equ 0x0001
ISFBVIEWMODE_LARGEICONS equ 0x0002
if (_WIN32_IE LT _WIN32_IE_IE70)
ISFBVIEWMODE_LOGOS	equ 0x0003
endif

.pragma pack(push, 8)

LPIShellFolder		typedef ptr IShellFolder

BANDINFOSFB		STRUC
dwMask			dd ?
dwStateMask		dd ?
dwState			dd ?
crBkgnd			COLORREF ?
crBtnLt			COLORREF ?
crBtnDk			COLORREF ?
wViewMode		dw ?
wAlign			dw ?
 psf			LPIShellFolder ?
pidl			PIDLIST_ABSOLUTE ?
BANDINFOSFB		ENDS
PBANDINFOSFB		typedef ptr BANDINFOSFB

.pragma pack(pop)

.comdef IShellFolderBand
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InitializeSFB	proc :ptr, :PCIDLIST_ABSOLUTE
    SetBandInfoSFB	proc :PBANDINFOSFB
    GetBandInfoSFB	proc :PBANDINFOSFB
    .ends

.comdef IDeskBarClient
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow		proc :ptr
    ContextSensitiveHelp proc :BOOL
    SetDeskBarSite	proc :ptr
    SetModeDBC		proc :DWORD
    UIActivateDBC	proc :DWORD
    GetSize		proc :DWORD, :LPRECT
    .ends

DBC_GS_IDEAL		equ 0
DBC_GS_SIZEDOWN		equ 1


DBC_HIDE		equ 0
DBC_SHOW		equ 1
DBC_SHOWOBSCURE		equ 2

DBCID_EMPTY		equ 0	; bandsite is empty
DBCID_ONDRAG		equ 1	; (down)DragMoveEnter/Leave vaIn:I4:eDrag
DBCID_CLSIDOFBAR	equ 2	; clsid of bar inside
DBCID_RESIZE		equ 3	; resize from keyboard
DBCID_GETBAR		equ 4	; returns vaOut:VT_UNKNOWN of hosting dockbar (IDeskBar)

endif

if (_WIN32_IE GE 0x400)
ifdef _WININET_

WALLPAPEROPT		STRUC
dwSize			dd ?
dwStyle			dd ?
WALLPAPEROPT		ENDS
LPWALLPAPEROPT		typedef ptr WALLPAPEROPT
LPCWALLPAPEROPT		typedef ptr WALLPAPEROPT

COMPONENTSOPT		STRUC
dwSize			dd ?
fEnableComponents	BOOL ?
fActiveDesktop		BOOL ?
COMPONENTSOPT		ENDS


LPCOMPONENTSOPT		typedef ptr COMPONENTSOPT
LPCCOMPONENTSOPT	typedef ptr COMPONENTSOPT

COMPPOS			STRUC
dwSize			dd ?
iLeft			SINT ?
iTop			SINT ?
dwWidth			dd ?
dwHeight		dd ?
izIndex			SINT ?
fCanResize		BOOL ?
fCanResizeX		BOOL ?
fCanResizeY		BOOL ?
iPreferredLeftPercent	SINT ?
iPreferredTopPercent	SINT ?
COMPPOS			ENDS


LPCOMPPOS		typedef ptr COMPPOS
LPCCOMPPOS		typedef ptr COMPPOS

COMPSTATEINFO		STRUC
dwSize			dd ?
iLeft			SINT ?
iTop			SINT ?
dwWidth			dd ?
dwHeight		dd ?
dwItemState		dd ?
COMPSTATEINFO		ENDS

LPCOMPSTATEINFO		typedef ptr COMPSTATEINFO
LPCCOMPSTATEINFO	typedef ptr COMPSTATEINFO

COMPONENT_TOP		equ (0x3fffffff)

COMP_TYPE_HTMLDOC	equ 0
COMP_TYPE_PICTURE	equ 1
COMP_TYPE_WEBSITE	equ 2
COMP_TYPE_CONTROL	equ 3
COMP_TYPE_CFHTML	equ 4
COMP_TYPE_MAX		equ 4

IE4COMPONENT		STRUC
dwSize			dd ?
dwID			dd ?
iComponentType		SINT ?
fChecked		BOOL ?
fDirty			BOOL ?
fNoScroll		BOOL ?
cpPos			COMPPOS <>
wszFriendlyName		WCHAR MAX_PATH dup(?)
wszSource		WCHAR INTERNET_MAX_URL_LENGTH dup(?)
wszSubscribedURL	WCHAR INTERNET_MAX_URL_LENGTH dup(?)
IE4COMPONENT		ENDS
LPIE4COMPONENT		typedef ptr IE4COMPONENT
LPCIE4COMPONENT		typedef ptr IE4COMPONENT

COMPONENT		STRUC
dwSize			dd ?
dwID			dd ?
iComponentType		SINT ?
fChecked		BOOL ?
fDirty			BOOL ?
fNoScroll		BOOL ?
cpPos			COMPPOS <>
wszFriendlyName		WCHAR MAX_PATH dup(?)
wszSource		WCHAR INTERNET_MAX_URL_LENGTH dup(?)
wszSubscribedURL	WCHAR INTERNET_MAX_URL_LENGTH dup(?)
dwCurItemState		dd ?
csiOriginal		COMPSTATEINFO <>
csiRestored		COMPSTATEINFO <>
COMPONENT		ENDS
LPCOMPONENT		typedef ptr COMPONENT
LPCCOMPONENT		typedef ptr COMPONENT


IS_NORMAL		equ 0x00000001
IS_FULLSCREEN		equ 0x00000002
IS_SPLIT		equ 0x00000004
IS_VALIDSIZESTATEBITS	equ (IS_NORMAL OR IS_SPLIT OR IS_FULLSCREEN)
IS_VALIDSTATEBITS	equ (IS_NORMAL OR IS_SPLIT OR IS_FULLSCREEN OR 0x80000000 OR 0x40000000)

AD_APPLY_SAVE		equ 0x00000001
AD_APPLY_HTMLGEN	equ 0x00000002
AD_APPLY_REFRESH	equ 0x00000004
AD_APPLY_ALL		equ (AD_APPLY_SAVE OR AD_APPLY_HTMLGEN OR AD_APPLY_REFRESH)
AD_APPLY_FORCE		equ 0x00000008
AD_APPLY_BUFFERED_REFRESH equ 0x00000010
AD_APPLY_DYNAMICREFRESH equ 0x00000020

if (NTDDI_VERSION GE NTDDI_VISTA)
AD_GETWP_BMP		equ 0x00000000
AD_GETWP_IMAGE		equ 0x00000001
AD_GETWP_LAST_APPLIED	equ 0x00000002
endif

WPSTYLE_CENTER		equ 0
WPSTYLE_TILE		equ 1
WPSTYLE_STRETCH		equ 2
if (NTDDI_VERSION GE NTDDI_WIN7)
WPSTYLE_KEEPASPECT	equ 3
WPSTYLE_CROPTOFIT	equ 4
WPSTYLE_MAX		equ 5
else
WPSTYLE_MAX		equ 3
endif


COMP_ELEM_TYPE		equ 0x00000001
COMP_ELEM_CHECKED	equ 0x00000002
COMP_ELEM_DIRTY		equ 0x00000004
COMP_ELEM_NOSCROLL	equ 0x00000008
COMP_ELEM_POS_LEFT	equ 0x00000010
COMP_ELEM_POS_TOP	equ 0x00000020
COMP_ELEM_SIZE_WIDTH	equ 0x00000040
COMP_ELEM_SIZE_HEIGHT	equ 0x00000080
COMP_ELEM_POS_ZINDEX	equ 0x00000100
COMP_ELEM_SOURCE	equ 0x00000200
COMP_ELEM_FRIENDLYNAME	equ 0x00000400
COMP_ELEM_SUBSCRIBEDURL equ 0x00000800
COMP_ELEM_ORIGINAL_CSI	equ 0x00001000
COMP_ELEM_RESTORED_CSI	equ 0x00002000
COMP_ELEM_CURITEMSTATE	equ 0x00004000
COMP_ELEM_ALL		equ COMP_ELEM_TYPE OR COMP_ELEM_CHECKED OR COMP_EEM_DIRTY OR \
			    COMP_ELEM_POS_LEFT OR COMP_ELEM_SIZE_WIDTH OR COMP_ELEM_NOSCROLL OR \
			    COMP_ELEM_POS_ZINDEX OR COMP_ELEM_SOURCE OR COMP_ELEM_SIZE_HEIGHT OR \
			    COMP_ELEM_POS_TOP OR COMP_ELEM_SUBSCRIBEDURL OR COMP_ELEM_FRIENDLYNAME OR \
			    COMP_ELEM_RESTORED_CSI OR COMP_ELEM_CURITEMSTATE OR COMP_ELEM_ORIGINAL_CSI


tagDTI_ADTIWUI		typedef SDWORD
DTI_ADDUI_DEFAULT	equ 0x00000000
DTI_ADDUI_DISPSUBWIZARD equ 0x00000001
DTI_ADDUI_POSITIONITEM	equ 0x00000002

ADDURL_SILENT		equ 0X0001

COMPONENT_DEFAULT_LEFT	equ (0xFFFF)
COMPONENT_DEFAULT_TOP	equ (0xFFFF)


.comdef IActiveDesktop
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ApplyChanges	proc :DWORD
    GetWallpaper	proc :LPWSTR, :UINT, :DWORD
    SetWallpaper	proc :LPCWSTR, :DWORD
    GetWallpaperOptions proc :LPWALLPAPEROPT, :DWORD
    SetWallpaperOptions proc :LPCWALLPAPEROPT, :DWORD
    GetPattern		proc :LPWSTR, :UINT, :DWORD
    SetPattern		proc :LPCWSTR, :DWORD
    GetDesktopItemOptions proc :LPCOMPONENTSOPT, :DWORD
    SetDesktopItemOptions proc :LPCCOMPONENTSOPT, :DWORD
    AddDesktopItem	proc :LPCCOMPONENT, :DWORD
    AddDesktopItemWithUI proc :HWND, :LPCOMPONENT, :DWORD
    ModifyDesktopItem	proc :LPCCOMPONENT, :DWORD
    RemoveDesktopItem	proc :LPCCOMPONENT, :DWORD
    GetDesktopItemCount proc :LPINT, :DWORD
    GetDesktopItem	proc :SINT, :LPCOMPONENT, :DWORD
    GetDesktopItemByID	proc :ULONG_PTR, :LPCOMPONENT, :DWORD
    GenerateDesktopItemHtml proc :LPCWSTR, :LPCOMPONENT, :DWORD
    AddUrl		proc :HWND, :LPCWSTR, :LPCOMPONENT, :DWORD
    GetDesktopItemBySource proc :LPCWSTR, :LPCOMPONENT, :DWORD
    .ends
LPACTIVEDESKTOP		typedef ptr IActiveDesktop

SSM_CLEAR		equ 0x0000
SSM_SET			equ 0x0001
SSM_REFRESH		equ 0x0002
SSM_UPDATE		equ 0x0004

SCHEME_DISPLAY		equ 0x0001
SCHEME_EDIT		equ 0x0002
SCHEME_LOCAL		equ 0x0004
SCHEME_GLOBAL		equ 0x0008
SCHEME_REFRESH		equ 0x0010
SCHEME_UPDATE		equ 0x0020
SCHEME_DONOTUSE		equ 0x0040
SCHEME_CREATE		equ 0x0080

.comdef IActiveDesktopP
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetSafeMode		proc :DWORD
    EnsureUpdateHTML	proc
    SetScheme		proc :LPCWSTR, :DWORD
    GetScheme		proc :LPWSTR, :ptr, :DWORD
    .ends
LPACTIVEDESKTOPP	typedef ptr IActiveDesktopP

GADOF_DIRTY		equ 0x00000001

.comdef IADesktopP2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ReReadWallpaper	proc
    GetADObjectFlags	proc :ptr, :DWORD
    UpdateAllDesktopSubscriptions proc
    MakeDynamicChanges	proc :ptr
    .ends
LPADESKTOPP2		typedef ptr IADesktopP2


endif

if (_WIN32_IE GE 0x0500)

MAX_COLUMN_NAME_LEN	equ 80
MAX_COLUMN_DESC_LEN	equ 128

.pragma pack(push, 1)

SHCOLUMNINFO		STRUC
scid			SHCOLUMNID <>
vt			VARTYPE ?
fmt			dd ?
cChars			UINT ?
csFlags			dd ?
wszTitle		WCHAR MAX_COLUMN_NAME_LEN dup(?)
wszDescription		WCHAR MAX_COLUMN_DESC_LEN dup(?)
SHCOLUMNINFO		ENDS
LPSHCOLUMNINFO		typedef ptr SHCOLUMNINFO
LPCSHCOLUMNINFO		typedef ptr SHCOLUMNINFO

.pragma pack(pop)

.pragma pack(push, 8)

SHCOLUMNINIT		STRUC
dwFlags			ULONG ?
dwReserved		ULONG ?
wszFolder		WCHAR MAX_PATH dup(?)
SHCOLUMNINIT		ENDS
LPSHCOLUMNINIT		typedef ptr SHCOLUMNINIT
LPCSHCOLUMNINIT		typedef ptr SHCOLUMNINIT

SHCDF_UPDATEITEM	equ 0x00000001

SHCOLUMNDATA		STRUC
dwFlags			ULONG ?
dwFileAttributes	dd ?
dwReserved		ULONG ?
pwszExt			LPWSTR ?
wszFile			WCHAR MAX_PATH dup(?)
SHCOLUMNDATA		ENDS
LPSHCOLUMNDATA		typedef ptr SHCOLUMNDATA
LPCSHCOLUMNDATA		typedef ptr SHCOLUMNDATA

.pragma pack(pop)

.comdef IColumnProvider
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPCSHCOLUMNINIT
    GetColumnInfo	proc :DWORD, :ptr
    GetItemData		proc :LPCSHCOLUMNID, :LPCSHCOLUMNDATA, :ptr
    .ends

endif
endif


CFSTR_SHELLIDLIST		equ <"Shell IDList Array">
CFSTR_SHELLIDLISTOFFSET		equ <"Shell Object Offsets">
CFSTR_NETRESOURCES		equ <"Net Resource">
CFSTR_FILEDESCRIPTORA		equ <"FileGroupDescriptor">
CFSTR_FILEDESCRIPTORW		equ <"FileGroupDescriptorW">
CFSTR_FILECONTENTS		equ <"FileContents">
CFSTR_FILENAMEA			equ <"FileName">
CFSTR_FILENAMEW			equ <"FileNameW">
CFSTR_PRINTERGROUP		equ <"PrinterFriendlyName">
CFSTR_FILENAMEMAPA		equ <"FileNameMap">
CFSTR_FILENAMEMAPW		equ <"FileNameMapW">
CFSTR_SHELLURL			equ <"UniformResourceocator">
CFSTR_INETURLA			equ <CFSTR_SHELLURL>
CFSTR_INETURLW			equ <"UniformResourceocatorW">
CFSTR_PREFERREDDROPEFFECT	equ <"Preferred DropEffect">
CFSTR_PERFORMEDDROPEFFECT	equ <"Performed DropEffect">
CFSTR_PASTESUCCEEDED		equ <"Paste Succeeded">
CFSTR_INDRAGLOOP		equ <"InShellDragLoop">
CFSTR_MOUNTEDVOLUME		equ <"MountedVolume">
CFSTR_PERSISTEDDATAOBJECT	equ <"PersistedDataObject">
CFSTR_TARGETCLSID		equ <"TargetCLSID">
CFSTR_LOGICALPERFORMEDDROPEFFECT equ <"Logical Performed DropEffect">
CFSTR_AUTOPLAY_SHELLIDLISTS	equ <"Autoplay Enumerated IDList Array">
CFSTR_UNTRUSTEDDRAGDROP		equ <"UntrustedDragDrop">
CFSTR_FILE_ATTRIBUTES_ARRAY	equ <"File Attributes Array">
CFSTR_INVOKECOMMAND_DROPPARAM	equ <"InvokeCommand DropParam">
CFSTR_SHELLDROPHANDLER		equ <"DropHandlerCLSID">
CFSTR_DROPDESCRIPTION		equ <"DropDescription">

ifdef _UNICODE
CFSTR_FILEDESCRIPTOR	equ CFSTR_FILEDESCRIPTORW
CFSTR_FILENAME		equ CFSTR_FILENAMEW
CFSTR_FILENAMEMAP	equ CFSTR_FILENAMEMAPW
CFSTR_INETURL		equ CFSTR_INETURLW
else
CFSTR_FILEDESCRIPTOR	equ CFSTR_FILEDESCRIPTORA
CFSTR_FILENAME		equ CFSTR_FILENAMEA
CFSTR_FILENAMEMAP	equ CFSTR_FILENAMEMAPA
CFSTR_INETURL		equ CFSTR_INETURLA
endif

DVASPECT_SHORTNAME	equ 2
DVASPECT_COPY		equ 3
DVASPECT_LINK		equ 4

.pragma pack(push, 8)

NRESARRAY		STRUC
cItems			UINT ?
nr			NETRESOURCE 1 dup(<>)
NRESARRAY		ENDS
LPNRESARRAY		typedef ptr NRESARRAY

.pragma pack(pop)

CIDA			STRUC
cidl			UINT ?
aoffset			UINT 1 dup(?)
CIDA			ENDS
LPIDA			typedef ptr CIDA

FD_FLAGS		typedef SDWORD
FD_CLSID		equ 0x00000001
FD_SIZEPOINT		equ 0x00000002
FD_ATTRIBUTES		equ 0x00000004
FD_CREATETIME		equ 0x00000008
FD_ACCESSTIME		equ 0x00000010
FD_WRITESTIME		equ 0x00000020
FD_FILESIZE		equ 0x00000040
FD_PROGRESSUI		equ 0x00004000
FD_LINKUI		equ 0x00008000	; 'link' UI is prefered
if (NTDDI_VERSION GE NTDDI_VISTA)
FD_UNICODE		equ 0x80000000	; this descriptor is UNICODE
endif


FILEDESCRIPTORA		STRUC
dwFlags			dd ?
clsid			CLSID <>
sizel			SIZEL <>
pointl			POINTL <>
dwFileAttributes	dd ?
ftCreationTime		FILETIME <>
ftLastAccessTime	FILETIME <>
ftLastWriteTime		FILETIME <>
nFileSizeHigh		dd ?
nFileSizeLow		dd ?
cFileName		CHAR  MAX_PATH	dup(?)
FILEDESCRIPTORA		ENDS
LPFILEDESCRIPTORA	typedef ptr FILEDESCRIPTORA

FILEDESCRIPTORW		STRUC
dwFlags			dd ?
clsid			CLSID <>
sizel			SIZEL <>
pointl			POINTL <>
dwFileAttributes	dd ?
ftCreationTime		FILETIME <>
ftLastAccessTime	FILETIME <>
ftLastWriteTime		FILETIME <>
nFileSizeHigh		dd ?
nFileSizeLow		dd ?
cFileName		WCHAR  MAX_PATH	 dup(?)
FILEDESCRIPTORW		ENDS
LPFILEDESCRIPTORW	typedef ptr FILEDESCRIPTORW
ifdef _UNICODE
FILEDESCRIPTOR		equ <FILEDESCRIPTORW>
LPFILEDESCRIPTOR	equ <LPFILEDESCRIPTORW>
else
FILEDESCRIPTOR		equ <FILEDESCRIPTORA>
LPFILEDESCRIPTOR	equ <LPFILEDESCRIPTORA>
endif

FILEGROUPDESCRIPTORA	STRUC
cItems			UINT ?
fgd			FILEDESCRIPTORA 1 dup(<>)
FILEGROUPDESCRIPTORA	ENDS
LPFILEGROUPDESCRIPTORA	typedef ptr FILEGROUPDESCRIPTORA

FILEGROUPDESCRIPTORW	STRUC
cItems			UINT ?
fgd			FILEDESCRIPTORW 1 dup(<>)
FILEGROUPDESCRIPTORW	ENDS
LPFILEGROUPDESCRIPTORW	typedef ptr FILEGROUPDESCRIPTORW

ifdef _UNICODE
FILEGROUPDESCRIPTOR	equ <FILEGROUPDESCRIPTORW>
LPFILEGROUPDESCRIPTOR	equ <LPFILEGROUPDESCRIPTORW>
else
FILEGROUPDESCRIPTOR	equ <FILEGROUPDESCRIPTORA>
LPFILEGROUPDESCRIPTOR	equ <LPFILEGROUPDESCRIPTORA>
endif

DROPFILES		STRUC
pFiles			dd ?
pt			POINT <>
fNC			BOOL ?
fWide			BOOL ?
DROPFILES		ENDS
LPDROPFILES		typedef ptr DROPFILES


if (NTDDI_VERSION GE NTDDI_VISTA)
FILE_ATTRIBUTES_ARRAY	STRUC
cItems			UINT ?
dwSumFileAttributes	dd ?
dwProductFileAttributes dd ?
rgdwFileAttributes	dd 1 dup(?)
FILE_ATTRIBUTES_ARRAY	ENDS
endif


if (NTDDI_VERSION GE NTDDI_VISTA)
DROPIMAGETYPE		typedef SDWORD
DROPIMAGE_INVALID	equ -1			; no image preference (use default)
DROPIMAGE_NONE		equ 0			; red "no" circle
DROPIMAGE_COPY		equ DROPEFFECT_COPY	; plus for copy
DROPIMAGE_MOVE		equ DROPEFFECT_MOVE	; movement arrow for move
DROPIMAGE_LINK		equ DROPEFFECT_LINK	; link arrow for link
DROPIMAGE_LABEL		equ 6			; tag icon to indicate metadata will be changed
DROPIMAGE_WARNING	equ 7			; yellow exclamation, something is amiss with the operation
DROPIMAGE_NOIMAGE	equ 8			; no image at all

DROPDESCRIPTION		STRUC
_type			DROPIMAGETYPE ?
szMessage		WCHAR MAX_PATH dup(?)
szInsert		WCHAR MAX_PATH dup(?)
DROPDESCRIPTION		ENDS

endif


SHChangeNotifyEntry	STRUC
pidl			PCIDLIST_ABSOLUTE ?
fRecursive		BOOL ?
SHChangeNotifyEntry	ENDS



SHCNRF_InterruptLevel	equ 0x0001
SHCNRF_ShellLevel	equ 0x0002
SHCNRF_RecursiveInterrupt equ 0x1000
SHCNRF_NewDelivery	equ 0x8000

SHCNE_RENAMEITEM	equ 0x00000001
SHCNE_CREATE		equ 0x00000002
SHCNE_DELETE		equ 0x00000004
SHCNE_MKDIR		equ 0x00000008
SHCNE_RMDIR		equ 0x00000010
SHCNE_MEDIAINSERTED	equ 0x00000020
SHCNE_MEDIAREMOVED	equ 0x00000040
SHCNE_DRIVEREMOVED	equ 0x00000080
SHCNE_DRIVEADD		equ 0x00000100
SHCNE_NETSHARE		equ 0x00000200
SHCNE_NETUNSHARE	equ 0x00000400
SHCNE_ATTRIBUTES	equ 0x00000800
SHCNE_UPDATEDIR		equ 0x00001000
SHCNE_UPDATEITEM	equ 0x00002000
SHCNE_SERVERDISCONNECT	equ 0x00004000
SHCNE_UPDATEIMAGE	equ 0x00008000
SHCNE_DRIVEADDGUI	equ 0x00010000
SHCNE_RENAMEFOLDER	equ 0x00020000
SHCNE_FREESPACE		equ 0x00040000

if (_WIN32_IE GE 0x0400)

SHCNE_EXTENDED_EVENT	equ 0x04000000
endif

SHCNE_ASSOCCHANGED	equ 0x08000000

SHCNE_DISKEVENTS	equ 0x0002381F
SHCNE_GLOBALEVENTS	equ 0x0C0581E0
SHCNE_ALLEVENTS		equ 0x7FFFFFFF
SHCNE_INTERRUPT		equ 0x80000000

if (_WIN32_IE GE 0x0400)

SHCNEE_ORDERCHANGED	equ 2
SHCNEE_MSI_CHANGE	equ 4
SHCNEE_MSI_UNINSTALL	equ 5
endif

SHCNF_IDLIST		equ 0x0000
SHCNF_PATHA		equ 0x0001
SHCNF_PRINTERA		equ 0x0002
SHCNF_DWORD		equ 0x0003
SHCNF_PATHW		equ 0x0005
SHCNF_PRINTERW		equ 0x0006
SHCNF_TYPE		equ 0x00FF
SHCNF_FLUSH		equ 0x1000
SHCNF_FLUSHNOWAIT	equ 0x3000

SHCNF_NOTIFYRECURSIVE	equ 0x10000

ifdef _UNICODE
SHCNF_PATH		equ SHCNF_PATHW
SHCNF_PRINTER		equ SHCNF_PRINTERW
else
SHCNF_PATH		equ SHCNF_PATHA
SHCNF_PRINTER		equ SHCNF_PRINTERA
endif

;SHSTDAPI
SHChangeNotify proto WINAPI \
	      wEventId: LONG,
		uFlags: UINT,
	       dwItem1: LPCVOID,
	       dwItem2: LPCVOID



.comdef IShellChangeNotify
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnChange		proc :LONG, :PCIDLIST_ABSOLUTE, :PCIDLIST_ABSOLUTE
    .ends


.comdef IQueryInfo
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetInfoTip		proc :DWORD, :ptr
    GetInfoFlags	proc :ptr
    .ends

QITIPF_DEFAULT		equ 0x00000000
QITIPF_USENAME		equ 0x00000001
QITIPF_LINKNOTARGET	equ 0x00000002
QITIPF_LINKUSETARGET	equ 0x00000004
if (NTDDI_VERSION GE NTDDI_WINXP)
QITIPF_USESLOWTIP	equ 0x00000008
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
QITIPF_SINGLELINE	equ 0x00000010
endif

QIF_CACHED		equ 0x00000001
QIF_DONTEXPANDFOLDER	equ 0x00000002

SHARD			typedef SDWORD
SHARD_PIDL		equ 0x00000001
SHARD_PATHA		equ 0x00000002
SHARD_PATHW		equ 0x00000003
if (NTDDI_VERSION GE NTDDI_WIN7)
SHARD_APPIDINFO		equ 0x00000004
SHARD_APPIDINFOIDLIST	equ 0x00000005
SHARD_LINK		equ 0x00000006
SHARD_APPIDINFOLINK	equ 0x00000007
SHARD_SHELLITEM		equ 0x00000008
endif

if (NTDDI_VERSION GE NTDDI_WIN7)

LPIShellItem		typedef ptr IShellItem
SHARDAPPIDINFO		STRUC
psi			LPIShellItem ?
pszAppID		PCWSTR ?
SHARDAPPIDINFO		ENDS

SHARDAPPIDINFOIDLIST	STRUC
pidl			PCIDLIST_ABSOLUTE ?
pszAppID		PCWSTR ?
SHARDAPPIDINFOIDLIST	ENDS

LPIShellLink		typedef ptr IShellLink
SHARDAPPIDINFOLINK	STRUC
psl			LPIShellLink ?
pszAppID		PCWSTR ?
SHARDAPPIDINFOLINK	ENDS

endif

ifdef _UNICODE
SHARD_PATH		equ <SHARD_PATHW>
else
SHARD_PATH		equ <SHARD_PATHA>
endif

;SHSTDAPI
SHAddToRecentDocs proto WINAPI \
		uFlags: UINT,
		    pv: LPCVOID


SHChangeDWORDAsIDList	STRUC
cb			USHORT ?
dwItem1			dd ?
dwItem2			dd ?
cbZero			USHORT ?
SHChangeDWORDAsIDList	ENDS
LPSHChangeDWORDAsIDList typedef ptr SHChangeDWORDAsIDList


if (NTDDI_VERSION GE NTDDI_WIN2K)


SHChangeUpdateImageIDList STRUC
cb			USHORT ?
iIconIndex		SINT ?
iCurIndex		SINT ?
uFlags			UINT ?
dwProcessID		dd ?
szName			WCHAR MAX_PATH dup(?)
cbZero			USHORT ?
SHChangeUpdateImageIDList ENDS
 LPSHChangeUpdateImageIDList typedef ptr SHChangeUpdateImageIDList
;SHSTDAPI
SHHandleUpdateImage proto WINAPI \
	     pidlExtra: PCIDLIST_ABSOLUTE



SHChangeProductKeyAsIDList  STRUC
cb			USHORT ?
wszProductKey		WCHAR 39 dup(?)
cbZero			USHORT ?
SHChangeProductKeyAsIDList ENDS
LPSHChangeProductKeyAsIDList typedef ptr SHChangeProductKeyAsIDList


;SHSTDAPI
SHUpdateImageA proto WINAPI \
	   pszHashItem: LPCSTR,
		iIndex: SINT,
		uFlags: UINT,
	   iImageIndex: SINT

;SHSTDAPI
SHUpdateImageW proto WINAPI \
	   pszHashItem: LPCWSTR,
		iIndex: SINT,
		uFlags: UINT,
	   iImageIndex: SINT

ifdef _UNICODE
SHUpdateImage		equ <SHUpdateImageW>
else
SHUpdateImage		equ <SHUpdateImageA>
endif
endif

;SHSTDAPI_(ULONG)
SHChangeNotifyRegister proto WINAPI \
		  hwnd: HWND,
	      fSources: SINT,
	       fEvents: LONG,
		  wMsg: UINT,
	      cEntries: SINT,
		pshcne: ptr SHChangeNotifyEntry

;SHSTDAPI
SHChangeNotifyDeregister proto WINAPI \
		  ulID: DWORD


SCNRT_STATUS		typedef SDWORD
SCNRT_ENABLE		equ 0
SCNRT_DISABLE		equ 1

if (NTDDI_VERSION GE NTDDI_VISTA)
;STDAPI
SHChangeNotifyRegisterThread proto WINAPI \
		status: SCNRT_STATUS

endif

;SHSTDAPI_(HANDLE)
SHChangeNotification_Lock proto WINAPI \
	      hChange: HANDLE,
	     dwProcId: DWORD,
	       pppidl: ptr PIDLIST_ABSOLUTE,
	      plEvent: ptr

;SHSTDAPI
SHChangeNotification_Unlock proto WINAPI \
		 hLock: HANDLE

if (_WIN32_IE GE 0x0400)
;SHSTDAPI
SHGetRealIDL proto WINAPI \
		   psf: ptr IShellFolder,
	    pidlSimple: PCUITEMID_CHILD,
	     ppidlReal: ptr PITEMID_CHILD

endif


;SHSTDAPI
SHGetInstanceExplorer proto WINAPI \
		 ppunk: ptr IUnknown


SHGDFIL_FINDDATA	equ 1
SHGDFIL_NETRESOURCE	equ 2
SHGDFIL_DESCRIPTIONID	equ 3

SHDID_ROOT_REGITEM	equ 1
SHDID_FS_FILE		equ 2
SHDID_FS_DIRECTORY	equ 3
SHDID_FS_OTHER		equ 4
SHDID_COMPUTER_DRIVE35	equ 5
SHDID_COMPUTER_DRIVE525 equ 6
SHDID_COMPUTER_REMOVABLE equ 7
SHDID_COMPUTER_FIXED	equ 8
SHDID_COMPUTER_NETDRIVE equ 9
SHDID_COMPUTER_CDROM	equ 10
SHDID_COMPUTER_RAMDISK	equ 11
SHDID_COMPUTER_OTHER	equ 12
SHDID_NET_DOMAIN	equ 13
SHDID_NET_SERVER	equ 14
SHDID_NET_SHARE		equ 15
SHDID_NET_RESTOFNET	equ 16
SHDID_NET_OTHER		equ 17
if (NTDDI_VERSION GE NTDDI_WINXP)
SHDID_COMPUTER_IMAGING	equ 18
SHDID_COMPUTER_AUDIO	equ 19
SHDID_COMPUTER_SHAREDDOCS equ 20
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
SHDID_MOBILE_DEVICE	equ 21
endif

.pragma pack(push, 8)

SHDESCRIPTIONID		STRUC
dwDescriptionId		dd ?
clsid			CLSID <>
SHDESCRIPTIONID		ENDS
LPSHDESCRIPTIONID	typedef ptr SHDESCRIPTIONID

.pragma pack(pop)


;SHSTDAPI
SHGetDataFromIDListA proto WINAPI \
		   psf: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
	       nFormat: SINT,
		    pv: PVOID,
		    cb: SINT
SHGetDataFromIDListW proto WINAPI \
		   psf: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
	       nFormat: SINT,
		    pv: PVOID,
		    cb: SINT
ifdef _UNICODE
SHGetDataFromIDList	equ <SHGetDataFromIDistW>
else
SHGetDataFromIDList	equ <SHGetDataFromIDistA>
endif



PRF_VERIFYEXISTS	equ 0x0001
PRF_TRYPROGRAMEXTENSIONS equ (0x0002 OR PRF_VERIFYEXISTS)
PRF_FIRSTDIRDEF		equ 0x0004
PRF_DONTFINDLNK		equ 0x0008
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
PRF_REQUIREABSOLUTE	equ 0x0010
endif

;SHSTDAPI
RestartDialog proto WINAPI \
		  hwnd: HWND,
	      lpPrompt: LPCWSTR,
	      dwReturn: DWORD

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
RestartDialogEx proto WINAPI \
		  hwnd: HWND,
	      lpPrompt: LPCWSTR,
	      dwReturn: DWORD,
	  dwReasonCode: DWORD

endif

;SHSTDAPI
SHCoCreateInstance proto WINAPI \
	      pszCLSID: LPCWSTR,
		pclsid: ptr CLSID,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
		   ppv: PVOID


if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHCreateDataObject proto WINAPI \
	    pidlFolder: PCIDLIST_ABSOLUTE,
		  cidl: UINT,
		 apidl: PCUITEMID_CHILD_ARRAY,
	      pdtInner: ptr IDataObject,
		  riid: REFIID,
		   ppv: PVOID
endif
;SHSTDAPI
CIDLData_CreateFromIDArray proto WINAPI \
	    pidlFolder: PCIDLIST_ABSOLUTE,
		  cidl: UINT,
		 apidl: PCUIDLIST_RELATIVE_ARRAY,
	       ppdtobj: ptr IDataObject

;SHSTDAPI
SHCreateStdEnumFmtEtc proto WINAPI \
		  cfmt: UINT,
		  afmt: ptr FORMATETC,
       ppenumFormatEtc: ptr IEnumFORMATETC

;SHSTDAPI
SHDoDragDrop proto WINAPI \
		  hwnd: HWND,
		 pdata: ptr IDataObject,
		 pdsrc: ptr IDropSource,
	      dwEffect: DWORD,
	     pdwEffect: ptr DWORD

NUM_POINTS		equ 3
AUTO_SCROLL_DATA	STRUC
iNextSample		SINT ?
dwLastScroll		dd ?
bFull			BOOL ?
pts			POINT NUM_POINTS dup(<>)
dwTimes			dd NUM_POINTS dup(?)
AUTO_SCROLL_DATA	ENDS

;SHSTDAPI
DAD_SetDragImage proto WINAPI \
		   him: HIMAGELIST,
	     pptOffset: ptr POINT

;SHSTDAPI
DAD_DragEnterEx proto WINAPI \
	    hwndTarget: HWND,
	       ptStart: POINT

;SHSTDAPI
DAD_DragEnterEx2 proto WINAPI \
	    hwndTarget: HWND,
	       ptStart: POINT,
	     pdtObject: ptr IDataObject

;SHSTDAPI
DAD_ShowDragImage proto WINAPI \
		 fShow: BOOL

;SHSTDAPI
DAD_DragMove proto WINAPI \
		    pt: POINT

;SHSTDAPI
DAD_DragLeave proto WINAPI
;SHSTDAPI
DAD_AutoScroll proto WINAPI \
		  hwnd: HWND,
		   pad: ptr AUTO_SCROLL_DATA,
		pptNow: ptr POINT

CABINETSTATE		STRUC
cLength			dw ?
nVersion		dw ?
Flags			UINT ?
;fFullPathTitle		   : 1 BOOL ?
;fSaveLocalView		   : 1 BOOL ?
;fNotShell		   : 1 BOOL ?
;fSimpleDefault		   : 1 BOOL ?
;fDontShowDescBar	   : 1 BOOL ?
;fNewWindowMode		   : 1 BOOL ?
;fShowCompColor		   : 1 BOOL ?
;fDontPrettyNames	   : 1 BOOL ?
;fAdminsCreateCommonGroups : 1 BOOL ?
;fUnusedFlags : 7	 UINT ?
fMenuEnumFilter		UINT ?
CABINETSTATE		ENDS
LPCABINETSTATE		typedef ptr CABINETSTATE

CABINETSTATE_VERSION	equ 2

;SHSTDAPI
ReadCabinetState proto WINAPI \
		   pcs: ptr CABINETSTATE,
	       cLength: SINT

;SHSTDAPI
WriteCabinetState proto WINAPI \
		   pcs: ptr CABINETSTATE

;SHSTDAPI
PathMakeUniqueName proto WINAPI \
	 pszUniqueName: LPWSTR,
		cchMax: UINT,
	   pszTemplate: LPCWSTR,
	  pszLongPlate: LPCWSTR,
		pszDir: LPCWSTR

;SHSTDAPI
PathQualify proto WINAPI \
		   psz: LPWSTR

;SHSTDAPI
PathIsExe proto WINAPI \
	       pszPath: LPCWSTR

;SHSTDAPI
PathIsSlowA proto WINAPI \
	       pszFile: LPCSTR,
		dwAttr: DWORD

;SHSTDAPI
PathIsSlowW proto WINAPI \
	       pszFile: LPCWSTR,
		dwAttr: DWORD

ifdef _UNICODE
PathIsSlow		equ <PathIsSlowW>
else
PathIsSlow		equ <PathIsSlowA>
endif
PCS_FATAL		equ 0x80000000
PCS_REPLACEDCHAR	equ 0x00000001
PCS_REMOVEDCHAR		equ 0x00000002
PCS_TRUNCATED		equ 0x00000004
PCS_PATHTOOLONG		equ 0x00000008

;SHSTDAPI
PathCleanupSpec proto WINAPI \
		pszDir: LPCWSTR,
	       pszSpec: LPWSTR


;SHSTDAPI
PathResolve proto WINAPI \
	      lpszPath: LPWSTR,
		  dirs: PZPCWSTR,
		fFlags: UINT

;SHSTDAPI
GetFileNameFromBrowse proto WINAPI \
		  hwnd: HWND,
	   pszFilePath: LPWSTR,
	   cchFilePath: UINT,
	 pszWorkingDir: LPCWSTR,
	     pszDefExt: LPCWSTR,
	    pszFilters: LPCWSTR,
	      pszTitle: LPCWSTR

;SHSTDAPI
DriveType proto WINAPI \
		iDrive: SINT


;SHSTDAPI
RealDriveType proto WINAPI \
		iDrive: SINT,
	   fOKToHitNet: BOOL

;SHSTDAPI
IsNetDrive proto WINAPI \
		iDrive: SINT

MM_ADDSEPARATOR		equ 0x00000001
MM_SUBMENUSHAVEIDS	equ 0x00000002
MM_DONTREMOVESEPS	equ 0x00000004

;SHSTDAPI_(UINT)
Shell_MergeMenus proto WINAPI \
		 hmDst: HMENU,
		 hmSrc: HMENU,
	       uInsert: UINT,
	     uIDAdjust: UINT,
	  uIDAdjustMax: UINT,
		uFlags: ULONG



;SHSTDAPI
SHObjectProperties proto WINAPI \
		  hwnd: HWND,
	shopObjectType: DWORD,
	 pszObjectName: PCWSTR,
       pszPropertyPage: PCWSTR


SHOP_PRINTERNAME	equ 0x00000001
SHOP_FILEPATH		equ 0x00000002
SHOP_VOLUMEGUID		equ 0x00000004

;SHSTDAPI
SHFormatDrive proto WINAPI \
		  hwnd: HWND,
		 drive: UINT,
		 fmtID: UINT,
	       options: UINT


SHFMT_ID_DEFAULT	equ 0xFFFF

SHFMT_OPT_FULL		equ 0x0001
SHFMT_OPT_SYSONLY	equ 0x0002

SHFMT_ERROR		equ 0xFFFFFFFF
SHFMT_CANCEL		equ 0xFFFFFFFE
SHFMT_NOFORMAT		equ 0xFFFFFFFD

ifndef HPSXA_DEFINED
HPSXA_DEFINED equ 1
DECLARE_HANDLE( HPSXA )
endif
;UINT
SHCreatePropSheetExtArray proto WINAPI \
		  hKey: HKEY,
	     pszSubKey: LPCWSTR,
	     max_iface: UINT

;UINT
SHDestroyPropSheetExtArray proto WINAPI \
		 hpsxa: HPSXA

;UINT
SHAddFromPropSheetExtArray proto WINAPI \
		 hpsxa: HPSXA,
	   lpfnAddPage: LPFNADDPROPSHEETPAGE,
		lParam: LPARAM

;UINT
SHReplaceFromPropSheetExtArray proto WINAPI \
		 hpsxa: HPSXA,
	       uPageID: UINT,
       lpfnReplaceWith: LPFNADDPROPSHEETPAGE,
		lParam: LPARAM

if (NTDDI_VERSION GE NTDDI_WIN2K AND NTDDI_VERSION LT NTDDI_VISTA)
.comdef IDefViewFrame
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindowLV		proc :ptr
    ReleaseWindowLV	proc
    GetShellFolder	proc :ptr
    .ends
endif
RESTRICTIONS		typedef SDWORD
REST_NONE		equ 0x00000000
REST_NORUN		equ 0x00000001
REST_NOCLOSE		equ 0x00000002
REST_NOSAVESET		equ 0x00000004
REST_NOFILEMENU		equ 0x00000008
REST_NOSETFOLDERS	equ 0x00000010
REST_NOSETTASKBAR	equ 0x00000020
REST_NODESKTOP		equ 0x00000040
REST_NOFIND		equ 0x00000080
REST_NODRIVES		equ 0x00000100
REST_NODRIVEAUTORUN	equ 0x00000200
REST_NODRIVETYPEAUTORUN equ 0x00000400
REST_NONETHOOD		equ 0x00000800
REST_STARTBANNER	equ 0x00001000
REST_RESTRICTRUN	equ 0x00002000
REST_NOPRINTERTABS	equ 0x00004000
REST_NOPRINTERDELETE	equ 0x00008000
REST_NOPRINTERADD	equ 0x00010000
REST_NOSTARTMENUSUBFOLDERS equ 0x00020000
REST_MYDOCSONNET	equ 0x00040000
REST_NOEXITTODOS	equ 0x00080000
REST_ENFORCESHELLEXTSECURITY equ 0x00100000
REST_LINKRESOLVEIGNORELINKINFO equ 0x00200000
REST_NOCOMMONGROUPS	equ 0x00400000
REST_SEPARATEDESKTOPPROCESS equ 0x00800000
REST_NOWEB		equ 0x01000000
REST_NOTRAYCONTEXTMENU	equ 0x02000000
REST_NOVIEWCONTEXTMENU	equ 0x04000000
REST_NONETCONNECTDISCONNECT equ 0x08000000
REST_STARTMENULOGOFF	equ 0x10000000
REST_NOSETTINGSASSIST	equ 0x20000000
REST_NOINTERNETICON	equ 0x40000001
REST_NORECENTDOCSHISTORY equ 0x40000002
REST_NORECENTDOCSMENU	equ 0x40000003
REST_NOACTIVEDESKTOP	equ 0x40000004
REST_NOACTIVEDESKTOPCHANGES equ 0x40000005
REST_NOFAVORITESMENU	equ 0x40000006
REST_CLEARRECENTDOCSONEXIT equ 0x40000007
REST_CLASSICSHELL	equ 0x40000008
REST_NOCUSTOMIZEWEBVIEW equ 0x40000009
REST_NOHTMLWALLPAPER	equ 0x40000010
REST_NOCHANGINGWALLPAPER equ 0x40000011
REST_NODESKCOMP		equ 0x40000012
REST_NOADDDESKCOMP	equ 0x40000013
REST_NODELDESKCOMP	equ 0x40000014
REST_NOCLOSEDESKCOMP	equ 0x40000015
REST_NOCLOSE_DRAGDROPBAND equ 0x40000016
REST_NOMOVINGBAND	equ 0x40000017
REST_NOEDITDESKCOMP	equ 0x40000018
REST_NORESOLVESEARCH	equ 0x40000019
REST_NORESOLVETRACK	equ 0x4000001A
REST_FORCECOPYACLWITHFILE equ 0x4000001B
if (NTDDI_VERSION LT NTDDI_VISTA)
REST_NOLOGO3CHANNELNOTIFY equ 0x4000001C
endif
REST_NOFORGETSOFTWAREUPDATE equ 0x4000001D
REST_NOSETACTIVEDESKTOP equ 0x4000001E
REST_NOUPDATEWINDOWS	equ 0x4000001F
REST_NOCHANGESTARMENU	equ 0x40000020
REST_NOFOLDEROPTIONS	equ 0x40000021
REST_HASFINDCOMPUTERS	equ 0x40000022
REST_INTELLIMENUS	equ 0x40000023
REST_RUNDLGMEMCHECKBOX	equ 0x40000024
REST_ARP_ShowPostSetup	equ 0x40000025
REST_NOCSC		equ 0x40000026
REST_NOCONTROLPANEL	equ 0x40000027
REST_ENUMWORKGROUP	equ 0x40000028
REST_ARP_NOARP		equ 0x40000029
REST_ARP_NOREMOVEPAGE	equ 0x4000002A
REST_ARP_NOADDPAGE	equ 0x4000002B
REST_ARP_NOWINSETUPPAGE equ 0x4000002C
REST_GREYMSIADS		equ 0x4000002D
REST_NOCHANGEMAPPEDDRIVELABEL equ 0x4000002E
REST_NOCHANGEMAPPEDDRIVECOMMENT equ 0x4000002F
REST_MaxRecentDocs	equ 0x40000030
REST_NONETWORKCONNECTIONS equ 0x40000031
REST_FORCESTARTMENULOGOFF equ 0x40000032
REST_NOWEBVIEW		equ 0x40000033
REST_NOCUSTOMIZETHISFOLDER equ 0x40000034
REST_NOENCRYPTION	equ 0x40000035
REST_DONTSHOWSUPERHIDDEN equ 0x40000037
REST_NOSHELLSEARCHBUTTON equ 0x40000038
REST_NOHARDWARETAB	equ 0x40000039
REST_NORUNASINSTALLPROMPT equ 0x4000003A
REST_PROMPTRUNASINSTALLNETPATH equ 0x4000003B
REST_NOMANAGEMYCOMPUTERVERB equ 0x4000003C
REST_DISALLOWRUN	equ 0x4000003E
REST_NOWELCOMESCREEN	equ 0x4000003F
REST_RESTRICTCPL	equ 0x40000040
REST_DISALLOWCPL	equ 0x40000041
REST_NOSMBALLOONTIP	equ 0x40000042
REST_NOSMHELP		equ 0x40000043
REST_NOWINKEYS		equ 0x40000044
REST_NOENCRYPTONMOVE	equ 0x40000045
REST_NOLOCALMACHINERUN	equ 0x40000046
REST_NOCURRENTUSERRUN	equ 0x40000047
REST_NOLOCALMACHINERUNONCE equ 0x40000048
REST_NOCURRENTUSERRUNONCE equ 0x40000049
REST_FORCEACTIVEDESKTOPON equ 0x4000004A
REST_NOVIEWONDRIVE	equ 0x4000004C
if (NTDDI_VERSION GT NTDDI_WINXP) or defined(IE_BACKCOMPAT_VERSION)
REST_NONETCRAWL		equ 0x4000004D
REST_NOSHAREDDOCUMENTS	equ 0x4000004E
endif
REST_NOSMMYDOCS		equ 0x4000004F
if (NTDDI_VERSION GE NTDDI_WINXP)
REST_NOSMMYPICS		equ 0x40000050
REST_ALLOWBITBUCKDRIVES equ 0x40000051
REST_NONLEGACYSHELLMODE equ 0x40000052
REST_NOCONTROLPANELBARRICADE equ 0x40000053
REST_NOSTARTPAGE	equ 0x40000054
REST_NOAUTOTRAYNOTIFY	equ 0x40000055
REST_NOTASKGROUPING	equ 0x40000056
REST_NOCDBURNING	equ 0x40000057
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP3)
REST_MYCOMPNOPROP	equ 0x40000058
REST_MYDOCSNOPROP	equ 0x40000059
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
REST_NOSTARTPANEL	equ 0x4000005A
REST_NODISPLAYAPPEARANCEPAGE equ 0x4000005B
REST_NOTHEMESTAB	equ 0x4000005C
REST_NOVISUALSTYLECHOICE equ 0x4000005D
REST_NOSIZECHOICE	equ 0x4000005E
REST_NOCOLORCHOICE	equ 0x4000005F
REST_SETVISUALSTYLE	equ 0x40000060
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP3)
REST_STARTRUNNOHOMEPATH equ 0x40000061
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
REST_NOUSERNAMEINSTARTPANEL equ 0x40000062
REST_NOMYCOMPUTERICON	equ 0x40000063
REST_NOSMNETWORKPLACES	equ 0x40000064
REST_NOSMPINNEDLIST	equ 0x40000065
REST_NOSMMYMUSIC	equ 0x40000066
REST_NOSMEJECTPC	equ 0x40000067
REST_NOSMMOREPROGRAMS	equ 0x40000068
REST_NOSMMFUPROGRAMS	equ 0x40000069
REST_NOTRAYITEMSDISPLAY equ 0x4000006A
REST_NOTOOLBARSONTASKBAR equ 0x4000006B
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP3)
REST_NOSMCONFIGUREPROGRAMS equ 0x4000006F
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
REST_HIDECLOCK		equ 0x40000070
REST_NOLOWDISKSPACECHECKS equ 0x40000071
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP4)
REST_NOENTIRENETWORK	equ 0x40000072
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
REST_NODESKTOPCLEANUP	equ 0x40000073
REST_BITBUCKNUKEONDELETE equ 0x40000074
REST_BITBUCKCONFIRMDELETE equ 0x40000075
REST_BITBUCKNOPROP	equ 0x40000076
REST_NODISPBACKGROUND	equ 0x40000077
REST_NODISPSCREENSAVEPG equ 0x40000078
REST_NODISPSETTINGSPG	equ 0x40000079
REST_NODISPSCREENSAVEPREVIEW equ 0x4000007A
REST_NODISPLAYCPL	equ 0x4000007B
REST_HIDERUNASVERB	equ 0x4000007C
REST_NOTHUMBNAILCACHE	equ 0x4000007D
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP1) OR defined(IE_BACKCOMPAT_VERSION)
REST_NOSTRCMPLOGICAL	equ 0x4000007E
REST_NOPUBLISHWIZARD	equ 0x4000007F
REST_NOONLINEPRINTSWIZARD equ 0x40000080
REST_NOWEBSERVICES	equ 0x40000081
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP3)
REST_ALLOWUNHASHEDWEBVIEW equ 0x40000082
endif
REST_ALLOWLEGACYWEBVIEW equ 0x40000083
if (NTDDI_VERSION GE NTDDI_WIN2KSP3)
REST_REVERTWEBVIEWSECURITY equ 0x40000084
endif
if (NTDDI_VERSION GE NTDDI_WIN2KSP4)
REST_INHERITCONSOLEHANDLES equ 0x40000086
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP2 AND NTDDI_VERSION LT NTDDI_VISTA)
REST_SORTMAXITEMCOUNT	equ 0x40000087
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
REST_NOREMOTERECURSIVEEVENTS equ 0x40000089
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
REST_NOREMOTECHANGENOTIFY equ 0x40000091
if (NTDDI_VERSION LT NTDDI_VISTA)
REST_NOSIMPLENETIDLIST	equ 0x40000092
endif
REST_NOENUMENTIRENETWORK equ 0x40000093
if (NTDDI_VERSION LT NTDDI_VISTA)
REST_NODETAILSTHUMBNAILONNETWORK equ 0x40000094
endif
REST_NOINTERNETOPENWITH equ 0x40000095
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
REST_DONTRETRYBADNETNAME equ 0x4000009B
REST_ALLOWFILECLSIDJUNCTIONS equ 0x4000009C
REST_NOUPNPINSTALL	equ 0x4000009D
endif
REST_ARP_DONTGROUPPATCHES equ 0x400000AC
REST_ARP_NOCHOOSEPROGRAMSPAGE equ 0x400000AD
REST_NODISCONNECT	equ 0x41000001
REST_NOSECURITY		equ 0x41000002
REST_NOFILEASSOCIATE	equ 0x41000003
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
REST_ALLOWCOMMENTTOGGLE equ 0x41000004
if (NTDDI_VERSION LT NTDDI_VISTA)
REST_USEDESKTOPINICACHE equ 0x41000005
endif
endif

;SHSTDAPI_(IStream
OpenRegStream proto WINAPI \
		  hkey: HKEY,
	     pszSubkey: LPCWSTR,
	      pszValue: LPCWSTR,
	       grfMode: DWORD

;SHSTDAPI
SHFindFiles proto WINAPI \
	    pidlFolder: PCIDLIST_ABSOLUTE,
	  pidlSaveFile: PCIDLIST_ABSOLUTE

;SHSTDAPI
PathGetShortPath proto WINAPI \
	   pszLongPath: LPWSTR


;SHSTDAPI
PathYetAnotherMakeUniqueName proto WINAPI \
	 pszUniqueName: LPWSTR,
	       pszPath: LPCWSTR,
	      pszShort: LPCWSTR,
	   pszFileSpec: LPCWSTR

;SHSTDAPI
Win32DeleteFile proto WINAPI \
	       pszPath: LPCWSTR

if (NTDDI_VERSION LT NTDDI_VISTA)
PPCF_ADDQUOTES		equ 0x00000001
PPCF_ADDARGUMENTS	equ 0x00000003
PPCF_NODIRECTORIES	equ 0x00000010
PPCF_FORCEQUALIFY	equ 0x00000040
PPCF_LONGESTPOSSIBLE	equ 0x00000080

;SHSTDAPI
PathProcessCommand proto WINAPI \
		 lpSrc: LPCWSTR,
		lpDest: LPWSTR,
		  iMax: SINT,
	       dwFlags: DWORD

endif
;SHSTDAPI
SHRestricted proto WINAPI \
		  rest: RESTRICTIONS

;SHSTDAPI
SignalFileOpen proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE


if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
AssocGetDetailsOfPropKey proto WINAPI \
		   psf: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
		  pkey: ptr PROPERTYKEY,
		    pv: ptr VARIANT,
	pfFoundPropKey: ptr BOOL

endif

if (NTDDI_VERSION LT NTDDI_VISTA)
;SHSTDAPI
SHLoadOLE proto WINAPI \
		lParam: LPARAM

endif

;SHSTDAPI
SHStartNetConnectionDialogA proto WINAPI \
		  hwnd: HWND,
	 pszRemoteName: LPCSTR,
		dwType: DWORD

;SHSTDAPI
SHStartNetConnectionDialogW proto WINAPI \
		  hwnd: HWND,
	 pszRemoteName: LPCWSTR,
		dwType: DWORD

ifdef _UNICODE
SHStartNetConnectionDialog equ <SHStartNetConnectionDialogW>
else
SHStartNetConnectionDialog equ <SHStartNetConnectionDialogA>
endif
;SHSTDAPI
SHDefExtractIconA proto WINAPI \
	   pszIconFile: LPCSTR,
		iIndex: SINT,
		uFlags: UINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
	     nIconSize: UINT

;SHSTDAPI
SHDefExtractIconW proto WINAPI \
	   pszIconFile: LPCWSTR,
		iIndex: SINT,
		uFlags: UINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
	     nIconSize: UINT

ifdef _UNICODE
SHDefExtractIcon	equ <SHDefExtractIconW>
else
SHDefExtractIcon	equ <SHDefExtractIconA>
endif


tagOPEN_AS_INFO_FLAGS	typedef SDWORD
OAIF_ALLOW_REGISTRATION equ 0x00000001
OAIF_REGISTER_EXT	equ 0x00000002
OAIF_EXEC		equ 0x00000004
OAIF_FORCE_REGISTRATION equ 0x00000008
if (NTDDI_VERSION GT NTDDI_VISTA)
OAIF_HIDE_REGISTRATION	equ 0x00000020
OAIF_URL_PROTOCOL	equ 0x00000040
endif
OPEN_AS_INFO_FLAGS	typedef SINT

.pragma pack(push, 8)

OPENASINFO		STRUC
pcszFile		LPCWSTR ?
pcszClass		LPCWSTR ?
oaifInFlags		OPEN_AS_INFO_FLAGS ?
OPENASINFO		ENDS
POPENASINFO		typedef ptr OPENASINFO

.pragma pack(pop)

if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHOpenWithDialog proto WINAPI \
	    hwndParent: HWND,
	       poainfo: ptr OPENASINFO

endif

;SHSTDAPI
Shell_GetImageLists proto WINAPI \
		 phiml: ptr HIMAGELIST,
	    phimlSmall: ptr HIMAGELIST
if 0
;SHSTDAPI
Shell_GetCachedImageIndex proto WINAPI \
	  pwszIconPath: LPCWSTR,
	    iIconIndex: SINT,
	    uIconFlags: UINT
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
Shell_GetCachedImageIndexA proto WINAPI \
	   pszIconPath: LPCSTR,
	    iIconIndex: SINT,
	    uIconFlags: UINT

;SHSTDAPI
Shell_GetCachedImageIndexW proto WINAPI \
	   pszIconPath: LPCWSTR,
	    iIconIndex: SINT,
	    uIconFlags: UINT
ifdef _UNICODE
Shell_GetCachedImageIndex equ <Shell_GetCachedImageIndexW>
else
Shell_GetCachedImageIndex equ <Shell_GetCachedImageIndexA>
endif
endif

.comdef IDocViewSite
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnSetTitle		proc :ptr
    .ends

VALIDATEUNC_CONNECT	equ 0x0001
VALIDATEUNC_NOUI	equ 0x0002
VALIDATEUNC_PRINT	equ 0x0004
if (NTDDI_VERSION GE NTDDI_VISTA)
VALIDATEUNC_PERSIST	equ 0x0008
VALIDATEUNC_VALID	equ 0x000F
else
VALIDATEUNC_VALID	equ 0x0007
endif

;SHSTDAPI
SHValidateUNC proto WINAPI \
	     hwndOwner: HWND,
	       pszFile: LPWSTR,
	      fConnect: UINT

OPENPROPS_NONE		equ 0x0000
OPENPROPS_INHIBITPIF	equ 0x8000
GETPROPS_NONE		equ 0x0000
SETPROPS_NONE		equ 0x0000
CLOSEPROPS_NONE		equ 0x0000
CLOSEPROPS_DISCARD	equ 0x0001

PIFNAMESIZE		equ 30
PIFSTARTLOCSIZE		equ 63
PIFDEFPATHSIZE		equ 64
PIFPARAMSSIZE		equ 64
PIFSHPROGSIZE		equ 64
PIFSHDATASIZE		equ 64
PIFDEFFILESIZE		equ 80
PIFMAXFILEPATH		equ 260

PROPPRG			STRUC
flPrg			dw ?
flPrgInit		dw ?
achTitle		CHAR PIFNAMESIZE dup(?)
achCmdLine		CHAR PIFSTARTLOCSIZE+PIFPARAMSSIZE+1 dup(?)
achWorkDir		CHAR PIFDEFPATHSIZE dup(?)
wHotKey			dw ?
achIconFile		CHAR PIFDEFFILESIZE dup(?)
wIconIndex		dw ?
dwEnhModeFlags		dd ?
dwRealModeFlags		dd ?
achOtherFile		CHAR PIFDEFFILESIZE dup(?)
achPIFFile		CHAR PIFMAXFILEPATH dup(?)
PROPPRG			ENDS
PPROPPRG		typedef ptr PROPPRG
LPPROPPRG		typedef ptr PROPPRG
LPCPROPPRG		typedef ptr PROPPRG

;SHSTDAPI_(HANDLE)
PifMgr_OpenProperties proto WINAPI \
		pszApp: LPCWSTR,
		pszPIF: LPCWSTR,
		  hInf: UINT,
		 flOpt: UINT

;SHSTDAPI
PifMgr_GetProperties proto WINAPI \
		hProps: HANDLE,
	      pszGroup: LPCSTR,
	       lpProps: ptr,
	       cbProps: SINT,
		 flOpt: UINT

;SHSTDAPI
PifMgr_SetProperties proto WINAPI \
		hProps: HANDLE,
	      pszGroup: LPCSTR,
	       lpProps: ptr,
	       cbProps: SINT,
		 flOpt: UINT

;SHSTDAPI_(HANDLE)
PifMgr_CloseProperties proto WINAPI \
		hProps: HANDLE,
		 flOpt: UINT


;SHSTDAPI
SHSetInstanceExplorer proto WINAPI \
		  punk: ptr IUnknown

;SHSTDAPI
IsUserAnAdmin proto WINAPI

.comdef IInitializeObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc
    .ends


BMICON_LARGE		equ 0

.comdef IBanneredBar
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetIconSize		proc :DWORD
    GetIconSize		proc :ptr
    SetBitmap		proc :HBITMAP
    GetBitmap		proc :ptr
    .ends

;SHSTDAPI_(LRESULT)
SHShellFolderView_Message proto WINAPI \
	      hwndMain: HWND,
		  uMsg: UINT,
		lParam: LPARAM


.comdef IShellFolderViewCB
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    MessageSFVCB	proc :UINT, :WPARAM, :LPARAM
    .ends
LPIShellFolderViewCB	typedef ptr IShellFolderViewCB

.pragma pack(push, 8)

QCMINFO_PLACE_BEFORE	equ 0
QCMINFO_PLACE_AFTER	equ 1
QCMINFO_IDMAP_PLACEMENT STRUC
id			UINT ?
fFlags			UINT ?
QCMINFO_IDMAP_PLACEMENT ENDS

QCMINFO_IDMAP		STRUC
nMaxIds			UINT ?
pIdList			QCMINFO_IDMAP_PLACEMENT 1 dup(<>)
QCMINFO_IDMAP		ENDS

QCMINFO			STRUC
hmenu			HMENU ?
indexMenu		UINT ?
idCmdFirst		UINT ?
idCmdLast		UINT ?
pIdMap			PVOID ? ; QCMINFO_IDMAP ?
QCMINFO			ENDS
LPQCMINFO		typedef ptr QCMINFO

TBIF_APPEND		equ 0
TBIF_PREPEND		equ 1
TBIF_REPLACE		equ 2
TBIF_DEFAULT		equ 0x00000000
TBIF_INTERNETBAR	equ 0x00010000
TBIF_STANDARDTOOLBAR	equ 0x00020000
TBIF_NOTOOLBAR		equ 0x00030000

TBINFO			STRUC
cbuttons		UINT ?
uFlags			UINT ?
TBINFO			ENDS
LPTBINFO		typedef ptr TBINFO


DETAILSINFO		STRUC
pidl			PCUITEMID_CHILD ?
fmt			SINT ?
cxChar			SINT ?
_str			STRRET <>
iImage			SINT ?
DETAILSINFO		ENDS
PDETAILSINFO		typedef ptr DETAILSINFO

SFVM_PROPPAGE_DATA	STRUC
dwReserved		dd ?
pfn			LPFNADDPROPSHEETPAGE ?
lParam			LPARAM ?
SFVM_PROPPAGE_DATA	ENDS

SFVM_HELPTOPIC_DATA	STRUC
wszHelpFile		WCHAR MAX_PATH dup(?)
wszHelpTopic		WCHAR MAX_PATH dup(?)
SFVM_HELPTOPIC_DATA	ENDS

SFVM_MERGEMENU		equ 1
SFVM_INVOKECOMMAND	equ 2
SFVM_GETHELPTEXT	equ 3
SFVM_GETTOOLTIPTEXT	equ 4
SFVM_GETBUTTONINFO	equ 5
SFVM_GETBUTTONS		equ 6
SFVM_INITMENUPOPUP	equ 7
SFVM_FSNOTIFY		equ 14
SFVM_WINDOWCREATED	equ 15
SFVM_GETDETAILSOF	equ 23
SFVM_COLUMNCLICK	equ 24
SFVM_QUERYFSNOTIFY	equ 25
SFVM_DEFITEMCOUNT	equ 26
SFVM_DEFVIEWMODE	equ 27
SFVM_UNMERGEMENU	equ 28
SFVM_UPDATESTATUSBAR	equ 31
SFVM_BACKGROUNDENUM	equ 32
SFVM_DIDDRAGDROP	equ 36
SFVM_SETISFV		equ 39
SFVM_THISIDLIST		equ 41
SFVM_ADDPROPERTYPAGES	equ 47
SFVM_BACKGROUNDENUMDONE equ 48
SFVM_GETNOTIFY		equ 49
SFVM_GETSORTDEFAULTS	equ 53
SFVM_SIZE		equ 57
SFVM_GETZONE		equ 58
SFVM_GETPANE		equ 59
SFVM_GETHELPTOPIC	equ 63
SFVM_GETANIMATION	equ 68


ITEMSPACING		STRUC
cxSmall			SINT ?
cySmall			SINT ?
cxLarge			SINT ?
cyLarge			SINT ?
ITEMSPACING		ENDS

.pragma pack(pop)

SFVSOC_INVALIDATE_ALL	equ 0x00000001
SFVSOC_NOSCROLL		equ LVSICF_NOSCROLL

SFVS_SELECT_NONE	equ 0x0
SFVS_SELECT_ALLITEMS	equ 0x1
SFVS_SELECT_INVERT	equ 0x2

.comdef IShellFolderView
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Rearrange		proc :LPARAM
    GetArrangeParam	proc :ptr
    ArrangeGrid		proc
    AutoArrange		proc
    GetAutoArrange	proc
    AddObject		proc :PUITEMID_CHILD, :ptr
    GetObject		proc :ptr, :UINT
    RemoveObject	proc :PUITEMID_CHILD, :ptr
    GetObjectCount	proc :ptr
    SetObjectCount	proc :UINT, :UINT
    UpdateObject	proc :PUITEMID_CHILD, :PUITEMID_CHILD, :ptr
    RefreshObject	proc :PUITEMID_CHILD, :ptr
    SetRedraw		proc :BOOL
    GetSelectedCount	proc :ptr
    GetSelectedObjects	proc :ptr, :ptr
    IsDropOnSource	proc :ptr
    GetDragPoint	proc :ptr
    GetDropPoint	proc :ptr
    MoveIcons		proc :ptr
    SetItemPos		proc :PCUITEMID_CHILD, :ptr
    IsBkDropTarget	proc :ptr
    SetClipboard	proc :BOOL
    SetPoints		proc :ptr
    GetItemSpacing	proc :ptr
    SetCallback		proc :ptr, :ptr
    Select		proc :UINT
    QuerySupport	proc :ptr
    SetAutomationObject proc :ptr
    .ends

LPIShellView		typedef ptr IShellView

SFV_CREATE		STRUC
cbSize			UINT ?
pshf			LPIShellFolder ?
psvOuter		LPIShellView ?
psfvcb			LPIShellFolderViewCB ?
SFV_CREATE		ENDS

;SHSTDAPI
SHCreateShellFolderView proto WINAPI \
		 pcsfv: ptr SFV_CREATE,
		  ppsv: ptr IShellView

CALLBACK(LPFNDFMCALLBACK, :ptr, :HWND, :ptr IDataObject, :UINT, :WPARAM, :LPARAM)

;SHSTDAPI
CDefFolderMenu_Create2 proto WINAPI \
	    pidlFolder: PCIDLIST_ABSOLUTE,
		  hwnd: HWND,
		  cidl: UINT,
		 apidl: PCUITEMID_CHILD_ARRAY,
		   psf: ptr IShellFolder,
		   pfn: LPFNDFMCALLBACK,
		 nKeys: UINT,
		ahkeys: ptr HKEY,
		  ppcm: ptr IContextMenu

LPHKEY			typedef ptr HKEY
LPIContextMenuCB	typedef ptr IContextMenuCB

DEFCONTEXTMENU		STRUC
hwnd			HWND ?
pcmcb			LPIContextMenuCB ?
pidlFolder		PCIDLIST_ABSOLUTE ?
psf			LPIShellFolder ?
cidl			UINT ?
apidl			PCUITEMID_CHILD_ARRAY ?
punkAssociationInfo	LPIUnknown ?
cKeys			UINT ?
aKeys			LPHKEY ?
DEFCONTEXTMENU		ENDS


if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHCreateDefaultContextMenu proto WINAPI \
		  pdcm: ptr DEFCONTEXTMENU,
		  riid: REFIID,
		   ppv: PVOID

endif


;SHSTDAPI
SHOpenPropSheetA proto WINAPI \
	    pszCaption: LPCSTR,
		ahkeys: ptr HKEY,
		cikeys: UINT,
	 pclsidDefault: ptr CLSID,
		pdtobj: ptr IDataObject,
		   psb: ptr LPIShellBrowser,
	    pStartPage: LPCSTR
SHOpenPropSheetW proto WINAPI \
	    pszCaption: LPCWSTR,
		ahkeys: ptr HKEY,
		cikeys: UINT,
	 pclsidDefault: ptr CLSID,
		pdtobj: ptr IDataObject,
		   psb: ptr LPIShellBrowser,
	    pStartPage: LPCWSTR
ifdef _UNICODE
SHOpenPropSheet		equ <SHOpenPropSheetW>
else
SHOpenPropSheet		equ <SHOpenPropSheetA>
endif

LPCMINVOKECOMMANDINFO	typedef ptr CMINVOKECOMMANDINFO

DFMICS			STRUC
cbSize			dd ?
fMask			dd ?
lParam			LPARAM ?
idCmdFirst		UINT ?
idDefMax		UINT ?
pici			LPCMINVOKECOMMANDINFO ?
if (NTDDI_VERSION GE NTDDI_VISTA)
punkSite		LPIUnknown ?
endif
DFMICS			ENDS
PDFMICS			typedef ptr DFMICS


DFM_MERGECONTEXTMENU	equ 1
DFM_INVOKECOMMAND	equ 2
DFM_GETHELPTEXT		equ 5
DFM_WM_MEASUREITEM	equ 6
DFM_WM_DRAWITEM		equ 7
DFM_WM_INITMENUPOPUP	equ 8
DFM_VALIDATECMD		equ 9
DFM_MERGECONTEXTMENU_TOP equ 10
DFM_GETHELPTEXTW	equ 11
DFM_INVOKECOMMANDEX	equ 12
DFM_MAPCOMMANDNAME	equ 13
DFM_GETDEFSTATICID	equ 14
DFM_GETVERBW		equ 15
DFM_GETVERBA		equ 16
DFM_MERGECONTEXTMENU_BOTTOM equ 17
DFM_MODIFYQCMFLAGS	equ 18

DFM_CMD_DELETE		equ (-1)
DFM_CMD_MOVE		equ (-2)
DFM_CMD_COPY		equ (-3)
DFM_CMD_LINK		equ (-4)
DFM_CMD_PROPERTIES	equ (-5)
DFM_CMD_NEWFOLDER	equ (-6)
DFM_CMD_PASTE		equ (-7)
DFM_CMD_VIEWLIST	equ (-8)
DFM_CMD_VIEWDETAILS	equ (-9)
DFM_CMD_PASTELINK	equ (-10)
DFM_CMD_PASTESPECIAL	equ (-11)
DFM_CMD_MODALPROP	equ (-12)
DFM_CMD_RENAME		equ (-13)


CALLBACK(LPFNVIEWCALLBACK, :ptr IShellView, :ptr IShellFolder, :HWND, :UINT, :WPARAM, :LPARAM)

CSFV			STRUC
cbSize			UINT ?
pshf			LPIShellFolder ?
psvOuter		LPIShellView ?
pidl			PCIDLIST_ABSOLUTE ?
lEvents			LONG ?
pfnCallback		LPFNVIEWCALLBACK ?
fvm			FOLDERVIEWMODE ?
CSFV			ENDS
LPCSFV			typedef ptr CSFV


SFVM_REARRANGE		equ 0x00000001
ShellFolderView_ReArrange macro _hwnd, _lparam
	exitm<SHShellFolderView_Message(_hwnd,SFVM_REARRANGE,_lparam)>
	endm

SFVM_ADDOBJECT		equ 0x00000003
ShellFolderView_AddObject macro _hwnd, _pidl
	exitm<SHShellFolderView_Message(_hwnd,SFVM_ADDOBJECT, _pidl)>
	endm

SFVM_REMOVEOBJECT	equ 0x00000006
ShellFolderView_RemoveObject macro _hwnd, _pidl
	exitm<SHShellFolderView_Message(_hwnd,SFVM_REMOVEOBJECT, _pidl)>
	endm


SFVM_UPDATEOBJECT	equ 0x00000007
ShellFolderView_UpdateObject macro _hwnd, _ppidl
	exitm<SHShellFolderView_Message(_hwnd,SFVM_UPDATEOBJECT, _ppidl)>
	endm

SFVM_GETSELECTEDOBJECTS equ 0x00000009
ShellFolderView_GetSelectedObjects macro _hwnd, ppidl
	exitm<SHShellFolderView_Message(_hwnd,SFVM_GETSELECTEDOBJECTS, ppidl)>
	endm

SFV_SETITEMPOS		STRUC
pidl			PCUITEMID_CHILD ?
pt			POINT <>
SFV_SETITEMPOS		ENDS
LPSFV_SETITEMPOS	typedef ptr SFV_SETITEMPOS
PCSFV_SETITEMPOS	typedef ptr SFV_SETITEMPOS

SFVM_SETITEMPOS		equ 0x0000000e
ShellFolderView_SetItemPos macro _hwnd, _pidl, _x, _y
	exitm<>
	endm
SFVM_SETCLIPBOARD	equ 0x00000010
ShellFolderView_SetClipboard macro _hwnd, _dwEffect
	exitm<SHShellFolderView_Message(_hwnd,SFVM_SETCLIPBOARD, _dwEffect)>
	endm

SFVM_SETPOINTS		equ 0x00000017
ShellFolderView_SetPoints macro _hwnd, _pdtobj
	exitm<SHShellFolderView_Message(_hwnd,SFVM_SETPOINTS, _pdtobj)>
	endm

;include poppack.inc
;SHSTDAPI_(IContextMenu
SHFind_InitMenuPopup proto WINAPI \
		 hmenu: HMENU,
	     hwndOwner: HWND,
	    idCmdFirst: UINT,
	     idCmdLast: UINT

;SHSTDAPI
SHCreateShellFolderViewEx proto WINAPI \
		 pcsfv: LPCSFV,
		  ppsv: ptr IShellView


PID_IS_URL		equ 2
PID_IS_NAME		equ 4
PID_IS_WORKINGDIR	equ 5
PID_IS_HOTKEY		equ 6
PID_IS_SHOWCMD		equ 7
PID_IS_ICONINDEX	equ 8
PID_IS_ICONFILE		equ 9
PID_IS_WHATSNEW		equ 10
PID_IS_AUTHOR		equ 11
PID_IS_DESCRIPTION	equ 12
PID_IS_COMMENT		equ 13


PID_INTSITE_WHATSNEW	equ 2
PID_INTSITE_AUTHOR	equ 3
PID_INTSITE_LASTVISIT	equ 4
PID_INTSITE_LASTMOD	equ 5
PID_INTSITE_VISITCOUNT	equ 6
PID_INTSITE_DESCRIPTION equ 7
PID_INTSITE_COMMENT	equ 8
PID_INTSITE_FLAGS	equ 9
PID_INTSITE_CONTENTLEN	equ 10
PID_INTSITE_CONTENTCODE equ 11
PID_INTSITE_RECURSE	equ 12
PID_INTSITE_WATCH	equ 13
PID_INTSITE_SUBSCRIPTION equ 14
PID_INTSITE_URL		equ 15
PID_INTSITE_TITLE	equ 16
PID_INTSITE_CODEPAGE	equ 18
PID_INTSITE_TRACKING	equ 19
PID_INTSITE_ICONINDEX	equ 20
PID_INTSITE_ICONFILE	equ 21

PIDISF_RECENTLYCHANGED	equ 0x00000001
PIDISF_CACHEDSTICKY	equ 0x00000002
PIDISF_CACHEIMAGES	equ 0x00000010
PIDISF_FOLLOWALLLINKS	equ 0x00000020


PIDISM_GLOBAL		equ 0
PIDISM_WATCH		equ 1
PIDISM_DONTWATCH	equ 2

SHELLSTATEA		STRUC
Flags			UINT ?
dwWin95Unused		dd ?
uWin95Unused		UINT ?
lParamSort		LONG ?
iSortDirection		SINT ?
version			UINT ?
uNotUsed		UINT ?
Flags2			UINT ?
SHELLSTATEA		ENDS
LPSHELLSTATEA		typedef ptr SHELLSTATEA

SHELLSTATEW		STRUC
Flags			UINT ?
dwWin95Unused		dd ?
uWin95Unused		UINT ?
lParamSort		LONG ?
iSortDirection		SINT ?
version			UINT ?
uNotUsed		UINT ?
Flags2			UINT ?
SHELLSTATEW		ENDS
LPSHELLSTATEW		typedef ptr SHELLSTATEW

SHELLSTATEVERSION_IE4	equ 9
SHELLSTATEVERSION_WIN2K equ 10

ifdef _UNICODE
SHELLSTATE		equ <SHELLSTATEW>
LPSHELLSTATE		equ <LPSHELLSTATEW>
else
SHELLSTATE		equ <SHELLSTATEA>
LPSHELLSTATE		equ <LPSHELLSTATEA>
endif

SHELLSTATE_SIZE_WIN95	equ FIELD_OFFSET(SHELLSTATE,lParamSort)
SHELLSTATE_SIZE_NT4	equ FIELD_OFFSET(SHELLSTATE,version)
SHELLSTATE_SIZE_IE4	equ FIELD_OFFSET(SHELLSTATE,uNotUsed)
SHELLSTATE_SIZE_WIN2K	equ sizeof(SHELLSTATE)

;SHSTDAPI
SHGetSetSettings proto WINAPI \
		  lpss: ptr SHELLSTATE,
		dwMask: DWORD,
		  bSet: BOOL


SHELLFLAGSTATE		STRUC
Flags			UINT ?
SHELLFLAGSTATE		ENDS
LPSHELLFLAGSTATE	typedef ptr SHELLFLAGSTATE

SSF_SHOWALLOBJECTS	equ 0x00000001
SSF_SHOWEXTENSIONS	equ 0x00000002
SSF_HIDDENFILEEXTS	equ 0x00000004
SSF_SERVERADMINUI	equ 0x00000004
SSF_SHOWCOMPCOLOR	equ 0x00000008
SSF_SORTCOLUMNS		equ 0x00000010
SSF_SHOWSYSFILES	equ 0x00000020
SSF_DOUBLECLICKINWEBVIEW equ 0x00000080
SSF_SHOWATTRIBCOL	equ 0x00000100
SSF_DESKTOPHTML		equ 0x00000200
SSF_WIN95CLASSIC	equ 0x00000400
SSF_DONTPRETTYPATH	equ 0x00000800
SSF_SHOWINFOTIP		equ 0x00002000
SSF_MAPNETDRVBUTTON	equ 0x00001000
SSF_NOCONFIRMRECYCLE	equ 0x00008000
SSF_HIDEICONS		equ 0x00004000
SSF_FILTER		equ 0x00010000
SSF_WEBVIEW		equ 0x00020000
SSF_SHOWSUPERHIDDEN	equ 0x00040000
SSF_SEPPROCESS		equ 0x00080000
if (NTDDI_VERSION GE NTDDI_WINXP)
SSF_NONETCRAWLING	equ 0x00100000
SSF_STARTPANELON	equ 0x00200000
SSF_SHOWSTARTPAGE	equ 0x00400000
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
SSF_AUTOCHECKSELECT	equ 0x00800000
SSF_ICONSONLY		equ 0x01000000
SSF_SHOWTYPEOVERLAY	equ 0x02000000
endif

;SHSTDAPI
SHGetSettings proto WINAPI \
		  psfs: ptr SHELLFLAGSTATE,
		dwMask: DWORD


;SHSTDAPI
SHBindToParent proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
		  riid: REFIID,
		   ppv: PVOID,
	     ppidlLast: ptr PCUITEMID_CHILD


if (NTDDI_VERSION GE NTDDI_VISTA)

;SHSTDAPI
SHBindToFolderIDListParent proto WINAPI \
	       psfRoot: ptr IShellFolder,
		  pidl: PCUIDLIST_RELATIVE,
		  riid: REFIID,
		   ppv: PVOID,
	     ppidlLast: ptr PCUITEMID_CHILD


;SHSTDAPI
SHBindToFolderIDListParentEx proto WINAPI \
	       psfRoot: ptr IShellFolder,
		  pidl: PCUIDLIST_RELATIVE,
		  ppbc: ptr IBindCtx,
		  riid: REFIID,
		   ppv: ptr,
	     ppidlLast: ptr PCUITEMID_CHILD


;SHSTDAPI
SHBindToObject proto WINAPI \
		   psf: ptr IShellFolder,
		  pidl: PCUIDLIST_RELATIVE,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
		    pp: ptr

endif

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHParseDisplayName proto WINAPI \
	       pszName: PCWSTR,
		   pbc: ptr IBindCtx,
		 ppidl: ptr PIDLIST_ABSOLUTE,
	       sfgaoIn: SFGAOF,
	     psfgaoOut: ptr SFGAOF

endif

SHPPFW_NONE		equ 0x00000000
SHPPFW_DEFAULT		equ SHPPFW_DIRCREATE
SHPPFW_DIRCREATE	equ 0x00000001
SHPPFW_ASKDIRCREATE	equ 0x00000002
SHPPFW_IGNOREFILENAME	equ 0x00000004
SHPPFW_NOWRITECHECK	equ 0x00000008
if (NTDDI_VERSION GE NTDDI_WINXP)
SHPPFW_MEDIACHECKONLY	equ 0x00000010
endif

;SHSTDAPI
SHPathPrepareForWriteA proto WINAPI \
		  hwnd: HWND,
     punkEnableModless: ptr IUnknown,
	       pszPath: LPCSTR,
	       dwFlags: DWORD

;SHSTDAPI
SHPathPrepareForWriteW proto WINAPI \
		  hwnd: HWND,
     punkEnableModless: ptr IUnknown,
	       pszPath: LPCWSTR,
	       dwFlags: DWORD

ifdef _UNICODE
SHPathPrepareForWrite	equ <SHPathPrepareForWriteW>
else
SHPathPrepareForWrite	equ <SHPathPrepareForWriteA>
endif

.comdef INamedPropertyBag
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ReadPropertyNPB	proc :LPCWSTR, :LPCWSTR, :ptr
    WritePropertyNPB	proc :LPCWSTR, :LPCWSTR, :ptr
    RemovePropertyNPB	proc :LPCWSTR, :LPCWSTR
    .ends

ifdef __urlmon_h__

;SHDOCAPI
SoftwareUpdateMessageBox proto WINAPI \
		  hWnd: HWND,
	   pszDistUnit: LPCWSTR,
	       dwFlags: DWORD,
		  psdi: LPSOFTDISTINFO

endif

;SHSTDAPI
SHPropStgCreate proto WINAPI \
		 psstg: ptr IPropertySetStorage,
		 fmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	       grfMode: DWORD,
	 dwDisposition: DWORD,
		 ppstg: ptr IPropertyStorage,
	    puCodePage: ptr UINT
;SHSTDAPI
SHPropStgReadMultiple proto WINAPI \
		   pps: ptr IPropertyStorage,
	     uCodePage: UINT,
		cpspec: ULONG,
	       rgpspec: ptr PROPSPEC,
		 rgvar: ptr PROPVARIANT

;SHSTDAPI
SHPropStgWriteMultiple proto WINAPI \
		   pps: ptr IPropertyStorage,
	    puCodePage: ptr UINT,
		cpspec: ULONG,
	       rgpspec: ptr PROPSPEC,
		 rgvar: ptr PROPVARIANT,
       propidNameFirst: PROPID


if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHCreateFileExtractIconA proto WINAPI \
	       pszFile: LPCSTR,
      dwFileAttributes: DWORD,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHCreateFileExtractIconW proto WINAPI \
	       pszFile: LPCWSTR,
      dwFileAttributes: DWORD,
		  riid: REFIID,
		   ppv: PVOID

ifdef _UNICODE
SHCreateFileExtractIcon equ <SHCreateFileExtractIconW>
else
SHCreateFileExtractIcon equ <SHCreateFileExtractIconA>
endif
;include pshpack8.inc
;include poppack.inc
;SHSTDAPI
SHLimitInputEdit proto WINAPI \
	      hwndEdit: HWND,
		   psf: ptr IShellFolder

;STDAPI
SHGetAttributesFromDataObject proto WINAPI \
		   pdo: ptr IDataObject,
       dwAttributeMask: DWORD,
	 pdwAttributes: ptr DWORD,
	       pcItems: ptr UINT

endif

if (NTDDI_VERSION GE NTDDI_WIN2K)

;SHSTDAPI
SHMultiFileProperties proto WINAPI \
		pdtobj: ptr IDataObject,
	       dwFlags: DWORD


endif

;SHSTDAPI
SHMapPIDLToSystemImageListIndex proto WINAPI \
		  pshf: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
	    piIndexSel: ptr SINT


;SHSTDAPI
SHCLSIDFromString proto WINAPI \
		   psz: LPCWSTR,
		pclsid: ptr CLSID

;SHSTDAPI
SHCreateQueryCancelAutoPlayMoniker proto WINAPI \
	     ppmoniker: IMoniker

;STDAPI
PerUserInit proto WINAPI

;SHSTDAPI
SHRunControlPanel proto WINAPI \
	  lpcszCmdLine: LPCWSTR,
	 hwndMsgParent: HWND


;SHSTDAPI
PickIconDlg proto WINAPI \
		  hwnd: HWND,
	   pszIconPath: LPWSTR,
	   cchIconPath: UINT,
	   piIconIndex: ptr SINT


.pragma pack(push, 8)

AASHELLMENUFILENAME	STRUC
cbTotal			SWORD ?
rgbReserved		db 12 dup(?)
szFileName		WCHAR 1 dup(?)
AASHELLMENUFILENAME	ENDS
LPAASHELLMENUFILENAME	typedef ptr AASHELLMENUFILENAME

AASHELLMENUITEM		STRUC 8
lpReserved1		PVOID ?
iReserved		SINT ?
uiReserved		UINT ?
lpName			LPAASHELLMENUFILENAME ?
psz			LPWSTR ?
AASHELLMENUITEM		ENDS
LPAASHELLMENUITEM	typedef ptr AASHELLMENUITEM

.pragma pack(pop)


if (NTDDI_VERSION GE NTDDI_WIN7)
;STDAPI
StgMakeUniqueName proto WINAPI \
	    pstgParent: ptr IStorage,
	   pszFileSpec: PCWSTR,
	       grfMode: DWORD,
		  riid: REFIID,
		   ppv: PVOID

endif

if (_WIN32_IE GE _WIN32_IE_IE70)
tagIESHORTCUTFLAGS	typedef SDWORD
IESHORTCUT_NEWBROWSER	equ 0x01
IESHORTCUT_OPENNEWTAB	equ 0x02
IESHORTCUT_FORCENAVIGATE equ 0x04
IESHORTCUT_BACKGROUNDTAB equ 0x08
endif

if (_WIN32_IE GE _WIN32_IE_XP)

;SHDOCAPI
ImportPrivacySettings proto WINAPI \
	   pszFilename: LPCWSTR,
pfParsePrivacyPreferences: ptr BOOL,
   pfParsePerSiteRules: ptr BOOL

;SHDOCAPI
DoPrivacyDlg proto WINAPI \
	     hwndOwner: HWND,
		pszUrl: LPCWSTR,
	  pPrivacyEnum: ptr IEnumPrivacyRecords,
       fReportAllSites: BOOL

endif

;.pragma pack(pop)
.pragma list(pop)
endif
