; FREXP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; double frexp(double x, int *exp);
;
include math.inc

.data
 scale real8 04350000000000000r ; 2^54

.code

frexp proc x:double, y:ptr int_t

    ldr rdx,y

    mov ecx,dword ptr x[4]
    mov eax,ecx
    shr ecx,20
    and ecx,0x07FF
    and eax,0x000FFFFF
    or  eax,dword ptr x

    ; Zero, infinity, and NaN

    .if ( ( ecx == 0 && eax == 0 ) || ecx == 0x07FF )

        mov dword ptr [rdx],0

    .elseif ( ecx )

        ; Normalized value

        sub ecx,1022
        mov [rdx],ecx

        mov eax,dword ptr x[4]
        and eax,0xBFEFFFFF
        or  eax,0x3FE00000
        mov dword ptr x[4],eax

    .else

        ; Subnormal value

ifdef _WIN64
        mulsd xmm0,scale
        movsd x,xmm0
else
        fld x
        fld scale
        fmulp
        fstp x
endif
        mov ecx,dword ptr x[4]
        mov eax,ecx
        shr ecx,20
        and ecx,0x07FF
        sub ecx,1076
        mov [rdx],ecx
        and eax,0xBFEFFFFF
        or  eax,0x3FE00000
        mov dword ptr x[4],eax
    .endif
ifdef _WIN64
    movsd xmm0,x
else
    fld x
endif
    ret
    endp

    end
