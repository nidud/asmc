; _GCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc

.code

_gcvt proc uses rbx value:double_t, digits:int_t, buffer:string_t

   .new q:REAL16
   .new cvt:FLTINFO

    ldr rbx,buffer
    mov cvt.bufsize,_CVTBUFSIZE-1
    mov cvt.expchar,'e'
    mov cvt.scale,1
    mov cvt.expwidth,3
    mov cvt.ndigits,digits
    mov cvt.flags,_ST_G
    __cvtsd_q( &q, &value )
    inc rbx
    _flttostr( &q, &cvt, rbx, _ST_DOUBLE )

    lea rax,[rbx-1]
    .if ( cvt.sign == -1 )
        mov byte ptr [rax],'-'
    .else
        .for ( rcx = rax, dl = 1 : dl : rcx++ )

            mov dl,[rcx+1]
            mov [rcx],dl
        .endf
    .endif
    ret

_gcvt endp

    end
