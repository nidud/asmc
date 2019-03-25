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
    mov eax,ct.dwLowDateTime
    mov edx,ct.dwHighDateTime
    sub eax,dword ptr start_tics
    sbb edx,dword ptr start_tics[4]
    mov ecx,10000
    div ecx
    ret

clock endp

__inittime proc

  local ct:FILETIME

    GetSystemTimeAsFileTime( &ct )
    mov eax,ct.dwLowDateTime
    mov edx,ct.dwHighDateTime
    mov dword ptr start_tics,eax
    mov dword ptr start_tics[4],edx
    xor eax,eax
    ret

__inittime endp

.pragma init(__inittime, 20)

    END
