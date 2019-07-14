; _WCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

_wchdir proc frame directory:LPWSTR

  local abspath[_MAX_PATH]:wchar_t, result[4]:wchar_t

    .ifd SetCurrentDirectoryW( rcx )

        .ifd GetCurrentDirectoryW( _MAX_PATH, &abspath )

            xor eax,eax
            mov cx,abspath[2]
            .return .if cx != ':'

            mov qword ptr result,rax
            mov result[4],cx
            mov result[0],'='
            mov cx,abspath
            .if cl >= 'a' && cl <= 'z'
                sub cl,'a' - 'A'
            .endif
            mov result[2],cx
            .return 0 .ifd SetEnvironmentVariableW( &result, &abspath )
        .endif
    .endif
    _dosmaperr(GetLastError())
    ret

_wchdir endp

    end
