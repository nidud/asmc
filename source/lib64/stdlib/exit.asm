; EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc
include stdlib.inc
include winbase.inc

_EXIT	segment para flat PUBLIC 'EXIT'
ExitStart LABEL BYTE
_EXIT	ENDS
_EEND	segment para flat PUBLIC 'EXIT'
ExitEnd LABEL BYTE
_EEND	ENDS

.code

exit proc erlevel:int_t
    lea rcx,ExitStart
    lea rdx,ExitEnd
    __initialize(rcx, rdx)
    ExitProcess(erlevel)
exit endp

    end
