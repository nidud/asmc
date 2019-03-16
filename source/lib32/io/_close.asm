; _CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

close proc handle:SINT
close endp

_close proc handle:SINT

    mov eax,handle
    .if eax < 3 || eax >= _nfile || !(_osfile[eax] & FH_OPEN)

        mov errno,EBADF
        mov _doserrno,0
        xor eax,eax
    .else

        mov _osfile[eax],0
        mov eax,_osfhnd[eax*4]
        .if !CloseHandle(eax)

            osmaperr()
        .else
            xor eax,eax
        .endif
    .endif
    ret

_close endp

    end
