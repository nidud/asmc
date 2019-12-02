; CREATECONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include process.inc
include string.inc
include consx.inc
include winbase.inc

    .code

CreateConsole proc uses esi edi string:LPSTR, flag

  local cmd[1024]:byte

    lea edi,cmd
    strcpy(edi, "cmd.exe")
    .if !GetEnvironmentVariable("Comspec", edi, 1024)

        SearchPath(eax, "cmd.exe", eax, 1024, edi, eax)
    .endif

    strcat(edi, " /C ")
    lea esi,[edi+strlen(string)]

    strcat(edi, string)
    .if strchr(edi, 10)
        __mktempcmd(esi, 0)
    .endif

    mov eax,flag
    .if eax == _P_NOWAIT
        or eax,DETACHED_PROCESS
    .endif

    process(0, edi, eax)
    SetKeyState()
    ret

CreateConsole endp

    END
