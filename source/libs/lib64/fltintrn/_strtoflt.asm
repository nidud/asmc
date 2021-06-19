; _STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include errno.inc
include quadmath.inc

    .data
    flt STRFLT { { 0, 0, 0 }, 0, 0, 0 }

    .code

_strtoflt proc string:string_t

  local buffer[256]:char_t
  local digits:int_t
  local sign:int_t

    .repeat

        _fltsetflags(&flt, rcx, 0)
        .break .if eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID

        mov digits,_destoflt(&flt, &buffer)

        .if ( eax == 0 )

            or flt.flags,_ST_ISZERO
            .break
        .endif
        mov buffer[rax],0

        ;
        ; convert string to binary
        ;
        lea rdx,buffer
        xor eax,eax
        mov al,[rdx]
        mov sign,eax

        .if ( al == '+' || al == '-' )

            inc rdx
        .endif

        mov r8d,16
        .if !( flt.flags & _ST_ISHEX )

            mov r8d,10
        .endif
        lea r10,flt.mantissa
        mov r11,r10
        .while 1

            mov al,[rdx]
            .break .if !al

            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            .repeat
                movzx r9d,word ptr [r11]
                imul  r9d,r8d
                add   eax,r9d
                mov   [r11],ax
                add   r11,2
                shr   eax,16
            .untilcxz
            sub r11,16
            inc rdx
        .endw

        mov rax,[r10]
        mov rdx,[r10+8]

        xor ecx,ecx
        mov r8d,Q_EXPBIAS

        .if rax || rdx
            .if rdx         ; find most significant non-zero bit
                bsr rcx,rdx
                add ecx,64
            .else
                bsr rcx,rax
            .endif
            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch
            .if cl >= 64
                sub cl,64
                mov rdx,rax
                xor eax,eax
            .endif
            shld rdx,rax,cl
            shl rax,cl
            shr ecx,8       ; get shift count
            add ecx,r8d     ; calculate exponent
            mov [r10],rax
            mov [r10+8],rdx
        .else
            or flt.flags,_ST_ISZERO
        .endif
        mov r9d,flt.flags
        .if ( sign == '-' || r9d & _ST_NEGNUM )
            or cx,0x8000
        .endif

        mov r8d,ecx
        and r8d,Q_EXPMASK
        .switch
          .case r9d & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case r8d >= Q_EXPMAX + Q_EXPBIAS
            or  ecx,0x7FFF
            xor eax,eax
            mov flt.mantissa.l,rax
            mov flt.mantissa.h,rax
            .if r9d & _ST_ISNAN or _ST_INVALID
                or ecx,0x8000
                or byte ptr flt.mantissa.h[7],0x80
            .endif
        .endsw
        mov flt.mantissa.e,cx

        and ecx,Q_EXPMASK
        .if ecx >= 0x7FFF

            _set_errno(ERANGE)

        .elseif ( flt.exponent && !( flt.flags & _ST_ISHEX ) )

            _fltscale(&flt)
        .endif

        mov eax,flt.exponent
        add eax,digits
        dec eax
        .ifs eax > 4932
            or flt.flags,_ST_OVERFLOW
        .endif
        .ifs eax < -4932
            or flt.flags,_ST_UNDERFLOW
        .endif

    .until 1

    _fltpackfp(&flt, &flt)
    ret

_strtoflt endp

    END
