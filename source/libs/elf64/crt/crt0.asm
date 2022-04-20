; CRT0.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for LIBC
;
include stdlib.inc

main      proto __cdecl :dword, :ptr, :ptr
_initterm proto __cdecl :ptr, :ptr

;
; pointers to initialization sections
;
externdef __xi_a:byte
externdef __xi_z:byte
externdef __xt_a:byte
externdef __xt_z:byte

    .data
     __argc     int_t 0
     __argv     array_t 0
     _environ   array_t 0

    .code

    dd 495A440Ah
    dd 564A4A50h
    db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

_start proc

    xor ebp,ebp
    mov __argc,[rsp]
    mov _environ,&[rsp+rax*8+16]
    mov __argv,&[rsp+8]

    _initterm( &__xi_a, &__xi_z )
    exit( main( __argc, __argv, _environ ) )

_start endp

    end
