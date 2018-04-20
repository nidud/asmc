include tchar.inc
include iconfig.inc

    .code

    assume rcx:ptr IConfig
    assume rbx:ptr IConfig

main proc

    mov rbx, IConfig::IConfig( NULL )

    [rbx].Create( "Version" )
    [rcx].Create( "Base=%d.%d", 1, 0 )
    [rbx].Create( "Product" )
    [rcx].Create( "Source=AsmcOOP" )
    [rbx].Create( "URL" )
    [rcx].Create( "UpdateURL=http://masm32.com/board/index.php?topic=7000.0" )
    [rbx].Find  ( "Version" )
    [rcx].Create( "Package=%d.%d", 1, 1 )
    [rbx].Write ( "test.ini" )
    [rbx].Release()

    mov rbx, IConfig::IConfig( NULL )

    [rbx].Read  ( "test.ini" )
    [rbx].Write ( "test.ini" )
    [rbx].Release()

    xor eax,eax
    ret

main endp

    end _tstart
