; _WTOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc

    .code

_wtof proc string:wstring_t

   .new buf[256]:char_t
   .new i:int_t = 0

    ldr rcx,string

    .for ( al = -1, rdx = &buf: al && i < lengthof(buf) : i++, rdx++, rcx += 2 )

        mov al,[rcx]
        mov [rdx],al
    .endf
    _strtoflt( &buf )
    __cvtq_sd( rax, rax )
ifdef __SSE__
    movsd xmm0,[rax]
else
    fld real8 ptr [rax]
endif
    ret

_wtof endp

    end
