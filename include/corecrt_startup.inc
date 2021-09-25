include corecrt.inc
include math.inc
include vcruntime_startup.inc

_seh_filter_dll proto __cdecl :ulong_t, :ptr EXCEPTION_POINTERS
_seh_filter_exe proto __cdecl :ulong_t, :ptr EXCEPTION_POINTERS

.enum _crt_app_type {
    _crt_unknown_app,
    _crt_console_app,
    _crt_gui_app
    }

_query_app_type proto __cdecl
_set_app_type proto __cdecl :_crt_app_type

CALLBACKC(_UserMathErrorFunctionPointer, :ptr _exception)

__setusermatherr proto __cdecl :_UserMathErrorFunctionPointer
_is_c_termination_complete proto __cdecl

_configure_narrow_argv proto __cdecl :_crt_argv_mode
_configure_wide_argv   proto __cdecl :_crt_argv_mode

_initialize_narrow_environment proto __cdecl
_initialize_wide_environment   proto __cdecl

_get_initial_narrow_environment proto __cdecl
_get_initial_wide_environment proto __cdecl

_get_narrow_winmain_command_line proto __cdecl
_get_wide_winmain_command_line proto __cdecl

__p__acmdln proto __cdecl
__p__wcmdln proto __cdecl

ifdef _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
    externdef _acmdln:ptr char_t
    externdef _wcmdln:ptr wchar_t
else
    _acmdln equ [__p__acmdln()]
    _wcmdln equ [__p__wcmdln()]
endif


CALLBACKC(_PVFV)
CALLBACKC(_PIFV)
CALLBACKC(_PVFI :int_t)

ifndef _M_CEE
_initterm   proto __cdecl :ptr _PVFV, :ptr _PVFV
_initterm_e proto __cdecl :ptr _PIFV, :ptr _PIFV
endif

ifndef _CRT_ONEXIT_T_DEFINED
define _CRT_ONEXIT_T_DEFINED

    CALLBACK(_onexit_t)
    ifdef _M_CEE
        CALLBACK(_onexit_m_t)
    endif
endif

_onexit_table_t struct
_first          ptr_t ?
_last           ptr_t ?
_end            ptr_t ?
_onexit_table_t ends

_initialize_onexit_table    proto __cdecl :ptr _onexit_table_t
_register_onexit_function   proto __cdecl :ptr _onexit_table_t, :_onexit_t
_execute_onexit_table       proto __cdecl :ptr _onexit_table_t

_crt_atexit                 proto __cdecl :_PVFV
_crt_at_quick_exit          proto __cdecl :_PVFV

if _CRT_FUNCTIONS_REQUIRED

__acrt_initialize           proto __cdecl
__acrt_uninitialize         proto __cdecl :__crt_bool
__acrt_uninitialize_critical proto __cdecl :__crt_bool
__acrt_thread_attach        proto __cdecl
__acrt_thread_detach        proto __cdecl

endif
