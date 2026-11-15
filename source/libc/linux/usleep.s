; USLEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include unistd.inc

define NSEC_PER_USEC 1000

.code

usleep proc usec:useconds_t
   .new req:timespec
    ldr eax,usec
    mov ecx,1000000
    xor edx,edx
    div ecx
    mov req.tv_sec,rax
    imul rdx,rdx,NSEC_PER_USEC
    mov req.tv_nsec,rdx
    .return nanosleep(&req, NULL)
    endp

    end
