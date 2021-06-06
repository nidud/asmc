; _FLTTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _flttostr() - Converts quad float to string
;

include fltintrn.inc
include quadmath.inc

STK_BUF_SIZE    equ 512 ; ANSI-specified minimum is 509
NDIG            equ 16

D_CVT_DIGITS    equ 20
LD_CVT_DIGITS   equ 23
QF_CVT_DIGITS   equ 33

E16_EXP         equ 0x4034
E16_HIGH        equ 0x8E1BC9BF
E16_LOW         equ 0x04000000
E32_EXP         equ 0x4069
E32_HIGH        equ (0x80000000 or (0x3B8B5B50 shr 1))
E32_LOW         equ (0x56E16B3B shr 1)

    .data
     e_space    db "#not enough space",0

    .code

    assume ebx:ptr FLTINFO

_flttostr proc uses esi edi ebx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local value[2]:int_t
  local maxsize:int_t
  local digits :int_t
  local radix  :int_t
  local flt    :STRFLT
  local tmp    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    mov ebx,cvt
    mov eax,buf
    add eax,[ebx].bufsize
    dec eax
    mov endbuf,eax
    mov eax,flags
    mov ecx,D_CVT_DIGITS
    .if eax & _ST_LONGDOUBLE
        mov ecx,LD_CVT_DIGITS
    .elseif eax & _ST_QUADFLOAT
        mov ecx,QF_CVT_DIGITS
    .endif
    mov digits,ecx
    mov radix,10

    xor eax,eax
    mov [ebx].n1,eax
    mov [ebx].nz1,eax
    mov [ebx].n2,eax
    mov [ebx].nz2,eax
    mov [ebx].decimal_place,eax
    mov value,eax
    mov value[4],eax

    _fltunpack(&flt, q)
    mov ax,flt.mantissa.e
    bt  eax,15
    sbb ecx,ecx
    mov [ebx].sign,ecx
    and eax,Q_EXPMASK   ; make number positive
    mov flt.mantissa.e,ax

    movzx ecx,ax
    lea edi,flt
    xor eax,eax
    mov flt.flags,eax

    .if ecx == Q_EXPMASK

        ; NaN or Inf

        or eax,[edi]
        or eax,[edi+4]
        or eax,[edi+8]
        or eax,[edi+12]

        .ifz
            mov eax,'fni'
            or  [ebx].flags,_ST_ISINF
        .else
            mov eax,'nan'
            or  [ebx].flags,_ST_ISNAN
        .endif
        .if flags & _ST_CAPEXP
            and eax,NOT 0x202020
        .endif
        mov edx,buf
        mov [edx],eax
        mov [ebx].n1,3

        .return 0
    .endif

    .if !ecx

        ; ZERO/DENORMAL

        mov [ebx].sign,eax ; force sign to +0.0
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

        .if eax

            .ifs

                ; scale up

                neg eax
                add eax,NDIG / 2 - 1
                and eax,NOT (NDIG / 2 - 1)
                neg eax
                mov xexp,eax
                neg eax
                mov flt.exponent,eax

                _fltscale(&flt)

            .else

                mov eax,[edi+8]
                mov edx,[edi+12]

                .if ( esi < E16_EXP || ( ( esi == E16_EXP && ( edx < E16_HIGH || \
                    ( edx == E16_HIGH && eax < E16_LOW ) ) ) ) )

                    ; number is < 1e16

                    mov xexp,0

                .else
                    .if ( esi < E32_EXP || ( ( esi == E32_EXP && ( edx < E32_HIGH || \
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
                    _fltscale(&flt)

                .endif
            .endif
        .endif
    .endif

    mov eax,[ebx].ndigits
    .if [ebx].flags & _ST_F
        add eax,xexp
        add eax,2 + NDIG
        .ifs [ebx].scale > 0
            add eax,[ebx].scale
        .endif
    .else
        add eax,NDIG + NDIG / 2 ; need at least this for rounding
    .endif
    .if eax > STK_BUF_SIZE-1-NDIG
        mov eax,STK_BUF_SIZE-1-NDIG
    .endif
    mov n,eax

    mov ecx,digits
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert quad into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

    lea edi,stkbuf
    mov word ptr [edi],'0'
    inc edi
    mov i,0

    .while ( n > 0 )

        sub n,NDIG

        .if ( value == 0 && value[4] == 0 )
            ;
            ; get value to subtract
            ;
            _flttoi64(&flt)
            mov value,eax
            mov value[4],edx
            _i64toflt(&tmp, edx::eax)
            _fltsub(&flt, &tmp)
            .ifs ( n > 0 )
                _fltmul(&flt, &EXQ_1E16)
            .endif
        .endif

        mov eax,value
        mov edx,value[4]
        mov ecx,NDIG
        .if ( eax || edx )

            add edi,ecx
            mov esi,ecx
            .fors ( : eax || edx || esi > 0 : esi-- )

                .if !edx
                    div radix
                    mov ecx,edx
                    xor edx,edx
                .else
                    push esi
                    push edi
                    .for ecx = 64, esi = 0, edi = 0 : ecx : ecx--
                        add eax,eax
                        adc edx,edx
                        adc esi,esi
                        adc edi,edi
                        .if edi || esi >= radix
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
            .endf
            add edi,NDIG

        .else
            or al,'0'
            rep stosb
        .endif
        add i,NDIG
        mov value,0
        mov value[4],0
    .endw

    ; get number of characters in buf

    .for ( eax = i, ; skip over leading zeros
           edx = STK_BUF_SIZE-2,
           esi = &stkbuf[1],
           ecx = xexp,
           ecx += NDIG-1 : edx && byte ptr [esi] == '0' : eax--, ecx--, edx--, esi++ )
    .endf

    mov n,eax
    mov ebx,cvt
    mov edx,[ebx].ndigits

    .if ( [ebx].flags & _ST_F )
        add ecx,[ebx].scale
        lea edx,[edx+ecx+1]
    .elseif ( [ebx].flags & _ST_E )
        .ifs ( [ebx].scale > 0 )
            inc edx
        .else
            add edx,[ebx].scale
        .endif
        inc ecx ; xexp = xexp + 1 - scale
        sub ecx,[ebx].scale
    .endif

    .ifs ( edx >= 0 ) ; round and strip trailing zeros
        .ifs edx > eax
            mov edx,eax ; nsig = n
        .endif
        mov eax,digits
        .ifs edx > eax
            mov edx,eax
        .endif
        mov maxsize,eax

        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [esi+edx] >= '5' ) || \
            ( edx == digits && byte ptr [esi+edx-1] == '9' ) )
            mov al,'9'
        .endif

        mov edi,[ebx].scale
        add edi,[ebx].ndigits
        .if ( al == '9' && edx == edi && \
            byte ptr [esi+edx] != '9' &&  byte ptr [esi+edx-1] == '9' )
            .while edi
                dec edi
                .break .if byte ptr [esi+edi] != '9'
            .endw
            .if byte ptr [esi+edi] == '9'
                 mov al,'0'
            .endif
        .endif

        lea edi,[esi+edx-1]
        xchg ecx,edx
        inc ecx
        std
        repz scasb
        cld
        xchg ecx,edx
        inc edi
        .if al == '9' ; round up
            inc byte ptr [edi]
        .endif
        sub edi,esi
        .ifs
            dec esi ; repeating 9's rounded up to 10000...
            inc edx
            inc ecx
        .endif
    .endif

    .ifs edx <= 0 || flt.flags == _ST_ISZERO

        mov edx,1    ; nsig = 1
        xor ecx,ecx  ; xexp = 0
        mov stkbuf,'0'
        mov [ebx].sign,ecx
        lea esi,stkbuf
    .endif

    mov i,0
    mov eax,[ebx].flags

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -4 && ecx < [ebx].ndigits ) \
          || eax & _ST_CVT ) ) )

        mov edi,buf
        inc ecx

        .if eax & _ST_G
            .ifs ( edx < [ebx].ndigits && !( eax & _ST_DOT ) )
                mov [ebx].ndigits,edx
            .endif
            sub [ebx].ndigits,ecx
            .ifs ( [ebx].ndigits < 0 )
                mov [ebx].ndigits,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [edi],'0'
                inc i

                .ifs ( [ebx].ndigits > 0 || eax & _ST_DOT )
                    mov byte ptr [edi+1],'.'
                    inc i
                .endif
            .endif

            mov [ebx].n1,i
            mov eax,ecx
            neg eax
            .ifs ( [ebx].ndigits < eax )
                mov ecx,[ebx].ndigits
                neg ecx
            .endif
            mov eax,ecx
            neg eax
            mov [ebx].decimal_place,eax ; position of '.'
            mov [ebx].nz1,eax
            add [ebx].ndigits,ecx
            .ifs ( [ebx].ndigits < edx )
                mov edx,[ebx].ndigits
            .endif
            mov [ebx].n2,edx
            sub edx,[ebx].ndigits
            neg edx
            mov [ebx].nz2,edx
            add edi,[ebx].n1    ; number of leading characters

            mov ecx,[ebx].nz1   ; followed by this many '0's
            lea eax,[edi+ecx]
            add eax,[ebx].n2
            add eax,[ebx].nz2
            cmp eax,endbuf
            ja  overflow
            add i,ecx
            mov al,'0'
            rep stosb
            mov ecx,[ebx].n2    ; followed by these characters
            add i,ecx
            rep movsb
            mov ecx,[ebx].nz2   ; followed by this many '0's
            add i,ecx
            rep stosb

        .elseifs ( edx < ecx ) ; zeros before '.'

            add i,edx
            mov [ebx].n1,edx
            mov eax,ecx
            sub eax,edx
            mov [ebx].nz1,eax
            mov [ebx].decimal_place,ecx
            mov ecx,edx
            rep movsb

            lea ecx,[edi+eax+2]
            cmp ecx,endbuf
            ja  overflow
            mov ecx,eax
            mov eax,'0'
            add i,ecx
            rep stosb

            mov ecx,[ebx].ndigits
            .if !( [ebx].flags & _ST_CVT )

                .ifs ( ecx > 0 || [ebx].flags & _ST_DOT )

                    mov byte ptr [edi],'.'
                    inc edi
                    inc i
                    mov [ebx].n2,1
                .endif
            .endif

            lea edx,[edi+ecx]
            cmp edx,endbuf
            ja  overflow
            mov [ebx].nz2,ecx
            add i,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [ebx].decimal_place,ecx
            add i,ecx
            sub edx,ecx
            rep movsb
            mov edi,buf
            mov ecx,[ebx].decimal_place

            .if !( [ebx].flags & _ST_CVT )
                .ifs [ebx].ndigits > 0 || [ebx].flags & _ST_DOT

                    mov eax,edi
                    add eax,i
                    mov byte ptr [eax],'.'
                    inc i
                .endif
            .elseif byte ptr [edi] == '0' ; ecvt or fcvt with 0.0
                mov [ebx].decimal_place,0
            .endif
            .ifs [ebx].ndigits < edx
                mov edx,[ebx].ndigits
            .endif

            add edi,i
            mov ecx,edx
            rep movsb
            add i,edx
            mov [ebx].n1,i
            mov eax,edx
            mov ecx,[ebx].ndigits
            add edx,ecx
            mov [ebx].nz1,edx
            sub ecx,eax
            lea eax,[edi+ecx]
            cmp eax,endbuf
            ja  overflow
            add i,ecx
            mov eax,'0'
            rep stosb

        .endif

        mov edi,buf
        add edi,i
        mov byte ptr [edi],0

    .else

        mov eax,[ebx].ndigits
        .ifs [ebx].scale <= 0
            add eax,[ebx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[ebx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        mov i,0
        .if [ebx].flags & _ST_G

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if ( edx < eax && !( [ebx].flags & _ST_DOT ) )
                mov eax,edx
            .endif
            dec eax
            .ifs eax < 0
                xor eax,eax
            .endif
        .endif

        mov [ebx].ndigits,eax
        mov xexp,ecx
        mov nsig,edx
        mov edi,buf

        .ifs ( [ebx].scale <= 0 )

            mov byte ptr [edi],'0'
            inc i
            .if ( ecx >= maxsize )
                inc xexp
            .endif
        .else

            mov eax,[ebx].scale
            .if ( eax > edx )
                mov eax,edx
            .endif

            mov n,eax
            add edi,i ; put in leading digits
            mov ecx,eax
            mov eax,esi
            rep movsb
            mov esi,eax
            mov eax,n
            add i,eax
            add esi,eax
            sub nsig,eax

            .ifs ( eax < [ebx].scale ) ; put in zeros if required

                mov ecx,[ebx].scale
                sub ecx,eax
                mov n,ecx
                add i,ecx
                mov edi,buf
                add edi,i
                mov al,'0'
                rep stosb
            .endif
        .endif

        mov ecx,i
        mov edi,buf
        mov [ebx].decimal_place,ecx
        mov eax,[ebx].ndigits

        .if !( [ebx].flags & _ST_CVT )
            .ifs ( eax > 0 || [ebx].flags & _ST_DOT )

                mov byte ptr [edi+ecx],'.'
                inc i
            .endif
        .endif

        mov ecx,[ebx].scale
        .ifs ( ecx < 0 )

            neg ecx
            mov n,ecx
            add edi,i
            mov al,'0'
            rep stosb
            mov eax,n
            add i,eax
        .endif

        mov ecx,nsig
        mov eax,[ebx].ndigits

        .ifs ( eax > 0 ) ; put in fraction digits

            .ifs eax < ecx
                mov ecx,eax
                mov nsig,eax
            .endif
            .if ecx
                mov edi,buf
                add edi,i
                add i,ecx
                rep movsb
            .endif

            mov eax,i
            mov [ebx].n1,eax
            mov ecx,[ebx].ndigits
            sub ecx,nsig
            mov [ebx].nz1,ecx
            mov edi,buf
            add edi,i
            add i,ecx
            mov eax,'0'
            rep stosb
        .endif

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
        .else
            mov byte ptr [edi+ecx],'-'
            neg eax
        .endif
        inc i

        mov xexp,eax
        mov ecx,[ebx].expwidth
        .switch ecx
        .case 0           ; width unspecified
            mov ecx,3
            .ifs eax >= 1000
                mov ecx,4
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
        mov [ebx].expwidth,ecx    ; pass back width actually used

        .if ecx >= 4
            xor esi,esi
            .if eax >= 1000
                mov ecx,1000
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
            mov edx,i
            mov [edi+edx],al
            inc i
        .endif

        .if ecx >= 3
            xor esi,esi
            mov eax,xexp
            .ifs eax >= 100
                mov ecx,100
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
            mov edx,i
            mov [edi+edx],al
            inc i
        .endif

        .if ecx >= 2
            xor esi,esi
            mov eax,xexp
            .ifs eax >= 10
                mov ecx,10
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
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
    .endif
toend:
    ret
overflow:
    mov edi,buf
    lea esi,e_space
    mov ecx,sizeof(e_space)
    rep movsb
    jmp toend

_flttostr endp

    end
