include iconfig.inc

    .code

    assume rbx:ptr IConfig ; base
    assume rdi:ptr IConfig ; return from Create/Find

main proc uses rbx

    mov rbx, IConfig::IConfig( NULL )

    [rbx].Create( "Version" )
    [rdi].Create( "Base=%d.%d", 2, 28 )
    [rbx].Create( "Product" )
    [rdi].Create( "Source=AsmcOOP" )
    [rbx].Create( "URL" )
    [rdi].Create( "UpdateURL=https://github.com/nidud/asmc" )
    [rbx].Find  ( "Version" )
    [rdi].Create( "Package=%d.%d", 4, 0 )
    [rbx].Write ( "test.ini" )
    [rbx].Release()

    mov rbx, IConfig::IConfig( NULL )

    [rbx].Read  ( "test.ini" )
    [rbx].Write ( "test2.ini" )
    [rbx].Release()

    xor eax,eax
    ret

main endp

    end
