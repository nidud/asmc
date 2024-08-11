; MULO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

ifdef _WIN64

    .code

__mulo proc __ccall multiplier:ptr uint128_t, multiplicand:ptr uint128_t, highproduct:ptr uint128_t

    mov rax,[rcx]
    mov r10,[rcx+8]
    mov r9, [rdx+8]

    .if ( !r10 && !r9 )

        .if ( r8 )

            mov [r8],r9
            mov [r8+8],r9
        .endif

        mul qword ptr [rdx]

    .else

        push rcx
        mov  r11,[rdx]
        mul  r11         ; a * b
        push rax
        xchg rdx,r11
        mov  rax,r10
        mul  rdx         ; a[8] * b
        add  r11,rax
        xchg rcx,rdx
        mov  rax,[rdx]
        mul  r9          ; a * b[8]
        add  r11,rax
        adc  rcx,rdx
        mov  edx,0
        adc  edx,0

        .if ( r8 )

            xchg rdx,r9
            mov  rax,r10
            mul  rdx     ; a[8] * b[8]
            add  rax,rcx
            adc  rdx,r9
            mov  [r8],rax
            mov  [r8+8],rdx
        .endif

        pop rax
        mov rdx,r11
        pop rcx
    .endif

    mov [rcx],rax
    mov [rcx+8],rdx
    mov rax,rcx
    ret

__mulo endp

else

u128 struct
l64_l dd ?
l64_h dd ?
h64_l dd ?
h64_h dd ?
u128 ends

    .code

    ; ecx:ebx:edx:eax = edx:eax * ecx:ebx

_mulqw proc watcall private a64_l:uint_t, a64_h:uint_t, b64_l:uint_t, b64_h:uint_t

    .if !edx && !ecx

        mul ebx
        xor ebx,ebx

        .return
    .endif

    push    ebp
    push    esi
    push    edi
    push    eax
    push    edx
    push    edx
    mul     ebx
    mov     esi,edx
    mov     edi,eax
    pop     eax
    mul     ecx
    mov     ebp,edx
    xchg    ebx,eax
    pop     edx
    mul     edx
    add     esi,eax
    adc     ebx,edx
    adc     ebp,0
    pop     eax
    mul     ecx
    add     esi,eax
    adc     ebx,edx
    adc     ebp,0
    mov     ecx,ebp
    mov     edx,esi
    mov     eax,edi
    pop     edi
    pop     esi
    pop     ebp
    ret

_mulqw endp

    assume esi:ptr u128
    assume edi:ptr u128

__mulo proc __ccall uses esi edi ebx multiplier:ptr uint128_t, multiplicand:ptr uint128_t, highproduct:ptr uint128_t

  local n[8]:dword ; 256-bit result

    mov edi,multiplier
    mov esi,multiplicand

    _mulqw( [edi].l64_l, [edi].l64_h, [esi].l64_l, [esi].l64_h )

    mov n[0x00],eax
    mov n[0x04],edx
    mov n[0x08],ebx
    mov n[0x0C],ecx

    _mulqw( [edi].h64_l, [edi].h64_h, [esi].h64_l, [esi].h64_h )

    mov n[0x10],eax
    mov n[0x14],edx
    mov n[0x18],ebx
    mov n[0x1C],ecx

    _mulqw( [edi].l64_l, [edi].l64_h, [esi].h64_l, [esi].h64_h )

    add n[0x08],eax
    adc n[0x0C],edx
    adc n[0x10],ebx
    adc n[0x14],ecx
    adc n[0x18],0
    adc n[0x1C],0

    _mulqw( [edi].h64_l, [edi].h64_h, [esi].l64_l, [esi].l64_h )

    add n[0x08],eax
    adc n[0x0C],edx
    adc n[0x10],ebx
    adc n[0x14],ecx
    adc n[0x18],0
    adc n[0x1C],0

    mov [edi].l64_l,n[0x00]
    mov [edi].l64_h,n[0x04]
    mov [edi].h64_l,n[0x08]
    mov [edi].h64_h,n[0x0C]
    mov esi,highproduct
    .if esi
        mov [esi].l64_l,n[0x10]
        mov [esi].l64_h,n[0x14]
        mov [esi].h64_l,n[0x18]
        mov [esi].h64_h,n[0x1C]
    .endif
    mov eax,edi
    ret

__mulo endp

endif

    end
