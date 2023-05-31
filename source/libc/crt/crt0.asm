; CRT0.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

main proto __cdecl :dword, :ptr, :ptr

ifdef __UNIX__
define entry <>
externdef __init_array_start:ptr
externdef __init_array_end:ptr
.data
 __argv         array_t NULL
 _environ       array_t NULL
 __ImageBase    size_t 0
 __argc         int_t 0
 public         __ImageBase
else
define entry <cstart>
externdef __xi_a:ptr ; pointers to initialization sections
externdef __xi_z:ptr
endif

    .code

ifdef __UNIX__

    option win64:0

_start proc

    xor ebp,ebp

    mov __argc,[rsp]
    mov _environ,&[rsp+rax*8+16]
    mov __argv,&[rsp+8]

    lea rax,_start
    mov rcx,imagerel _start
    sub rax,rcx
    mov __ImageBase,rax

    and spl,-16

    _initterm( &__init_array_start, &__init_array_end )
    exit( main( __argc, __argv, _environ ) )

_start endp

else

cstart::
_cstart::

mainCRTStartup proc
ifndef _WIN64
  local _exception_registration[2]:dword
endif
    _initterm( &__xi_a, &__xi_z )
    exit( main( __argc, __argv, _environ ) )

mainCRTStartup endp
endif
    end entry
