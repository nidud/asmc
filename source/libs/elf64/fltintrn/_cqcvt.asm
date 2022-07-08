; _CQCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cqcvt() - Converts quad float to string
;

include fltintrn.inc

    .code

_cqcvt proc uses rbx q:ptr real16, buffer:string_t, ch_type:int_t, precision:int_t, flag:int_t

  local cvt:FLTINFO

    mov cvt.bufsize,512
    mov r10d,flag
    mov eax,'e'
    .if r10d & _ST_CAPEXP
        mov eax,'E'
    .endif
    mov cvt.expchar,eax

    mov eax,_ST_F
    .if ch_type == 'e'
        mov eax,_ST_E
    .elseif ch_type == 'g'
        mov eax,_ST_G
    .endif
    mov cvt.flags,eax

    xor ebx,ebx
    .if eax & _ST_E or _ST_G
        inc ebx
    .endif
    mov cvt.scale,ebx
    mov cvt.expwidth,3
    mov cvt.ndigits,precision

    mov rbx,buffer

    ; make space for '-' sign

    _flttostr(q, &cvt, &[buffer+1], r10d)

    mov rax,rbx
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
