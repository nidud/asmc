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

_fltround proc __ccall fp:ptr STRFLT

ifdef _WIN64
    mov rax,[rcx].mantissa.l
else
    mov ecx,fp
    mov eax,dword ptr [ecx].mantissa.l[0]
endif

    .if ( eax & 0x4000)

ifdef _WIN64
        mov rdx,[rcx].mantissa.h
else
        push esi
        push edi

        mov edx,dword ptr [ecx].mantissa.l[4]
        mov edi,dword ptr [ecx].mantissa.h[0]
        mov esi,dword ptr [ecx].mantissa.h[4]
endif
        add rax,0x4000
        adc rdx,0
ifndef _WIN64
        adc edi,0
        adc esi,0
endif
        .ifc

ifndef _WIN64
            rcr esi,1
            rcr edi,1
endif
            rcr rdx,1
            rcr rax,1
            inc [rcx].mantissa.e

            .if ( [rcx].mantissa.e == Q_EXPMASK )

                mov [rcx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
ifndef _WIN64
                xor edi,edi
                xor esi,esi
endif
            .endif
        .endif
ifdef _WIN64
        mov [rcx].mantissa.l,rax
        mov [rcx].mantissa.h,rdx
else
        mov dword ptr [ecx].mantissa.l[0],eax
        mov dword ptr [ecx].mantissa.l[4],edx
        mov dword ptr [ecx].mantissa.h[0],edi
        mov dword ptr [ecx].mantissa.h[4],esi
        pop edi
        pop esi
endif
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


_fltgetrounding proc __ccall
    .return current_rounding_mode
_fltgetrounding endp


_fltsetrounding proc __ccall mode:rounding_mode
ifndef _WIN64
    mov ecx,mode
endif
    mov eax,current_rounding_mode
    mov current_rounding_mode,ecx
    ret
_fltsetrounding endp

    end
