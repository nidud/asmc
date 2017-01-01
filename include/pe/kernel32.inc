ifndef __LIBC_INC
 include libc.inc
endif

	.xlist

ifdef	__PE__
	option	dllimport:<kernel32>
endif

; Global Memory Flags

GMEM_FIXED		equ 0x0000
GMEM_MOVEABLE		equ 0x0002
GMEM_NOCOMPACT		equ 0x0010
GMEM_NODISCARD		equ 0x0020
GMEM_ZEROINIT		equ 0x0040
GMEM_MODIFY		equ 0x0080
GMEM_DISCARDABLE	equ 0x0100
GMEM_NOT_BANKED		equ 0x1000
GMEM_SHARE		equ 0x2000
GMEM_DDESHARE		equ 0x2000
GMEM_NOTIFY		equ 0x4000
GMEM_LOWER		equ GMEM_NOT_BANKED
GMEM_VALID_FLAGS	equ 0x7F72
GMEM_INVALID_HANDLE	equ 0x8000

GHND			equ GMEM_MOVEABLE or GMEM_ZEROINIT
GPTR			equ GMEM_FIXED or GMEM_ZEROINIT

; Flags returned by GlobalFlags (in addition to GMEM_DISCARDABLE)

GMEM_DISCARDED		equ 0x4000
GMEM_LOCKCOUNT		equ 0x00FF

GlobalAlloc proto,
	uFlags:		UINT,
	dwBytes:	SIZE_T
GlobalFree proto hMem:	HANDLE
GlobalReAlloc proto,
	hMem:		HANDLE,
	dwBytes:	SIZE_T,
	uFlags:		UINT
GlobalSize  proto hMem: HANDLE
GlobalFlags proto hMem: HANDLE
GlobalHandle proto,pMem:PVOID
GlobalLock  proto hMem: HANDLE
GlobalUnlock proto,hMem:HANDLE
GlobalCompact proto,
	dwMinFree:	SIZE_T
GlobalFix   proto hMem: HANDLE
GlobalUnfix proto hMem: HANDLE
GlobalWire  proto hMem: HANDLE
GlobalUnWire proto hMem:HANDLE
GlobalMemoryStatus proto,
	lpBuffer:	PTR MEMORYSTATUS
GlobalMemoryStatusEx proto,
	lpBuffer:	PTR MEMORYSTATUSEX

; Local Memory Flags

LMEM_FIXED		equ 0x0000
LMEM_MOVEABLE		equ 0x0002
LMEM_NOCOMPACT		equ 0x0010
LMEM_NODISCARD		equ 0x0020
LMEM_ZEROINIT		equ 0x0040
LMEM_MODIFY		equ 0x0080
LMEM_DISCARDABLE	equ 0x0F00
LMEM_VALID_FLAGS	equ 0x0F72
LMEM_INVALID_HANDLE	equ 0x8000

LHND			equ LMEM_MOVEABLE OR LMEM_ZEROINIT
LPTR			equ LMEM_FIXED OR LMEM_ZEROINIT

NONZEROLHND		equ LMEM_MOVEABLE
NONZEROLPTR		equ LMEM_FIXED

; Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE)

LMEM_DISCARDED		equ 0x4000
LMEM_LOCKCOUNT		equ 0x00FF

LocalAlloc proto uFlags:UINT,
	uBytes:		SIZE_T
LocalReAlloc proto hMem:HANDLE,
	uBytes:		SIZE_T,
	uFlags:		UINT
LocalLock   proto hMem: HANDLE
LocalHandle proto pMem: PVOID
LocalUnlock proto hMem: HANDLE
LocalSize   proto hMem: HANDLE
LocalFlags  proto hMem: HANDLE
LocalFree   proto hMem: HANDLE
LocalShrink proto hMem: HANDLE,
	cbNewSize:	SIZE_T
LocalCompact proto,
	uMinFree:	SIZE_T


PROCESS_HEAP_REGION		equ 0x0001
PROCESS_HEAP_UNCOMMITTED_RANGE	equ 0x0002
PROCESS_HEAP_ENTRY_BUSY		equ 0x0004
PROCESS_HEAP_ENTRY_MOVEABLE	equ 0x0010
PROCESS_HEAP_ENTRY_DDESHARE	equ 0x0020

HEAP_ZERO_MEMORY	equ 00000008h

PROCESS_HEAP_ENTRY	STRUC SIZE_T
lpData			PVOID ?
cbData			DWORD ?
cbOverhead		BYTE ?
iRegionIndex		BYTE ?
wFlags			WORD ?
UNION
    STRUC ;Block
	hMem		HANDLE ?
	dwReserved	DWORD 3 dup(?)
    ENDS
    STRUC ;Region
	dwCommittedSize DWORD ?
	dwUnCommittedSize DWORD ?
	lpFirstBlock	PVOID ?
	lpLastBlock	PVOID ?
    ENDS
ENDS
PROCESS_HEAP_ENTRY	ENDS

GetProcessHeap proto
GetProcessHeaps proto,
	NumberOfHeaps:	DWORD,
	ProcessHeaps:	PVOID
HeapCreate proto,
	flOptions:	DWORD,
	dwInitialSize:	SIZE_T,
	dwMaximumSize:	SIZE_T
HeapDestroy proto hHeap:HANDLE
HeapAlloc proto hHeap:	HANDLE,
	dwFlags:	DWORD,
	dwBytes:	SIZE_T
HeapReAlloc proto hHeap:HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID,
	dwBytes:	SIZE_T
HeapFree proto hHeap:	HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID
HeapSize proto hHeap:	HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID
HeapValidate proto,
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID
HeapCompact proto hHeap:HANDLE,
	dwFlags:	DWORD
HeapLock proto hHeap:	HANDLE
HeapUnlock proto hHeap: HANDLE
HeapWalk proto hHeap:	HANDLE,
	lpEntry:	PTR LPPROCESS_HEAP_ENTRY


PAGE_NOACCESS		equ 0x01
PAGE_READONLY		equ 0x02
PAGE_READWRITE		equ 0x04
PAGE_WRITECOPY		equ 0x08
PAGE_EXECUTE		equ 0x10
PAGE_EXECUTE_READ	equ 0x20
PAGE_EXECUTE_READWRITE	equ 0x40
PAGE_EXECUTE_WRITECOPY	equ 0x80
PAGE_GUARD		equ 0x0100
PAGE_NOCACHE		equ 0x0200
PAGE_WRITECOMBINE	equ 0x0400

MEM_COMMIT		equ 0x1000
MEM_RESERVE		equ 0x2000
MEM_DECOMMIT		equ 0x4000
MEM_RELEASE		equ 0x8000
MEM_FREE		equ 0x00010000
MEM_PRIVATE		equ 0x00020000
MEM_MAPPED		equ 0x00040000
MEM_RESET		equ 0x00080000
MEM_TOP_DOWN		equ 0x00100000
MEM_4MB_PAGES		equ 0x80000000
SEC_FILE		equ 0x00800000
SEC_IMAGE		equ 0x01000000
SEC_VLM			equ 0x02000000
SEC_RESERVE		equ 0x04000000
SEC_COMMIT		equ 0x08000000
SEC_NOCACHE		equ 0x10000000
MEM_IMAGE		equ SEC_IMAGE

MEMORY_BASIC_INFORMATION STRUC SIZE_T
BaseAddress		PVOID ?
AllocationBase		PVOID ?
AllocationProtect	DWORD ?
RegionSize		SIZE_T ?
State			DWORD ?
Protect			DWORD ?
_Type			DWORD ?
MEMORY_BASIC_INFORMATION ENDS

VirtualAlloc proto,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flAllocationType:DWORD,
	flProtect:	DWORD

VirtualFree proto,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	dwFreeType:	DWORD

VirtualProtect proto,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flNewProtect:	DWORD,
	lpflOldProtect: PTR DWORD

VirtualQuery proto,
	lpAddress:	PVOID,
	lpBuffer:	PTR MEMORY_BASIC_INFORMATION,
	dwLength:	SIZE_T

VirtualAllocEx proto,
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flAllocationType:DWORD,
	flProtect:	DWORD

VirtualFreeEx proto,
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	dwFreeType:	DWORD

VirtualProtectEx proto,
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flNewProtect:	DWORD,
	lpflOldProtect: PTR DWORD

VirtualQueryEx proto,
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	lpBuffer:	PTR MEMORY_BASIC_INFORMATION,
	dwLength:	SIZE_T

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ENABLE_WINDOW_INPUT	equ 8
ENABLE_MOUSE_INPUT	equ 16

FOREGROUND_BLUE		equ 01h
FOREGROUND_GREEN	equ 02h
FOREGROUND_RED		equ 04h
FOREGROUND_INTENSITY	equ 08h
BACKGROUND_BLUE		equ 10h
BACKGROUND_GREEN	equ 20h
BACKGROUND_RED		equ 40h
BACKGROUND_INTENSITY	equ 80h

SWP_NOSIZE		equ 01h
SWP_NOACTIVATE		equ 10h
SWP_NOZORDER		equ 04h

CHAR_INFO	STRUCT
 Char		dw ?
 Attributes	dw ?
CHAR_INFO	ENDS

COORD		STRUCT
 x		dw ?
 y		dw ?
COORD		ENDS

SMALL_RECT	STRUCT
 Left		dw ?
 Top		dw ?
 Right		dw ?
 Bottom		dw ?
SMALL_RECT	ENDS

CONSOLE_SCREEN_BUFFER_INFO STRUCT
 dwSize			COORD <>
 dwCursorPosition	COORD <>
 wAttributes		dw ?
 srWindow		SMALL_RECT <>
 dwMaximumWindowSize	COORD <>
CONSOLE_SCREEN_BUFFER_INFO ENDS

CONSOLE_CURSOR_INFO STRUCT
 dwSize		dd ?
 bVisible	dd ?
CONSOLE_CURSOR_INFO ENDS

FillConsoleOutputAttribute	PROTO :PTR, :DWORD, :DWORD, :DWORD, :PTR
FlushConsoleInputBuffer		PROTO :PTR
GetConsoleCursorInfo		PROTO :PTR, :PTR
GetConsoleMode			PROTO :PTR, :PTR
GetConsoleScreenBufferInfo	PROTO :PTR, :PTR
GetConsoleWindow		PROTO
GetForegroundWindow		PROTO
GetLargestConsoleWindowSize	PROTO :PTR
ReadConsoleOutputAttribute	PROTO :PTR, :PTR, :PTR, :COORD, :PTR
SetConsoleActiveScreenBuffer	PROTO :PTR
SetConsoleCP			PROTO :PTR
SetConsoleCtrlHandler		PROTO :PTR, :PTR
SetConsoleCursor		PROTO :PTR, :PTR
SetConsoleCursorInfo		PROTO :PTR, :PTR
SetConsoleCursorPosition	PROTO :PTR, :DWORD
SetConsoleMode			PROTO :PTR, :DWORD
SetConsoleOutputCP		PROTO :PTR
SetConsoleScreenBufferSize	PROTO :PTR, :COORD
SetConsoleTextAttribute		PROTO :PTR, :PTR
SetConsoleWindowInfo		PROTO :PTR, :PTR, :PTR
SetWindowPos			PROTO :PTR, :PTR, :PTR, :PTR, :PTR, :PTR, :PTR
WriteConsoleOutputAttribute	PROTO :PTR, :PTR, :DWORD, :COORD, :PTR

GetModuleHandleA		PROTO :SIZE_T
GetModuleHandleW		PROTO :SIZE_T
FillConsoleOutputCharacterA	PROTO :PTR, :DWORD, :DWORD, :DWORD, :PTR
FillConsoleOutputCharacterW	PROTO :PTR, :PTR, :PTR, :PTR, :PTR
ReadConsoleOutputA		PROTO :PTR, :PTR, :COORD, :PTR, :PTR
ReadConsoleOutputW		PROTO :PTR, :PTR, :PTR, :PTR, :PTR
ReadConsoleOutputCharacterA	PROTO :PTR, :PTR, :PTR, :COORD, :PTR
ReadConsoleOutputCharacterW	PROTO :PTR, :PTR, :PTR, :PTR, :PTR
SetConsoleTitleA		PROTO :PTR
SetConsoleTitleW		PROTO :PTR
WriteConsoleOutputA		PROTO :PTR, :PTR, :COORD, :PTR, :PTR
WriteConsoleOutputW		PROTO :PTR, :PTR, :PTR, :PTR, :PTR
WriteConsoleOutputCharacterA	PROTO :PTR, :PTR, :PTR, :COORD, :PTR
WriteConsoleOutputCharacterW	PROTO :PTR, :PTR, :PTR, :PTR, :PTR

ifdef __UNICODE__
 GetModuleHandle		equ <GetModuleHandleW>
 FillConsoleOutputCharacter	equ <FillConsoleOutputCharacterW>
 ReadConsoleOutput		equ <ReadConsoleOutputW>
 ReadConsoleOutputCharacter	equ <ReadConsoleOutputCharacterW>
 SetConsoleTitle		equ <SetConsoleTitleW>
 WriteConsoleOutput		equ <WriteConsoleOutputW>
 WriteConsoleOutputCharacter	equ <WriteConsoleOutputCharacterW>
else
 GetModuleHandle		equ <GetModuleHandleA>
 FillConsoleOutputCharacter	equ <FillConsoleOutputCharacterA>
 ReadConsoleOutput		equ <ReadConsoleOutputA>
 ReadConsoleOutputCharacter	equ <ReadConsoleOutputCharacterA>
 SetConsoleTitle		equ <SetConsoleTitleA>
 WriteConsoleOutput		equ <WriteConsoleOutputA>
 WriteConsoleOutputCharacter	equ <WriteConsoleOutputCharacterA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CP_ACP			equ 0
SEM_FAILCRITICALERRORS	equ 1

externdef		OldErrorMode:SIZE_T

SetErrorMode		PROTO :SIZE_T
GetLogicalDrives	PROTO
MultiByteToWideChar	PROTO :PTR, :PTR, :PTR, :PTR, :PTR, :PTR

GetShortPathNameA	PROTO :PTR, :PTR, :PTR
GetFullPathNameA	PROTO :PTR, :PTR, :PTR, :PTR
RemoveDirectoryA	PROTO :PTR
CreateDirectoryA	PROTO :PTR, :PTR
SetCurrentDirectoryA	PROTO :PTR
GetCurrentDirectoryA	PROTO :PTR, :PTR
GetDriveTypeA		PROTO :PTR
GetDiskFreeSpaceA	PROTO :PTR, :PTR, :PTR, :PTR, :PTR
GetDiskFreeSpaceExA	PROTO :PTR, :PTR, :PTR, :PTR
GetVolumeInformationA	PROTO :PTR, :PTR, :PTR, :PTR, :PTR, :PTR, :PTR, :PTR

GetShortPathNameW	PROTO :PTR, :PTR, :PTR
GetFullPathNameW	PROTO :PTR, :PTR, :PTR, :PTR
RemoveDirectoryW	PROTO :PTR
CreateDirectoryW	PROTO :PTR, :PTR
SetCurrentDirectoryW	PROTO :PTR
GetCurrentDirectoryW	PROTO :PTR, :PTR
GetDriveTypeW		PROTO :PTR
GetDiskFreeSpaceW	PROTO :PTR, :PTR, :PTR, :PTR, :PTR
GetDiskFreeSpaceExW	PROTO :PTR, :PTR, :PTR, :PTR
GetVolumeInformationW	PROTO :PTR, :PTR, :PTR, :PTR, :PTR, :PTR, :PTR, :PTR

ifdef __UNICODE__
 GetShortPathName	equ <GetShortPathNameW>
 GetCurrentDirectory	equ <GetCurrentDirectoryW>
 SetCurrentDirectory	equ <SetCurrentDirectoryW>
 GetFullPathName	equ <GetFullPathNameW>
 CreateDirectory	equ <CreateDirectoryW>
 RemoveDirectory	equ <RemoveDirectoryW>
 GetDriveType		equ <GetDriveTypeW>
 GetDiskFreeSpace	equ <GetDiskFreeSpaceW>
 GetDiskFreeSpaceEx	equ <GetDiskFreeSpaceExW>
 GetVolumeInformation	equ <GetVolumeInformationW>
else
 GetShortPathName	equ <GetShortPathNameA>
 GetCurrentDirectory	equ <GetCurrentDirectoryA>
 SetCurrentDirectory	equ <SetCurrentDirectoryA>
 GetFullPathName	equ <GetFullPathNameA>
 CreateDirectory	equ <CreateDirectoryA>
 RemoveDirectory	equ <RemoveDirectoryA>
 GetDriveType		equ <GetDriveTypeA>
 GetDiskFreeSpace	equ <GetDiskFreeSpaceA>
 GetDiskFreeSpaceEx	equ <GetDiskFreeSpaceExA>
 GetVolumeInformation	equ <GetVolumeInformationA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

GetLastError	proto

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_A_RDONLY	equ 01h
_A_HIDDEN	equ 02h
_A_SYSTEM	equ 04h
_A_VOLID	equ 08h
_A_SUBDIR	equ 10h
_A_ARCH		equ 20h
_A_NORMAL	equ 80h

_A_TEMPORARY	equ 0100h
_A_SPARSE_FILE	equ 0200h
_A_REPARSEPOINT equ 0400h
_A_COMPRESSED	equ 0800h
_A_OFFLINE	equ 1000h
_A_NOT_INDEXED	equ 2000h
_A_ENCRYPTED	equ 4000h

FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS

S_WFBLK		STRUC
wf_attrib	dd ?	; DWORD File attributes
wf_timecreate	dq ?	; QWORD File creation time
wf_timeaccess	dq ?	; QWORD Last access time
wf_time		dq ?	; QWORD Last modification time
wf_size		dq ?	; QWORD File size
wf_reserved	dq ?
wf_name		db 260 dup(?)
wf_shortname	db 14 dup(?)
S_WFBLK		ENDS	;  318 byte

S_WFBLKW	STRUC
wf_attrib	dd ?	; DWORD File attributes
wf_timecreate	dq ?	; QWORD File creation time
wf_timeaccess	dq ?	; QWORD Last access time
wf_time		dq ?	; QWORD Last modification time
wf_size		dq ?	; QWORD File size
wf_reserved	dq ?
wf_name		dw 260 dup(?)
wf_shortname	dw 14 dup(?)
S_WFBLKW	ENDS

A_CREATE		equ 1 ; fails if exists
A_CREATETRUNC		equ 2 ; trunc if exists
A_OPEN			equ 3 ; fails if not exists
A_OPENCREATE		equ 4 ; open if exists or create
A_TRUNC			equ 5 ; fails if not exists

CREATE_NEW		equ 1
CREATE_ALWAYS		equ 2
OPEN_EXISTING		equ 3
OPEN_ALWAYS		equ 4
TRUNCATE_EXISTING	equ 5

M_DELETE		equ 00010000h
M_RDONLY		equ 80000000h
M_WRONLY		equ 40000000h
M_RDWR			equ M_RDONLY or M_WRONLY

GENERIC_WRITE		equ M_WRONLY
GENERIC_READ		equ M_RDONLY
SHARE_READ		equ 1
SHARE_WRITE		equ 2

FILE_TYPE_UNKNOWN	equ 0
FILE_TYPE_DISK		equ 1
FILE_TYPE_CHAR		equ 2
FILE_TYPE_PIPE		equ 3
FILE_TYPE_REMOTE	equ 8000h

STD_INPUT_HANDLE	equ -10
STD_OUTPUT_HANDLE	equ -11
STD_ERROR_HANDLE	equ -12

SEM_FAILCRITICALERRORS	equ 1

FILE_ATTRIBUTE_READONLY		equ 1h
FILE_ATTRIBUTE_HIDDEN		equ 2h
FILE_ATTRIBUTE_SYSTEM		equ 4h
FILE_ATTRIBUTE_DIRECTORY	equ 10h
FILE_ATTRIBUTE_ARCHIVE		equ 20h
FILE_ATTRIBUTE_NORMAL		equ 80h
FILE_ATTRIBUTE_TEMPORARY	equ 100h
FILE_ATTRIBUTE_COMPRESSED	equ 800h

FILE_FLAG_WRITE_THROUGH		equ 80000000h	; CreateFile()
FILE_FLAG_OVERLAPPED		equ 40000000h
FILE_FLAG_NO_BUFFERING		equ 20000000h
FILE_FLAG_RANDOM_ACCESS		equ 10000000h
FILE_FLAG_SEQUENTIAL_SCAN	equ 8000000h
FILE_FLAG_DELETE_ON_CLOSE	equ 4000000h
FILE_FLAG_BACKUP_SEMANTICS	equ 2000000h
FILE_FLAG_POSIX_SEMANTICS	equ 1000000h

SECURITY_ATTRIBUTES	STRUC SIZE_T
nLength			DWORD ?
lpSecurityDescriptor	SIZE_T ?
bInheritHandle		DWORD ?
SECURITY_ATTRIBUTES	ENDS

SetErrorMode		PROTO :SIZE_T
GetStdHandle		PROTO :SIZE_T
CloseHandle		PROTO :SIZE_T
SetFilePointer		PROTO :PTR, :PTR, :PTR, :PTR
ifdef __WXP__
 SetFilePointerEx	PROTO :PTR, :QWORD, :PTR, :PTR
 GetFileSizeEx		PROTO :PTR, :PTR
 GetFileSize		equ <GetFileSizeEx>
else
GetFileSize		PROTO :PTR, :PTR
endif

ReadFile		PROTO :PTR, :PTR, :PTR, :PTR, :PTR
WriteFile		PROTO :PTR, :PTR, :PTR, :PTR, :PTR
SetEndOfFile		PROTO :PTR ; BOOL(HANDLE hFile)
GetFileType		PROTO :PTR ; _isatty()
FindClose		PROTO :PTR
GetFileTime		PROTO :PTR, :PTR, :PTR, :PTR
SetFileTime		PROTO :PTR, :PTR, :PTR, :PTR

CreateFileA		PROTO :LPSTR, :DWORD, :DWORD, :PVOID, :DWORD, :DWORD, :HANDLE
FindFirstFileA		PROTO :PTR, :PTR
FindNextFileA		PROTO :PTR, :PTR
GetFileAttributesA	PROTO :PTR
SetFileAttributesA	PROTO :PTR, :PTR
DeleteFileA		PROTO :PTR
MoveFileA		PROTO :PTR, :PTR

CreateFileW		PROTO :LPSTR, :DWORD, :DWORD, :PVOID, :DWORD, :DWORD, :HANDLE
FindFirstFileW		PROTO :PTR, :PTR
FindNextFileW		PROTO :PTR, :PTR
GetFileAttributesW	PROTO :PTR
SetFileAttributesW	PROTO :PTR, :PTR
DeleteFileW		PROTO :PTR
MoveFileW		PROTO :PTR, :PTR

ifdef __UNICODE__
 FindFirstFile		equ <FindFirstFileW>
 FindNextFile		equ <FindNextFileW>
 SetFileAttributes	equ <SetFileAttributesW>
 GetFileAttributes	equ <GetFileAttributesW>
 DeleteFile		equ <DeleteFileW>
 MoveFile		equ <MoveFileW>
 CreateFile		equ <CreateFileW>
else
 FindFirstFile		equ <FindFirstFileA>
 FindNextFile		equ <FindNextFileA>
 SetFileAttributes	equ <SetFileAttributesA>
 GetFileAttributes	equ <GetFileAttributesA>
 DeleteFile		equ <DeleteFileA>
 MoveFile		equ <MoveFileA>
 CreateFile		equ <CreateFileA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MAPVK_VK_TO_VSC		equ 0
MAPVK_VSC_TO_VK		equ 1

KEY_EVENT		equ 1
MOUSE_EVENT		equ 2
MAXINPUTRECORDS		equ 100

KEY_EVENT_RECORD	STRUCT
 bKeyDown		dd ?
 wRepeatCount		dw ?
 wVirtualKeyCode	dw ?
 wVirtualScanCode	dw ?
 Char			dw ?
 dwControlKeyState	dd ?
KEY_EVENT_RECORD	ENDS

MOUSE_EVENT_RECORD	STRUCT
 dwMousePosition	COORD <>
 dwButtonState		dd ?
 dwControlKeyState	dd ?
 dwEventFlags		dd ?
MOUSE_EVENT_RECORD	ENDS

WINDOW_BUFFER_SIZE_RECORD STRUCT
 dwSize			COORD <>
WINDOW_BUFFER_SIZE_RECORD ENDS

MENU_EVENT_RECORD	STRUCT
 dwCommandId		dd ?
MENU_EVENT_RECORD	ENDS

FOCUS_EVENT_RECORD	STRUCT
 bSetFocus		dd ?
FOCUS_EVENT_RECORD	ENDS

INPUT_RECORD		STRUCT
 EventType		dw ?
 two_byte_alignment	dw ?
 UNION
  KeyEvent		KEY_EVENT_RECORD <>
  MouseEvent		MOUSE_EVENT_RECORD <>
  WindowBufferSizeEvent WINDOW_BUFFER_SIZE_RECORD <>
  MenuEvent		MENU_EVENT_RECORD <>
  FocusEvent		FOCUS_EVENT_RECORD <>
 ENDS
INPUT_RECORD		ENDS

VK_LSHIFT		equ 0A0h
VK_RSHIFT		equ 0A1h
VK_LCONTROL		equ 0A2h
VK_RCONTROL		equ 0A3h
VK_ESCAPE		equ 01Bh

GetAsyncKeyState		PROTO :PTR
GetKeyState			PROTO :PTR
GetNumberOfConsoleInputEvents	PROTO :PTR, :PTR

ReadConsoleInputA		PROTO :PTR, :PTR, :PTR, :PTR
PeekConsoleInputA		PROTO :PTR, :PTR, :PTR, :PTR
MapVirtualKeyA			PROTO :PTR, :PTR
WriteConsoleInputA		PROTO :PTR, :PTR, :PTR, :PTR

ReadConsoleInputW		PROTO :PTR, :PTR, :PTR, :PTR
PeekConsoleInputW		PROTO :PTR, :PTR, :PTR, :PTR
MapVirtualKeyW			PROTO :PTR, :PTR
WriteConsoleInputW		PROTO :PTR, :PTR, :PTR, :PTR

ifdef __UNICODE__
 ReadConsoleInput		equ <ReadConsoleInputW>
 PeekConsoleInput		equ <PeekConsoleInputW>
 WriteConsoleInput		equ <WriteConsoleInputW>
 MapVirtualKey			equ <MapVirtualKeyW>
else
 ReadConsoleInput		equ <ReadConsoleInputA>
 PeekConsoleInput		equ <PeekConsoleInputA>
 WriteConsoleInput		equ <WriteConsoleInputA>
 MapVirtualKey			equ <MapVirtualKeyA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

WIN32_FIND_DATA		STRUC ;SIZE_T
dwFileAttributes	DWORD ?
ftCreationTime		QWORD ?
ftLastAccessTime	QWORD ?
ftLastWriteTime		QWORD ?
nFileSizeHigh		DWORD ?
nFileSizeLow		DWORD ?
dwReserved0		DWORD ?
dwReserved1		DWORD ?
cFileName		SBYTE 260 dup(?)
cAlternateFileName	SBYTE 14 dup(?)
WIN32_FIND_DATA		ENDS

GetCurrentProcess	PROTO
GetExitCodeProcess	PROTO :PTR,:PTR
CreatePipe		PROTO :PTR,:PTR,:PTR,:PTR
DuplicateHandle		PROTO :PTR,:PTR,:PTR,:PTR,:PTR,:PTR,:PTR
WaitForSingleObject	PROTO :PTR,:PTR

GetStartupInfoA		PROTO :PTR
CreateProcessA		PROTO :LPSTR,:LPSTR,:PTR,:PTR,:DWORD,:DWORD,:PTR,:PTR,:PTR,:PTR
ShellExecuteA		PROTO :PTR,:PTR,:PTR,:PTR,:PTR,:PTR

GetStartupInfoW		PROTO :PTR
CreateProcessW		PROTO :PTR,:PTR,:PTR,:PTR,:PTR,:PTR,:PTR,:PTR,:PTR,:PTR
ShellExecuteW		PROTO :PTR,:PTR,:PTR,:PTR,:PTR,:PTR

ifdef __UNICODE__
 GetStartupInfo		equ <GetStartupInfoW>
 CreateProcess		equ <CreateProcessW>
 ShellExecute		equ <ShellExecuteW>
else
 GetStartupInfo		equ <GetStartupInfoA>
 CreateProcess		equ <CreateProcessA>
 ShellExecute		equ <ShellExecuteA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

wvsprintfA		PROTO :SIZE_T, :SIZE_T, :SIZE_T

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Beep			PROTO :SIZE_T, :SIZE_T
Sleep			PROTO :SIZE_T	; sleep time in milliseconds
GetTickCount		PROTO
GetLastError		PROTO
ExitProcess		PROTO :SIZE_T

LoadLibraryA		PROTO :SIZE_T
GetProcAddress		PROTO :SIZE_T, :SIZE_T
FreeLibrary		PROTO :SIZE_T

GetModuleHandleA	PROTO :SIZE_T
GetModuleFileNameA	proto :SIZE_T,:SIZE_T,:SIZE_T
GetCommandLineA		PROTO
SearchPathA		PROTO :SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T
GetEnvironmentStringsA	PROTO
GetEnvironmentVariableA PROTO :SIZE_T, :SIZE_T, :SIZE_T
SetEnvironmentVariableA PROTO :SIZE_T, :SIZE_T
FreeEnvironmentStringsA PROTO :SIZE_T

GetModuleHandleW	PROTO :SIZE_T
GetCommandLineW		PROTO
SearchPathW		PROTO :SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T,:SIZE_T
GetEnvironmentStringsW	PROTO
GetEnvironmentVariableW PROTO :SIZE_T, :SIZE_T, :SIZE_T
SetEnvironmentVariableW PROTO :SIZE_T, :SIZE_T
FreeEnvironmentStringsW PROTO :SIZE_T

ExpandEnvironmentStringsA PROTO :SIZE_T, :SIZE_T, :SIZE_T

ifdef __UNICODE__
 GetModuleHandle	equ <GetModuleHandleW>
 GetCommandLine		equ <GetCommandLineW>
 SearchPath		equ <SearchPathW>
 GetEnvironmentStrings	equ <GetEnvironmentStringsW>
 GetEnvironmentVariable equ <GetEnvironmentVariableW>
 SetEnvironmentVariable equ <SetEnvironmentVariableW>
 FreeEnvironmentStrings equ <FreeEnvironmentStringsW>
else
 GetModuleHandle	equ <GetModuleHandleA>
 GetCommandLine		equ <GetCommandLineA>
 SearchPath		equ <SearchPathA>
 GetEnvironmentStrings	equ <GetEnvironmentStringsA>
 GetEnvironmentVariable equ <GetEnvironmentVariableA>
 SetEnvironmentVariable equ <SetEnvironmentVariableA>
 ExpandEnvironmentStrings equ <ExpandEnvironmentStringsA>
 FreeEnvironmentStrings equ <FreeEnvironmentStringsA>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SYSTEMTIME		STRUC
wYear			dw ?
wMonth			dw ?
wDayOfWeek		dw ?
wDay			dw ?
wHour			dw ?
wMinute			dw ?
wSecond			dw ?
wMilliseconds		dw ?
SYSTEMTIME		ENDS

TIME_ZONE_INFORMATION	STRUC
Bias			DD ?
StandardName		DW 32 dup(?)
StandardDate		SYSTEMTIME <>
StandardBias		DD ?
DaylightName		DW 32 dup(?)
DaylightDate		SYSTEMTIME <>
DaylightBias		DD ?
TIME_ZONE_INFORMATION	ENDS

GetLocalTime		PROTO :PTR SYSTEMTIME
FileTimeToSystemTime	PROTO :PTR FILETIME, :PTR SYSTEMTIME
SystemTimeToFileTime	PROTO :PTR SYSTEMTIME, :PTR FILETIME
FileTimeToLocalFileTime PROTO :PTR FILETIME, :PTR FILETIME
LocalFileTimeToFileTime PROTO :PTR FILETIME, :PTR FILETIME
GetTimeFormatA		PROTO :DWORD, :DWORD, :PTR, :LPSTR, :PTR, :DWORD
GetTimeFormatW		PROTO :DWORD, :DWORD, :PTR, :LPSTR, :PTR, :DWORD
GetDateFormatA		PROTO :DWORD, :DWORD, :PTR, :LPSTR, :PTR, :DWORD
GetDateFormatW		PROTO :DWORD, :DWORD, :PTR, :LPSTR, :PTR, :DWORD
GetUserDefaultLCID	PROTO
GetTimeZoneInformation	PROTO :PTR

ifdef __UNICODE__
 GetTimeFormat	equ	<GetTimeFormatW>
 GetDateFormat	equ	<GetDateFormatW>
else
 GetTimeFormat	equ	<GetTimeFormatA>
 GetDateFormat	equ	<GetDateFormatA>
endif

; BOOL - 16-bit date and time
DosDateTimeToFileTime	PROTO wFatDate:PTR, wFatTime:PTR, :PTR FILETIME
FileTimeToDosDateTime	PROTO :PTR FILETIME, lpFatDate:PTR, lpFatTime:PTR

.list
