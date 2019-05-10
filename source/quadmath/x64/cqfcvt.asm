; CQFCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cqfcvt proc vectorcall q:real16, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

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

    mov cvt.flags,eax
    mov cvt.ndigits,ecx
    xor ecx,ecx
    .if eax & _ST_E
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3

    mov r8,buffer
    inc r8
    cvtq_a(xmm0, &cvt, r8, flags)

    mov rax,buffer
    .if cvt.sign == -1
        mov byte ptr [rax],'-'
    .else
        .for ( rcx = rax, dl = 1 : dl : rcx++ )

            mov dl,[rcx+1]
            mov [rcx],dl
        .endf
    .endif
    ret

cqfcvt endp

    end
