; CSTART_.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for Open Watcom (Win32)
;
include stdlib.inc

if defined(_WIN64) or defined(__UNIX__)
define entry <>
else
define entry <cstart_>

ALIAS <argc>=<__argc>

main proto syscall :int_t, :ptr, :ptr

externdef __xi_a:ptr ; pointers to initialization sections
externdef __xi_z:ptr

    .code

cstart_ proc

  local _exception_registration[2]:dword

    _initterm( &__xi_a, &__xi_z )
    mov ecx,__argc
    mov rdx,__argv
    mov rbx,_environ
    mov eax,ecx
    exit(main(ecx, rdx, rbx))

cstart_ endp
endif
    end entry
