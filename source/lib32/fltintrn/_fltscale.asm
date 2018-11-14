; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ltype.inc
include fltintrn.inc
include crtl.inc

    .data

pow_table label DWORD
    dt 4002A000000000000000h    ; 1e1
    dt 4005C800000000000000h    ; 1e2
    dt 400C9C40000000000000h    ; 1e4
    dt 4019BEBC200000000000h    ; 1e8
    dt 40348E1BC9BF04000000h    ; 1e16
    dt 40699DC5ADA82B70B59Eh    ; 1e32
    dt 40D3C2781F49FFCFA6D5h    ; 1e64
    dt 41A893BA47C980E98CE0h    ; 1e128
    dt 4351AA7EEBFB9DF9DE8Eh    ; 1e256
    dt 46A3E319A0AEA60E91C7h    ; 1e512
    dt 4D48C976758681750C17h    ; 1e1024
    dt 5A929E8b3B5DC53D5DE5h    ; 1e2048
    dt 7525C46052028A20979Bh    ; 1e4096
    dt 7FFF8000000000000000h    ; infinity

    .code

doscale proc private uses edi ebx
    mov ebx,eax
    xor edi,edi
    .if esi >= 8192
        mov esi,8192    ; set to infinity multiplier
    .endif
    .if esi
        .repeat
            .if esi & 1
                lea edx,pow_table[edi]
                mov eax,ebx
                _FLDM()
            .endif
            add edi,10
            shr esi,1
        .untilz
    .endif
    ret
doscale endp

scale10 proc private
local factor:REAL10
    .if esi
        lea eax,factor
        mov dword ptr [eax],00000000h
        mov dword ptr [eax+4],80000000h
        mov word ptr [eax+8],3FFFh  ; 1.0
        .ifs esi < 0
            neg esi
            doscale()
            mov eax,ebx
            lea edx,factor
            _FLDD()
        .else
            doscale()
            lea edx,factor
            mov eax,ebx
            _FLDM()
        .endif
    .endif
    ret
scale10 endp

    assume edi: ptr S_STRFLT

_fltscale proc uses esi edi ebx fp:LPSTRFLT
    mov edi,fp
    mov esi,[edi].exponent
    mov ebx,[edi].mantissa
    .ifs esi > 4096
        mov esi,4096
        scale10()
        mov esi,[edi].exponent
        sub esi,4096
    .else
        .ifs esi < -4096
            mov esi,-4096
            scale10()
            mov esi,[edi].exponent
            add esi,4096
        .endif
    .endif
    scale10()
    ret
_fltscale endp

    END
