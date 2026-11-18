; GETLASTERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include errhandlingapi.inc

.code

 GetLastError proc WINAPI
    mov eax,_doserrno
    ret
    endp

    end
