; GETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include linux/kernel.inc

    .code

getcwd proc uses rbx buffer:string_t, maxlen:int_t

    mov rbx,rdi
    .ifsd ( sys_getcwd(rdi, esi) < 0 )

        neg eax
        _set_errno(eax)
        .return(NULL)
    .endif
    .return( rbx )

getcwd endp

    end
