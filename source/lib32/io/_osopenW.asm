; _OSOPENW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

_osopenW proc uses ebx lpFileName:LPWSTR, dwAccess:SIZE_T, dwShareMode:SIZE_T,
    lpSecurity:PVOID, dwCreation:SIZE_T, dwAttributes:SIZE_T

    xor eax,eax
    .repeat

        .while _osfile[eax] & FH_OPEN

            inc eax
            .if eax == _nfile

                xor eax,eax
                mov _doserrno,eax ; no OS error
                mov errno,EBADF
                dec eax
                .break(1)
            .endif
        .endw
        mov ebx,eax

        .if CreateFileW(lpFileName, dwAccess, dwShareMode, lpSecurity,
                dwCreation, dwAttributes, 0) == -1

            osmaperr()
            .break
        .endif

        mov _osfhnd[ebx*4],eax
        or  _osfile[ebx],FH_OPEN
        mov eax,ebx

    .until 1
    ret

_osopenW endp

    END
