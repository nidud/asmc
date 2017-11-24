; _cqfcvt() - Converts quad float to string
;
include intn.inc
include alloc.inc
include ltype.inc
include string.inc

FL_SIGN         equ 0x0001  ; put plus or minus in front
FL_SIGNSP       equ 0x0002  ; put space or minus in front
FL_LEFT         equ 0x0004  ; left justify
FL_LEADZERO     equ 0x0008  ; pad with leading zeros
FL_LONG         equ 0x0010  ; long value given
FL_SHORT        equ 0x0020  ; short value given
FL_SIGNED       equ 0x0040  ; signed data given
FL_ALTERNATE    equ 0x0080  ; alternate form requested
FL_NEGATIVE     equ 0x0100  ; value is negative
FL_FORCEOCTAL   equ 0x0200  ; force leading '0' for octals
FL_LONGDOUBLE   equ 0x0400  ; long double
FL_WIDECHAR     equ 0x0800
FL_LONGLONG     equ 0x1000  ; long long or REAL16 value given
FL_I64          equ 0x8000  ; 64-bit value given
FL_CAPEXP       equ 0x10000

E8_EXP          equ 0x4019
E8_HIGH         equ 0xBEBC2000
E8_LOW          equ 0x00000000
E16_EXP         equ 0x4034
E16_HIGH        equ 0x8E1BC9BF
E16_LOW         equ 0x04000000

STK_BUF_SIZE    equ 128
NDIG            equ 8
D_CVT_DIGITS    equ 20
LD_CVT_DIGITS   equ 23
QF_CVT_DIGITS   equ 34
NO_TRUNC        equ 0x40    ; always provide ndigits in buffer

CVT_INFO        STRUC
ndigits         SINT ?      ; INPUT: number of digits
scale           SINT ?      ; INPUT: FORTRAN scale factor
flags           SINT ?      ; INPUT/OUTPUT: flags (see ldcvt_flags)
expchar         SINT ?      ; INPUT: exponent character to use
expwidth        SINT ?      ; INPUT/OUTPUT: number of exponent digits
sign            SINT ?      ; OUTPUT: 0 => +ve; otherwise -ve
decimal_place   SINT ?      ; OUTPUT: position of '.'
n1              SINT ?      ; OUTPUT: number of leading characters
nz1             SINT ?      ; OUTPUT: followed by this many '0's
n2              SINT ?      ; OUTPUT: followed by these characters
nz2             SINT ?      ; OUTPUT: followed by this many '0's
CVT_INFO        ENDS

.code

__fconv proc private uses rsi rdi rbx fp:ptr, cvt:ptr, buf:LPSTR, flags:dword

    local i      :SINT
    local n      :SINT
    local nsig   :SINT
    local xexp   :SINT
    local p      :LPSTR
    local drop   :SBYTE
    local value  :SDWORD
    local qf     :REAL16
    local tmp    :REAL16
    local tmp2   :REAL16
    local maxsize:SINT
    local digits :SINT
    local stkbuf[STK_BUF_SIZE]:SBYTE

    mov eax,flags
    mov ecx,D_CVT_DIGITS
    .if eax & FL_LONGDOUBLE
        mov ecx,LD_CVT_DIGITS
    .elseif eax & FL_LONGLONG
        mov ecx,QF_CVT_DIGITS
    .endif
    mov digits,ecx

    mov rbx,cvt
    assume rbx:ptr CVT_INFO

    mov     rsi,fp
    lea     rdi,qf
    mov     ecx,7
    rep     movsw
    lodsw
    bt      eax,15
    sbb     ecx,ecx
    mov     [rbx].sign,ecx
    and     eax,Q_EXPMASK   ; make number positive
    stosw
    movzx   ecx,ax
    xor     eax,eax
    mov     [rbx].n1,eax
    mov     [rbx].nz1,eax
    mov     [rbx].n2,eax
    mov     [rbx].nz2,eax
    mov     [rbx].decimal_place,eax
    mov     value,eax
    lea     rdi,qf

    .repeat

        .if ecx == Q_EXPMASK
            ;
            ; NaN or Inf
            ;
            or rax,[rdi]
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
                    _normalizefq(rdi, eax)

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
                        _normalizefq(rdi, eax)
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
                .if _qftol(rdi)

                    mov value,eax

                    _ltoqf(&tmp, eax)
                    _subfq(rdi, rdi, &tmp)
                .elseif i && value
                    mov [rdi],rax
                    mov [rdi+8],rax
                .endif
                .if n
                    _mulfq(rdi, rdi, &_Q_1E8)
                .endif
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

        mov r9,buf
        mov r8d,i
        ;
        ; get number of characters in buf
        ;
        .for eax=r8d, rsi=&stkbuf[1], ecx=xexp, ecx+=NDIG-1,
             : byte ptr [rsi] == '0' : eax--, ecx--, rsi++
             ; skip over leading zeros
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

        mov eax,[rbx].flags
        .ifs eax & _ST_F || (eax & _ST_G && ((ecx >= -4 && ecx < [rbx].ndigits) || eax & _ST_CVT))

            mov rdi,r9
            inc ecx
            xor r8d,r8d

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
                    inc r8d
                    .ifs [rbx].ndigits > 0 || eax & _ST_DOT
                        mov byte ptr [rdi+1],'.'
                        inc r8d
                    .endif
                .endif
                add rdi,r8
                mov [rbx].n1,r8d
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
                    add r8d,ecx
                    sub edx,ecx
                    sub [rbx].nz2,ecx
                    mov eax,'0'
                    rep stosb
                .endif
                add r8d,edx
                mov ecx,edx
                rep movsb
                mov ecx,[rbx].nz2
                add r8d,ecx
                mov eax,'0'
                rep stosb

            .elseif edx < ecx ; zeros before '.'

                add r8d,edx
                mov [rbx].n1,edx
                mov eax,ecx
                sub eax,edx
                mov [rbx].nz1,eax
                mov [rbx].decimal_place,ecx
                mov ecx,edx
                rep movsb
                add r8d,eax
                mov ecx,eax
                mov eax,'0'
                rep stosb

                .if !( [rbx].flags & _ST_CVT )

                    .if ( [rbx].ndigits > 0 || [rbx].flags & _ST_DOT )

                        mov byte ptr [r9+r8],'.'
                        inc r8d
                        mov [rbx].n2,1
                    .endif
                .endif
                mov eax,[rbx].ndigits
                mov [rbx].nz2,eax

                .if ( ecx > edx )
                    sub ecx,edx
                    add r8d,ecx
                    mov eax,'0'
                    rep stosb
                .endif

            .else                    ; enough digits before '.'
                mov [rbx].decimal_place,ecx
                add r8d,ecx
                sub edx,ecx
                rep movsb
                mov rdi,r9
                mov ecx,[rbx].decimal_place

                .if !([rbx].flags & _ST_CVT)
                    .ifs [rbx].ndigits > 0 || [rbx].flags & _ST_DOT
                        mov byte ptr [rdi+r8],'.'
                        inc r8d
                    .endif
                .elseif byte ptr [rdi] == '0' ; ecvt or fcvt with 0.0
                    mov [rbx].decimal_place,0
                .endif
                .ifs [rbx].ndigits < edx
                    mov edx,[ebx].ndigits
                .endif
                add rdi,r8
                mov ecx,edx
                rep movsb
                add r8d,edx
                mov [rbx].n1,r8d
                mov eax,edx
                mov ecx,[rbx].ndigits
                add edx,ecx
                mov [rbx].nz1,edx
                sub ecx,eax
                add r8d,ecx
                mov eax,'0'
                rep stosb
            .endif
            mov byte ptr [r9+r8],0
        .else

            mov eax,[rbx].ndigits
            .ifs [rbx].scale <= 0
                add eax,[rbx].scale   ; decrease number of digits after decimal
            .else
                sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
                inc eax
            .endif

            xor r8,r8
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
            .if !([rbx].flags & _ST_CVT)
                .ifs eax > 0 || [rbx].flags & _ST_DOT
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
                inc r8d
            .else
                mov byte ptr [r9+r8],'-'
                inc r8d
                neg edi
            .endif

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
                mov eax,esi
                add al,'0'
                mov [r9+r8],al
                inc r8d
            .endif

            .if ecx >= 3
                xor esi,esi
                .ifs edi >= 100
                    mov ecx,100
                    xor edx,edx
                    div ecx
                    mov esi,edi
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
                .ifs edi >= 10
                    mov ecx,10
                    xor edx,edx
                    div ecx
                    mov esi,edi
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
        .endif
    .until 1
    ret

__fconv endp

_qcvt proc q:ptr, buffer:LPSTR, ch_type:SINT, precision:SINT, flags:SINT
local cvt:CVT_INFO

    mov edx,flags
    mov eax,'e'
    .if edx & FL_CAPEXP
        mov eax,'E'
    .endif
    mov cvt.expchar,eax

    mov ecx,precision
    mov eax,_ST_F
    .if ch_type == 'e'
        mov eax,_ST_E
    .elseif ch_type == 'g'
        mov eax,_ST_G
    .endif

    mov cvt.flags,eax
    mov cvt.ndigits,ecx
    xor ecx,ecx
    .if eax & _ST_E
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3

    mov r8,buffer
    inc r8
    __fconv(q, &cvt, r8, flags)
    mov rax,buffer
    .if cvt.sign == -1
        mov byte ptr [rax],'-'
    .else
        inc rax
        strcpy(buffer, rax)
    .endif
    ret
_qcvt endp

_ldcvt proc ld:ptr, buffer:LPSTR, ch_type:SINT, precision:SINT, flags:SINT
local q:REAL16
    _ldtoqf(&q, ld)
    _qcvt(&q, buffer, ch_type, precision, flags)
    ret
_ldcvt endp

_dcvt proc d:ptr, buffer:LPSTR, ch_type:SINT, precision:SINT, flags:SINT
local q:REAL16
    mov rcx,d
    mov rax,[rcx]
    _dtoqf(&q, rax)
    _qcvt(&q, buffer, ch_type, precision, flags)
    ret
_dcvt endp

    end
