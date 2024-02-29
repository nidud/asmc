; _TWINSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC Windows Unicode
;
include stdlib.inc

ifdef __UNIX__

define entry <>

else

include winbase.inc
include winuser.inc
include tchar.inc

define entry <_tWinMainCRTStartup>

externdef __xi_a:ptr
externdef __xi_z:ptr

    .code

ifdef _UNICODE
wWinStart::
else
WinStart::
endif

_tWinMainCRTStartup proc uses rbx

ifndef _WIN64
  local _exception_registration[2]:dword
endif

    _initterm( &__xi_a, &__xi_z )
    mov rbx,GetModuleHandle( 0 )
    ExitProcess( _tWinMain( rbx, 0, GetCommandLine(), SW_SHOWDEFAULT ) )

_tWinMainCRTStartup endp

endif

    end entry
