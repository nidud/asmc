; _FLTROUND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .data
     current_rounding_mode rounding_mode rm_none

    .code

    assume ebx:ptr STRFLT

_fltround proc uses esi edi ebx p:ptr STRFLT

    mov ebx,p
    mov eax,[ebx]
    .if eax & 0x4000

        mov edx,[ebx+4]
        mov edi,[ebx+8]
        mov esi,[ebx+12]

        add eax,0x4000
        adc edx,0
        adc edi,0
        adc esi,0
        .ifc
            rcr esi,1
            rcr edi,1
            rcr edx,1
            rcr eax,1
            inc [ebx].mantissa.e
            .if [ebx].mantissa.e == Q_EXPMASK

                mov [ebx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
                xor edi,edi
                xor esi,esi
            .endif
        .endif
        mov [ebx],eax
        mov [ebx+4],edx
        mov [ebx+8],edi
        mov [ebx+12],esi
    .endif

if 0
    .if ( current_rounding_mode )

        .switch current_rounding_mode
        .case rm_downward
            .endc
        .case rm_tonearest
            .endc
        .case rm_towardzero
            .endc
        .case rm_upward
            .endc
        .endsw
    .endif
endif
    mov eax,p
    ret

_fltround endp

_fltgetrounding proc
    .return current_rounding_mode
_fltgetrounding endp

_fltsetrounding proc mode:rounding_mode
    mov eax,current_rounding_mode
    mov current_rounding_mode,ecx
    ret
_fltsetrounding endp

    end
