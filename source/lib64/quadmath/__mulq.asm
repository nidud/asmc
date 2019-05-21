; __MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

    option win64:rsp noauto

__mulq proc uses rsi rdi rbx A:ptr, B:ptr

    mov     rax,[rcx]           ; A(si:rdx:rax), B(highword(esi):rdi:rbx)
    mov     rbx,[rdx]
    mov     rdi,[rdx+8]
    mov     rdx,[rcx+8]
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
    jmp     @C0018

    .switch jmp r8

      .case 0                   ; return 0
        xor eax,eax
        xor edx,edx
        xor esi,esi
        .endc

      .case 1                   ; return B
        mov rax,rbx
        mov rdx,rdi
        shr esi,16
        .endc

      .case 2                   ; overflow
        mov esi,0x7FFF
        xor eax,eax
        xor edx,edx
        .endc

      .case 3                   ; A is a NaN or infinity
        mov r8,0x8000000000000000
        .if ( !rax && rdx == r8 && !rbx && !rdi )
            mov esi,-1 ; -NaN
            .endc
        .endif
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .ifs ( !rax && rdx == r8 && esi < 0 )
                    xor esi,0x8000
                .endif
                .endc
            .endif
        .endif
        sub esi,0x10000
        .if rdx == rdi
            cmp rax,rbx
        .endif
        .ifna
            .ifz
                .endc .if ( rax || rdx != r8 )
                or si,si
                .ifs
                    xor esi,0x80000000
                .endif
            .endif
            .gotosw(1)
        .endif
        .endc

      .case 4                   ; B is a NaN or infinity
        sub esi,0x10000
        mov r8,0x8000000000000000
        .if ( rbx == 0 && rdi == r8 )

            .if ( !rax && !rdx )
                mov esi,-1      ; -NaN
            .else
                or si,si
                .ifs            ; flip sign bit
                    xor esi,0x80000000
                .endif
            .endif
        .endif
        .gotosw(1)

      .case 5                   ; A is 0
        add si,si               ; place sign in carry
        .endc .ifz              ; return 0
        rcr si,1                ; restore sign of A
        .gotosw(9) .if ( rbx || rdi )

      .case 6                   ; B is 0
        .gotosw(0) .if !( esi & 0x7FFF0000 )
        .gotosw(9)

      .case 7
        dec si
        add esi,esi
        rcr si,1
        xor eax,eax
        xor edx,edx
        .endc

      .case 8

        add si,1                ; add 1 to exponent
        .gotosw(3) .ifc         ; quit if NaN
        .gotosw(3) .ifo
        add esi,0xFFFF          ; readjust low exponent and inc high word
        .gotosw(4) .ifc         ; quit if NaN
        .gotosw(4) .ifo
        sub esi,0x10000         ; readjust high exponent

        .gotosw(5) .if ( rax == 0 && rdx == 0 )
        .gotosw(6) .if ( rbx == 0 && rdi == 0 )

      .case 9

        mov ecx,esi         ; exponent and sign of A into EDI
        rol ecx,16          ; shift to top
        sar ecx,16          ; duplicate sign
        sar esi,16          ; ...
        and ecx,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        add esi,ecx         ; determine exponent of result and sign
        sub si,0x3FFE       ; remove extra bias
        .ifnc               ; exponent negative ?
            .gotosw(2) .if ( si > 0x7FFF )
        .endif
        .gotosw(7) .ifs si < -64

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

        .ifns ; if not normalized

            add rcx,rcx
            adc rax,rax
            adc rdx,rdx
            dec si
        .endif

        shl ecx,1
        .ifc
            .ifz
                .if ecx
                    stc
                .else
                    bt eax,0
                .endif
            .endif
            adc rax,0
            adc rdx,0
            .ifc
                rcr rdx,1
                rcr rax,1
                inc si
                .gotosw(2) .if ( si == 0x7FFF )
            .endif
        .endif

        or si,si
        .ifng
            mov ecx,esi
            .ifz
                mov cl,1
            .else
                neg cx
            .endif
            shrd rax,rdx,cl
            shr rdx,cl
            xor si,si
        .endif

        add esi,esi
        rcr si,1

    .endsw

    mov  rcx,A
    shl  rax,1          ; shift bits back
    rcl  rdx,1          ; shift high bit out..
    shrd rax,rdx,16
    shrd rdx,rsi,16     ; exponent and sign
    mov  [rcx],rax
    mov  [rcx+8],rdx
    mov  rax,rcx        ; return result
    ret

__mulq endp

    end
