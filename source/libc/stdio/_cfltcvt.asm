; _CFLTCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cfltcvt() - Converts float (real8, real10, and real16) to string
;
include fltintrn.inc

    .code

_cfltcvt proc uses rbx p:ptr, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

   .new q:REAL16
   .new cvt:FLTINFO

    ldr rbx,buffer
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
    .if ( ch_type == 'e' )
        mov eax,_ST_E
    .elseif ( ch_type == 'g' )
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

    ; make space for '-' sign

    inc rbx
    _flttostr( p, &cvt, rbx, flags )
    lea rax,[rbx-1]

    .if ( cvt.sign == -1 )

        ; add sign

        mov byte ptr [rax],'-'
    .else

        ; copy string

        .for ( rcx = rax, dl = 1 : dl : rcx++ )

            mov dl,[rcx+1]
            mov [rcx],dl
        .endf
    .endif
    ret

_cfltcvt endp

    end
