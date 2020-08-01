; __ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

_lk_addq proc private uses esi edi ebx A:ptr, B:ptr, negate:uint_t

  local b:__m128i
  local x, reg

    mov     edx,B       ; A(si:ecx:ebx:edx:eax), B(highword(esi):stack)
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
    mov     b.m128i_u32[0],eax
    mov     b.m128i_u32[4],edi
    mov     b.m128i_u32[8],ebx
    mov     b.m128i_u32[12],ecx
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
    jmp     entry

    .switch jmp ecx

      .case 0
        mov eax,b.m128i_u32[0]
        mov edx,b.m128i_u32[4]
        mov ebx,b.m128i_u32[8]
        mov edi,b.m128i_u32[12]
        shr esi,16
        .endc

      .case 1
        mov esi,0x7FFF
        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi
        .endc

      .case 2 ; A is a NaN or infinity
        dec si
        add esi,0x10000
        .ifnc
            .endc .ifno
        .endif
        sub esi,0x10000
        mov ecx,eax
        or  ecx,edx
        or  ecx,ebx
        .ifz
            mov ecx,b.m128i_u32[0]
            or  ecx,b.m128i_u32[4]
            or  ecx,b.m128i_u32[8]
            .ifz
                .if edi == 0x80000000 && edi == b.m128i_u32[12]
                    sar edi,1
                    or  esi,-1  ; -NaN
                    .endc
                .endif
            .endif
        .endif
        .if edi == b.m128i_u32[12]
            .if ebx == b.m128i_u32[8]
                .if edx == b.m128i_u32[4]
                    cmp eax,b.m128i_u32[0]
                .endif
            .endif
        .endif
        .gotosw(0) .ifna
        .endc

      .case 3 ; B is a NaN or infinity

        sub esi,0x10000

        .if ( b.m128i_u32[0x00] == 0 && \
              b.m128i_u32[0x04] == 0 && \
              b.m128i_u32[0x08] == 0 && \
              b.m128i_u32[0x0C] == 0x80000000 )

            mov eax,esi
            shl eax,16
            xor esi,eax
            and esi,0x80000000
            mov b.m128i_u32[12],0
        .endif
        .gotosw(0)

      .case 4                   ; A is 0
        shl si,1                ; place sign in carry
        .ifz
            shr esi,16          ; return B
            mov eax,b.m128i_u32[0]
            mov edx,b.m128i_u32[4]
            mov ebx,b.m128i_u32[8]
            mov edi,b.m128i_u32[12]
            shl esi,1
            mov ecx,eax         ; check for 0
            or  ecx,edx
            or  ecx,ebx
            or  ecx,edi
            .ifnz               ; if not zero
                shr esi,1       ; -> restore sign bit
            .endif
            .endc
        .endif
        rcr si,1                ; put back the sign
        .gotosw(6)

      .case <entry> 5

        add si,1                ; add 1 to exponent
        .gotosw(2) .ifc         ; quit if NaN
        .gotosw(2) .ifo
        add esi,0xFFFF          ; readjust low exponent and inc high word
        .gotosw(3) .ifc         ; quit if NaN
        .gotosw(3) .ifo
        sub esi,0x10000         ; readjust high exponent
        xor esi,negate          ; flip sign if subtract

        mov ecx,eax             ; A is 0 ?
        or  ecx,edx
        or  ecx,ebx
        or  ecx,edi
        .gotosw(4) .ifz

      .case 6
                                ; B is 0 ?
        mov ecx,b.m128i_u32[0x00]
        or  ecx,b.m128i_u32[0x04]
        or  ecx,b.m128i_u32[0x08]
        or  ecx,b.m128i_u32[0x0C]
        .ifz                    ; quit if B is 0
            .endc .if !( esi & 0x7FFF0000 )
        .endif

        mov ecx,esi             ; exponent and sign of A into EDI
        rol esi,16              ; shift to top
        sar esi,16              ; duplicate sign
        sar ecx,16              ; ...
        and esi,0x80007FFF      ; isolate signs and exponent
        and ecx,0x80007FFF      ; ...
        mov x,ecx               ; assume A < B
        rol esi,16              ; rotate signs to bottom
        rol ecx,16              ; ...
        add cx,si               ; calc sign of result
        rol esi,16              ; rotate signs to top
        rol ecx,16              ; ...
        sub cx,si               ; calculate difference in exponents

        .ifnz                   ; if different

            .ifb                ; if B < A
                mov  x,esi      ; get larger exponent for result
                neg  cx         ; negate the shift count
                push ecx        ; flip operands
                mov  ecx,b.m128i_u32[0]
                mov  b.m128i_u32[0],eax
                mov  eax,ecx
                mov  ecx,b.m128i_u32[4]
                mov  b.m128i_u32[4],edx
                mov  edx,ecx
                mov  ecx,b.m128i_u32[8]
                mov  b.m128i_u32[8],ebx
                mov  ebx,ecx
                mov  ecx,b.m128i_u32[12]
                mov  b.m128i_u32[12],edi
                mov  edi,ecx
                pop  ecx
            .endif

            .if cx > 128        ; if shift count too big
                mov esi,x
                shl esi,1       ; get sign
                rcr si,1        ; merge with exponent
                mov eax,b.m128i_u32[0]
                mov edx,b.m128i_u32[4]
                mov ebx,b.m128i_u32[8]
                mov edi,b.m128i_u32[12]
                .endc
            .endif
        .endif
        mov esi,x
        mov ch,0                ; zero extend B
        or  ecx,ecx             ; get bit 0 of sign word - value is 0 if
                                ; both operands have same sign, 1 if not
        .ifs                    ; if signs are different
            mov ch,-1           ; - set high part to ones
            neg b.m128i_u32[12]
            neg b.m128i_u32[8]
            sbb b.m128i_u32[12],0
            neg b.m128i_u32[4]
            sbb b.m128i_u32[8],0
            neg b.m128i_u32[0]
            sbb b.m128i_u32[4],0
            xor esi,0x80000000  ; - flip sign
        .endif
        .repeat
            mov reg,0               ; get a zero for sticky bits
            .if cl                  ; if shifting required
                .if cl >= 64        ; if shift count >= 64
                    .if eax || edx  ; check low order qword for 1 bits
                        inc reg     ; edi=1 if EDX:EAX non zero
                    .endif
                    .if cl == 128   ; if shift count is 128
                        or  reg,edi ; get rest of sticky bits from high part
                        xor ebx,ebx ; zero high part
                        xor edi,edi
                    .endif
                    mov eax,ebx     ; shift right 64
                    mov edx,edi
                    xor ebx,ebx
                    xor edi,edi
                .elseif cl >= 32    ; if shift count >= 32
                    .if eax         ; check low order qword for 1 bits
                        inc reg     ; edi=1 if EDX:EAX non zero
                    .endif
                    mov eax,edx     ; shift right 32
                    mov edx,ebx
                    mov ebx,edi
                    xor edi,edi
                .else
                    push eax            ; get the extra sticky bits
                    push ebx
                    xor  ebx,ebx
                    shr  eax,15
                    shrd ebx,eax,cl
                    or   reg,ebx        ; save them
                    pop  ebx
                    pop  eax
                .endif
                shrd eax,edx,cl     ; align the fractions
                shrd edx,ebx,cl
                shrd ebx,edi,cl
                shr  edi,cl
            .endif
            add eax,b.m128i_u32[0]
            adc edx,b.m128i_u32[4]
            adc ebx,b.m128i_u32[8]
            adc edi,b.m128i_u32[12]
            adc ch,0
            .ifs
                .if cl == 128
                    .if reg & 0x7FFFFFFF
                        stc         ; make single sticky bit
                    .else
                        clc
                    .endif
                    adc eax,0       ; round up fraction if required
                    adc edx,0
                    adc ebx,0
                    adc edi,0
                .endif
                neg edi
                neg ebx
                sbb edi,0
                neg edx
                sbb ebx,0
                neg eax
                sbb edx,0
                mov ch,0
                xor esi,0x80000000
            .endif
            push ecx
            movzx ecx,ch
            or  ecx,eax
            or  ecx,edx
            or  ecx,ebx
            or  ecx,edi
            pop ecx
            .ifz
                xor esi,esi
            .endif
            .endc .if !si
            ;
            ; if top bits are 0
            ;
            test ch,ch
            mov ecx,reg
            .ifz
                rol ecx,1       ; set carry from last sticky bit
                rol ecx,1
                .repeat
                    dec si      ; decrement exponent
                    .endc .ifz
                    adc eax,eax
                    adc edx,edx
                    adc ebx,ebx
                    adc edi,edi
                .untilb         ; until carry
            .endif
            inc si
            .gotosw(1) .if si == Q_EXPMASK
            stc                 ; set carry
            rcr edi,1           ; shift fraction right 1
            rcr ebx,1
            rcr edx,1
            rcr eax,1
            add ecx,ecx         ; get top sticky bit
            .ifc                ; set carry with bit 14 of AX
                adc eax,0x4000  ; round up fraction if required
                adc edx,0
                adc ebx,0
                adc edi,0
                .ifc            ; if we got a carry
                    rcr edi,1   ; shift fraction right 1
                    rcr ebx,1
                    rcr edx,1
                    rcr eax,1
                    inc si      ; increment exponent
                    .gotosw(1) .if si == Q_EXPMASK
                .endif
            .endif

        .until 1

        add esi,esi
        rcr si,1

    .endsw

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

_lk_addq endp

__addq proc A:ptr, B:ptr

    _lk_addq(A, B, 0)
    ret

__addq endp

__subq proc A:ptr, B:ptr

    _lk_addq(A, B, 0x80000000)
    ret

__subq endp

    end
