; DLLMAIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc
ifndef __UNIX__
include winbase.inc
include winuser.inc
include tchar.inc
ifndef _MSVCRT
externdef __xi_a:ptr
externdef __xi_z:ptr
externdef __xt_a:ptr
externdef __xt_z:ptr
endif
DllMain proto WINAPI :HANDLE, :DWORD, :ptr
endif

.code

_DllMainCRTStartup proc WINAPI hDllHandle:HANDLE, dwReason:DWORD, lpreserved:ptr
ifndef __UNIX__
ifndef _MSVCRT
ifndef _WIN64
  local _exception_registration[2]:dword
endif
    _initterm( &__xi_a, &__xi_z )
endif

    .new retcode:int_t = DllMain(hDllHandle, dwReason, lpreserved)

    .if ( eax == false && dwReason == DLL_PROCESS_ATTACH )

        ; The user's DllMain routine returned failure.  Unwind the init.

        DllMain(hDllHandle, DLL_PROCESS_DETACH, lpreserved)
        mov dwReason,DLL_PROCESS_DETACH
    .endif

    .if ( dwReason == DLL_PROCESS_DETACH )

        _initterm(&__xt_a, &__xt_z)
    .endif
    mov eax,retcode
endif
    ret

_DllMainCRTStartup endp

    end
