ifndef __LIBC_INC
 include libc.inc
endif

.xlist
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

_P_WAIT		equ 0
_P_NOWAIT	equ 1
_OLD_P_OVERLAY	equ 2
_P_NOWAITO	equ 3
_P_DETACH	equ 4

; CreationFlags: CREATE_NEW_CONSOLE, DETACHED_PROCESS

system		PROTO lpCommand:LPSTR
process		PROTO lpProgram:LPSTR, lpCommand:LPSTR, CreationFlags:DWORD

externdef	errorlevel:DWORD	; Exit Code from GetExitCodeProcess
externdef	comspec_type:DWORD	; 1 if CMD.EXE, 0 if %comspec%

externdef	__pCommandCom:LPSTR	; "C:\Windows\system32\cmd.exe"
externdef	__pCommandArg:LPSTR	; "/C "

__initcomspec	proto	; Auto install..

CreateConsole	PROTO :LPSTR, :DWORD
CreateBatch	PROTO :LPSTR, :DWORD, :DWORD
ExecuteSection	PROTO :LPSTR
CmdIsExe	PROTO :LPSTR
getcomspec	PROTO :dword

;;;;;;;;;;;;;;;;;;;;;;; kernel32.dll
IFDEF __PE__
option	dllimport:<kernel32>
ENDIF

INFINITE		equ -1
STARTF_USESHOWWINDOW	equ 001h
STARTF_USESTDHANDLES	equ 100h
SW_HIDE			equ 0
DUPLICATE_SAME_ACCESS	equ 2
STATUS_PENDING		equ 103h
STILL_ACTIVE		equ STATUS_PENDING
CREATE_NEW_CONSOLE	equ 10h
DETACHED_PROCESS	equ 8h

PROCESS_QUERY_INFORMATION equ 0400h
PROCESS_VM_READ		equ 0010h

SECURITY_ATTRIBUTES	STRUC SIZE_T
nLength			dd ?
lpSecurityDescriptor	SIZE_T ?
bInheritHandle		dd ?
SECURITY_ATTRIBUTES	ENDS

PROCESS_INFORMATION	STRUC SIZE_T
hProcess		SIZE_T ?
hThread			SIZE_T ?
dwProcessId		dd ?
dwThreadId		dd ?
PROCESS_INFORMATION	ENDS

STARTUPINFO		STRUC SIZE_T
cb			dd ?
lpReserved		SIZE_T ?
lpDesktop		SIZE_T ?
lpTitle			SIZE_T ?
dwX			dd ?
dwY			dd ?
dwXSize			dd ?
dwYSize			dd ?
dwXCountChars		dd ?
dwYCountChars		dd ?
dwFillAttribute		dd ?
dwFlags			dd ?
wShowWindow		dw ?
cbReserved2		dw ?
lpReserved2		SIZE_T ?
hStdInput		SIZE_T ?
hStdOutput		SIZE_T ?
hStdError		SIZE_T ?
STARTUPINFO		ENDS

LPSTARTUPINFO		TYPEDEF PTR STARTUPINFO
PHANDLE			TYPEDEF PTR HANDLE
LPSECURITY_ATTRIBUTES	TYPEDEF PTR SECURITY_ATTRIBUTES
LPPROCESS_INFORMATION	TYPEDEF PTR PROCESS_INFORMATION

; HANDLE
GetCurrentProcess proto _CType
; BOOL
GetExitCodeProcess proto _CType \
	hProcess:	HANDLE, ; handle to the process
	lpExitCode:	LPDWORD ; address to receive termination status
; BOOL
CreatePipe proto _CType \
	hReadPipe:	PHANDLE,		; pointer to read handle
	hWritePipe:	PHANDLE,		; pointer to write handle
	lpPipeAttributes:LPSECURITY_ATTRIBUTES, ; pointer to security attributes
	nSize:		DWORD			; pipe size
; BOOL
DuplicateHandle proto _CType \
	hSourceProcessHandle:	HANDLE, ; handle to the source process
	hSourceHandle:		HANDLE, ; handle to duplicate
	hTargetProcessHandle:	HANDLE, ; handle to process to duplicate to
	lpTargetHandle:		PHANDLE,; pointer to duplicate handle
	dwDesiredAccess:	DWORD,	; access for duplicate handle
	bInheritHandle:		DWORD,	; (BOOL) handle inheritance flag
	dwOptions:		DWORD	; optional actions
; DWORD
WaitForSingleObject proto _CType \
	hHandle:	HANDLE, ; handle to object to wait for
	dwMilliseconds: DWORD	; time-out interval in milliseconds
; VOID
GetStartupInfoA proto _CType \
	lpStartupInfo:	LPSTARTUPINFO	; address of STARTUPINFO structure
GetStartupInfoW proto _CType :LPSTARTUPINFO
; BOOL
CreateProcessA proto _CType \
	lpApplicationName:	LPSTR,; pointer to name of executable module
	lpCommandLine:		LPSTR, ; pointer to command line string
	lpProcessAttributes:	LPSECURITY_ATTRIBUTES,
	lpThreadAttributes:	LPSECURITY_ATTRIBUTES,
	bInheritHandles:	DWORD,	; (BOOL) handle inheritance flag
	dwCreationFlags:	DWORD,	; creation flags
	lpEnvironment:		PVOID, ; pointer to new environment block
	lpCurrentDirectory:	LPSTR,; pointer to current directory name
	lpStartupInfo:		LPSTARTUPINFO,
	lpProcessInformation:	LPPROCESS_INFORMATION
CreateProcessW proto _CType :PTR, :PTR, :PTR, :PTR, :DWORD, :DWORD, :PTR, :PTR, : PTR, :PTR
; HINSTANCE
ShellExecuteA proto _CType \
	hwnd:		HANDLE, ; HWND
	lpOperation:	LPSTR,
	lpFile:		LPSTR,
	lpParameters:	LPSTR,
	lpDirectory:	LPSTR,
	nShowCmd:	DWORD
ShellExecuteW proto _CType :HANDLE, :LPSTR, :LPSTR, :LPSTR, :LPSTR, :DWORD

IFDEF _UNICODE
 GetStartupInfo		equ <GetStartupInfoW>
 CreateProcess		equ <CreateProcessW>
 ShellExecute		equ <ShellExecuteW>
ELSE
 GetStartupInfo		equ <GetStartupInfoA>
 CreateProcess		equ <CreateProcessA>
 ShellExecute		equ <ShellExecuteA>
ENDIF

.list
