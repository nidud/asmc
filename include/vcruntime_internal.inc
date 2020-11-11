
if not defined(_VCRT_BUILD) and not defined(_VCRT_ALLOW_INTERNALS)
    .err <ERROR: Use of C Runtime library internal header file.>
endif

_WIN32_FUSION equ 0x0100

include malloc.inc
include vcruntime.inc
include vcruntime_startup.inc
include vcruntime_string.inc
include crtdbg.inc
include eh.inc
include internal_shared.inc
include isa_availability.inc
include stdbool.inc
include Windows.inc
include evntprov.inc

ifndef _VCRT_WIN32_WINNT
_VCRT_WIN32_WINNT equ _WIN32_WINNT_WINXP
endif

CALLBACKC(_PIFV)

__vcrt_initialize_ptd proto __cdecl
__vcrt_uninitialize_ptd proto __cdecl

__vcrt_initialize_locks proto __cdecl
__vcrt_uninitialize_locks proto __cdecl

externdef __isa_available:int_t

if defined(_M_IX86) or defined(_M_X64)
    externdef __isa_enabled:int_t
    externdef __favor:int_t
endif

ifndef _M_CEE
    CALLBACK(GUARDCF_CHECK_ROUTINE, :uintptr_t)
    externdef __guard_check_icall_fptr:GUARDCF_CHECK_ROUTINE
    _GUARD_CHECK_ICALL macro FPTR
        exitm<__guard_check_icall_fptr(FPTR)>
        endm
else
    _GUARD_CHECK_ICALL macro FPTR
        exitm<>
        endm
endif

ifndef DECLSPEC_GUARD_SUPPRESS
    DECLSPEC_GUARD_SUPPRESS macro
        exitm<__declspec(guard(suppress))>
        endm
endif

.enum __vcrt_lock_id {
    __vcrt_undname_lock,
    __vcrt_lock_count
    }

_VCRT_SPINCOUNT equ 4000

__vcrt_lock     proto __cdecl :__vcrt_lock_id
__vcrt_unlock   proto __cdecl :__vcrt_lock_id

__telemetry_main_invoke_trigger proto __cdecl :HINSTANCE
__telemetry_main_return_trigger proto __cdecl :HINSTANCE
__vcrt_initialize_telemetry_provider proto __cdecl
__vcrt_uninitialize_telemetry_provider proto __cdecl

__vcrt_ptd struct

    _NLG_dwCode         ULONG ?
    _unexpected         unexpected_handler ?
    _translator         PVOID ?
    _purecall           PVOID ?
    _curexception       PVOID ?
    _curcontext         PVOID ?
    _ProcessingThrow    int_t ?
    _curexcspec         PVOID ?
    _cxxReThrow         int_t ?

if defined(_M_X64) or defined(_M_ARM) or defined(_M_ARM64) or defined(_M_HYBRID)
    _pExitContext       PVOID ?
    _pUnwindContext     PVOID ?
    _pFrameInfoChain    PVOID ?
    _ImageBase          uintptr_t ?
    _ThrowImageBase     uintptr_t ?
    _pForeignException  PVOID ?
elseifdef _M_IX86
    _pFrameInfoChain    PVOID ?
endif

__vcrt_ptd ends

__vcrt_getptd           proto __cdecl
__vcrt_getptd_noexit    proto __cdecl
__vcrt_getptd_noinit    proto __cdecl
__vcrt_freeptd          proto __cdecl :ptr __vcrt_ptd
__vcrt_freefls          proto WINAPI :ptr


ifdef _VCRT_ENCLAVE_BUILD

__vcrt_FlsAlloc proto :PFLS_CALLBACK_FUNCTION {
        TlsAlloc()
        }
__vcrt_FlsFree proto :DWORD {
        TlsFree(_1)
        }
__vcrt_FlsGetValue proto :DWORD {
        return TlsGetValue(_1)
        }
__vcrt_FlsSetValue proto :DWORD, :ptr {
        TlsSetValue(_1, _2)
        }
__vcrt_InitializeCriticalSectionEx proto :LPCRITICAL_SECTION, :DWORD, :DWORD {
        InitializeCriticalSectionEx(_1, _2, _3)
        }
__vcrt_EncodePointer proto :ptr {
        mov rax,_1
        }

elseif not defined(_VCRT_WINDOWS_BUILD) and (defined(_ONECORE) or _VCRT_WIN32_WINNT GE _WIN32_WINNT_VISTA)


__vcrt_FlsAlloc proto :PFLS_CALLBACK_FUNCTION {
        FlsAlloc(_1)
        }
__vcrt_FlsFree proto :DWORD {
        FlsFree(_1)
        }
__vcrt_FlsGetValue proto :DWORD {
        FlsGetValue(_1)
        }
__vcrt_FlsSetValue proto :DWORD, :ptr {
        FlsSetValue(_1, _2)
        }
__vcrt_InitializeCriticalSectionEx proto :LPCRITICAL_SECTION, :DWORD, :DWORD {
        InitializeCriticalSectionEx(_1, _2, _3)
        }
__vcrt_EncodePointer proto :ptr {
        EncodePointer(_1)
        }

else

__vcrt_FlsAlloc         proto :PFLS_CALLBACK_FUNCTION
__vcrt_FlsFree          proto :DWORD
__vcrt_FlsGetValue      proto :DWORD
__vcrt_FlsSetValue      proto :DWORD, :ptr
__vcrt_InitializeCriticalSectionEx proto :LPCRITICAL_SECTION, :DWORD, :DWORD
__vcrt_EncodePointer    proto :ptr

__vcrt_EncodePointer proto :ptr {
        EncodePointer(_1)
        }

endif

ifdef _CRT_WINDOWS
    __vcrt_GetModuleFileNameW   equ <GetModuleFileNameW>
    __vcrt_GetModuleHandleW     equ <GetModuleHandleW>
    __vcrt_LoadLibraryExW       equ <LoadLibraryExW>
else
    __vcrt_GetModuleFileNameW   proto __cdecl :HMODULE, :LPWSTR, :DWORD
    __vcrt_GetModuleHandleW     proto __cdecl :LPCWSTR
    __vcrt_LoadLibraryExW       proto __cdecl :LPCWSTR, :HANDLE, :DWORD
endif

__vcrt_initialize_winapi_thunks proto __cdecl
__vcrt_uninitialize_winapi_thunks proto __cdecl :BOOL
__vcrt_initialize_pure_virtual_call_handler proto __cdecl

_ValidateImageBase proto __cdecl :PBYTE
_FindPESection proto __cdecl :PBYTE, :DWORD_PTR
_IsNonwritableInCurrentImage proto __cdecl :ptr

ifdef __cplusplus
    __type_info_node struct
    _Header _SLIST_HEADER <>
    __type_info_node ends
    __std_type_info_destroy_list proto __cdecl :ptr __type_info_node
endif

if defined(_VCRT_WINDOWS_BUILD) and defined(_CRT_GLOBAL_STATE_ISOLATION)
    _o__callnewh proto __cdecl :size_t
    _callnewh equ <_o__callnewh>
endif

