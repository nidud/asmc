; __DIVO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

u128 struct
l64_l dd ?
l64_h dd ?
h64_l dd ?
h64_h dd ?
u128 ends

    .code

    assume esi:ptr u128
    assume edi:ptr u128

__divo proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr

    mov     esi,dividend
    mov     edi,reminder
    mov     ecx,4
    rep     movsd
    xor     eax,eax
    mov     edi,dividend
    mov     ecx,4
    rep     stosd
    mov     esi,divisor
    mov     edi,reminder
    or      eax,[esi].l64_l
    or      eax,[esi].l64_h
    or      eax,[esi].h64_l
    or      eax,[esi].h64_h
    .ifz
        mov ecx,4
        rep stosd
        .return
    .endif

    .if [esi].h64_h == [edi].h64_h
        .if [esi].h64_l == [edi].h64_l
            .if [esi].l64_h == [edi].l64_h
                mov eax,[esi].l64_l
                cmp eax,[edi].l64_l
            .endif
        .endif
    .endif
    .return .ifa ; if divisor > dividend : reminder = dividend, quotient = 0
    .ifz         ; if divisor == dividend :
        mov ecx,4
        xor eax,eax         ; reminder = 0
        rep stosd
        mov edi,dividend    ; quotient = 1
        inc byte ptr [edi]
        .return
    .endif

    mov ecx,[esi].h64_h ; esi = divisor
    mov ebx,[esi].h64_l ; - divisor used as bit-count
    mov edx,[esi].l64_h
    mov esi,[esi].l64_l
    mov divisor,-1

    .while 1

        inc divisor

        add esi,esi
        adc edx,edx
        adc ebx,ebx
        adc ecx,ecx
        .break .ifc

        .break .if ecx > [edi].h64_h
        .continue .ifb
        .break .if ebx > [edi].h64_l
        .continue .ifb
        .break .if edx > [edi].l64_h
        .continue .ifb
        .break .if esi > [edi].l64_l
    .endw

    .while 1

        rcr ecx,1
        rcr ebx,1
        rcr edx,1
        rcr esi,1

        mov edi,reminder
        sub [edi].l64_l,esi
        sbb [edi].l64_h,edx
        sbb [edi].h64_l,ebx
        sbb [edi].h64_h,ecx
        cmc

        .ifnc

            .repeat

                mov edi,dividend
                add [edi].l64_l,[edi].l64_l
                adc [edi].l64_h,[edi].l64_h
                adc [edi].h64_l,[edi].h64_l
                adc [edi].h64_h,[edi].h64_h

                dec divisor
                mov edi,reminder

                .ifs

                    add [edi].l64_l,esi
                    adc [edi].l64_h,edx
                    adc [edi].h64_l,ebx
                    adc [edi].h64_h,ecx

                    .break(1)
                .endif

                shr ecx,1
                rcr ebx,1
                rcr edx,1
                rcr esi,1

                add [edi].l64_l,esi
                adc [edi].l64_h,edx
                adc [edi].h64_l,ebx
                adc [edi].h64_h,ecx
            .untilb
        .endif

        mov edi,dividend
        adc [edi].l64_l,[edi].l64_l
        adc [edi].l64_h,[edi].l64_h
        adc [edi].h64_l,[edi].h64_l
        adc [edi].h64_h,[edi].h64_h

        dec divisor
        .break .ifs
    .endw
    mov eax,dividend
    ret

__divo endp

    end
