; GETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc

    .code

getfattr proc uses ecx edx lpFilename:LPSTR

    .if GetFileAttributesA(lpFilename) == -1

        .if GetFileAttributesW(__allocwpath(lpFilename)) == -1

            osmaperr()
        .endif
    .endif
    mov esp,ebp
    ret

getfattr endp

    END

