; _TFREOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include share.inc
include tchar.inc

    .code

_tfreopen proc file:LPTSTR, mode:LPTSTR, fp:LPFILE

    fclose(fp)
    _topenfile(file, mode, SH_DENYNO, fp)
    ret

_tfreopen endp

    end
