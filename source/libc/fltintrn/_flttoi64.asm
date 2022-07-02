; _FLTTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include limits.inc
include errno.inc

    .code

_flttoi64 proc __ccall p:ptr STRFLT

ifndef _WIN64
    mov ecx,p
endif
    mov dx,[rcx+16]
    mov eax,edx
    and eax,Q_EXPMASK

    .ifs ( eax < Q_EXPBIAS )

        xor eax,eax
        .if ( dx & 0x8000 )
            dec rax
        .endif
ifndef _WIN64
        cdq
endif

    .elseif ( eax > 62 + Q_EXPBIAS )

        mov qerrno,ERANGE
ifdef _WIN64
        mov rax,_I64_MAX
        .if ( edx & 0x8000 )
            mov rax,_I64_MIN
        .endif
else
        xor eax,eax
        .if ( edx & 0x8000 )
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif
endif

    .else

ifdef _WIN64

        mov r10,[rcx+8]
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS
        shl r10,1
        adc eax,eax
        shld rax,r10,cl
        .if ( edx & 0x8000 )
            neg rax
        .endif

else

        push    edx
        push    ebx
        push    edi
        mov     ebx,[ecx+8]
        mov     edi,[ecx+12]
        mov     ecx,eax
        xor     eax,eax
        xor     edx,edx
        shld    edi,ebx,1
        adc     eax,eax
        shl     ebx,1
        sub     ecx,Q_EXPBIAS

        .if ( ecx < 32 )

            shld eax,edi,cl

        .else

            .while ecx

                add ebx,ebx
                adc edi,edi
                adc eax,eax
                adc edx,edx
                dec ecx
            .endw
        .endif
        pop edi
        pop ebx
        pop ecx

        .if ( ecx & 0x8000 )

            neg edx
            neg eax
            sbb edx,0
        .endif
endif
    .endif
    ret

_flttoi64 endp

    end
