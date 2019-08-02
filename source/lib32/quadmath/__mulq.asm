; __MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

__mulq proc uses esi edi ebx A:ptr, B:ptr

    local multiplier    :__m128i
    local multiplicand  :__m128i
    local result[2]     :__m128i

    mov     edx,B           ; A(si:ecx:ebx:edx:eax), B(highword(esi):stack)
    mov     ax,[edx]
    shl     eax,16
    mov     edi,[edx+2]
    mov     ebx,[edx+6]
    mov     ecx,[edx+10]
    mov     si,[edx+14]
    and     si,Q_EXPMASK
    neg     si
    mov     si,[edx+14]
    rcr     ecx,1
    rcr     ebx,1
    rcr     edi,1
    rcr     eax,1
    mov     multiplicand.m128i_u32[0],eax
    mov     multiplicand.m128i_u32[4],edi
    mov     multiplicand.m128i_u32[8],ebx
    mov     multiplicand.m128i_u32[12],ecx

    shl     esi,16
    mov     ecx,A
    mov     ax,[ecx]
    shl     eax,16
    mov     edx,[ecx+2]
    mov     ebx,[ecx+6]
    mov     edi,[ecx+10]
    mov     si,[ecx+14]
    and     si,Q_EXPMASK
    neg     si
    mov     si,[ecx+14]
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1

    .repeat

        add     si,1            ; add 1 to exponent
        jc      er_NaN_A        ; quit if NaN
        jo      er_NaN_A        ; ...
        add     esi,0xFFFF      ; readjust low exponent and inc high word
        jc      er_NaN_B        ; quit if NaN
        jo      er_NaN_B        ; ...
        sub     esi,0x10000     ; readjust high exponent

        mov     ecx,eax         ; A is 0 ?
        or      ecx,edx
        or      ecx,ebx
        or      ecx,edi
        jz      A_is_zero       ; exit if A is 0

      if_B_is_zero:

        mov     ecx,multiplicand.m128i_u32[0x00]
        or      ecx,multiplicand.m128i_u32[0x04]
        or      ecx,multiplicand.m128i_u32[0x08]
        or      ecx,multiplicand.m128i_u32[0x0C]
        jz      B_is_zero       ; exit if B is 0

      exponent_and_sign:

        mov     ecx,esi         ; exponent and sign of A into EDI
        rol     ecx,16          ; shift to top
        sar     ecx,16          ; duplicate sign
        sar     esi,16          ; ...
        and     ecx,0x80007FFF  ; isolate signs and exponent
        and     esi,0x80007FFF  ; ...
        add     esi,ecx         ; determine exponent of result and sign
        sub     si,0x3FFE       ; remove extra bias
        jnc     exponent_size
        cmp     si,0x7FFF       ; exponent negative ?
        ja      overflow        ; overflow ?

      exponent_size:            ; exponent too small ?
        cmp     si,-64
        jl      exponent_too_small

        mov     multiplier.m128i_u32[0x00],eax
        mov     multiplier.m128i_u32[0x04],edx
        mov     multiplier.m128i_u32[0x08],ebx
        mov     multiplier.m128i_u32[0x0C],edi

        mul     multiplicand.m128i_u32[0x00]
        mov     result.m128i_u32[0x00],eax
        mov     result.m128i_u32[0x04],edx
        mov     eax,multiplier.m128i_u32[0x04]
        mul     multiplicand.m128i_u32[0x04]
        mov     result.m128i_u32[0x08],eax
        mov     result.m128i_u32[0x0C],edx
        mov     eax,ebx
        mul     multiplicand.m128i_u32[0x08]
        mov     result.m128i_u32[0x10],eax
        mov     result.m128i_u32[0x14],edx
        mov     eax,edi
        mul     multiplicand.m128i_u32[0x0C]
        mov     result.m128i_u32[0x18],eax
        mov     result.m128i_u32[0x1C],edx

        .for ( ebx = 0 : ebx < 12 : ebx++ )

            lea ecx,[ebx*2]

                  ;  b a 9 8 7 6 5 4 3 2 1 0 - index

                  ;  3 2 3 1 3 0 2 1 2 0 0 1 - A
                  ;  2 3 1 3 0 3 1 2 0 2 1 0 - B

            mov eax,111011011100100110000001B
            mov edx,101101110011011000100100B
            shr eax,cl
            shr edx,cl
            and eax,3
            and edx,3

            mov eax,multiplier.m128i_u32[eax*4]
            mul multiplicand.m128i_u32[edx*4]

            .if ( eax || edx )

                ;  b a 9 8 7 6 5 4 3 2 1 0 - index
                ;  5 5 4 4 3 3 3 3 2 2 1 1

                mov edi,010100001111111110100101B
                shr edi,cl
                and edi,3
                .if ebx > 7
                    add edi,4
                .endif
                add result.m128i_u32[edi*4],eax
                adc result.m128i_u32[edi*4+4],edx
                sbb edx,edx

                .continue .ifz

                .for ( eax = 1, edi += 2: edx, edi < 8: edi++ )

                    add result.m128i_u32[edi*4],eax
                    sbb edx,edx
                .endf
            .endif
        .endf

        mov ecx,result.m128i_u32[0x0C]
        mov eax,result.m128i_u32[0x10]  ; high256
        mov edx,result.m128i_u32[0x14]
        mov ebx,result.m128i_u32[0x18]
        mov edi,result.m128i_u32[0x1C]

        .ifs ( edi > 0 )       ; if not normalized

            add ecx,ecx
            adc eax,eax
            adc edx,edx
            adc ebx,ebx
            adc edi,edi
            dec si
        .endif

        shl ecx,1
        .ifc
            .ifz
                .if result.m128i_u32[0x08]
                    stc
                .else
                    bt eax,0
                .endif
            .endif
            adc eax,0
            adc edx,0
            adc ebx,0
            adc edi,0
            .ifc
                rcr edi,1
                rcr ebx,1
                rcr edx,1
                rcr eax,1
                inc si
                cmp si,0x7FFF
                je  overflow
            .endif
        .endif

        or si,si
        .ifng
            .ifz
                and si,0xFF00
                inc si
            .else
                neg si
            .endif
            mov  ecx,esi
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr  edi,cl
            xor  si,si
        .endif
        add esi,esi
        rcr si,1
        .break

    A_is_zero:
        add     si,si       ; place sign in carry
        .break .ifz         ; return 0
        rcr     si,1        ; restore sign of A
        jmp     if_B_is_zero

    B_is_zero:
        test    esi,0x7FFF0000
        jz      return_0
        jmp     exponent_and_sign

    exponent_too_small:
        mov     si,0x7FFF
        jmp     return_m0

    er_NaN_A:   ; A is a NaN or infinity

        .if ( eax == 0 && \
              edx == 0 && \
              ebx == 0 && \
              edi == 0x80000000 && \
              eax == multiplicand.m128i_u32[0x00] && \
              eax == multiplicand.m128i_u32[0x04] && \
              eax == multiplicand.m128i_u32[0x08] && \
              eax == multiplicand.m128i_u32[0x0C] )

            mov esi,-1 ; -NaN
            .break
        .endif

        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .if ( eax == 0 && \
                      edx == 0 && \
                      ebx == 0 && \
                      edi == 0x80000000 && \
                      esi & edi )
                    xor esi,0x8000
                .endif
                .break
            .endif
        .endif

        sub esi,0x10000

        .if ( edi == multiplicand.m128i_u32[0x0C] && \
              ebx == multiplicand.m128i_u32[0x08] && \
              edx == multiplicand.m128i_u32[0x04] )
            cmp eax,multiplicand.m128i_u32[0x00]
        .endif

        .ifna
            .ifz
                .break .if eax || edx || ebx
                .break .if edi != 0x80000000
                or si,si
                .ifs
                    xor esi,0x80000000
                .endif
            .endif
            jmp return_B
        .endif
        .break

      er_NaN_B: ; B is a NaN or infinity

        sub esi,0x10000

        .if ( multiplicand.m128i_u32[0x00] == 0 && \
              multiplicand.m128i_u32[0x04] == 0 && \
              multiplicand.m128i_u32[0x08] == 0 && \
              multiplicand.m128i_u32[0x0C] == 0x80000000 )

            .if ( eax == 0 && edx == 0 && ebx == 0 && edi == 0 )
                mov esi,-1          ; -NaN
            .elseif ( esi & 0x8000 )
                xor esi,0x80000000  ; flip sign bit
            .endif
        .endif

      return_B:
        mov eax,multiplicand.m128i_u32[0]
        mov edx,multiplicand.m128i_u32[4]
        mov ebx,multiplicand.m128i_u32[8]
        mov edi,multiplicand.m128i_u32[12]
        shr esi,16
        .break
      return_0:
        xor esi,esi
        jmp return_m0
      overflow:
        mov esi,0x7FFF
      return_si0:
        add esi,esi
        rcr si,1
      return_m0:
        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi
    .until 1

    mov ecx,A
    add eax,eax         ; shift bits back
    adc edx,edx
    adc ebx,ebx
    adc edi,edi         ; shift high bit out..
    shr eax,16          ; 16 low bits
    mov [ecx],ax
    mov [ecx+2],edx
    mov [ecx+6],ebx
    mov [ecx+10],edi
    mov [ecx+14],si     ; exponent and sign
    mov eax,ecx         ; return result
    ret

__mulq endp

    end
