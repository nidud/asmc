; WCPUTXG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wcputxg proc uses ecx
    inc ebx
    .repeat
        and [ebx],ah
        or  [ebx],al
        add ebx,2
    .untilcxz
    ret
wcputxg endp

    END
