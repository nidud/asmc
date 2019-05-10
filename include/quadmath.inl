; QUADMATH.INL--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Quadruple precision - binary128 -- __float128
;
;
; __float128 __vectocall addq(__float128, __float128);
; __float128 __vectocall subq(__float128, __float128);
; __float128 __vectocall mulq(__float128, __float128);
; __float128 __vectocall divq(__float128, __float128);
; __float128 __vectocall normq(__float128, int);
;
; void * __cdecl addq(void *, void *);
; void * __cdecl subq(void *, void *);
; void * __cdecl mulq(void *, void *);
; void * __cdecl divq(void *, void *);
; void * __cdecl normq(void *, int);
;
include quadmath.inc
include intrin.inc
include errno.inc
include limits.inc

    .code

_PROLOG macro name
ifdef _WIN64
    option win64:rsp nosave noauto
    name proc vectorcall uses rsi rdi rbx A:real16, B:real16
else
    name proc __cdecl uses esi edi ebx A:ptr, B:ptr
endif
    endm

_LOAD macro
ifdef _WIN64
    movq    rax,xmm0    ; A(si:rdx:rax), B(highword(esi):rdi:rbx)
    movq    rbx,xmm1
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movhlps xmm0,xmm1
    movq    rdi,xmm0
    shld    rsi,rdi,16
    shld    rdi,rbx,16
    shl     rbx,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdi,1
    rcr     rbx,1
    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdx,1
    rcr     rax,1
else
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
    mov     dword ptr b[0],eax
    mov     dword ptr b[4],edi
    mov     dword ptr b[8],ebx
    mov     dword ptr b[12],ecx
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
endif
    endm

_STORE macro
ifdef _WIN64
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rsi,16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1
else
    mov     ecx,A
    shl     eax,1           ; shift bits back
    rcl     edx,1
    rcl     ebx,1
    rcl     edi,1           ; shift high bit out..
    shr     eax,16          ; 16 low bits
    mov     [ecx],ax
    mov     [ecx+2],edx
    mov     [ecx+6],ebx
    mov     [ecx+10],edi
    mov     [ecx+14],si     ; exponent and sign
    mov     eax,ecx         ; return result
endif
    endm

_ISNAN macro
    add     si,1            ; add 1 to exponent
    jc      er_NaN_A        ; quit if NaN
    jo      er_NaN_A        ; ...
    add     esi,0xFFFF      ; readjust low exponent and inc high word
    jc      er_NaN_B        ; quit if NaN
    jo      er_NaN_B        ; ...
    sub     esi,0x10000     ; readjust high exponent
    endm

_ISZEROA macro
ifdef _WIN64
    mov     rcx,rax
    or      rcx,rdx
else
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
endif
    endm

_ISZEROB macro
ifdef _WIN64
    mov     rcx,rdi
    or      rcx,rbx
else
    mov     ecx,dword ptr b[0]
    or      ecx,dword ptr b[4]
    or      ecx,dword ptr b[8]
    or      ecx,dword ptr b[12]
endif
    endm

_CMPAB macro
ifdef _WIN64
    .if rdx == rdi
        cmp rax,rbx
    .endif
else
    .if edi == dword ptr b[12]
        .if ebx == dword ptr b[8]
            .if edx == dword ptr b[4]
                cmp eax,dword ptr b[0]
            .endif
        .endif
    .endif
endif
    endm

_LOADB macro
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,dword ptr b[0]
    mov     edx,dword ptr b[4]
    mov     ebx,dword ptr b[8]
    mov     edi,dword ptr b[12]
endif
    endm

_FLIPAB macro
ifdef _WIN64
    xchg    rbx,rax
    xchg    rdi,rdx
else
    push    ecx
    mov     ecx,dword ptr b[0]
    mov     dword ptr b[0],eax
    mov     eax,ecx
    mov     ecx,dword ptr b[4]
    mov     dword ptr b[4],edx
    mov     edx,ecx
    mov     ecx,dword ptr b[8]
    mov     dword ptr b[8],ebx
    mov     ebx,ecx
    mov     ecx,dword ptr b[12]
    mov     dword ptr b[12],edi
    mov     edi,ecx
    pop     ecx
endif
    endm

_NEGATEB macro
ifdef _WIN64
    neg     rdi             ; - negate the fraction of op2
    neg     rbx
    sbb     rdi,0
else
    neg     dword ptr b[12]
    neg     dword ptr b[8]
    sbb     dword ptr b[12],0
    neg     dword ptr b[4]
    sbb     dword ptr b[8],0
    neg     dword ptr b[0]
    sbb     dword ptr b[4],0
endif
    endm

_RCR macro
ifdef _WIN64
    rcr     rdx,1   ; shift fraction right 1
    rcr     rax,1
else
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
endif
    endm

_RCL macro
ifdef _WIN64
    rcl     rax,1   ; shift fraction left one bit
    rcl     rdx,1
else
    rcl     eax,1
    rcl     edx,1
    rcl     ebx,1
    rcl     edi,1
endif
    endm

_SHL macro
ifdef _WIN64
    add     rax,rax
    adc     rdx,rdx
else
    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
endif
    endm

_SHLB macro
ifdef _WIN64
    add     rbx,rbx
    adc     rdi,rdi
else
    push    eax
    mov     eax,dword ptr b[0]
    add     dword ptr b[0],eax
    mov     eax,dword ptr b[4]
    adc     dword ptr b[4],eax
    mov     eax,dword ptr b[8]
    adc     dword ptr b[8],eax
    mov     eax,dword ptr b[12]
    adc     dword ptr b[12],eax
    pop     eax
endif
    endm

_OP32 macro cmd:vararg
ifndef _WIN64
    cmd
endif
    endm

_OP64 macro cmd:vararg
ifdef _WIN64
    cmd
endif
    endm


_ADDQ macro name, negate
    _PROLOG name
ifndef _WIN64
    local b:__m128i
    local r9d, reg
endif
    _LOAD
    .repeat ; create frame -- no loop
        _ISNAN
    if negate
        xor esi,0x80000000  ; flip sign if subtract
    endif
        _ISZEROA            ; A is 0 ?
        .ifz
            shl si,1        ; place sign in carry
            .ifz
                shr esi,16
                _LOADB      ; return B
                shl esi,1
                _ISZEROA    ; check for 0
                .ifnz       ; if not zero
                    shr esi,1 ; -> restore sign bit
                .endif
                .break
            .endif
            rcr si,1        ; put back the sign
        .endif
        _ISZEROB            ; B is 0 ?
        .ifz                ; quit if B is 0
            .break .if !( esi & 0x7FFF0000 )
        .endif
        mov ecx,esi         ; exponent and sign of A into EDI
        rol esi,16          ; shift to top
        sar esi,16          ; duplicate sign
        sar ecx,16          ; ...
        and esi,0x80007FFF  ; isolate signs and exponent
        and ecx,0x80007FFF  ; ...
        mov r9d,ecx         ; assume A < B
        rol esi,16          ; rotate signs to bottom
        rol ecx,16          ; ...
        add cx,si           ; calc sign of result
        rol esi,16          ; rotate signs to top
        rol ecx,16          ; ...
        sub cx,si           ; calculate difference in exponents
        .ifnz               ; if different
            .ifb            ; if B < A
                mov r9d,esi ; get larger exponent for result
                neg cx      ; negate the shift count
                _FLIPAB     ; flip operands
            .endif
            .if cx > 128    ; if shift count too big
                mov esi,r9d
                shl esi,1   ; get sign
                rcr si,1    ; merge with exponent
                _LOADB      ; get result
                .break
            .endif
        .endif
        mov esi,r9d
        mov ch,0            ; zero extend B
        or  ecx,ecx         ; get bit 0 of sign word - value is 0 if
                            ; both operands have same sign, 1 if not
        .ifs                ; if signs are different
            mov ch,-1       ; - set high part to ones
            _NEGATEB
            xor esi,0x80000000 ; - flip sign
        .endif
        .repeat
ifdef _WIN64
            xor r8d,r8d         ; get a zero for sticky bits
            .if cl              ; if shifting required
                .if cl >= 64    ; if shift count >= 64
                    .if rax     ; check low order qword for 1 bits
                        inc r8d ; r11=1 if RAX non zero
                    .endif
                    .if cl == 128   ; if shift count is 128
                        shr rdx,32  ; get rest of sticky bits from high part
                        or  r8d,edx
                        xor edx,edx ; zero high part
                    .endif
                    mov rax,rdx     ; shift right 64
                    xor edx,edx
                .endif
                xor  r9d,r9d
                mov  r10d,eax
                shr  r10d,15
                shrd r9d,r10d,cl    ; get the extra sticky bits
                or   r8d,r9d        ; save them
                shrd rax,rdx,cl     ; align the fractions
                shr  rdx,cl
            .endif
            add rax,rbx
            adc rdx,rdi
            adc ch,0
            .ifs
                .if cl == 128
                    .if r8d & 0x7FFFFFFF
                        stc
                    .else
                        clc
                    .endif
                    adc rax,0   ; round up fraction if required
                    adc rdx,0
                .endif
                neg rdx
                neg rax
                sbb rdx,0
                mov ch,0
                xor esi,0x80000000
            .endif
            mov r9d,ecx
            and r9d,0xFF00
            or  r9,rax
            or  r9,rdx
else
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
                .endif
                push eax            ; get the extra sticky bits
                push ebx
                xor  ebx,ebx
                shr  eax,15
                shrd ebx,eax,cl
                or   reg,ebx        ; save them
                pop  ebx
                pop  eax
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
endif
            .ifz
                xor esi,esi
            .endif
            .break .if !si
            ;
            ; if top bits are 0
            ;
            test ch,ch
ifdef _WIN64
            mov ecx,r8d
else
            mov ecx,reg
endif
            .ifz
                rol ecx,1       ; set carry from last sticky bit
                rol ecx,1
                .repeat
                    dec si      ; decrement exponent
                    .break(1) .ifz
                    _RCL
                .untilb         ; until carry
            .endif
            inc si
            cmp si,Q_EXPMASK
            je  overflow
            stc                 ; set carry
            _RCR                ; shift fraction right 1
            add ecx,ecx         ; get top sticky bit
            .ifc                ; set carry with bit 14 of AX
ifdef _WIN64
                adc rax,0x4000  ; round up fraction if required
                adc rdx,0
else
                adc eax,0x4000  ; round up fraction if required
                adc edx,0
                adc ebx,0
                adc edi,0
endif
                .ifc            ; if we got a carry
                    _RCR        ; shift fraction right 1
                    inc si      ; increment exponent
                    cmp si,Q_EXPMASK
                    je overflow
                .endif
            .endif
        .until 1
        add esi,esi
        rcr si,1
        .break

    er_NaN_A:   ; A is a NaN or infinity
        dec si
        add esi,0x10000
        .ifnc
            .break .ifno
        .endif
        sub esi,0x10000
ifdef _WIN64
        mov r11,0x8000000000000000
        .if !rax
            .if !rbx
                .if rdx == rdi && rdx == r11
                    shr rdx,2
else
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
endif
                    or  esi,-1 ; -NaN
                    .break
                .endif
            .endif
        .endif
        _CMPAB
        jna return_B
        .break

      er_NaN_B:         ; B is a NaN or infinity
        sub esi,0x10000
ifdef _WIN64
        .if !rbx
            mov rdx,0x8000000000000000
            .if rdx == rdi
                mov r9d,esi
                shl r9d,16
                xor esi,r9d
                and esi,0x80000000
                sub edi,0x80000000
            .endif
        .endif
else
        mov ecx,b.m128i_u32[0]
        or  ecx,b.m128i_u32[4]
        or  ecx,b.m128i_u32[8]
        .ifz
            mov edi,0x80000000
            .if edi == b.m128i_u32[12]
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,edi
                sub b.m128i_u32[12],edi
            .endif
        .endif
endif
      return_B:
        _LOADB
        shr esi,16
        .break
      overflow:
        mov esi,0x7FFF
      return_si0:
        add esi,esi
        rcr si,1
        jmp return_m0
      return_m0:
        xor eax,eax
        xor edx,edx
ifndef _WIN64
        xor ebx,ebx
        xor edi,edi
endif
    .until 1
    _STORE
    ret
name endp
    endm

_MULQ macro name
    _PROLOG name
ifndef _WIN64
    local multiplier:__m128i, b:__m128i, highproduct:__m128i
endif
    _LOAD
    .repeat ; create frame -- no loop
        _ISNAN
        _ISZEROA            ; A is 0 ?
        .ifz                ; exit if A is 0
            add si,si       ; place sign in carry
            .break .ifz     ; return 0
            rcr si,1        ; restore sign of A
        .endif
        _ISZEROB            ; exit if B is 0
        .ifz
            test esi,0x7FFF0000
            jz return_0
        .endif
        mov ecx,esi         ; exponent and sign of A into EDI
        rol ecx,16          ; shift to top
        sar ecx,16          ; duplicate sign
        sar esi,16          ; ...
        and ecx,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        add esi,ecx         ; determine exponent of result and sign
        sub si,0x3FFE       ; remove extra bias
        .ifnc               ; exponent negative ?
            cmp si,0x7FFF   ; overflow ?
            ja  overflow
        .endif
        .ifs si < -64       ; exponent too small ?
            dec si
            jmp return_si0
        .endif
ifdef _WIN64
        mov     r10,rbx
        mov     r11,rdi
        mov     r8,rax
        mov     r9,rdi
        mov     rdi,rdx
        mul     r10
        mov     rbx,rdx
        mov     rcx,rax
        mov     rax,rdi
        mul     r11
        mov     r11,rdx
        xchg    r10,rax
        mov     rdx,rdi
        mul     rdx
        add     rbx,rax
        adc     r10,rdx
        adc     r11,0
        mov     rax,r8
        mov     rdx,r9
        mul     rdx
        add     rbx,rax
        adc     r10,rdx
        adc     r11,0
        mov     rdx,rbx
        mov     rax,rcx
        mov     rcx,rdx
        mov     rax,r10
        mov     rdx,r11
        test    rdx,rdx
else
        mov multiplier.m128i_u32[0],eax
        mov multiplier.m128i_u32[4],edx
        mov multiplier.m128i_u32[8],ebx
        mov multiplier.m128i_u32[12],edi
        _mul256(&multiplier, &b, &highproduct)  ; A * B
        mov ecx,multiplier.m128i_u32[12]
        mov eax,highproduct.m128i_u32[0]
        mov edx,highproduct.m128i_u32[4]
        mov ebx,highproduct.m128i_u32[8]
        mov edi,highproduct.m128i_u32[12]
        or  edi,edi
endif
        .ifns ; if not normalized
            shl rcx,1
            _RCL
            dec si
        .endif
        shl rcx,1
        .ifb
            .ifz
ifdef _WIN64
                .if ecx
else
                .if multiplier.m128i_u32[8]
endif
                    stc
                .else
                    bt eax,0
                .endif
            .endif
ifdef _WIN64
            adc rax,0
            adc rdx,0
else
            adc eax,0
            adc edx,0
            adc ebx,0
            adc edi,0
endif
            .ifc
                _RCR
                inc si
                cmp si,0x7FFF
                jz overflow
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
ifdef _WIN64
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr  edi,cl
else
            shrd rax,rdx,cl
            shr  rdx,cl
endif
            xor si,si
        .endif
        add esi,esi
        rcr si,1
        .break

    er_NaN_A:   ; A is a NaN or infinity
ifdef _WIN64
        mov r8,0x8000000000000000
        .if !rax && rdx == r8
else
        .if !eax && !edx && !ebx && edi == 0x80000000
endif
            _ISZEROB
            .ifz
                mov esi,-1 ; -NaN
                .break
            .endif
        .endif
        dec si
        add esi,0x10000
        .ifnb
            .ifno
ifdef _WIN64
                .if !rax && rdx == r8
else
                .if !eax && !edx && !ebx && edi == 0x80000000
endif
                    or esi,esi
                    .ifs
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        _CMPAB
        .ifna
            .ifz
ifdef _WIN64
                .break .if rax || rdx != r8
else
                .break .if eax || edx || ebx
                .break .if edi != 0x80000000
endif
                or si,si
                .ifs
                    xor esi,0x80000000
                .endif
            .endif
            jmp return_B
        .endif
        .break

      er_NaN_B:         ; B is a NaN or infinity
        sub esi,0x10000
ifdef _WIN64
        mov r8,0x8000000000000000
        .if !rbx
            .if rdi == r8
else
        mov ecx,b.m128i_u32[0]
        or  ecx,b.m128i_u32[4]
        or  ecx,b.m128i_u32[8]
        .ifz
            .if b.m128i_u32[12] == 0x80000000
endif
                _ISZEROA
                .ifz
                    mov esi,-1 ; -NaN
                .else
                    or si,si
                    .ifs
                        xor esi,0x80000000 ; flip sign bit
                    .endif
                .endif
            .endif
        .endif
      return_B:
        _LOADB
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
ifndef _WIN64
        xor ebx,ebx
        xor edi,edi
endif
    .until 1
    _STORE
    ret
name endp
    endm

_DIVQ macro name
    _PROLOG name
ifndef _WIN64
    local dividend:__m256i, b:__m256i, reminder:__m256i
    xor eax,eax
    lea edi,b   ; -- divisor
    mov ecx,2*8
    rep stosd
endif
    _LOAD
    .repeat ; create frame -- no loop
        _ISNAN
        _ISZEROB    ; B is 0 ?
        .ifz
            .if !( esi & 0x7FFF0000 )
                _ISZEROA    ; A is 0 ?
                .ifz        ; exit if A is 0
                    mov edi,esi
                    add di,di
                    .ifz
                        ;
                        ; Invalid operation - return NaN
                        ;
                        _OP32 mov edi,0x40000000
                        _OP64 mov rdx,0x4000000000000000
                        mov esi,0x7FFF
                        .break
                    .endif
                .endif
                ;
                ; zero divide - return infinity
                ;
                or esi,0x7FFF
                jmp return_m0
            .endif
        .endif
        _ISZEROA            ; A is 0 ?
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
                _SHL        ; - shift fraction left
            .untilb         ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            .repeat
                dec si
                _SHLB
            .untilb
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
        jl  return_0        ; return underflow
ifdef _WIN64
        push    r12
        push    r13
        push    r14
        mov     r10,rbx
        mov     r11,rdi
        mov     r13,rax
        mov     r14,rdx
        xor     eax,eax
        xor     edx,edx
        xor     ebx,ebx
        or      rdi,r10
        jz      D4
        xor     r8d,r8d
        xor     r9d,r9d
        xor     edi,edi
        xor     r12d,r12d
        mov     esi,127
D0:
        inc     esi
        add     r10,r10
        adc     r11,r11
        jc      D1
        cmp     r11,r14
        jb      D0
        ja      D1
        cmp     r10,r13
        jbe     D0
D1:
        rcr     r11,1
        rcr     r10,1
        rcr     r9,1
        rcr     r8,1
        sub     rdi,r8
        sbb     r12,r9
        sbb     r13,r10
        sbb     r14,r11
        cmc
        jc      D3
D2:
        add     rax,rax
        adc     rdx,rdx
        adc     rbx,rbx
        dec     esi
        js      D4
        shr     r11,1
        rcr     r10,1
        rcr     r9,1
        rcr     r8,1
        add     rdi,r8
        adc     r12,r9
        adc     r13,r10
        adc     r14,r11
        jnc     D2
D3:
        adc     rax,rax
        adc     rdx,rdx
        adc     rbx,rbx
        dec     esi
        jns     D1
D4:
        pop     r14
        pop     r13
        pop     r12
        mov     esi,ecx
        dec     si
        shr     bl,1    ; overflow bit..
else
        mov esi,ecx
        mov dividend.m256i_u32[16],eax  ; save dividend
        mov dividend.m256i_u32[20],edx
        mov dividend.m256i_u32[24],ebx
        mov dividend.m256i_u32[28],edi
        _udiv256(&dividend, &b, &reminder)
        mov eax,dividend.m256i_u32[0]         ; load quotient
        mov edx,dividend.m256i_u32[4]
        mov ebx,dividend.m256i_u32[8]
        mov edi,dividend.m256i_u32[12]
        dec si
        shr dividend.m256i_u8[16],1           ; overflow bit..
endif
        .ifc
            _RCR
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
ifdef _WIN64
            shrd rax,rdx,cl
            shr  rdx,cl
else
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr edi,cl
endif
            xor esi,esi
        .endif
        add esi,esi
        rcr si,1
        .break

      er_NaN_A:             ; A is a NaN or infinity
  _OP64 mov r8,0x8000000000000000
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .ifs
ifdef _WIN64
                    .if !rax && rdx == r8
else
                    .if !eax && !edx && !ebx && edi == 0x80000000
endif
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
ifdef _WIN64
        .if !rax
            .if !rbx
                .if rdx == r8 && rdi == r8
else
        .if !eax && !edx && !ebx
            mov ecx,b.m256i_u32[0]
            or  ecx,b.m256i_u32[4]
            or  ecx,b.m256i_u32[8]
            .ifz
                .if edi == 0x80000000 && edi == b.m256i_u32[12]
endif
                    sar edi,1
                    or  esi,-1 ; -NaN
                    .break
                .endif
            .endif
        .endif
        _CMPAB
        jna return_B
        .break

      er_NaN_B:             ; B is a NaN or infinity
        sub esi,0x10000
ifdef _WIN64
        .if !rbx
            mov rdx,0x8000000000000000
            .if rdx == rdi
                mov r9d,esi
                shl r9d,16
                xor esi,r9d
                and esi,0x80000000
                sub edi,0x80000000
            .endif
        .endif
else
        mov ecx,b.m256i_u32[0]
        or  ecx,b.m256i_u32[4]
        or  ecx,b.m256i_u32[8]
        .ifz
            mov edi,0x80000000
            .if edi == b.m256i_u32[12]
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,edi
                sub b.m256i_u32[12],edi
            .endif
        .endif
endif
      return_B:
        _LOADB
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
ifndef _WIN64
        xor ebx,ebx
        xor edi,edi
endif
    .until 1

    _STORE
    ret

name endp
    endm

_NORMQ macro name, DIVQ, MULQ

  local argq, qmax, temp, tmp2

    option win64:nosave

name proc QFCALLCONV uses rsi rdi rbx q:XQFLOAT, exponent:int_t
ifndef _WIN64
  local factor:__m128i
    mov     factor.m128i_u32[0],0
    mov     factor.m128i_u32[4],0
    mov     factor.m128i_u32[8],0
    mov     factor.m128i_u32[12],0x3FFF0000 ; 1.0
    mov     edi,exponent
    argq    equ <q>
    qmax    equ <addr _Q_1E4096>
    temp    equ <addr factor>
    tmp2    equ <q>
else
    argq    equ <xmm0>
    qmax    equ <_Q_1E4096>
    temp    equ <xmm0>
    tmp2    equ <xmm2>
    mov     edi,edx
endif

    .ifs ( edi > 4096 )
        MULQ(argq, qmax)
        sub edi,4096
    .elseif ( sdword ptr edi < -4096 )
        DIVQ(argq, qmax)
        add edi,4096
    .endif
    .if edi
        xor ebx,ebx
ifdef _WIN64
        movaps xmm2,xmm0
        movaps xmm0,_Q_ONE
endif
        .ifs edi < 0
            neg edi
            inc ebx
        .endif
        .if edi >= 8192
            mov edi,8192
        .endif
        .for ( rsi = &_Q_1E1 : edi : edi >>= 1, rsi += 16 )
            .if ( edi & 1 )
ifdef _WIN64
                MULQ(temp, [rsi])
else
                MULQ(temp, rsi)
endif
            .endif
        .endf
        .if ebx
            DIVQ(tmp2, temp)
        .else
            MULQ(tmp2, temp)
        .endif
    .endif
    ret
name endp
    endm


_CMPQ macro name

    option win64:rsp nosave noauto

name proc QFCALLCONV A:XQFLOAT, B:XQFLOAT

ifdef _WIN64

    xor eax,eax

    _mm_cvtsi128_si64(xmm0, rcx)
    _mm_shuffle_ps(xmm0, xmm0, _MM_SHUFFLE(1,0,3,2))
    _mm_cvtsi128_si64(xmm0, rdx)
    _mm_shuffle_ps(xmm0, xmm0, _MM_SHUFFLE(1,0,3,2))
    _mm_cvtsi128_si64(xmm1, r10)
    _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(1,0,3,2))
    _mm_cvtsi128_si64(xmm1, r11)
    _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(1,0,3,2))

    .repeat

        .break .if ( rdx == r11 && rcx == r10 )

        .ifs ( rdx >= rax && r11 < rax )

            inc eax
            ret
        .endif

        .ifs ( rdx < rax && r11 >= rax )

            dec rax
            ret
        .endif

        .ifs ( rdx < rax && r11 < rax )

            xchg rcx,r10
            xchg rdx,r11
        .endif

        .if rdx == r11

            cmp rcx,r10
        .endif

        sbb rax,rax
        sbb rax,-1
    .until 1

else

    mov ecx,A
    mov edx,B

    assume ecx:ptr __m128i
    assume edx:ptr __m128i

    .repeat

        .if ( [ecx].m128i_u32[0]  == [edx].m128i_u32[0] && \
              [ecx].m128i_u32[4]  == [edx].m128i_u32[4] && \
              [ecx].m128i_u32[8]  == [edx].m128i_u32[8] && \
              [ecx].m128i_u32[12] == [edx].m128i_u32[12] )

            xor eax,eax
            .break
        .endif

        .if ( [ecx].m128i_i8[15] >= 0 && [edx].m128i_i8[15] < 0 )

            mov eax,1
            .break
        .endif

        .if ( [ecx].m128i_i8[15] < 0 && [edx].m128i_i8[15] >= 0 )

            mov eax,-1
            .break
        .endif

        .if ( [ecx].m128i_i8[15] < 0 && [edx].m128i_i8[15] < 0 )
            .if ( [edx].m128i_u32[12] == [ecx].m128i_u32[12] )
                .if ( [edx].m128i_u32[8] == [ecx].m128i_u32[8] )
                    .if ( [edx].m128i_u32[4] == [ecx].m128i_u32[4] )
                        mov eax,[ecx].m128i_u32
                        cmp [edx].m128i_u32,eax
                    .endif
                .endif
            .endif
        .else
            .if ( [ecx].m128i_u32[12] == [edx].m128i_u32[12] )
                .if ( [ecx].m128i_u32[8] == [edx].m128i_u32[8] )
                    .if ( [ecx].m128i_u32[4] == [edx].m128i_u32[4] )
                        mov eax,[edx].m128i_u32
                        cmp [ecx].m128i_u32,eax
                    .endif
                .endif
            .endif
        .endif
        sbb eax,eax
        sbb eax,-1
    .until 1
endif
    ret
name endp
    endm


_CVTQ_H macro name

HFLT_MAX equ 0x7BFF
HFLT_MIN equ 0x0001

    option win64:rsp nosave noauto

name proc QCALLCONVR q:XQFLOAT
ifdef _WIN64
    movhlps xmm0,xmm0
    movq rax,xmm0
    shld rcx,rax,16     ; get exponent and sign
    shrd rdx,rax,32     ; get rounding bits
    shr rax,32          ; get top part
    shr eax,1

    .if ecx & Q_EXPMASK

        or eax,0x80000000
    .endif

    mov r9d,eax         ; duplicate it
    shl r9d,H_SIGBITS+1 ; get rounding bit
    mov r9d,0xFFE00000  ; get mask of bits to keep

    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if edx == 0
                shl r9d,1
            .endif
        .endif
        add eax,0x80000000 shr (H_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif

    mov edx,ecx         ; save exponent and sign
    and cx,Q_EXPMASK    ; if number not 0

    .repeat

        .ifnz
            .if cx == Q_EXPMASK
                .if ( eax & 0x7FFFFFFF )

                    mov eax,-1
                    .break
                .endif
                mov eax,0x7C000000 shl 1
                shl dx,1
                rcr eax,1
                .break
            .endif
            add cx,H_EXPBIAS-Q_EXPBIAS
            .ifs
                ;
                ; underflow
                ;
                mov eax,0x00010000
                mov errno,ERANGE
                .break
            .endif

            .if cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && eax > r9d )
                ;
                ; overflow
                ;
                mov eax,0x7BFF0000 shl 1
                shl dx,1
                rcr eax,1
                mov errno,ERANGE
                .break

            .endif

            and  eax,r9d ; mask off bottom bits
            shl  eax,1
            shrd eax,ecx,H_EXPBITS
            shl  dx,1
            rcr  eax,1

            .break .ifs cx || eax >= HFLT_MIN

            mov errno,ERANGE
            .break

        .endif
        and eax,r9d
    .until 1
    shr eax,16
    movd xmm0,eax
else
    push ebx
    mov ebx,q
    mov eax,[ebx+10]    ; get top part
    mov cx,[ebx+14]     ; get exponent and sign
    shr eax,1
    .if ecx & Q_EXPMASK
        or eax,0x80000000
    .endif
    mov edx,eax         ; duplicate it
    shl edx,H_SIGBITS+1 ; get rounding bit
    mov edx,0xFFE00000  ; get mask of bits to keep
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [ebx+6] == 0
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr (H_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    mov ebx,ecx         ; save exponent and sign
    and cx,Q_EXPMASK    ; if number not 0

    .repeat

        .ifnz
            .if cx == Q_EXPMASK
                .if (eax & 0x7FFFFFFF)
                    mov eax,-1
                    .break
                .endif
                mov eax,0x7C000000 shl 1
                shl bx,1
                rcr eax,1
                .break
            .endif

            add cx,H_EXPBIAS-Q_EXPBIAS
            .ifs
                ;
                ; underflow
                ;
                mov eax,0x00010000
                _set_errno(ERANGE)
                .break
            .endif

            .if cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && eax > edx )
                ;
                ; overflow
                ;
                mov eax,0x7BFF0000 shl 1
                shl bx,1
                rcr eax,1
                _set_errno(ERANGE)
                .break
            .endif

            and  eax,edx ; mask off bottom bits
            shl  eax,1
            shrd eax,ecx,H_EXPBITS
            shl  bx,1
            rcr  eax,1

            .break .ifs cx || eax >= HFLT_MIN
            _set_errno(ERANGE)
            .break
        .endif
        and eax,edx
    .until 1
    shr eax,16
    mov ecx,eax
    mov eax,x
    mov [eax],cx
    .if eax == q
        xor ecx,ecx
        mov [eax+2],cx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
    .endif
    pop ebx
endif
    ret
name endp
    endm

_CVTQ_SS macro name

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

    option win64:rsp nosave noauto

name proc QCALLCONVR q:XQFLOAT
ifdef _WIN64
    movq rcx,xmm0
    shufps xmm0,xmm0,11101110B
    movq rax,xmm0
    shld rdx,rax,16
    shrd rcx,rax,16
    shr  rax,16

    mov r9d,0xFFFFFF00  ; get mask of bits to keep
    mov r8w,dx
    and r8d,Q_EXPMASK
    neg r8d
    rcr eax,1
    mov r8d,eax         ; duplicate it
    shl r8d,25          ; get rounding bit
    mov r8w,dx          ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if ecx == 0
                shl r9d,1
            .endif
        .endif
        add eax,0x0100
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc r8w
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,r9d         ; mask off bottom bits
    mov r9d,r8d         ; save exponent and sign
    and r8w,0x7FFF      ; if number not 0
    .ifnz
        .if r8w == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl r9w,1
            rcr eax,1
        .else
            add r8w,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor eax,eax
                mov errno,ERANGE
            .else
                .ifs r8w >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl r9w,1
                    rcr eax,1
                    mov errno,ERANGE
                .else
                    shl eax,1
                    shrd eax,r8d,8
                    shl r9w,1
                    rcr eax,1
                    .ifs !r8w && eax < DDFLT_MIN
                        mov errno,ERANGE
                    .endif
                .endif
            .endif
        .endif
    .endif
    movd xmm0,eax
else
    push ebx
    mov ebx,q
    mov edx,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[ebx+10]    ; get top part
    mov cx,[ebx+14]
    and ecx,Q_EXPMASK
    neg ecx
    rcr eax,1
    mov ecx,eax         ; duplicate it
    shl ecx,F_SIGBITS+1 ; get rounding bit
    mov cx,[ebx+14]     ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [ebx+6] == 0
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr (F_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,edx         ; mask off bottom bits
    mov ebx,ecx         ; save exponent and sign
    and cx,0x7FFF       ; if number not 0
    .ifnz
        .if cx == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl bx,1
            rcr eax,1
        .else
            add cx,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor eax,eax
                _set_errno(ERANGE)
            .else
                .ifs cx >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl bx,1
                    rcr eax,1
                    _set_errno(ERANGE)
                .else
                    shl eax,1
                    shrd eax,ecx,8
                    shl bx,1
                    rcr eax,1
                    .ifs !cx && eax < DDFLT_MIN
                        _set_errno(ERANGE)
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov ecx,eax
    mov eax,x
    mov [eax],ecx
    .if eax == q
        xor ecx,ecx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
    .endif
    pop ebx
endif
    ret
name endp
    endm


_CVTQ_LD macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR q:XQFLOAT
ifdef _WIN64
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shld    rdx,rax,16

    mov     eax,ecx
    and     eax,LD_EXPMASK
    neg     eax
    mov     rax,rdx
    rcr     rax,1

    ;; round result

    .ifc
        .if rax == -1
            mov rax,0x8000000000000000
            inc cx
        .else
            add rax,1
        .endif
    .endif

    movq    xmm0,rax
    movd    xmm1,ecx
    movlhps xmm0,xmm1

else

    push    ebx
    mov     eax,q
    movzx   ecx,word ptr [eax+14]
    mov     edx,[eax+10]
    mov     ebx,ecx
    and     ebx,LD_EXPMASK
    neg     ebx
    mov     eax,[eax+6]
    rcr     edx,1
    rcr     eax,1
    ;
    ; round result
    ;
    .ifc
        .if eax == -1 && edx == -1
            xor eax,eax
            mov edx,0x80000000
            inc cx
        .else
            add eax,1
            adc edx,0
        .endif
    .endif

    mov     ebx,x
    mov     [ebx],eax
    mov     [ebx+4],edx
    mov     [ebx+8],cx
    mov     eax,ebx
    pop     ebx
endif
    ret
name endp
    endm

_CVTQ_SD macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR q:XQFLOAT
ifdef _WIN64
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shrd    rax,rdx,32
    shr     rdx,16
    mov     r10d,eax
    or      r10d,edx
    and     ecx,0xFFFF
    mov     r8d,ecx
    and     r8d,Q_EXPMASK
    mov     r9d,r8d
    neg     r8d
    rcr     edx,1
    rcr     eax,1
    mov     r8d,eax
    shl     r8d,22
    jnc     L1
    jnz     L2
    add     r8d,r8d
L2:
    add     eax,0x0800
    adc     edx,0
    jnc     L1
    mov     edx,0x80000000
    inc     cx
L1:
    and     eax,0xFFFFF800
    mov     r8d,ecx
    and     cx,0x7FFF
    add     cx,0x03FF-0x3FFF
    jz      L4
    cmp     cx,0x07FF
    jb      L5
    cmp     cx,0xC400
    jb      L7
    cmp     cx,-52
    jl      L8
    mov     r8d,0xFFFFF800
    sub     cx,12
    neg     cx
    cmp     cx,32
    jb      L9
    sub     cl,32
    mov     r8d,eax
    mov     eax,edx
    xor     edx,edx
L9:
    shrd    r8d,eax,cl
    shrd    eax,edx,cl
    shr     edx,cl
    add     r8d,r8d
    adc     eax,0
    adc     edx,0
    jmp     L3
L8:
    xor     eax,eax
    xor     edx,edx
    shl     r8d,17
    rcr     edx,1
    jmp     L3
L7:
    shrd    eax,edx,11
    shl     edx,1
    shr     edx,11
    shl     r8w, 1
    rcr     edx,1
    or      edx,0x7FF00000
    jmp     L3
L4:
    shrd    eax,edx,12
    shl     edx,1
    shr     edx,12
    jmp     L6
L5:
    shrd    eax,edx,11
    shl     edx,1
    shrd    edx,ecx,11
L6:
    shl     r8w,1
    rcr     edx,1
L3:
    xor     r8d,r8d
    cmp     r9d,0x3BCC
    jnb     L11
    or      r10d,r9d
    jz      L10
    xor     eax,eax
    xor     edx,edx
    mov     r8d,ERANGE
    jmp     L13
L11:
    cmp     r9d,0x3BCD
    jb      L12
    mov     r9d,edx
    and     r9d,0x7FF00000
    mov     r8d,ERANGE
    jz      L13
    cmp     r9d,0x7FF00000
    je      L13
    jmp     L10
L12:
    cmp     r9d,0x3BCC
    jb      L10
    mov     r9d,edx
    or      r9d,eax
    mov     r8d,ERANGE
    jz      L13
    mov     r9d,edx
    and     r9d,0x7FF00000
    jnz     L10
L13:
    xchg    r8,rax
    mov     errno,eax
    mov     rax,r8
L10:
    shl     rdx,32
    or      rax,rdx
    movq    xmm0,rax
else
    push    esi
    push    edi
    push    ebx
    mov     eax,q
    movzx   ecx,word ptr [eax+14]
    mov     edx,[eax+10]
    mov     ebx,ecx
    and     ebx,Q_EXPMASK
    mov     edi,ebx
    neg     ebx
    mov     eax,[eax+6]
    rcr     edx,1
    rcr     eax,1
    mov     esi,0xFFFFF800
    mov     ebx,eax
    shl     ebx,22
    .ifc
        .ifz
            shl ebx,1
        .endif
        add eax,0x0800
        adc edx,0
        .ifc
            mov edx,0x80000000
            inc cx
        .endif
    .endif
    and eax,esi
    mov ebx,ecx
    and cx,0x7FFF
    add cx,0x03FF-0x3FFF
    .if cx < 0x07FF
        .if !cx
            shrd eax,edx,12
            shl  edx,1
            shr  edx,12
        .else
            shrd eax,edx,11
            shl  edx,1
            shrd edx,ecx,11
        .endif
        shl bx,1
        rcr edx,1
    .else
        .if cx >= 0xC400
            .ifs cx >= -52
                sub cx,12
                neg cx
                .if cl >= 32
                    sub cl,32
                    mov esi,eax
                    mov eax,edx
                    xor edx,edx
                .endif
                shrd esi,eax,cl
                shrd eax,edx,cl
                shr edx,cl
                add esi,esi
                adc eax,0
                adc edx,0
            .else
                xor eax,eax
                xor edx,edx
                shl ebx,17
                rcr edx,1
            .endif
        .else
            shrd eax,edx,11
            shl edx,1
            shr edx,11
            shl bx, 1
            rcr edx,1
            or  edx,0x7FF00000
        .endif
    .endif
    xor ebx,ebx
    .if edi < 0x3BCC
        mov ecx,q
        .if !(!edi && edi == [ecx+6] && edi == [ecx+10])
            xor eax,eax
            xor edx,edx
            mov ebx,ERANGE
        .endif
    .elseif edi >= 0x3BCD
        mov edi,edx
        and edi,0x7FF00000
        mov ebx,ERANGE
        .ifnz
            .if edi != 0x7FF00000
                xor ebx,ebx
            .endif
        .endif
    .elseif edi >= 0x3BCC
        mov edi,edx
        or  edi,eax
        mov ebx,ERANGE
        .ifnz
            mov edi,edx
            and edi,0x7FF00000
            .ifnz
                xor ebx,ebx
            .endif
        .endif
    .endif
    .if ebx
        _set_errno(ebx)
    .endif
    mov ebx,x
    mov [ebx],eax
    mov [ebx+4],edx
    .if ebx == q
        xor eax,eax
        mov [ebx+8],eax
        mov [ebx+12],eax
    .endif
    mov eax,ebx
    pop ebx
    pop edi
    pop esi
endif
    ret
name endp
    endm


_CVTQ_I32 macro name

    option win64:rsp nosave noauto

name proc QFCALLCONV q:XQFLOAT

ifdef _WIN64
    shufps  xmm0,xmm0,01001110B
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shr     rdx,16
else
    mov     edx,q
    mov     cx,[edx+14]
endif
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor eax,eax
    .elseif eax > 32 + Q_EXPBIAS
ifdef _WIN64
        mov errno,ERANGE
else
        _set_errno(ERANGE)
endif
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
ifdef _WIN64
        mov r8,rcx
else
        mov edx,[edx+10]
endif
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        mov eax,1
        shld eax,edx,cl
ifdef _WIN64
        .if r8w & 0x8000
else
        mov ecx,q
        .if byte ptr [ecx+15] & 0x80
endif
            neg eax
        .endif
    .endif
    ret

name endp

    endm


_CVTQ_I64 macro name

    option win64:rsp nosave noauto

name proc QFCALLCONV q:XQFLOAT

ifdef _WIN64
    movq r8,xmm0
    movhlps xmm0,xmm0
    movq rdx,xmm0
    shld rcx,rdx,16

    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor rax,rax
        .if ecx & 0x8000
            dec rax
        .endif
    .elseif eax > 62 + Q_EXPBIAS
        mov errno,ERANGE
        mov rax,_I64_MAX
        .if ecx & 0x8000
            mov rax,_I64_MIN
        .endif
    .else
        shld rdx,r8,16
        mov  r8d,eax
        sub  r8d,Q_EXPBIAS
        mov  rax,1
        .while r8d
            shl rdx,1
            rcl rax,1
            dec r8d
        .endw
        .if ecx & 0x8000
            neg rax
        .endif
    .endif

else

    mov edx,q
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor edx,edx
        xor eax,eax
        .if cx & 0x8000
            dec eax
            dec edx
        .endif
    .elseif eax > 62 + Q_EXPBIAS
        _set_errno(ERANGE)
        xor eax,eax
        .if cx & 0x8000
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif
    .else
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        push esi
        push edi
        mov edi,[edx+10]
        mov esi,[edx+6]
        mov eax,1
        xor edx,edx
        .while ecx
            shl esi,1
            rcl edi,1
            rcl eax,1
            rcl edx,1
            dec ecx
        .endw
        pop edi
        pop esi
        mov ecx,q
        .if byte ptr [ecx+15] & 0x80
            neg edx
            neg eax
            sbb edx,0
        .endif
    .endif
endif
    ret
name endp
    endm


; cvti32_q() - long to Quadruple float

_CVTI32_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR l:long_t

ifdef _WIN64
    mov  eax,0x3FFF
    test ecx,ecx        ; if number is negative
    .ifs
        neg ecx         ; negate number
        mov eax,0xBFFF  ; set exponent
    .endif
    .if ecx
        bsr edx,ecx     ; find most significant non-zero bit
        xchg ecx,edx
        mov ch,cl
        mov cl,32
        sub cl,ch
        shl rdx,cl      ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,eax     ; calculate exponent
        mov eax,edx     ; get the bits
    .else
        xor eax,eax     ; else zero
    .endif
    shl     rax,32
    shrd    rax,rcx,16
    movq    xmm0,rax
    shufps  xmm0,xmm0,01001110B
else
    mov  eax,l
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        mov edx,0xBFFF  ; set exponent
    .else
        mov edx,0x3FFF
    .endif
    .if eax
        bsr ecx,eax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,32
        sub cl,ch
        .if cl == 32
            xor eax,eax
        .else
            shl eax,cl  ; shift bits into position
        .endif
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
        mov edx,eax     ; get the bits
    .else
        xor ecx,ecx     ; else zero
        xor edx,edx
    .endif
    mov eax,x
    mov [eax+10],edx
    mov [eax+14],cx
    xor edx,edx         ; zero the rest of the fraction bits
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],dx
endif
    ret
name endp
    endm


; CVTI64_Q() - long long to Quadruple float

_CVTI64_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR ll:int64_t

ifdef _WIN64
    mov  rax,rcx
    test rcx,rcx        ; if number is negative
    .ifs
        neg rax         ; negate number
        mov edx,Q_EXPBIAS or 0x8000
    .else               ; set exponent
        mov edx,Q_EXPBIAS
    .endif

    .if rax

        bsr rcx,rax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl < 64     ; shift bits into position
            shl rax,cl
        .else
            xor eax,eax
        .endif
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
    .else
        xor ecx,ecx     ; else zero
    .endif

    shld    rcx,rax,64-16
    shl     rax,64-16
    movq    xmm0,rax
    movq    xmm1,rcx
    movlhps xmm0,xmm1

else

    push ebx
    mov  eax,dword ptr ll
    mov  edx,dword ptr ll[4]
    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        mov ebx,Q_EXPBIAS or 0x8000
    .else
        mov ebx,Q_EXPBIAS ; set exponent
    .endif
    .if eax || edx
        .if edx         ; find most significant non-zero bit
            bsr ecx,edx
            add ecx,32
        .else
            bsr ecx,eax
        .endif
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl < 64     ; shift bits into position
            .if cl < 32
                shld edx,eax,cl
                shl eax,cl
            .else
                and cl,31
                mov edx,eax
                xor eax,eax
                shl edx,cl
             .endif
       .else
            xor eax,eax
            xor edx,edx
        .endif
        shr ecx,8       ; get shift count
        add ecx,ebx     ; calculate exponent
    .else
        xor ecx,ecx     ; else zero
    .endif
    mov ebx,x
    xchg eax,ebx
    mov [eax+6],ebx
    mov [eax+10],edx
    mov [eax+14],cx
    xor edx,edx         ; zero the rest of the fraction bits
    mov [eax],edx
    mov [eax+4],dx
    pop ebx
endif
    ret
name endp
    endm


_CVTH_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR h:XQREAL2
ifdef _WIN64
    movd eax,xmm0           ; get half value
    movsx eax,ax
    mov ecx,eax             ; get exponent and sign
    shl eax,H_EXPBITS+16    ; shift fraction into place
    sar ecx,15-H_EXPBITS    ; shift to bottom
    and cx,H_EXPMASK        ; isolate exponent
    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov ecx,Q_EXPMASK
                mov eax,0x40000000 ; QNaN
                mov errno,EDOM
            .else
                xor eax,eax
            .endif
        .endif
    .elseif eax
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif
    shl     rax,1+32
    add     ecx,ecx
    rcr     cx,1
    shrd    rax,rcx,16
    movq    xmm0,rax
    shufps  xmm0,xmm0,01001110B

else

    mov     ecx,h               ; get half value
    movsx   eax,word ptr [ecx]
    mov     ecx,eax             ; get exponent and sign
    shl     eax,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov ecx,Q_EXPMASK
                mov eax,0x40000000 ; QNaN
                _set_errno(EDOM)
            .else
                xor eax,eax
            .endif
        .endif
    .elseif eax
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif

    mov     edx,x
    shl     eax,1
    xchg    eax,edx
    mov     [eax+10],edx
    xor     edx,edx
    mov     [eax],edx
    mov     [eax+4],edx
    mov     [eax+8],dx
    shl     ecx,1
    rcr     cx,1
    mov     [eax+14],cx
endif
    ret
name endp
    endm


_CVTSS_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR f:XQREAL4
ifdef _WIN64
    movd edx,xmm0
    mov ecx,edx     ; get exponent and sign
    shl edx,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,0x3FFF-0x7F
        .else
            or ch,0x7F
            .if !( edx & 0x7FFFFFFF )
                ;
                ; Invalid exception
                ;
                or edx,0x40000000 ; QNaN
                mov errno,EDOM
            .endif
        .endif
        or edx,0x80000000
    .elseif edx
        or cx,0x3FFF-0x7F+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif
    shl     rdx,1+32
    add     ecx,ecx
    rcr     cx,1
    shrd    rdx,rcx,16
    movq    xmm0,rdx
    shufps  xmm0,xmm0,01001110B
else
    mov ecx,f               ; get float value
    mov eax,[ecx]
    mov ecx,eax             ; get exponent and sign
    shl eax,F_EXPBITS       ; shift fraction into place
    sar ecx,F_SIGBITS-1     ; shift to bottom
    xor ch,ch               ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,Q_EXPBIAS-F_EXPBIAS
        .else
            or ch,0x7F
            .if !(eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                or eax,0x40000000 ; QNaN
                _set_errno(EDOM)
            .endif
        .endif
        or eax,0x80000000
    .elseif eax
        or cx,Q_EXPBIAS-F_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif
    mov edx,x
    shl eax,1
    xchg eax,edx
    mov [eax+10],edx
    xor edx,edx
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],dx
    shl ecx,1
    rcr cx,1
    mov [eax+14],cx
endif
    ret
name endp
    endm


_CVTSD_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR d:XQREAL8

ifdef _WIN64
    movq    rax,xmm0
    mov     rdx,rax
    shl     rax,11
    sar     rdx,64-12
    and     dx,0x7FF
    jz      L1
    mov     r8,0x8000000000000000
    or      rax,r8
    cmp     dx,0x7FF
    je      L2
    add     dx,0x3FFF-0x03FF
L0:
    add     edx,edx
    rcr     dx,1
    shl     rax,1
    xor     ecx,ecx
    shrd    rcx,rax,16
    shrd    rax,rdx,16
    movq    xmm1,rax
    movq    xmm0,rcx
    movlhps xmm0,xmm1
    ret
L1:
    test    rax,rax
    jz      L0
    or      edx,0x3FFF-0x03FF+1
    bsr     r8,rax
    mov     ecx,63
    sub     ecx,r8d
    shl     rax,cl
    sub     dx,cx
    jmp     L0
L2:
    or      dh,0x7F
    not     r8
    test    rax,r8
    jz      L0
    not     r8
    shr     r8,1
    or      rax,r8
    jmp     L0

else

    mov     ecx,d
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    mov     ecx,edx
    shld    edx,eax,11
    shl     eax,11
    sar     ecx,32-12
    and     cx,0x7FF

    .ifnz
        .if cx != 0x7FF
            add cx,0x3FFF-0x03FF
        .else
            or ch,0x7F
            .if edx & 0x7FFFFFFF || eax
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif edx || eax
        or ecx,0x3FFF-0x03FF+1
        .if !edx
            xchg edx,eax
            sub cx,32
        .endif
        .repeat
            test edx,edx
            .break .ifs
            shl eax,1
            rcl edx,1
        .untilcxz
    .endif
    add     ecx,ecx
    rcr     cx,1
    shl     eax,1
    rcl     edx,1
    push    ebx
    mov     ebx,x
    xchg    eax,ebx
    mov     [eax+6],ebx
    mov     [eax+10],edx
    mov     [eax+14],cx
    xor     ebx,ebx
    mov     [eax],ebx
    mov     [eax+4],bx
    pop     ebx
endif
    ret
name endp
    endm

_CVTLD_Q macro name

    option win64:rsp nosave noauto

name proc QCALLCONVR ld:XQREAL10

ifdef _WIN64
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movd    edx,xmm0
    add     edx,edx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    movq    xmm1,rdx
    movq    xmm0,rax
    movlhps xmm0,xmm1
else
    mov     eax,x
    mov     ecx,ld
    mov     dx,[ecx+8]
    mov     [eax+14],dx
    mov     edx,[ecx+4]
    mov     ecx,[ecx]
    shl     ecx,1
    rcl     edx,1
    mov     [eax+6],ecx
    mov     [eax+10],edx
    xor     ecx,ecx
    mov     [eax],ecx
    mov     [eax+4],cx
endif
    ret
name endp
    endm

_CVTQ_A macro name, NORMQ, CVTQI, CVTIQ, SUBQ, MULQ
  local id
ifdef _WIN64
  id equ <r8d>
else
  id equ <i>
endif

STK_BUF_SIZE    equ 128
NDIG            equ 8
D_CVT_DIGITS    equ 20
LD_CVT_DIGITS   equ 23
QF_CVT_DIGITS   equ 34
NO_TRUNC        equ 0x40    ; always provide ndigits in buffer
E8_EXP          equ 0x4019
E8_HIGH         equ 0xBEBC2000
E8_LOW          equ 0x00000000
E16_EXP         equ 0x4034
E16_HIGH        equ 0x8E1BC9BF
E16_LOW         equ 0x04000000

    assume rbx:ptr CVT_INFO
    option win64:align

name proc QFCALLCONV uses rsi rdi rbx q:XQFLOAT, cvt:ptr, buf:string_t, flags:uint_t

    local qf     :REAL16
ifndef _WIN64
    local tmp    :REAL16
    local tmp2   :REAL16
endif
    local i      :int_t
    local n      :int_t
    local nsig   :int_t
    local xexp   :int_t
    local p      :string_t
    local drop   :char_t
    local value  :int_t
    local maxsize:int_t
    local digits :int_t
    local stkbuf[STK_BUF_SIZE]:char_t

    mov eax,flags
    mov ecx,D_CVT_DIGITS
    .if eax & FL_LONGDOUBLE
        mov ecx,LD_CVT_DIGITS
    .elseif eax & FL_LONGLONG
        mov ecx,QF_CVT_DIGITS
    .endif

    mov     digits,ecx
    mov     rbx,cvt
    xor     eax,eax
    mov     [rbx].n1,eax
    mov     [rbx].nz1,eax
    mov     [rbx].n2,eax
    mov     [rbx].nz2,eax
    mov     [rbx].decimal_place,eax
    mov     value,eax
ifdef _WIN64
    movaps  qf,xmm0
    mov     ax,word ptr qf[14]
else
    lea     edi,qf
    mov     esi,q
    mov     ecx,7
    rep     movsw
    lodsw
endif
    bt      eax,15
    sbb     ecx,ecx
    mov     [rbx].sign,ecx
    and     eax,Q_EXPMASK   ; make number positive
    mov     word ptr qf[14],ax
    movzx   ecx,ax
    lea     rdi,qf
ifdef _WIN64
    movaps  xmm0,qf
endif
    xor     eax,eax

    .repeat

        .if ecx == Q_EXPMASK
            ;
            ; NaN or Inf
            ;
ifdef _WIN64
            or rax,[rdi]
else
            or eax,[rdi]
            or eax,[rdi+4]
endif
            or eax,[rdi+8]
            or ax,[rdi+12]
            .ifz
                ;
                ; INFINITY
                ;
                mov eax,'fni'
                or  [rbx].flags,_ST_ISINF
            .else
                ;
                ; NaN
                ;
                mov eax,'nan'
                or  [rbx].flags,_ST_ISNAN
            .endif
            .if [rbx].flags & _ST_CAPEXP
                and eax,NOT 0x202020
            .endif
            mov rdx,buf
            mov [rdx],eax
            mov [rbx].n1,3

            .break
        .endif

        .if !ecx
            ;
            ; ZERO/DENORMAL
            ;
            mov [rbx].sign,eax ; force sign to +0.0
            mov xexp,eax

        .else

            mov esi,ecx
            sub cx,0x3FFE
            mov eax,30103
            mul ecx
            mov ecx,100000
            div ecx
            sub eax,NDIG / 2
            mov xexp,eax

            .if eax

                .ifs
                    ;
                    ; scale up
                    ;
                    neg eax
                    add eax,NDIG / 2 - 1
                    and eax,NOT (NDIG / 2 - 1)
                    neg eax
                    mov xexp,eax
                    neg eax
ifdef _WIN64
                    NORMQ(xmm0, eax)
else
                    NORMQ(edi, eax)
endif
                .else

                    mov eax,[rdi+6]
                    mov edx,[rdi+10]
                    stc
                    rcr edx,1
                    rcr eax,1

                    .if (esi < E8_EXP || (esi == E8_EXP && edx < E8_HIGH))
                        ;
                        ; number is < 1e8
                        ;
                        mov xexp,0

                    .else
                        .if (esi < E16_EXP || ((esi == E16_EXP && (edx <  E16_HIGH || \
                            (edx == E16_HIGH && eax < E16_LOW)))))
                            ;
                            ; number is < 1e16
                            ;
                            mov xexp,8
                        .endif
                        ;
                        ; scale number down
                        ;
                        mov eax,xexp
                        and eax,NOT (NDIG / 2 - 1)
                        mov xexp,eax
                        neg eax
ifdef _WIN64
                        NORMQ(xmm0, eax)
else
                        NORMQ(edi, eax)
endif
                    .endif
                .endif
            .endif
        .endif

        .if [rbx].flags & _ST_F

            mov eax,[rbx].ndigits
            add eax,xexp
            add eax,2 + NDIG
            .ifs [rbx].scale > 0

                add eax,[rbx].scale
            .endif
        .else
            mov eax,[rbx].ndigits
            add eax,4 + NDIG / 2 ; need at least this for rounding
        .endif

        mov ecx,digits
        .if [rbx].flags & NO_TRUNC
            shl ecx,1
        .endif
        add ecx,NDIG / 2
        .if eax > ecx
            mov eax,ecx
        .endif

        mov n,eax
        mov maxsize,ecx
        ;
        ; convert ld into string of digits
        ; put in leading '0' in case we round 99...99 to 100...00
        ;
        lea rsi,stkbuf
        mov word ptr [rsi],'0'
        inc rsi
        mov i,0

        .whiles n > 0

            sub n,NDIG

            .if !value
                ;
                ; get long value to subtract
                ;
ifdef _WIN64
                movaps xmm3,xmm0
                .if CVTQI(xmm0)

                    mov value,eax
                    SUBQ(xmm3, CVTIQ(eax))
                .elseif i && value
                    xorps xmm0,xmm0
                .endif
                .if n
                    MULQ(xmm0, _Q_1E8)
                .endif
else
                .if CVTQI(edi)

                    mov value,eax

                    CVTIQ(&tmp, eax)
                    SUBQ(edi, &tmp)
                .elseif i && value
                    mov [edi],eax
                    mov [edi+4],eax
                    mov [edi+8],eax
                    mov [edi+12],eax
                .endif
                .if n
                    MULQ(edi, &_Q_1E8)
                .endif
endif
            .endif

            .for ( ecx = NDIG, eax = value, ebx = 10: ecx: ecx-- )

                xor edx,edx
                div ebx
                add dl,'0'
                mov [rsi+rcx-1],dl
            .endf
            add rsi,NDIG
            add i,NDIG
            mov value,0
        .endw

ifdef _WIN64
        mov r9,buf
        mov r8d,i
endif
        ;
        ; get number of characters in buf
        ;
        .for ( eax = i, ; skip over leading zeros
               rsi = &stkbuf[1],
               ecx = xexp,
               ecx += NDIG-1,
             : byte ptr [rsi] == '0' : eax--, ecx--, rsi++ )
        .endf

        mov n,eax
        mov rbx,cvt
        mov edx,[rbx].ndigits

        .if [rbx].flags & _ST_F
            add ecx,[rbx].scale
            add edx,ecx
            inc edx
        .elseif [rbx].flags & _ST_E
            .ifs [rbx].scale > 0
                inc edx
            .else
                add edx,[rbx].scale
            .endif
            inc ecx             ; xexp = xexp + 1 - scale
            sub ecx,[rbx].scale
        .endif

        .ifs edx >= 0           ; round and strip trailing zeros
            .ifs edx > eax
                mov edx,eax     ; nsig = n
            .endif
            mov eax,digits
            .if [rbx].flags & NO_TRUNC
                shl eax,1
            .endif
            .if edx > eax
                mov edx,eax
            .endif
            mov maxsize,eax
            mov eax,'0'
            .if n > edx && byte ptr [rsi+rdx] >= '5' || \
                n == edx && byte ptr [rsi+rdx-1] == '9'
                mov al,'9'
            .endif
            lea rdi,[rsi+rdx-1]
            .while [rdi] == al
                dec rdx
                dec rdi
            .endw
            .if al == '9'       ; round up
                inc byte ptr [rdi]
            .endif
            sub rdi,rsi
            .ifs edi < 0
                dec rsi         ; repeating 9's rounded up to 10000...
                inc edx
                inc ecx
            .endif
        .endif

        .ifs edx <= 0
            mov edx,1           ; nsig = 1
            xor ecx,ecx         ; xexp = 0
            mov stkbuf,'0'
            mov [rbx].sign,ecx
            lea rsi,stkbuf
        .endif

        mov id,0
        mov eax,[rbx].flags
        .ifs eax & _ST_F || (eax & _ST_G && ((ecx >= -4 && ecx < [rbx].ndigits) || eax & _ST_CVT))

ifdef _WIN64
            mov rdi,r9
else
            mov edi,buf
endif
            inc ecx

            .if eax & _ST_G
                .if edx < [rbx].ndigits && !(eax & _ST_DOT)
                    mov [rbx].ndigits,edx
                .endif
                sub [rbx].ndigits,ecx
                .ifs [rbx].ndigits < 0
                    mov [rbx].ndigits,0
                .endif
            .endif

            .ifs ecx <= 0 ; digits only to right of '.'

                .if !( eax & _ST_CVT )

                    mov byte ptr [rdi],'0'
ifdef _WIN64
                    inc r8d
                    .ifs [rbx].ndigits > 0 || eax & _ST_DOT
                        mov byte ptr [rdi+1],'.'
                        inc r8d
                    .endif
                .endif
                add rdi,r8
                mov [rbx].n1,r8d
else
                    inc edi
                    .ifs [ebx].ndigits > 0 || eax & _ST_DOT
                        mov byte ptr [edi],'.'
                        inc edi
                    .endif
                .endif

                mov eax,edi
                sub eax,buf
                mov i,eax
                mov [ebx].n1,eax
endif
                mov eax,ecx
                neg eax
                .if [rbx].ndigits < eax
                    mov ecx,[rbx].ndigits
                    neg ecx
                .endif
                mov [rbx].decimal_place,ecx
                mov [rbx].nz1,eax
                add [rbx].ndigits,eax
                .ifs [rbx].ndigits < edx
                    mov edx,[rbx].ndigits
                .endif
                mov ecx,eax
                mov [rbx].n2,edx
                mov eax,[rbx].ndigits
                add edx,ecx
                sub eax,edx
                mov [rbx].nz2,eax
                mov rax,buf
                .if word ptr [rax] == '.0'
                    add id,ecx
                    sub edx,ecx
                    sub [rbx].nz2,ecx
                    mov eax,'0'
                    rep stosb
                .endif
                add id,edx
                mov ecx,edx
                rep movsb
                mov ecx,[rbx].nz2
                add id,ecx
                mov eax,'0'
                rep stosb

            .elseif edx < ecx ; zeros before '.'

                add id,edx
                mov [rbx].n1,edx
                mov eax,ecx
                sub eax,edx
                mov [rbx].nz1,eax
                mov [rbx].decimal_place,ecx
                mov ecx,edx
                rep movsb
                add id,eax
                mov ecx,eax
                mov eax,'0'
                rep stosb

                .if !( [rbx].flags & _ST_CVT )

                    .if ( [rbx].ndigits > 0 || [rbx].flags & _ST_DOT )
ifdef _WIN64
                        mov byte ptr [r9+r8],'.'
else
                        mov al,'.'
                        stosb
endif
                        inc id
                        mov [rbx].n2,1
                    .endif
                .endif
                mov ecx,[rbx].ndigits
                mov [rbx].nz2,ecx

                .if ( ecx > edx )
                    sub ecx,edx
                    add id,ecx
                    mov eax,'0'
                    rep stosb
                .endif
            .else                    ; enough digits before '.'

                mov [rbx].decimal_place,ecx
                add id,ecx
                sub edx,ecx
                rep movsb
ifdef _WIN64
                mov rdi,r9
else
                mov edi,buf
endif
                mov ecx,[rbx].decimal_place

                .if !([rbx].flags & _ST_CVT)
                    .ifs [rbx].ndigits > 0 || [rbx].flags & _ST_DOT
ifdef _WIN64
                        mov byte ptr [rdi+r8],'.'
else
                        mov eax,edi
                        add eax,i
                        mov byte ptr [eax],'.'
endif
                        inc id
                    .endif
                .elseif byte ptr [rdi] == '0' ; ecvt or fcvt with 0.0
                    mov [rbx].decimal_place,0
                .endif
                .ifs [rbx].ndigits < edx
                    mov edx,[ebx].ndigits
                .endif
ifdef _WIN64
                add rdi,r8
else
                add edi,i
endif
                mov ecx,edx
                rep movsb
                add id,edx
                mov [rbx].n1,id
                mov eax,edx
                mov ecx,[rbx].ndigits
                add edx,ecx
                mov [rbx].nz1,edx
                sub ecx,eax
                add id,ecx
                mov eax,'0'
                rep stosb
            .endif
ifdef _WIN64
            mov byte ptr [r9+r8],0
else
            mov edi,buf
            add edi,i
            mov byte ptr [edi],0
endif
        .else

            mov eax,[rbx].ndigits
            .ifs [rbx].scale <= 0
                add eax,[rbx].scale   ; decrease number of digits after decimal
            .else
                sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
                inc eax
            .endif

            mov id,0
            .if [rbx].flags & _ST_G
                ;
                ; fixup for 'G'
                ; for 'G' format, ndigits is the number of significant digits
                ; cvt->scale should be 1 indicating 1 digit before decimal place
                ; so decrement ndigits to get number of digits after decimal place
                ;
                .if (edx < eax && !([rbx].flags & _ST_DOT))
                    mov eax,edx
                .endif
                dec eax
                .ifs eax < 0
                    xor eax,eax
                .endif
            .endif

            mov [rbx].ndigits,eax
            mov xexp,ecx
ifdef _WIN64
            mov r10d,edx
            mov rdi,r9
            .ifs [rbx].scale <= 0
                mov byte ptr [r9],'0'
else
            mov nsig,edx
            mov edi,buf
            .ifs [rbx].scale <= 0
                mov byte ptr [edi],'0'
endif
                inc id

            .else

                mov eax,[rbx].scale
                .if eax > edx
                    mov eax,edx
                .endif
ifdef _WIN64
                mov edx,eax
                add rdi,r8          ; put in leading digits
                mov ecx,eax
                mov rax,rsi
                rep movsb
                mov rsi,rax
                add r8d,edx
                add rsi,rdx
                sub r10d,edx
                .ifs edx < [rbx].scale    ; put in zeros if required
                    mov ecx,[rbx].scale
                    sub ecx,edx
                    add r8d,ecx
                    lea rdi,[r9+r8]
else
                mov n,eax
                add edi,i           ; put in leading digits
                mov ecx,eax
                mov eax,esi
                rep movsb
                mov esi,eax
                mov eax,n
                add i,eax
                add esi,eax
                sub nsig,eax
                .ifs eax < [ebx].scale    ; put in zeros if required
                    mov ecx,[ebx].scale
                    sub ecx,eax
                    mov n,ecx
                    add i,ecx
                    mov edi,buf
                    add edi,i
endif
                    mov al,'0'
                    rep stosb
                .endif
            .endif
ifdef _WIN64
            mov [rbx].decimal_place,r8d
else
            mov ecx,i
            mov edi,buf
            mov [rbx].decimal_place,ecx
endif

            mov eax,[rbx].ndigits
            .if !([rbx].flags & _ST_CVT)
                .ifs eax > 0 || [rbx].flags & _ST_DOT
ifdef _WIN64
                    mov byte ptr [r9+r8],'.'
else
                    mov byte ptr [edi+ecx],'.'
endif
                    inc id
                .endif
            .endif

            mov ecx,[rbx].scale
            .ifs ecx < 0
                neg ecx
ifdef _WIN64
                lea rdi,[r9+r8]
                add r8d,ecx
                mov al,'0'
                rep stosb
            .endif
            mov ecx,r10d
else
                mov n,ecx
                add edi,i
                mov al,'0'
                rep stosb
                mov eax,n
                add i,eax
            .endif
            mov ecx,nsig
endif
            mov eax,[rbx].ndigits

            .ifs eax > 0        ; put in fraction digits

                .ifs eax < ecx
                    mov ecx,eax
ifdef _WIN64
                    mov r10d,eax
                .endif
                .if ecx
                    lea rdi,[r9+r8]
                    add r8d,ecx
                    rep movsb
                .endif
                mov [rbx].n1,r8d
                mov ecx,[rbx].ndigits
                sub ecx,r10d
                mov [rbx].nz1,ecx
                lea rdi,[r9+r8]
else
                    mov nsig,eax
                .endif
                .if ecx
                    mov edi,buf
                    add edi,i
                    add i,ecx
                    mov eax,esi
                    rep movsb
                    mov esi,eax
                .endif
                mov eax,i
                mov [ebx].n1,eax
                mov ecx,[ebx].ndigits
                sub ecx,nsig
                mov [ebx].nz1,ecx
                mov edi,buf
                add edi,i
endif
                add id,ecx
                mov eax,'0'
                rep stosb
            .endif
ifdef _WIN64
            mov eax,[rbx].expchar
            .if al
                mov [r9+r8],al
                inc r8d
            .endif
            mov edi,xexp
            .ifs edi >= 0
                mov byte ptr [r9+r8],'+'
            .else
                mov byte ptr [r9+r8],'-'
                neg edi
            .endif
            inc r8d
else
            mov edi,buf
            mov eax,[ebx].expchar
            .if al
                mov ecx,i
                mov [edi+ecx],al
                inc i
            .endif
            mov eax,xexp
            mov ecx,i
            .ifs eax >= 0
                mov byte ptr [edi+ecx],'+'
                inc i
            .else
                mov byte ptr [edi+ecx],'-'
                inc i
                neg eax
            .endif
            mov xexp,eax
endif
            mov ecx,[rbx].expwidth
            .switch ecx
              .case 0           ; width unspecified
                .ifs eax >= 1000
                    mov ecx,4
                .else
                    mov ecx,3
                .endif
                .endc
              .case 1
                .ifs eax >= 10
                    mov ecx,2
                .endif
              .case 2
                .ifs eax >= 100
                    mov ecx,3
                .endif
              .case 3
                .ifs eax >= 1000
                    mov ecx,4
                .endif
                .endc
            .endsw
            mov [rbx].expwidth,ecx    ; pass back width actually used

            .if ecx >= 4
ifdef _WIN64
                xor esi,esi
                .if eax >= 1000
                    mov ecx,1000
                    xor edx,edx
                    div ecx
                    mov esi,eax
                    mul ecx
                    sub edi,eax
                    mov ecx,[rbx].expwidth
                .endif
                mov eax,esi
                add al,'0'
                mov [r9+r8],al
                inc r8d
            .endif

            .if ecx >= 3
                xor esi,esi
                mov eax,edi
                .ifs edi >= 100
                    mov ecx,100
                    xor edx,edx
                    div ecx
                    mov esi,eax
                    mul ecx
                    sub edi,eax
                    mov ecx,[rbx].expwidth
                .endif
                mov eax,esi
                add al,'0'
                mov [r9+r8],al
                inc r8d
            .endif

            .if ecx >= 2
                xor esi,esi
                mov eax,edi
                .ifs edi >= 10
                    mov ecx,10
                    xor edx,edx
                    div ecx
                    mov esi,eax
                    mul ecx
                    sub edi,eax
                    mov ecx,[rbx].expwidth
                .endif
                mov eax,esi
                add al,'0'
                mov [r9+r8],al
                inc r8d
            .endif

            mov eax,edi
            add al,'0'
            mov [r9+r8],al
            inc r8d
            mov eax,r8d
            sub eax,[rbx].n1
            mov [rbx].n2,eax
            xor eax,eax
            mov [r9+r8],al
else
                mov n,0
                .if eax >= 1000
                    mov ecx,1000
                    xor edx,edx
                    div ecx
                    mov n,eax
                    mul ecx
                    sub xexp,eax
                    mov ecx,[ebx].expwidth
                .endif
                mov eax,n
                add al,'0'
                mov edx,i
                mov [edi+edx],al
                inc i
            .endif

            .if ecx >= 3
                mov n,0
                mov eax,xexp
                .ifs eax >= 100
                    mov ecx,100
                    xor edx,edx
                    div ecx
                    mov n,eax
                    mul ecx
                    sub xexp,eax
                    mov ecx,[ebx].expwidth
                .endif
                mov eax,n
                add al,'0'
                mov edx,i
                mov [edi+edx],al
                inc i
            .endif

            .if ecx >= 2
                mov n,0
                mov eax,xexp
                .ifs eax >= 10
                    mov ecx,10
                    xor edx,edx
                    div ecx
                    mov n,eax
                    mul ecx
                    sub xexp,eax
                    mov ecx,[ebx].expwidth
                .endif
                mov eax,n
                add al,'0'
                mov edx,i
                mov [edi+edx],al
                inc i
            .endif

            mov eax,xexp
            add al,'0'
            mov edx,i
            mov [edi+edx],al
            inc edx
            mov eax,edx
            sub eax,[ebx].n1
            mov [ebx].n2,eax
            xor eax,eax
            mov [edi+edx],al
endif
        .endif
    .until 1
    ret

name endp
    endm

_CVTA_Q macro name, NORMQ

MAXDIGIT        equ 38
MAXSIGDIGIT     equ 49

ifdef _WIN64
option win64:align
name proc vectorcall uses rsi rdi rbx string:string_t, endptr:ptr string_t
  local number:__m128i
else
name proc __cdecl uses esi edi ebx number:ptr, string:string_t, endptr:ptr string_t
endif

  local digits      :int_t,
        sigdig      :int_t,
        flags       :int_t,
        exponent    :int_t,
        buffer[128] :char_t

    xor eax,eax
    mov sigdig,eax
    mov exponent,eax
ifdef _WIN64
    mov rsi,rcx
    mov number.m128i_u64[0],rax
    mov number.m128i_u64[8],rax
else
    mov esi,string
    mov edi,number
    mov [edi],eax
    mov [edi+4],eax
    mov [edi+8],eax
    mov [edi+12],eax
endif
    mov flags,_ST_ISZERO

    .repeat

        .repeat

            lodsb
            .break(1) .if ( al == 0 )
            .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )

        .until 1
        dec rsi

        xor ecx,ecx
        .if ( al == '+' )
            inc rsi
            or  ecx,_ST_SIGN
        .endif
        .if ( al == '-' )
            inc rsi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or al,0x20
        .if ( al == 'n' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'na' )

                add rsi,2
                or ecx,_ST_ISNAN
                movzx eax,byte ptr [rsi]

                .if ( al == '(' )

                    lea rdx,[rsi+1]
                    movzx eax,byte ptr [rdx]

                    .while 1
                        .switch
                          .case ( al == '_' )
                          .case ( al >= '0' && al <= '9' )
                          .case ( al >= 'a' && al <= 'z' )
                          .case ( al >= 'A' && al <= 'Z' )
                            inc rdx
                            mov al,[rdx]
                            .gotosw
                          .default
                            .break
                        .endsw
                    .endw

                    .if al == ')'
                        lea rsi,[rdx+1]
                    .endif
                .endif
            .else
                dec rsi
                or ecx,_ST_INVALID
            .endif
            mov flags,ecx
            .break
        .endif

        .if ( al == 'i' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'fn' )

                add rsi,2
                or ecx,_ST_ISINF
            .else
                dec rsi
                or ecx,_ST_INVALID
            .endif

            mov flags,ecx
            .break
        .endif

        dec rsi
        lea rdi,buffer
        xor ebx,ebx
        xor edx,edx
        xor eax,eax
        ;
        ; Parse the mantissa
        ;
        .while 1

            lodsb
            .break .if !al

            .if ( al == '.' )

                .break .if ( ecx & _ST_DOT )
                or ecx,_ST_DOT

            .else

                .break .if ( al < '0' || al > '9' )

                .if ( ecx & _ST_DOT )

                    inc sigdig
                .endif

                or ecx,_ST_DIGITS
                or edx,eax

                .continue .if edx == '0' ; if a significant digit

                .if ebx < MAXSIGDIGIT
                    stosb
                .endif
                inc ebx
            .endif
        .endw
        mov byte ptr [rdi],0
        mov digits,ebx
        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor edi,edi ; exponent

            or  al,0x20
            .if al == 'e'

                mov al,[rsi]
                lea edx,[rsi-1]
                .if al == '+'
                    inc rsi
                .endif
                .if al == '-'
                    inc rsi
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1

                    movzx eax,byte ptr [rsi]
                    .break .if al < '0'
                    .break .if al > '9'

                    .if edi < 100000000 ; else overflow

                        lea rbx,[rdi*8]
                        lea rdi,[rdi*2+rbx-'0']
                        add rdi,rax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc rsi
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg rdi
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov rsi,rdx
                .endif

            .else

                dec rsi ; digits found, but no e or E
            .endif

            mov rdx,rdi
            mov eax,sigdig
            sub rdx,rax
            mov ebx,digits
            mov eax,MAXDIGIT

            .if ( ebx > eax )

                add rdx,rbx
                mov rbx,rax
                sub edx,eax
            .endif

            lea rax,buffer

            .while 1

                .break .ifs ebx <= 0
                .break .if byte ptr [rax+rbx-1] != '0'

                inc edx
                dec ebx
            .endw

            mov digits,ebx
        .else
            mov rsi,string
        .endif

        mov flags,ecx
        mov exponent,edx
        lea rdx,buffer
        mov eax,digits
        mov byte ptr [rdx+rax],0

        ;
        ; convert string to binary
        ;
ifdef _WIN64
        lea r10,number
else
        push esi
endif
        xor eax,eax
        mov bl,[rdx]

        .if ( bl == '+' || bl == '-' )

            inc rdx
        .endif

        .while 1

            mov al,[rdx]
            .break .if !al

            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
ifdef _WIN64
            mov r11,r10
            .repeat
                movzx edi,word ptr [r11]
                imul  edi,10
                add   eax,edi
                mov   [r11],ax
                add   r11,2
else
            mov esi,number
            .repeat
                movzx edi,word ptr [esi]
                imul  edi,10
                add   eax,edi
                mov   [esi],ax
                add   esi,2
endif
                shr   eax,16
            .untilcxz

            inc rdx
        .endw

ifdef _WIN64

        mov rax,[r10]
        mov rdx,[r10+8]

        .if ( bl == '-' )

            neg rdx
            neg rax
            sbb rdx,0
        .endif
        ;
        ; get bit-count of number
        ;
        xor ecx,ecx
        bsr rcx,rdx
        .ifz
            bsr rcx,rax
        .else
            add ecx,64
        .endif
        .ifnz
            inc ecx
        .endif

        .if ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            mov edi,Q_SIGBITS
            mov ebx,edi
            sub ebx,ecx

            .if ecx > edi
                sub ecx,edi
                ;
                ; or 0x10000 --> 0x1000
                ;
                .if cl >= 64
                    mov rax,rdx
                    xor edx,edx
                    sub cl,64
                .endif
                shrd rax,rdx,cl
                shr rdx,cl

            .elseif ebx

                mov ecx,ebx
                .if cl >= 64
                    mov rdx,rax
                    xor eax,eax
                    sub cl,64
                .endif
                shld rdx,rax,cl
                shl rax,cl

            .endif
            mov [r10],rax
            mov [r10+8],rdx
            ;
            ; create exponent bias and mask
            ;
            mov edi,Q_EXPBIAS+Q_SIGBITS-1
            sub edi,ebx         ; - shift count
            and edi,Q_EXPMASK   ; remove sign bit
            .if flags & _ST_NEGNUM
                or di,0x8000
            .endif
            mov [r10+14],di
        .else
            or flags,_ST_ISZERO
        .endif
else
        mov esi,number
        mov eax,[esi]
        mov edx,[esi+4]
        mov ecx,[esi+8]
        mov esi,[esi+12]

        .if bl == '-'
            neg esi
            neg ecx
            sbb esi,0
            neg edx
            sbb ecx,0
            neg eax
            sbb edx,0
        .endif
        ;
        ; get bit-count of number
        ;
        xor ebx,ebx
        bsr ebx,esi
        .ifz
            bsr ebx,ecx
            .ifz
                bsr ebx,edx
                .ifz
                    bsr ebx,eax
                .else
                    add ebx,32
                .endif
            .else
                add ebx,64
            .endif
        .else
            add ebx,96
        .endif
        .ifnz
            inc ebx
        .endif

        .if ebx

            xchg ebx,ecx
            mov edi,Q_SIGBITS
            sub edi,ecx
            ;
            ; shift number to bit-size
            ;
            ; - 0x0001 --> 0x8000
            ;
            .if ecx > Q_SIGBITS

                sub ecx,Q_SIGBITS
                ;
                ; or 0x10000 --> 0x1000
                ;
                .while cl >= 32
                    mov eax,edx
                    mov edx,ebx
                    mov ebx,esi
                    xor esi,esi
                    sub cl,32
                .endw
                shrd eax,edx,cl
                shrd edx,ebx,cl
                shrd ebx,esi,cl
                shr esi,cl

            .elseif edi

                mov ecx,edi
                .while cl >= 32
                    mov esi,ebx
                    mov ebx,edx
                    mov edx,eax
                    xor eax,eax
                    sub cl,32
                .endw
                shld esi,ebx,cl
                shld ebx,edx,cl
                shld edx,eax,cl
                shl eax,cl
            .endif
            mov ecx,number
            mov [ecx],eax
            mov [ecx+4],edx
            mov [ecx+8],ebx
            mov [ecx+12],esi
            ;
            ; create exponent bias and mask
            ;
            mov ebx,Q_EXPBIAS+Q_SIGBITS-1
            sub ebx,edi
            and ebx,Q_EXPMASK ; remove sign bit
            .if flags & _ST_NEGNUM
                or ebx,0x8000
            .endif
            mov [ecx+14],bx
        .else
            or flags,_ST_ISZERO
        .endif
        pop esi
endif
    .until 1

    mov rax,endptr
    .if rax
        mov [rax],rsi
    .endif

    mov edi,flags
ifdef _WIN64
    mov ax,[r10+14]
else
    mov eax,number
    mov ax,[eax+14]
endif
    and eax,Q_EXPMASK
    mov edx,1

    .switch
      .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
        mov edx,0x7FFF0000
        .if edi & _ST_ISNAN or _ST_INVALID
            or edx,0x00004000
        .endif
        .endc
      .case edi & _ST_OVERFLOW
      .case eax >= Q_EXPMAX + Q_EXPBIAS
        mov edx,0x7FFF0000
        .if edi & _ST_NEGNUM
            or edx,0x80000000
        .endif
        .endc
      .case edi & _ST_UNDERFLOW
        xor edx,edx
        .endc
    .endsw
ifdef _WIN64
    movaps xmm0,[r10]
    .if edx != 1
        xorps xmm0,xmm0
        mov errno,ERANGE
    .elseif exponent
        NORMQ(xmm0, exponent)
    .endif
    mov ecx,exponent
    mov edx,edi
else
    mov eax,number
    .if edx != 1
        xor ecx,ecx
        mov [eax],ecx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
        _set_errno(ERANGE)
    .elseif exponent
        NORMQ(eax, exponent)
    .endif
endif
    ret

name endp
    endm
