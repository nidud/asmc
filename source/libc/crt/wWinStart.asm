; WWINSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC Windows Unicode
;
include stdlib.inc
include winbase.inc
include winuser.inc

ifdef __UNIX__
define entry <>
else
define entry <wWinStart>

externdef __xi_a:ptr
externdef __xi_z:ptr

    .code

wWinMainCRTStartup::

wWinStart proc uses rbx
ifndef _WIN64
  local _exception_registration[2]:dword
endif

    _initterm( &__xi_a, &__xi_z )
    mov rbx,GetModuleHandle( 0 )
    ExitProcess( wWinMain( rbx, 0, GetCommandLineW(), SW_SHOWDEFAULT ) )

wWinStart endp
endif
    end entry
