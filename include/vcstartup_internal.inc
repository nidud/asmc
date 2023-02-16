include Windows.inc
include corecrt_startup.inc
include internal_shared.inc
include intrin.inc
include process.inc
include vcruntime_startup.inc

ifndef _ONECORE
    ;_CRT_INTEROPSERVICES_DLLIMPORT("KERNEL32.dll", "EncodePointer", _CRT_CALLING_CONVENTION_WINAPI)
else
    ;_CRT_INTEROPSERVICES_DLLIMPORT("API-MS-WIN-CORE-UTIL-L1-1-0.dll", "EncodePointer", _CRT_CALLING_CONVENTION_WINAPI)
endif

EncodePointer proto WINAPI :PVOID

ifndef _ONECORE
    ;_CRT_INTEROPSERVICES_DLLIMPORT("KERNEL32.dll", "DecodePointer", _CRT_CALLING_CONVENTION_WINAPI)
else
    ;_CRT_INTEROPSERVICES_DLLIMPORT("API-MS-WIN-CORE-UTIL-L1-1-0.dll", "DecodePointer", _CRT_CALLING_CONVENTION_WINAPI)
endif

DecodePointer proto WINAPI :PVOID

ifdef _M_IX86
    ifdef _M_HYBRID
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX equ <"#">
    else
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX equ <"_">
    endif
    _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA equ <"_">
elseif defined(_M_X64) or defined(_M_ARM) or defined(_M_ARM64)
    _VCRT_DECLARE_ALTERNATE_NAME_PREFIX equ <"">
    _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA equ <"">
else
    .err <Unsupported architecture>
endif

_VCRT_DECLARE_ALTERNATE_NAME macro name, alternate_name
    .pragma comment(linker, "/alternatename:" \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX name \
        "=" \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX alternate_name)
    exitm<>
    endm

_VCRT_DECLARE_ALTERNATE_NAME_DATA macro name, alternate_name
    .pragma comment(linker, "/alternatename:" \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA name \
        "=" \
        _VCRT_DECLARE_ALTERNATE_NAME_PREFIX_DATA alternate_name)
    exitm<>
    endm


_VCRT_DEFINE_IAT_SYMBOL_MAKE_NAME macro f
ifdef _M_IX86
    exitm<_CRT_CONCATENATE(_imp__, f)>
else
    exitm<_CRT_CONCATENATE(__imp_, f)>
endif
    endm

_VCRT_DEFINE_IAT_SYMBOL macro f
    exitm<_VCRT_DEFINE_IAT_SYMBOL_MAKE_NAME(f)>
    endm

ifndef _M_CEE
    main        proto __CRTDECL :int_t, :ptr ptr char_t, :ptr ptr char_t
    wmain       proto __CRTDECL :int_t, :ptr ptr wchar_t, :ptr ptr wchar_t
    WinMain     proto WINAPI :HINSTANCE, :HINSTANCE, :LPSTR, :int_t
    wWinMain    proto WINAPI :HINSTANCE, :HINSTANCE, :LPWSTR, :int_t
endif

ifdef MRTDLL
    DllMain proto :HINSTANCE, :DWORD, :LPVOID
else
    DllMain proto WINAPI :HINSTANCE, :DWORD, :LPVOID
endif

CALLBACK(__scrt_dllmain_type, :HINSTANCE, :DWORD, :LPVOID)

.enum __scrt_module_type { dll, exe }

ifndef _M_CEE_PURE

    .enum __scrt_native_startup_state {
        uninitialized,
        initializing,
        initialized
        }

    externdef __scrt_current_native_startup_state:__scrt_native_startup_state
    externdef __scrt_native_startup_lock:ptr
    externdef __scrt_native_dllmain_reason:uint_t

    NATIVE_DLLMAIN_REASON_NO_REASON equ UINT_MAX

    __scrt_is_safe_for_managed_code proto {
        .switch (__scrt_native_dllmain_reason)
        .case DLL_PROCESS_ATTACH
        .case DLL_PROCESS_DETACH
            xor eax,eax
            .endc
        .default
            mov eax,1
        .endsw
        }

endif

_get_startup_argv_mode          proto __CRTDECL
_get_startup_commit_mode        proto __CRTDECL
_get_startup_file_mode          proto __CRTDECL
_get_startup_new_mode           proto __CRTDECL
_get_startup_thread_locale_mode proto __CRTDECL

__scrt_initialize_type_info     proto __CRTDECL
__scrt_uninitialize_type_info   proto __CRTDECL

_should_initialize_environment  proto __CRTDECL
_initialize_default_precision   proto __CRTDECL
_initialize_invalid_parameter_handler proto __CRTDECL
_initialize_denormal_control    proto __CRTDECL

__scrt_initialize_default_local_stdio_options proto __CRTDECL
__scrt_is_nonwritable_in_current_image proto __cdecl :ptr
__scrt_is_user_matherr_present  proto __cdecl
__scrt_is_ucrt_dll_in_use       proto __cdecl

__scrt_get_dyn_tls_init_callback proto __cdecl
__scrt_get_dyn_tls_dtor_callback proto __cdecl

ifdef _M_CEE_PURE
    __scrt_initialize_stdio_msvcrt_compatibility_mode proto __clrcall
    __clrcall __scrt_initialize_legacy_stdio_wide_specifier_mode proto __clrcall
    __clrcall __scrt_initialize_iso_stdio_wide_specifier_mode proto __clrcall
endif

externdef __crtWinrtInitType:int_t

__scrt_acquire_startup_lock     proto __cdecl
__scrt_release_startup_lock     proto __cdecl :bool

__scrt_initialize_crt           proto __cdecl :__scrt_module_type
__scrt_uninitialize_crt         proto __cdecl :bool, :bool

__scrt_initialize_onexit_tables proto __cdecl :__scrt_module_type

__scrt_dllmain_exception_filter proto __cdecl :HINSTANCE, :DWORD, :LPVOID,
        :__scrt_dllmain_type, :ulong_t, :PEXCEPTION_POINTERS

__scrt_dllmain_before_initialize_c      proto __cdecl
__scrt_dllmain_after_initialize_c       proto __cdecl
__scrt_dllmain_uninitialize_c           proto __cdecl
__scrt_dllmain_uninitialize_critical    proto __cdecl

__scrt_dllmain_crt_thread_attach        proto __cdecl
__scrt_dllmain_crt_thread_detach        proto __cdecl
__scrt_get_show_window_mode             proto __cdecl
__scrt_is_managed_app                   proto __cdecl
__scrt_initialize_winrt                 proto __cdecl
__scrt_set_unhandled_exception_filter   proto __cdecl
__scrt_fastfail                         proto __cdecl :uint_t

__scrt_throw_std_bad_alloc              proto __CRTDECL
__scrt_throw_std_bad_array_new_length   proto __CRTDECL

externdef _Init_global_epoch:int_t
_Init_thread_lock       proto __cdecl
_Init_thread_unlock     proto __cdecl
_Init_thread_wait       proto __cdecl :DWORD
_Init_thread_notify     proto __cdecl

__scrt_narrow_argv_policy::configure_argv proto {
    _configure_narrow_argv(_get_startup_argv_mode())
    }

__scrt_wide_argv_policy::configure_argv proto {
    _configure_wide_argv(_get_startup_argv_mode())
    }

__scrt_no_argv_policy::configure_argv proto {
    xor eax,eax
    }

__scrt_narrow_environment_policy::initialize_environment proto {
    _initialize_narrow_environment()
    }

__scrt_wide_environment_policy::initialize_environment proto {
    _initialize_wide_environment()
    }

__scrt_no_environment_policy::initialize_environment proto {
    xor eax,eax
    }

ifdef _SCRT_ENCLAVE_BUILD
__scrt_dll_argv_policy          equ <__scrt_no_argv_policy>
__scrt_dll_environment_policy   equ <__scrt_no_environment_policy>
else
__scrt_dll_argv_policy          equ <__scrt_narrow_argv_policy>
__scrt_dll_environment_policy   equ <__scrt_narrow_environment_policy>
endif
