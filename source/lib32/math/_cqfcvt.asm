; _cqfcvt() - Converts quad float to string
;
include intn.inc
include malloc.inc
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

__fconv proc private uses esi edi ebx fp:ptr, cvt:ptr, buf:LPSTR, flags:dword

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

    mov ebx,cvt
    assume ebx:ptr CVT_INFO

    mov     esi,fp
    lea     edi,qf
    mov     ecx,7
    rep     movsw
    lodsw
    bt      eax,15
    sbb     ecx,ecx
    mov     [ebx].sign,ecx
    and     eax,Q_EXPMASK   ; make number positive
    stosw
    movzx   ecx,ax
    xor     eax,eax
    mov     [ebx].n1,eax
    mov     [ebx].nz1,eax
    mov     [ebx].n2,eax
    mov     [ebx].nz2,eax
    mov     [ebx].decimal_place,eax
    mov     value,eax
    lea     edi,qf

    .repeat

        .if ecx == Q_EXPMASK
            ;
            ; NaN or Inf
            ;
            or eax,[edi]
            or eax,[edi+4]
            or eax,[edi+8]
            or ax,[edi+12]
            .ifz
                ;
                ; INFINITY
                ;
                mov eax,'fni'
                or  [ebx].flags,_ST_ISINF
            .else
                ;
                ; NaN
                ;
                mov eax,'nan'
                or  [ebx].flags,_ST_ISNAN
            .endif
            .if [ebx].flags & _ST_CAPEXP
                and eax,NOT 0x202020
            .endif
            mov edx,buf
            mov [edx],eax
            mov [ebx].n1,3

            .break
        .endif

        .if !ecx
            ;
            ; ZERO/DENORMAL
            ;
            mov [ebx].sign,eax ; force sign to +0.0
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
                    _normalizefq(edi, eax)

                .else

                    mov eax,[edi+6]
                    mov edx,[edi+10]
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
                        _normalizefq(edi, eax)
                    .endif
                .endif
            .endif
        .endif

        .if [ebx].flags & _ST_F
            mov eax,[ebx].ndigits
            add eax,xexp
            add eax,2 + NDIG
            .ifs [ebx].scale > 0
                add eax,[ebx].scale
            .endif
        .else
            mov eax,[ebx].ndigits
            add eax,4 + NDIG / 2 ; need at least this for rounding
        .endif

        mov ecx,digits
        .if [ebx].flags & NO_TRUNC
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
        lea esi,stkbuf
        mov word ptr [esi],'0'
        inc esi
        mov i,0

        .whiles n > 0

            sub n,NDIG

            .if !value
                ;
                ; get long value to subtract
                ;
                .if _qftol(edi)

                    mov value,eax

                    _ltoqf(&tmp, eax)
                    _subfq(edi, edi, &tmp)
                .elseif i && value
                    mov [edi],eax
                    mov [edi+4],eax
                    mov [edi+8],eax
                    mov [edi+12],eax
                .endif
                .if n
                    _mulfq(edi, edi, &_Q_1E8)
                .endif
            .endif

            .for ( ecx = NDIG, eax = value, ebx = 10: ecx: ecx-- )

                xor edx,edx
                div ebx
                add dl,'0'
                mov [esi+ecx-1],dl
            .endf
            add esi,NDIG

            add i,8
            mov value,0
        .endw
        ;
        ; get number of characters in buf
        ;
        .for eax=i, esi=&stkbuf[1], ecx=xexp, ecx+=NDIG-1,
             : byte ptr [esi] == '0' : eax--, ecx--, esi++
             ; skip over leading zeros
        .endf

        mov ebx,cvt
        mov n,eax
        mov edx,[ebx].ndigits

        .if [ebx].flags & _ST_F
            add ecx,[ebx].scale
            add edx,ecx
            inc edx
        .elseif [ebx].flags & _ST_E
            .ifs [ebx].scale > 0
                inc edx
            .else
                add edx,[ebx].scale
            .endif
            inc ecx             ; xexp = xexp + 1 - scale
            sub ecx,[ebx].scale
        .endif

        .ifs edx >= 0           ; round and strip trailing zeros

            .ifs edx > eax
                mov edx,eax     ; nsig = n
            .endif

            mov eax,digits
            .if [ebx].flags & NO_TRUNC
                shl eax,1
            .endif
            .if edx > eax
                mov edx,eax
            .endif
            mov maxsize,eax

            mov eax,'0'
            .if n > edx && byte ptr [esi+edx] >= '5' || \
                n == edx && byte ptr [esi+edx-1] == '9'
                mov al,'9'
            .endif
            lea edi,[esi+edx-1]
            .while [edi] == al
                dec edx
                dec edi
            .endw
            .if al == '9'       ; round up
                inc byte ptr [edi]
            .endif
            sub edi,esi
            .ifs edi < 0
                dec esi         ; repeating 9's rounded up to 10000...
                inc edx
                inc ecx
            .endif
        .endif

        .ifs edx <= 0
            mov edx,1           ; nsig = 1
            xor ecx,ecx         ; xexp = 0
            mov stkbuf,'0'
            mov [ebx].sign,ecx
            lea esi,stkbuf
        .endif

        mov i,0

        mov eax,[ebx].flags
        .ifs eax & _ST_F || (eax & _ST_G && ((ecx >= -4 && ecx < [ebx].ndigits) || eax & _ST_CVT))

            mov edi,buf
            inc ecx
            .if eax & _ST_G
                .if edx < [ebx].ndigits && !(eax & _ST_DOT)
                    mov [ebx].ndigits,edx
                .endif
                sub [ebx].ndigits,ecx
                .ifs [ebx].ndigits < 0
                    mov [ebx].ndigits,0
                .endif
            .endif

            .ifs ecx <= 0 ; digits only to right of '.'

                .if !( eax & _ST_CVT )
                    mov byte ptr [edi],'0'
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
                mov eax,ecx
                neg eax
                .if [ebx].ndigits < eax
                    mov ecx,[ebx].ndigits
                    neg ecx
                .endif
                mov [ebx].decimal_place,ecx
                mov [ebx].nz1,eax
                add [ebx].ndigits,eax
                .ifs [ebx].ndigits < edx
                    mov edx,[ebx].ndigits
                .endif
                mov ecx,eax
                mov [ebx].n2,edx
                mov eax,[ebx].ndigits
                add edx,ecx
                sub eax,edx
                mov [ebx].nz2,eax
                mov eax,buf
                .if word ptr [eax] == '.0'
                    add i,ecx
                    sub edx,ecx
                    sub [ebx].nz2,ecx
                    mov eax,'0'
                    rep stosb
                .endif
                add i,edx
                mov ecx,edx
                rep movsb
                mov ecx,[ebx].nz2
                add i,ecx
                mov eax,'0'
                rep stosb

            .elseif edx < ecx ; zeros before '.'

                add i,edx
                mov [ebx].n1,edx
                mov eax,ecx
                sub eax,edx
                mov [ebx].nz1,eax
                mov [ebx].decimal_place,ecx
                mov ecx,edx
                rep movsb
                add i,eax
                mov ecx,eax
                mov eax,'0'
                rep stosb

                .if !( [ebx].flags & _ST_CVT )

                    .if ( [ebx].ndigits > 0 || [ebx].flags & _ST_DOT )

                        mov al,'.'
                        stosb
                        inc i
                        mov [ebx].n2,1
                    .endif
                .endif
                mov ecx,[ebx].ndigits
                mov [ebx].nz2,ecx

                .if ( ecx > edx )
                    sub ecx,edx
                    add i,ecx
                    mov eax,'0'
                    rep stosb
                .endif
            .else                    ; enough digits before '.'

                mov [ebx].decimal_place,ecx
                add i,ecx
                sub edx,ecx
                rep movsb
                mov edi,buf
                mov ecx,[ebx].decimal_place

                .if !([ebx].flags & _ST_CVT)
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
                mov eax,i
                mov [ebx].n1,eax
                mov eax,edx
                mov ecx,[ebx].ndigits
                add edx,ecx
                mov [ebx].nz1,edx
                sub ecx,eax
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
                ;
                ; fixup for 'G'
                ; for 'G' format, ndigits is the number of significant digits
                ; cvt->scale should be 1 indicating 1 digit before decimal place
                ; so decrement ndigits to get number of digits after decimal place
                ;
                .if (edx < eax && !([ebx].flags & _ST_DOT))
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

            .ifs [ebx].scale <= 0

                mov byte ptr [edi],'0'
                inc i

            .else

                mov eax,[ebx].scale
                .if eax > edx
                    mov eax,edx
                .endif
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
                    mov al,'0'
                    rep stosb
                .endif
            .endif

            mov edi,buf
            mov ecx,i
            mov [ebx].decimal_place,ecx

            mov eax,[ebx].ndigits
            .if !([ebx].flags & _ST_CVT)
                .ifs eax > 0 || [ebx].flags & _ST_DOT
                    mov byte ptr [edi+ecx],'.'
                    inc i
                .endif
            .endif

            mov ecx,[ebx].scale
            .ifs ecx < 0
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

            .ifs eax > 0        ; put in fraction digits

                .ifs eax < ecx
                    mov ecx,eax
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
                inc i
            .else
                mov byte ptr [edi+ecx],'-'
                inc i
                neg eax
            .endif
            mov xexp,eax

            mov ecx,[ebx].expwidth
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
            mov [ebx].expwidth,ecx    ; pass back width actually used

            .if ecx >= 4
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
    ;or  eax,NO_TRUNC
    mov cvt.flags,eax
    mov cvt.ndigits,ecx
    xor ecx,ecx
    .if eax & _ST_E
        inc ecx
    .endif
    mov cvt.scale,ecx
    mov cvt.expwidth,3

    mov ecx,buffer
    inc ecx
    __fconv(q, &cvt, ecx, flags)
    mov eax,buffer
    .if cvt.sign == -1
        mov byte ptr [eax],'-'
    .else
        inc eax
        strcpy(buffer, eax)
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
    mov ecx,d
    mov eax,[ecx]
    mov edx,[ecx+4]
    _dtoqf(&q, edx::eax)
    _qcvt(&q, buffer, ch_type, precision, flags)
    ret
_dcvt endp

    end
