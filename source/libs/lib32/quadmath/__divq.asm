; __DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

__divq proc uses esi edi ebx A:ptr, B:ptr

  local dividend[2]:__m128i
  local divisor [2]:__m128i
  local reminder[2]:__m128i
  local bits:int_t

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
    mov     divisor.m128i_u32[0],eax
    mov     divisor.m128i_u32[4],edi
    mov     divisor.m128i_u32[8],ebx
    mov     divisor.m128i_u32[12],ecx

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

    .repeat ; create frame -- no loop

        add     si,1            ; add 1 to exponent
        jc      er_NaN_A        ; quit if NaN
        jo      er_NaN_A        ; ...
        add     esi,0xFFFF      ; readjust low exponent and inc high word
        jc      er_NaN_B        ; quit if NaN
        jo      er_NaN_B        ; ...
        sub     esi,0x10000     ; readjust high exponent

        mov     ecx,divisor.m128i_u32[0]
        or      ecx,divisor.m128i_u32[4]
        or      ecx,divisor.m128i_u32[8]
        or      ecx,divisor.m128i_u32[12]

        .ifz

            .if !( esi & 0x7FFF0000 )

                mov ecx,eax
                or  ecx,edx
                or  ecx,ebx
                or  ecx,edi

                .ifz    ; exit if A is 0

                    mov edi,esi
                    add di,di

                    .ifz

                        ; Invalid operation - return NaN

                        mov edi,0x40000000
                        mov esi,0x7FFF
                        .break
                    .endif
                .endif

                ; zero divide - return infinity

                or esi,0x7FFF
                jmp return_m0
            .endif
        .endif

        mov ecx,eax
        or  ecx,edx
        or  ecx,ebx
        or  ecx,edi
        .ifz
            add si,si
            .break .ifz
            rcr si,1        ; put back the sign
        .endif
        mov ecx,esi         ; exponent and sign of A into EDI
        rol ecx,16          ; shift to top
        sar ecx,16          ; duplicate sign
        sar esi,16          ; ...
        and ecx,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        rol ecx,16          ; rotate signs to bottom
        rol esi,16          ; ...
        add cx,si           ; calc sign of result
        rol ecx,16          ; rotate signs to top
        rol esi,16          ; ...
        .if !cx             ; if A is a denormal
            .repeat         ; then normalize it
                dec cx      ; - decrement exponent
                add eax,eax ; - shift fraction left
                adc edx,edx
                adc ebx,ebx
                adc edi,edi
            .untilb         ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            push eax
            .repeat
                dec si
                mov eax,divisor.m128i_u32[0]
                add divisor.m128i_u32[0],eax
                mov eax,divisor.m128i_u32[4]
                adc divisor.m128i_u32[4],eax
                mov eax,divisor.m128i_u32[8]
                adc divisor.m128i_u32[8],eax
                mov eax,divisor.m128i_u32[12]
                adc divisor.m128i_u32[12],eax
            .untilb
            pop eax
        .endif
        sub cx,si           ; calculate exponent of result
        add cx,0x3FFF       ; add in removed bias
        .ifns               ; overflow ?
            .if cx >= 0x7FFF    ; quit if exponent is negative
                mov si,0x7FFF   ; - set infinity
                jmp return_si0  ; return infinity
            .endif
        .endif
        cmp cx,-65          ; if exponent is too small
        jl return_0         ; return underflow

        push ecx

        mov reminder.m128i_u32[0x10],eax    ; dividend --> reminder
        mov reminder.m128i_u32[0x14],edx
        mov reminder.m128i_u32[0x18],ebx
        mov reminder.m128i_u32[0x1C],edi

        xor eax,eax
        mov bits,eax

        mov dividend.m128i_u32[0x00],eax    ; quotient (dividend) --> 0
        mov dividend.m128i_u32[0x04],eax
        mov dividend.m128i_u32[0x08],eax
        mov dividend.m128i_u32[0x0C],eax
        mov dividend.m128i_u32[0x10],eax
        mov reminder.m128i_u32[0x00],eax    ; 0, dividend
        mov reminder.m128i_u32[0x04],eax
        mov reminder.m128i_u32[0x08],eax
        mov reminder.m128i_u32[0x0C],eax
        mov divisor.m128i_u32[0x10],eax     ; divisor, 0
        mov divisor.m128i_u32[0x14],eax
        mov divisor.m128i_u32[0x18],eax
        mov divisor.m128i_u32[0x1C],eax

        .repeat

            mov esi,divisor.m128i_u32[0x00]
            mov edi,divisor.m128i_u32[0x04]
            mov edx,divisor.m128i_u32[0x08]
            mov ebx,divisor.m128i_u32[0x0C]
            mov ecx,divisor.m128i_u32[0x10]

            .while 1

                ; divisor *= 2

                add esi,esi
                adc edi,edi
                adc edx,edx
                adc ebx,ebx
                adc ecx,ecx
                adc divisor.m128i_u32[0x14],divisor.m128i_u32[0x14]
                adc divisor.m128i_u32[0x18],divisor.m128i_u32[0x18]
                adc divisor.m128i_u32[0x1C],divisor.m128i_u32[0x1C]

                .break .ifc

                .if divisor.m128i_u32[0x1C] == reminder.m128i_u32[0x1C] && \
                    divisor.m128i_u32[0x18] == reminder.m128i_u32[0x18] && \
                    divisor.m128i_u32[0x14] == reminder.m128i_u32[0x14] && \
                    ecx == reminder.m128i_u32[0x10] && \
                    ebx == reminder.m128i_u32[0x0C] && \
                    edx == reminder.m128i_u32[0x08] && \
                    edi == reminder.m128i_u32[0x04]
                    cmp esi,reminder.m128i_u32[0x00]
                .endif
                .break .ifa
                inc bits
            .endw

            .while 1

                ; divisor /= 2

                rcr divisor.m128i_u32[0x1C],1
                rcr divisor.m128i_u32[0x18],1
                rcr divisor.m128i_u32[0x14],1
                rcr ecx,1
                rcr ebx,1
                rcr edx,1
                rcr edi,1
                rcr esi,1

                ; reminder -= divisor

                sub reminder.m128i_u32[0x00],esi
                sbb reminder.m128i_u32[0x04],edi
                sbb reminder.m128i_u32[0x08],edx
                sbb reminder.m128i_u32[0x0C],ebx
                sbb reminder.m128i_u32[0x10],ecx
                sbb reminder.m128i_u32[0x14],divisor.m128i_u32[0x14]
                sbb reminder.m128i_u32[0x18],divisor.m128i_u32[0x18]
                sbb reminder.m128i_u32[0x1C],divisor.m128i_u32[0x1C]

                cmc
                .ifnc

                    .repeat

                        ; dividend *= 2

                        add dividend.m128i_u32[0x00],dividend.m128i_u32[0x00]
                        adc dividend.m128i_u32[0x04],dividend.m128i_u32[0x04]
                        adc dividend.m128i_u32[0x08],dividend.m128i_u32[0x08]
                        adc dividend.m128i_u32[0x0C],dividend.m128i_u32[0x0C]
                        adc dividend.m128i_u32[0x10],dividend.m128i_u32[0x10]

                        dec bits
                        .break(1) .ifs

                            ; reminder += divisor

                            ; reminder not needed here..

                        ; divisor /= 2

                        shr divisor.m128i_u32[0x1C],1
                        rcr divisor.m128i_u32[0x18],1
                        rcr divisor.m128i_u32[0x14],1
                        rcr ecx,1
                        rcr ebx,1
                        rcr edx,1
                        rcr edi,1
                        rcr esi,1

                        ; reminder += divisor

                        add reminder.m128i_u32[0x00],esi
                        adc reminder.m128i_u32[0x04],edi
                        adc reminder.m128i_u32[0x08],edx
                        adc reminder.m128i_u32[0x0C],ebx
                        adc reminder.m128i_u32[0x10],ecx
                        adc reminder.m128i_u32[0x14],divisor.m128i_u32[0x14]
                        adc reminder.m128i_u32[0x18],divisor.m128i_u32[0x18]
                        adc reminder.m128i_u32[0x1C],divisor.m128i_u32[0x1C]
                    .untilb
                .endif

                ; dividend *= 2

                adc dividend.m128i_u32[0x00],dividend.m128i_u32[0x00]
                adc dividend.m128i_u32[0x04],dividend.m128i_u32[0x04]
                adc dividend.m128i_u32[0x08],dividend.m128i_u32[0x08]
                adc dividend.m128i_u32[0x0C],dividend.m128i_u32[0x0C]
                adc dividend.m128i_u32[0x10],dividend.m128i_u32[0x10]
                dec bits
                .break .ifs
            .endw
        .until 1
        pop esi

        mov eax,dividend.m128i_u32[0] ; load quotient
        mov edx,dividend.m128i_u32[4]
        mov ebx,dividend.m128i_u32[8]
        mov edi,dividend.m128i_u32[12]
        dec si
        shr dividend.m128i_u8[16],1 ; overflow bit..

        .ifc
            rcr edi,1
            rcr ebx,1
            rcr edx,1
            rcr eax,1
            inc esi
        .endif
        or si,si
        .ifng
            .ifz
                mov cl,1
            .else
                neg si
                mov ecx,esi
            .endif
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr edi,cl
            xor esi,esi
        .endif
        add esi,esi
        rcr si,1
        .break

      er_NaN_A:             ; A is a NaN or infinity
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .ifs
                    .if !eax && !edx && !ebx && edi == 0x80000000
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        .if !eax && !edx && !ebx
            mov ecx,divisor.m128i_u32[0]
            or  ecx,divisor.m128i_u32[4]
            or  ecx,divisor.m128i_u32[8]
            .ifz
                .if edi == 0x80000000 && edi == divisor.m128i_u32[12]
                    sar edi,1
                    or  esi,-1 ; -NaN
                    .break
                .endif
            .endif
        .endif
        .if edi == divisor.m128i_u32[12]
            .if ebx == divisor.m128i_u32[8]
                .if edx == divisor.m128i_u32[4]
                    cmp eax,divisor.m128i_u32[0]
                .endif
            .endif
        .endif
        jna return_B
        .break

      er_NaN_B:             ; B is a NaN or infinity
        sub esi,0x10000
        mov ecx,divisor.m128i_u32[0]
        or  ecx,divisor.m128i_u32[4]
        or  ecx,divisor.m128i_u32[8]
        .ifz
            mov edi,0x80000000
            .if edi == divisor.m128i_u32[12]
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,edi
                sub divisor.m128i_u32[12],edi
            .endif
        .endif
      return_B:
        mov eax,divisor.m128i_u32[0]
        mov edx,divisor.m128i_u32[4]
        mov ebx,divisor.m128i_u32[8]
        mov edi,divisor.m128i_u32[12]
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
    shl eax,1           ; shift bits back
    rcl edx,1
    rcl ebx,1
    rcl edi,1           ; shift high bit out..
    shr eax,16          ; 16 low bits
    mov [ecx],ax
    mov [ecx+2],edx
    mov [ecx+6],ebx
    mov [ecx+10],edi
    mov [ecx+14],si     ; exponent and sign
    mov eax,ecx         ; return result
    ret

__divq endp

    end
