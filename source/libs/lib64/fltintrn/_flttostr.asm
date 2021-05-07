; _FLTTOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _flttostr() - Converts quad float to string
;

include fltintrn.inc
include quadmath.inc

BUFFERSIZE      equ 512     ; ANSI-specified minimum is 509
STK_BUF_SIZE    equ BUFFERSIZE
NDIG            equ 8
D_CVT_DIGITS    equ 20
LD_CVT_DIGITS   equ 23
QF_CVT_DIGITS   equ 38
E8_EXP          equ 0x4019
E8_HIGH         equ 0xBEBC2000
E8_LOW          equ 0x00000000
E16_EXP         equ 0x4034
E16_HIGH        equ 0x8E1BC9BF
E16_LOW         equ 0x04000000

    .data
    Q_1E8 real16 40197D78400000000000000000000000r

    .code

    assume rbx:ptr FLTINFO

_flttostr proc uses rsi rdi rbx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local qf     :REAL16
  local tmp    :REAL16
  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local value  :int_t
  local maxsize:int_t
  local digits :int_t
  local radix  :int_t
  local flt    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t

    mov eax,D_CVT_DIGITS
    .if r9d & _ST_LONGDOUBLE
        mov eax,LD_CVT_DIGITS
    .elseif r9d & _ST_QUADFLOAT
        mov eax,QF_CVT_DIGITS
    .endif
    mov digits,eax
    mov radix,10

    mov rbx,rdx
    xor eax,eax
    mov qword ptr tmp[0],rax
    mov qword ptr tmp[8],rax
    mov [rbx].n1,eax
    mov [rbx].nz1,eax
    mov [rbx].n2,eax
    mov [rbx].nz2,eax
    mov [rbx].decimal_place,eax

    mov value,eax
    lea rdi,qf
    mov flt.mantissa,rdi
    mov rsi,rcx
    mov ecx,7
    rep movsw
    lodsw
    bt      eax,15
    sbb     ecx,ecx
    mov     [rbx].sign,ecx
    and     eax,Q_EXPMASK   ; make number positive
    mov     word ptr qf[14],ax
    movzx   ecx,ax
    lea     rdi,qf
    xor     eax,eax

    .if ecx == Q_EXPMASK

        ; NaN or Inf

        or ax,[rdi+12]
        or eax,[rdi+8]
        or rax,[rdi]
        .ifz

            ; INFINITY

            mov eax,'fni'
            or  [rbx].flags,_ST_ISINF
        .else

            ; NaN

            mov eax,'nan'
            or  [rbx].flags,_ST_ISNAN
        .endif

        .if flags & _ST_CAPEXP

            and eax,NOT 0x202020
        .endif
        mov [r8],eax
        mov [rbx].n1,3
        .return 64
    .endif

    .if !ecx

        ; ZERO/DENORMAL

        mov [rbx].sign,eax ; force sign to +0.0
        mov xexp,eax

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

                mov eax,[rdi+6]
                mov edx,[rdi+10]
                stc
                rcr edx,1
                rcr eax,1

                .if ( esi < E8_EXP || ( esi == E8_EXP && edx < E8_HIGH ) )

                    ; number is < 1e8

                    mov xexp,0

                .else
                    .if ( esi < E16_EXP || ( ( esi == E16_EXP && ( edx < E16_HIGH || \
                        ( edx == E16_HIGH && eax < E16_LOW ) ) ) ) )

                        ; number is < 1e16

                        mov xexp,8
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

    mov eax,[rbx].ndigits
    .if [rbx].flags & _ST_F
        add eax,xexp
        add eax,2 + NDIG
        .ifs [rbx].scale > 0
            add eax,[rbx].scale
        .endif
    .else
        add eax,4 + NDIG / 2 ; need at least this for rounding
    .endif
    .if eax > STK_BUF_SIZE-1-NDIG
        mov eax,STK_BUF_SIZE-1-NDIG
    .endif
    mov n,eax

    mov ecx,digits
    .if flags & _ST_NO_TRUNC
        add ecx,ecx
    .endif
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert ld into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

    lea rdi,stkbuf
    mov word ptr [rdi],'0'
    inc rdi
    mov i,0
    lea rsi,qf
    mov bl,'0'
    mov bh,byte ptr digits
    sub bh,NDIG

    .whiles n > 0

        sub n,NDIG

        .if !value

            ; get long value to subtract

            mov cx,[rsi+14]
            mov r8d,ecx
            and ecx,0x7FFF
            .if ecx > 0x3FFF

                and r8d,0x8000
                mov edx,[rsi+10]
                sub ecx,0x3FFF
                mov eax,1
                .if ecx > 31
                    mov ecx,31
                .endif
                shld eax,edx,cl
                .if r8d
                    neg eax
                .endif
                mov value,eax
                mov eax,ecx
                neg ecx
                add ecx,32
                shr edx,cl
                shl edx,cl
                mov dword ptr tmp[10],edx
                add eax,0x3FFF
                or  eax,r8d

                mov word ptr tmp[14],ax

                __subq(rsi, &tmp)

            .elseif i && value

                mov [rsi],rax
                mov [rsi+8],rax
            .endif

            .if n

                __mulq(rsi, &Q_1E8)
            .endif
        .endif

        mov eax,value
        .if eax
            .for ( ecx = NDIG : ecx : ecx-- )
                xor edx,edx
                div radix
                add dl,'0'
                or  bl,dl
                mov [rdi+rcx-1],dl
            .endf
            add rdi,NDIG
        .else
            mov al,'0'
            mov ecx,NDIG
            rep stosb
        .endif
        add i,NDIG
        .if bl != '0'
            sub bh,NDIG
            .break .ifs
        .endif
        mov value,0
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

    .if [rbx].flags & _ST_F
        add ecx,[rbx].scale
        lea edx,[rdx+rcx+1]
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
        .if flags & _ST_NO_TRUNC
            add eax,eax
        .endif
        .ifs edx > eax
            mov edx,eax
        .endif
        mov maxsize,eax
        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [rsi+rdx] >= '5' ) || \
               ( n == edx && byte ptr [rsi+rdx-1] == '9' ) )
            mov al,'9'
        .endif

        lea rdi,[rsi+rdx-1]
        xchg ecx,edx
        inc ecx
        std
        repz scasb
        cld
        xchg ecx,edx
        inc rdi
        .if al == '9'       ; round up
            inc byte ptr [rdi]
        .endif
        sub rdi,rsi
        .ifs
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

    mov i,0
    mov eax,[rbx].flags
    mov r9,buf
    xor r8d,r8d
    mov r10d,[rbx].ndigits

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -4 && ecx < r10d ) || eax & _ST_CVT ) ) )

        mov rdi,r9
        inc ecx
        mov r11d,eax


        .if eax & _ST_G
            .ifs ( edx < r10d && !( eax & _ST_DOT ) )
                mov r10d,edx
            .endif
            sub r10d,ecx
            .ifs ( r10d < 0 )
                mov r10d,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [rdi],'0'
                inc r8d

                .ifs ( r10d > 0 || eax & _ST_DOT )
                    mov byte ptr [rdi+1],'.'
                    inc r8d
                .endif
            .endif

            mov [rbx].n1,r8d
            mov eax,ecx
            neg eax
            .ifs ( r10d < eax )
                mov ecx,r10d
                neg ecx
            .endif
            mov eax,ecx
            neg eax
            mov [rbx].decimal_place,eax
            mov [rbx].nz1,eax
            add r10d,ecx
            .ifs ( r10d < edx )
                mov edx,r10d
            .endif
            mov [rbx].n2,edx
            sub edx,r10d
            neg edx
            mov [rbx].nz2,edx
            add edi,[rbx].n1    ; number of leading characters

            mov ecx,[rbx].nz1   ; followed by this many '0's
            add r8d,ecx
            mov al,'0'
            rep stosb
            mov ecx,[rbx].n2    ; followed by these characters
            add r8d,ecx
            rep movsb
            mov ecx,[rbx].nz2   ; followed by this many '0's
            add r8d,ecx
            rep stosb

        .elseifs ( edx < ecx )  ; zeros before '.'

            add r8d,edx
            mov [rbx].n1,edx
            mov eax,ecx
            sub eax,edx
            mov [rbx].nz1,eax
            mov [rbx].decimal_place,ecx
            mov ecx,edx
            rep movsb

            mov edx,eax
            mov eax,'#'
            mov ecx,BUFFERSIZE-2
            sub ecx,r8d
            sub ecx,r10d
            .ifs edx < ecx || flags & _ST_NO_TRUNC
                mov ecx,edx
                mov eax,'0'
            .endif
            add r8d,ecx
            rep stosb

            .if !( r11d & _ST_CVT )

                .ifs ( r10d > 0 || r11d & _ST_DOT )

                    mov byte ptr [rdi],'.'
                    inc rdi
                    inc r8d
                    mov [rbx].n2,1
                .endif
            .endif

            mov ecx,BUFFERSIZE-1
            sub ecx,r8d
            .ifs r10d < ecx || flags & _ST_NO_TRUNC
                mov ecx,r10d
            .endif
            mov [rbx].nz2,ecx
            add r8d,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [rbx].decimal_place,ecx
            add r8d,ecx
            sub edx,ecx
            rep movsb
            mov rdi,r9
            mov ecx,[rbx].decimal_place

            .if !( r11d & _ST_CVT )

                .ifs ( r10d > 0 || r11d & _ST_DOT )

                    mov byte ptr [rdi+r8],'.'
                    inc r8d
                .endif

            .elseif byte ptr [rdi] == '0' ; ecvt or fcvt with 0.0

                mov [rbx].decimal_place,0
            .endif

            .ifs ( r10d < edx )

                mov edx,r10d
            .endif

            add rdi,r8
            mov ecx,edx
            rep movsb
            add r8d,edx
            mov [rbx].n1,r8d
            mov eax,edx
            mov ecx,r10d
            add edx,ecx
            mov [rbx].nz1,edx
            sub ecx,eax
            add r8d,ecx
            mov eax,'0'
            rep stosb

        .endif
        mov byte ptr [r9+r8],0
        mov [rbx].ndigits,r10d

    .else

        mov eax,[rbx].ndigits
        .ifs [rbx].scale <= 0
            add eax,[rbx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        xor r8d,r8d

        .if [rbx].flags & _ST_G

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if (edx < eax && !([rbx].flags & _ST_DOT))
                mov eax,edx
            .endif
            dec eax
            .ifs eax < 0
                xor eax,eax
            .endif
        .endif

        mov [ebx].ndigits,eax
        mov xexp,ecx
        mov r10d,edx
        mov rdi,r9
        .ifs [rbx].scale <= 0

            mov byte ptr [r9],'0'
            inc r8d

        .else

            mov eax,[rbx].scale
            .if eax > edx
                mov eax,edx
            .endif

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
                mov al,'0'
                rep stosb
            .endif
        .endif
        mov [rbx].decimal_place,r8d

        mov eax,[rbx].ndigits
        .if !( [rbx].flags & _ST_CVT )

            .ifs ( eax > 0 || [rbx].flags & _ST_DOT )

                mov byte ptr [r9+r8],'.'
                inc r8d
            .endif
        .endif

        mov ecx,[rbx].scale
        .ifs ecx < 0
            neg ecx
            lea rdi,[r9+r8]
            add r8d,ecx
            mov al,'0'
            rep stosb
        .endif
        mov ecx,r10d
        mov eax,[rbx].ndigits

        .ifs eax > 0        ; put in fraction digits

            .ifs eax < ecx
                mov ecx,eax
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
            mov ecx,[rbx].ndigits
            add r8d,ecx
            mov eax,'0'
            rep stosb
        .endif
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
            lea rax,[rsi+'0']
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
            lea rax,[rsi+'0']
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
            lea rax,[rsi+'0']
            mov [r9+r8],al
            inc r8d
         .endif

         lea rax,[rdi+'0']
         mov [r9+r8],al
         inc r8d
         mov eax,r8d
         sub eax,[rbx].n1
         mov [rbx].n2,eax
         xor eax,eax
         mov [r9+r8],al
    .endif
    ret

_flttostr endp

    end
