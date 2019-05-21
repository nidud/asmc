; _STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include errno.inc

    .data
    real real16 0.0
    flt STRFLT <0,0,0,real>

    .code

_strtoflt proc uses esi edi ebx string:string_t

  local buffer[128]:char_t
  local digits:int_t
  local sign:int_t

    .repeat

        _fltsetflags(&flt, string, 0)
        .break .if eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID

        mov digits,_destoflt(&flt, &buffer)
        mov edx,flt.mantissa

        .if ( eax == 0 )

            or flt.flags,_ST_ISZERO
            .break
        .endif
        mov buffer[eax],0

        ;
        ; convert string to binary
        ;
        lea edx,buffer
        xor eax,eax
        mov al,[edx]
        mov sign,eax

        .if ( al == '+' || al == '-' )

            inc edx
        .endif

        mov ebx,16
        .if !( flt.flags & _ST_ISHEX )

            mov ebx,10
        .endif
        mov esi,flt.mantissa

        .while 1

            mov al,[edx]
            .break .if !al

            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            .repeat
                movzx edi,word ptr [esi]
                imul  edi,ebx
                add   eax,edi
                mov   [esi],ax
                add   esi,2
                shr   eax,16
            .untilcxz
            sub esi,16
            inc edx
        .endw

        mov eax,[esi]
        mov edx,[esi+4]
        mov ecx,[esi+8]
        mov esi,[esi+12]

        .if ( sign == '-' )

            neg esi
            neg ecx
            sbb esi,0
            neg edx
            sbb ecx,0
            neg eax
            sbb edx,0
        .endif
        ;
        ; get bit-count of number
        ;
        xor ebx,ebx
        bsr ebx,esi
        .ifz
            bsr ebx,ecx
            .ifz
                bsr ebx,edx
                .ifz
                    bsr ebx,eax
                .else
                    add ebx,32
                .endif
            .else
                add ebx,64
            .endif
        .else
            add ebx,96
        .endif
        .ifnz
            inc ebx
        .endif

        .if ebx

            xchg ebx,ecx
            mov edi,Q_SIGBITS
            sub edi,ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            .if ecx > Q_SIGBITS

                sub ecx,Q_SIGBITS
                ;
                ; or 0x10000 --> 0x1000
                ;
                .while cl >= 32
                    mov eax,edx
                    mov edx,ebx
                    mov ebx,esi
                    xor esi,esi
                    sub cl,32
                .endw
                shrd eax,edx,cl
                shrd edx,ebx,cl
                shrd ebx,esi,cl
                shr esi,cl

            .elseif edi

                mov ecx,edi
                .while cl >= 32
                    mov esi,ebx
                    mov ebx,edx
                    mov edx,eax
                    xor eax,eax
                    sub cl,32
                .endw
                shld esi,ebx,cl
                shld ebx,edx,cl
                shld edx,eax,cl
                shl eax,cl
            .endif
            mov ecx,flt.mantissa
            mov [ecx],eax
            mov [ecx+4],edx
            mov [ecx+8],ebx
            mov [ecx+12],esi
            ;
            ; create exponent bias and mask
            ;
            mov ebx,Q_EXPBIAS+Q_SIGBITS-1
            sub ebx,edi
            and ebx,Q_EXPMASK ; remove sign bit
            .if flt.flags & _ST_NEGNUM
                or ebx,0x8000
            .endif
            .if flt.flags & _ST_ISHEX
                add ebx,flt.exponent
            .endif
            mov [ecx+14],bx
        .else
            or flt.flags,_ST_ISZERO
        .endif

        mov edi,flt.flags
        mov ecx,flt.mantissa
        mov ax,[ecx+14]
        and eax,Q_EXPMASK
        mov edx,1

        .switch
          .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
            mov edx,0x7FFF0000
            .if edi & _ST_ISNAN or _ST_INVALID
                or edx,0x00004000
            .endif
            .endc
          .case edi & _ST_OVERFLOW
          .case eax >= Q_EXPMAX + Q_EXPBIAS
            mov edx,0x7FFF0000
            .if edi & _ST_NEGNUM
                or edx,0x80000000
            .endif
            .endc
          .case edi & _ST_UNDERFLOW
            xor edx,edx
            .endc
        .endsw

        .if edx != 1

            xor eax,eax
            mov [ecx+0x00],eax
            mov [ecx+0x04],eax
            mov [ecx+0x08],eax
            mov [ecx+0x0C],edx
            _set_errno(ERANGE)

        .elseif flt.exponent && !( flt.flags & _ST_ISHEX )

            _fltscale(&flt)
        .endif

        .if flt.flags & _ST_NEGNUM

            mov edx,flt.mantissa
            or byte ptr [edx+15],0x80
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
    lea eax,flt
    ret

_strtoflt endp

    END
