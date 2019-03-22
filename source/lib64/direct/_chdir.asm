; _CHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

_chdir proc directory:LPSTR

  local abspath[_MAX_PATH]:SBYTE, result:DWORD

    .repeat

        .ifd SetCurrentDirectory( rcx )

            .ifd GetCurrentDirectory( _MAX_PATH, &abspath )

                xor eax,eax
                mov ecx,DWORD PTR abspath
                .break .if ch != ':'

                mov eax,0x003A003D
                mov ah,cl
                .if cl >= 'a' && cl <= 'z'
                    sub ah,'a' - 'A'
                .endif
                mov result,eax
                .ifd SetEnvironmentVariable( &result, &abspath )

                    xor eax,eax
                    .break
                .endif
            .endif
       .endif
        _dosmaperr(GetLastError())

    .until 1
    ret

_chdir endp

    end
