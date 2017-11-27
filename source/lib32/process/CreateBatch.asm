include string.inc
include strlib.inc
include io.inc
include direct.inc
include stdlib.inc

    .code

CreateBatch proc uses ebx cmd, CallBatch, UpdateEnviron
local batch[_MAX_PATH]:sbyte, argv0[_MAX_PATH]:sbyte, temp:ptr byte

    mov temp,@CStr(".")
    .if getenv("TEMP")
        mov temp,eax
    .endif
    .if _osopenA(strfcat(addr batch, temp, "dzcmd.bat"), M_WRONLY, 0, 0, A_CREATETRUNC, 0 ) != -1
        mov ebx,eax
        oswrite(ebx, "@echo off", 11)
        .if CallBatch
            oswrite(ebx, "call ", 5)
        .endif
        oswrite(ebx, cmd, strlen(cmd))
        oswrite(ebx, "\r\n", 2)
        _close(ebx)
        strcpy(cmd, addr batch)
    .endif
    ret

CreateBatch endp

    END
