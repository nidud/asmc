; QUERYPERFORMANCECOUNTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include profileapi.inc

define NSEC_PER_SEC 1000000000

.code

 QueryPerformanceCounter proc WINAPI lpPerformanceCount:PLARGE_INTEGER
   .new ts:timespec
    .if ( !ldr(lpPerformanceCount) )
        .return( FALSE )
    .endif
    .ifsd ( clock_gettime(CLOCK_MONOTONIC, &ts) < 0 )
        .return( FALSE )
    .endif
    mov rcx,lpPerformanceCount
    mov rax,ts.tv_sec
  ifdef _WIN64
    imul rax,rax,NSEC_PER_SEC
    add rax,ts.tv_nsec
    mov [rcx],rax
  else
    mov edx,NSEC_PER_SEC
    mul edx
    add eax,ts.tv_nsec
    adc edx,0
    mov [ecx],eax
    mov [ecx+4],edx
  endif
    .return( TRUE )
    endp

    end
