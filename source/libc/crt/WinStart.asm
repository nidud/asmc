; WINSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC Windows
;
include stdlib.inc
include winbase.inc
include winuser.inc

ifdef __UNIX__
define entry <>
else
define entry <WinStart>

externdef __xi_a:ptr
externdef __xi_z:ptr

    .code

WinMainCRTStartup::

WinStart proc uses rbx
ifndef _WIN64
  local _exception_registration[2]:dword
endif

    _initterm( &__xi_a, &__xi_z )

    mov rbx,GetModuleHandle( 0 )
    ExitProcess( WinMain( rbx, 0, GetCommandLineA(), SW_SHOWDEFAULT ) )

WinStart endp
endif
    end entry
