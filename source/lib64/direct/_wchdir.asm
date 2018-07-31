include direct.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

_wchdir proc directory:LPWSTR

  local abspath[_MAX_PATH]:wchar_t, result[4]:wchar_t

    .repeat

        .ifd SetCurrentDirectoryW( rcx )

            .ifd GetCurrentDirectoryW( _MAX_PATH, &abspath )

                xor eax,eax
                mov cx,abspath[2]
                .break .if cx != ':'

                mov qword ptr result,rax
                mov result[4],cx
                mov result[0],'='
                mov cx,abspath
                .if cl >= 'a' && cl <= 'z'
                    sub cl,'a' - 'A'
                .endif
                mov result[2],cx
                .ifd SetEnvironmentVariableW( &result, &abspath )

                    xor eax,eax
                    .break
                .endif
            .endif
        .endif
        osmaperr()
    .until 1
    ret

_wchdir endp

    end
