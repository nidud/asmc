; _GET_FMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fcntl.inc

    .code

_get_fmode proc p:ptr int_t

    ldr rcx,p
    mov eax,_fmode
    mov [rcx],eax
    xor eax,eax
    ret

_get_fmode endp


_set_fmode proc mode:int_t

    ldr ecx,mode
    mov _fmode,ecx
    xor eax,eax
    ret

_set_fmode endp

    end
