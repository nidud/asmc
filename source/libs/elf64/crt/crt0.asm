; CRT0.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

public  __ImageBase

main      proto __cdecl :dword, :ptr, :ptr
_initterm proto __cdecl :ptr, :ptr

;
; pointers to initialization sections
;
externdef __init_array_start:ptr
externdef __init_array_end:ptr

    .data
     __argc         int_t 0
     __argv         array_t 0
     _environ       array_t 0
     __ImageBase    size_t 0

    .code

    dd 495A440Ah
    dd 564A4A50h
    db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

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

    end
