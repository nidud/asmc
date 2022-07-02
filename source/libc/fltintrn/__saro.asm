; __SARO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

u128 struct
l64_l dd ?
l64_h dd ?
h64_l dd ?
h64_h dd ?
u128 ends

    .code

    assume rsi:ptr u128

__saro proc __ccall uses rsi rdi rbx val:ptr uint128_t, count:int_t, bits:int_t

ifdef _WIN64
    mov rsi,rcx
    mov ecx,edx
else
    mov esi,val
    mov ecx,count
endif

    mov eax,[rsi].l64_l
    mov edx,[rsi].l64_h
    mov ebx,[rsi].h64_l
    mov edi,[rsi].h64_h

    .if ( ecx >= 64 && bits <= 64 )

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ( ecx >= 128 && bits == 128 )

        sar edi,31
        mov ebx,edi
        mov edx,edi
        mov eax,edi

    .elseif ( bits == 128 )

        .while ( ecx > 32 )

            mov eax,edx
            mov edx,ebx
            mov ebx,edi
            sar edi,31
            sub ecx,32
        .endw

        shrd eax,edx,cl
        shrd edx,ebx,cl
        shrd ebx,edi,cl
        sar edi,cl

    .else

        .if ( eax == -1 && bits == 32 )

            xor edx,edx
        .endif

        .if ( bits == 32 )

            sar eax,cl

        .elseif ( ecx < 32 )

            shrd eax,edx,cl
            sar edx,cl

        .else

            mov eax,edx
            sar edx,31
            and cl,32-1
            sar eax,cl
        .endif
    .endif

    mov [rsi].l64_l,eax
    mov [rsi].l64_h,edx
    mov [rsi].h64_l,ebx
    mov [rsi].h64_h,edi
    mov rax,rsi
    ret

__saro endp

    end
