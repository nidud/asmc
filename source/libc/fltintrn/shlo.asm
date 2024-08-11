; SHLO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

ifdef _WIN64

    .code

__shlo proc __ccall uses rbx val:ptr uint128_t, count:int_t, bits:int_t

    mov rbx,rcx
    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 ) )

        xor eax,eax
        xor edx,edx

    .elseif ( r8d == 128 )

        .while ( ecx >= 64 )

            mov rdx,rax
            xor eax,eax
            sub ecx,64
        .endw

        shld rdx,rax,cl
        shl rax,cl

    .else

        shl rax,cl
    .endif
    mov [r10],rax
    mov [r10+8],rdx
    mov rax,rbx
    ret

__shlo endp

else

u128 struct
l64_l dd ?
l64_h dd ?
h64_l dd ?
h64_h dd ?
u128 ends

    .code

    assume esi:ptr u128

__shlo proc __ccall uses esi edi ebx val:ptr uint128_t, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].l64_l
    mov edx,[esi].l64_h
    mov ebx,[esi].h64_l
    mov edi,[esi].h64_h

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 ) )

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ( bits == 128 )

        .while ( ecx >= 32 )

            mov edi,ebx
            mov ebx,edx
            mov edx,eax
            xor eax,eax
            sub ecx,32
        .endw

        shld edi,ebx,cl
        shld ebx,edx,cl
        shld edx,eax,cl
        shl eax,cl

    .else

        .if ( cl < 32 )

            shld edx,eax,cl
            shl eax,cl
        .else

            and ecx,31
            mov edx,eax
            xor eax,eax
            shl edx,cl
        .endif
    .endif

    mov [esi].l64_l,eax
    mov [esi].l64_h,edx
    mov [esi].h64_l,ebx
    mov [esi].h64_h,edi
    mov eax,esi
    ret

__shlo endp

endif

    end
