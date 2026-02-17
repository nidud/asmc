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

ifndef _MSVCRT
externdef _CRTINIT_S:ptr ; pointers to initialization sections
externdef _CRTINIT_E:ptr
endif

ifdef __UNIX__

    .data
     __argv         array_t NULL
     _environ       array_t NULL
     __ImageBase    size_t 0
     __argc         int_t 0
     public         __ImageBase

elseifdef _MSVCRT

    .data
     __targv    tarray_t 0
     _tenviron  tarray_t 0
     _startup   _startupinfo { 0 }
     __argc     int_t 0

endif

    .code

ifdef __UNIX__

    option win64:0

_start proc
    xor ebp,ebp
    mov __argc,[rsp]
    mov _environ,&[rsp+rax*size_t+size_t*2]
    mov __argv,&[rsp+size_t]
ifdef _WIN64
    lea rax,_start
    mov rcx,imagerel _start
    sub rax,rcx
    mov __ImageBase,rax
    and spl,-16
endif
    _initterm( &_CRTINIT_S, &_CRTINIT_E )
    xor eax,eax
    exit( _tmain( __argc, __argv, _environ ) )
else
_tmainCRTStartup proc
ifdef _MSVCRT
    _tgetmainargs( addr __argc, addr __targv, addr _tenviron, 0, addr _startup )
    exit( _tmain( __argc, __targv, _tenviron ) )
else
ifndef _WIN64
    .new _exception_registration[2]:dword
endif
    _initterm( &_CRTINIT_S, &_CRTINIT_E )
    exit( _tmain( __argc, _targvcrt, _tenvironcrt ) )
endif
endif
    endp
    end
