; __DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
    DoserrorNoMem ulong_t ERROR_NOT_ENOUGH_MEMORY

    .code

    option win64:rsp noauto

__doserrno proc

    lea rax,DoserrorNoMem
    ret

__doserrno endp

_set_doserrno proc value:ulong_t

    mov DoserrorNoMem,ecx
    ret

_set_doserrno endp

_get_doserrno proc pValue:ptr ulong_t

    mov eax,DoserrorNoMem
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_doserrno endp

    end
