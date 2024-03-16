; _TWSNEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc
include malloc.inc

.code

_wsnew proc

    .if ( malloc(WSUB+WMAXPATH*TCHAR) )

        mov [rax].WSUB.flags,_W_MALLOC
        xor ecx,ecx
        mov [rax].WSUB.count,ecx
        mov [rax].WSUB.mask,rcx
        mov [rax].WSUB.fcb,rcx
        lea rcx,[rax+WSUB]
        mov [rax].WSUB.path,rcx
    .endif
    ret

_wsnew endp

    end
