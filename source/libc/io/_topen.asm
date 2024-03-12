; _TOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include share.inc
include tchar.inc

if defined(__UNIX__) and defined(_WIN64)
option win64:noauto ; skip the vararg stack
endif

.code

_topen proc path:LPTSTR, oflag:SINT, args:VARARG
if defined(__UNIX__) and defined(_WIN64)
    _tsopen( rdi, esi, SH_DENYNO, edx )
elseifdef _WIN64
    _tsopen( rcx, edx, SH_DENYNO, r8d )
else
    _tsopen( path, oflag, SH_DENYNO, args )
endif
    ret

_topen endp

    end
