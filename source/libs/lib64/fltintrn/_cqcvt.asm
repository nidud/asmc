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

    mov r10d,flags
    mov eax,'e'
    .if r10d & _ST_CAPEXP
        mov eax,'E'
    .endif
    mov cvt.expchar,eax

    mov eax,_ST_F
    .if r8b == 'e'
        mov eax,_ST_E
    .elseif r8b == 'g'
        mov eax,_ST_G
    .endif
    mov cvt.flags,eax
    mov cvt.ndigits,r9d

    xor r8d,r8d
    .if eax & _ST_E
        inc r8d
    .endif
    mov cvt.scale,r8d
    mov cvt.expwidth,3

    ; make space for '-' sign

    _flttostr(rcx, &cvt, &[rdx+1], r10d)

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
