include wsub.inc
include string.inc
include winbase.inc

    .code

wschdrv proc wsub:ptr S_WSUB, drive

local lpFileName: dword,        ; name of file to find path for
      lpBuffer[512]:  sbyte,    ; path buffer
      lpFilePart: dword         ; filename in path

    mov eax,drive
    add eax,'.:@'
    mov lpFileName,eax

    .if GetFullPathName(
        &lpFileName,
        512,
        &lpBuffer,
        &lpFilePart)

        mov edx,wsub
        and [edx].S_WSUB.ws_flag,not (_W_ARCHIVE or _W_ROOTDIR)
        strcpy([edx].S_WSUB.ws_path, &lpBuffer)
        wssetflag(wsub)
    .endif
    ret

wschdrv endp

    END
