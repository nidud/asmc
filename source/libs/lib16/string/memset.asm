; MEMSET.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memset proc __ctype uses di string:ptr, char:int_t, count:size_t

    mov     cx,count
    lesl    di,string
    mov     ax,char
    rep     stosb
    mov     ax,word ptr string
    movl    dx,es
    ret

memset endp

    end
