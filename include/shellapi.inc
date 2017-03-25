ifndef __SHELLAPI_INC
__SHELLAPI_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif
.xlist
;;
;; SHELL.DLL functions, types, and definitions
;;
;;
;; Define API decoration for direct importing of DLL references.
;;
ifdef __PE__
option	dllimport:<shell32>
endif

ifdef _WIN64
SHELL_ALIGN	equ <>
else
;#include <pshpack1.h>
SHELL_ALIGN	equ <BYTE>
endif

HDROP	typedef HANDLE
HKEY	typedef HANDLE

;UINT
DragQueryFileA proto _CType \
		 hDrop: HDROP,
		 iFile: UINT,
	      lpszFile: LPSTR,
		   cch: UINT
DragQueryFileW proto _CType \
		      : HDROP,
		      : UINT,
		      : LPWSTR,
		      : UINT
ifdef _UNICODE
DragQueryFile equ <DragQueryFileW>
else
DragQueryFile equ <DragQueryFileA>
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
ShellExecute  equ <ShellExecuteW>
else
ShellExecute  equ <ShellExecuteA>
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
FindExecutable equ <FindExecutableW>
else
FindExecutable equ <FindExecutableA>
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
ShellAbout equ <ShellAboutW>
else
ShellAbout equ <ShellAboutA>
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
ExtractAssociatedIcon equ <ExtractAssociatedIconW>
else
ExtractAssociatedIcon equ <ExtractAssociatedIconA>
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
ExtractIcon equ <ExtractIconW>
else
ExtractIcon equ <ExtractIconA>
endif ;; NOT UNICODE

if(WINVER GE 0x0400)
DRAGINFOA		STRUC SHELL_ALIGN
uSize			UINT ?	;; init with sizeof(DRAGINFO)
pt			POINT <>
fNC			BOOL ?
lpFileList		LPSTR ?
grfKeyState		dd ?
DRAGINFOA		ENDS
LPDRAGINFOA		typedef ptr DRAGINFOA

DRAGINFOW		STRUC SHELL_ALIGN
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
if (NTDDI_VERSION GE NTDDI_WINXP)
ABM_SETSTATE		equ 0x0000000a
endif ;; (NTDDI_VERSION >= NTDDI_WINXP)


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

APPBARDATA		STRUC SHELL_ALIGN
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
DoEnvironmentSubst equ <DoEnvironmentSubstW>
else
DoEnvironmentSubst equ <DoEnvironmentSubstA>
endif ;; NOT UNICODE
;LPSTR
FindEnvironmentStringA proto _CType \
	      szEnvVar: LPSTR
;LPWSTR
FindEnvironmentStringW proto _CType \
	      szEnvVar: LPWSTR
ifdef _UNICODE
FindEnvironmentString equ <FindEnvironmentStringW>
else
FindEnvironmentString equ <FindEnvironmentStringA>
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
ExtractIconEx equ <ExtractIconExW>
else
ExtractIconEx equ <ExtractIconExA>
endif ;; NOT UNICODE



;;
;; Shell File Operations
;;

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
if (_WIN32_IE GE 0x0500)
FOF_NOCOPYSECURITYATTRIBS equ 0x0800;; dont copy file security attributes (ACLs)
FOF_NORECURSION		  equ 0x1000;; don't recurse into directories for operations that would recurse
FOF_NO_CONNECTED_ELEMENTS equ 0x2000;; don't operate on connected elements ("xxx_files" folders that go with .htm files)
FOF_WANTNUKEWARNING	  equ 0x4000;; during delete operation, warn if nuking instead of recycling (partially overrides FOF_NOCONFIRMATION)
endif ;; (_WIN32_IE >= 0x500)
if (_WIN32_WINNT GE 0x0501)
FOF_NORECURSEREPARSE	equ 0x8000  ;; deprecated; the operations engine always does the right thing on FolderLink objects (symlinks, reparse points, folder shortcuts)
endif ;; (_WIN32_WINNT >= 0x501)

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

SHFILEOPSTRUCTA		STRUC SHELL_ALIGN
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
SHFILEOPSTRUCTW		STRUC SHELL_ALIGN
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
SHFileOperation equ <SHFileOperationW>
else
SHFileOperation equ <SHFileOperationA>
endif ;; NOT UNICODE

;void
SHFreeNameMappings proto _CType \
	 hNameMappings: HANDLE

SHNAMEMAPPINGA		STRUC SHELL_ALIGN
pszOldPath		LPSTR ?
pszNewPath		LPSTR ?
cchOldPath		SINT ?
cchNewPath		SINT ?
SHNAMEMAPPINGA		ENDS
LPSHNAMEMAPPINGA	typedef ptr SHNAMEMAPPINGA
SHNAMEMAPPINGW		STRUC SHELL_ALIGN
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


;;
;; End Shell File Operations
;;

;;
;;  Begin ShellExecuteEx and family
;;


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
if (NTDDI_VERSION LT NTDDI_VISTA)
SEE_MASK_ICON		equ 0x00000010
endif ;; (NTDDI_VERSION < NTDDI_VISTA)
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
SEE_MASK_HMONITOR	equ 0x00200000	 ;; SHELLEXECUTEINFO.hMonitor
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)
if (NTDDI_VERSION GE NTDDI_WINXPSP1)
SEE_MASK_NOZONECHECKS	equ 0x00800000
endif ;; (NTDDI_VERSION >= NTDDI_WINXPSP1)
if (NTDDI_VERSION GE NTDDI_WIN2K)
SEE_MASK_NOQUERYCLASSSTORE equ 0x01000000
SEE_MASK_WAITFORINPUTIDLE  equ 0x02000000
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)
if (NTDDI_VERSION GE NTDDI_WINXP)
SEE_MASK_FLAG_LOG_USAGE equ 0x04000000
endif ;; (NTDDI_VERSION >= NTDDI_WINXP)

SHELLEXECUTEINFOA	STRUC SHELL_ALIGN
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
    hMonitor		HANDLE ? ;; in, valid when SEE_MASK_HMONITOR specified
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)
ENDS
hProcess		HANDLE ?
SHELLEXECUTEINFOA	ENDS
LPSHELLEXECUTEINFOA	typedef ptr SHELLEXECUTEINFOA

SHELLEXECUTEINFOW	STRUC SHELL_ALIGN
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
    hMonitor		HANDLE ? ;; in, valid when SEE_MASK_HMONITOR specified
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)
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
ShellExecuteExW proto _CType \
	    lpExecInfo: LPSHELLEXECUTEINFOW
ifdef _UNICODE
ShellExecuteEx equ <ShellExecuteExW>
else
ShellExecuteEx equ <ShellExecuteExA>
endif ;; NOT UNICODE

if (NTDDI_VERSION GE NTDDI_WIN2K)
;; deprecated, no longer implemented
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
SHCreateProcessAsUserW proto _CType \
		 pscpi: PSHCREATEPROCESSINFOW
endif
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)

if (NTDDI_VERSION GE NTDDI_VISTA)

;SHSTDAPI
SHEvaluateSystemCommandTemplate proto _CType \
	pszCmdTemplate: PCWSTR,
       ppszApplication: ptr PWSTR,
       ppszCommandLine: ptr PWSTR,
	ppszParameters: ptr PWSTR
;;
;;  SHEvaluateSystemCommandTemplate()
;;	*   enforces stricter validation before calling CreateProcess().	 may also be
;;	       used before calling ShellExecute().
;;	*   should be used when caller wants the deterministic behavior from a command template
;;	       regardless of execution context.	 it ignores the current process state,
;;	       such as the %PATH%, GetCurrentDirectory(), and parent process directory.
;;	*   should be used when the command is hardcoded.
;;	*   is used by ShellExecute() when handling file associations from HKCR.
;;	*   reduces CreateProcess() commandline exploits
;;	*   is not designed for processing user input, and may generate unexpected failures.
;;
;;  INPUT:
;;	pszCmdTemplate =	   command line, this may or may not include parameters.
;;			   if the parameters are substitution parameters then this API
;;			   should be called before parameters have been replaced.
;;			   (check the examples below to see sample supported inputs.)
;;
;;  OUTPUT on return: S_OK
;;	ppszApplication =   verified path to the Application.  this should be passed as the lpApplication
;;			   parameter to CreateProcess() or the lpFile parameter to ShellExecute().
;;			   (allocated using CoTaskMemAlloc(), free with CoTaskMemFree())
;;
;;	ppszCommandLine =   OPTIONAL - use if planning to call CreateProcess().
;;			   resulting command line template.  parameters should be replaced based on this template,
;;			   and then passed as the lpCommandLine parameter to CreateProcess().
;;			   it is guaranteed to be of a form that PathGetArgs() will always succeed correctly.
;;			   (allocated using CoTaskMemAlloc(), free with CoTaskMemFree())
;;
;;	ppszParameters	=   OPTIONAL - use if planning to call ShellExecute().
;;			   resulting parameter list template.  parameters should be replaced based on this template,
;;			   and then passed as the lpParameters parameter to ShellExecute().
;;			   NOTE: identical to PathGetArgs(*ppszCommandLine).
;;			   (allocated using CoTaskMemAlloc(), free with CoTaskMemFree())
;;
;;  OUTPUT on return: FAILED()
;;	all outputs will be NULL'ed on failure
;;
;;  NOTES:  the parsing logic to determine a valid Application path is non-trivial, although
;;	       the extension is not required and if missing will be completed
;;	       in the following standard order:	 { .PIF, .COM, .EXE, .BAT, .CMD }
;;
;;	Relative Paths are System Paths - if the first token has no path qualifiers
;;	       then the token is first checked to see if a key of the same name has
;;	       been installed under HKLM\Software\Microsoft\Windows\CurrentVersion\App Paths.
;;	       if the key or default value does not exist, it is assumed to be a child
;;	       of the system directories.  the following directories will be searched
;;	       in order for the relative token: { CSIDL_SYSTEM, CSIDL_WINDOWS }
;;
;;	Prefer Quoted Paths - if the first token in pszCmdTemplate is quoted and appears
;;	       to be an absolute path then the token is the only possible result.
;;
;;	Limit Forms of Unquoted Paths - if the first token is unquoted and appears
;;	       to be an absolute path, then it is subject to more stringent limitations.
;;	       if the token is a substring of CSIDL_PROGRAM_FILES or does not
;;	       exist on the file system, then SHEvaluateSystemCommandTemplate() will
;;	       attempt to complete using a token delimited by the first space of the
;;	       last valid path segment (usually the file name).	 if this token also doesnt exist,
;;	       then the next space will be used, etc.
;;
;;  USAGE:	used before calling into CreateProcess() or ShellExecute(), callers
;;	       would typically look like the following:
if 0 ;; SAMPLE CODE
;HRESULT
MyCreateProcessPriv proc pszCmd:PCWSTR

local	pszApp:PWSTR,
	pszCmdLine:PWSTR,
	hr:HRESULT,
	pi:PROCESS_INFORMATION,
	_si:STARTUPINFO


    mov hr,SHEvaluateSystemCommandTemplate(pszCmd, addr pszApp, addr pszCmdLine)
    .if SUCCEEDED(hr)

	;;  if this was a real template, maybe some kind of wnsprintf() first?

	;STARTUPINFO si = {0};
	mov _si.cb,sizeof(startup)
	mov _si.wShowWindow,SW_SHOWNORMAL

	.if CreateProcess(pszApp, pszCmdLine, NULL, NULL, FALSE,
		 CREATE_DEFAULT_ERROR_MODE, NULL, NULL, addr _si, addr pi)

	    ;;	we are good
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

	;;  if this was a real template, maybe some kind of wnsprintf() first?

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

	    ;;	we are good
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
endif ;;  0 ;; SAMPLE CODE

;;  EXAMPLE:   Each example will show an input parameter and the results returned by
;;	       SHEvaluateSystemCommandTemplate().  Also included is the alternate result
;;	       of what CreateProcess() would have created if pszCmdTemplate were
;;	       passed directly as lpCommandLine and lpApplication were NULL.
;;	       (results marked with an asterisk (*) indicate differences.)
;;
;;	   Assume for the examples that the following paths and values exist:
;;
;;	SHGetFolderPath() values:
;;	   CSIDL_SYSTEM		   =   C:\windows\system32
;;	   CSIDL_WINDOWS	   =   C:\windows
;;	   CSIDL_PROGRAM_FILES	   =   C:\Program Files
;;
;;	Environment settings
;;	   GetModuleFileName(NULL) =   C:\Program Files\Example\sample.exe
;;	   GetCurrentDirectory()   =   \\server\share\foo
;;	   HKLM\...\App Paths\pbrush.exe = C:\windows\system32\mspaint.exe
;;	   HKLM\...\App Paths\mycl.exe = C:\Program Files\Compilers\mycl.exe
;;	   PATH			   =   c:\windows\system32;C:\windows;c:\;C:\Program Files\Compilers\
;;
;;	Valid Application paths:
;;	   C:\Program Files\Internet Explorer\iexplore.exe
;;	   C:\windows\system32\rundll32.exe
;;	   C:\windows\system32\notepad.exe
;;	   C:\windows\notepad.exe
;;	   C:\Program Files\Example\sample.exe
;;	   C:\Program Files\Compilers\cl.exe
;;	   C:\Other Programs\prog.exe
;;
;;	Suspicious (possibly hostile) Application paths:
;;	   C:\Program.exe
;;	   C:\Program Files\Internet.exe
;;	   C:\Program Files\Example\regedit.bat
;;	   C:\mycl.exe
;;	   \\server\share\foo\rundll32.exe
;;	   \\server\share\foo\myapp.exe
;;
;;
;;  Relative Path Example #1
;;	pszCmdTemplate	   =   notepad.exe %1
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\windows\system32\notepad.exe
;;	       pszCommandLine  =   "notepad.exe" %1
;;	   CreateProcess() would return TRUE
;;	       new process =   C:\windows\system32\notepad.exe
;;
;;  Relative Path Example #2
;;	pszCmdTemplate	   =   rundll32.exe shell32.dll,RunDll
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\windows\system32\rundll32.exe
;;	       pszCommandLine  =   "rundll32.exe" shell32.dll,RunDll
;;	   * CreateProcess() would return TRUE
;;	       new process =   \\server\share\foo\rundll32.exe
;;
;;  Relative Path Example #3
;;	pszCmdTemplate	   =   regedit %1
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\windows\system32\regedit.exe
;;	       pszCommandLine  =   "regedit.exe" %1
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program Files\Example\regedit.bat
;;
;;  Relative Path Example #4
;;	pszCmdTemplate	   =   pbrush "%1"
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\windows\system32\mspaint.exe
;;	       pszCommandLine  =   "mspaint.exe" "%1"
;;	   * CreateProcess() would return FALSE
;;
;;  Relative Path Example #5
;;	pszCmdTemplate	   =   mycl "%1" "%2"
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Compilers\mycl.exe
;;	       pszCommandLine  =   "mycl.exe" "%1" "%2"
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\mycl.exe
;;
;;  Relative Path Example #6
;;	pszCmdTemplate	   =   myapp.exe
;;	   SHEvaluateSystemCommandTemplate() returns: CO_E_APPNOTFOUND
;;	   * CreateProcess() would return TRUE
;;	       new process =   \\server\share\foo\myapp.exe
;;
;;  Quoted Path Example #1
;;	pszCmdTemplate	   =   "C:\Program Files\Internet Explorer\iexplore.exe" -nohome
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet Explorer\iexplore.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet Explorer\iexplore.exe" -nohome
;;	   CreateProcess() would return TRUE
;;	       new process =   C:\Program Files\Internet Explorer\iexplore.exe
;;
;;  Quoted Path Example #2
;;	pszCmdTemplate	   =   "C:\Program Files\Internet" -url
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet.exe" -url
;;	   CreateProcess() would return TRUE
;;	       new process =   C:\Program Files\internet.exe
;;
;;  Quoted Path Example #3
;;	pszCmdTemplate	   =   "C:\Program" -url
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program.exe
;;	       pszCommandLine  =   "C:\Program.exe" -url
;;	   CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #1
;;	pszCmdTemplate	   =   C:\Program Files\Internet Explorer\iexplore.exe -nohome
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet Explorer\iexplore.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet Explorer\iexplore.exe" -nohome
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #2
;;	pszCmdTemplate	   =   C:\Program Files\Internet Explorer\iexplore.exe -url fool.htm
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet Explorer\iexplore.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet Explorer\iexplore.exe" -url fool.htm
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #3
;;	pszCmdTemplate	   =   C:\Program Files\Internet Explorer\iexplore.exe -url C:\fool.htm
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet Explorer\iexplore.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet Explorer\iexplore.exe" -url C:\fool.htm
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #4
;;	pszCmdTemplate	   =   C:\Program Files\Internet -url
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Program Files\Internet.exe
;;	       pszCommandLine  =   "C:\Program Files\Internet.exe" -url
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #5
;;	pszCmdTemplate	   =   C:\Other Programs\prog.exe -go %1 \fool %2
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Other Programs\prog.exe
;;	       pszCommandLine  =   "C:\Other Programs\prog.exe" %1 \fool %2
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Other Programs\prog.exe
;;
;;  Unquoted Example #6
;;	pszCmdTemplate	   =   C:\Other Programs\prog.exe -go "\fool" "%1"
;;	   SHEvaluateSystemCommandTemplate() returns: S_OK
;;	       pszApplication  =   C:\Other Programs\prog.exe
;;	       pszCommandLine  =   "C:\Other Programs\prog.exe" -go "\fool" "%1"
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Other Programs\prog.exe
;;
;;  Unquoted Example #7
;;	pszCmdTemplate	   =   C:\Program Files\Internet Explorer\iexplore.exe -url \fool.htm
;;	   SHEvaluateSystemCommandTemplate() returns: CO_E_APPNOTFOUND
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #8
;;	pszCmdTemplate	   =   C:\Program -url
;;	   SHEvaluateSystemCommandTemplate() returns: CO_E_APPNOTFOUND
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #9
;;	pszCmdTemplate	   =   C:\Other Programs\prog.exe -go \fool us
;;	   SHEvaluateSystemCommandTemplate() returns: CO_E_APPNOTFOUND
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Other Programs\prog.exe
;;
;;  Unquoted Example #10
;;	pszCmdTemplate	   =   C:\Other Programs\prog.exe -go \fool %1
;;	   SHEvaluateSystemCommandTemplate() returns: CO_E_APPNOTFOUND
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Other Programs\prog.exe
;;
;;  Unquoted Example #11
;;	pszCmdTemplate	   =   C:\Program "%1"
;;	   SHEvaluateSystemCommandTemplate() returns: E_ACCESSDENIED
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;
;;  Unquoted Example #12
;;	pszCmdTemplate	   =   C:\Program
;;	   SHEvaluateSystemCommandTemplate() returns: E_ACCESSDENIED
;;	   * CreateProcess() would return TRUE
;;	       new process =   C:\Program.exe
;;

;;  used for implementing IShellFolder::GetUIObject(IID_IQueryAssociations)
;;  designed for namespace extensions with registered extensible types
;;  SHCreateDefaultContextMenu() and others use IQueryAssociations to build up data sets

ASSOCCLASS		typedef sdword ; enum
				;;  which other members are used
ASSOCCLASS_SHELL_KEY	equ 0	;;  hkeyClass
ASSOCCLASS_PROGID_KEY	equ 1	;;  hkeyClass
ASSOCCLASS_PROGID_STR	equ 2	;;  pszClass (HKCR\pszClass)
ASSOCCLASS_CLSID_KEY	equ 3	;;  hkeyClass
ASSOCCLASS_CLSID_STR	equ 4	;;  pszClass (HKCR\CLSID\pszClass)
ASSOCCLASS_APP_KEY	equ 5	;;  hkeyClass
ASSOCCLASS_APP_STR	equ 6	;;  pszClass (HKCR\Applications\PathFindFileName(pszClass))
ASSOCCLASS_SYSTEM_STR	equ 7	;;  pszClass
ASSOCCLASS_FOLDER	equ 8	;;  none
ASSOCCLASS_STAR		equ 9	;;  none

ASSOCIATIONELEMENT	STRUC
ac			ASSOCCLASS ?	;; required
hkClass			HKEY ?		;; may be NULL
pszClass		PCWSTR ?	;; may be NULL
ASSOCIATIONELEMENT	ENDS

;SHSTDAPI
AssocCreateForClasses proto _CType \
	     rgClasses: ptr ASSOCIATIONELEMENT,
	      cClasses: ULONG,
		  riid: REFIID,
		   ppv: ptr PVOID

endif ;; (NTDDI_VERSION >= NTDDI_VISTA)

;;
;;  End ShellExecuteEx and family
;;

if (NTDDI_VERSION GE NTDDI_WIN2K)

;;
;; RecycleBin
;;


;; struct for query recycle bin info
SHQUERYRBINFO		STRUC SHELL_ALIGN
cbSize			dd ?
i64Size			dq ?
i64NumItems		dq ?
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
SHEmptyRecycleBin equ <SHEmptyRecycleBinW>
else
SHEmptyRecycleBin equ <SHEmptyRecycleBinA>
endif ;; NOT UNICODE

;;
;; end of RecycleBin
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)


;;
;; Taskbar notification definitions
;;

if (NTDDI_VERSION GE NTDDI_VISTA)
QUERY_USER_NOTIFICATION_STATE typedef sdword ; enum

QUNS_NOT_PRESENT		equ 1	;; The user is not present.  Heuristic check for modes like: screen saver, locked machine, non-active FUS session
QUNS_BUSY			equ 2	;; The user is busy.  Heuristic check for modes like: full-screen app
QUNS_RUNNING_D3D_FULL_SCREEN	equ 3	;; full-screen (exlusive-mode) D3D app
QUNS_PRESENTATION_MODE		equ 4	;; Windows presentation mode (laptop feature) is turned on
QUNS_ACCEPTS_NOTIFICATIONS	equ 5	;; notifications can be freely sent
if (NTDDI_VERSION GE NTDDI_WIN7)
QUNS_QUIET_TIME			equ 6	;; We are in OOBE quiet period
endif

;SHSTDAPI
SHQueryUserNotificationState proto _CType \
		 pquns: ptr QUERY_USER_NOTIFICATION_STATE
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)

if (NTDDI_VERSION GE NTDDI_WIN7)
;; This api retrieves an IPropertyStore that stores the window's properties.
;SHSTDAPI
SHGetPropertyStoreForWindow proto _CType \
		  hwnd: HWND,
		  riid: REFIID,
		   ppv: ptr PVOID
endif

NOTIFYICONDATAA		STRUC SHELL_ALIGN
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
  uVersion		UINT ? ;; used with NIM_SETVERSION, values 0, 3 and 4
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
NOTIFYICONDATAW		STRUC SHELL_ALIGN
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
  uVersion		UINT ? ;; used with NIM_SETVERSION, values 0, 3 and 4
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
endif ;; UNICODE

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
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)
if (NTDDI_VERSION GE NTDDI_WIN7)
endif ;; (NTDDI_VERSION >= NTDDI_WIN7)

NIM_ADD			equ 0x00000000
NIM_MODIFY		equ 0x00000001
NIM_DELETE		equ 0x00000002

if (_WIN32_IE GE 0x0500)
NIM_SETFOCUS		equ 0x00000003
NIM_SETVERSION		equ 0x00000004
;; set NOTIFYICONDATA.uVersion with 0, 3 or 4
;; please read the documentation on the behavior difference that the different
;; versions imply
NOTIFYICON_VERSION	equ 3
if (NTDDI_VERSION GE NTDDI_VISTA)
NOTIFYICON_VERSION_4	equ 4
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)
endif ;; (_WIN32_IE GE 0x0500)

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
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)

if (_WIN32_IE GE 0x0500)
NIS_HIDDEN		equ 0x00000001
NIS_SHAREDICON		equ 0x00000002

;; says this is the source of a shared icon

;; Notify Icon Infotip flags
NIIF_NONE		equ 0x00000000
;; icon flags are mutually exclusive
;; and take only the lowest 2 bits
NIIF_INFO		equ 0x00000001
NIIF_WARNING		equ 0x00000002
NIIF_ERROR		equ 0x00000003
if (NTDDI_VERSION GE NTDDI_WINXPSP2) ;; also available in NTDDI_WS03SP1
NIIF_USER		equ 0x00000004
endif ;; (NTDDI_VERSION >= NTDDI_XPSP2)
NIIF_ICON_MASK		equ 0x0000000F
if (_WIN32_IE GE 0x0501)
NIIF_NOSOUND		equ 0x00000010
endif
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
NIIF_LARGE_ICON		equ 0x00000020
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)
if (NTDDI_VERSION GE NTDDI_WIN7)
NIIF_RESPECT_QUIET_TIME equ 0x00000080
endif ;; (NTDDI_VERSION >= NTDDI_WIN7)


NOTIFYICONIDENTIFIER	STRUC
cbSize			dd ?
hWnd			HWND ?
uID			UINT ?
guidItem		GUID <>
NOTIFYICONIDENTIFIER	ENDS
PNOTIFYICONIDENTIFIER	typedef ptr NOTIFYICONIDENTIFIER

;BOOL
Shell_NotifyIconA proto _CType \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAA
;BOOL
Shell_NotifyIconW proto _CType \
	     dwMessage: DWORD,
		lpData: PNOTIFYICONDATAW
ifdef _UNICODE
Shell_NotifyIcon equ <Shell_NotifyIconW>
else
Shell_NotifyIcon equ <Shell_NotifyIconA>
endif ;; NOT UNICODE

;SHSTDAPI
Shell_NotifyIconGetRect proto _CType \
	    identifier: ptr NOTIFYICONIDENTIFIER,
	  iconLocation: ptr RECT

;;
;; End Taskbar Notification Icons
;;

ifndef SHFILEINFO_DEFINED
SHFILEINFO_DEFINED equ <>

;;
;; Begin SHGetFileInfo
;;

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

SHFILEINFOA		STRUC SHELL_ALIGN
hIcon			HICON ? ;; out: icon
iIcon			SINT ?	;; out: icon index
dwAttributes		dd ?	;; out: SFGAO_ flags
szDisplayName		DB MAX_PATH DUP(?) ;; out: display name (or path)
szTypeName		DB 80 DUP(?) ;; out: type name
SHFILEINFOA		ENDS

SHFILEINFOW		STRUC SHELL_ALIGN
hIcon			HICON ? ;; out: icon
iIcon			SINT ?	;; out: icon index
dwAttributes		dd ?	;; out: SFGAO_ flags
szDisplayName		DW MAX_PATH DUP(?)	;; out: display name (or path)
szTypeName		DW 80 DUP(?) ;; out: type name
SHFILEINFOW		ENDS

ifdef _UNICODE
SHFILEINFO typedef SHFILEINFOW
else
SHFILEINFO typedef SHFILEINFOA
endif ;; UNICODE

;; NOTE: This is also in shlwapi.h.  Please keep in synch.
endif ;; !SHFILEINFO_DEFINED

SHGFI_ICON		equ 0x000000100 ;; get icon
SHGFI_DISPLAYNAME	equ 0x000000200 ;; get display name
SHGFI_TYPENAME		equ 0x000000400 ;; get type name
SHGFI_ATTRIBUTES	equ 0x000000800 ;; get attributes
SHGFI_ICONLOCATION	equ 0x000001000 ;; get icon location
SHGFI_EXETYPE		equ 0x000002000 ;; return exe type
SHGFI_SYSICONINDEX	equ 0x000004000 ;; get system icon index
SHGFI_LINKOVERLAY	equ 0x000008000 ;; put a link overlay on icon
SHGFI_SELECTED		equ 0x000010000 ;; show icon in selected state
if (NTDDI_VERSION GE NTDDI_WIN2K)
SHGFI_ATTR_SPECIFIED	equ 0x000020000 ;; get only specified attributes
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)
SHGFI_LARGEICON		equ 0x000000000 ;; get large icon
SHGFI_SMALLICON		equ 0x000000001 ;; get small icon
SHGFI_OPENICON		equ 0x000000002 ;; get open icon
SHGFI_SHELLICONSIZE	equ 0x000000004 ;; get shell size icon
SHGFI_PIDL		equ 0x000000008 ;; pszPath is a pidl
SHGFI_USEFILEATTRIBUTES equ 0x000000010 ;; use passed dwFileAttribute
if (_WIN32_IE GE 0x0500)
SHGFI_ADDOVERLAYS	equ 0x000000020 ;; apply the appropriate overlays
SHGFI_OVERLAYINDEX	equ 0x000000040 ;; Get the index of the overlay
					;; in the upper 8 bits of the iIcon
endif

;SHSTDAPI_(DWORD)
SHGetFileInfoA proto _CType \
	       pszPath: LPCSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOA,
	    cbFileInfo: UINT,
		uFlags: UINT
SHGetFileInfoW proto _CType \
	       pszPath: LPCWSTR,
      dwFileAttributes: DWORD,
		  psfi: ptr SHFILEINFOW,
	    cbFileInfo: UINT,
		uFlags: UINT
ifdef _UNICODE
SHGetFileInfo equ <SHGetFileInfoW>
else
SHGetFileInfo equ <SHGetFileInfoA>
endif ;; NOT UNICODE

if (NTDDI_VERSION GE NTDDI_VISTA)
SHSTOCKICONINFO		STRUC
cbSize			dd ?
hIcon			HICON ?
iSysImageIndex		SINT ?
iIcon			SINT ?
szPath			WCHAR MAX_PATH dup(?)
SHSTOCKICONINFO		ENDS

SHGSI_ICONLOCATION	equ 0 ;; you always get the icon location
SHGSI_ICON		equ SHGFI_ICON
SHGSI_SYSICONINDEX	equ SHGFI_SYSICONINDEX
SHGSI_LINKOVERLAY	equ SHGFI_LINKOVERLAY
SHGSI_SELECTED		equ SHGFI_SELECTED
SHGSI_LARGEICON		equ SHGFI_LARGEICON
SHGSI_SMALLICON		equ SHGFI_SMALLICON
SHGSI_SHELLICONSIZE	equ SHGFI_SHELLICONSIZE

;; Shell icons

SHSTOCKICONID		typedef sdword ; enum

SIID_DOCNOASSOC		equ 0	;; document (blank page), no associated program
SIID_DOCASSOC		equ 1	;; document with an associated program
SIID_APPLICATION	equ 2	;; generic application with no custom icon
SIID_FOLDER		equ 3	;; folder (closed)
SIID_FOLDEROPEN		equ 4	;; folder (open)
SIID_DRIVE525		equ 5	;; 5.25" floppy disk drive
SIID_DRIVE35		equ 6	;; 3.5" floppy disk drive
SIID_DRIVEREMOVE	equ 7	;; removable drive
SIID_DRIVEFIXED		equ 8	;; fixed (hard disk) drive
SIID_DRIVENET		equ 9	;; network drive
SIID_DRIVENETDISABLED	equ 10	;; disconnected network drive
SIID_DRIVECD		equ 11	;; CD drive
SIID_DRIVERAM		equ 12	;; RAM disk drive
SIID_WORLD		equ 13	;; entire network
SIID_SERVER		equ 15	;; a computer on the network
SIID_PRINTER		equ 16	;; printer
SIID_MYNETWORK		equ 17	;; My network places
SIID_FIND		equ 22	;; Find
SIID_HELP		equ 23	;; Help
SIID_SHARE		equ 28	;; overlay for shared items
SIID_LINK		equ 29	;; overlay for shortcuts to items
SIID_SLOWFILE		equ 30	;; overlay for slow items
SIID_RECYCLER		equ 31	;; empty recycle bin
SIID_RECYCLERFULL	equ 32	;; full recycle bin
SIID_MEDIACDAUDIO	equ 40	;; Audio CD Media
SIID_LOCK		equ 47	;; Security lock
SIID_AUTOLIST		equ 49	;; AutoList
SIID_PRINTERNET		equ 50	;; Network printer
SIID_SERVERSHARE	equ 51	;; Server share
SIID_PRINTERFAX		equ 52	;; Fax printer
SIID_PRINTERFAXNET	equ 53	;; Networked Fax Printer
SIID_PRINTERFILE	equ 54	;; Print to File
SIID_STACK		equ 55	;; Stack
SIID_MEDIASVCD		equ 56	;; SVCD Media
SIID_STUFFEDFOLDER	equ 57	;; Folder containing other items
SIID_DRIVEUNKNOWN	equ 58	;; Unknown drive
SIID_DRIVEDVD		equ 59	;; DVD Drive
SIID_MEDIADVD		equ 60	;; DVD Media
SIID_MEDIADVDRAM	equ 61	;; DVD-RAM Media
SIID_MEDIADVDRW		equ 62	;; DVD-RW Media
SIID_MEDIADVDR		equ 63	;; DVD-R Media
SIID_MEDIADVDROM	equ 64	;; DVD-ROM Media
SIID_MEDIACDAUDIOPLUS	equ 65	;; CD+ (Enhanced CD) Media
SIID_MEDIACDRW		equ 66	;; CD-RW Media
SIID_MEDIACDR		equ 67	;; CD-R Media
SIID_MEDIACDBURN	equ 68	;; Burning CD
SIID_MEDIABLANKCD	equ 69	;; Blank CD Media
SIID_MEDIACDROM		equ 70	;; CD-ROM Media
SIID_AUDIOFILES		equ 71	;; Audio files
SIID_IMAGEFILES		equ 72	;; Image files
SIID_VIDEOFILES		equ 73	;; Video files
SIID_MIXEDFILES		equ 74	;; Mixed files
SIID_FOLDERBACK		equ 75	;; Folder back
SIID_FOLDERFRONT	equ 76	;; Folder front
SIID_SHIELD		equ 77	;; Security shield. Use for UAC prompts only.
SIID_WARNING		equ 78	;; Warning
SIID_INFO		equ 79	;; Informational
SIID_ERROR		equ 80	;; Error
SIID_KEY		equ 81	;; Key / Secure
SIID_SOFTWARE		equ 82	;; Software
SIID_RENAME		equ 83	;; Rename
SIID_DELETE		equ 84	;; Delete
SIID_MEDIAAUDIODVD	equ 85	;; Audio DVD Media
SIID_MEDIAMOVIEDVD	equ 86	;; Movie DVD Media
SIID_MEDIAENHANCEDCD	equ 87	;; Enhanced CD Media
SIID_MEDIAENHANCEDDVD	equ 88	;; Enhanced DVD Media
SIID_MEDIAHDDVD		equ 89	;; HD-DVD Media
SIID_MEDIABLURAY	equ 90	;; BluRay Media
SIID_MEDIAVCD		equ 91	;; VCD Media
SIID_MEDIADVDPLUSR	equ 92	;; DVD+R Media
SIID_MEDIADVDPLUSRW	equ 93	;; DVD+RW Media
SIID_DESKTOPPC		equ 94	;; desktop computer
SIID_MOBILEPC		equ 95	;; mobile computer (laptop/notebook)
SIID_USERS		equ 96	;; users
SIID_MEDIASMARTMEDIA	equ 97	;; Smart Media
SIID_MEDIACOMPACTFLASH	equ 98	;; Compact Flash
SIID_DEVICECELLPHONE	equ 99	;; Cell phone
SIID_DEVICECAMERA	equ 100 ;; Camera
SIID_DEVICEVIDEOCAMERA	equ 101 ;; Video camera
SIID_DEVICEAUDIOPLAYER	equ 102 ;; Audio player
SIID_NETWORKCONNECT	equ 103 ;; Connect to network
SIID_INTERNET		equ 104 ;; Internet
SIID_ZIPFILE		equ 105 ;; ZIP file
SIID_SETTINGS		equ 106 ;; Settings
				;; 107-131 are internal Vista RTM icons
				;; 132-159 for SP1 icons
SIID_DRIVEHDDVD		equ 132 ;; HDDVD Drive (all types)
SIID_DRIVEBD		equ 133 ;; BluRay Drive (all types)
SIID_MEDIAHDDVDROM	equ 134 ;; HDDVD-ROM Media
SIID_MEDIAHDDVDR	equ 135 ;; HDDVD-R Media
SIID_MEDIAHDDVDRAM	equ 136 ;; HDDVD-RAM Media
SIID_MEDIABDROM		equ 137 ;; BluRay ROM Media
SIID_MEDIABDR		equ 138 ;; BluRay R Media
SIID_MEDIABDRE		equ 139 ;; BluRay RE Media (Rewriable and RAM)
SIID_CLUSTEREDDRIVE	equ 140 ;; Clustered disk
				;; 160+ are for Windows 7 icons
SIID_MAX_ICONS		equ 174


SIID_INVALID		equ (-1)

;SHSTDAPI
SHGetStockIconInfo proto _CType \
		  siid: SHSTOCKICONID,
		uFlags: UINT,
		  psii: ptr SHSTOCKICONINFO

endif ;; (NTDDI_VERSION >= NTDDI_VISTA)


if (NTDDI_VERSION LT NTDDI_WIN2K)
;SHSTDAPI_(BOOL)
SHGetDiskFreeSpaceA proto _CType \
	     pszVolume: LPCSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
SHGetDiskFreeSpaceW proto _CType \
	     pszVolume: LPCWSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
ifdef _UNICODE
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceW>
else
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceA>
endif ;; NOT UNICODE
endif ;; (NTDDI_VERSION LT NTDDI_WIN2K)

if (NTDDI_VERSION GE NTDDI_WIN2K)
SHGetDiskFreeSpace equ <SHGetDiskFreeSpaceEx>

;BOOL
SHGetDiskFreeSpaceExA proto _CType \
      pszDirectoryName: LPCSTR,
	 pqwFreeCaller: PTR ULARGE_INTEGER,
		pqwTot: PTR ULARGE_INTEGER,
	       pqwFree: PTR ULARGE_INTEGER
SHGetDiskFreeSpaceExW proto _CType \
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
SHGetNewLinkInfo equ <SHGetNewLinkInfoW>
else
SHGetNewLinkInfo equ <SHGetNewLinkInfoA>
endif ;; NOT UNICODE

SHGNLI_PIDL		equ 0x000000001 ;; pszLinkTo is a pidl
SHGNLI_PREFIXNAME	equ 0x000000002 ;; Make name "Shortcut to xxx"
SHGNLI_NOUNIQUE		equ 0x000000004 ;; don't do the unique name generation
if (_WIN32_IE GE 0x0501)
SHGNLI_NOLNK		equ 0x000000008 ;; don't add ".lnk" extension
endif ;; _WIN2_IE >= 0x0501
if (_WIN32_IE GE 0x0600)
SHGNLI_NOLOCNAME	equ 0x000000010 ;; use non localized (parsing) name from the target
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
SHGNLI_USEURLEXT	equ 0x000000020 ;; use ".url" extension instead of ".lnk"
endif
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)

;;
;; End SHGetFileInfo
;;

if (NTDDI_VERSION GE NTDDI_WIN2K)

;; Printer stuff
PRINTACTION_OPEN		equ 0
PRINTACTION_PROPERTIES		equ 1
PRINTACTION_NETINSTALL		equ 2
PRINTACTION_NETINSTALLLINK	equ 3
PRINTACTION_TESTPAGE		equ 4
PRINTACTION_OPENNETPRN		equ 5
PRINTACTION_DOCUMENTDEFAULTS	equ 6
PRINTACTION_SERVERPROPERTIES	equ 7


;SHSTDAPI_(BOOL)
SHInvokePrinterCommandA proto _CType \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCSTR,
		lpBuf2: LPCSTR,
		fModal: BOOL
SHInvokePrinterCommandW proto _CType \
		  hwnd: HWND,
	       uAction: UINT,
		lpBuf1: LPCWSTR,
		lpBuf2: LPCWSTR,
		fModal: BOOL
ifdef _UNICODE
SHInvokePrinterCommand equ <SHInvokePrinterCommandW>
else
SHInvokePrinterCommand equ <SHInvokePrinterCommandA>
endif ;; NOT UNICODE
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)

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
endif ;; _UNICODE
PRINT_PROP_FORCE_NAME	equ 0x01
endif ;; (NTDDI_VERSION GE NTDDI_VISTA)

endif ;; WINVER GE 0x0400

if (_WIN32_WINNT GE 0x0500) OR (_WIN32_WINDOWS GE 0x0500)

;;
;; The SHLoadNonloadedIconOverlayIdentifiers API causes the shell's
;; icon overlay manager to load any registered icon overlay
;; identifers that are not currently loaded.  This is useful if an
;; overlay identifier did not load at shell startup but is needed
;; and can be loaded at a later time.  Identifiers already loaded
;; are not affected.  Overlay identifiers implement the
;; IShellIconOverlayIdentifier interface.
;;
;; Returns:
;;	S_OK
;;
;SHSTDAPI
SHLoadNonloadedIconOverlayIdentifiers proto _CType

;;
;; The SHIsFileAvailableOffline API determines whether a file
;; or folder is available for offline use.
;;
;; Parameters:
;;     pwszPath		   file name to get info about
;;     pdwStatus		   (optional) OFFLINE_STATUS_* flags returned here
;;
;; Returns:
;;     S_OK		   File/directory is available offline, unless
;;			     OFFLINE_STATUS_INCOMPLETE is returned.
;;     E_INVALIDARG	   Path is invalid, or not a net path
;;     E_FAIL		   File/directory is not available offline
;;
;; Notes:
;;     OFFLINE_STATUS_INCOMPLETE is never returned for directories.
;;     Both OFFLINE_STATUS_LOCAL and OFFLINE_STATUS_REMOTE may be returned,
;;     indicating "open in both places." This is common when the server is online.
;;
;SHSTDAPI
SHIsFileAvailableOffline proto _CType \
	      pwszPath: LPCWSTR,
	     pdwStatus: LPDWORD

OFFLINE_STATUS_LOCAL	  equ 0x0001 ;; If open, it's open locally
OFFLINE_STATUS_REMOTE	  equ 0x0002 ;; If open, it's open remotely
OFFLINE_STATUS_INCOMPLETE equ 0x0004 ;; The local copy is currently imcomplete.
				     ;; The file will not be available offline
				     ;; until it has been synchronized.

endif

if (NTDDI_VERSION GE NTDDI_WINXP)
;;  sets the specified path to use the string resource
;;  as the UI instead of the file system name
;SHSTDAPI
SHSetLocalizedName proto _CType \
	       pszPath: LPCWSTR,
	  pszResModule: LPCWSTR,
		idsRes: SINT
endif ;; (NTDDI_VERSION >= NTDDI_WINXP)
if (NTDDI_VERSION GE NTDDI_VISTA)
;;  sets the specified path to use the string resource
;;  as the UI instead of the file system name
;SHSTDAPI
SHRemoveLocalizedName proto _CType \
	       pszPath: LPCWSTR
;;  gets the string resource for the specified path
SHGetLocalizedName proto _CType \
	       pszPath: LPCWSTR,
	  pszResModule: LPWSTR,
		   cch: UINT,
	       pidsRes: ptr SINT
endif ;; (NTDDI_VERSION >= NTDDI_VISTA)


;;====== ShellMessageBox ================================================

;; If lpcTitle is NULL, the title is taken from hWnd
;; If lpcText is NULL, this is assumed to be an Out Of Memory message
;; If the selector of lpcTitle or lpcText is NULL, the offset should be a
;;     string resource ID
;; The variable arguments must all be 32-bit values (even if fewer bits
;;     are actually used)
;; lpcText (or whatever string resource it causes to be loaded) should
;;     be a formatting string similar to wsprintf except that only the
;;     following formats are available:
;;	  %%		  formats to a single '%'
;;	  %nn%s		  the nn-th arg is a string which is inserted
;;	  %nn%ld	  the nn-th arg is a DWORD, and formatted decimal
;;	  %nn%lx	  the nn-th arg is a DWORD, and formatted hex
;;     note that lengths are allowed on the %s, %ld, and %lx, just
;;			  like wsprintf
;;

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
endif ;; !UNICODE

if (NTDDI_VERSION GE NTDDI_WIN2K)
;SHSTDAPI_(BOOL)
IsLFNDriveA proto _CType \
	       pszPath: LPCSTR
IsLFNDriveW proto _CType \
	       pszPath: LPCWSTR
ifdef _UNICODE
IsLFNDrive equ <IsLFNDriveW>
else
IsLFNDrive equ <IsLFNDriveA>
endif ;; !UNICODE
endif ;; (NTDDI_VERSION >= NTDDI_WIN2K)

if _WIN32_IE GE 0x0600
;STDAPI
SHEnumerateUnreadMailAccountsA proto _CType \
	      hKeyUser: HKEY,
	       dwIndex: DWORD,
	pszMailAddress: LPSTR,
	cchMailAddress: SINT
SHEnumerateUnreadMailAccountsW proto _CType \
	      hKeyUser: HKEY,
	       dwIndex: DWORD,
	pszMailAddress: LPWSTR,
	cchMailAddress: SINT
ifdef _UNICODE
SHEnumerateUnreadMailAccounts equ <SHEnumerateUnreadMailAccountsW>
else
SHEnumerateUnreadMailAccounts equ <SHEnumerateUnreadMailAccountsA>
endif ;; !UNICODE
SHGetUnreadMailCountA proto _CType \
	      hKeyUser: HKEY,
	pszMailAddress: LPCSTR,
	      pdwCount: LPDWORD,
	     pFileTime: ptr FILETIME,
pszShellExecuteCommand: LPSTR,
cchShellExecuteCommand: SINT
SHGetUnreadMailCountW proto _CType \
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
endif ;; !UNICODE
SHSetUnreadMailCountA proto _CType \
	pszMailAddress: LPCSTR,
	       dwCount: DWORD,
pszShellExecuteCommand: LPCSTR
SHSetUnreadMailCountW proto _CType \
	pszMailAddress: LPCWSTR,
	       dwCount: DWORD,
pszShellExecuteCommand: LPCWSTR
ifdef _UNICODE
SHSetUnreadMailCount equ <SHSetUnreadMailCountW>
else
SHSetUnreadMailCount equ <SHSetUnreadMailCountA>
endif ;; !UNICODE
endif ;; _WIN32_IE GE 0x0600

if (_WIN32_IE GE 0x0601)
;STDAPI_(BOOL)
SHTestTokenMembership proto _CType \
		hToken: HANDLE,
		 ulRID: ULONG
endif ;; (_WIN32_IE GE 0x0601)

if _WIN32_IE GE 0x0600

if (NTDDI_VERSION GE NTDDI_WINXP)
;SHSTDAPI
SHGetImageList proto _CType \
	    iImageList: SINT,
		  riid: REFIID,
		ppvObj: ptr PVOID
endif ;; (NTDDI_VERSION GE NTDDI_WINXP)

if (NTDDI_VERSION GE NTDDI_WINXP)
SHIL_LARGE		equ 0 ;; normally 32x32
SHIL_SMALL		equ 1 ;; normally 16x16
SHIL_EXTRALARGE		equ 2
SHIL_SYSSMALL		equ 3 ;; like SHIL_SMALL, but tracks system small icon metric correctly
if (NTDDI_VERSION GE NTDDI_VISTA)
SHIL_JUMBO		equ 4 ;; normally 256x256
SHIL_LAST		equ SHIL_JUMBO
else
SHIL_LAST		equ SHIL_SYSSMALL
endif ;; (NTDDI_VERSION GE NTDDI_VISTA)
endif ;; (NTDDI_VERSION GE NTDDI_WINXP)

;; Function call types for ntshrui folder sharing helpers
;typedef HRESULT (STDMETHODCALLTYPE *
FNCANSHAREFOLDERWT typedef proto _CType \
	       pszPath: LPCWSTR
PFNCANSHAREFOLDERW typedef ptr FNCANSHAREFOLDERWT
;typedef HRESULT (STDMETHODCALLTYPE *
FNSHOWSHAREFOLDERUIWT typedef proto _CType \
	    hwndParent: HWND,
	       pszPath: LPCWSTR
PFNSHOWSHAREFOLDERUIW typedef ptr FNSHOWSHAREFOLDERUIWT

endif ;;  _WIN32_IE GE 0x0600

ifdef __cplusplus
;;}
endif

ifndef _WIN64
;include <poppack.h>
endif

ifdef _MSC_VER
if _MSC_VER GE 1200
;pragma warning(pop)
endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
;; API for new Network Address Control

;; Instantiation
WC_NETADDRESS equ <L"msctls_netaddress">
;SHSTDAPI_(BOOL)
InitNetworkAddressControl proto _CType

;; Address Control Messages

;; NCM_GETADDRESS returns the type of address that is present in the
;; control (based on TBD Net Address flags).  If the input string has
;; not been validated using this message will force the validation of
;; the input string.  The WPARAM is a BOOL to determine to show the
;; balloon tip. The LPARAM is a pointer to the structure to fill in
;; with the address type and address string.
NCM_GETADDRESS	equ (WM_USER+1)
NetAddr_GetAddress macro hwnd, pv
    exitm<SNDMSG(hwnd,NCM_GETADDRESS,0,pv)>
    endm

NC_ADDRESS	STRUC
pAddrInfo	PVOID ? ; struct NET_ADDRESS_INFO_ * ;; defined in iphlpapi.h
PortNumber	dw ?
PrefixLength	db ?
NC_ADDRESS	ENDS
PNC_ADDRESS	typedef ptr NC_ADDRESS

;; NCM_SETALLOWTYPE sets the type of addresses that the control will allow.
;; The address flags are defined in iphlpapi.h
NCM_SETALLOWTYPE equ (WM_USER+2)
NetAddr_SetAllowType macro hwnd,addrMask
    exitm<SNDMSG(hwnd,NCM_SETALLOWTYPE,addrMask,0)>
    endm

;; NCM_GETALLOWTYPE returns the currently allowed type mask.
NCM_GETALLOWTYPE equ (WM_USER+3)
NetAddr_GetAllowType macro hwnd
    exitm<SNDMSG(hwnd,NCM_GETALLOWTYPE,0,0)>
    endm

;; NCM_DISPLAYERRORTIP displays the error balloon tip with the correct
;; error string (based on the last failure from the NCM_GETADDRESS call
NCM_DISPLAYERRORTIP equ (WM_USER+4)
NetAddr_DisplayErrorTip macro hwnd
    exitm<SNDMSG(hwnd,NCM_DISPLAYERRORTIP,0,0)>
    endm

endif ;; (NTDDI_VERSION GE NTDDI_VISTA)

if (NTDDI_VERSION GE NTDDI_VISTA)
;; Returns the type of media (CD, DVD, Blank, etc) that is in the drive.
;; dwMediaContent is set to a combination of ARCONTENT flags.
;STDAPI
SHGetDriveMedia proto _CType \
	      pszDrive: LPCWSTR,
       pdwMediaContent: LPDWORD
endif ;; (NTDDI_VERSION GE NTDDI_VISTA)

;; Windows Parental Controls (WPC) query apis
if (NTDDI_VERSION GE NTDDI_VISTA)
endif ;; (NTDDI_VERSION GE NTDDI_VISTA)

.list
endif	;; _INC_SHELLAPI
