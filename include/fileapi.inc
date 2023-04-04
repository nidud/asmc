ifndef _APISETFILE_
define _APISETFILE_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

.pragma comment(lib, kernel32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

define CREATE_NEW          1
define CREATE_ALWAYS       2
define OPEN_EXISTING       3
define OPEN_ALWAYS         4
define TRUNCATE_EXISTING   5

define INVALID_FILE_SIZE (0xFFFFFFFF)
define INVALID_SET_FILE_POINTER (-1)
define INVALID_FILE_ATTRIBUTES (-1)

CompareFileTime proto WINAPI :ptr, :ptr
CreateDirectoryA proto WINAPI :LPCSTR, :LPSECURITY_ATTRIBUTES
CreateDirectoryW proto WINAPI :LPCWSTR, :LPSECURITY_ATTRIBUTES

ifdef _UNICODE
define CreateDirectory  <CreateDirectoryW>
else
define CreateDirectory  <CreateDirectoryA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

CreateFileA proto WINAPI :LPCSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :HANDLE
CreateFileW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :HANDLE

ifdef _UNICODE
define CreateFile  <CreateFileW>
else
define CreateFile  <CreateFileA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
DefineDosDeviceW proto WINAPI :DWORD, :LPCWSTR, :LPCWSTR

ifdef _UNICODE
define DefineDosDevice  <DefineDosDeviceW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

DeleteFileA proto WINAPI :LPCSTR
DeleteFileW proto WINAPI :LPCWSTR

ifdef _UNICODE
define DeleteFile  <DeleteFileW>
else
define DeleteFile  <DeleteFileA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

DeleteVolumeMountPointW proto WINAPI :LPCWSTR

ifdef _UNICODE
define DeleteVolumeMountPoint  <DeleteVolumeMountPointW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

FileTimeToLocalFileTime proto WINAPI :ptr, :LPFILETIME

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

FindClose proto WINAPI :HANDLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

FindCloseChangeNotification proto WINAPI :HANDLE
FindFirstChangeNotificationA proto WINAPI :LPCSTR, :BOOL, :DWORD
FindFirstChangeNotificationW proto WINAPI :LPCWSTR, :BOOL, :DWORD

ifdef _UNICODE
define FindFirstChangeNotification  <FindFirstChangeNotificationW>
else
define FindFirstChangeNotification  <FindFirstChangeNotificationA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

FindFirstFileA proto WINAPI :LPCSTR, :LPWIN32_FIND_DATAA
FindFirstFileW proto WINAPI :LPCWSTR, :LPWIN32_FIND_DATAW

ifdef _UNICODE
define FindFirstFile  <FindFirstFileW>
else
define FindFirstFile  <FindFirstFileA>
endif

if (_WIN32_WINNT ge 0x0400)

FindFirstFileExA proto WINAPI :LPCSTR, :FINDEX_INFO_LEVELS, :LPVOID, :FINDEX_SEARCH_OPS, :LPVOID, :DWORD
FindFirstFileExW proto WINAPI :LPCWSTR, :FINDEX_INFO_LEVELS, :LPVOID, :FINDEX_SEARCH_OPS, :LPVOID, :DWORD

ifdef _UNICODE
define FindFirstFileEx  <FindFirstFileExW>
else
define FindFirstFileEx  <FindFirstFileExA>
endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

FindFirstVolumeW proto WINAPI :LPWSTR, :DWORD

ifdef _UNICODE
define FindFirstVolume <FindFirstVolumeW>
endif

FindNextChangeNotification proto WINAPI :HANDLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

FindNextFileA proto WINAPI :HANDLE, :LPWIN32_FIND_DATAA
FindNextFileW proto WINAPI :HANDLE, :LPWIN32_FIND_DATAW

ifdef _UNICODE
define FindNextFile  <FindNextFileW>
else
define FindNextFile  <FindNextFileA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

FindNextVolumeW proto WINAPI :HANDLE, :LPWSTR, :DWORD

ifdef _UNICODE
define FindNextVolume <FindNextVolumeW>
endif

FindVolumeClose proto WINAPI :HANDLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

FlushFileBuffers proto WINAPI :HANDLE
GetDiskFreeSpaceA proto WINAPI :LPCSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD
GetDiskFreeSpaceW proto WINAPI :LPCWSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD

ifdef _UNICODE
define GetDiskFreeSpace  <GetDiskFreeSpaceW>
else
define GetDiskFreeSpace  <GetDiskFreeSpaceA>
endif

GetDiskFreeSpaceExA proto WINAPI :LPCSTR, :PULARGE_INTEGER, :PULARGE_INTEGER, :PULARGE_INTEGER
GetDiskFreeSpaceExW proto WINAPI :LPCWSTR, :PULARGE_INTEGER, :PULARGE_INTEGER, :PULARGE_INTEGER

ifdef _UNICODE
define GetDiskFreeSpaceEx  <GetDiskFreeSpaceExW>
else
define GetDiskFreeSpaceEx  <GetDiskFreeSpaceExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

DISK_SPACE_INFORMATION  struct
ActualTotalAllocationUnits ULONGLONG ?
ActualAvailableAllocationUnits ULONGLONG ?
ActualPoolUnavailableAllocationUnits ULONGLONG ?
CallerTotalAllocationUnits ULONGLONG ?
CallerAvailableAllocationUnits ULONGLONG ?
CallerPoolUnavailableAllocationUnits ULONGLONG ?
UsedAllocationUnits     ULONGLONG ?
TotalReservedAllocationUnits ULONGLONG ?
VolumeStorageReserveAllocationUnits ULONGLONG ?
AvailableCommittedAllocationUnits ULONGLONG ?
PoolAvailableAllocationUnits ULONGLONG ?
SectorsPerAllocationUnit DWORD ?
BytesPerSector          DWORD ?
DISK_SPACE_INFORMATION  ends

GetDiskSpaceInformationA proto WINAPI :LPCSTR, :ptr
GetDiskSpaceInformationW proto WINAPI :LPCWSTR, :ptr

ifdef _UNICODE
define GetDiskSpaceInformation  <GetDiskSpaceInformationW>
else
define GetDiskSpaceInformation  <GetDiskSpaceInformationA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetDriveTypeA proto WINAPI :LPCSTR
GetDriveTypeW proto WINAPI :LPCWSTR

ifdef _UNICODE
define GetDriveType  <GetDriveTypeW>
else
define GetDriveType  <GetDriveTypeA>
endif

_WIN32_FILE_ATTRIBUTE_DATA struct
dwFileAttributes        DWORD ?
ftCreationTime          FILETIME <>
ftLastAccessTime        FILETIME <>
ftLastWriteTime         FILETIME <>
nFileSizeHigh           DWORD ?
nFileSizeLow            DWORD ?
_WIN32_FILE_ATTRIBUTE_DATA ends
WIN32_FILE_ATTRIBUTE_DATA typedef _WIN32_FILE_ATTRIBUTE_DATA
LPWIN32_FILE_ATTRIBUTE_DATA typedef ptr _WIN32_FILE_ATTRIBUTE_DATA

GetFileAttributesA proto WINAPI :LPCSTR
GetFileAttributesW proto WINAPI :LPCWSTR

ifdef _UNICODE
define GetFileAttributes  <GetFileAttributesW>
else
define GetFileAttributes  <GetFileAttributesA>
endif

GetFileAttributesExA proto WINAPI :LPCSTR, :GET_FILEEX_INFO_LEVELS, :LPVOID
GetFileAttributesExW proto WINAPI :LPCWSTR, :GET_FILEEX_INFO_LEVELS, :LPVOID

ifdef _UNICODE
define GetFileAttributesEx  <GetFileAttributesExW>
else
define GetFileAttributesEx  <GetFileAttributesExA>
endif

_BY_HANDLE_FILE_INFORMATION struct
dwFileAttributes        DWORD ?
ftCreationTime          FILETIME <>
ftLastAccessTime        FILETIME <>
ftLastWriteTime         FILETIME <>
dwVolumeSerialNumber    DWORD ?
nFileSizeHigh           DWORD ?
nFileSizeLow            DWORD ?
nNumberOfLinks          DWORD ?
nFileIndexHigh          DWORD ?
nFileIndexLow           DWORD ?
_BY_HANDLE_FILE_INFORMATION ends
BY_HANDLE_FILE_INFORMATION typedef _BY_HANDLE_FILE_INFORMATION
PBY_HANDLE_FILE_INFORMATION typedef ptr _BY_HANDLE_FILE_INFORMATION
LPBY_HANDLE_FILE_INFORMATION typedef ptr _BY_HANDLE_FILE_INFORMATION

GetFileInformationByHandle proto WINAPI :HANDLE, :LPBY_HANDLE_FILE_INFORMATION

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetFileSize proto WINAPI :HANDLE, :LPDWORD

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetFileSizeEx proto WINAPI :HANDLE, :PLARGE_INTEGER
GetFileType proto WINAPI :HANDLE

if (_WIN32_WINNT ge 0x0600)

GetFinalPathNameByHandleA proto WINAPI :HANDLE, :LPSTR, :DWORD, :DWORD
GetFinalPathNameByHandleW proto WINAPI :HANDLE, :LPWSTR, :DWORD, :DWORD

ifdef _UNICODE
define GetFinalPathNameByHandle  <GetFinalPathNameByHandleW>
else
define GetFinalPathNameByHandle  <GetFinalPathNameByHandleA>
endif

endif

GetFileTime proto WINAPI :HANDLE, :LPFILETIME, :LPFILETIME, :LPFILETIME
GetFullPathNameW proto WINAPI :LPCWSTR, :DWORD, :LPWSTR, :ptr

ifdef _UNICODE
define GetFullPathName  <GetFullPathNameW>
endif

GetFullPathNameA proto WINAPI :LPCSTR, :DWORD, :LPSTR, :ptr

ifndef _UNICODE
define GetFullPathName <GetFullPathNameA>
endif

GetLogicalDrives proto WINAPI

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

GetLogicalDriveStringsW proto WINAPI :DWORD, :LPWSTR

ifdef _UNICODE
define GetLogicalDriveStrings  <GetLogicalDriveStringsW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetLongPathNameA proto WINAPI :LPCSTR, :LPSTR, :DWORD

ifndef _UNICODE
define GetLongPathName <GetLongPathNameA>
endif

GetLongPathNameW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
define GetLongPathName <GetLongPathNameW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

GetShortPathNameW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
define GetShortPathName  <GetShortPathNameW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetTempFileNameW proto WINAPI :LPCWSTR, :LPCWSTR, :UINT, :LPWSTR

ifdef _UNICODE
define GetTempFileName  <GetTempFileNameW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
if (_WIN32_WINNT ge 0x0600)
GetVolumeInformationByHandleW proto WINAPI :HANDLE, :LPWSTR, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPWSTR, :DWORD
endif

GetVolumeInformationW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPWSTR, :DWORD

ifdef _UNICODE
define GetVolumeInformation  <GetVolumeInformationW>
endif

GetVolumePathNameW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
define GetVolumePathName  <GetVolumePathNameW>
endif

LocalFileTimeToFileTime proto WINAPI :ptr, :LPFILETIME
LockFile proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :DWORD
LockFileEx proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :DWORD, :LPOVERLAPPED

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

QueryDosDeviceW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
define QueryDosDevice  <QueryDosDeviceW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ReadFile proto WINAPI :HANDLE, :LPVOID, :DWORD, :LPDWORD, :LPOVERLAPPED
ReadFileEx proto WINAPI :HANDLE, :LPVOID, :DWORD, :LPOVERLAPPED, :LPOVERLAPPED_COMPLETION_ROUTINE
ReadFileScatter proto WINAPI :HANDLE, :FILE_SEGMENT_ELEMENT, :DWORD, :LPDWORD, :LPOVERLAPPED
RemoveDirectoryA proto WINAPI :LPCSTR
RemoveDirectoryW proto WINAPI :LPCWSTR

ifdef _UNICODE
define RemoveDirectory  <RemoveDirectoryW>
else
define RemoveDirectory  <RemoveDirectoryA>
endif

SetEndOfFile proto WINAPI :HANDLE
SetFileAttributesA proto WINAPI :LPCSTR, :DWORD
SetFileAttributesW proto WINAPI :LPCWSTR, :DWORD

ifdef _UNICODE
define SetFileAttributes  <SetFileAttributesW>
else
define SetFileAttributes  <SetFileAttributesA>
endif

if (_WIN32_WINNT ge 0x0600)
SetFileInformationByHandle proto WINAPI :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :LPVOID, :DWORD
endif

SetFilePointer proto WINAPI :HANDLE, :LONG, :PLONG, :DWORD
SetFilePointerEx proto WINAPI :HANDLE, :LARGE_INTEGER, :PLARGE_INTEGER, :DWORD
SetFileTime proto WINAPI :HANDLE, :ptr, :ptr, :ptr

if _WIN32_WINNT ge 0x0501
SetFileValidData proto WINAPI :HANDLE, :LONGLONG
endif

UnlockFile proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :DWORD
UnlockFileEx proto WINAPI :HANDLE, :DWORD, :DWORD, :DWORD, :LPOVERLAPPED
WriteFile proto WINAPI :HANDLE, :LPCVOID, :DWORD, :LPDWORD, :LPOVERLAPPED
WriteFileEx proto WINAPI :HANDLE, :LPCVOID, :DWORD, :LPOVERLAPPED, :LPOVERLAPPED_COMPLETION_ROUTINE
WriteFileGather proto WINAPI :HANDLE, :FILE_SEGMENT_ELEMENT, :DWORD, :LPDWORD, :LPOVERLAPPED
GetTempPathW proto WINAPI :DWORD, :LPWSTR

ifdef _UNICODE
define GetTempPath  <GetTempPathW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetVolumeNameForVolumeMountPointW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

ifdef _UNICODE
define GetVolumeNameForVolumeMountPoint  <GetVolumeNameForVolumeMountPointW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if (_WIN32_WINNT ge 0x0501)

GetVolumePathNamesForVolumeNameW proto WINAPI :LPCWSTR, :LPWCH, :DWORD, :PDWORD

ifdef _UNICODE
define GetVolumePathNamesForVolumeName  <GetVolumePathNamesForVolumeNameW>
endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

if (_WIN32_WINNT ge 0x0602)

_CREATEFILE2_EXTENDED_PARAMETERS struct
dwSize                  DWORD ?
dwFileAttributes        DWORD ?
dwFileFlags             DWORD ?
dwSecurityQosFlags      DWORD ?
lpSecurityAttributes    LPSECURITY_ATTRIBUTES ?
hTemplateFile           HANDLE ?
_CREATEFILE2_EXTENDED_PARAMETERS ends
CREATEFILE2_EXTENDED_PARAMETERS typedef _CREATEFILE2_EXTENDED_PARAMETERS
PCREATEFILE2_EXTENDED_PARAMETERS typedef ptr _CREATEFILE2_EXTENDED_PARAMETERS
LPCREATEFILE2_EXTENDED_PARAMETERS typedef ptr _CREATEFILE2_EXTENDED_PARAMETERS

CreateFile2 proto WINAPI :LPCWSTR, :DWORD, :DWORD, :DWORD, :LPCREATEFILE2_EXTENDED_PARAMETERS

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if (_WIN32_WINNT ge 0x0600)

SetFileIoOverlappedRange proto WINAPI :HANDLE, :PUCHAR, :ULONG

endif

if _WIN32_WINNT ge 0x0501

GetCompressedFileSizeA proto WINAPI :LPCSTR, :LPDWORD
GetCompressedFileSizeW proto WINAPI :LPCWSTR, :LPDWORD

ifdef _UNICODE
define GetCompressedFileSize  <GetCompressedFileSizeW>
else
define GetCompressedFileSize  <GetCompressedFileSizeA>
endif

endif

if (_WIN32_WINNT ge 0x0501)

.enum STREAM_INFO_LEVELS {
    FindStreamInfoStandard,
    FindStreamInfoMaxInfoLevel
    }

_WIN32_FIND_STREAM_DATA struct
StreamSize              LARGE_INTEGER <>
cStreamName             WCHAR MAX_PATH + 36 dup(?)
_WIN32_FIND_STREAM_DATA ends
WIN32_FIND_STREAM_DATA  typedef _WIN32_FIND_STREAM_DATA
PWIN32_FIND_STREAM_DATA typedef ptr _WIN32_FIND_STREAM_DATA

FindFirstStreamW proto WINAPI :LPCWSTR, :STREAM_INFO_LEVELS, :LPVOID, :DWORD
FindNextStreamW proto WINAPI :HANDLE, :LPVOID

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
AreFileApisANSI proto WINAPI
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetTempPathA proto WINAPI :DWORD, :LPSTR

ifndef _UNICODE
define GetTempPath  <GetTempPathA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if _WIN32_WINNT ge 0x0600

FindFirstFileNameW proto WINAPI :LPCWSTR, :DWORD, :LPDWORD, :PWSTR
FindNextFileNameW proto WINAPI :HANDLE, :LPDWORD, :PWSTR

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetVolumeInformationA proto WINAPI :LPCSTR, :LPSTR, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPSTR, :DWORD

ifndef _UNICODE
define GetVolumeInformation  <GetVolumeInformationA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetTempFileNameA proto WINAPI :LPCSTR, :LPCSTR, :UINT, :LPSTR

ifndef _UNICODE
define GetTempFileName  <GetTempFileNameA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

SetFileApisToOEM proto WINAPI
SetFileApisToANSI proto WINAPI

endif
endif
