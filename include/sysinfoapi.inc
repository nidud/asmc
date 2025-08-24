ifndef _SYSINFOAPI_H_
define _SYSINFOAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

SYSTEM_INFO		struct
union
 dwOemId		DWORD ?
 struct
  wProcessorArchitecture WORD ?
  wReserved		WORD ?
 ends
ends
dwPageSize		DWORD ?
lpMinimumApplicationAddress LPVOID ?
lpMaximumApplicationAddress LPVOID ?
dwActiveProcessorMask	DWORD_PTR ?
dwNumberOfProcessors	DWORD ?
dwProcessorType		DWORD ?
dwAllocationGranularity DWORD ?
wProcessorLevel		WORD ?
wProcessorRevision	WORD ?
SYSTEM_INFO		ends
LPSYSTEM_INFO		typedef ptr SYSTEM_INFO

MEMORYSTATUSEX		struct
dwLength		DWORD ?
dwMemoryLoad		DWORD ?
ullTotalPhys		DWORDLONG ?
ullAvailPhys		DWORDLONG ?
ullTotalPageFile	DWORDLONG ?
ullAvailPageFile	DWORDLONG ?
ullTotalVirtual		DWORDLONG ?
ullAvailVirtual		DWORDLONG ?
ullAvailExtendedVirtual DWORDLONG ?
MEMORYSTATUSEX		ends
LPMEMORYSTATUSEX	typedef ptr MEMORYSTATUSEX

define USER_CET_ENVIRONMENT_WIN32_PROCESS	 0x00000000
define USER_CET_ENVIRONMENT_SGX2_ENCLAVE	 0x00000002
define USER_CET_ENVIRONMENT_VBS_ENCLAVE		 0x00000010
define USER_CET_ENVIRONMENT_VBS_BASIC_ENCLAVE	 0x00000011

GlobalMemoryStatusEx proto WINAPI :LPMEMORYSTATUSEX
GetSystemInfo proto WINAPI :LPSYSTEM_INFO
GetSystemTime proto WINAPI :LPSYSTEMTIME
GetSystemTimeAsFileTime proto WINAPI :LPFILETIME
GetLocalTime proto WINAPI :LPSYSTEMTIME

if (NTDDI_VERSION ge NTDDI_WIN10_VB)
IsUserCetAvailableInEnvironment proto WINAPI :DWORD
endif

if (NTDDI_VERSION ge NTDDI_WIN10_19H1)
GetSystemLeapSecondInformation proto WINAPI :PBOOL, :PDWORD
endif

GetVersion proto WINAPI
SetLocalTime proto WINAPI :ptr

GetTickCount proto WINAPI
if (_WIN32_WINNT ge 0x0600)
GetTickCount64 proto WINAPI
endif

GetSystemTimeAdjustment proto WINAPI :PDWORD, :PDWORD, :PBOOL
GetSystemTimeAdjustmentPrecise proto WINAPI :PDWORD64, :PDWORD64, :PBOOL
GetSystemDirectoryA proto WINAPI :LPSTR, :UINT
GetSystemDirectoryW proto WINAPI :LPWSTR, :UINT
ifdef _UNICODE
define GetSystemDirectory  <GetSystemDirectoryW>
else
define GetSystemDirectory  <GetSystemDirectoryA>
endif

GetWindowsDirectoryA proto WINAPI :LPSTR, :UINT
GetWindowsDirectoryW proto WINAPI :LPWSTR, :UINT
ifdef _UNICODE
define GetWindowsDirectory  <GetWindowsDirectoryW>
else
define GetWindowsDirectory  <GetWindowsDirectoryA>
endif

GetSystemWindowsDirectoryA proto WINAPI :LPSTR, :UINT
GetSystemWindowsDirectoryW proto WINAPI :LPWSTR, :UINT
ifdef _UNICODE
define GetSystemWindowsDirectory  <GetSystemWindowsDirectoryW>
else
define GetSystemWindowsDirectory  <GetSystemWindowsDirectoryA>
endif

.enum COMPUTER_NAME_FORMAT {
    ComputerNameNetBIOS,
    ComputerNameDnsHostname,
    ComputerNameDnsDomain,
    ComputerNameDnsFullyQualified,
    ComputerNamePhysicalNetBIOS,
    ComputerNamePhysicalDnsHostname,
    ComputerNamePhysicalDnsDomain,
    ComputerNamePhysicalDnsFullyQualified,
    ComputerNameMax
    }

GetComputerNameExA proto WINAPI :COMPUTER_NAME_FORMAT, :LPSTR, :LPDWORD
GetComputerNameExW proto WINAPI :COMPUTER_NAME_FORMAT, :LPWSTR, :LPDWORD
ifdef _UNICODE
define GetComputerNameEx  <GetComputerNameExW>
else
define GetComputerNameEx  <GetComputerNameExA>
endif

SetComputerNameExW proto WINAPI :COMPUTER_NAME_FORMAT, :LPCWSTR

ifdef _UNICODE
define SetComputerNameEx <SetComputerNameExW>
endif

SetSystemTime proto WINAPI :ptr

GetVersionExA proto WINAPI :LPOSVERSIONINFOA
GetVersionExW proto WINAPI :LPOSVERSIONINFOW
ifdef _UNICODE
define GetVersionEx  <GetVersionExW>
else
define GetVersionEx  <GetVersionExA>
endif

GetLogicalProcessorInformation proto WINAPI :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, :PDWORD

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
GetLogicalProcessorInformationEx proto WINAPI :LOGICAL_PROCESSOR_RELATIONSHIP, :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, :PDWORD
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
GetNativeSystemInfo proto WINAPI :LPSYSTEM_INFO
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
GetSystemTimePreciseAsFileTime proto WINAPI :LPFILETIME
endif

if (_WIN32_WINNT ge _WIN32_WINNT_VISTA)
GetProductInfo proto WINAPI :DWORD, :DWORD, :DWORD, :DWORD, :PDWORD
endif

if (NTDDI_VERSION ge NTDDI_WIN2K)
VerSetConditionMask proto WINAPI :ULONGLONG, :ULONG, :UCHAR
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
GetOsSafeBootMode proto WINAPI :PDWORD
endif

EnumSystemFirmwareTables proto WINAPI :DWORD, :PVOID, :DWORD
GetSystemFirmwareTable proto WINAPI :DWORD, :DWORD, :PVOID, :DWORD

DnsHostnameToComputerNameExW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD
GetPhysicallyInstalledSystemMemory proto WINAPI :PULONGLONG

define SCEX2_ALT_NETBIOS_NAME 0x00000001

SetComputerNameEx2W proto WINAPI :COMPUTER_NAME_FORMAT, :DWORD, :LPCWSTR

ifdef _UNICODE
define SetComputerNameEx2 <SetComputerNameEx2W>
endif

SetSystemTimeAdjustment proto WINAPI :DWORD, :BOOL
SetSystemTimeAdjustmentPrecise proto WINAPI :DWORD64, :BOOL
InstallELAMCertificateInfo proto WINAPI :HANDLE

if (_WIN32_WINNT ge _WIN32_WINNT_WIN7)
GetProcessorSystemCycleTime proto WINAPI :USHORT, :PSYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION, :PDWORD
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
GetOsManufacturingMode proto WINAPI :PBOOL
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
GetIntegratedDisplaySize proto WINAPI :ptr
endif

SetComputerNameA proto WINAPI :LPCSTR
SetComputerNameW proto WINAPI :LPCWSTR
ifdef _UNICODE
define SetComputerName	<SetComputerNameW>
else
define SetComputerName	<SetComputerNameA>
endif
SetComputerNameExA proto WINAPI :COMPUTER_NAME_FORMAT, :LPCSTR
ifndef _UNICODE
define SetComputerNameEx <SetComputerNameExA>
endif

endif
