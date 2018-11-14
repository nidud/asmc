; WCMEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wcmemset proc uses edi string:PVOID, val, count
    mov ecx,count
    mov edi,string
    mov eax,val
    rep stosw
    ret
wcmemset endp

    END
