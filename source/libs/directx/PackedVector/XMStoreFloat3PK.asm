; XMSTOREFLOAT3PK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreFloat3PK proc XM_CALLCONV uses rsi rdi rbx pDestination:ptr XMFLOAT3PK, V:FXMVECTOR

   .new i:int_t

    ldr xmm0,V

    ;; X & Y Channels (5-bit exponent, 6-bit mantissa)
    ;; Z Channel (5-bit exponent, 5-bit mantissa)

    .for ( i = 0 : i < 3: i++ )

        movd eax,xmm0
        XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
        shld rsi,rdi,32
        shl rdi,32

        mov ebx,eax
        and ebx,0x80000000
        mov edx,eax
        and edx,0x7FFFFFFF

        mov eax,edx
        and eax,0x7F800000

        .if (eax == 0x7F800000)

            ;; INF or NAN

            .if ( i == 2 )

                mov eax,0x3E0

                .if ( edx & 0x7FFFFF )

                    mov eax,edx
                    shr eax,18
                    mov ebx,edx
                    shr ebx,13
                    or  eax,ebx
                    mov ebx,edx
                    shr ebx,3
                    or  eax,ebx
                    or  eax,edx
                    and eax,0x1F
                    or  eax,0x3E0

                .elseif ( ebx )

                    xor eax,eax
                .endif

            .else

                mov eax,0x7C0

                .if ( edx & 0x7FFFFF )

                    mov eax,edx
                    shr eax,17
                    mov ebx,edx
                    shr ebx,11
                    shr edx,6
                    or  eax,ebx
                    or  eax,edx
                    and eax,0x3F
                    or  eax,0x7C0

                .elseif ( ebx )

                    ;; -INF is clamped to 0 since 3PK is positive only

                    xor eax,eax
                .endif
            .endif

            or  rdi,rax

        .elseif ( ebx )

            ;; 3PK is positive only, so clamp to zero

        .else

            .if ( i == 2 )

                .if ( edx > 0x477C0000 )

                    ;; The number is too large to be represented as a float10, set to max

                    mov eax,0x3DF
                    or  rdi,rax

                .else

                    .if ( edx < 0x38800000 )

                        ;; The number is too small to be represented as a normalized float10
                        ;; Convert it to a denormalized value.

                        mov eax,edx
                        shr eax,23
                        mov ecx,113
                        sub ecx,eax
                        and edx,0x7FFFFF
                        or  edx,0x800000
                        shr edx,cl

                    .else

                        ;; Rebias the exponent to represent the value as a normalized float10

                        add edx,0xC8000000
                    .endif

                    lea rax,[rdx+0x1FFFF]
                    shr edx,18
                    and edx,1
                    add eax,edx
                    shr eax,18
                    and eax,0x3FF
                    or  rdi,rax
                .endif

            .else

                .if ( edx > 0x477E0000 )

                    ;; The number is too large to be represented as a float11, set to max

                    mov eax,0x7BF
                    or  rdi,rax

                .else

                    .if ( edx < 0x38800000 )

                        ;; The number is too small to be represented as a normalized float11
                        ;; Convert it to a denormalized value.

                        mov eax,edx
                        shr eax,23
                        mov ecx,113
                        sub ecx,eax
                        and edx,0x7FFFFF
                        or  edx,0x800000
                        shr edx,cl

                    .else

                        ;; Rebias the exponent to represent the value as a normalized float11

                        add edx,0xC8000000
                    .endif

                    mov eax,edx
                    shr eax,17
                    and eax,1
                    add eax,0xFFFF
                    add eax,edx
                    shr eax,17
                    and eax,0x7FF
                    or  rdi,rax
                .endif
            .endif
        .endif
    .endf

    ;; Pack Result into memory

    mov ebx,edi
    shr rdi,32
    and esi,0x7ff
    and edi,0x7ff
    and ebx,0x3ff
    shl edi,11
    shl ebx,22
    or  esi,edi
    or  esi,ebx
    mov rax,pDestination
    mov [rax].XMFLOAT3PK.v,esi
    ret

XMStoreFloat3PK endp

    end
