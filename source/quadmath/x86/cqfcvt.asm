; CQFCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cqfcvt() - Converts quad float to string
;

include quadmath.inc
include string.inc

    .code

cqfcvt proc q:ptr, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local cvt:CVT_INFO

    mov edx,flags
    mov eax,'e'
    .if edx & FL_CAPEXP
        mov eax,'E'
    .endif
    mov cvt.expchar,eax

    mov ecx,precision
    mov eax,_ST_F
    .if ch_type == 'e'
        mov eax,_ST_E
    .elseif ch_type == 'g'
        mov eax,_ST_G
    .endif
    ;or  eax,NO_TRUNC
    mov cvt.flags,eax
    mov cvt.ndigits,ecx
    xor ecx,ecx
    .if eax & _ST_E
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3

    mov ecx,buffer
    inc ecx
    cvtq_a(q, &cvt, ecx, flags)

    mov eax,buffer
    .if ( cvt.sign == -1 )

        mov byte ptr [eax],'-'
    .else
        .for ( ecx = eax, dl = [eax] : dl : ecx++ )

            mov dl,[ecx+1]
            mov [ecx],dl
        .endf
    .endif
    ret

cqfcvt endp

    end
