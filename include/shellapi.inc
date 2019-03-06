ifndef __SHELLAPI_INC
__SHELLAPI_INC equ <>

ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif

ifdef __PE__
option dllimport:<shell32>
else
includelib shell32.lib
endif

ifdef _WIN64
SHELL_ALIGN	equ <QWORD>
else
SHELL_ALIGN	equ <BYTE>
endif

.pragma pack(push, SHELL_ALIGN)

HDROP	typedef HANDLE
HKEY	typedef HANDLE

;UINT
DragQueryFileA proto WINAPI \
		 hDrop: HDROP,
		 iFile: UINT,
	      lpszFile: LPSTR,
		   cch: UINT
DragQueryFileW proto WINAPI \
		      : HDROP,
		      : UINT,
		      : LPWSTR,
		      : UINT
ifdef _UNICODE
DragQueryFile equ <DragQueryFileW>
else
DragQueryFile equ <DragQueryFileA>
endif
;BOOL
DragQueryPoint proto WINAPI \
		      : HDROP,
		      : LPPOINT
;VOID
DragFinish proto WINAPI \
		      : HDROP
;VOID
DragAcceptFiles proto WINAPI \
		      : HWND,
		      : BOOL

;HINSTANCE
ShellExecuteA proto WINAPI \
		  hwnd: HWND,
	   lpOperation: LPCSTR,
		lpFile: LPCSTR,
	  lpParameters: LPCSTR,
	   lpDirectory: LPCSTR,
	      nShowCmd: SINT
;HINSTANCE
ShellExecuteW proto WINAPI \
		  hwnd: HWND,
	   lpOperation: LPCWSTR,
		lpFile: LPCWSTR,
	  lpParameters: LPCWSTR,
	   lpDirectory: LPCWSTR,
	      nShowCmd: SINT
ifdef _UNICODE
ShellExecute  equ <ShellExecuteW>
else
ShellExecute  equ <ShellExecuteA>
endif
;HINSTANCE
FindExecutableA proto WINAPI \
		lpFile: LPCSTR,
	   lpDirectory: LPCSTR,
	      lpResult: LPSTR
;HINSTANCE
FindExecutableW proto WINAPI \
		lpFile: LPCWSTR,
	   lpDirectory: LPCWSTR,
	      lpResult: LPWSTR
ifdef _UNICODE
FindExecutable equ <FindExecutableW>
else
FindExecutable equ <FindExecutableA>
endif
;LPWSTR
CommandLineToArgvW proto WINAPI \
	     lpCmdLine: LPCWSTR,
	      pNumArgs: ptr SINT

;INT
ShellAboutA proto WINAPI \
		  hWnd: HWND,
		 szApp: LPCSTR,
	  szOtherStuff: LPCSTR,
		 hIcon: HICON
;INT
ShellAboutW proto WINAPI \
		  hWnd: HWND,
		 szApp: LPCWSTR,
	  szOtherStuff: LPCWSTR,
		 hIcon: HICON
ifdef _UNICODE
ShellAbout equ <ShellAboutW>
else
ShellAbout equ <ShellAboutA>
endif
;HICON
DuplicateIcon proto WINAPI \
		 hInst: HINSTANCE,
		 hIcon: HICON
;HICON
ExtractAssociatedIconA proto WINAPI \
		 hInst: HINSTANCE,
	    lpIconPath: LPSTR,
	       lpiIcon: LPWORD
;HICON
ExtractAssociatedIconW proto WINAPI \
		 hInst: HINSTANCE,
	    lpIconPath: LPWSTR,
	       lpiIcon: LPWORD
ifdef _UNICODE
ExtractAssociatedIcon equ <ExtractAssociatedIconW>
else
ExtractAssociatedIcon equ <ExtractAssociatedIconA>
endif

;HICON
ExtractIconA proto WINAPI \
		 hInst: HINSTANCE,
       lpszExeFileName: LPCSTR,
	    nIconIndex: UINT
;HICON
ExtractIconW proto WINAPI \
		 hInst: HINSTANCE,
       lpszExeFileName: LPCWSTR,
	    nIconIndex: UINT
ifdef _UNICODE
ExtractIcon equ <ExtractIconW>
else
ExtractIcon equ <ExtractIconA>
endif

if(WINVER GE 0x0400)
DRAGINFOA		STRUC
uSize			UINT ?
pt			POINT <>
fNC			BOOL ?
lpFileList		LPSTR ?
grfKeyState		dd ?
DRAGINFOA		ENDS
LPDRAGINFOA		typedef ptr DRAGINFOA

DRAGINFOW		STRUC
uSize			UINT ?
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
endif


ABM_NEW			equ 0x00000000
ABM_REMOVE		equ 0x00000001
ABM_QUERYPOS		equ 0x00000002
ABM_SETPOS		equ 0x00000003
ABM_GETSTATE		equ 0x00000004
ABM_GETTASKBARPOS	equ 0x00000005
ABM_ACTIVATE		equ 0x00000006
ABM_GETAUTOHIDEBAR	equ 0x00000007
ABM_SETAUTOHIDEBAR	equ 0x00000008
ABM_WINDOWPOSCHANGED	equ 0x0000009
if (NTDDI_VERSION GE NTDDI_WINXP)
ABM_SETSTATE		equ 0x0000000a
endif


ABN_STATECHANGE		equ 0x0000000
ABN_POSCHANGED		equ 0x0000001
ABN_FULLSCREENAPP	equ 0x0000002
ABN_WINDOWARRANGE	equ 0x0000003

ABS_AUTOHIDE		equ 0x0000001
ABS_ALWAYSONTOP		equ 0x0000002

ABE_LEFT		equ 0
ABE_TOP			equ 1
ABE_RIGHT		equ 2
ABE_BOTTOM		equ 3

APPBARDATA		STRUC
cbSize			dd ?
hWnd			HWND ?
uCallbackMessage	UINT ?
uEdge			UINT ?
rc			RECT <>
lParam			LPARAM ?
APPBARDATA		ENDS
PAPPBARDATA		typedef ptr APPBARDATA

;UINT
SHAppBarMessage proto WINAPI \
	     dwMessage: DWORD,
		 pData: PAPPBARDATA



;DWORD
DoEnvironmentSubstA proto WINAPI \
	      szString: LPSTR,
	      cbString: UINT
;DWORD
DoEnvironmentSubstW proto WINAPI \
	      szString: LPWSTR,
	      cbString: UINT
ifdef _UNICODE
DoEnvironmentSubst equ <DoEnvironmentSubstW>
else
DoEnvironmentSubst equ <DoEnvironmentSubstA>
endif
;LPSTR
FindEnvironmentStringA proto WINAPI \
	      szEnvVar: LPSTR
;LPWSTR
FindEnvironmentStringW proto WINAPI \
	      szEnvVar: LPWSTR
ifdef _UNICODE
FindEnvironmentString equ <FindEnvironmentStringW>
else
FindEnvironmentString equ <FindEnvironmentStringA>
endif

EIRESID macro x
	exitm<x * -1>
	endm
;UINT
ExtractIconExA proto WINAPI \
	      lpszFile: LPCSTR,
	    nIconIndex: SINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
		nIcons: UINT
;UINT
ExtractIconExW proto WINAPI \
	      lpszFile: LPCWSTR,
	    nIconIndex: SINT,
	   phiconLarge: ptr HICON,
	   phiconSmall: ptr HICON,
		nIcons: UINT
ifdef _UNICODE
ExtractIconEx equ <ExtractIconExW>
else
ExtractIconEx equ <ExtractIconExA>
endif


ifndef FO_MOVE

FO_MOVE			equ 0x0001
FO_COPY			equ 0x0002
FO_DELETE		equ 0x0003
FO_RENAME		equ 0x0004

FOF_MULTIDESTFILES	equ 0x0001
FOF_CONFIRMMOUSE	equ 0x0002
FOF_SILENT		equ 0x0004
FOF_RENAMEONCOLLISION	equ 0x0008
FOF_NOCONFIRMATION	equ 0x0010
FOF_WANTMAPPINGHANDLE	equ 0x0020
FOF_ALLOWUNDO		equ 0x0040
FOF_FILESONLY		equ 0x0080
FOF_SIMPLEPROGRESS	equ 0x0100
FOF_NOCONFIRMMKDIR	equ 0x0200
FOF_NOERRORUI		equ 0x0400
if (_WIN32_IE GE 0x0500)
FOF_NOCOPYSECURITYATTRIBS equ 0x0800
FOF_NORECURSION		  equ 0x1000
FOF_NO_CONNECTED_ELEMENTS equ 0x2000
FOF_WANTNUKEWARNING	  equ 0x4000
endif
if (_WIN32_WINNT GE 0x0501)
FOF_NORECURSEREPARSE	equ 0x8000
endif

FILEOP_FLAGS		typedef WORD

PO_DELETE		equ 0x0013
PO_RENAME		equ 0x0014
PO_PORTCHANGE		equ 0x0020
PO_REN_PORT		equ 0x0034


PRINTEROP_FLAGS		typedef WORD

endif


SHFILEOPSTRUCTA		STRUC
hwnd			HWND ?
wFunc			UINT ?
pFrom			LPCSTR ?
pTo			LPCSTR ?
fFlags			FILEOP_FLAGS ?
fAnyOperationsAborted	BOOL ?
hNameMappings		LPVOID ?
lpszProgressTitle	LPCSTR ?
SHFILEOPSTRUCTA		ENDS
LPSHFILEOPSTRUCTA	typedef ptr SHFILEOPSTRUCTA
SHFILEOPSTRUCTW		STRUC
hwnd			HWND ?
wFunc			UINT ?
pFrom			LPCWSTR ?
pTo			LPCWSTR ?
fFlags			FILEOP_FLAGS ?
fAnyOperationsAborted	BOOL ?
hNameMappings		LPVOID ?
lpszProgressTitle	LPCWSTR ?
SHFILEOPSTRUCTW		ENDS
LPSHFILEOPSTRUCTW	typedef ptr SHFILEOPSTRUCTW
ifdef _UNICODE
SHFILEOPSTRUCT		typedef SHFILEOPSTRUCTW
LPSHFILEOPSTRUCT	typedef LPSHFILEOPSTRUCTW
else
SHFILEOPSTRUCT		typedef SHFILEOPSTRUCTA
LPSHFILEOPSTRUCT	typedef LPSHFILEOPSTRUCTA
endif

;int
SHFileOperationA proto WINAPI \
	      lpFileOp: LPSHFILEOPSTRUCTA
;int
SHFileOperationW proto WINAPI \
	      lpFileOp: LPSHFILEOPSTRUCTW
ifdef _UNICODE
SHFileOperation equ <SHFileOperationW>
else
SHFileOperation equ <SHFileOperationA>
endif

;void
SHFreeNameMappings proto WINAPI \
	 hNameMappings: HANDLE

SHNAMEMAPPINGA		STRUC
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
endif


SE_ERR_FNF		equ 2
SE_ERR_PNF		equ 3
SE_ERR_ACCESSDENIED	equ 5
SE_ERR_OOM		equ 8
SE_ERR_DLLNOTFOUND	equ 32

endif

SE_ERR_SHARE		equ 26
SE_ERR_ASSOCINCOMPLETE	equ 27
SE_ERR_DDETIMEOUT	equ 28
SE_ERR_DDEFAIL		equ 29
SE_ERR_DDEBUSY		equ 30
SE_ERR_NOASSOC		equ 31

if(WINVER GE 0x0400)

SEE_MASK_CLASSNAME	equ 0x00000001
SEE_MASK_CLASSKEY	equ 0x00000003
SEE_MASK_IDLIST		equ 0x00000004
SEE_MASK_INVOKEIDLIST	equ 0x0000000c
if (NTDDI_VERSION LT NTDDI_VISTA)
SEE_MASK_ICON		equ 0x00000010
endif
SEE_MASK_HOTKEY		equ 0x00000020
SEE_MASK_NOCLOSEPROCESS equ 0x00000040
SEE_MASK_CONNECTNETDRV	equ 0x00000080
SEE_MASK_FLAG_DDEWAIT	equ 0x00000100
SEE_MASK_DOENVSUBST	equ 0x00000200
SEE_MASK_FLAG_NO_UI	equ 0x00000400
SEE_MASK_UNICODE	equ 0x00004000
SEE_MASK_NO_CONSOLE	equ 0x00008000
SEE_MASK_ASYNCOK	equ 0x00100000
if (NTDDI_VERSION GE NTDDI_WIN2K)
SEE_MASK_HMONITOR	equ 0x00200000
endif
if (NTDDI_VERSION GE NTDDI_WINXPSP1)
SEE_MASK_NOZONECHECKS	equ 0x00800000
endif
if (NTDDI_VERSION GE NTDDI_WIN2K)
SEE_MASK_NOQUERYCLASSSTORE equ 0x01000000
SEE_MASK_WAITFORINPUTIDLE  equ 0x02000000
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
SEE_MASK_FLAG_LOG_USAGE equ 0x04000000
endif

SHELLEXECUTEINFOA	STRUC
cbSize			dd ?
fMask			dd ?
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
if (NTDDI_VERSION GE NTDDI_WIN2K)
    hMonitor		HANDLE ?
endif
ENDS
hProcess		HANDLE ?
SHELLEXECUTEINFOA	ENDS
LPSHELLEXECUTEINFOA	typedef ptr SHELLEXECUTEINFOA

SHELLEXECUTEINFOW	STRUC
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
if (NTDDI_VERSION GE NTDDI_WIN2K)
    hMonitor		HANDLE ?
endif
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
endif

;BOOL
ShellExecuteExA proto WINAPI \
	    lpExecInfo: LPSHELLEXECUTEINFOA
ShellExecuteExW proto WINAPI \
	    lpExecInfo: LPSHELLEXECUTEINFOW
ifdef _UNICODE
ShellExecuteEx equ <ShellExecuteExW>
else
ShellExecuteEx equ <ShellExecuteExA>
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
if 0
SHCREATEPROCESSINFOW	STRUC
cbSize			dd ?
fMask			dd ?
hwnd			HWND ?
pszFile			LPCWSTR ?
pszParameters		LPCWSTR ?
pszCurrentDirectory	LPCWSTR ?
hUserToken		HANDLE ?
lpProcessAttributes	LPSECURITY_ATTRIBUTES ?
lpThreadAttributes	LPSECURITY_ATTRIBUTES ?
bInheritHandles		BOOL ?
dwCreationFlags		dd ?
lpStartupInfo		LPSTARTUPINFOW ?
lpProcessInformation	LPPROCESS_INFORMATION ?
SHCREATEPROCESSINFOW	ENDS
PSHCREATEPROCESSINFOW	typedef ptr SHCREATEPROCESSINFOW

;SHSTDAPI_(BOOL)
SHCreateProcessAsUserW proto WINAPI \
		 pscpi: PSHCREATEPROCESSINFOW
endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)

;SHSTDAPI
SHEvaluateSystemCommandTemplate proto WINAPI \
	pszCmdTemplate: PCWSTR,
       ppszApplication: ptr PWSTR,
       ppszCommandLine: ptr PWSTR,
	ppszParameters: ptr PWSTR
if 0
;HRESULT
MyCreateProcessPriv proc pszCmd:PCWSTR

local	pszApp:PWSTR,
	pszCmdLine:PWSTR,
	hr:HRESULT,
	pi:PROCESS_INFORMATION,
	_si:STARTUPINFO


    mov hr,SHEvaluateSystemCommandTemplate(pszCmd, addr pszApp, addr pszCmdLine)
    .if SUCCEEDED(hr)


	;STARTUPINFO si = {0};
	mov _si.cb,sizeof(startup)
	mov _si.wShowWindow,SW_SHOWNORMAL

	.if CreateProcess(pszApp, pszCmdLine, NULL, NULL, FALSE,
		 CREATE_DEFAULT_ERROR_MODE, NULL, NULL, addr _si, addr pi)

	    .ASSERT(hr == S_OK)
	    CloseHandle(pi.hProcess)
	    CloseHandle(pi.hThread)
	.else

	    mov hr,HRESULT_FROM_WIN32(GetLastError())
	.endif

	CoTaskMemFree(pszApp)
	CoTaskMemFree(pszCmdLine)
    .endif
    mov eax,hr
    ret
MyCreateProcessPriv endp

;HRESULT
MyShellExec proc pszCmd:PCWSTR

local pszApp:PWSTR, pszCmdLine:PWSTR, hr:HRESULT, sei:SHELLEXECUTEINFOW

    mov hr,SHEvaluateSystemCommandTemplate(pszCmd, addr pszApp, addr pszCmdLine)
    .if SUCCEEDED(hr)


	xor eax,eax
	mov ecx,pszApp
	mov sei.cbSize,		sizeof(sei)
	mov sei.fMask,		eax
	mov sei.hwnd,		eax
	mov sei.lpVerb,		eax
	mov sei.lpFile,		ecx
	mov sei.lpParameters,	PathGetArgs(pszCmdLine)
	mov sei.lpDirectory,	eax
	mov sei.nShow,		SW_SHOWNORMAL
	mov sei.hInstApp,	eax
	mov sei.lpIDList,	eax
	mov sei.lpClass,	eax
	mov sei.hkeyClass,	eax
	mov sei.dwHotKey,	eax
	mov sei.hIcon,		eax
	mov sei.hProcess,	eax

	.if ShellExecuteEx(addr sei)

	    .ASSERT(hr == S_OK)
	.else
	    mov hr,HRESULT_FROM_WIN32(GetLastError())
	.endif

	CoTaskMemFree(pszApp)
	CoTaskMemFree(pszCmdLine)
    .endif
    mov eax,hr
    ret
MyShellExec endp
endif



ASSOCCLASS		typedef sdword ; enum
ASSOCCLASS_SHELL_KEY	equ 0
ASSOCCLASS_PROGID_KEY	equ 1
ASSOCCLASS_PROGID_STR	equ 2
ASSOCCLASS_CLSID_KEY	equ 3
ASSOCCLASS_CLSID_STR	equ 4
ASSOCCLASS_APP_KEY	equ 5
ASSOCCLASS_APP_STR	equ 6
ASSOCCLASS_SYSTEM_STR	equ 7
ASSOCCLASS_FOLDER	equ 8
ASSOCCLASS_STAR		equ 9

ASSOCIATIONELEMENT	STRUC
ac			ASSOCCLASS ?
hkClass			HKEY ?
pszClass		PCWSTR ?
ASSOCIATIONELEMENT	ENDS

;SHSTDAPI
AssocCreateForClasses proto WINAPI \
	     rgClasses: ptr ASSOCIATIONELEMENT,
	      cClasses: ULONG,
		  riid: REFIID,
		   ppv: ptr PVOID

endif


if (NTDDI_VERSION GE NTDDI_WIN2K)

SHQUERYRBINFO		STRUC
cbSize			dd ?
i64Size			dq ?
i64NumItems		dq ?
SHQUERYRBINFO		ENDS
LPSHQUERYRBINFO		typedef ptr SHQUERYRBINFO


SHERB_NOCONFIRMATION	equ 0x00000001
SHERB_NOPROGRESSUI	equ 0x00000002
SHERB_NOSOUND		equ 0x00000004

;SHSTDAPI
SHQueryRecycleBinA proto WINAPI \
	    pszRootPath: LPCSTR,
	 pSHQueryRBInfo: LPSHQUERYRBINFO
SHQueryRecycleBinW proto WINAPI \
	    pszRootPath: LPCWSTR,
	 pSHQueryRBInfo: LPSHQUERYRBINFO
ifdef _UNICODE
SHQueryRecycleBin	equ <SHQueryRecycleBinW>
else
SHQueryRecycleBin	equ <SHQueryRecycleBinA>
endif
SHEmptyRecycleBinA proto WINAPI \
		  hwnd: HWND,
	   pszRootPath: LPCSTR,
	       dwFlags: DWORD
SHEmptyRecycleBinW proto WINAPI \
		  hwnd: HWND,
	   pszRootPath: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
SHEmptyRecycleBin equ <SHEmptyRecycleBinW>
else
SHEmptyRecycleBin equ <SHEmptyRecycleBinA>
endif

endif



if (NTDDI_VERSION GE NTDDI_VISTA)
QUERY_USER_NOTIFICATION_STATE typedef sdword ; enum

QUNS_NOT_PRESENT		equ 1
QUNS_BUSY			equ 2
QUNS_RUNNING_D3D_FULL_SCREEN	equ 3
QUNS_PRESENTATION_MODE		equ 4
QUNS_ACCEPTS_NOTIFICATIONS	equ 5
if (NTDDI_VERSION GE NTDDI_WIN7)
QUNS_QUIET_TIME			equ 6
endif

;SHSTDAPI
SHQueryUserNotificationState proto WINAPI \
		 pquns: ptr QUERY_USER_NOTIFICATION_STATE
endif

if (NTDDI_VERSION GE NTDDI_WIN7)
;SHSTDAPI
SHGetPropertyStoreForWindow proto WINAPI \
		  hwnd: HWND,
		  riid: REFIID,
		   ppv: ptr PVOID
endif

NOTIFYICONDATAA		STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
uFlags			UINT ?
uCallbackMessage	UINT ?
hIcon			HICON ?
if (NTDDI_VERSION LT NTDDI_WIN2K)
szTip			db 64 dup(?)
endif
if (NTDDI_VERSION GE NTDDI_WIN2K)
szTip			db 128 dup(?)
dwState			dd ?
dwStateMask		dd ?
szInfo			db 256 dup(?)
UNION
  uTimeout		UINT ?
  uVersion		UINT ?
ENDS
szInfoTitle		db 64 dup(?)
dwInfoFlags		dd ?
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
guidItem		GUID <>
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
hBalloonIcon		HICON ?
endif
NOTIFYICONDATAA		ENDS
PNOTIFYICONDATAA	typedef ptr NOTIFYICONDATAA
NOTIFYICONDATAW		STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
uFlags			UINT ?
uCallbackMessage	UINT ?
hIcon			HICON ?
if (NTDDI_VERSION LT NTDDI_WIN2K)
szTip			dw 64 dup(?)
endif
if (NTDDI_VERSION GE NTDDI_WIN2K)
szTip			dw 128 dup(?)
dwState			dd ?
dwStateMask		dd ?
szInfo			dw 256 dup(?)
UNION
  uTimeout		UINT ?
  uVersion		UINT ?
ENDS
szInfoTitle		dw 64 dup(?)
dwInfoFlags		dd ?
endif
if (NTDDI_VERSION GE NTDDI_WINXP)
guidItem		GUID <>
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
hBalloonIcon		HICON ?
endif
NOTIFYICONDATAW		ENDS
PNOTIFYICONDATAW	typedef ptr NOTIFYICONDATAW
ifdef _UNICODE
NOTIFYICONDATA		typedef NOTIFYICONDATAW
PNOTIFYICONDATA		typedef PNOTIFYICONDATAW
else
NOTIFYICONDATA		typedef NOTIFYICONDATAA
PNOTIFYICONDATA		typedef PNOTIFYICONDATAA
endif

NOTIFYICONDATAA_V1_SIZE equ FIELD_OFFSET(NOTIFYICONDATAA, szTip[64])
NOTIFYICONDATAW_V1_SIZE equ FIELD_OFFSET(NOTIFYICONDATAW, szTip[64])
ifdef _UNICODE
NOTIFYICONDATA_V1_SIZE	equ NOTIFYICONDATAW_V1_SIZE
else
NOTIFYICONDATA_V1_SIZE	equ NOTIFYICONDATAA_V1_SIZE
endif

NOTIFYICONDATAA_V2_SIZE equ FIELD_OFFSET(NOTIFYICONDATAA, guidItem)
NOTIFYICONDATAW_V2_SIZE equ FIELD_OFFSET(NOTIFYICONDATAW, guidItem)
ifdef _UNICODE
NOTIFYICONDATA_V2_SIZE	equ NOTIFYICONDATAW_V2_SIZE
else
NOTIFYICONDATA_V2_SIZE	equ NOTIFYICONDATAA_V2_SIZE
endif

NOTIFYICONDATAA_V3_SIZE equ FIELD_OFFSET(NOTIFYICONDATAA, hBalloonIcon)
NOTIFYICONDATAW_V3_SIZE equ FIELD_OFFSET(NOTIFYICONDATAW, hBalloonIcon)
ifdef _UNICODE
NOTIFYICONDATA_V3_SIZE	equ NOTIFYICONDATAW_V3_SIZE
else
NOTIFYICONDATA_V3_SIZE	equ NOTIFYICONDATAA_V3_SIZE
endif


if (_WIN32_IE GE 0x0500)
NIN_SELECT		equ (WM_USER + 0)
NINF_KEY		equ 0x1
NIN_KEYSELECT		equ NIN_SELECT OR NINF_KEY
endif

if (_WIN32_IE GE 0x0501)
NIN_BALLOONSHOW		equ (WM_USER + 2)
NIN_BALLOONHIDE		equ (WM_USER + 3)
NIN_BALLOONTIMEOUT	equ (WM_USER + 4)
NIN_BALLOONUSERCLICK	equ (WM_USER + 5)
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
NIN_POPUPOPEN		equ (WM_USER + 6)
NIN_POPUPCLOSE		equ (WM_USER + 7)
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
endif

NIM_ADD			equ 0x00000000
NIM_MODIFY		equ 0x00000001
NIM_DELETE		equ 0x00000002

if (_WIN32_IE GE 0x0500)
NIM_SETFOCUS		equ 0x00000003
NIM_SETVERSION		equ 0x00000004
NOTIFYICON_VERSION	equ 3
if (NTDDI_VERSION GE NTDDI_VISTA)
NOTIFYICON_VERSION_4	equ 4
endif
endif

NIF_MESSAGE		equ 0x00000001
NIF_ICON		equ 0x00000002
NIF_TIP			equ 0x00000004
if (_WIN32_IE GE 0x0500)
NIF_STATE		equ 0x00000008
NIF_INFO		equ 0x00000010
endif
if (_WIN32_IE GE 0x600)
NIF_GUID		equ 0x00000020
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
NIF_REALTIME		equ 0x00000040
NIF_SHOWTIP		equ 0x00000080
endif

if (_WIN32_IE GE 0x0500)
NIS_HIDDEN		equ 0x00000001
NIS_SHAREDICON		equ 0x00000002


NIIF_NONE		equ 0x00000000
NIIF_INFO		equ 0x00000001
NIIF_WARNING		equ 0x00000002
NIIF_ERROR		equ 0x00000003
if (NTDDI_VERSION GE NTDDI_WINXPSP2)
NIIF_USER		equ 0x00000004
endif
NIIF_ICON_MASK		equ 0x0000000F
if (_WIN32_IE GE 0x0501)
NIIF_NOSOUND		equ 0x00000010
endif
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
NIIF_LARGE_ICON		equ 0x00000020
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
NIIF_RESPECT_QUIET_TIME equ 0x00000080
endif


NOTIFYICONIDENTIFIER	STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
guidItem		GUID <>
NOTIFYICONIDENTIFIER	ENDS
PNOTIFYICONIDENTIFIER	typedef ptr NOTIFYICONIDENTIFIER

;BOOL
Shell_NotifyIconA proto WINAPI \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAA
;BOOL
Shell_NotifyIconW proto WINAPI \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAW
ifdef _UNICODE
Shell_NotifyIcon equ <Shell_NotifyIconW>
else
Shell_NotifyIcon equ <Shell_NotifyIconA>
endif

;SHSTDAPI
Shell_NotifyIconGetRect proto WINAPI \
	    identifier: ptr NOTIFYICONIDENTIFIER,
	  iconLocation: ptr RECT


ifndef SHFILEINFO_DEFINED
SHFILEINFO_DEFINED equ <>



SHFILEINFOA		STRUC
hIcon			HICON ?
iIcon			SINT ?
dwAttributes		dd ?
szDisplayName		DB MAX_PATH DUP(?)
szTypeName		DB 80 DUP(?)
SHFILEINFOA		ENDS

SHFILEINFOW		STRUC
hIcon			HICON ?
iIcon			SINT ?
dwAttributes		dd ?
szDisplayName		DW MAX_PATH DUP(?)
szTypeName		DW 80 DUP(?)
SHFILEINFOW		ENDS

ifdef _UNICODE
SHFILEINFO typedef SHFILEINFOW
else
SHFILEINFO typedef SHFILEINFOA
endif

endif

SHGFI_ICON		equ 0x000000100
SHGFI_DISPLAYNAME	equ 0x000000200
SHGFI_TYPENAME		equ 0x000000400
SHGFI_ATTRIBUTES	equ 0x000000800
SHGFI_ICONLOCATION	equ 0x000001000
SHGFI_EXETYPE		equ 0x000002000
SHGFI_SYSICONINDEX	equ 0x000004000
SHGFI_LINKOVERLAY	equ 0x000008000
SHGFI_SELECTED		equ 0x000010000
if (NTDDI_VERSION GE NTDDI_WIN2K)
SHGFI_ATTR_SPECIFIED	equ 0x000020000
endif
SHGFI_LARGEICON		equ 0x000000000
SHGFI_SMALLICON		equ 0x000000001
SHGFI_OPENICON		equ 0x000000002
SHGFI_SHELLICONSIZE	equ 0x000000004
SHGFI_PIDL		equ 0x000000008
SHGFI_USEFILEATTRIBUTES equ 0x000000010
if (_WIN32_IE GE 0x0500)
SHGFI_ADDOVERLAYS	equ 0x000000020
SHGFI_OVERLAYINDEX	equ 0x000000040
endif

;SHSTDAPI_(DWORD)
SHGetFileInfoA proto WINAPI \
	       pszPath: LPCSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOA,
	    cbFileInfo: UINT,
		uFlags: UINT
SHGetFileInfoW proto WINAPI \
	       pszPath: LPCWSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOW,
	    cbFileInfo: UINT,
		uFlags: UINT
ifdef _UNICODE
SHGetFileInfo equ <SHGetFileInfoW>
else
SHGetFileInfo equ <SHGetFileInfoA>
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
SHSTOCKICONINFO		STRUC
cbSize			dd ?
hIcon			HICON ?
iSysImageIndex		SINT ?
iIcon			SINT ?
szPath			WCHAR MAX_PATH dup(?)
SHSTOCKICONINFO		ENDS

SHGSI_ICONLOCATION	equ 0
SHGSI_ICON		equ SHGFI_ICON
SHGSI_SYSICONINDEX	equ SHGFI_SYSICONINDEX
SHGSI_LINKOVERLAY	equ SHGFI_LINKOVERLAY
SHGSI_SELECTED		equ SHGFI_SELECTED
SHGSI_LARGEICON		equ SHGFI_LARGEICON
SHGSI_SMALLICON		equ SHGFI_SMALLICON
SHGSI_SHELLICONSIZE	equ SHGFI_SHELLICONSIZE


SHSTOCKICONID		typedef sdword ; enum

SIID_DOCNOASSOC		equ 0
SIID_DOCASSOC		equ 1
SIID_APPLICATION	equ 2
SIID_FOLDER		equ 3
SIID_FOLDEROPEN		equ 4
SIID_DRIVE525		equ 5
SIID_DRIVE35		equ 6
SIID_DRIVEREMOVE	equ 7
SIID_DRIVEFIXED		equ 8
SIID_DRIVENET		equ 9
SIID_DRIVENETDISABLED	equ 10
SIID_DRIVECD		equ 11
SIID_DRIVERAM		equ 12
SIID_WORLD		equ 13
SIID_SERVER		equ 15
SIID_PRINTER		equ 16
SIID_MYNETWORK		equ 17
SIID_FIND		equ 22
SIID_HELP		equ 23
SIID_SHARE		equ 28
SIID_LINK		equ 29
SIID_SLOWFILE		equ 30
SIID_RECYCLER		equ 31
SIID_RECYCLERFULL	equ 32
SIID_MEDIACDAUDIO	equ 40
SIID_LOCK		equ 47
SIID_AUTOLIST		equ 49
SIID_PRINTERNET		equ 50
SIID_SERVERSHARE	equ 51
SIID_PRINTERFAX		equ 52
SIID_PRINTERFAXNET	equ 53
SIID_PRINTERFILE	equ 54
SIID_STACK		equ 55
SIID_MEDIASVCD		equ 56
SIID_STUFFEDFOLDER	equ 57
SIID_DRIVEUNKNOWN	equ 58
SIID_DRIVEDVD		equ 59
SIID_MEDIADVD		equ 60
SIID_MEDIADVDRAM	equ 61
SIID_MEDIADVDRW		equ 62
SIID_MEDIADVDR		equ 63
SIID_MEDIADVDROM	equ 64
SIID_MEDIACDAUDIOPLUS	equ 65
SIID_MEDIACDRW		equ 66
SIID_MEDIACDR		equ 67
SIID_MEDIACDBURN	equ 68
SIID_MEDIABLANKCD	equ 69
SIID_MEDIACDROM		equ 70
SIID_AUDIOFILES		equ 71
SIID_IMAGEFILES		equ 72
SIID_VIDEOFILES		equ 73
SIID_MIXEDFILES		equ 74
SIID_FOLDERBACK		equ 75
SIID_FOLDERFRONT	equ 76
SIID_SHIELD		equ 77
SIID_WARNING		equ 78
SIID_INFO		equ 79
SIID_ERROR		equ 80
SIID_KEY		equ 81
SIID_SOFTWARE		equ 82
SIID_RENAME		equ 83
SIID_DELETE		equ 84
SIID_MEDIAAUDIODVD	equ 85
SIID_MEDIAMOVIEDVD	equ 86
SIID_MEDIAENHANCEDCD	equ 87
SIID_MEDIAENHANCEDDVD	equ 88
SIID_MEDIAHDDVD		equ 89
SIID_MEDIABLURAY	equ 90
SIID_MEDIAVCD		equ 91
SIID_MEDIADVDPLUSR	equ 92
SIID_MEDIADVDPLUSRW	equ 93
SIID_DESKTOPPC		equ 94
SIID_MOBILEPC		equ 95
SIID_USERS		equ 96
SIID_MEDIASMARTMEDIA	equ 97
SIID_MEDIACOMPACTFLASH	equ 98
SIID_DEVICECELLPHONE	equ 99
SIID_DEVICECAMERA	equ 100
SIID_DEVICEVIDEOCAMERA	equ 101
SIID_DEVICEAUDIOPLAYER	equ 102
SIID_NETWORKCONNECT	equ 103
SIID_INTERNET		equ 104
SIID_ZIPFILE		equ 105
SIID_SETTINGS		equ 106
SIID_DRIVEHDDVD		equ 132
SIID_DRIVEBD		equ 133
SIID_MEDIAHDDVDROM	equ 134
SIID_MEDIAHDDVDR	equ 135
SIID_MEDIAHDDVDRAM	equ 136
SIID_MEDIABDROM		equ 137
SIID_MEDIABDR		equ 138
SIID_MEDIABDRE		equ 139
SIID_CLUSTEREDDRIVE	equ 140
SIID_MAX_ICONS		equ 174


SIID_INVALID		equ (-1)

;SHSTDAPI
SHGetStockIconInfo proto WINAPI \
		  siid: SHSTOCKICONID,
		uFlags: UINT,
		  psii: ptr SHSTOCKICONINFO

endif


if (NTDDI_VERSION LT NTDDI_WIN2K)
;SHSTDAPI_(BOOL)
SHGetDiskFreeSpaceA proto WINAPI \
	     pszVolume: LPCSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
SHGetDiskFreeSpaceW proto WINAPI \
	     pszVolume: LPCWSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
ifdef _UNICODE
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceW>
else
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceA>
endif
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceEx>

;BOOL
SHGetDiskFreeSpaceExA proto WINAPI \
      pszDirectoryName: LPCSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
SHGetDiskFreeSpaceExW proto WINAPI \
      pszDirectoryName: LPCWSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
ifdef _UNICODE
SHGetDiskFreeSpaceEx equ <SHGetDiskFreeSpaceExW>
else
SHGetDiskFreeSpaceEx equ <SHGetDiskFreeSpaceExA>
endif

;SHSTDAPI_(BOOL)
SHGetNewLinkInfoA proto WINAPI \
	     pszLinkTo: LPCSTR,
		pszDir: LPCSTR,
	       pszName: LPSTR,
	    pfMustCopy: ptr BOOL,
		uFlags: UINT
;SHSTDAPI_(BOOL)
SHGetNewLinkInfoW proto WINAPI \
	     pszLinkTo: LPCWSTR,
		pszDir: LPCWSTR,
	       pszName: LPWSTR,
	    pfMustCopy: ptr BOOL,
		uFlags: UINT
ifdef _UNICODE
SHGetNewLinkInfo equ <SHGetNewLinkInfoW>
else
SHGetNewLinkInfo equ <SHGetNewLinkInfoA>
endif

SHGNLI_PIDL		equ 0x000000001
SHGNLI_PREFIXNAME	equ 0x000000002
SHGNLI_NOUNIQUE		equ 0x000000004
if (_WIN32_IE GE 0x0501)
SHGNLI_NOLNK		equ 0x000000008
endif
if (_WIN32_IE GE 0x0600)
SHGNLI_NOLOCNAME	equ 0x000000010
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
SHGNLI_USEURLEXT	equ 0x000000020
endif
endif


if (NTDDI_VERSION GE NTDDI_WIN2K)

PRINTACTION_OPEN		equ 0
PRINTACTION_PROPERTIES		equ 1
PRINTACTION_NETINSTALL		equ 2
PRINTACTION_NETINSTALLLINK	equ 3
PRINTACTION_TESTPAGE		equ 4
PRINTACTION_OPENNETPRN		equ 5
PRINTACTION_DOCUMENTDEFAULTS	equ 6
PRINTACTION_SERVERPROPERTIES	equ 7


;SHSTDAPI_(BOOL)
SHInvokePrinterCommandA proto WINAPI \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCSTR,
		lpBuf2: LPCSTR,
		fModal: BOOL
SHInvokePrinterCommandW proto WINAPI \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCWSTR,
		lpBuf2: LPCWSTR,
		fModal: BOOL
ifdef _UNICODE
SHInvokePrinterCommand equ <SHInvokePrinterCommandW>
else
SHInvokePrinterCommand equ <SHInvokePrinterCommandA>
endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
OPEN_PRINTER_PROPS_INFOA STRUC
dwSize			dd ?
pszSheetName		LPSTR ?
uSheetIndex		UINT ?
dwFlags			dd ?
bModal			BOOL ?
OPEN_PRINTER_PROPS_INFOA ENDS
POPEN_PRINTER_PROPS_INFOA typedef ptr OPEN_PRINTER_PROPS_INFOA
OPEN_PRINTER_PROPS_INFOW STRUC
dwSize			dd ?
pszSheetName		LPWSTR ?
uSheetIndex		UINT ?
dwFlags			dd ?
bModal			BOOL ?
OPEN_PRINTER_PROPS_INFOW ENDS
POPEN_PRINTER_PROPS_INFOW typedef ptr OPEN_PRINTER_PROPS_INFOW
ifdef _UNICODE
OPEN_PRINTER_PROPS_INFO	 typedef OPEN_PRINTER_PROPS_INFOW
POPEN_PRINTER_PROPS_INFO typedef POPEN_PRINTER_PROPS_INFOW
else
OPEN_PRINTER_PROPS_INFO	 typedef OPEN_PRINTER_PROPS_INFOA
POPEN_PRINTER_PROPS_INFO typedef POPEN_PRINTER_PROPS_INFOA
endif
PRINT_PROP_FORCE_NAME	equ 0x01
endif

endif

if (_WIN32_WINNT GE 0x0500) OR (_WIN32_WINDOWS GE 0x0500)

;SHSTDAPI
SHLoadNonloadedIconOverlayIdentifiers proto WINAPI

;SHSTDAPI
SHIsFileAvailableOffline proto WINAPI \
	      pwszPath: LPCWSTR,
	     pdwStatus: LPDWORD

OFFLINE_STATUS_LOCAL	  equ 0x0001
OFFLINE_STATUS_REMOTE	  equ 0x0002
OFFLINE_STATUS_INCOMPLETE equ 0x0004

endif

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHSetLocalizedName proto WINAPI \
	       pszPath: LPCWSTR,
	  pszResModule: LPCWSTR,
		idsRes: SINT
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHRemoveLocalizedName proto WINAPI \
	       pszPath: LPCWSTR
SHGetLocalizedName proto WINAPI \
	       pszPath: LPCWSTR,
	  pszResModule: LPWSTR,
		   cch: UINT,
	       pidsRes: ptr SINT
endif




ifndef _SHLWAPI_
LWSTDAPIV_ macro x
    exitm<EXTERN_C DECLSPEC_IMPORT x STDAPIVCALLTYPE>
    endm
else
LWSTDAPIV_ macro x
    exitm<STDAPIV_(x)>
    endm
endif

;LWSTDAPIV_(int)
ShellMessageBoxA proto _CDecl \
	      hAppInst: HINSTANCE,
		  hWnd: HWND,
	       lpcText: LPCSTR,
	      lpcTitle: LPCSTR,
	       fuStyle: UINT,
		      : VARARG
ShellMessageBoxW proto _CDecl \
	      hAppInst: HINSTANCE,
		  hWnd: HWND,
	       lpcText: LPCWSTR,
	      lpcTitle: LPCWSTR,
	       fuStyle: UINT,
		      : VARARG
ifdef _UNICODE
ShellMessageBox equ <ShellMessageBoxW>
else
ShellMessageBox equ <ShellMessageBoxA>
endif

if (NTDDI_VERSION GE NTDDI_WIN2K)
;SHSTDAPI_(BOOL)
IsLFNDriveA proto WINAPI \
	       pszPath: LPCSTR
IsLFNDriveW proto WINAPI \
	       pszPath: LPCWSTR
ifdef _UNICODE
IsLFNDrive equ <IsLFNDriveW>
else
IsLFNDrive equ <IsLFNDriveA>
endif
endif

if _WIN32_IE GE 0x0600
;STDAPI
SHEnumerateUnreadMailAccountsA proto WINAPI \
	      hKeyUser: HKEY,
	       dwIndex: DWORD,
	pszMailAddress: LPSTR,
	cchMailAddress: SINT
SHEnumerateUnreadMailAccountsW proto WINAPI \
	      hKeyUser: HKEY,
	       dwIndex: DWORD,
	pszMailAddress: LPWSTR,
	cchMailAddress: SINT
ifdef _UNICODE
SHEnumerateUnreadMailAccounts equ <SHEnumerateUnreadMailAccountsW>
else
SHEnumerateUnreadMailAccounts equ <SHEnumerateUnreadMailAccountsA>
endif
SHGetUnreadMailCountA proto WINAPI \
	      hKeyUser: HKEY,
	pszMailAddress: LPCSTR,
	      pdwCount: LPDWORD,
	     pFileTime: ptr FILETIME,
pszShellExecuteCommand: LPSTR,
cchShellExecuteCommand: SINT
SHGetUnreadMailCountW proto WINAPI \
	      hKeyUser: HKEY,
	pszMailAddress: LPCWSTR,
	      pdwCount: LPDWORD,
	     pFileTime: ptr FILETIME,
pszShellExecuteCommand: LPWSTR,
cchShellExecuteCommand: SINT
ifdef _UNICODE
SHGetUnreadMailCount equ <SHGetUnreadMailCountW>
else
SHGetUnreadMailCount equ <SHGetUnreadMailCountA>
endif
SHSetUnreadMailCountA proto WINAPI \
	pszMailAddress: LPCSTR,
	       dwCount: DWORD,
pszShellExecuteCommand: LPCSTR
SHSetUnreadMailCountW proto WINAPI \
	pszMailAddress: LPCWSTR,
	       dwCount: DWORD,
pszShellExecuteCommand: LPCWSTR
ifdef _UNICODE
SHSetUnreadMailCount equ <SHSetUnreadMailCountW>
else
SHSetUnreadMailCount equ <SHSetUnreadMailCountA>
endif
endif

if (_WIN32_IE GE 0x0601)
;STDAPI_(BOOL)
SHTestTokenMembership proto WINAPI \
		hToken: HANDLE,
		 ulRID: ULONG
endif

if _WIN32_IE GE 0x0600

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHGetImageList proto WINAPI \
	    iImageList: SINT,
		  riid: REFIID,
		ppvObj: ptr PVOID
endif

if (NTDDI_VERSION GE NTDDI_WINXP)
SHIL_LARGE		equ 0
SHIL_SMALL		equ 1
SHIL_EXTRALARGE		equ 2
SHIL_SYSSMALL		equ 3
if (NTDDI_VERSION GE NTDDI_VISTA)
SHIL_JUMBO		equ 4
SHIL_LAST		equ SHIL_JUMBO
else
SHIL_LAST		equ SHIL_SYSSMALL
endif
endif

CALLBACK(FNCANSHAREFOLDERW, pszPath:LPCWSTR)
CALLBACK(FNSHOWSHAREFOLDERUIW, hwndParent:HWND, pszPath:LPCWSTR)

endif

ifndef _WIN64
.pragma pack(pop)
.pragma pack(push, 1)
endif

if (NTDDI_VERSION GE NTDDI_VISTA)

WC_NETADDRESS equ <L"msctls_netaddress">
;SHSTDAPI_(BOOL)
InitNetworkAddressControl proto WINAPI


NCM_GETADDRESS	equ (WM_USER+1)
NetAddr_GetAddress macro hwnd, pv
    exitm<SNDMSG(hwnd,NCM_GETADDRESS,0,pv)>
    endm

NC_ADDRESS	STRUC
pAddrInfo	PVOID ? ; struct NET_ADDRESS_INFO_ *
PortNumber	dw ?
PrefixLength	db ?
NC_ADDRESS	ENDS
PNC_ADDRESS	typedef ptr NC_ADDRESS

NCM_SETALLOWTYPE equ (WM_USER+2)
NetAddr_SetAllowType macro hwnd,addrMask
    exitm<SNDMSG(hwnd,NCM_SETALLOWTYPE,addrMask,0)>
    endm

NCM_GETALLOWTYPE equ (WM_USER+3)
NetAddr_GetAllowType macro hwnd
    exitm<SNDMSG(hwnd,NCM_GETALLOWTYPE,0,0)>
    endm

NCM_DISPLAYERRORTIP equ (WM_USER+4)
NetAddr_DisplayErrorTip macro hwnd
    exitm<SNDMSG(hwnd,NCM_DISPLAYERRORTIP,0,0)>
    endm

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
;STDAPI
SHGetDriveMedia proto WINAPI \
	      pszDrive: LPCWSTR,
       pdwMediaContent: LPDWORD
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
endif

.pragma pack(pop)
endif
