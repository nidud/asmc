; _FLTROUND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .data
     current_rounding_mode rounding_mode rm_none

    .code

    assume rcx:ptr STRFLT

_fltround proc fp:ptr STRFLT

    mov rax,[rcx].mantissa.l
    .if eax & 0x4000

        mov rdx,[rcx].mantissa.h
        add rax,0x4000
        adc rdx,0
        .ifc
            rcr rdx,1
            rcr rax,1
            inc [rcx].mantissa.e
            .if [rcx].mantissa.e == Q_EXPMASK

                mov [rcx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
            .endif
        .endif
        mov [rcx].mantissa.l,rax
        mov [rcx].mantissa.h,rdx
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
        .endsw
    .endif
endif
    .return rcx

_fltround endp

    option win64:rsp noauto

_fltgetrounding proc
    .return current_rounding_mode
_fltgetrounding endp

_fltsetrounding proc mode:rounding_mode
    mov eax,current_rounding_mode
    mov current_rounding_mode,ecx
    ret
_fltsetrounding endp

    end
