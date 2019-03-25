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

clock proc frame

  local ct:FILETIME

    GetSystemTimeAsFileTime( &ct )
    mov eax,ct.dwLowDateTime
    mov ecx,ct.dwHighDateTime
    shl rcx,32
    or  rax,rcx
    sub rax,start_tics
    mov ecx,10000
    xor edx,edx
    div rcx
    ret

clock endp

__inittime proc frame

  local ct:FILETIME

    GetSystemTimeAsFileTime( &ct )
    mov eax,ct.dwLowDateTime
    mov ecx,ct.dwHighDateTime
    shl rcx,32
    or  rax,rcx
    mov start_tics,rax
    xor eax,eax
    ret

__inittime endp

.pragma init(__inittime, 20)

    end
