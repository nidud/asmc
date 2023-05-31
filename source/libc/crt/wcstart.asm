; WCSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

ifdef __UNIX__
define entry <>
else
define entry <wcstart>

externdef __xi_a:ptr
externdef __xi_z:ptr

wmain proto __cdecl :dword, :ptr, :ptr

    .code

wcstart::

wmainCRTStartup proc
ifndef _WIN64
  local _exception_registration[2]:dword
endif
    _initterm( &__xi_a, &__xi_z )
    exit( wmain( __argc, __wargv, _wenviron ) )

wmainCRTStartup endp
endif
    end entry
