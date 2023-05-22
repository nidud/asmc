; __CVTQ_LD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__cvtq_ld proc __ccall uses rsi rdi rbx ld:ptr ldouble_t, q:ptr qfloat_t

    ldr     rax,ld
    ldr     rdi,q

    xor     ecx,ecx
    mov     ebx,[rdi+6]
    mov     edx,[rdi+10]
    mov     cx, [rdi+14]
    mov     esi,ecx
    and     esi,LD_EXPMASK
    neg     esi
    rcr     edx,1
    rcr     ebx,1

    ; round result

    .ifc
        .if ( ebx == -1 && edx == -1 )
            xor ebx,ebx
            mov edx,0x80000000
            inc cx
        .else
            add ebx,1
            adc edx,0
        .endif
    .endif

    mov [rax],ebx
    mov [rax+4],edx
    .if ( rax == rdi )
        mov [rax+8],ecx
        mov dword ptr [rax+12],0
    .else
        mov [rax+8],cx
    .endif
    ret

__cvtq_ld endp

    end
