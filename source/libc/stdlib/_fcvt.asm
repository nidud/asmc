; _FCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc

.code

_fcvt proc uses rsi rdi value:double_t, count:int_t, decimal:ptr int_t, sign:ptr int_t

   .new b[512]:char_t
   .new q:REAL16
   .new cvt:FLTINFO

    .if ( count > _CVTBUFSIZE-1 )

        mov count,_CVTBUFSIZE-1
    .endif

    mov cvt.bufsize,512
    mov cvt.expchar,'E'
    mov cvt.scale,0
    mov cvt.expwidth,3
    mov cvt.ndigits,count
    mov cvt.flags,_ST_F
    __cvtsd_q( &q, &value )
    _flttostr( &q, &cvt, &b, _ST_DOUBLE )

    xor eax,eax
    .if ( cvt.sign == -1 )
        inc eax
    .endif
    mov rcx,sign
    mov [rcx],eax
    mov edx,cvt.dec_place
    mov rcx,decimal
    mov [rcx],edx

    .for ( rsi=&b, rdi=_cvtbuf, ecx = 0 : ecx < edx : )

        lodsb
        .if ( al == 0 )
            .break
        .elseif ( al >= '0' && al <= '9' )
            inc ecx
            stosb
        .endif
    .endf
    .if ( al )
        .for ( ecx = 0 : ecx < count : )

            lodsb
            .if ( al == 0 )
                .break
            .elseif ( al >= '0' && al <= '9' )
                inc ecx
                stosb
            .endif
        .endf
    .endif
    .if ( al == 0 )

        .for ( al = '0' : ecx < count : ecx++ )
            stosb
        .endf
        mov byte ptr [rdi],0
    .else
        .if ( byte ptr [rsi] > '4' )
            inc byte ptr [rdi-1]
        .endif
        mov byte ptr [rdi],0
    .endif
    .return( _cvtbuf )

_fcvt endp

    end
