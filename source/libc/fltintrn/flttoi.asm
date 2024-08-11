; FLTTOI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include limits.inc
include errno.inc

    .code

_flttoi proc __ccall uses rbx p:ptr STRFLT

    ldr rbx,p

    mov cx,[rbx+16]
    mov eax,ecx
    and eax,Q_EXPMASK

    .ifs ( eax < Q_EXPBIAS )

        xor eax,eax

    .elseif ( eax > 32 + Q_EXPBIAS )

        mov qerrno,ERANGE
        mov eax,INT_MAX
        .if ( cx & 0x8000 )
            mov eax,INT_MIN
        .endif

    .else

        mov ecx,eax
        sub ecx,Q_EXPBIAS
        xor eax,eax
        mov edx,[rbx+12]
        shl edx,1
        adc eax,eax
        shld eax,edx,cl
        .if ( byte ptr [rbx+17] & 0x80 )
            neg eax
        .endif
    .endif
    ret

_flttoi endp

    end
