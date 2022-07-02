; _CQCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cqcvt() - Converts quad float to string
;

include fltintrn.inc

    .code

_cqcvt proc q:ptr real16, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local cvt:FLTINFO

    mov cvt.bufsize,512

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
    mov cvt.ndigits,precision

    xor ecx,ecx
    .if ( eax & _ST_E or _ST_G )
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3

    ; make space for '-' sign

    mov rdx,buffer
    inc rdx

    _flttostr( q, &cvt, rdx, flags )

    mov rax,buffer
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

_cqcvt endp

    end
