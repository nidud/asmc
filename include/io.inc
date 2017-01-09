ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_NFILE_		equ 20

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

FH_OPEN		equ 01h
FH_EOF		equ 02h
FH_CRLF		equ 04h
FH_PIPE		equ 08h
FH_NOINHERIT	equ 10h
FH_APPEND	equ 20h
FH_DEVICE	equ 40h
FH_TEXT		equ 80h

SEEK_SET	equ 0
SEEK_CUR	equ 1
SEEK_END	equ 2

FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS

_finddata_t	STRUC
ff_attrib	dd ?	; DWORD File attributes
ff_time_create	dd ?	; DWORD File creation time
ff_time_access	dd ?	; DWORD Last access time
ff_time_write	dd ?	; DWORD Last modification time
ff_size		dq ?	; QWORD File size
ff_name		db 260 dup(?)
_finddata_t	ENDS	; 284 byte

externdef	_nfile:DWORD
externdef	_osfile:BYTE
externdef	_osfhnd:HANDLE
externdef	_diskflag:DWORD

A_CREATE	equ 1 ; fails if exists
A_CREATETRUNC	equ 2 ; trunc if exists
A_OPEN		equ 3 ; fails if not exists
A_OPENCREATE	equ 4 ; open if exists or create
A_TRUNC		equ 5 ; fails if not exists

M_DELETE	equ 0x00010000
M_RDONLY	equ 0x80000000
M_WRONLY	equ 0x40000000
M_RDWR		equ M_RDONLY or M_WRONLY

_open		PROTO _CDecl :LPSTR, :UINT, :VARARG
_sopen		PROTO _CDecl :LPSTR, :UINT, :UINT, :VARARG
_read		PROTO :SINT, :PVOID, :SIZE_T
_creat		PROTO :LPSTR, :UINT
_close		PROTO :SINT
_lseek		PROTO :SINT, :SIZE_T, :UINT
_write		PROTO :SINT, :PVOID, :SIZE_T
_access		PROTO :LPSTR, :UINT
_isatty		PROTO :SINT
_eof		PROTO :SINT
_chsize		PROTO :SINT, :SIZE_T
_filelength	PROTO :SINT
_findfirst	PROTO :LPSTR, :PTR _finddata_t
_findnext	PROTO :HANDLE, :PTR _finddata_t
_findclose	PROTO :HANDLE
_tell		PROTO :SINT
_osopen		PROTO :LPSTR, :UINT, :UINT, :PVOID, :UINT, :UINT
_lseeki64	PROTO :SINT, :QWORD, :UINT
remove		PROTO :LPSTR
rename		PROTO :LPSTR, :LPSTR

osopen		PROTO :LPSTR, :UINT, :UINT, :UINT
osread		PROTO :SINT, :PVOID, :SIZE_T
oswrite		PROTO :SINT, :PVOID, :SIZE_T

getosfhnd	PROTO :SINT
osmaperr	PROTO

;;;;;;;;;;;;;;; crtl

getfattr	PROTO :LPTSTR
setfattr	PROTO :LPTSTR, :UINT
__FTToTime	PROTO :PTR FILETIME
filexist	PROTO :LPSTR

IFDEF __DZ__
externdef	console:DWORD
externdef	_diskflag:DWORD
ENDIF

;;;;;;;;;;;;;;; kernel32.dll

CREATE_NEW		equ 1
CREATE_ALWAYS		equ 2
OPEN_EXISTING		equ 3
OPEN_ALWAYS		equ 4
TRUNCATE_EXISTING	equ 5

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

INVALID_SET_FILE_POINTER	equ -1

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
LPSECURITY_ATTRIBUTES	TYPEDEF PTR SECURITY_ATTRIBUTES

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

WIN32_FIND_DATAW	STRUC ;SIZE_T
dwFileAttributes	DWORD ?
ftCreationTime		QWORD ?
ftLastAccessTime	QWORD ?
ftLastWriteTime		QWORD ?
nFileSizeHigh		DWORD ?
nFileSizeLow		DWORD ?
dwReserved0		DWORD ?
dwReserved1		DWORD ?
cFileName		SWORD 260 dup(?)
cAlternateFileName	SWORD 14 dup(?)
WIN32_FIND_DATAW	ENDS

;UINT
SetErrorMode proto \
	uMode:		UINT
;HANDLE
GetStdHandle proto \
	nStdHandle:	DWORD
;BOOL
CloseHandle proto \
	hObject:	HANDLE
;BOOL
SetFilePointer proto \
	hFile:			HANDLE,
	lDistanceToMove:	sdword,
	lpDistanceToMoveHigh:	ptr sdword,
	dwMoveMethod:		dword

ifdef __WXP__
;BOOL
SetFilePointerEx proto \
	hFile:			HANDLE,
	liDistanceToMove:	sqword, ; LARGE_INTEGER
	lpNewFilePointer:	ptr sqword,
	dwMoveMethod:		dword
;BOOL
GetFileSizeEx proto \
	hFile:		HANDLE,
	lpFileSize:	ptr sqword	; PLARGE_INTEGER
GetFileSize		equ <GetFileSizeEx>
else
GetFileSize proto \
	hFile:		HANDLE,
	lpFileSizeHigh: ptr dword
endif

;BOOL
ReadFile proto \
	hFile:			HANDLE, ; handle of file to read
	lpBuffer:		PVOID,	; pointer to buffer that receives data
	nNumberOfBytesToRead:	SIZE_T, ; number of bytes to read
	lpNumberOfBytesRead:	LPDWORD,; pointer to number of bytes read
	lpOverlapped:		PTR	; pointer to structure for data - LPOVERLAPPED
;BOOL
WriteFile proto \
	hFile:			HANDLE,
	lpBuffer:		PVOID,
	nNumberOfBytesToWrite:	DWORD,
	lpNumberOfBytesWritten: LPDWORD,
	lpOverlapped:		PTR	; LPOVERLAPPED
;BOOL
SetEndOfFile proto \
	hFile:		HANDLE
;UINT
GetFileType proto \
	hFile:		HANDLE ; _isatty()
;BOOL
GetFileTime proto \
	hFile:			HANDLE,		; handle to the file
	lpCreationTime:		PTR,; FILETIME	; address of creation time
	lpLastAccessTime:	PTR,; FILETIME	; address of last access time
	lpLastWriteTime:	PTR ; FILETIME	; address of last write time
;BOOL
SetFileTime proto \
	hFile:			HANDLE,		; handle to the file
	lpCreationTime:		PTR,; FILETIME	; time the file was created
	lpLastAccessTime:	PTR,; FILETIME	; time the file was last accessed
	lpLastWriteTime:	PTR ; FILETIME	; time the file was last written
;HANDLE
CreateFileA proto \
	lpFileName:		LPSTR,
	dwDesiredAccess:	DWORD,
	dwShareMode:		DWORD,
	lpSecurityAttributes:	LPSECURITY_ATTRIBUTES,
	dwCreationDisposition:	DWORD,
	dwFlagsAndAttributes:	DWORD,
	hTemplateFile:		HANDLE
CreateFileW proto \
	lpFileName:		LPWSTR,
	dwDesiredAccess:	DWORD,
	dwShareMode:		DWORD,
	lpSecurityAttributes:	LPSECURITY_ATTRIBUTES,
	dwCreationDisposition:	DWORD,
	dwFlagsAndAttributes:	DWORD,
	hTemplateFile:		HANDLE
;HANDLE
FindFirstFileA proto \
	lpFileName:	LPSTR,	; pointer to name of file to search for
	lpFindFileData: PTR WIN32_FIND_DATA ; pointer to returned information
FindFirstFileW proto \
	lpFileName:	LPWSTR,
	lpFindFileData: PTR WIN32_FIND_DATAW
;BOOL
FindNextFileA proto \
	hFindFile:	HANDLE, ; handle to search
	lpFindFileData: PTR WIN32_FIND_DATA ; pointer to structure for data on found file
FindNextFileW proto \
	hFindFile:	HANDLE,
	lpFindFileData: PTR WIN32_FIND_DATAW
;BOOL
FindClose proto \
	hFile:		HANDLE
;DWORD
GetFileAttributesA proto \
	lpFileName:	LPSTR	; pointer to the name of a file or directory
GetFileAttributesW proto \
	lpFileName:	LPWSTR
;BOOL
SetFileAttributesA proto \
	lpFileName:	LPSTR,	; pointer to filename
	dwFileAttributes:DWORD	; attributes to set
SetFileAttributesW proto \
	lpFileName:	LPWSTR,
	dwFileAttributes:DWORD
;BOOL
DeleteFileA proto \
	lpFileName:	LPSTR	; pointer to name of file to delete
DeleteFileW proto \
	lpFileName:	LPWSTR
;BOOL
MoveFileA proto \
	lpExistingFileName:	LPSTR,	; pointer to the name of the existing file
	lpNewFileName:		LPSTR	; pointer to the new name for the file
MoveFileW proto \
	lpExistingFileName:	LPWSTR,
	lpNewFileName:		LPWSTR
;BOOL
MoveFileExA proto \
	lpExistingFileName:	LPSTR,	; pointer to the name of the existing file
	lpNewFileName:		LPSTR,	; pointer to the new name for the file
	dwFlags:		DWORD	; flag that specifies how to move file
MoveFileExW proto \
	lpExistingFileName:	LPWSTR,
	lpNewFileName:		LPWSTR,
	dwFlags:		DWORD


ifdef _UNICODE
 FindFirstFile		equ <FindFirstFileW>
 FindNextFile		equ <FindNextFileW>
 SetFileAttributes	equ <SetFileAttributesW>
 GetFileAttributes	equ <GetFileAttributesW>
 DeleteFile		equ <DeleteFileW>
 MoveFile		equ <MoveFileW>
 MoveFileEX		equ <MoveFileExW>
 CreateFile		equ <CreateFileW>
else
 FindFirstFile		equ <FindFirstFileA>
 FindNextFile		equ <FindNextFileA>
 SetFileAttributes	equ <SetFileAttributesA>
 GetFileAttributes	equ <GetFileAttributesA>
 DeleteFile		equ <DeleteFileA>
 MoveFile		equ <MoveFileA>
 MoveFileEx		equ <MoveFileExA>
 CreateFile		equ <CreateFileA>
endif

.list
