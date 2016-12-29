ifndef __LIBC_INC
 include libc.inc
endif
.xlist

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

externdef	_argc:SIZE_T
externdef	_argv:SIZE_T
externdef	_environ:SIZE_T
externdef	_pgmptr:SIZE_T

abort		PROTO
exit		PROTO :DWORD
atol		PROTO :LPSTR
_atoi64		PROTO :LPSTR
qsort		PROTO :PVOID, :SIZE_T, :SIZE_T, :PVOID
getenv		PROTO :LPSTR
strtod		PROTO :LPSTR, :DWORD
system		PROTO :LPSTR
malloc		proto :SIZE_T
realloc		PROTO :PVOID, :SIZE_T
free		proto :PVOID

;;;;;;;;;;;;;;; kernel32.dll

;BOOL
Beep proto \
	dwFreq:		DWORD,	; sound frequency, in hertz
	dwDuration:	DWORD	; sound duration, in milliseconds
;VOID
Sleep proto \
	dwMilliseconds: DWORD	; sleep time in milliseconds
;DWORD
GetTickCount proto
;DWORD
GetLastError proto
;VOID
ExitProcess proto \
	uExitCode:	UINT	; exit code for all threads
;HINSTANCE
LoadLibraryA proto \
	lpLibFileName:	LPSTR	; address of filename of executable module
LoadLibraryW proto \
	lpLibFileName:	LPWSTR
;FARPROC
GetProcAddress proto \
	hModule:	HANDLE, ; handle to DLL module - HMODULE
	lpProcName:	LPSTR	; name of function
;BOOL
FreeLibrary proto \
	hLibModule:	HANDLE	; handle to loaded library module
;HMODULE
GetModuleHandleA proto \
	lpModuleName:	LPSTR	; address of module name to return handle
GetModuleHandleW proto	:LPWSTR
;DWORD
GetModuleFileNameA proto \
	hModule:	HANDLE, ; handle to module to find filename for
	lpFilename:	LPSTR,	; pointer to buffer to receive module path
	nSize:		DWORD	; size of buffer, in characters
GetModuleFileNameW proto :HANDLE, :LPWSTR, :DWORD
;LPSTR
GetCommandLineA proto
GetCommandLineW proto
;DWORD
SearchPathA proto \
	lpPath:		LPSTR,	; pointer to search path
	lpFileName:	LPSTR,	; pointer to filename
	lpExtension:	LPSTR,	; pointer to extension
	nBufferLength:	DWORD,	; size, in characters, of buffer
	lpBuffer:	LPSTR,	; pointer to buffer for found filename
	lpFilePart:	LPSTR	; pointer to pointer to file component
SearchPathW proto	:LPWSTR, :LPWSTR, :LPWSTR, :DWORD, :LPWSTR, :LPWSTR
;LPSTR
GetEnvironmentStringsA proto
GetEnvironmentStringsW proto
;DWORD
GetEnvironmentVariableA proto \
	lpName:		LPSTR,	; address of environment variable name
	lpBuffer:	LPSTR,	; address of buffer for variable value
	nSize:		DWORD	; size of buffer, in characters
GetEnvironmentVariableW proto	:LPSTR, :LPSTR, :DWORD
;BOOL
SetEnvironmentVariableA proto \
	lpName:		LPSTR,	; address of environment variable name
	lpValue:	LPSTR	; address of new value for variable
SetEnvironmentVariableW proto	:LPWSTR, :LPWSTR
;BOOL
FreeEnvironmentStringsA proto \
	lpszEnvironmentBlock:	LPSTR	; pointer to a block of environment strings
FreeEnvironmentStringsW proto	:LPWSTR
;DWORD
ExpandEnvironmentStringsA proto \
	lpSrc:		LPSTR,
	lpDst:		LPSTR,
	nSize:		DWORD
ExpandEnvironmentStringsW proto :LPWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
 LoadLibrary		equ <LoadLibraryW>
 GetModuleHandle	equ <GetModuleHandleW>
 GetCommandLine		equ <GetCommandLineW>
 GetModuleFileName	equ <GetModuleFileNameW>
 SearchPath		equ <SearchPathW>
 GetEnvironmentStrings	equ <GetEnvironmentStringsW>
 GetEnvironmentVariable equ <GetEnvironmentVariableW>
 SetEnvironmentVariable equ <SetEnvironmentVariableW>
 FreeEnvironmentStrings equ <FreeEnvironmentStringsW>
 ExpandEnvironmentStrings equ <ExpandEnvironmentStringsW>
else
 LoadLibrary		equ <LoadLibraryA>
 GetModuleHandle	equ <GetModuleHandleA>
 GetCommandLine		equ <GetCommandLineA>
 GetModuleFileName	equ <GetModuleFileNameA>
 SearchPath		equ <SearchPathA>
 GetEnvironmentStrings	equ <GetEnvironmentStringsA>
 GetEnvironmentVariable equ <GetEnvironmentVariableA>
 SetEnvironmentVariable equ <SetEnvironmentVariableA>
 FreeEnvironmentStrings equ <FreeEnvironmentStringsA>
 ExpandEnvironmentStrings equ <ExpandEnvironmentStringsA>
endif

.list
