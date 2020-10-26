include objbase.inc
include tchar.inc
include IConfig.inc
include locals.inc

    .data
    IID_IClassFactory IID _IID_IClassFactory
    IID_IConfig       IID _IID_IConfig
    CLSID_IConfig     IID _CLSID_IConfig

    .code

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    local config:ptr IConfig
    local class:ptr IClassFactory
    local hr:HRESULT

    .ifd !CoInitialize(0)

        .ifd CoGetClassObject(&CLSID_IConfig, CLSCTX_INPROC_SERVER, 0, &IID_IClassFactory, &class)

            MessageBox(0, "Can't get IClassFactory", "CoGetClassObject error", MB_OK or MB_ICONEXCLAMATION)
        .else

            .ifd class.CreateInstance(0, &IID_IConfig, &config)

                MessageBox(0, "Can't create IConfig object", "CreateInstance error",
                        MB_OK or MB_ICONEXCLAMATION)

            .else

                assume rcx:ptr IConfig
                config.create( "Version" )
                [rcx].create ( "Base=%d.%d", 1, 0 )
                config.create( "Product" )
                [rcx].create ( "Source=IConfig COM component" )
                config.create( "URL" )
                [rcx].create ( "UpdateURL=https://github.com/nidud/asmc/tree/master/source/test/comdll" )
                config.find  ( "Version" )
                [rcx].create ( "Package=%d.%d", 1, 0 )
                config.write ( "test.ini" )
                config.Release()
            .endif
            class.Release()
        .endif
        CoUninitialize()
    .else
        MessageBox(0, "Can't initialize COM", "CoInitialize error", MB_OK or MB_ICONEXCLAMATION)
    .endif
    xor eax,eax
    ret

WinMain endp

    end _tstart
