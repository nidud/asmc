; DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
ifndef _WIN64
    _doserrno label errno_t
endif
    DoserrorNoMem errno_t ERROR_NOT_ENOUGH_MEMORY

    .code

__doserrno proc

    lea rax,DoserrorNoMem
    ret

__doserrno endp

_set_doserrno proc value:uint_t

    ldr ecx,value
    mov DoserrorNoMem,ecx
    ret

_set_doserrno endp

_get_doserrno proc pValue:ptr uint_t

    ldr rcx,pValue
    mov eax,DoserrorNoMem
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_doserrno endp

    end
