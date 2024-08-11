; STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include errno.inc

    .data
    flt STRFLT { { 0, 0, 0 }, 0, 0, 0 }

    .code

_strtoflt proc __ccall uses rsi rdi rbx string:string_t

    .new buffer[256]:char_t
    .new digits:int_t
    .new sign:int_t

    .repeat

        _fltsetflags( &flt, string, 0 )
        .break .if ( eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID )

        mov digits,_destoflt( &flt, &buffer )

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

        mov ebx,16
        .if !( flt.flags & _ST_ISHEX )

            mov ebx,10
        .endif
        lea rsi,flt.mantissa

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
                movzx edi,word ptr [rsi]
                imul  edi,ebx
                add   eax,edi
                mov   [rsi],ax
                add   rsi,2
                shr   eax,16
            .untilcxz
            sub rsi,16
            inc rdx
        .endw

        xor ecx,ecx

ifdef _WIN64

        mov rax,flt.mantissa.l
        mov rdx,flt.mantissa.h

        .if ( rax || rdx )

            .if ( rdx )     ; find most significant non-zero bit
                bsr rcx,rdx
                add ecx,64
            .else
                bsr rcx,rax
            .endif

            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch

            .if ( cl >= 64 )

                sub cl,64
                mov rdx,rax
                xor eax,eax
            .endif

            shld rdx,rax,cl
            shl rax,cl
            mov flt.mantissa.l,rax
            mov flt.mantissa.h,rdx
else

        mov eax,dword ptr flt.mantissa.l[0]
        mov edx,dword ptr flt.mantissa.l[4]
        mov ebx,dword ptr flt.mantissa.h[0]
        mov esi,dword ptr flt.mantissa.h[4]

        .if ( eax || edx || ebx || esi )

            .if ( esi )
                bsr ecx,esi
                add ecx,96
            .elseif ( ebx )
                bsr ecx,ebx
                add ecx,64
            .elseif ( edx )
                bsr ecx,edx
                add ecx,32
            .else
                bsr ecx,eax
            .endif

            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch

            .while ( cl >= 32 )

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
endif

            shr ecx,8           ; get shift count
            add ecx,Q_EXPBIAS   ; calculate exponent
            .if ( flt.flags & _ST_ISHEX )
                add ecx,flt.exponent
            .endif
        .else
            or flt.flags,_ST_ISZERO
        .endif

        mov edx,flt.flags
        .if ( sign == '-' || edx & _ST_NEGNUM )
            or cx,0x8000
        .endif

        mov ebx,ecx
        and ebx,Q_EXPMASK
        .switch
          .case edx & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case ebx >= Q_EXPMAX + Q_EXPBIAS
            or  ecx,0x7FFF
            xor eax,eax
ifdef _WIN64
            mov flt.mantissa.l,rax
            mov flt.mantissa.h,rax
else
            mov dword ptr flt.mantissa.l[0],eax
            mov dword ptr flt.mantissa.l[4],eax
            mov dword ptr flt.mantissa.h[0],eax
            mov dword ptr flt.mantissa.h[4],eax
endif
            .if ( edx & _ST_ISNAN or _ST_INVALID )

                or ecx,0x8000
                or byte ptr flt.mantissa.h[7],0x80
            .endif
        .endsw
        mov flt.mantissa.e,cx

        and ecx,Q_EXPMASK
        .if ( ecx >= 0x7FFF )

            mov qerrno,ERANGE

        .elseif ( flt.exponent && !( flt.flags & _ST_ISHEX ) )

            _fltscale( &flt )
        .endif

        mov eax,flt.exponent
        add eax,digits
        dec eax
        .ifs ( eax > 4932 )
            or flt.flags,_ST_OVERFLOW
        .endif
        .ifs ( eax < -4932 )
            or flt.flags,_ST_UNDERFLOW
        .endif
    .until 1
    _fltpackfp( &flt, &flt )
    ret

_strtoflt endp

    end
