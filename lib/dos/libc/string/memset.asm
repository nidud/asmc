; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memset proc <usesds> uses di string:ptr, char:int_t, count:size_t

    ldr     di,string
    mov     cx,count
    mov     dx,di
    mov     ax,char
    rep     stosb
    mov     ax,dx
    movl    dx,es
    ret

memset endp

    end
