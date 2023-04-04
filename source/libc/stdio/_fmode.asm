; _FMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fcntl.inc

    .data
    _fmode int_t 0

    .code

_get_fmode proc p:ptr int_t

ifndef _WIN64
    mov ecx,p
endif
    mov eax,_fmode
    mov [rcx],eax
    xor eax,eax
    ret

_get_fmode endp


_set_fmode proc mode:int_t

ifndef _WIN64
    mov ecx,mode
endif
    mov _fmode,ecx
    xor eax,eax
    ret

_set_fmode endp

    end
