include process.inc
include string.inc
include consx.inc
include cfini.inc
include winbase.inc
include dzlib.inc

    .code

CreateConsole proc uses esi edi ebx string:string_t, flag:uint_t

  local cmd[1024]:byte

    lea edi,cmd
    mov esi,console
    and esi,CON_NTCMD

    strcat(strcpy(edi, CFGetComspec(esi)), " ")

    .if __pCommandArg

        strcat(strcat(edi, __pCommandArg), " ")
    .endif
    .if esi

        strcat(edi, "\"")
    .endif
    lea ebx,[edi+strlen(edi)]
    .if strchr(strcat(edi, string), 10)

        CreateBatch(ebx, 0, 0)
    .endif
    .if esi

        strcat(edi, "\"")
    .endif
    mov eax,flag
    .if eax == _P_NOWAIT
        or eax,DETACHED_PROCESS
    .endif
    process(0, edi, eax)
    SetKeyState()
    ret

CreateConsole endp

    end
