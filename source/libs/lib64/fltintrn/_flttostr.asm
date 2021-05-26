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
     Q_1E16     real16 1.E16
     e_space    db "#not enough space",0

    .code

    assume rbx:ptr FLTINFO

_flttostr proc uses rsi rdi rbx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local qf     :REAL16
  local nsig   :int_t
  local xexp   :int_t
  local maxsize:int_t
  local digits :int_t
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    mov rbx,cvt
    mov eax,[rbx].bufsize
    add rax,buf
    dec rax
    mov endbuf,rax
    mov eax,D_CVT_DIGITS
    .if r9d & _ST_LONGDOUBLE
        mov eax,LD_CVT_DIGITS
    .elseif r9d & _ST_QUADFLOAT
        mov eax,QF_CVT_DIGITS
    .endif
    mov digits,eax

    mov rbx,rdx
    xor eax,eax
    mov [rbx].n1,eax
    mov [rbx].nz1,eax
    mov [rbx].n2,eax
    mov [rbx].nz2,eax
    mov [rbx].decimal_place,eax
    lea rdi,qf
    mov rsi,rcx
    mov ecx,7
    rep movsw
    lodsw
    bt      eax,15
    sbb     ecx,ecx
    mov     [rbx].sign,ecx
    and     eax,Q_EXPMASK   ; make number positive
    mov     word ptr qf[14],ax
    mov     ecx,eax
    lea     rdi,qf
    xor     eax,eax
    movaps  xmm0,[rdi]

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
                fltscale(xmm0, eax)

            .else

                mov eax,[rdi+6]
                mov edx,[rdi+10]
                stc
                rcr edx,1
                rcr eax,1

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
                    fltscale(xmm0, eax)
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
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert quad into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

    lea rdi,stkbuf
    mov word ptr [rdi],'0'
    inc rdi
    xor esi,esi
    mov i,esi
    movaps xmm3,xmm0

    .while ( n > 0 )

        sub n,NDIG

        .if ( rsi == 0 )

            ; get value to subtract

            mov rsi,cvtq_i64(xmm3)
            .ifs ( n > 0 )
                subq(xmm3, cvti64_q(rsi))
                mulq(xmm0, Q_1E16)
                movaps xmm3,xmm0
            .endif
        .endif

        mov ecx,NDIG
        .if rsi
            .for ( rax = rsi, r8d = 10 : ecx : ecx-- )
                xor edx,edx
                div r8
                add dl,'0'
                mov [rdi+rcx-1],dl
            .endf
            add rdi,NDIG
        .else
            mov al,'0'
            rep stosb
        .endif
        add i,NDIG
        xor esi,esi
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
        .ifs edx > eax
            mov edx,eax     ; nsig = n
        .endif
        mov eax,digits
        .ifs edx > eax
            mov edx,eax
        .endif
        mov maxsize,eax
        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [rsi+rdx] >= '5' ) || \
            ( edx == digits && byte ptr [rsi+rdx-1] == '9' ) )
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
            mov eax,[rbx].n2
            add eax,[rbx].nz2
            add eax,ecx
            lea rax,[rdi+rax]
            cmp rax,endbuf
            ja  overflow

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

            lea rcx,[rdi+rax+2]
            cmp rcx,endbuf
            ja  overflow
            mov ecx,eax
            mov eax,'0'
            add r8d,ecx
            rep stosb

            mov ecx,r10d
            .if !( r11d & _ST_CVT )

                .ifs ( ecx > 0 || r11d & _ST_DOT )

                    mov byte ptr [rdi],'.'
                    inc rdi
                    inc r8d
                    mov [rbx].n2,1
                .endif
            .endif

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
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
            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
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

            .if ( edx < eax && !( [rbx].flags & _ST_DOT) )
                mov eax,edx
            .endif
            dec eax
            .ifs eax < 0
                xor eax,eax
            .endif
        .endif

        mov [rbx].ndigits,eax
        mov xexp,ecx
        mov r10d,edx
        mov rdi,r9

        .ifs [rbx].scale <= 0

            mov byte ptr [r9],'0'
            inc r8d
            .if ecx >= maxsize
                inc xexp
            .endif

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
         mov eax,edi

         mov ecx,[rbx].expwidth
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
            lea eax,[rsi+'0']
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
