; _STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include errno.inc

    .data
    flt STRFLT { { 0, 0, 0 }, 0, 0, 0 }

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
        lea esi,flt.mantissa

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
        mov ebx,[esi+8]
        mov esi,[esi+12]
if 0
        .if ( sign == '-' )

            neg esi
            neg ecx
            sbb esi,0
            neg edx
            sbb ecx,0
            neg eax
            sbb edx,0
        .endif
endif
        xor ecx,ecx
        .if eax || edx || ebx || esi
            .if esi
                bsr ecx,esi
                add ecx,96
            .elseif ebx
                bsr ecx,ebx
                add ecx,64
            .elseif edx
                bsr ecx,edx
                add ecx,32
            .else
                bsr ecx,eax
            .endif
            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch
            .while cl >= 32
                sub cl,32
                mov esi,ebx
                mov ebx,edx
                mov edx,eax
                xor eax,eax
            .endw
            shld esi,ebx,cl
            shld ebx,edx,cl
            shld edx,eax,cl
            shl eax,cl
            mov dword ptr flt.mantissa.l[0],eax
            mov dword ptr flt.mantissa.l[4],edx
            mov dword ptr flt.mantissa.h[0],ebx
            mov dword ptr flt.mantissa.h[4],esi
            shr ecx,8
            add ecx,Q_EXPBIAS
            .if flt.flags & _ST_NEGNUM
                or ecx,0x8000
            .endif
            .if flt.flags & _ST_ISHEX
                add ecx,flt.exponent
            .endif
            mov flt.mantissa.e,cx
        .else
            or flt.flags,_ST_ISZERO
        .endif
        mov ebx,ecx
        mov edi,flt.flags
        mov ax,flt.mantissa.e
        and eax,Q_EXPMASK

        .switch
          .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case eax >= Q_EXPMAX + Q_EXPBIAS
            or  ebx,0x7FFF
            xor eax,eax
            mov dword ptr flt.mantissa.l[0],eax
            mov dword ptr flt.mantissa.l[4],eax
            mov dword ptr flt.mantissa.h[0],eax
            mov dword ptr flt.mantissa.h[4],eax
            .if edi & _ST_ISNAN or _ST_INVALID
                or ebx,0x8000
                or byte ptr flt.mantissa.h[7],0x80
            .endif
        .endsw
        mov flt.mantissa.e,bx
        and ebx,Q_EXPMASK
        .if ebx >= 0x7FFF
            _set_errno(ERANGE)
        .elseif flt.exponent && !( flt.flags & _ST_ISHEX )
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

        _fltpackfp(&flt, &flt)

    .until 1
    lea eax,flt
    ret

_strtoflt endp

    END
