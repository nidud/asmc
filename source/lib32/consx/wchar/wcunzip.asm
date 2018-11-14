; WCUNZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

rsunzipch proto
rsunzipat proto

    .code

wcunzip proc uses esi edi dest:PVOID, src:PVOID, wcount
    mov edi,dest
    inc edi
    mov esi,src
    mov eax,wcount
    and wcount,07FFh
    and eax,8000h
    mov ecx,wcount
    .ifnz
        rsunzipat()
    .else
        rsunzipch()
    .endif
    mov edi,dest
    mov ecx,wcount
    rsunzipch()
    ret
wcunzip endp

    END
