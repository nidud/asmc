; GETSYSTEMTIMEASFILETIME.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc
include timezoneapi.inc

define NSEC_PER_SEC 1000000000

.code

 GetSystemTimeAsFileTime proc WINAPI lpSystemTimeAsFileTime:LPFILETIME
   .new ts:timespec
    ldr rcx,lpSystemTimeAsFileTime
    .if ( !rcx )
        .return
    .endif
    clock_gettime(CLOCK_REALTIME, &ts)
    mov rcx,lpSystemTimeAsFileTime
  ifdef _WIN64
    mov     rax,ts.tv_sec
    imul    rax,rax,NSEC_PER_SEC
    add     rax,ts.tv_nsec
    mov     [rcx],rax
  else
    mov     eax,ts.tv_sec
    mov     edx,NSEC_PER_SEC
    imul    edx
    add     eax,ts.tv_nsec
    adc     edx,0
    mov     [ecx],eax
    mov     [ecx+4],edx
  endif
    ret
    endp

    end
