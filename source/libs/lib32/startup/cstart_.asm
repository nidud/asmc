; CSTART_.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for Open Watcom (Win32)
;
include stdlib.inc

main_	  proto syscall
_initterm proto __cdecl :ptr, :ptr

externdef __xi_a:ptr	;; pointers to initialization sections
externdef __xi_z:ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

cstart_ proc

  local _exception_registration[2]:dword

	_initterm( &__xi_a, &__xi_z )
	mov ecx,__argc
	mov edx,__argv
	mov ebx,_environ
	mov eax,ecx
	exit(main_())

cstart_ endp

	END	cstart_
