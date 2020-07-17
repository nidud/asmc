include cruntime.inc
include internal.inc
include stdlib.inc
include Windows.inc
include AppModel.inc
include awint.inc
include libloaderapi.inc

if defined (_M_IX86) or defined (_M_X64) or defined (_CORESYS) or defined (_KERNELX)
PFN_GetCurrentPackageId typedef proto :ptr UINT32, :ptr BYTE
endif

if not defined(_M_ARM) and (defined (_CORESYS) or defined (_KERNELX))

IsGetCurrentPackageIdPresent proto

    .code

__IsPackagedAppHelper proc private

    local retValue:LONG
    local bufferLength:UINT32
    local hPackageDll:HMODULE

    mov retValue,APPMODEL_ERROR_NO_PACKAGE
    mov bufferLength,0
    mov pfn,NULL

    .if IsGetCurrentPackageIdPresent()

        LoadLibraryExW(L"ext-ms-win-kernel32-package-current-l1-1-0.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32 )

        .if rax

            mov hPackageDll,rax

            .if GetProcAddress( rax, "GetCurrentPackageId" )

                assume rax:ptr PFN_GetCurrentPackageId
                rax( &bufferLength, NULL )
                assume rax:nothing

                .if eax == ERROR_INSUFFICIENT_BUFFER

                    FreeLibrary(hPackageDll)
                    .return 1
                .endif
            .endif

            FreeLibrary(hPackageDll)
        .endif
    .endif
    .return 0

__IsPackagedAppHelper endp

else

    .code

__IsPackagedAppHelper proc private

    local bufferLength:UINT32

    mov bufferLength,0

if defined (_M_IX86) or defined (_M_X64)
    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFN_GetCurrentPackageId, GetCurrentPackageId, pfn)

        pfn( &bufferLength, NULL )
    .endif

else
    GetCurrentPackageId( &bufferLength, NULL )
endif

    .if eax == ERROR_INSUFFICIENT_BUFFER

        .return 1
    .endif
    .return 0

__IsPackagedAppHelper endp

endif

__crtIsPackagedApp proc

ifdef _CRT_APP
    .return TRUE
else
    .data
     isPackaged int_t -1

    .code

    .if isPackaged < 0

        mov isPackaged,__IsPackagedAppHelper()
    .endif
    xor     eax,eax
    cmp     isPackaged,eax
    setg    al
endif
    ret

__crtIsPackagedApp endp

ifndef _CRT_APP

__crtGetShowWindowMode proc

    local startupInfo:STARTUPINFOW

    GetStartupInfoW(&startupInfo)

    mov eax,SW_SHOWDEFAULT

    .if startupInfo.dwFlags & STARTF_USESHOWWINDOW

        movzx eax,startupInfo.wShowWindow
    .endif
    ret

__crtGetShowWindowMode endp

__crtSetUnhandledExceptionFilter proc exceptionFilter:LPTOP_LEVEL_EXCEPTION_FILTER

    SetUnhandledExceptionFilter(rcx)
    ret

__crtSetUnhandledExceptionFilter endp

if (defined (_M_IX86) or defined (_M_X64))
__crtTerminateProcess proc uExitCode:UINT
    TerminateProcess(GetCurrentProcess(), uExitCode)
    ret
__crtTerminateProcess endp
endif

if defined (_M_IX86) or defined (_M_X64)
__crtUnhandledException proc exceptionInfo:ptr EXCEPTION_POINTERS

    SetUnhandledExceptionFilter(NULL)
    UnhandledExceptionFilter(exceptionInfo)
    ret

__crtUnhandledException endp
endif

ifdef _M_X64
__crtCapturePreviousContext proc pContextRecord:ptr CONTEXT

    local ControlPc:ULONG64
    local EstablisherFrame:ULONG64
    local ImageBase:ULONG64
    local FunctionEntry:PRUNTIME_FUNCTION
    local HandlerData:PVOID
    local frames:SINT

    RtlCaptureContext(pContextRecord)

    mov rcx,pContextRecord
    mov ControlPc,[rcx].CONTEXT._Rip

    .for (frames = 0: frames < 2: ++frames)

        mov FunctionEntry,RtlLookupFunctionEntry(ControlPc, &ImageBase, NULL)

        .if FunctionEntry != NULL

            RtlVirtualUnwind(0, ;; UNW_FLAG_NHANDLER
                             ImageBase,
                             ControlPc,
                             FunctionEntry,
                             pContextRecord,
                             &HandlerData,
                             &EstablisherFrame,
                             NULL)
        .else
            .break
        .endif
    .endf
    ret

__crtCapturePreviousContext endp
endif

ifdef _M_X64

__crtCaptureCurrentContext proc pContextRecord:ptr CONTEXT

    local ControlPc:ULONG64
    local EstablisherFrame:ULONG64
    local ImageBase:ULONG64
    local FunctionEntry:PRUNTIME_FUNCTION
    local HandlerData:PVOID

    RtlCaptureContext(pContextRecord)

    mov rcx,pContextRecord
    mov ControlPc,[rcx].CONTEXT._Rip
    mov FunctionEntry,RtlLookupFunctionEntry(ControlPc, &ImageBase, NULL)

    .if FunctionEntry != NULL
        RtlVirtualUnwind(0, ;; UNW_FLAG_NHANDLER
                            ImageBase,
                            ControlPc,
                            FunctionEntry,
                            pContextRecord,
                            &HandlerData,
                            &EstablisherFrame,
                            NULL)
    .endif
    ret

__crtCaptureCurrentContext endp
endif

endif

if _CRT_NTDDI_MIN LT NTDDI_VISTA

__crtGetTickCount64 proc

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNGETTICKCOUNT64, GetTickCount64, pfGetTickCount64)

        .return pfGetTickCount64()
    .endif
    GetTickCount()
    ret

__crtGetTickCount64 endp

__crtFlsAlloc proc lpCallback:PFLS_CALLBACK_FUNCTION

if _CRT_NTDDI_MIN GE NTDDI_WS03
    FlsAlloc(lpCallback)
else
    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLSALLOC, FlsAlloc, pfFlsAlloc)

        .return pfFlsAlloc(lpCallback)
    .endif
    TlsAlloc()
endif
    ret

__crtFlsAlloc endp

__crtFlsFree proc dwFlsIndex:DWORD
if _CRT_NTDDI_MIN GE NTDDI_WS03
    FlsFree(dwFlsIndex)
else
    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLSFREE, FlsFree, pfFlsFree)

        .return pfFlsFree(dwFlsIndex)
    .endif
    TlsFree(dwFlsIndex)
endif
    ret
__crtFlsFree endp

__crtFlsGetValue proc dwFlsIndex:DWORD
if _CRT_NTDDI_MIN GE NTDDI_WS03
    FlsGetValue(dwFlsIndex)
else
    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLSGETVALUE, FlsGetValue, pfFlsGetValue)

        .return pfFlsGetValue(dwFlsIndex)
    .endif
    TlsGetValue(dwFlsIndex)
endif
    ret
__crtFlsGetValue endp

__crtFlsSetValue proc dwFlsIndex:DWORD, lpFlsData:PVOID

if _CRT_NTDDI_MIN GE NTDDI_WS03
    FlsSetValue(dwFlsIndex, lpFlsData)
else
    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLSSETVALUE, FlsSetValue, pfFlsSetValue)

        .return pfFlsSetValue(dwFlsIndex, lpFlsData)
    .endif
    TlsSetValue(dwFlsIndex, lpFlsData)
endif
    ret
__crtFlsSetValue endp

__crtInitializeCriticalSectionEx proc lpCriticalSection:LPCRITICAL_SECTION,
        dwSpinCount:DWORD, Flags:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNINITIALIZECRITICALSECTIONEX, InitializeCriticalSectionEx, pfInitializeCriticalSectionEx)

        .return pfInitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, Flags)
    .endif
    InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount)
    .return TRUE
__crtInitializeCriticalSectionEx endp

__crtCreateEventExW proc lpEventAttributes:LPSECURITY_ATTRIBUTES,
        lpName:LPCWSTR, dwFlags:DWORD, dwDesiredAccess:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCREATEEVENTEXW, CreateEventExW, pfCreateEventExW)

        .return pfCreateEventExW(lpEventAttributes, lpName, dwFlags, dwDesiredAccess)
    .endif

    mov edx,dwFlags
    mov r8d,dwFlags
    and edx,CREATE_EVENT_MANUAL_RESET
    and r8d,CREATE_EVENT_INITIAL_SET
    .return CreateEventW(lpEventAttributes, edx, r8d, lpName)
__crtCreateEventExW endp

__crtCreateSemaphoreExW proc lpSemaphoreAttributes:LPSECURITY_ATTRIBUTES, lInitialCount:LONG,
        lMaximumCount:LONG, lpName:LPCWSTR, dwFlags:DWORD, dwDesiredAccess:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCREATESEMAPHOREEXW, CreateSemaphoreExW, pfCreateSemaphoreExW)

        .return pfCreateSemaphoreExW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, dwFlags, dwDesiredAccess)
    .endif
    .return CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName)
__crtCreateSemaphoreExW endp

__crtSetThreadStackGuarantee proc StackSizeInBytes:PULONG

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNSETTHREADSTACKGUARANTEE, SetThreadStackGuarantee, pfSetThreadStackGuarantee)

        .return pfSetThreadStackGuarantee(StackSizeInBytes)
    .endif
    .return FALSE
__crtSetThreadStackGuarantee endp

__crtCreateThreadpoolTimer proc pfnti:PTP_TIMER_CALLBACK, pv:PVOID, pcbe:PTP_CALLBACK_ENVIRON

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCREATETHREADPOOLTIMER, CreateThreadpoolTimer, pfCreateThreadpoolTimer)

        .return pfCreateThreadpoolTimer(pfnti, pv, pcbe)
    .endif
    .return NULL

__crtCreateThreadpoolTimer endp

__crtSetThreadpoolTimer proc pti:PTP_TIMER, pftDueTime:PFILETIME, msPeriod:DWORD, msWindowLength:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNSETTHREADPOOLTIMER, SetThreadpoolTimer, pfSetThreadpoolTimer)

        pfSetThreadpoolTimer(pti, pftDueTime, msPeriod, msWindowLength)
    .endif
    ret

__crtSetThreadpoolTimer endp

__crtWaitForThreadpoolTimerCallbacks proc pti:PTP_TIMER, fCancelPendingCallbacks:BOOL

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNWAITFORTHREADPOOLTIMERCALLBACKS, WaitForThreadpoolTimerCallbacks, pfWaitForThreadpoolTimerCallbacks)

        pfWaitForThreadpoolTimerCallbacks(pti, fCancelPendingCallbacks)
    .endif
    ret

__crtWaitForThreadpoolTimerCallbacks endp

__crtCloseThreadpoolTimer proc pti:PTP_TIMER

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCLOSETHREADPOOLTIMER, CloseThreadpoolTimer, pfCloseThreadpoolTimer)

        pfCloseThreadpoolTimer(pti)
    .endif
    ret

__crtCloseThreadpoolTimer endp

__crtCreateThreadpoolWait proc pfnwa:PTP_WAIT_CALLBACK, pv:PVOID, pcbe:PTP_CALLBACK_ENVIRON

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCREATETHREADPOOLWAIT, CreateThreadpoolWait, pfCreateThreadpoolWait)

        .return pfCreateThreadpoolWait(pfnwa, pv, pcbe)
    .endif
    .return NULL

__crtCreateThreadpoolWait endp

__crtSetThreadpoolWait proc pwa:PTP_WAIT, h:HANDLE, pftTimeout:PFILETIME

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNSETTHREADPOOLWAIT, SetThreadpoolWait, pfSetThreadpoolWait)

        pfSetThreadpoolWait(pwa, h, pftTimeout)
    .endif
    ret

__crtSetThreadpoolWait endp

__crtCloseThreadpoolWait proc pwa:PTP_WAIT

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCLOSETHREADPOOLWAIT, CloseThreadpoolWait, pfCloseThreadpoolWait)

        pfCloseThreadpoolWait(pwa)
    .endif
    ret

__crtCloseThreadpoolWait endp

__crtFlushProcessWriteBuffers proc

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLUSHPROCESSWRITEBUFFERS, FlushProcessWriteBuffers, pfFlushProcessWriteBuffers)

        pfFlushProcessWriteBuffers()
    .endif
    ret

__crtFlushProcessWriteBuffers endp

__crtFreeLibraryWhenCallbackReturns proc pci:PTP_CALLBACK_INSTANCE, _mod:HMODULE

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFREELIBRARYWHENCALLBACKRETURNS, FreeLibraryWhenCallbackReturns, pfFreeLibraryWhenCallbackReturns)

        pfFreeLibraryWhenCallbackReturns(pci, _mod)
    .endif
    ret

__crtFreeLibraryWhenCallbackReturns endp

__crtGetCurrentProcessorNumber proc

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNGETCURRENTPROCESSORNUMBER, GetCurrentProcessorNumber, pfGetCurrentProcessorNumber)

        .return pfGetCurrentProcessorNumber()
    .endif
    .return 0

__crtGetCurrentProcessorNumber endp

__crtGetLogicalProcessorInformation proc Buffer:PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, ReturnLength:PDWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNGETLOGICALPROCESSORINFORMATION, GetLogicalProcessorInformation, pfGetLogicalProcessorInformation)

        .return pfGetLogicalProcessorInformation(Buffer, ReturnLength)
    .endif
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED)
    .return FALSE

__crtGetLogicalProcessorInformation endp

__crtCreateSymbolicLinkW proc lpSymlinkFileName:LPCWSTR, lpTargetFileName:LPCWSTR, dwFlags:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNCREATESYMBOLICLINK, CreateSymbolicLinkW, pfCreateSymbolicLink)

        .return pfCreateSymbolicLink(lpSymlinkFileName, lpTargetFileName, dwFlags)
    .endif
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED)
    .return 0

__crtCreateSymbolicLinkW endp

__crtGetFileInformationByHandleEx proc hFile:HANDLE, FileInformationClass:FILE_INFO_BY_HANDLE_CLASS,
        lpFileInformation:LPVOID, dwBufferSize:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNGETFILEINFORMATIONBYHANDLEEX, GetFileInformationByHandleExW, pfGetFileInformationByHandleEx)

        .return pfGetFileInformationByHandleEx(hFile, FileInformationClass, lpFileInformation, dwBufferSize)
    .endif
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED)
    .return 0

__crtGetFileInformationByHandleEx endp

__crtSetFileInformationByHandle proc hFile:HANDLE, FileInformationClass:FILE_INFO_BY_HANDLE_CLASS,
        lpFileInformation:LPVOID, dwBufferSize:DWORD

    .if IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNSETFILEINFORMATIONBYHANDLE, SetFileInformationByHandleW, pfSetFileInformationByHandle)

        .return pfSetFileInformationByHandle(hFile, FileInformationClass, lpFileInformation, dwBufferSize)
    .endif
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED)
    .return 0

__crtSetFileInformationByHandle endp

endif

__crtSleep proc dwMilliseconds:DWORD
if defined (_CRT_APP) and  not defined (_KERNELX)
    local handle:HANDLE
    .if CreateEventExW( NULL, NULL, 0, EVENT_ALL_ACCESS )

        mov handle,rax
        mov edx,dwMilliseconds
        mov eax,1
        and edx,edx
        cmovz edx,eax
        WaitForSingleObjectEx( handle, edx, FALSE )
        CloseHandle(handle)
    .endif
else
    Sleep(ecx)
endif
    ret
__crtSleep endp

    .data
     encodedKERNEL32Functions PVOID eMaxKernel32Function dup(0)

    .code

__crtLoadWinApiPointers proc uses rbx

    mov rbx,GetModuleHandleW(L"kernel32.dll")

    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FlsAlloc)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FlsFree)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FlsGetValue)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FlsSetValue)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, InitializeCriticalSectionEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CreateEventExW)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CreateSemaphoreExW)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, SetThreadStackGuarantee)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CreateThreadpoolTimer)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, SetThreadpoolTimer)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, WaitForThreadpoolTimerCallbacks)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CloseThreadpoolTimer)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CreateThreadpoolWait)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, SetThreadpoolWait)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CloseThreadpoolWait)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FlushProcessWriteBuffers)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, FreeLibraryWhenCallbackReturns)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetCurrentProcessorNumber)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetLogicalProcessorInformation)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CreateSymbolicLinkW)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, SetDefaultDllDirectories)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, EnumSystemLocalesEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, CompareStringEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetDateFormatEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetLocaleInfoEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetTimeFormatEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetUserDefaultLocaleName)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, IsValidLocaleName)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, LCMapStringEx)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetCurrentPackageId)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetTickCount64)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, GetFileInformationByHandleExW)
    STOREENCODEDFUNCTIONPOINTER(rbx, KERNEL32, SetFileInformationByHandleW)
    ret

__crtLoadWinApiPointers endp

.pragma init(__crtLoadWinApiPointers, 70)

    end
