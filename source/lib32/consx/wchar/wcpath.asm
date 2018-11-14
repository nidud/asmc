; WCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include string.inc

    .code

wcpath proc uses esi edi b:PVOID, l:dword, p:PVOID
    __wcpath(b, l, p)
    .if ecx
        mov esi,edx
        mov edi,eax
        .repeat
            movsb
            inc edi
        .untilcxz
    .endif
    ret
wcpath endp

    END
