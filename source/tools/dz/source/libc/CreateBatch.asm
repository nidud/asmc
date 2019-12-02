include string.inc
include io.inc
include direct.inc
include stdlib.inc
include strlib.inc
include dzlib.inc

extern envtemp:string_t

    .code

CreateBatch proc uses ebx cmd:string_t, CallBatch:int_t, UpdateEnviron:int_t

  local batch[_MAX_PATH]:char_t, argv0[_MAX_PATH]:char_t

    strfcat( &batch, envtemp, "dzcmd.bat" )

    .return .if osopen( eax, 0, M_WRONLY, A_CREATETRUNC ) == -1

    mov ebx,eax

    oswrite( ebx, "@echo off\r\n", 11 )

    .if CallBatch

        oswrite( ebx, "call ", 5 )
    .endif

    oswrite( ebx, cmd, strlen( cmd ) )
    oswrite( ebx, "\r\n", 2 )

    .if UpdateEnviron

        mov ecx,__argv
        strcpy( &argv0, [ecx] )
        strcat( strcat( strcat( eax, " /E:" ), envtemp ), "\\dzcmd.env" )

        oswrite( ebx, &argv0, strlen( eax ) )
        oswrite( ebx, "\r\n", 2 )
    .endif

    _close( ebx )
    strcpy( cmd, &batch )
    ret

CreateBatch ENDP

    END
