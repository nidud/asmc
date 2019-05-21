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

    option win64:nosave

_strtoflt proc string:string_t

  local buffer[128]:char_t
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
        mov r10,flt.mantissa
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

        .if ( sign == '-' )

            neg rdx
            neg rax
            sbb rdx,0
        .endif
        ;
        ; get bit-count of number
        ;
        xor ecx,ecx
        bsr rcx,rdx
        .ifz
            bsr rcx,rax
        .else
            add ecx,64
        .endif
        .ifnz
            inc ecx
        .endif

        .if ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            mov r8d,Q_SIGBITS
            mov r9d,r8d
            sub r9d,ecx

            .if ecx > r8d
                sub ecx,r8d
                ;
                ; or 0x10000 --> 0x1000
                ;
                .if cl >= 64
                    mov rax,rdx
                    xor edx,edx
                    sub cl,64
                .endif
                shrd rax,rdx,cl
                shr rdx,cl

            .elseif r9d

                mov ecx,r9d
                .if cl >= 64
                    mov rdx,rax
                    xor eax,eax
                    sub cl,64
                .endif
                shld rdx,rax,cl
                shl rax,cl

            .endif
            mov [r10],rax
            mov [r10+8],rdx
            ;
            ; create exponent bias and mask
            ;
            mov ecx,Q_EXPBIAS+Q_SIGBITS-1
            sub ecx,r9d         ; - shift count
            and ecx,Q_EXPMASK   ; remove sign bit
            .if flt.flags & _ST_NEGNUM
                or cx,0x8000
            .endif
            mov [r10+14],cx
        .else
            or flt.flags,_ST_ISZERO
        .endif


        mov ecx,flt.flags
        mov ax,[r10+14]
        and eax,Q_EXPMASK
        mov edx,1

        .switch
          .case ecx & _ST_ISNAN or _ST_ISINF or _ST_INVALID
            mov edx,0x7FFF0000
            .if ecx & _ST_ISNAN or _ST_INVALID
                or edx,0x00004000
            .endif
            .endc
          .case ecx & _ST_OVERFLOW
          .case eax >= Q_EXPMAX + Q_EXPBIAS
            mov edx,0x7FFF0000
            .if ecx & _ST_NEGNUM
                or edx,0x80000000
            .endif
            .endc
          .case ecx & _ST_UNDERFLOW
            xor edx,edx
            .endc
        .endsw

        .if edx != 1

            shl rdx,32
            xor eax,eax
            mov [r10+0x00],rax
            mov [r10+0x08],rdx
            mov errno,ERANGE

        .elseif flt.exponent && !( flt.flags & _ST_ISHEX )

            _fltscale(&flt)
        .endif

        .if flt.flags & _ST_NEGNUM

            mov rdx,flt.mantissa
            or byte ptr [rdx+15],0x80
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
    lea rax,flt
    ret

_strtoflt endp

    END
