; SCROLL_DELAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include time.inc

    .code

scroll_delay proc
    tupdate()
    Sleep(2)
    ret
scroll_delay endp

    end
