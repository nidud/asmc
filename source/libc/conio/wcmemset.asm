; WCMEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

wcmemset proc uses rdi p:PCHAR_INFO, ci:CHAR_INFO, count:int_t

    ldr eax,ci
    ldr rdi,p
    ldr ecx,count
    rep stosd
    ret

wcmemset endp

    end
