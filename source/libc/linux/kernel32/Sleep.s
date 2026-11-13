; SLEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include synchapi.inc

.code

Sleep proc WINAPI dwMilliseconds:DWORD
   .new req:timespec
   .new rem:timespec
    ldr  eax,dwMilliseconds
    mov  ecx,1000
    xor  edx,edx
    div  rcx
    mov  req.tv_sec,rax
    imul rax,rdx,1000000
    mov  req.tv_nsec,rax
    nanosleep( &req, &rem )
    ret
    endp

    end
