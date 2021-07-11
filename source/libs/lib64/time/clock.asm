; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .data
    start_tics dq 0

    .code

clock proc

  local ct:FILETIME

    GetSystemTimeAsFileTime( &ct )
    mov rax,qword ptr ct.dwLowDateTime
    sub rax,start_tics
    mov ecx,10000
    xor edx,edx
    div rcx
    ret

clock endp

__inittime proc

  local ct:FILETIME

    GetSystemTimeAsFileTime( &ct )
    mov rax,qword ptr ct.dwLowDateTime
    mov start_tics,rax
    xor eax,eax
    ret

__inittime endp

.pragma init(__inittime, 20)

    end
