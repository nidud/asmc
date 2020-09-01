; _CHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include stdlib.inc
include winbase.inc

    .code

_chdir proc directory:LPSTR

  local root
  local abspath[_MAX_PATH]:byte

    .repeat
        .repeat
            .if SetCurrentDirectory(directory)

                .if GetCurrentDirectory(_MAX_PATH, &abspath)

                    mov ecx,dword ptr abspath
                    .if ch == ':'

                        mov eax,0x003A003D
                        mov ah,cl
                        .if ah >= 'a' && ah <= 'z'
                            sub ah,'a' - 'A'
                        .endif
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

_chdir endp

    END
