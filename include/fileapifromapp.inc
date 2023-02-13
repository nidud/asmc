ifndef _FILEAPIFROMAPP_H_
define _FILEAPIFROMAPP_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc
include fileapi.inc

if ((_WIN32_WINNT ge _WIN32_WINNT_WIN10) and (NTDDI_VERSION ge NTDDI_WIN10_RS3))
CopyFileFromAppW proto WINAPI :LPCWSTR, :LPCWSTR, :BOOL
CreateDirectoryFromAppW proto WINAPI :LPCWSTR, :LPSECURITY_ATTRIBUTES
CreateFileFromAppW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :LPSECURITY_ATTRIBUTES, :DWORD, :DWORD, :HANDLE
CreateFile2FromAppW proto WINAPI :LPCWSTR, :DWORD, :DWORD, :DWORD, :LPCREATEFILE2_EXTENDED_PARAMETERS
DeleteFileFromAppW proto WINAPI :LPCWSTR
FindFirstFileExFromAppW proto WINAPI :LPCWSTR, :FINDEX_INFO_LEVELS, :LPVOID, :FINDEX_SEARCH_OPS, :LPVOID, :DWORD
GetFileAttributesExFromAppW proto WINAPI :LPCWSTR, :GET_FILEEX_INFO_LEVELS, :LPVOID
MoveFileFromAppW proto WINAPI :LPCWSTR, :LPCWSTR
RemoveDirectoryFromAppW proto WINAPI :LPCWSTR
ReplaceFileFromAppW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :LPVOID, :LPVOID
SetFileAttributesFromAppW proto WINAPI :LPCWSTR, :DWORD
endif

endif
