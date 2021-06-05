; CSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

main	  proto __cdecl :dword, :ptr, :ptr
_initterm proto __cdecl :ptr, :ptr

;;
;; pointers to initialization sections
;;
externdef __xi_a:ptr
externdef __xi_z:ptr
externdef __xt_a:ptr
externdef __xt_z:ptr

;public __ImageBase

	.code
;	org -0x1050
;	__ImageBase label byte
;	org 0

	dd 495A440Ah
	dd 564A4A50h
	db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

cstart::

mainCRTStartup proc frame

	_initterm( &__xi_a, &__xi_z )
	exit( main( __argc, __argv, _environ ) )

mainCRTStartup endp

	end cstart
