; QFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include asmc.inc
include qfloat.inc
include expreval.inc

    .code

ifdef _WIN64

;-------------------------------------------------------------------------------
; 64-bit DIV
;-------------------------------------------------------------------------------

__udiv64 proc watcall dividend:uint64_t, divisor:uint64_t

    mov     rcx,rdx
    xor     edx,edx
    test    rcx,rcx
    jz      .0
    div     rcx
    jmp     .1
.0:
    xor     eax,eax
.1:
    ret

__udiv64 endp

;-------------------------------------------------------------------------------
; 64-bit IDIV
;-------------------------------------------------------------------------------

__div64 proc watcall dividend:int64_t, divisor:int64_t

    test    rax,rax ; dividend signed ?
    js      .0
    test    rdx,rdx ; divisor signed ?
    js      .0
    call    __udiv64
    jmp     .2
.0:
    neg     rax
    test    rdx,rdx
    jns     .1
    neg     rdx
    call    __udiv64
    neg     rdx
    jmp     .2
.1:
    call    __udiv64
    neg     rdx
    neg     rax
.2:
    ret

__div64 endp

;-------------------------------------------------------------------------------
; 64-bit REM
;-------------------------------------------------------------------------------

__rem64 proc watcall dividend:int64_t, divisor:int64_t

    call    __div64
    mov     rax,rdx
    ret

__rem64 endp

_atoow proc fastcall dst:string_t, src:string_t, radix:int_t, bsize:int_t

    push    rcx
    mov     r11,rdx
    xor     edx,edx
    mov     [rcx],rdx
    mov     [rcx+8],rdx
    xor     ecx,ecx

ifdef CHEXPREFIX
    movzx   eax,word ptr [r11]
    or      eax,0x2000
    cmp     eax,'x0'
    jne     .0
    add     r11,2
    sub     r9d,2
.0:
endif

    cmp     r8d,16
    jne     .2

    ; hex value

.1:
    movzx   eax,byte ptr [r11]
    inc     r11
    and     eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
    bt      eax,6           ; digit ?
    sbb     r8d,r8d         ; -1 : 0
    and     r8d,0x37        ; 10 = 0x41 - 0x37
    sub     eax,r8d
    shld    rdx,rcx,4
    shl     rcx,4
    add     rcx,rax
    dec     r9d
    jnz     .1
    jmp     .8

.2:
    cmp     r8d,10
    jne     .5
.3:
    mov     cl,[r11]
    inc     r11
    sub     cl,'0'
.4:
    dec     r9d
    jz      .8

    mov     r8,rdx
    mov     rax,rcx
    shld    rdx,rcx,3
    shl     rcx,3
    add     rcx,rax
    adc     rdx,r8
    add     rcx,rax
    adc     rdx,r8
    movzx   eax,byte ptr [r11]
    inc     r11
    sub     al,'0'
    add     rcx,rax
    adc     rdx,0
    jmp     .4

.5:
    mov     r10,[rsp]
.6:
    movzx   eax,byte ptr [r11]
    and     eax,not 0x30
    bt      eax,6
    sbb     ecx,ecx
    and     ecx,0x37
    sub     eax,ecx
    mov     ecx,8
.7:
    movzx   edx,word ptr [r10]
    imul    edx,r8d
    add     eax,edx
    mov     [r10],ax
    add     r10,2
    shr     eax,16
    dec     ecx
    jnz     .7
    sub     r10,16
    inc     r11
    dec     r9d
    jnz     .6
    pop     rax
    jmp     .9
.8:
    pop     rax
    mov     [rax],rcx
    mov     [rax+8],rdx
.9:
    ret

_atoow endp


else ; _WIN64


;-------------------------------------------------------------------------------
; 64-bit MUL  ecx:ebx:edx:eax = edx:eax * ecx:ebx
;-------------------------------------------------------------------------------

__mul64 proc watcall a:int64_t, b:int64_t

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

__mul64 endp

;-------------------------------------------------------------------------------
; 64-bit DIV
;-------------------------------------------------------------------------------

__udiv64 proc watcall private dividend:qword, divisor:qword

    .repeat

        .break .if ecx

        dec ebx
        .ifnz

            inc ebx
            .if ebx <= edx
                mov  ecx,eax
                mov  eax,edx
                xor  edx,edx
                div  ebx        ; edx / ebx
                xchg ecx,eax
            .endif
            div ebx             ; edx:eax / ebx
            mov ebx,edx
            mov edx,ecx
            xor ecx,ecx
        .endif
        ret
    .until 1

    .repeat

        .break .if ecx < edx
        .ifz
            .if ebx <= eax
                sub eax,ebx
                mov ebx,eax
                xor ecx,ecx
                xor edx,edx
                mov eax,1
                ret
            .endif
        .endif
        xor  ecx,ecx
        xor  ebx,ebx
        xchg ebx,eax
        xchg ecx,edx
        ret

    .until 1

    push ebp
    push esi
    push edi

    xor ebp,ebp
    xor esi,esi
    xor edi,edi

    .repeat

        add ebx,ebx
        adc ecx,ecx
        .ifnc
            inc ebp
            .continue(0) .if ecx < edx
            .ifna
                .continue(0) .if ebx <= eax
            .endif
            add esi,esi
            adc edi,edi
            dec ebp
            .break .ifs
        .endif
        .while 1
            rcr ecx,1
            rcr ebx,1
            sub eax,ebx
            sbb edx,ecx
            cmc
            .continue(0) .ifc
            .repeat
                add esi,esi
                adc edi,edi
                dec ebp
                .break(1) .ifs
                shr ecx,1
                rcr ebx,1
                add eax,ebx
                adc edx,ecx
            .untilb
            adc esi,esi
            adc edi,edi
            dec ebp
            .break(1) .ifs
        .endw
        add eax,ebx
        adc edx,ecx
    .until 1
    mov ebx,eax
    mov ecx,edx
    mov eax,esi
    mov edx,edi
    pop edi
    pop esi
    pop ebp
    ret
__udiv64 endp

;-------------------------------------------------------------------------------
; 64-bit IDIV
;-------------------------------------------------------------------------------

__div64 proc watcall dividend:int64_t, divisor:int64_t

    or edx,edx     ; hi word of dividend signed ?
    .ifns
        or ecx,ecx ; hi word of divisor signed ?
        .ifns
            jmp __udiv64
        .endif
        neg ecx
        neg ebx
        sbb ecx,0
        __udiv64()
        neg edx
        neg eax
        sbb edx,0
        ret
    .endif
    neg edx
    neg eax
    sbb edx,0
    or ecx,ecx
    .ifs
        neg ecx
        neg ebx
        sbb ecx,0
        __udiv64()
        neg ecx
        neg ebx
        sbb ecx,0
        ret
    .endif
    __udiv64()
    neg ecx
    neg ebx
    sbb ecx,0
    neg edx
    neg eax
    sbb edx,0
    ret

__div64 endp

;-------------------------------------------------------------------------------
; 64-bit REM
;-------------------------------------------------------------------------------

__rem64 proc watcall dividend:int64_t, divisor:int64_t

    __div64()
    mov eax,ebx
    mov edx,ecx
    ret

__rem64 endp


_atoow proc uses esi edi ebx dst:string_t, src:string_t, radix:int_t, bsize:int_t

    mov esi,src
    mov edx,dst
    mov ebx,radix
    mov edi,bsize

ifdef CHEXPREFIX
    movzx eax,word ptr [esi]
    or eax,0x2000
    .if eax == 'x0'
        add esi,2
        sub edi,2
    .endif
endif

    xor eax,eax
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],eax
    mov [edx+12],eax

    .repeat

        .if ebx == 16 && edi <= 16

            ; hex value <= qword

            xor ecx,ecx

            .if edi <= 8

                ; 32-bit value

                .repeat
                    mov al,[esi]
                    add esi,1
                    and eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
                    bt  eax,6           ; digit ?
                    sbb ebx,ebx         ; -1 : 0
                    and ebx,0x37        ; 10 = 0x41 - 0x37
                    sub eax,ebx
                    shl ecx,4
                    add ecx,eax
                    dec edi
                .untilz

                mov [edx],ecx
                mov eax,edx
                .break
            .endif

            ; 64-bit value

            xor edx,edx

            .repeat
                mov  al,[esi]
                add  esi,1
                and  eax,not 0x30
                bt   eax,6
                sbb  ebx,ebx
                and  ebx,0x37
                sub  eax,ebx
                shld edx,ecx,4
                shl  ecx,4
                add  ecx,eax
                adc  edx,0
                dec  edi
            .untilz

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx
            .break

        .elseif ebx == 10 && edi <= 20

            xor ecx,ecx

            mov cl,[esi]
            add esi,1
            sub cl,'0'

            .if edi < 10

                .while 1

                    ; FFFFFFFF - 4294967295 = 10

                    dec edi
                    .break .ifz

                    mov al,[esi]
                    add esi,1
                    sub al,'0'
                    lea ebx,[ecx*8+eax]
                    lea ecx,[ecx*2+ebx]
                .endw

                mov [edx],ecx
                mov eax,edx
                .break

            .endif

            xor edx,edx

            .while 1

                ; FFFFFFFFFFFFFFFF - 18446744073709551615 = 20

                dec edi
                .break .ifz

                mov  al,[esi]
                add  esi,1
                sub  al,'0'
                mov  ebx,edx
                mov  bsize,ecx
                shld edx,ecx,3
                shl  ecx,3
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,eax
                adc  edx,0
            .endw

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx

        .else

            mov bsize,edi
            mov edi,edx
            .repeat
                mov al,[esi]
                and eax,not 0x30
                bt  eax,6
                sbb ecx,ecx
                and ecx,0x37
                sub eax,ecx
                mov ecx,8
                .repeat
                    movzx edx,word ptr [edi]
                    imul  edx,ebx
                    add   eax,edx
                    mov   [edi],ax
                    add   edi,2
                    shr   eax,16
                .untilcxz
                sub edi,16
                add esi,1
                dec bsize
            .untilz
            mov eax,dst
        .endif
    .until 1
    ret

_atoow endp

endif

_atoqw proc fastcall uses rbx string:string_t

    xor     edx,edx
    xor     eax,eax
.0:
    mov     dl,[rcx]
    inc     rcx
    cmp     dl,' '
    je      .0
    mov     bl,dl
    cmp     dl,'+'
    je      .1
    cmp     dl,'-'
    jne     .2
.1:
    mov     dl,[rcx]
    inc     rcx
.2:
    sub     dl,'0'
    jb      .3
    cmp     dl,9
    ja      .3
    imul    eax,eax,10
    add     eax,edx
    mov     dl,[rcx]
    inc     rcx
    jmp     .2
.3:
    cmp     bl,'-'
    jne     .4
    neg     eax
.4:
    ret

_atoqw endp


atofloat proc __ccall _out:ptr, inp:string_t, size:uint_t, negative:int_t, ftype:uchar_t

    mov qerrno,0

    ; v2.04: accept and handle 'real number designator'

    .if ( ftype )

        ; convert hex string with float "designator" to float.
        ; this is supposed to work with real4, real8 and real10.
        ; v2.11: use _atoow() for conversion ( this function
        ;    always initializes and reads a 16-byte number ).
        ;    then check that the number fits in the variable.

        lea eax,[tstrlen(inp)-1]
        mov negative,eax

        ; v2.31.24: the size is 2,4,8,10,16
        ; real4 3ff0000000000000r is allowed: real8 -> real16 -> real4

        .switch eax
        .case 4,8,16,20,32
            .endc
        .case 5,9,17,21,33
            mov rcx,inp
            .if byte ptr [rcx] == '0'
                inc inp
                dec negative
                .endc
            .endif
        .default
            asmerr( 2104, inp )
        .endsw

        _atoow( _out, inp, 16, negative )
        mov eax,size
        .for ( rcx = _out, rdx = rcx, rcx += rax, rdx += 16: rcx < rdx: rcx++ )
            .if ( byte ptr [rcx] != 0 )
                asmerr( 2104, inp )
                .break
            .endif
        .endf

        mov eax,negative
        shr eax,1
        .if eax != size
            .switch eax
            .case 2  : __cvth_q(_out, _out)  : .endc
            .case 4  : __cvtss_q(_out, _out) : .endc
            .case 8  : __cvtsd_q(_out, _out) : .endc
            .case 10 : __cvtld_q(_out, _out) : .endc
            .case 16 : .endc
            .default
                .if ( Parse_Pass == PASS_1 )
                    asmerr( 7004 )
                .endif
                tmemset( _out, 0, size )
            .endsw
            .if qerrno
                asmerr( 2071 )
            .endif
        .endif

    .else

        __cvta_q(_out, inp, NULL)
        .if ( qerrno )
            asmerr( 2104, inp )
        .endif
        .if ( negative )
            mov rcx,_out
            or  byte ptr [rcx+15],0x80
        .endif
        mov eax,size
        .switch al
        .case 2
            __cvtq_h(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 4
            __cvtq_ss(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 8
            __cvtq_sd(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 10
            __cvtq_ld(_out, _out)
        .case 16
            .endc
        .default
            ;
            ; sizes != 4,8,10 or 16 aren't accepted.
            ; Masm ignores silently, JWasm also unless -W4 is set.
            ;
            .if ( Parse_Pass == PASS_1 )
                asmerr( 7004 )
            .endif
            tmemset( _out, 0, size )
        .endsw
    .endif
    ret

atofloat endp


    assume rbx:ptr expr

quad_resize proc __ccall uses rsi rbx opnd:ptr expr, size:int_t

    mov     qerrno,0
    mov     rbx,opnd
    movzx   esi,word ptr [rbx+14]
    and     esi,0x7FFF
    mov     eax,size

    .switch eax
    .case 10
        __cvtq_ld(rbx, rbx)
        .endc
    .case 8
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_sd(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[7],0x80
        .endif
        mov [rbx].mem_type,MT_REAL8
        .endc
    .case 4
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_ss(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[3],0x80
        .endif
        mov [rbx].mem_type,MT_REAL4
        .endc
    .case 2
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_h(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[1],0x80
        .endif
        mov [rbx].mem_type,MT_REAL2
        .endc
    .endsw

    .if ( qerrno && esi != 0x7FFF )
        asmerr( 2071 )
    .endif
    ret

quad_resize endp

    end
