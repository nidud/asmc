; RAND_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

rand_s proc _RandomValue:ptr UINT

    rand()
    mov rcx,_RandomValue
    mov [rcx],eax
    mov eax,1
    ret

rand_s endp

    end
