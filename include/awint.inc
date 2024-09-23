ifdef _WIN32

ifndef _INC_AWINC
define _INC_AWINC

ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif

include sal.inc
include windows.inc
include sdkddkver.inc
include winnls.inc
if (defined (_M_IX86) OR defined (_M_X64)) AND NOT defined (_CORESYS) AND NOT defined (_CRT_APP) AND NOT defined (_KERNELX)
_CRT_NTDDI_MIN equ NTDDI_WINXPSP2
else
_CRT_NTDDI_MIN equ NTDDI_WIN8
endif

pthreadlocinfo typedef ptr threadlocinfo

FAST_FAIL_VTGUARD_CHECK_FAILURE         equ 1
FAST_FAIL_STACK_COOKIE_CHECK_FAILURE    equ 2
FAST_FAIL_CORRUPT_LIST_ENTRY            equ 3
FAST_FAIL_INCORRECT_STACK               equ 4
FAST_FAIL_INVALID_ARG                   equ 5
FAST_FAIL_GS_COOKIE_INIT                equ 6
FAST_FAIL_FATAL_APP_EXIT                equ 7
FAST_FAIL_RANGE_CHECK_FAILURE           equ 8

ifndef PF_FASTFAIL_AVAILABLE
PF_FASTFAIL_AVAILABLE   equ 23
endif

__crtCompareStringW proto WINAPI :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPCWSTR, :SINT
__crtCompareStringA proto WINAPI :_locale_t, :LPCWSTR, :DWORD, :LPCSTR, :SINT, :LPCSTR, :SINT, :SINT
__crtGetLocaleInfoA proto WINAPI :_locale_t, :LPCWSTR, :LCTYPE, :LPSTR, :SINT
__crtLCMapStringW proto WINAPI :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPWSTR, :SINT
__crtLCMapStringA proto WINAPI :_locale_t, :LPCWSTR, :DWORD, :LPCSTR, :SINT, :LPSTR, :SINT, :SINT, :BOOL
__crtGetStringTypeA proto WINAPI :_locale_t, :DWORD, :LPCSTR, :SINT, :LPWORD, :SINT, :BOOL
__crtGetEnvironmentStringsA proto __cdecl
__crtGetEnvironmentStringsW proto __cdecl
__crtMessageBoxA proto WINAPI :LPCSTR, :LPCSTR, :UINT
__crtMessageBoxW proto WINAPI :LPCWSTR, :LPCWSTR, :UINT
__crtIsPackagedApp proto WINAPI
__crtGetShowWindowMode proto __cdecl
__crtSetUnhandledExceptionFilter proto WINAPI :LPTOP_LEVEL_EXCEPTION_FILTER

if defined (_M_IX86) OR defined (_M_X64)
__crtUnhandledException proto WINAPI :ptr EXCEPTION_POINTERS
__crtTerminateProcess proto WINAPI :UINT
endif

ifdef _M_X64
__crtCaptureCurrentContext proto WINAPI :ptr CONTEXT
__crtCapturePreviousContext proto WINAPI :ptr CONTEXT
endif

if _CRT_NTDDI_MIN GE NTDDI_VISTA

__crtFlsAlloc macro lpCallback
    exitm<FlsAlloc(lpCallback)>
    endm

__crtFlsFree macro dwFlsIndex
    exitm<FlsFree(dwFlsIndex)>
    endm

__crtFlsGetValue macro dwFlsIndex
    exitm<FlsGetValue(dwFlsIndex)>
    endm

__crtFlsSetValue macro dwFlsIndex,lpFlsData
    exitm<FlsSetValue(dwFlsIndex,lpFlsData)>
    endm

__crtInitializeCriticalSectionEx macro lpCriticalSection, dwSpinCount, Flags
    exitm<InitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, Flags)>
    endm

__crtCreateEventExW macro lpEventAttributes, lpName, dwFlags, dwDesiredAccess
    exitm<CreateEventExW(lpEventAttributes, lpName, dwFlags, dwDesiredAccess)>
    endm

__crtCreateSemaphoreExW macro lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, dwFlags, dwDesiredAccess
    exitm<CreateSemaphoreExW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, dwFlags, dwDesiredAccess)>
    endm

__crtSetThreadStackGuarantee macro StackSizeInBytes
    exitm<SetThreadStackGuarantee(StackSizeInBytes)>
    endm

__crtCreateThreadpoolTimer macro pfnti, pv, pcbe
    exitm<CreateThreadpoolTimer(pfnti, pv, pcbe)>
    endm

__crtSetThreadpoolTimer macro pti, pftDueTime, msPeriod, msWindowLength
    exitm<SetThreadpoolTimer(pti, pftDueTime, msPeriod, msWindowLength)>
    endm

__crtWaitForThreadpoolTimerCallbacks macro pti, fCancelPendingCallbacks
    exitm<WaitForThreadpoolTimerCallbacks(pti, fCancelPendingCallbacks)>
    endm

__crtCloseThreadpoolTimer macro pti
    exitm<CloseThreadpoolTimer(pti)>
    endm

__crtCreateThreadpoolWait macro pfnwa, pv, pcbe
    exitm<CreateThreadpoolWait(pfnwa, pv, pcbe)>
    endm

__crtSetThreadpoolWait macro pwa, h, pftTimeout
    exitm<SetThreadpoolWait(pwa, h, pftTimeout)>
    endm

__crtCloseThreadpoolWait macro pwa
    exitm<CloseThreadpoolWait(pwa)>
    endm

;; wrapper for FlushProcessWriteBuffers, available only on Vista+
__crtFlushProcessWriteBuffers macro
    exitm<FlushProcessWriteBuffers()>
    endm

;; wrapper for FreeLibraryWhenCallbackReturns, available only on Vista+
__crtFreeLibraryWhenCallbackReturns macro pci, mod
    exitm<FreeLibraryWhenCallbackReturns(pci, mod)>
    endm

;; wrapper for GetCurrentProcessorNumber, available only on Vista+
__crtGetCurrentProcessorNumber macro
    exitm<GetCurrentProcessorNumber()>
    endm

;; wrapper for GetLogicalProcessorInformation, available only on Vista+
__crtGetLogicalProcessorInformation macro Buffer, ReturnLength
    exitm<GetLogicalProcessorInformation(Buffer, ReturnLength)>
    endm

;; wrapper for CreateSymbolicLink, available only on Vista+
__crtCreateSymbolicLinkW macro lpSymlinkFileName, lpTargetFileName, dwFlags
    exitm<CreateSymbolicLinkW(lpSymlinkFileName, lpTargetFileName, dwFlags)>
    endm

__crtCompareStringEx macro lpLocaleName, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2
    exitm<CompareStringEx(lpLocaleName, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2, NULL, NULL, 0)>
    endm

__crtEnumSystemLocalesEx macro lpLocaleEnumProcEx, dwFlags, lParam
    exitm<EnumSystemLocalesEx(lpLocaleEnumProcEx, dwFlags, lParam, NULL)>
    endm

__crtGetDateFormatEx macro lpLocaleName, dwFlags, lpDate, lpFormat, lpDateStr, cchDate
    exitm<GetDateFormatEx(lpLocaleName, dwFlags, lpDate, lpFormat, lpDateStr, cchDate, NULL)>
    endm

__crtGetLocaleInfoEx macro lpLocaleName, LCType, lpLCData, cchData
    exitm<GetLocaleInfoEx(lpLocaleName, LCType, lpLCData, cchData)>
    endm

__crtGetTimeFormatEx macro lpLocaleName, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime
    exitm<GetTimeFormatEx(lpLocaleName, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime)>
    endm

__crtGetUserDefaultLocaleName macro lpLocaleName, cchLocaleName
    exitm<GetUserDefaultLocaleName(lpLocaleName, cchLocaleName)>
    endm

__crtIsValidLocaleName macro lpLocaleName
    exitm<IsValidLocaleName(lpLocaleName)>
    endm

__crtLCMapStringEx macro lpLocaleName, dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest
    exitm<LCMapStringEx(lpLocaleName, dwMapFlags, lpSrcStr, cchSrc, lpDestStr, cchDest, NULL, NULL, 0)>
    endm

__crtGetFileInformationByHandleEx macro hFile, FileInformationClass, lpFileInformation, dwBufferSize
    exitm<GetFileInformationByHandleEx(hFile, FileInformationClass, lpFileInformation, dwBufferSize)>
    endm

__crtSetFileInformationByHandle macro hFile, FileInformationClass, lpFileInformation, dwBufferSize
    exitm<SetFileInformationByHandle(hFile, FileInformationClass, lpFileInformation, dwBufferSize)>
    endm

__crtGetTickCount64 macro
    exitm<GetTickCount64()>
    endm

else  ;; _CRT_NTDDI_MIN GE NTDDI_VISTA

__crtDownlevelLocaleNameToLCID proto WINAPI :LPCWSTR
__crtDownlevelLCIDToLocaleName proto WINAPI :LCID, :LPWSTR, :SINT
__crtFlsAlloc proto WINAPI :PFLS_CALLBACK_FUNCTION
__crtFlsFree proto WINAPI :DWORD
__crtFlsGetValue proto WINAPI :DWORD
__crtFlsSetValue proto WINAPI :DWORD, :ptr
__crtInitializeCriticalSectionEx proto WINAPI :LPCRITICAL_SECTION, :DWORD, :DWORD
__crtCreateEventExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCWSTR, :DWORD, :DWORD
__crtCreateSemaphoreExW proto WINAPI :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCWSTR, :DWORD, :DWORD
__crtSetThreadStackGuarantee proto WINAPI :PULONG
__crtCreateThreadpoolTimer proto __cdecl :PTP_TIMER_CALLBACK, :ptr, :PTP_CALLBACK_ENVIRON
__crtSetThreadpoolTimer proto WINAPI :PTP_TIMER, :PFILETIME, :DWORD, :DWORD
__crtWaitForThreadpoolTimerCallbacks proto WINAPI :PTP_TIMER, :BOOL
__crtCloseThreadpoolTimer proto WINAPI :PTP_TIMER
__crtCreateThreadpoolWait proto __cdecl :PTP_WAIT_CALLBACK, :ptr, :PTP_CALLBACK_ENVIRON
__crtSetThreadpoolWait proto WINAPI :PTP_WAIT, :HANDLE, :PFILETIME
__crtCloseThreadpoolWait proto WINAPI :PTP_WAIT
__crtFlushProcessWriteBuffers proto WINAPI
__crtFreeLibraryWhenCallbackReturns proto WINAPI :PTP_CALLBACK_INSTANCE, :HMODULE
__crtGetCurrentProcessorNumber proto WINAPI
__crtGetLogicalProcessorInformation proto WINAPI :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, :PDWORD
__crtCreateSymbolicLinkW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD
__crtCompareStringEx proto WINAPI :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPCWSTR, :SINT
__crtEnumSystemLocalesEx proto WINAPI :LOCALE_ENUMPROCEX, :DWORD, :LPARAM
__crtGetDateFormatEx proto WINAPI :LPCWSTR, :DWORD, :ptr SYSTEMTIME, :LPCWSTR, :LPWSTR, :SINT
__crtGetLocaleInfoEx proto WINAPI :LPCWSTR, :LCTYPE, :LPWSTR, :SINT
__crtGetTimeFormatEx proto WINAPI :LPCWSTR, :DWORD, :ptr, :LPCWSTR, :LPWSTR, :SINT
__crtGetUserDefaultLocaleName proto WINAPI :LPWSTR, :SINT
__crtIsValidLocaleName proto WINAPI :LPCWSTR
__crtLCMapStringEx proto WINAPI :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPWSTR, :SINT
__crtGetFileInformationByHandleEx proto WINAPI :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :ptr, :DWORD
__crtSetFileInformationByHandle proto WINAPI :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :ptr, :DWORD
__crtGetTickCount64 proto WINAPI

endif  ;; _CRT_NTDDI_MIN GE NTDDI_VISTA

__crtSleep proto WINAPI :DWORD

__crtLoadWinApiPointers proto WINAPI

wrapEncodedKERNEL32Functions typedef SDWORD
eFlsAlloc               equ 0
eFlsFree                equ 1
eFlsGetValue            equ 2
eFlsSetValue            equ 3
eInitializeCriticalSectionEx equ 4
eCreateEventExW         equ 5
eCreateSemaphoreExW     equ 6
eSetThreadStackGuarantee equ 7
eCreateThreadpoolTimer  equ 8
eSetThreadpoolTimer     equ 9
eWaitForThreadpoolTimerCallbacks equ 10
eCloseThreadpoolTimer   equ 11
eCreateThreadpoolWait   equ 12
eSetThreadpoolWait      equ 13
eCloseThreadpoolWait    equ 14
eFlushProcessWriteBuffers equ 15
eFreeLibraryWhenCallbackReturns equ 16
eGetCurrentProcessorNumber equ 17
eGetLogicalProcessorInformation equ 18
eCreateSymbolicLinkW    equ 19
eSetDefaultDllDirectories equ 20
eCompareStringEx        equ 21
eEnumSystemLocalesEx    equ 22
eGetDateFormatEx        equ 23
eGetLocaleInfoEx        equ 24
eGetTimeFormatEx        equ 25
eGetUserDefaultLocaleName equ 26
eIsValidLocaleName      equ 27
eLCMapStringEx          equ 28
eGetCurrentPackageId    equ 29
eGetTickCount64         equ 30
eGetFileInformationByHandleExW equ 31
eSetFileInformationByHandleW equ 32
eMaxKernel32Function    equ 33

externdef               encodedKERNEL32Functions:PVOID ; [eMaxKernel32Function]

;; Needed for pointer encoding
externdef               __security_cookie:UINT_PTR

CALLBACK(PFNFLSALLOC, :PFLS_CALLBACK_FUNCTION)
CALLBACK(PFNFLSFREE, :DWORD)
CALLBACK(PFNFLSGETVALUE, :DWORD)
CALLBACK(PFNFLSSETVALUE, :DWORD, :PVOID)
CALLBACK(PFNINITIALIZECRITICALSECTIONEX, :LPCRITICAL_SECTION, :DWORD, :DWORD)
CALLBACK(PFNCREATEEVENTEXW, :LPSECURITY_ATTRIBUTES, :LPCWSTR, :DWORD, :DWORD)
CALLBACK(PFNCREATESEMAPHOREEXW, :LPSECURITY_ATTRIBUTES, :LONG, :LONG, :LPCWSTR, :DWORD, :DWORD)
CALLBACK(PFNSETTHREADSTACKGUARANTEE, :PULONG)
CALLBACK(PFNCREATETHREADPOOLTIMER, :PTP_TIMER_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON)
CALLBACK(PFNSETTHREADPOOLTIMER, :PTP_TIMER, :PFILETIME, :DWORD, :DWORD)
CALLBACK(PFNWAITFORTHREADPOOLTIMERCALLBACKS, :PTP_TIMER, :BOOL)
CALLBACK(PFNCLOSETHREADPOOLTIMER, :PTP_TIMER)
CALLBACK(PFNCREATETHREADPOOLWAIT, :PTP_WAIT_CALLBACK, :PVOID, :PTP_CALLBACK_ENVIRON)
CALLBACK(PFNSETTHREADPOOLWAIT, :PTP_WAIT, :HANDLE, :PFILETIME)
CALLBACK(PFNCLOSETHREADPOOLWAIT, :PTP_WAIT)
CALLBACK(PFNFLUSHPROCESSWRITEBUFFERS)
CALLBACK(PFNFREELIBRARYWHENCALLBACKRETURNS, :PTP_CALLBACK_INSTANCE, :HMODULE)
CALLBACK(PFNGETCURRENTPROCESSORNUMBER)
CALLBACK(PFNGETLOGICALPROCESSORINFORMATION, :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, :PDWORD)
CALLBACK(PFNCREATESYMBOLICLINK, :LPCWSTR, :LPCWSTR, :DWORD)
CALLBACK(PFNENUMSYSTEMLOCALESEX, :LOCALE_ENUMPROCEX, :DWORD, :LPARAM, :LPVOID)
CALLBACK(PFNCOMPARESTRINGEX, :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPCWSTR, :SINT, :LPNLSVERSIONINFO, :LPVOID, :LPARAM)
CALLBACK(PFNGETDATEFORMATEX, :LPCWSTR, :DWORD, :ptr, :LPCWSTR, :LPWSTR, :SINT, :LPCWSTR)
CALLBACK(PFNGETLOCALEINFOEX, :LPCWSTR, :LCTYPE, :LPWSTR, :SINT)
CALLBACK(PFNGETTIMEFORMATEX, :LPCWSTR, :DWORD, :ptr, :LPCWSTR, :LPWSTR, :SINT)
CALLBACK(PFNGETUSERDEFAULTLOCALENAME, :LPWSTR, :SINT)
CALLBACK(PFNISVALIDLOCALENAME, :LPCWSTR)
CALLBACK(PFNLCMAPSTRINGEX, :LPCWSTR, :DWORD, :LPCWSTR, :SINT, :LPWSTR, :SINT, :LPNLSVERSIONINFO, :LPVOID, :LPARAM)
CALLBACK(PFNGETTICKCOUNT64)
CALLBACK(PFNGETFILEINFORMATIONBYHANDLEEX, :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :LPVOID, :DWORD)
CALLBACK(PFNSETFILEINFORMATIONBYHANDLE, :HANDLE, :FILE_INFO_BY_HANDLE_CLASS, :LPVOID, :DWORD)

;; Use this macro for encoding and caching a function pointer from a DLL
STOREENCODEDFUNCTIONPOINTER macro instance, libraryname, functionname
    GetProcAddress(instance, "&functionname&")
    xor rax,__security_cookie
    mov encoded&libraryname&Functions[e&functionname&*size_t],rax
    exitm<>
    endm


;; Use this macro for decoding a cached function pointer from a DLL
IFDYNAMICGETCACHEDFUNCTION macro libraryname, functiontypedef, functionname, functionpointer
   .new functionpointer:ptr functiontypedef
    mov rax,encoded&libraryname&Functions[e&functionname&*size_t]
    xor rax,__security_cookie
    mov functionpointer,rax
    exitm<rax>
    endm


ifdef _CRT_APP

__crtCreateWinRTThread proto WINAPI :LPTHREAD_START_ROUTINE, :ptr, :LPDWORD
__crtCloseWinRTThreadHandle proto WINAPI :HANDLE
__crtGetCurrentWinRTThread proto WINAPI
__crtGetCurrentWinRTThreadId proto WINAPI
__crtGetExitCodeWinRTThread proto WINAPI :HANDLE, :ptr DWORD
__crtGetWinRTThreadWaitableHandle proto WINAPI :HANDLE
__crtGetWinRTThreadId proto WINAPI :HANDLE
__crtSetExitCodeWinRTThread proto WINAPI :HANDLE, :DWORD
__crtWaitForWinRTThreadExit proto WINAPI :HANDLE, :DWORD
__crtCreateWinRTTimer proto WINAPI :WAITORTIMERCALLBACK, :ptr, :SINT, :BOOL
__crtDeleteWinRTTimer proto WINAPI :HANDLE, :BOOL
__crtCancelWinRTTimer proto WINAPI :HANDLE, :BOOL
__crtExitProcessWinRT proto WINAPI
__crtGetFullPathNameWinRTW proto WINAPI :LPWSTR, :DWORD, :LPWSTR
__crtGetFullPathNameWinRTA proto WINAPI :ptr, :DWORD, :LPSTR
__crtGetTempPathWinRTW proto WINAPI :SINT, :LPWSTR
__crtGetTempPathWinRTA proto WINAPI :SINT, :LPSTR

endif  ;; _CRT_APP
endif  ;; _INC_AWINC
endif  ;; _WIN32
