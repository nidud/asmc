; _FLTTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _flttostr() - Converts quad float to string
;

include fltintrn.inc

define STK_BUF_SIZE     512 ; ANSI-specified minimum is 509
define NDIG             16

define D_CVT_DIGITS     20
define LD_CVT_DIGITS    23
define QF_CVT_DIGITS    33

define E16_EXP          0x4034
define E16_HIGH         0x8E1BC9BF
define E16_LOW          0x04000000
define E32_EXP          0x4069
define E32_HIGH         ( 0x80000000 or ( 0x3B8B5B50 shr 1 ) )
define E32_LOW          ( 0x56E16B3B shr 1 )

m64 union
struc
 l  int_t ?
 h  int_t ?
ends
v   int64_t ?
m64 ends

    .data
     e_space    db "#not enough space",0

    .code

    assume rbx:ptr FLTINFO

_flttostr proc __ccall uses rsi rdi rbx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local maxsize:int_t
  local digits :int_t
  local flt    :STRFLT
  local tmp    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    ldr rbx,cvt
    ldr rcx,buf
    mov eax,[rbx].bufsize
    add rax,rcx
    dec rax
    mov endbuf,rax

    mov eax,D_CVT_DIGITS
    .if ( flags & _ST_LONGDOUBLE )
        mov eax,LD_CVT_DIGITS
    .elseif ( flags & _ST_QUADFLOAT )
        mov eax,QF_CVT_DIGITS
    .endif
    mov digits,eax

    xor eax,eax
    mov [rbx].n1,eax
    mov [rbx].nz1,eax
    mov [rbx].n2,eax
    mov [rbx].nz2,eax
    mov [rbx].dec_place,eax

    _fltunpack( &flt, q )

    mov ax,flt.mantissa.e
    bt  eax,15
    sbb ecx,ecx
    mov [rbx].sign,ecx
    and eax,Q_EXPMASK   ; make number positive
    mov flt.mantissa.e,ax

    movzx ecx,ax

    xor eax,eax
    mov flt.flags,eax

    .if ( ecx == Q_EXPMASK )

        ; NaN or Inf
ifdef _WIN64
        or rax,flt.mantissa.l
        or rax,flt.mantissa.h
else
        or eax,dword ptr flt.mantissa.l[0]
        or eax,dword ptr flt.mantissa.l[4]
        or eax,dword ptr flt.mantissa.h[0]
        or eax,dword ptr flt.mantissa.h[4]
endif
        .ifz

            ; INFINITY

            mov eax,'fni'
            or  [rbx].flags,_ST_ISINF
        .else

            ; NaN

            mov eax,'nan'
            or  [rbx].flags,_ST_ISNAN
        .endif

        .if ( flags & _ST_CAPEXP )

            and eax,NOT 0x202020
        .endif
        mov rcx,buf
        mov [rcx],eax
        mov [rbx].n1,3
       .return( 64 )
    .endif

    .if ( ecx == 0 )

        ; ZERO/DENORMAL

        mov [rbx].sign,eax ; force sign to +0.0
        mov xexp,eax
        mov flt.flags,_ST_ISZERO

    .else

        mov  esi,ecx
        sub  ecx,0x3FFE
        mov  eax,30103
        imul ecx
        mov  ecx,100000
        idiv ecx
        sub  eax,NDIG / 2
        mov  xexp,eax

        .if ( eax )

            .ifs

                ; scale up

                neg eax
                add eax,NDIG / 2 - 1
                and eax,NOT (NDIG / 2 - 1)
                neg eax
                mov xexp,eax
                neg eax
                mov flt.exponent,eax

                _fltscale( &flt )

            .else

                mov eax,dword ptr flt.mantissa.h[0]
                mov edx,dword ptr flt.mantissa.h[4]

                .if ( esi < E16_EXP || ( ( esi == E16_EXP && ( edx < E16_HIGH ||
                      ( edx == E16_HIGH && eax < E16_LOW ) ) ) ) )

                    ; number is < 1e16

                    mov xexp,0

                .else
                    .if ( esi < E32_EXP || ( ( esi == E32_EXP && ( edx < E32_HIGH ||
                          ( edx == E32_HIGH && eax < E32_LOW ) ) ) ) )

                        ; number is < 1e32

                        mov xexp,16
                    .endif

                    ; scale number down

                    mov eax,xexp
                    and eax,NOT (NDIG / 2 - 1)
                    mov xexp,eax
                    neg eax
                    mov flt.exponent,eax

                    _fltscale( &flt )
                .endif
            .endif
        .endif
    .endif

    mov eax,[rbx].ndigits
    .if ( [rbx].flags & _ST_F )

        add eax,xexp
        add eax,2 + NDIG
        .ifs ( [rbx].scale > 0 )
            add eax,[rbx].scale
        .endif
    .else
        add eax,NDIG + NDIG / 2 ; need at least this for rounding
    .endif
    .if ( eax > STK_BUF_SIZE-1-NDIG )
        mov eax,STK_BUF_SIZE-1-NDIG
    .endif
    mov n,eax

    mov ecx,digits
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert quad into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

   .new value:m64 = {0}
ifndef _WIN64
   .new radix:int_t = 10
endif
    lea rdi,stkbuf
    mov word ptr [rdi],'0'
    inc rdi
    mov i,0

    .while ( n > 0 )

        sub n,NDIG
ifdef _WIN64
        .if ( value.v == 0 )
else
        .if ( value.l == 0 && value.h == 0 )
endif

            ; get value to subtract

            _flttoi64( &flt )
ifdef _WIN64
            mov value.v,rax
else
            mov value.l,eax
            mov value.h,edx
endif
            .ifs ( n > 0 )

                _i64toflt( &tmp, value )
                _fltsub( &flt, &tmp )
                _fltmul( &flt, &_fltpowtable[EXTFLOAT*4] )
            .endif
        .endif

        mov ecx,NDIG

ifdef _WIN64

        mov rax,value.v
        mov value.v,0

        .if ( rax )

            .for ( r8d = 10 : ecx : ecx-- )

                xor edx,edx
                div r8
                add dl,'0'
                mov [rdi+rcx-1],dl

else
        mov eax,value.l
        mov edx,value.h
        mov value.l,0
        mov value.h,0

        .if ( eax || edx )

            add edi,ecx
            mov esi,ecx

            .fors ( : eax || edx || esi > 0 : esi-- )

                .if ( edx == 0 )

                    div radix
                    mov ecx,edx
                    xor edx,edx

                .else

                    push esi
                    push edi

                    .for ( ecx = 64, esi = 0, edi = 0 : ecx : ecx-- )

                        add eax,eax
                        adc edx,edx
                        adc esi,esi
                        adc edi,edi

                        .if ( edi || esi >= radix )

                            sub esi,radix
                            sbb edi,0
                            inc eax
                        .endif
                    .endf
                    mov ecx,esi

                    pop edi
                    pop esi
                .endif

                add cl,'0'
                dec edi
                mov [edi],cl
endif
            .endf
            add rdi,NDIG

        .else

            mov al,'0'
            rep stosb
        .endif

        add i,NDIG
    .endw

    ; get number of characters in buf

    ; skip over leading zeros

    .for ( eax = i,
           edx = STK_BUF_SIZE-2,
           rsi = &stkbuf[1],
           ecx = xexp,
           ecx += NDIG-1 : edx && byte ptr [rsi] == '0' : eax--, ecx--, edx--, rsi++ )
    .endf

    mov n,eax
    mov rbx,cvt
    mov edx,[rbx].ndigits

    .if ( [rbx].flags & _ST_F )

        add ecx,[rbx].scale
        lea edx,[rdx+rcx+1]

    .elseif ( [rbx].flags & _ST_E )

        .ifs ( [rbx].scale > 0 )
            inc edx
        .else
            add edx,[rbx].scale
        .endif

        inc ecx             ; xexp = xexp + 1 - scale
        sub ecx,[rbx].scale
    .endif

    .ifs ( edx >= 0 )       ; round and strip trailing zeros

        .ifs ( edx > eax )
            mov edx,eax     ; nsig = n
        .endif
        mov eax,digits
        .ifs ( edx > eax )
            mov edx,eax
        .endif
        mov maxsize,eax

        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [rsi+rdx] >= '5' ) ||
               ( edx == digits && byte ptr [rsi+rdx-1] == '9' ) )
            mov al,'9'
        .endif

        mov edi,[rbx].scale
        add edi,[rbx].ndigits

        .if ( al == '9' && edx == edi &&
              byte ptr [rsi+rdx] != '9' &&  byte ptr [rsi+rdx-1] == '9' )

            .while edi

                dec edi
               .break .if ( byte ptr [rsi+rdi] != '9' )
            .endw

            .if ( byte ptr [rsi+rdi] == '9' )
                 mov al,'0'
            .endif
        .endif

        lea     rdi,[rsi+rdx-1]
        xchg    ecx,edx
        inc     ecx
        std
        repz    scasb
        cld
        xchg    ecx,edx
        inc     rdi

        .if ( al == '9' ) ; round up
            inc byte ptr [rdi]
        .endif
        sub rdi,rsi
        .ifs
            dec rsi ; repeating 9's rounded up to 10000...
            inc edx
            inc ecx
        .endif
    .endif

    .ifs ( edx <= 0 || flt.flags == _ST_ISZERO )

        mov edx,1   ; nsig = 1
        xor ecx,ecx ; xexp = 0

        mov stkbuf,'0'
        mov [rbx].sign,ecx
        lea rsi,stkbuf
    .endif

    mov i,0
    mov eax,[rbx].flags

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -1 && ecx < [rbx].ndigits ) || eax & _ST_CVT ) ) )

        mov rdi,buf
        inc ecx

        .if ( eax & _ST_G )

            .ifs ( edx < [rbx].ndigits && !( eax & _ST_DOT ) )

                mov [rbx].ndigits,edx
            .endif

            sub [rbx].ndigits,ecx
            .ifs ( [rbx].ndigits < 0 )
                mov [rbx].ndigits,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [rdi],'0'
                inc i

                .ifs ( [rbx].ndigits > 0 || eax & _ST_DOT )

                    mov byte ptr [rdi+1],'.'
                    inc i
                .endif
            .endif

            mov [rbx].n1,i
            mov eax,ecx
            neg eax

            .ifs ( [rbx].ndigits < eax )

                mov ecx,[rbx].ndigits
                neg ecx
            .endif

            mov eax,ecx
            neg eax
            mov [rbx].dec_place,eax
            mov [rbx].nz1,eax
            add [rbx].ndigits,ecx

            .ifs ( [rbx].ndigits < edx )
                mov edx,[rbx].ndigits
            .endif
            mov [rbx].n2,edx

            sub edx,[rbx].ndigits
            neg edx
            mov [rbx].nz2,edx

            mov ecx,[rbx].n1    ; number of leading characters
            add rdi,rcx

            mov ecx,[rbx].nz1   ; followed by this many '0's
            mov eax,[rbx].n2
            add eax,[rbx].nz2
            add eax,ecx
            lea rax,[rdi+rax]
            cmp rax,endbuf
            ja  overflow

            add i,ecx
            mov al,'0'
            rep stosb
            mov ecx,[rbx].n2    ; followed by these characters
            add i,ecx
            rep movsb

            mov ecx,[rbx].nz2   ; followed by this many '0's
            add i,ecx
            rep stosb

        .elseifs ( edx < ecx )  ; zeros before '.'

            add i,edx
            mov [rbx].n1,edx
            mov eax,ecx
            sub eax,edx
            mov [rbx].nz1,eax
            mov [rbx].dec_place,ecx
            mov ecx,edx
            rep movsb

            lea rcx,[rdi+rax+2]
            cmp rcx,endbuf
            ja  overflow
            mov ecx,eax
            mov eax,'0'
            add i,ecx
            rep stosb

            mov ecx,[rbx].ndigits
            .if !( [rbx].flags & _ST_CVT )

                .ifs ( ecx > 0 || [rbx].flags & _ST_DOT )

                    mov byte ptr [rdi],'.'
                    inc rdi
                    inc i
                    mov [rbx].n2,1
                .endif
            .endif

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
            mov [rbx].nz2,ecx
            add i,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [rbx].dec_place,ecx
            add i,ecx
            sub edx,ecx
            rep movsb

            mov rdi,buf
            mov ecx,[rbx].dec_place

            .if !( [rbx].flags & _ST_CVT )

                .ifs ( [rbx].ndigits > 0 || [rbx].flags & _ST_DOT )


                    mov eax,i
                    mov byte ptr [rdi+rax],'.'
                    inc i
                .endif

            .elseif ( byte ptr [rdi] == '0' ) ; ecvt or fcvt with 0.0

                mov [rbx].dec_place,0
            .endif

            .ifs ( [rbx].ndigits < edx )

                mov edx,[rbx].ndigits
            .endif

            mov eax,i
            add rdi,rax
            mov ecx,edx
            rep movsb

            add i,edx
            mov [rbx].n1,i
            mov eax,edx
            mov ecx,[rbx].ndigits
            add edx,ecx
            mov [rbx].nz1,edx
            sub ecx,eax
            add i,ecx

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow

            mov eax,'0'
            rep stosb

        .endif

        mov edi,i
        add rdi,buf
        mov byte ptr [rdi],0

    .else

        mov eax,[rbx].ndigits
        .ifs ( [rbx].scale <= 0 )
            add eax,[rbx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        mov i,0
        .if ( [rbx].flags & _ST_G )

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if ( edx < eax && !( [rbx].flags & _ST_DOT) )
                mov eax,edx
            .endif
            dec eax
            .ifs ( eax < 0 )
                xor eax,eax
            .endif
            .ifs ( ecx > -5 && ecx < 0 )

                neg ecx
                add eax,ecx
                add edx,ecx
                sub rsi,rcx
                xor ecx,ecx
            .endif
        .endif
        mov [rbx].ndigits,eax
        mov xexp,ecx
        mov nsig,edx
        mov rdi,buf

        .ifs ( [rbx].scale <= 0 )

            mov byte ptr [rdi],'0'
            inc i
            .if ( ecx >= maxsize )
                inc xexp
            .endif

        .else

            mov eax,[rbx].scale
            .if ( eax > edx )
                mov eax,edx
            .endif

            mov edx,eax
            mov ecx,i
            add rdi,rcx  ; put in leading digits
            mov ecx,eax
            mov rax,rsi
            rep movsb
            mov rsi,rax

            add i,edx
            add rsi,rdx
            sub nsig,edx

            .ifs ( edx < [rbx].scale ) ; put in zeros if required

                mov ecx,[rbx].scale
                sub ecx,edx
                add i,ecx
                mov edi,i
                add rdi,buf
                mov al,'0'
                rep stosb
            .endif
        .endif

        mov edx,i
        mov rdi,buf
        mov [rbx].dec_place,edx
        mov eax,[rbx].ndigits

        .if !( [rbx].flags & _ST_CVT )

            .ifs ( eax > 0 || [rbx].flags & _ST_DOT )

                mov byte ptr [rdi+rdx],'.'
                inc i
            .endif
        .endif

        mov ecx,[rbx].scale
        .ifs ( ecx < 0 )

            neg ecx
            add rdi,rdx
            add i,ecx
            mov al,'0'
            rep stosb
        .endif

        mov ecx,nsig
        mov eax,[rbx].ndigits

        .ifs ( eax > 0 ) ; put in fraction digits

            .ifs ( eax < ecx )

                mov ecx,eax
                mov nsig,eax
            .endif

            .if ( ecx )

                mov edi,i
                add rdi,buf
                add i,ecx
                rep movsb
            .endif

            mov [rbx].n1,i
            mov ecx,[rbx].ndigits
            sub ecx,nsig
            mov [rbx].nz1,ecx

            mov edi,i
            add rdi,buf
            add i,ecx
            mov eax,'0'
            rep stosb
        .endif

        mov edi,xexp
        mov rsi,buf
        mov ecx,i

        .if ( [rbx].flags & _ST_G && edi == 0 )

            mov edx,ecx
        .else

            mov eax,[rbx].expchar
            .if ( al )

                mov [rsi+rcx],al
                inc i
                inc ecx
            .endif

            .ifs ( edi >= 0 )
                mov byte ptr [rsi+rcx],'+'
            .else
                mov byte ptr [rsi+rcx],'-'
                neg edi
            .endif

            inc i
            mov eax,edi
            mov ecx,[rbx].expwidth

            .switch ecx
            .case 0           ; width unspecified
                mov ecx,3
                .ifs ( eax >= 1000 )
                    mov ecx,4
                .endif
                .endc
            .case 1
                .ifs ( eax >= 10 )
                    mov ecx,2
                .endif
            .case 2
                .ifs ( eax >= 100 )
                    mov ecx,3
                .endif
            .case 3
                .ifs ( eax >= 1000 )
                    mov ecx,4
                .endif
                .endc
            .endsw
            mov [rbx].expwidth,ecx    ; pass back width actually used

            .if ( ecx >= 4 )

                xor edx,edx

                .if ( eax >= 1000 )

                    mov  ecx,1000
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,1000
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            .if ( ecx >= 3 )

                xor edx,edx
                .ifs ( edi >= 100 )

                    mov  eax,edi
                    mov  ecx,100
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,100
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            .if ( ecx >= 2 )

                xor edx,edx
                .ifs ( edi >= 10 )

                    mov  eax,edi
                    mov  ecx,10
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,10
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            mov edx,i
            lea eax,[rdi+'0']
            mov [rsi+rdx],al
            inc edx
         .endif

         mov eax,edx
         sub eax,[rbx].n1
         mov [rbx].n2,eax
         xor eax,eax
         mov [rsi+rdx],al
    .endif

toend:
    ret

overflow:
    mov rdi,buf
    lea rsi,e_space
    mov ecx,sizeof(e_space)
    rep movsb
    jmp toend

_flttostr endp

    end
