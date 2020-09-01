; _WGETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc

.code

_wgetfattr proc uses ecx edx lpFilename:LPWSTR

    .if GetFileAttributesW(lpFilename) == -1

        osmaperr()
    .endif
    ret

_wgetfattr endp

    end

