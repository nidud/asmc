; GETTICKCOUNT64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc

define NSEC_PER_MSEC 1000000

.code

GetTickCount64 proc WINAPI
   .new ts:timespec
    clock_gettime(CLOCK_MONOTONIC, &ts)
    mov rax,ts.tv_nsec
    xor edx,edx
    mov ecx,NSEC_PER_MSEC
    div rcx
  ifdef _WIN64
    imul rcx,ts.tv_sec,1000
    add rax,rcx
  else
    mov ecx,eax
    mov eax,ts.tv_sec
    mov edx,1000
    mul edx
    add eax,ecx
    adc edx,0
  endif
    ret
    endp

    end
