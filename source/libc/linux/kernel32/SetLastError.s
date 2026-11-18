; SETLASTERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include errhandlingapi.inc

.code

SetLastError proc WINAPI dwErrCode:DWORD
    mov _doserrno,ldr(dwErrCode)
    xor eax,eax
    ret
    endp

    end
