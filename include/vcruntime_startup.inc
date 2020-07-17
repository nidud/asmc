include vcruntime.inc

.enum _crt_argv_mode {
    _crt_argv_no_arguments,
    _crt_argv_unexpanded_arguments,
    _crt_argv_expanded_arguments,
    }

.enum _crt_exit_return_mode {
    _crt_exit_terminate_process,
    _crt_exit_return_to_caller
    }

.enum _crt_exit_cleanup_mode {
    _crt_exit_full_cleanup,
    _crt_exit_quick_cleanup,
    _crt_exit_no_cleanup
    }

externdef __current_exit_return_mode:_crt_exit_return_mode

__vcrt_initialize       proto __cdecl
__vcrt_uninitialize     proto __cdecl :__vcrt_bool
__vcrt_uninitialize_critical proto __cdecl
__vcrt_thread_attach    proto __cdecl
__vcrt_thread_detach    proto __cdecl

__isa_available_init    proto __cdecl
_get_startup_argv_mode  proto __cdecl

