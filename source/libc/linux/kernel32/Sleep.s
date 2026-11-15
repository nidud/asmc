; SLEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include synchapi.inc

define NSEC_PER_MSEC 1000000
define NSEC_PER_USEC 1000

.code

 Sleep proc WINAPI dwMilliseconds:DWORD
   .new req:timespec
   .new rem:timespec
    ldr  eax,dwMilliseconds
    mov  ecx,NSEC_PER_USEC
    xor  edx,edx
    div  rcx
  ifdef _WIN64
    mov  req.tv_sec,rax
    imul rdx,rdx,NSEC_PER_MSEC
    mov  req.tv_nsec,rdx
  else
    mov  req.tv_sec,eax
    imul edx,edx,NSEC_PER_MSEC
    mov  req.tv_nsec,edx
  endif
    .whilesd ( nanosleep( &req, &rem ) < 0 )
        .break .if ( errno != EINTR )
        mov req.tv_sec,rem.tv_sec
        mov req.tv_nsec,rem.tv_nsec
    .endw
    ret
    endp

    end
