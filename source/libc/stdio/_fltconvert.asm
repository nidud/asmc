; _FLTCONVERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Converts float (real8, real10, and real16) to string
;
include string.inc
include fltintrn.inc

.code

_fltconvert proc uses rsi rdi rbx p:ptr, text:ptr, type:int_t, precision:int_t, flags:int_t

   .new q:REAL16
   .new cvt:FLTINFO

    ldr rbx,text
    mov cvt.bufsize,512

    .if ( flags & _ST_DOUBLE )
        mov p,__cvtsd_q( &q, p )
    .elseif ( flags & _ST_LONGDOUBLE )
        mov p,__cvtld_q( &q, p )
    .endif

    mov eax,'e'
    .if ( flags & _ST_CAPEXP )
        mov eax,'E'
    .endif
    mov cvt.expchar,eax

    mov eax,_ST_F
    .if ( type == 'e' )
        mov eax,_ST_E
    .elseif ( type == 'g' )
        mov eax,_ST_G
    .endif
    mov cvt.flags,eax

    xor ecx,ecx
    .if ( eax & _ST_E or _ST_G )
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3
    mov cvt.ndigits,precision

    _flttostr( p, &cvt, rbx, flags )

    ; '#' and precision == 0 means force a decimal point

    .if ( ( flags & _ST_ALTERNATE ) && !precision )

        _forcdecpt( rbx )
    .endif

    ; 'g' format means crop zero unless '#' given

    .if ( type == 'g' && !( flags & _ST_ALTERNATE ) )

        _cropzeros( rbx )
    .endif

    strlen( rbx ) ; compute length of text
    .if ( flags & _ST_UNICODE )

        mov rdx,rbx
        mov ebx,eax
        lea  rcx,[rax+1]
        lea  rsi,[rdx+rax]
        lea  rdi,[rdx+rax*2]
        xor  eax,eax
        std
        .repeat
            lodsb
            stosw
        .untilcxz
        cld
        mov eax,ebx
    .endif

    ; check if result was negative

    .if ( cvt.sign == -1 )

        neg eax
    .endif
    ret

_fltconvert endp

    end
