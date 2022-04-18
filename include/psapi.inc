ifndef _PSAPI_H_
define _PSAPI_H_

include winapifamily.inc

.pragma comment(lib, psapi)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LIST_MODULES_DEFAULT	equ 0x0
LIST_MODULES_32BIT	equ 0x01
LIST_MODULES_64BIT	equ 0x02

LIST_MODULES_ALL	equ (LIST_MODULES_32BIT OR LIST_MODULES_64BIT)

ifndef PSAPI_VERSION
if (NTDDI_VERSION GE NTDDI_WIN7)
PSAPI_VERSION		equ 2
else
PSAPI_VERSION		equ 1
endif
endif

if (PSAPI_VERSION GT 1)
EnumProcesses		equ <K32EnumProcesses>
EnumProcessModules	equ <K32EnumProcessModules>
EnumProcessModulesEx	equ <K32EnumProcessModulesEx>
GetModuleBaseNameA	equ <K32GetModuleBaseNameA>
GetModuleBaseNameW	equ <K32GetModuleBaseNameW>
GetModuleFileNameExA	equ <K32GetModuleFileNameExA>
GetModuleFileNameExW	equ <K32GetModuleFileNameExW>
GetModuleInformation	equ <K32GetModuleInformation>
EmptyWorkingSet		equ <K32EmptyWorkingSet>
QueryWorkingSet		equ <K32QueryWorkingSet>
QueryWorkingSetEx	equ <K32QueryWorkingSetEx>
InitializeProcessForWsWatch equ <K32InitializeProcessForWsWatch>
GetWsChanges		equ <K32GetWsChanges>
GetWsChangesEx		equ <K32GetWsChangesEx>
GetMappedFileNameW	equ <K32GetMappedFileNameW>
GetMappedFileNameA	equ <K32GetMappedFileNameA>
EnumDeviceDrivers	equ <K32EnumDeviceDrivers>
GetDeviceDriverBaseNameA equ <K32GetDeviceDriverBaseNameA>
GetDeviceDriverBaseNameW equ <K32GetDeviceDriverBaseNameW>
GetDeviceDriverFileNameA equ <K32GetDeviceDriverFileNameA>
GetDeviceDriverFileNameW equ <K32GetDeviceDriverFileNameW>
GetProcessMemoryInfo	equ <K32GetProcessMemoryInfo>
GetPerformanceInfo	equ <K32GetPerformanceInfo>
EnumPageFilesW		equ <K32EnumPageFilesW>
EnumPageFilesA		equ <K32EnumPageFilesA>
GetProcessImageFileNameA equ <K32GetProcessImageFileNameA>
GetProcessImageFileNameW equ <K32GetProcessImageFileNameW>
endif

;BOOL
EnumProcesses proto WINAPI \
	   lpidProcess: ptr DWORD,
		    cb: DWORD,
	    lpcbNeeded: LPDWORD

;BOOL
EnumProcessModules proto WINAPI \
	      hProcess: HANDLE,
	     lphModule: ptr HMODULE,
		    cb: DWORD,
	    lpcbNeeded: LPDWORD

;BOOL
EnumProcessModulesEx proto WINAPI \
	      hProcess: HANDLE,
	     lphModule: ptr HMODULE,
		    cb: DWORD,
	    lpcbNeeded: LPDWORD,
	  dwFilterFlag: DWORD

;DWORD
GetModuleBaseNameA proto WINAPI \
	      hProcess: HANDLE,
	       hModule: HMODULE,
	    lpBaseName: LPSTR,
		 nSize: DWORD

;DWORD
GetModuleBaseNameW proto WINAPI \
	      hProcess: HANDLE,
	       hModule: HMODULE,
	    lpBaseName: LPWSTR,
		 nSize: DWORD


ifdef _UNICODE
GetModuleBaseName	equ <GetModuleBaseNameW>
else
GetModuleBaseName	equ <GetModuleBaseNameA>
endif


;DWORD
GetModuleFileNameExA proto WINAPI \
	      hProcess: HANDLE,
	       hModule: HMODULE,
	    lpFilename: LPSTR,
		 nSize: DWORD

;DWORD
GetModuleFileNameExW proto WINAPI \
	      hProcess: HANDLE,
	       hModule: HMODULE,
	    lpFilename: LPWSTR,
		 nSize: DWORD


ifdef _UNICODE
GetModuleFileNameEx	equ <GetModuleFileNameExW>
else
GetModuleFileNameEx	equ <GetModuleFileNameExA>
endif


MODULEINFO		STRUC
lpBaseOfDll		LPVOID ?
SizeOfImage		dd ?
EntryPoint		LPVOID ?
MODULEINFO		ENDS
LPMODULEINFO		typedef ptr MODULEINFO

;BOOL
GetModuleInformation proto WINAPI \
	      hProcess: HANDLE,
	       hModule: HMODULE,
	     lpmodinfo: LPMODULEINFO,
		    cb: DWORD

;BOOL
EmptyWorkingSet proto WINAPI \
	      hProcess: HANDLE

PSAPI_WORKING_SET_BLOCK UNION
Flags			ULONG_PTR ?
;STRUC
;Protection : 5		 ULONG_PTR ?
;ShareCount : 3		 ULONG_PTR ?
;Shared : 1		 ULONG_PTR ?
;Reserved : 3		 ULONG_PTR ?
;if defined(_WIN64)
;VirtualPage : 52	 ULONG_PTR ?
;else
;VirtualPage : 20	 ULONG_PTR ?
;endif
;ENDS
PSAPI_WORKING_SET_BLOCK ENDS
PPSAPI_WORKING_SET_BLOCK typedef ptr PSAPI_WORKING_SET_BLOCK

PSAPI_WORKING_SET_INFORMATION  STRUC
NumberOfEntries		ULONG_PTR ?
WorkingSetInfo		PSAPI_WORKING_SET_BLOCK 1 dup(<>)
PSAPI_WORKING_SET_INFORMATION ENDS
PPSAPI_WORKING_SET_INFORMATION typedef ptr PSAPI_WORKING_SET_INFORMATION

PSAPI_WORKING_SET_EX_BLOCK UNION
Flags			ULONG_PTR ?
;UNION ; {
;STRUC
;Valid : 1		 ULONG_PTR ?
;ShareCount : 3		 ULONG_PTR ?
;Win32Protection : 11	 ULONG_PTR ?
;Shared : 1		 ULONG_PTR ?
;Node : 6		 ULONG_PTR ?
;Locked : 1		 ULONG_PTR ?
;LargePage : 1		 ULONG_PTR ?
;Reserved : 7		 ULONG_PTR ?
;Bad : 1		 ULONG_PTR ?
;if defined(_WIN64)
;ReservedUlong : 32	 ULONG_PTR ?
;endif
;ENDS ;
;STRUC
;Valid : 1		 ULONG_PTR ?	;; Valid = 0 in this format.
;Reserved0 : 14		 ULONG_PTR ?
;Shared : 1		 ULONG_PTR ?
;Reserved1 : 15		 ULONG_PTR ?
;Bad : 1		 ULONG_PTR ?
;if defined(_WIN64)
;ReservedUlong : 32	 ULONG_PTR ?
;endif
;Invalid		 ENDS
;ENDS
PSAPI_WORKING_SET_EX_BLOCK ENDS
PPSAPI_WORKING_SET_EX_BLOCK typedef ptr PSAPI_WORKING_SET_EX_BLOCK

PSAPI_WORKING_SET_EX_INFORMATION  STRUC
VirtualAddress		PVOID ?
VirtualAttributes	PSAPI_WORKING_SET_EX_BLOCK <>
PSAPI_WORKING_SET_EX_INFORMATION ENDS
PPSAPI_WORKING_SET_EX_INFORMATION typedef ptr PSAPI_WORKING_SET_EX_INFORMATION

;BOOL
QueryWorkingSet proto WINAPI \
	      hProcess: HANDLE,
		    pv: PVOID,
		    cb: DWORD

;BOOL
QueryWorkingSetEx proto WINAPI \
	      hProcess: HANDLE,
		    pv: PVOID,
		    cb: DWORD

;BOOL
InitializeProcessForWsWatch proto WINAPI \
	      hProcess: HANDLE


PSAPI_WS_WATCH_INFORMATION  STRUC
FaultingPc		LPVOID ?
FaultingVa		LPVOID ?
PSAPI_WS_WATCH_INFORMATION ENDS
PPSAPI_WS_WATCH_INFORMATION typedef ptr PSAPI_WS_WATCH_INFORMATION

PSAPI_WS_WATCH_INFORMATION_EX  STRUC
BasicInfo		PSAPI_WS_WATCH_INFORMATION <>
FaultingThreadId	ULONG_PTR ?
Flags			ULONG_PTR ?	;; Reserved
PSAPI_WS_WATCH_INFORMATION_EX ENDS
PPSAPI_WS_WATCH_INFORMATION_EX typedef ptr PSAPI_WS_WATCH_INFORMATION_EX

;BOOL
GetWsChanges proto WINAPI \
	      hProcess: HANDLE,
	   lpWatchInfo: PPSAPI_WS_WATCH_INFORMATION,
		    cb: DWORD

;BOOL
GetWsChangesEx proto WINAPI \
	      hProcess: HANDLE,
	 lpWatchInfoEx: PPSAPI_WS_WATCH_INFORMATION_EX,
		    cb: PDWORD

;DWORD
GetMappedFileNameW proto WINAPI \
	      hProcess: HANDLE,
		   lpv: LPVOID,
	    lpFilename: LPWSTR,
		 nSize: DWORD

;DWORD
GetMappedFileNameA proto WINAPI \
	      hProcess: HANDLE,
		   lpv: LPVOID,
	    lpFilename: LPSTR,
		 nSize: DWORD


ifdef _UNICODE
GetMappedFileName	equ <GetMappedFileNameW>
else
GetMappedFileName	equ <GetMappedFileNameA>
endif

;BOOL
EnumDeviceDrivers proto WINAPI \
	   lpImageBase: ptr LPVOID,
		    cb: DWORD,
	    lpcbNeeded: LPDWORD

;DWORD
GetDeviceDriverBaseNameA proto WINAPI \
	     ImageBase: LPVOID,
	    lpFilename: LPSTR,
		 nSize: DWORD

;DWORD
GetDeviceDriverBaseNameW proto WINAPI \
	     ImageBase: LPVOID,
	    lpBaseName: LPWSTR,
		 nSize: DWORD

ifdef _UNICODE
GetDeviceDriverBaseName equ <GetDeviceDriverBaseNameW>
else
GetDeviceDriverBaseName equ <GetDeviceDriverBaseNameA>
endif

;DWORD
GetDeviceDriverFileNameA proto WINAPI \
	     ImageBase: LPVOID,
	    lpFilename: LPSTR,
		 nSize: DWORD

;DWORD
GetDeviceDriverFileNameW proto WINAPI \
	     ImageBase: LPVOID,
	    lpFilename: LPWSTR,
		 nSize: DWORD

ifdef _UNICODE
GetDeviceDriverFileName equ <GetDeviceDriverFileNameW>
else
GetDeviceDriverFileName equ <GetDeviceDriverFileNameA>
endif

PROCESS_MEMORY_COUNTERS	 STRUC
cb			dd ?
PageFaultCount		dd ?
PeakWorkingSetSize	SIZE_T ?
WorkingSetSize		SIZE_T ?
QuotaPeakPagedPoolUsage SIZE_T ?
QuotaPagedPoolUsage	SIZE_T ?
QuotaPeakNonPagedPoolUsage SIZE_T ?
QuotaNonPagedPoolUsage	SIZE_T ?
PagefileUsage		SIZE_T ?
PeakPagefileUsage	SIZE_T ?
PROCESS_MEMORY_COUNTERS ENDS
PPROCESS_MEMORY_COUNTERS typedef ptr PROCESS_MEMORY_COUNTERS

if (_WIN32_WINNT GE 0x0501)
PROCESS_MEMORY_COUNTERS_EX  STRUC
cb			dd ?
PageFaultCount		dd ?
PeakWorkingSetSize	SIZE_T ?
WorkingSetSize		SIZE_T ?
QuotaPeakPagedPoolUsage SIZE_T ?
QuotaPagedPoolUsage	SIZE_T ?
QuotaPeakNonPagedPoolUsage SIZE_T ?
QuotaNonPagedPoolUsage	SIZE_T ?
PagefileUsage		SIZE_T ?
PeakPagefileUsage	SIZE_T ?
PrivateUsage		SIZE_T ?
PROCESS_MEMORY_COUNTERS_EX ENDS
PPROCESS_MEMORY_COUNTERS_EX typedef ptr PROCESS_MEMORY_COUNTERS_EX
endif

;BOOL
GetProcessMemoryInfo proto WINAPI \
	       Process: HANDLE,
	ppsmemCounters: PPROCESS_MEMORY_COUNTERS,
		    cb: DWORD


PERFORMANCE_INFORMATION	 STRUC
cb			dd ?
CommitTotal		SIZE_T ?
CommitLimit		SIZE_T ?
CommitPeak		SIZE_T ?
PhysicalTotal		SIZE_T ?
PhysicalAvailable	SIZE_T ?
SystemCache		SIZE_T ?
KernelTotal		SIZE_T ?
KernelPaged		SIZE_T ?
KernelNonpaged		SIZE_T ?
PageSize		SIZE_T ?
HandleCount		dd ?
ProcessCount		dd ?
ThreadCount		dd ?
PERFORMANCE_INFORMATION ENDS
PPERFORMANCE_INFORMATION typedef ptr PERFORMANCE_INFORMATION
PERFORMACE_INFORMATION	typedef PERFORMANCE_INFORMATION
PPERFORMACE_INFORMATION typedef ptr PERFORMANCE_INFORMATION

;BOOL
GetPerformanceInfo proto WINAPI \
pPerformanceInformation: PPERFORMANCE_INFORMATION,
		    cb: DWORD


ENUM_PAGE_FILE_INFORMATION  STRUC
cb			dd ?
Reserved		dd ?
TotalSize		SIZE_T ?
TotalInUse		SIZE_T ?
PeakUsage		SIZE_T ?
ENUM_PAGE_FILE_INFORMATION ENDS
PENUM_PAGE_FILE_INFORMATION typedef ptr ENUM_PAGE_FILE_INFORMATION

CALLBACK(PENUM_PAGE_FILE_CALLBACKW, :LPVOID, :PENUM_PAGE_FILE_INFORMATION, :LPCWSTR)
CALLBACK(PENUM_PAGE_FILE_CALLBACKA, :LPVOID, :PENUM_PAGE_FILE_INFORMATION, :LPCSTR)

;BOOL
EnumPageFilesW proto WINAPI \
      pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKW,
	      pContext: LPVOID

;BOOL
EnumPageFilesA proto WINAPI \
      pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKA,
	      pContext: LPVOID


ifdef _UNICODE
PENUM_PAGE_FILE_CALLBACK equ <PENUM_PAGE_FILE_CALLBACKW>
EnumPageFiles		equ <EnumPageFilesW>
else
PENUM_PAGE_FILE_CALLBACK equ <PENUM_PAGE_FILE_CALLBACKA>
EnumPageFiles		equ <EnumPageFilesA>
endif

;DWORD
GetProcessImageFileNameA proto WINAPI \
	      hProcess: HANDLE,
       lpImageFileName: LPSTR,
		 nSize: DWORD

;DWORD
GetProcessImageFileNameW proto WINAPI \
	      hProcess: HANDLE,
       lpImageFileName: LPWSTR,
		 nSize: DWORD

ifdef _UNICODE
GetProcessImageFileName equ <GetProcessImageFileNameW>
else
GetProcessImageFileName equ <GetProcessImageFileNameA>
endif

endif
endif
