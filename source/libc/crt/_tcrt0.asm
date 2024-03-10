; _TCRT0.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;

include stdlib.inc
include tchar.inc

_tmain proto __cdecl :dword, :ptr, :ptr

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

define entry <_tmainCRTStartup>

ifdef _MSVCRT
    .data
     __targv    tarray_t 0
     _tenviron  tarray_t 0
     _startup   _startupinfo { 0 }
     __argc     int_t 0
else
externdef __xi_a:ptr ; pointers to initialization sections
externdef __xi_z:ptr
endif

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
    xor eax,eax
    exit( _tmain( __argc, __argv, _environ ) )

_start endp

else

ifdef _WIN64
ifdef _UNICODE
_wcstart::
else
_cstart::
endif
else
ifdef _UNICODE
wcstart::
else
cstart::
endif
endif

_tmainCRTStartup proc

ifdef _MSVCRT
    _tgetmainargs( addr __argc, addr __targv, addr _tenviron, 0, addr _startup )
else
ifndef _WIN64
  local _exception_registration[2]:dword
endif
    _initterm( &__xi_a, &__xi_z )
endif
    exit( _tmain( __argc, __targv, _tenviron ) )

_tmainCRTStartup endp

endif

    end entry
