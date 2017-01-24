ifndef __LIBC_INC
 include libc.inc
endif
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

_MAX_PATH	equ 260
_MAX_DRIVE	equ 3
_MAX_DIR	equ 256
_MAX_FNAME	equ 256
_MAX_EXT	equ 256

.xlist

_getdrive	PROTO
_chdrive	PROTO :SINT
_chdir		PROTO :LPSTR
_mkdir		PROTO :LPSTR
_rmdir		PROTO :LPSTR
_getcwd		PROTO :LPSTR, :SINT
_getdcwd	PROTO :SINT, :LPSTR, :SINT
_wchdir		PROTO :LPWSTR
_wmkdir		PROTO :LPWSTR
_wrmdir		PROTO :LPWSTR
_wgetcwd	PROTO :LPWSTR, :SINT
_wgetdcwd	PROTO :SINT, :LPWSTR, :SINT

externdef	_diskflag:DWORD

IFNDEF __PE__

;;;;;;;;;;;;;;; crtl

__allocwpath	PROTO :LPSTR

;;;;;;;;;;;;;;; drvinfo

MAXDRIVES	equ 26

_DI_ROOTDIR	equ 0x00020000	; _FB_ROOTDIR
_DI_CDROOM	equ 0x00080000	; _FB_CDROOM
_DI_VOLID	equ 0x00000008	; _A_VOLID

S_DISK		STRUC
di_flag		dd ?
di_time		dd ?
di_size		dq ?
di_name		db 32 dup(?)
S_DISK		ENDS

externdef	drvinfo:S_DISK	; [MAXDRIVES]

_disk_read	PROTO
_disk_exist	PROTO :UINT

;;;;;;;;;;;;;;;

WMAXPATH	equ 2048

_DISK_LOCAL	equ 0x0001
_DISK_FLOPPY	equ 0x0100
_DISK_NETWORK	equ 0x0200
_DISK_SUBST	equ 0x0400
_DISK_CDROOM	equ 0x0800

DRIVE_REMOVABLE equ 2	; _disk_type()
DRIVE_FIXED	equ 3
DRIVE_REMOTE	equ 4
DRIVE_CDROM	equ 5
DRIVE_RAMDISK	equ 6

externdef	cp_stdpath:	SBYTE
externdef	cp_stdmask:	SBYTE
externdef	fp_maskp:	LPSTR
externdef	fp_directory:	PVOID	; int (*fp_directory)(char *);
externdef	fp_fileblock:	PVOID	; int (*fp_fileblock)(char *, wfblk *);
externdef	OldErrorMode:	DWORD

validdrive	PROTO :SINT

scansub		PROTO :LPSTR, :LPSTR, :UINT
scan_files	PROTO :LPSTR
scan_directory	PROTO :UINT, :LPSTR
recursive	PROTO :LPSTR, :LPSTR, :LPSTR

_disk_init	PROTO :UINT
_disk_type	PROTO :UINT
_disk_test	PROTO :UINT
_disk_ready	PROTO :UINT
_disk_retry	PROTO :UINT
_disk_select	PROTO :LPSTR

GetVolumeID	PROTO :LPSTR, :LPSTR
GetFileSystemName PROTO :LPSTR, :LPSTR

ELSE
option		dllimport:<kernel32>
ENDIF
;;;;;;;;;;;;;;; kernel32.dll

SECURITY_ATTRIBUTES	STRUC SIZE_T
nLength			DWORD ?
lpSecurityDescriptor	SIZE_T ?
bInheritHandle		DWORD ?
SECURITY_ATTRIBUTES	ENDS
LPSECURITY_ATTRIBUTES	TYPEDEF PTR SECURITY_ATTRIBUTES

CP_ACP			equ 0
SEM_FAILCRITICALERRORS	equ 1

;UINT
SetErrorMode proto _CType \
	uMode:		UINT
;DWORD
GetLogicalDrives proto _CType
;int
MultiByteToWideChar proto _CType \
	CodePage:	UINT,
	dwFlags:	DWORD,
	lpMultiByteStr: LPSTR,	; Pointer to the character string to convert
	cbMultiByte:	SINT,	; byte count of the lpMultiByteStr parameter
	lpWideCharStr:	LPWSTR, ; Pointer to a buffer that receives the converted string
	cchWideChar:	SINT	; character count of lpWideCharStr
;DWORD
GetShortPathNameA proto _CType \
	lpszLongPath:	LPSTR,	; pointer to a null-terminated path string
	lpszShortPath:	LPSTR,	; pointer to a buffer to receive the
				; null-terminated short form of the path
	cchBuffer:	DWORD	; specifies the size of the buffer pointed
				; to by lpszShortPath
GetShortPathNameW proto _CType \
	lpszLongPath:	LPWSTR,
	lpszShortPath:	LPWSTR,
	cchBuffer:	DWORD
;DWORD
GetFullPathNameA proto _CType \
	lpFileName:	LPSTR,	; pointer to name of file to find path for
	nBufferLength:	DWORD,	; size, in characters, of path buffer
	lpBuffer:	LPSTR,	; pointer to path buffer
	lpFilePart:	LPSTR	; pointer to filename in path
GetFullPathNameW proto _CType \
	lpFileName:	LPWSTR,
	nBufferLength:	DWORD,
	lpBuffer:	LPWSTR,
	lpFilePart:	LPWSTR
;BOOL
RemoveDirectoryA proto _CType \
	lpPathName:	LPSTR	; pointer to directory to remove
RemoveDirectoryW proto _CType \
	lpPathName:	LPWSTR
;BOOL
CreateDirectoryA proto _CType \
	lpPathName:	LPSTR,	; pointer to directory path string
	lpSecurityAttributes:LPSECURITY_ATTRIBUTES
CreateDirectoryW proto _CType \
	lpPathName:	LPWSTR,
	lpSecurityAttributes:LPSECURITY_ATTRIBUTES
;BOOL
SetCurrentDirectoryA proto _CType \
	lpPathName:	LPSTR	; pointer to name of new current directory
SetCurrentDirectoryW proto _CType \
	lpPathName:	LPWSTR
;DWORD
GetCurrentDirectoryA proto _CType \
	nBufferLength:	DWORD,	; size, in characters, of directory buffer
	lpBuffer:	LPSTR	; pointer to buffer for current directory
GetCurrentDirectoryW proto _CType \
	nBufferLength:	DWORD,
	lpBuffer:	LPWSTR
;UINT
GetDriveTypeA proto _CType \
	lpRootPathName: LPSTR	; pointer to root path
GetDriveTypeW proto _CType \
	lpRootPathName: LPWSTR
;BOOL
GetDiskFreeSpaceA proto _CType \
	lpRootPathName:		LPSTR,	; pointer to root path
	lpSectorsPerCluster:	LPDWORD,; pointer to sectors per cluster
	lpBytesPerSector:	LPDWORD,; pointer to bytes per sector
	lpNumberOfFreeClusters: LPDWORD,; pointer to number of free clusters
	lpTotalNumberOfClusters:LPDWORD ; pointer to total number of clusters
GetDiskFreeSpaceW proto _CType \
	lpRootPathName:		LPWSTR,
	lpSectorsPerCluster:	LPDWORD,
	lpBytesPerSector:	LPDWORD,
	lpNumberOfFreeClusters: LPDWORD,
	lpTotalNumberOfClusters:LPDWORD
;BOOL
GetDiskFreeSpaceExA proto _CType \
	lpDirectoryName:	      LPSTR,	; pointer to the directory name
	lpFreeBytesAvailableToCaller: PTR QWORD,; receives the number of bytes on
						; disk available to the caller
	lpTotalNumberOfBytes:	      PTR QWORD,; receives the number of bytes on disk
	lpTotalNumberOfFreeBytes:     PTR QWORD ; receives the free bytes on disk
GetDiskFreeSpaceExW proto _CType \
	lpDirectoryName:	      LPWSTR,
	lpFreeBytesAvailableToCaller: PTR QWORD,
	lpTotalNumberOfBytes:	      PTR QWORD,
	lpTotalNumberOfFreeBytes:     PTR QWORD
;BOOL
GetVolumeInformationA proto _CType \
	lpRootPathName:		LPSTR,	; address of root directory of the file system
	lpVolumeNameBuffer:	LPSTR,	; address of name of the volume
	nVolumeNameSize:	DWORD,	; length of lpVolumeNameBuffer
	lpVolumeSerialNumber:	LPDWORD,; address of volume serial number
	lpMaximumComponentLength:LPDWORD,; address of system's maximum filename length
	lpFileSystemFlags:	LPDWORD,; address of file system flags
	lpFileSystemNameBuffer: LPSTR,	; address of name of file system
	nFileSystemNameSize:	DWORD	; length of lpFileSystemNameBuffer
GetVolumeInformationW proto _CType \
	lpRootPathName:		LPWSTR, ; address of root directory of the file system
	lpVolumeNameBuffer:	LPWSTR, ; address of name of the volume
	nVolumeNameSize:	DWORD,	; length of lpVolumeNameBuffer
	lpVolumeSerialNumber:	LPDWORD,; address of volume serial number
	lpMaximumComponentLength:LPDWORD,; address of system's maximum filename length
	lpFileSystemFlags:	LPDWORD,; address of file system flags
	lpFileSystemNameBuffer: LPWSTR, ; address of name of file system
	nFileSystemNameSize:	DWORD	; length of lpFileSystemNameBuffer

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

.list
