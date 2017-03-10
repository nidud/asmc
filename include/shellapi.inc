ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; SHELL.DLL functions, types, and definitions
;;
ifndef _INC_SHELLAPI
_INC_SHELLAPI equ 1
;;
;; Define API decoration for direct importing of DLL references.
;;
ifdef __PE__
option	dllimport:<shell32>
endif

;#include <pshpack1.h>

HDROP	typedef HANDLE
HKEY	typedef HANDLE

;UINT
DragQueryFileA proto _CType \
		      : HDROP,
		      : UINT,
		      : LPSTR,
		      : UINT
;UINT
DragQueryFileW proto _CType \
		      : HDROP,
		      : UINT,
		      : LPWSTR,
		      : UINT
ifdef _UNICODE
DragQueryFile		equ <DragQueryFileW>
else
DragQueryFile		equ <DragQueryFileA>
endif ;; NOT UNICODE
;BOOL
DragQueryPoint proto _CType \
		      : HDROP,
		      : LPPOINT
;VOID
DragFinish proto _CType \
		      : HDROP
;VOID
DragAcceptFiles proto _CType \
		      : HWND,
		      : BOOL

;HINSTANCE
ShellExecuteA proto _CType \
		  hwnd: HWND,
	   lpOperation: LPCSTR,
		lpFile: LPCSTR,
	  lpParameters: LPCSTR,
	   lpDirectory: LPCSTR,
	      nShowCmd: SINT
;HINSTANCE
ShellExecuteW proto _CType \
		  hwnd: HWND,
	   lpOperation: LPCWSTR,
		lpFile: LPCWSTR,
	  lpParameters: LPCWSTR,
	   lpDirectory: LPCWSTR,
	      nShowCmd: SINT
ifdef _UNICODE
ShellExecute		equ <ShellExecuteW>
else
ShellExecute		equ <ShellExecuteA>
endif ;; NOT UNICODE
;HINSTANCE
FindExecutableA proto _CType \
		lpFile: LPCSTR,
	   lpDirectory: LPCSTR,
	      lpResult: LPSTR
;HINSTANCE
FindExecutableW proto _CType \
		lpFile: LPCWSTR,
	   lpDirectory: LPCWSTR,
	      lpResult: LPWSTR
ifdef _UNICODE
FindExecutable		equ <FindExecutableW>
else
FindExecutable		equ <FindExecutableA>
endif ;; NOT UNICODE
;LPWSTR
CommandLineToArgvW proto _CType \
	     lpCmdLine: LPCWSTR,
	      pNumArgs: ptr SINT

;INT
ShellAboutA proto _CType \
		  hWnd: HWND,
		 szApp: LPCSTR,
	  szOtherStuff: LPCSTR,
		 hIcon: HICON
;INT
ShellAboutW proto _CType \
		  hWnd: HWND,
		 szApp: LPCWSTR,
	  szOtherStuff: LPCWSTR,
		 hIcon: HICON
ifdef _UNICODE
ShellAbout		equ <ShellAboutW>
else
ShellAbout		equ <ShellAboutA>
endif ;; NOT UNICODE
;HICON
DuplicateIcon proto _CType \
		 hInst: HINSTANCE,
		 hIcon: HICON
;HICON
ExtractAssociatedIconA proto _CType \
		 hInst: HINSTANCE,
	    lpIconPath: LPSTR,
	       lpiIcon: LPWORD
;HICON
ExtractAssociatedIconW proto _CType \
		 hInst: HINSTANCE,
	    lpIconPath: LPWSTR,
	       lpiIcon: LPWORD
ifdef _UNICODE
ExtractAssociatedIcon	equ <ExtractAssociatedIconW>
else
ExtractAssociatedIcon	equ <ExtractAssociatedIconA>
endif ;; NOT UNICODE

;HICON
ExtractIconA proto _CType \
		 hInst: HINSTANCE,
       lpszExeFileName: LPCSTR,
	    nIconIndex: UINT
;HICON
ExtractIconW proto _CType \
		 hInst: HINSTANCE,
       lpszExeFileName: LPCWSTR,
	    nIconIndex: UINT
ifdef _UNICODE
ExtractIcon		equ <ExtractIconW>
else
ExtractIcon		equ <ExtractIconA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
DRAGINFOA		STRUC 1
uSize			UINT ?	;; init with sizeof(DRAGINFO)
pt			POINT <>
fNC			BOOL ?
lpFileList		LPSTR ?
grfKeyState		dd ?
DRAGINFOA		ENDS
LPDRAGINFOA		typedef ptr DRAGINFOA
DRAGINFOW		STRUC 1
uSize			UINT ?	;; init with sizeof(DRAGINFO)
pt			POINT <>
fNC			BOOL ?
lpFileList		LPWSTR ?
grfKeyState		dd ?
DRAGINFOW		ENDS
LPDRAGINFOW		typedef ptr DRAGINFOW
ifdef _UNICODE
DRAGINFO		typedef DRAGINFOW
LPDRAGINFO		typedef LPDRAGINFOW
else
DRAGINFO		typedef DRAGINFOA
LPDRAGINFO		typedef LPDRAGINFOA
endif ;; UNICODE


;;//
;;// AppBar stuff
;;//
ABM_NEW			equ 0x00000000
ABM_REMOVE		equ 0x00000001
ABM_QUERYPOS		equ 0x00000002
ABM_SETPOS		equ 0x00000003
ABM_GETSTATE		equ 0x00000004
ABM_GETTASKBARPOS	equ 0x00000005
ABM_ACTIVATE		equ 0x00000006	;; lParam EQ TRUE/FASE means activate/deactivate
ABM_GETAUTOHIDEBAR	equ 0x00000007
ABM_SETAUTOHIDEBAR	equ 0x00000008	;; this can fail at any time.  MUST check the result
;;lParam = TRUE/FALSE	Set/Unset
;;uEdge = what edge
ABM_WINDOWPOSCHANGED	equ 0x0000009


;; these are put in the wparam of callback messages
ABN_STATECHANGE		equ 0x0000000
ABN_POSCHANGED		equ 0x0000001
ABN_FULLSCREENAPP	equ 0x0000002
ABN_WINDOWARRANGE	equ 0x0000003 ;; lParam EQ TRUE means hide

;; flags for get state
ABS_AUTOHIDE		equ 0x0000001
ABS_ALWAYSONTOP		equ 0x0000002

ABE_LEFT		equ 0
ABE_TOP			equ 1
ABE_RIGHT		equ 2
ABE_BOTTOM		equ 3

APPBARDATA		STRUC 1
cbSize			dd ?
hWnd			HWND ?
uCallbackMessage	UINT ?
uEdge			UINT ?
rc			RECT <>
lParam			LPARAM ?	;; message specific
APPBARDATA		ENDS
PAPPBARDATA		typedef ptr APPBARDATA

;UINT
SHAppBarMessage proto _CType \
	     dwMessage: DWORD,
		 pData: PAPPBARDATA

;;//
;;//  EndAppBar
;;//


;DWORD
DoEnvironmentSubstA proto _CType \
	      szString: LPSTR,
	      cbString: UINT
;DWORD
DoEnvironmentSubstW proto _CType \
	      szString: LPWSTR,
	      cbString: UINT
ifdef _UNICODE
DoEnvironmentSubst	equ <DoEnvironmentSubstW>
else
DoEnvironmentSubst	equ <DoEnvironmentSubstA>
endif ;; NOT UNICODE
;LPSTR
FindEnvironmentStringA proto _CType \
	      szEnvVar: LPSTR
;LPWSTR
FindEnvironmentStringW proto _CType \
	      szEnvVar: LPWSTR
ifdef _UNICODE
FindEnvironmentString	equ <FindEnvironmentStringW>
else
FindEnvironmentString	equ <FindEnvironmentStringA>
endif ;; NOT UNICODE

EIRESID macro x
	exitm<x * -1>
	endm
;UINT
ExtractIconExA proto _CType \
	      lpszFile: LPCSTR,
	    nIconIndex: SINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
		nIcons: UINT
;UINT
ExtractIconExW proto _CType \
	      lpszFile: LPCWSTR,
	    nIconIndex: SINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
		nIcons: UINT
ifdef _UNICODE
ExtractIconEx		equ <ExtractIconExW>
else
ExtractIconEx		equ <ExtractIconExA>
endif ;; NOT UNICODE



;;//
;;// Shell File Operations
;;//

ifndef FO_MOVE ;;these need to be kept in sync with the ones in shlobj.h

FO_MOVE			equ 0x0001
FO_COPY			equ 0x0002
FO_DELETE		equ 0x0003
FO_RENAME		equ 0x0004

FOF_MULTIDESTFILES	equ 0x0001
FOF_CONFIRMMOUSE	equ 0x0002
FOF_SILENT		equ 0x0004  ;; don't create progress/report
FOF_RENAMEONCOLLISION	equ 0x0008
FOF_NOCONFIRMATION	equ 0x0010  ;; Don't prompt the user.
FOF_WANTMAPPINGHANDLE	equ 0x0020  ;; Fill in SHFILEOPSTRUCT.hNameMappings
				    ;; Must be freed using SHFreeNameMappings
FOF_ALLOWUNDO		equ 0x0040
FOF_FILESONLY		equ 0x0080  ;; on *.*, do only files
FOF_SIMPLEPROGRESS	equ 0x0100  ;; means don't show names of files
FOF_NOCONFIRMMKDIR	equ 0x0200  ;; don't confirm making any needed dirs
FOF_NOERRORUI		equ 0x0400  ;; don't put up error UI
FOF_NOCOPYSECURITYATTRIBS equ 0x0800  ;; dont copy NT file Security Attributes

FILEOP_FLAGS		typedef WORD

PO_DELETE		equ 0x0013	;; printer is being deleted
PO_RENAME		equ 0x0014	;; printer is being renamed
PO_PORTCHANGE		equ 0x0020	;; port this printer connected to is being changed
;; if this id is set, the strings received by
;; the copyhook are a doubly-null terminated
;; list of strings.  The first is the printer
;; name and the second is the printer port.
PO_REN_PORT		equ 0x0034	;; PO_RENAME and PO_PORTCHANGE at same time.

;; no POF_ flags currently defined

PRINTEROP_FLAGS		typedef WORD

endif ;; FO_MOVE

;; implicit parameters are:
;;	if pFrom or pTo are unqualified names the current directories are
;;	taken from the global current drive/directory settings managed
;;	by Get/SetCurrentDrive/Directory
;;
;;	the global confirmation settings

SHFILEOPSTRUCTA		STRUC 1
hwnd			HWND ?
wFunc			UINT ?
pFrom			LPCSTR ?
pTo			LPCSTR ?
fFlags			FILEOP_FLAGS ?
fAnyOperationsAborted	BOOL ?
hNameMappings		LPVOID ?
lpszProgressTitle	LPCSTR ?	;; only used if FOF_SIMPLEPROGRESS
SHFILEOPSTRUCTA		ENDS
LPSHFILEOPSTRUCTA	typedef ptr SHFILEOPSTRUCTA
SHFILEOPSTRUCTW		STRUC 1
hwnd			HWND ?
wFunc			UINT ?
pFrom			LPCWSTR ?
pTo			LPCWSTR ?
fFlags			FILEOP_FLAGS ?
fAnyOperationsAborted	BOOL ?
hNameMappings		LPVOID ?
lpszProgressTitle	LPCWSTR ?	;; only used if FOF_SIMPLEPROGRESS
SHFILEOPSTRUCTW		ENDS
LPSHFILEOPSTRUCTW	typedef ptr SHFILEOPSTRUCTW
ifdef _UNICODE
SHFILEOPSTRUCT		typedef SHFILEOPSTRUCTW
LPSHFILEOPSTRUCT	typedef LPSHFILEOPSTRUCTW
else
SHFILEOPSTRUCT		typedef SHFILEOPSTRUCTA
LPSHFILEOPSTRUCT	typedef LPSHFILEOPSTRUCTA
endif ;; UNICODE

;int
SHFileOperationA proto _CType \
	      lpFileOp: LPSHFILEOPSTRUCTA
;int
SHFileOperationW proto _CType \
	      lpFileOp: LPSHFILEOPSTRUCTW
ifdef _UNICODE
SHFileOperation		equ <SHFileOperationW>
else
SHFileOperation		equ <SHFileOperationA>
endif ;; NOT UNICODE

;void
SHFreeNameMappings proto _CType \
	 hNameMappings: HANDLE

SHNAMEMAPPINGA		STRUC 1
pszOldPath		LPSTR ?
pszNewPath		LPSTR ?
cchOldPath		SINT ?
cchNewPath		SINT ?
SHNAMEMAPPINGA		ENDS
LPSHNAMEMAPPINGA	typedef ptr SHNAMEMAPPINGA
SHNAMEMAPPINGW		STRUC
pszOldPath		LPWSTR ?
pszNewPath		LPWSTR ?
cchOldPath		SINT ?
cchNewPath		SINT ?
SHNAMEMAPPINGW		ENDS
LPSHNAMEMAPPINGW	typedef ptr SHNAMEMAPPINGW
ifdef _UNICODE
SHNAMEMAPPING		typedef SHNAMEMAPPINGW
LPSHNAMEMAPPING		typedef LPSHNAMEMAPPINGW
else
SHNAMEMAPPING		typedef SHNAMEMAPPINGA
LPSHNAMEMAPPING		typedef LPSHNAMEMAPPINGA
endif ;; UNICODE


;;//
;;// End Shell File Operations
;;//

;;//
;;//  Begin ShellExecuteEx and family
;;//


;; ShellExecute() and ShellExecuteEx() error codes

;; regular WinExec() codes
SE_ERR_FNF		equ 2	;; file not found
SE_ERR_PNF		equ 3	;; path not found
SE_ERR_ACCESSDENIED	equ 5	;; access denied
SE_ERR_OOM		equ 8	;; out of memory
SE_ERR_DLLNOTFOUND	equ 32

endif ;; WINVER GE 0x0400

;; error values for ShellExecute() beyond the regular WinExec() codes
SE_ERR_SHARE		equ 26
SE_ERR_ASSOCINCOMPLETE	equ 27
SE_ERR_DDETIMEOUT	equ 28
SE_ERR_DDEFAIL		equ 29
SE_ERR_DDEBUSY		equ 30
SE_ERR_NOASSOC		equ 31

if(WINVER GE 0x0400)

;; Note CLASSKEY overrides CLASSNAME
SEE_MASK_CLASSNAME	equ 0x00000001
SEE_MASK_CLASSKEY	equ 0x00000003
;; Note INVOKEIDLIST overrides IDLIST
SEE_MASK_IDLIST		equ 0x00000004
SEE_MASK_INVOKEIDLIST	equ 0x0000000c
SEE_MASK_ICON		equ 0x00000010
SEE_MASK_HOTKEY		equ 0x00000020
SEE_MASK_NOCLOSEPROCESS equ 0x00000040
SEE_MASK_CONNECTNETDRV	equ 0x00000080
SEE_MASK_FLAG_DDEWAIT	equ 0x00000100
SEE_MASK_DOENVSUBST	equ 0x00000200
SEE_MASK_FLAG_NO_UI	equ 0x00000400
SEE_MASK_UNICODE	equ 0x00004000
SEE_MASK_NO_CONSOLE	equ 0x00008000
SEE_MASK_ASYNCOK	equ 0x00100000
SEE_MASK_HMONITOR	equ 0x00200000

SHELLEXECUTEINFOA	STRUC 1
cbSize			dd ?
fMask			ULONG ?
hwnd			HWND ?
lpVerb			LPCSTR ?
lpFile			LPCSTR ?
lpParameters		LPCSTR ?
lpDirectory		LPCSTR ?
nShow			SINT ?
hInstApp		HINSTANCE ?
lpIDList		LPVOID ?
lpClass			LPCSTR ?
hkeyClass		HKEY ?
dwHotKey		dd ?
UNION
    hIcon		HANDLE ?
    hMonitor		HANDLE ?
ENDS
hProcess		HANDLE ?
SHELLEXECUTEINFOA	ENDS
LPSHELLEXECUTEINFOA	typedef ptr SHELLEXECUTEINFOA

;; Note CLASSKEY overrides CLASSNAME
SEE_MASK_CLASSNAME	equ 0x00000001
SEE_MASK_CLASSKEY	equ 0x00000003
;; Note INVOKEIDLIST overrides IDLIST
SEE_MASK_IDLIST		equ 0x00000004
SEE_MASK_INVOKEIDLIST	equ 0x0000000c
SEE_MASK_ICON		equ 0x00000010
SEE_MASK_HOTKEY		equ 0x00000020
SEE_MASK_NOCLOSEPROCESS equ 0x00000040
SEE_MASK_CONNECTNETDRV	equ 0x00000080
SEE_MASK_FLAG_DDEWAIT	equ 0x00000100
SEE_MASK_DOENVSUBST	equ 0x00000200
SEE_MASK_FLAG_NO_UI	equ 0x00000400
SEE_MASK_UNICODE	equ 0x00004000
SEE_MASK_NO_CONSOLE	equ 0x00008000
SEE_MASK_ASYNCOK	equ 0x00100000
SEE_MASK_HMONITOR	equ 0x00200000

SHELLEXECUTEINFOW	STRUC 1
cbSize			dd ?
fMask			ULONG ?
hwnd			HWND ?
lpVerb			LPCWSTR ?
lpFile			LPCWSTR ?
lpParameters		LPCWSTR ?
lpDirectory		LPCWSTR ?
nShow			SINT ?
hInstApp		HINSTANCE ?
lpIDList		LPVOID ?
lpClass			LPCWSTR ?
hkeyClass		HKEY ?
dwHotKey		dd ?
UNION
    hIcon		HANDLE ?
    hMonitor		HANDLE ?
ENDS
hProcess		HANDLE ?
SHELLEXECUTEINFOW	ENDS
LPSHELLEXECUTEINFOW	typedef ptr SHELLEXECUTEINFOW
ifdef _UNICODE
SHELLEXECUTEINFO	typedef SHELLEXECUTEINFOW
LPSHELLEXECUTEINFO	typedef LPSHELLEXECUTEINFOW
else
SHELLEXECUTEINFO	typedef SHELLEXECUTEINFOA
LPSHELLEXECUTEINFO	typedef LPSHELLEXECUTEINFOA
endif ;; UNICODE

;BOOL
ShellExecuteExA proto _CType \
	    lpExecInfo: LPSHELLEXECUTEINFOA
;BOOL
ShellExecuteExW proto _CType \
	    lpExecInfo: LPSHELLEXECUTEINFOW
ifdef _UNICODE
ShellExecuteEx		equ <ShellExecuteExW>
else
ShellExecuteEx		equ <ShellExecuteExA>
endif ;; NOT UNICODE
;void
WinExecErrorA proto _CType \
		  hwnd: HWND,
		 error: SINT,
	 lpstrFileName: LPCSTR,
	    lpstrTitle: LPCSTR
;void
WinExecErrorW proto _CType \
		  hwnd: HWND,
		 error: SINT,
	 lpstrFileName: LPCWSTR,
	    lpstrTitle: LPCWSTR
ifdef _UNICODE
WinExecError		equ <WinExecErrorW>
else
WinExecError		equ <WinExecErrorA>
endif ;; NOT UNICODE

;;//
;;//  End ShellExecuteEx and family
;;//

;;
;; RecycleBin
;;


;; struct for query recycle bin info
SHQUERYRBINFO		STRUC 1
cbSize			dd ?
i64Size			QWORD ?
i64NumItems		QWORD ?
SHQUERYRBINFO		ENDS
LPSHQUERYRBINFO		typedef ptr SHQUERYRBINFO


;; flags for SHEmptyRecycleBin
;;
SHERB_NOCONFIRMATION	equ 0x00000001
SHERB_NOPROGRESSUI	equ 0x00000002
SHERB_NOSOUND		equ 0x00000004

;SHSTDAPI
SHQueryRecycleBinA proto _CType \
	    pszRootPath: LPCSTR,
	 pSHQueryRBInfo: LPSHQUERYRBINFO
SHQueryRecycleBinW proto _CType \
	    pszRootPath: LPCWSTR,
	 pSHQueryRBInfo: LPSHQUERYRBINFO
ifdef _UNICODE
SHQueryRecycleBin	equ <SHQueryRecycleBinW>
else
SHQueryRecycleBin	equ <SHQueryRecycleBinA>
endif ;; NOT UNICODE
SHEmptyRecycleBinA proto _CType \
		  hwnd: HWND,
	   pszRootPath: LPCSTR,
	       dwFlags: DWORD
SHEmptyRecycleBinW proto _CType \
		  hwnd: HWND,
	   pszRootPath: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
SHEmptyRecycleBin	equ <SHEmptyRecycleBinW>
else
SHEmptyRecycleBin	equ <SHEmptyRecycleBinA>
endif ;; NOT UNICODE

;;//
;;// end of RecycleBin


;;//
;;// Tray notification definitions
;;//

NOTIFYICONDATAA		STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
uFlags			UINT ?
uCallbackMessage	UINT ?
hIcon			HICON ?
szTip			db 64 dup(?)
NOTIFYICONDATAA		ENDS
PNOTIFYICONDATAA	typedef ptr NOTIFYICONDATAA
NOTIFYICONDATAW		STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
uFlags			UINT ?
uCallbackMessage	UINT ?
hIcon			HICON ?
szTip			dw 64 dup(?)
NOTIFYICONDATAW		ENDS
PNOTIFYICONDATAW	typedef ptr NOTIFYICONDATAW
ifdef _UNICODE
NOTIFYICONDATA		typedef NOTIFYICONDATAW
PNOTIFYICONDATA		typedef PNOTIFYICONDATAW
else
NOTIFYICONDATA		typedef NOTIFYICONDATAA
PNOTIFYICONDATA		typedef PNOTIFYICONDATAA
endif ;; UNICODE


NIM_ADD			equ 0x00000000
NIM_MODIFY		equ 0x00000001
NIM_DELETE		equ 0x00000002

NIF_MESSAGE		equ 0x00000001
NIF_ICON		equ 0x00000002
NIF_TIP			equ 0x00000004

;BOOL
Shell_NotifyIconA proto _CType \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAA
;BOOL
Shell_NotifyIconW proto _CType \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAW
ifdef _UNICODE
Shell_NotifyIcon	equ <Shell_NotifyIconW>
else
Shell_NotifyIcon	equ <Shell_NotifyIconA>
endif ;; NOT UNICODE

;;//
;;// End Tray Notification Icons
;;//



;;//
;;// Begin SHGetFileInfo
;;//

;;
;; The SHGetFileInfo API provides an easy way to get attributes
;; for a file given a pathname.
;;
;;   PARAMETERS
;;
;;     pszPath		    file name to get info about
;;     dwFileAttributes	    file attribs, only used with SHGFI_USEFILEATTRIBUTES
;;     psfi		    place to return file info
;;     cbFileInfo	    size of structure
;;     uFlags		    flags
;;
;;   RETURN
;;     TRUE if things worked
;;

SHFILEINFOA		STRUC 1
hIcon			HICON ? ;; out: icon
iIcon			SINT ?	;; out: icon index
dwAttributes		dd ?	;; out: SFGAO_ flags
szDisplayName		DB MAX_PATH DUP(?) ;; out: display name (or path)
szTypeName		DB 80 DUP(?) ;; out: type name
SHFILEINFOA		ENDS

SHFILEINFOW		STRUC 1
hIcon			HICON ? ;; out: icon
iIcon			SINT ?	;; out: icon index
dwAttributes		dd ?	;; out: SFGAO_ flags
szDisplayName		DW MAX_PATH DUP(?)	;; out: display name (or path)
szTypeName		DW 80 DUP(?) ;; out: type name
SHFILEINFOW		ENDS

ifdef _UNICODE
SHFILEINFO		typedef SHFILEINFOW
else
SHFILEINFO		typedef SHFILEINFOA
endif ;; UNICODE

SHGFI_ICON		equ 0x000000100 ;; get icon
SHGFI_DISPLAYNAME	equ 0x000000200 ;; get display name
SHGFI_TYPENAME		equ 0x000000400 ;; get type name
SHGFI_ATTRIBUTES	equ 0x000000800 ;; get attributes
SHGFI_ICONLOCATION	equ 0x000001000 ;; get icon location
SHGFI_EXETYPE		equ 0x000002000 ;; return exe type
SHGFI_SYSICONINDEX	equ 0x000004000 ;; get system icon index
SHGFI_LINKOVERLAY	equ 0x000008000 ;; put a link overlay on icon
SHGFI_SELECTED		equ 0x000010000 ;; show icon in selected state
SHGFI_ATTR_SPECIFIED	equ 0x000020000 ;; get only specified attributes
SHGFI_LARGEICON		equ 0x000000000 ;; get large icon
SHGFI_SMALLICON		equ 0x000000001 ;; get small icon
SHGFI_OPENICON		equ 0x000000002 ;; get open icon
SHGFI_SHELLICONSIZE	equ 0x000000004 ;; get shell size icon
SHGFI_PIDL		equ 0x000000008 ;; pszPath is a pidl
SHGFI_USEFILEATTRIBUTES equ 0x000000010 ;; use passed dwFileAttribute


;SHSTDAPI_(DWORD)
SHGetFileInfoA proto _CType \
	       pszPath: LPCSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOA,
	    cbFileInfo: UINT,
		uFlags: UINT
;SHSTDAPI_(DWORD)
SHGetFileInfoW proto _CType \
	       pszPath: LPCWSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOW,
	    cbFileInfo: UINT,
		uFlags: UINT
ifdef _UNICODE
SHGetFileInfo		equ <SHGetFileInfoW>
else
SHGetFileInfo		equ <SHGetFileInfoA>
endif ;; NOT UNICODE
;SHSTDAPI_(BOOL)
SHGetDiskFreeSpaceA proto _CType \
	     pszVolume: LPCSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
;SHSTDAPI_(BOOL)
SHGetDiskFreeSpaceW proto _CType \
	     pszVolume: LPCWSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
ifdef _UNICODE
SHGetDiskFreeSpace	equ <SHGetDiskFreeSpaceW>
else
SHGetDiskFreeSpace	equ <SHGetDiskFreeSpaceA>
endif ;; NOT UNICODE
;SHSTDAPI_(BOOL)
SHGetNewLinkInfoA proto _CType \
	     pszLinkTo: LPCSTR,
		pszDir: LPCSTR,
	       pszName: LPSTR,
	    pfMustCopy: ptr BOOL,
		uFlags: UINT
;SHSTDAPI_(BOOL)
SHGetNewLinkInfoW proto _CType \
	     pszLinkTo: LPCWSTR,
		pszDir: LPCWSTR,
	       pszName: LPWSTR,
	    pfMustCopy: ptr BOOL,
		uFlags: UINT
ifdef _UNICODE
SHGetNewLinkInfo	equ <SHGetNewLinkInfoW>
else
SHGetNewLinkInfo	equ <SHGetNewLinkInfoA>
endif ;; NOT UNICODE

SHGNLI_PIDL		equ 0x000000001 ;; pszLinkTo is a pidl
SHGNLI_PREFIXNAME	equ 0x000000002 ;; Make name "Shortcut to xxx"
SHGNLI_NOUNIQUE		equ 0x000000004 ;; don't do the unique name generation


;;//
;;// End SHGetFileInfo
;;//

;; Printer stuff
PRINTACTION_OPEN	equ 0
PRINTACTION_PROPERTIES	equ 1
PRINTACTION_NETINSTALL	equ 2
PRINTACTION_NETINSTALLLINK equ 3
PRINTACTION_TESTPAGE	equ 4
PRINTACTION_OPENNETPRN	equ 5
ifdef WINNT
PRINTACTION_DOCUMENTDEFAULTS equ 6
PRINTACTION_SERVERPROPERTIES equ 7
endif

;SHSTDAPI_(BOOL)
SHInvokePrinterCommandA proto _CType \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCSTR,
		lpBuf2: LPCSTR,
		fModal: BOOL
;SHSTDAPI_(BOOL)
SHInvokePrinterCommandW proto _CType \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCWSTR,
		lpBuf2: LPCWSTR,
		fModal: BOOL
ifdef _UNICODE
SHInvokePrinterCommand	equ <SHInvokePrinterCommandW>
else
SHInvokePrinterCommand	equ <SHInvokePrinterCommandA>
endif ;; NOT UNICODE

endif ;; WINVER GE 0x0400
endif	;; _INC_SHELLAPI

.list
