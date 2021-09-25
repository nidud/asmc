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

;int
__crtCompareStringW proto WINAPI \
           _LocaleName: LPCWSTR,
           _DwCmpFlags: DWORD,
            _LpString1: LPCWSTR,
            _CchCount1: SINT,
            _LpString2: LPCWSTR,
            _CchCount2: SINT

__crtCompareStringA proto WINAPI \
             _Plocinfo: _locale_t,
           _LocaleName: LPCWSTR,
           _DwCmpFlags: DWORD,
            _LpString1: LPCSTR,
            _CchCount1: SINT,
            _LpString2: LPCSTR,
            _CchCount2: SINT,
            _Code_page: SINT

__crtGetLocaleInfoA proto WINAPI \
             _Plocinfo: _locale_t,
           _LocaleName: LPCWSTR,
               _LCType: LCTYPE,
             _LpLCData: LPSTR,
              _CchData: SINT

__crtLCMapStringW proto WINAPI \
           _LocaleName: LPCWSTR,
            _DWMapFlag: DWORD,
             _LpSrcStr: LPCWSTR,
               _CchSrc: SINT,
            _LpDestStr: LPWSTR,
              _CchDest: SINT

__crtLCMapStringA proto WINAPI \
             _Plocinfo: _locale_t,
           _LocaleName: LPCWSTR,
            _DwMapFlag: DWORD,
             _LpSrcStr: LPCSTR,
               _CchSrc: SINT,
            _LpDestStr: LPSTR,
              _CchDest: SINT,
            _Code_page: SINT,
               _BError: BOOL

__crtGetStringTypeA proto WINAPI \
             _Plocinfo: _locale_t,
           _DWInfoType: DWORD,
             _LpSrcStr: LPCSTR,
               _CchSrc: SINT,
           _LpCharType: LPWORD,
            _Code_page: SINT,
               _BError: BOOL


__crtGetEnvironmentStringsA proto __cdecl
__crtGetEnvironmentStringsW proto __cdecl

__crtMessageBoxA proto WINAPI \
               _LpText: LPCSTR,
            _LpCaption: LPCSTR,
                _UType: UINT

__crtMessageBoxW proto WINAPI \
               _LpText: LPCWSTR,
            _LpCaption: LPCWSTR,
                _UType: UINT

__crtIsPackagedApp proto WINAPI

__crtGetShowWindowMode proto __cdecl

__crtSetUnhandledExceptionFilter proto WINAPI \
       exceptionFilter: LPTOP_LEVEL_EXCEPTION_FILTER


if defined (_M_IX86) OR defined (_M_X64)

__crtUnhandledException proto WINAPI \
         exceptionInfo: ptr EXCEPTION_POINTERS

__crtTerminateProcess proto WINAPI \
             uExitCode: UINT

endif

ifdef _M_X64
__crtCaptureCurrentContext proto WINAPI \
        pContextRecord: ptr CONTEXT

__crtCapturePreviousContext proto WINAPI \
        pContextRecord: ptr CONTEXT
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

;; Downlevel NLS locale name <==> LCID conversion
__crtDownlevelLocaleNameToLCID proto WINAPI \
            localeName: LPCWSTR

;int
__crtDownlevelLCIDToLocaleName proto WINAPI \
                  lcid: LCID,
         outLocaleName: LPWSTR,
         cchLocaleName: SINT

;DWORD
__crtFlsAlloc proto WINAPI \
            lpCallback: PFLS_CALLBACK_FUNCTION

;BOOL
__crtFlsFree proto WINAPI \
            dwFlsIndex: DWORD


;PVOID
__crtFlsGetValue proto WINAPI \
            dwFlsIndex: DWORD


;BOOL
__crtFlsSetValue proto WINAPI \
            dwFlsIndex: DWORD,
             lpFlsData: PVOID


;; wrapper for InitializeCriticalSectionEx, available only on Vista+
;BOOL
__crtInitializeCriticalSectionEx proto WINAPI \
     lpCriticalSection: LPCRITICAL_SECTION,
           dwSpinCount: DWORD,
                 Flags: DWORD


;; wrapper for CreateEventExW, available only on Vista+
;HANDLE
__crtCreateEventExW proto WINAPI \
     lpEventAttributes: LPSECURITY_ATTRIBUTES,
                lpName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD


;; wrapper for CreateSemaphoreExW, available only on Vista+
;HANDLE
__crtCreateSemaphoreExW proto WINAPI \
 lpSemaphoreAttributes: LPSECURITY_ATTRIBUTES,
         lInitialCount: LONG,
         lMaximumCount: LONG,
                lpName: LPCWSTR,
               dwFlags: DWORD,
       dwDesiredAccess: DWORD


;; wrapper for SetThreadStackGuarantee, available only on Vista+
;BOOL
__crtSetThreadStackGuarantee proto WINAPI \
      StackSizeInBytes: PULONG


;; wrappers for thread pool APIs, available only on Vista+
;PTP_TIMER
__crtCreateThreadpoolTimer proto __cdecl \
                 pfnti: PTP_TIMER_CALLBACK,
                    pv: PVOID,
                  pcbe: PTP_CALLBACK_ENVIRON

;VOID
__crtSetThreadpoolTimer proto WINAPI \
                   pti: PTP_TIMER,
            pftDueTime: PFILETIME,
              msPeriod: DWORD,
        msWindowLength: DWORD

;VOID
__crtWaitForThreadpoolTimerCallbacks proto WINAPI \
                   pti: PTP_TIMER,
fCancelPendingCallbacks: BOOL


;VOID
__crtCloseThreadpoolTimer proto WINAPI \
                   pti: PTP_TIMER


;PTP_WAIT
__crtCreateThreadpoolWait proto __cdecl \
                 pfnwa: PTP_WAIT_CALLBACK,
                    pv: PVOID,
                  pcbe: PTP_CALLBACK_ENVIRON

;VOID
__crtSetThreadpoolWait proto WINAPI \
                   pwa: PTP_WAIT,
                     h: HANDLE,
            pftTimeout: PFILETIME


;VOID
__crtCloseThreadpoolWait proto WINAPI \
                   pwa: PTP_WAIT


;; wrapper for FlushProcessWriteBuffers, available only on Vista+
;VOID
__crtFlushProcessWriteBuffers proto WINAPI

;; wrapper for FreeLibraryWhenCallbackReturns, available only on Vista+
;VOID
__crtFreeLibraryWhenCallbackReturns proto WINAPI \
                   pci: PTP_CALLBACK_INSTANCE,
                   _mod: HMODULE


;; wrapper for GetCurrentProcessorNumber, available only on Vista+
;DWORD
__crtGetCurrentProcessorNumber proto WINAPI

;; wrapper for GetLogicalProcessorInformation, available only on Vista+
;BOOL
__crtGetLogicalProcessorInformation proto WINAPI \
                Buffer: PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
          ReturnLength: PDWORD


;; wrapper for CreateSymbolicLink, available only on Vista+
;BOOLEAN
__crtCreateSymbolicLinkW proto WINAPI \
     lpSymlinkFileName: LPCWSTR,
      lpTargetFileName: LPCWSTR,
               dwFlags: DWORD


;; Helper functions for NLS-specific Win32 APIs
;int
__crtCompareStringEx proto WINAPI \
          lpLocaleName: LPCWSTR,
            dwCmpFlags: DWORD,
             lpString1: LPCWSTR,
             cchCount1: SINT,
             lpString2: LPCWSTR,
             cchCount2: SINT


;BOOL
__crtEnumSystemLocalesEx proto WINAPI \
    lpLocaleEnumProcEx: LOCALE_ENUMPROCEX,
               dwFlags: DWORD,
                lParam: LPARAM


;int
__crtGetDateFormatEx proto WINAPI \
          lpLocaleName: LPCWSTR,
               dwFlags: DWORD,
                lpDate: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpDateStr: LPWSTR,
               cchDate: SINT


;int
__crtGetLocaleInfoEx proto WINAPI \
          lpLocaleName: LPCWSTR,
                LCType: LCTYPE,
              lpLCData: LPWSTR,
               cchData: SINT


;int
__crtGetTimeFormatEx proto WINAPI \
          lpLocaleName: LPCWSTR,
               dwFlags: DWORD,
                lpTime: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpTimeStr: LPWSTR,
               cchTime: SINT


;int
__crtGetUserDefaultLocaleName proto WINAPI \
          lpLocaleName: LPWSTR,
         cchLocaleName: SINT


;BOOL
__crtIsValidLocaleName proto WINAPI \
          lpLocaleName: LPCWSTR


;int
__crtLCMapStringEx proto WINAPI \
          lpLocaleName: LPCWSTR,
            dwMapFlags: DWORD,
              lpSrcStr: LPCWSTR,
                cchSrc: SINT,
             lpDestStr: LPWSTR,
               cchDest: SINT


;; wrapper for GetFileInformationByHandleEx, available only on Vista+
;BOOL
__crtGetFileInformationByHandleEx proto WINAPI \
                 hFile: HANDLE,
  FileInformationClass: FILE_INFO_BY_HANDLE_CLASS,
     lpFileInformation: LPVOID,
          dwBufferSize: DWORD


;; wrapper for SetFileInformationByHandle, available only on Vista+
;BOOL
__crtSetFileInformationByHandle proto WINAPI \
                 hFile: HANDLE,
  FileInformationClass: FILE_INFO_BY_HANDLE_CLASS,
     lpFileInformation: LPVOID,
          dwBufferSize: DWORD


;; wrapper function for GetTickCount64, available only on Vista+
;ULONGLONG
__crtGetTickCount64 proto WINAPI

endif  ;; _CRT_NTDDI_MIN GE NTDDI_VISTA

;; Helper function for Sleep
;void
__crtSleep proto WINAPI \
        dwMilliseconds: DWORD


;; Helper to load all necessary Win32 API function pointers
;void
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

;HANDLE
__crtCreateWinRTThread proto WINAPI \
        lpStartAddress: LPTHREAD_START_ROUTINE,
           lpParameter: LPVOID,
            lpThreadId: LPDWORD


;BOOL
__crtCloseWinRTThreadHandle proto WINAPI \
               hThread: HANDLE

;HANDLE
__crtGetCurrentWinRTThread proto WINAPI
;DWORD
__crtGetCurrentWinRTThreadId proto WINAPI
;BOOL
__crtGetExitCodeWinRTThread proto WINAPI \
               hThread: HANDLE,
           pdwExitCode: ptr DWORD

;HANDLE
__crtGetWinRTThreadWaitableHandle proto WINAPI \
               hThread: HANDLE

;DWORD
__crtGetWinRTThreadId proto WINAPI \
               hThread: HANDLE

;BOOL
__crtSetExitCodeWinRTThread proto WINAPI \
               hThread: HANDLE,
             wExitCode: DWORD

;DWORD
__crtWaitForWinRTThreadExit proto WINAPI \
               hThread: HANDLE,
               timeout: DWORD


;HANDLE
__crtCreateWinRTTimer proto WINAPI \
        lpStartAddress: WAITORTIMERCALLBACK,
           lpParameter: PVOID,
              duration: SINT,
              periodic: BOOL


;void
__crtDeleteWinRTTimer proto WINAPI \
                hTimer: HANDLE,
       waitForHandlers: BOOL

__crtCancelWinRTTimer proto WINAPI \
                hTimer: HANDLE,
       waitForHandlers: BOOL


;void
__crtExitProcessWinRT proto WINAPI
;DWORD
__crtGetFullPathNameWinRTW proto WINAPI \
              fileName: LPWSTR,
          bufferLength: DWORD,
                buffer: LPWSTR

;DWORD
__crtGetFullPathNameWinRTA proto WINAPI \
              fileName: char*,
          bufferLength: DWORD,
                buffer: LPSTR

;DWORD
__crtGetTempPathWinRTW proto WINAPI \
               maxBuff: SINT,
        tempPathBuffer: LPWSTR

;DWORD
__crtGetTempPathWinRTA proto WINAPI \
               maxBuff: SINT,
        tempPathBuffer: LPSTR


endif  ;; _CRT_APP
endif  ;; _INC_AWINC
endif  ;; _WIN32
