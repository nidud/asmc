ifndef _WOW64APISET_H_
define _WOW64APISET_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

if not defined(RC_INVOKED)
if _WIN32_WINNT ge 0x0501 or defined(WINBASE_DECLARE_GET_SYSTEM_WOW64_DIRECTORY)

Wow64DisableWow64FsRedirection proto WINAPI :ptr
Wow64RevertWow64FsRedirection proto WINAPI :PVOID

endif
endif

if (_WIN32_WINNT ge 0x0501)
IsWow64Process proto WINAPI :HANDLE, :PBOOL
endif

if not defined(RC_INVOKED)
if _WIN32_WINNT ge 0x0501 or defined(WINBASE_DECLARE_GET_SYSTEM_WOW64_DIRECTORY)

GetSystemWow64DirectoryA proto WINAPI :LPSTR, :UINT
GetSystemWow64DirectoryW proto WINAPI :LPWSTR, :UINT
ifdef _UNICODE
define GetSystemWow64Directory  <GetSystemWow64DirectoryW>
else
define GetSystemWow64Directory  <GetSystemWow64DirectoryA>
endif

endif
endif

if (_WIN32_WINNT ge 0x0A00)
Wow64SetThreadDefaultGuestMachine proto WINAPI :USHORT
endif

if (_WIN32_WINNT ge 0x0A00)
IsWow64Process2 proto WINAPI :HANDLE, :ptr, :ptr
endif

if (_WIN32_WINNT ge 0x0A00)
GetSystemWow64Directory2A proto WINAPI :LPSTR, :UINT, :WORD
GetSystemWow64Directory2W proto WINAPI :LPWSTR, :UINT, :WORD
ifdef _UNICODE
define GetSystemWow64Directory2  <GetSystemWow64Directory2W>
else
define GetSystemWow64Directory2  <GetSystemWow64Directory2A>
endif
endif

if (_WIN32_WINNT ge 0x0A00)
IsWow64GuestMachineSupported proto WINAPI :USHORT, :ptr
endif

if (_WIN32_WINNT ge 0x0600)
Wow64GetThreadContext proto WINAPI :HANDLE, :PWOW64_CONTEXT
Wow64SetThreadContext proto WINAPI :HANDLE, :ptr
Wow64SuspendThread proto WINAPI :HANDLE
endif

endif
