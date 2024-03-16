; _WSFLAG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc

.code

_wsflag proc wp:PWSUB, flag:UINT

    ldr rcx,wp
    ldr edx,flag

    mov eax,[rcx].WSUB.flags
    and eax,_W_MALLOC
    or  eax,edx
    mov [rcx].WSUB.flags,eax
    ret

_wsflag endp

    end
