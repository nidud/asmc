; WCSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

wmain	  proto __cdecl :dword, :ptr, :ptr
_initterm proto __cdecl :ptr, :ptr

externdef __xi_a:ptr
externdef __xi_z:ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

wcstart::

wmainCRTStartup proc

  local _exception_registration[2]:dword

	_initterm( &__xi_a, &__xi_z )
	exit( wmain( __argc, __wargv, _wenviron ) )

wmainCRTStartup endp

	end wcstart
