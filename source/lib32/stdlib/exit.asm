; EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc
include stdlib.inc
include winbase.inc

_EXIT   SEGMENT PARA flat PUBLIC 'EXIT'
_EXIT   ENDS
_EEND   SEGMENT PARA flat PUBLIC 'EXIT'
_EEND   ENDS

    .code

exit proc erlevel:SIZE_T
    mov edx,offset _EXIT
    mov eax,offset _EEND
    __initialize(edx, eax)
    ExitProcess(erlevel)
exit endp

    END
