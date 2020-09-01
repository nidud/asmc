; _WCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

    .code

_wchdir proc directory:LPWSTR

local root[2]
local abspath[_MAX_PATH]:word

    .repeat
        .repeat

            .if SetCurrentDirectoryW(directory)

                .if GetCurrentDirectoryW(_MAX_PATH, &abspath)

                    mov cl,byte ptr abspath
                    mov ch,byte ptr abspath[2]
                    .if ch == ':'
                        mov root[4],0x0000003A
                        movzx eax,cl
                        .if al >= 'a' && al <= 'z'
                            sub al,'a' - 'A'
                        .endif
                        shl eax,16
                        mov al,0x3D
                        mov root,eax
                        .break .if !SetEnvironmentVariable(&root, &abspath)
                    .endif
                    xor eax,eax
                    .break(1)
                .endif
            .endif
        .until 1
        osmaperr()
    .until 1
    ret

_wchdir endp

    END
