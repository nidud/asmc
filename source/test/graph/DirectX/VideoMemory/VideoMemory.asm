; DirectX SDK Samples
;
; https://github.com/walbourn/directx-sdk-samples
;

include windows.inc
include winnls.inc
include string.inc
include stdio.inc
include assert.inc
include ddraw.inc
include wbemidl.inc
include DirectX/d3d9.inc
include DirectX/dxgi.inc
include DirectX/dxdiag.inc
include tchar.inc

define PRINTF_DEBUGGING

DDRAW_MATCH     STRUC
guid            GUID <>
hMonitor        HMONITOR ?
strDriverName   SBYTE 512 dup(?)
bFound          BOOL ?
DDRAW_MATCH     ENDS


CALLBACK(PfnCoSetProxyBlanket, :ptr IUnknown, :DWORD, :DWORD, :ptr OLECHAR, :DWORD, :DWORD, :RPC_AUTH_IDENTITY_HANDLE, :DWORD)
CALLBACK(LPCREATEDXGIFACTORY, :REFIID, :ptr ptr)
CALLBACK(LPDIRECTDRAWCREATE, :ptr GUID, :ptr LPDIRECTDRAW, :ptr IUnknown)

.data
 IID_IDXGIFactory       GUID {0x7b7166ec,0x21c7,0x44ae,{0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69}}
 IID_IWbemLocator       GUID {0xdc12a687,0x737f,0x11cf,{0x88,0x4d,0x00,0xaa,0x00,0x4b,0x2e,0x24}}
 IID_IDirectDraw7       GUID {0x15e65ec0,0x3b9c,0x11d2,{0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b}}
 IID_IDxDiagProvider    GUID {0x9C6B4CB0,0x23F8,0x49CC,{0xA3,0xED,0x45,0xA5,0x50,0x00,0xA6,0xD2}}
 CLSID_DxDiagProvider   GUID {0xA65B8071,0x3BFE,0x4213,{0x9A,0x5B,0x49,0x1D,0xA4,0x46,0x1C,0xA7}}
 CLSID_WbemLocator      GUID {0x4590f811,0x1d3a,0x11d0,{0x89,0x1f,0x00,0xaa,0x00,0x4b,0x2e,0x24}}

.code

; This method queries D3D9 for the amount of available texture memory. On
; Windows Vista, this number is typically the dedicated video memory plus
; the shared system memory minus the amount of memory in use by textures
; and render targets.

GetVideoMemoryViaD3D9 proc hMonitor:HMONITOR, pdwAvailableTextureMem:ptr UINT

  local hr:HRESULT

    ldr rdx,pdwAvailableTextureMem
    mov UINT ptr [rdx],0

    .new bGotMemory:BOOL = FALSE
    .new pD3D9:ptr IDirect3D9 = Direct3DCreate9( D3D_SDK_VERSION )

    .if rax

       .new iAdapter:UINT
       .new dwAdapterCount:UINT = pD3D9.GetAdapterCount()

        .for( iAdapter = 0: iAdapter < dwAdapterCount: iAdapter++ )

            .new pd3dDevice:ptr IDirect3DDevice9 = NULL
            .new hAdapterMonitor:HMONITOR = pD3D9.GetAdapterMonitor( iAdapter )
            .continue .if( hMonitor != rax )

            .new hWnd:HWND = GetDesktopWindow()
            .new pp:D3DPRESENT_PARAMETERS

            ZeroMemory( &pp, sizeof( D3DPRESENT_PARAMETERS ) )
            mov pp.BackBufferWidth,800
            mov pp.BackBufferHeight,600
            mov pp.BackBufferFormat,D3DFMT_R5G6B5
            mov pp.BackBufferCount,1
            mov pp.MultiSampleType,D3DMULTISAMPLE_NONE
            mov pp.SwapEffect,D3DSWAPEFFECT_DISCARD
            mov pp.hDeviceWindow,hWnd
            mov pp.Windowed,TRUE
            mov hr,pD3D9.CreateDevice( iAdapter, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &pd3dDevice )
            .if (SUCCEEDED(hr))

                pd3dDevice.GetAvailableTextureMem()
                mov rcx,pdwAvailableTextureMem
                mov [rcx],eax
                mov bGotMemory,TRUE
                SafeRelease(pd3dDevice)
            .endif
        .endf
        SafeRelease(pD3D9)
    .endif
    xor eax,eax
    .if ( eax == bGotMemory )
        mov eax,E_FAIL
    .endif
    ret

GetVideoMemoryViaD3D9 endp


GetHMonitorFromD3D9Device proc pd3dDevice:ptr IDirect3DDevice9, hMonitor:ptr HMONITOR

   .new cp:D3DDEVICE_CREATION_PARAMETERS
   .new bFound:BOOL = FALSE

    ldr rdx,hMonitor
    mov size_t ptr [rdx],NULL
    pd3dDevice.GetCreationParameters( &cp )
    .if (SUCCEEDED(eax))

       .new pD3D:ptr IDirect3D9 = NULL
        pd3dDevice.GetDirect3D( &pD3D )
        .if (SUCCEEDED(eax))

            pD3D.GetAdapterMonitor( cp.AdapterOrdinal )
            mov rcx,hMonitor
            mov [rcx],rax
            mov bFound,TRUE
        .endif
        pD3D.Release()
    .endif
    xor eax,eax
    .if ( eax == bFound )
        mov eax,E_FAIL
    .endif
    ret

GetHMonitorFromD3D9Device endp


; DXGI is only available on Windows Vista or later. This method returns the
; amount of dedicated video memory, the amount of dedicated system memory,
; and the amount of shared system memory. DXGI is more reflective of the true
; system configuration than the previous 4 methods.

GetVideoMemoryViaDXGI proc hMonitor:HMONITOR, pDedicatedVideoMemory:ptr size_t,
    pDedicatedSystemMemory:ptr size_t, pSharedSystemMemory:ptr size_t

   .new hr:HRESULT
   .new bGotMemory:BOOL = FALSE

    xor eax,eax
    ldr rdx,pDedicatedVideoMemory
    ldr rcx,pDedicatedSystemMemory
    mov [rdx],rax
    mov [rcx],rax
    ldr rcx,pSharedSystemMemory
    mov [rcx],rax

    .new hDXGI:HINSTANCE = LoadLibrary( "dxgi.dll" )
    .if( rax )

       .new pCreateDXGIFactory:LPCREATEDXGIFACTORY = NULL
       .new pDXGIFactory:ptr IDXGIFactory = NULL

        mov pCreateDXGIFactory,GetProcAddress( hDXGI, "CreateDXGIFactory" )
        pCreateDXGIFactory( &IID_IDXGIFactory, &pDXGIFactory )

        .new index:int_t
        .for ( index = 0: : ++index )

           .new bFoundMatchingAdapter:BOOL = FALSE
           .new pAdapter:ptr IDXGIAdapter = NULL
            mov hr,pDXGIFactory.EnumAdapters( index, &pAdapter )
            .break .if (FAILED(hr)) ;; DXGIERR_NOT_FOUND is expected when the end of the list is hit

            .new iOutput:int_t
            .for( iOutput = 0: : ++iOutput )

               .new pOutput:ptr IDXGIOutput = NULL
                mov hr,pAdapter.EnumOutputs( iOutput, &pOutput )
                .break .if (FAILED(hr)) ;; DXGIERR_NOT_FOUND is expected when the end of the list is hit

                mov rax,pOutput
               .new outputDesc:DXGI_OUTPUT_DESC
                ZeroMemory( &outputDesc, DXGI_OUTPUT_DESC )

                pOutput.GetDesc( &outputDesc )
                .if( SUCCEEDED( eax ) )

                    .if( hMonitor == outputDesc._Monitor )
                        mov bFoundMatchingAdapter,TRUE
                    .endif

                .endif
                SafeRelease( pOutput )
            .endf

            .if( bFoundMatchingAdapter )

                .new desc:DXGI_ADAPTER_DESC
                ZeroMemory( &desc, sizeof( DXGI_ADAPTER_DESC ) )
                pAdapter.GetDesc( &desc )
                .if( SUCCEEDED( eax ) )

                    mov bGotMemory,TRUE
                    mov rcx,pDedicatedVideoMemory
                    mov [rcx],desc.DedicatedVideoMemory
                    mov rcx,pDedicatedSystemMemory
                    mov [rcx],desc.DedicatedSystemMemory
                    mov rcx,pSharedSystemMemory
                    mov [rcx],desc.SharedSystemMemory
                .endif
                .break
            .endif
        .endf
        FreeLibrary( hDXGI )
    .endif
    xor eax,eax
    .if ( eax == bGotMemory )
        mov eax,E_FAIL
    .endif
    ret

GetVideoMemoryViaDXGI endp


; This method queries the DirectDraw 7 interfaces for the amount of available
; video memory. On a discrete video card, this is often close to the amount
; of dedicated video memory and usually does not take into account the amount
; of shared system memory.

DDEnumCallbackEx proc lpGUID:ptr GUID, lpDriverDescription:LPSTR,
        lpDriverName:LPSTR, lpContext:LPVOID, hm:HMONITOR

    ldr rcx,lpContext
    .if( [rcx].DDRAW_MATCH.hMonitor == hm )

        mov [rcx].DDRAW_MATCH.bFound,TRUE
        strcpy_s( &[rcx].DDRAW_MATCH.strDriverName, 512, lpDriverName )
        mov rcx,lpContext
        memcpy( &[rcx].DDRAW_MATCH.guid, lpGUID, sizeof( GUID ) )
    .endif
    .return TRUE

DDEnumCallbackEx endp


GetVideoMemoryViaDirectDraw proc hMonitor:HMONITOR, pdwAvailableVidMem:ptr DWORD

   .new pDDraw:LPDIRECTDRAW = NULL
   .new pDirectDrawEnumerateEx:LPDIRECTDRAWENUMERATEEXA = NULL
   .new hr:HRESULT
   .new bGotMemory:BOOL = FALSE

    ldr rdx,pdwAvailableVidMem
    mov DWORD ptr [rdx],0

    .new pDDCreate:LPDIRECTDRAWCREATE = NULL
    .new hInstDDraw:HINSTANCE = LoadLibrary( "ddraw.dll" )
    .if( rax )

        .new match:DDRAW_MATCH
        ZeroMemory( &match, sizeof( DDRAW_MATCH ) )
        mov match.hMonitor,hMonitor

        mov pDirectDrawEnumerateEx,GetProcAddress( hInstDDraw, "DirectDrawEnumerateExA" )
        .if rax

            mov hr,pDirectDrawEnumerateEx( &DDEnumCallbackEx, &match, DDENUM_ATTACHEDSECONDARYDEVICES )
        .endif

        mov pDDCreate,GetProcAddress( hInstDDraw, "DirectDrawCreate" )
        .if rax

            pDDCreate( &match.guid, &pDDraw, NULL )

           .new pDDraw7:LPDIRECTDRAW7
            pDDraw.QueryInterface( &IID_IDirectDraw7, &pDDraw7 )
            .if( SUCCEEDED( eax ) )

               .new ddscaps:DDSCAPS2
                ZeroMemory( &ddscaps, sizeof( DDSCAPS2 ) )
                mov ddscaps.dwCaps,DDSCAPS_VIDEOMEMORY or DDSCAPS_LOCALVIDMEM
                mov hr,pDDraw7.GetAvailableVidMem( &ddscaps, pdwAvailableVidMem, NULL )
                .if( SUCCEEDED( hr ) )
                    mov bGotMemory,TRUE
                .endif
                pDDraw7.Release()
            .endif
        .endif
        FreeLibrary( hInstDDraw )
    .endif
    xor eax,eax
    .if ( eax == bGotMemory )
        mov eax,E_FAIL
    .endif
    ret

GetVideoMemoryViaDirectDraw endp


GetDeviceIDFromHMonitor proc hm:HMONITOR, strDeviceID:ptr WCHAR, cchDeviceID:int_t


    .new hInstDDraw:HINSTANCE = LoadLibrary( "ddraw.dll" )
    .if( rax )

       .new match:DDRAW_MATCH
        ZeroMemory( &match, sizeof( DDRAW_MATCH ) )
        mov match.hMonitor,hm

        .new pDirectDrawEnumerateEx:LPDIRECTDRAWENUMERATEEXA = GetProcAddress( hInstDDraw, "DirectDrawEnumerateExA" )
        .if( rax )
            pDirectDrawEnumerateEx( &DDEnumCallbackEx, &match, DDENUM_ATTACHEDSECONDARYDEVICES )
        .endif

        .if( match.bFound )

            .new iDevice:LONG = 0
            .new dispdev:DISPLAY_DEVICEA

            ZeroMemory( &dispdev, sizeof( dispdev ) )
            mov dispdev.cb,sizeof( dispdev )

            .while( EnumDisplayDevicesA( NULL, iDevice, &dispdev, 0 ) )

                ;; Skip devices that are monitors that echo another display

                .if( dispdev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER )

                    inc iDevice
                    .continue
                .endif

                ;; Skip devices that aren't attached since they cause problems

                .if( !( dispdev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) )

                    inc iDevice
                    .continue
                .endif

                .ifd ( _stricmp( &match.strDriverName, &dispdev.DeviceName ) == 0 )

                    MultiByteToWideChar( CP_ACP, 0, &dispdev.DeviceID, -1, strDeviceID, cchDeviceID )
                    .return S_OK
                .endif

                inc iDevice
            .endw
        .endif

        FreeLibrary( hInstDDraw )
    .endif
    .return E_FAIL

GetDeviceIDFromHMonitor endp


; This method queries the Windows Management Instrumentation (WMI) interfaces
; to determine the amount of video memory. On a discrete video card, this is
; often close to the amount of dedicated video memory and usually does not take
; into account the amount of shared system memory.

GetVideoMemoryViaWMI proc hMonitor:HMONITOR, pdwAdapterRam:ptr DWORD

   .new strInputDeviceID[512]:WCHAR
   .new hr:HRESULT
   .new bGotMemory:BOOL = FALSE
   .new hrCoInitialize:HRESULT = S_OK
   .new pIWbemLocator:ptr IWbemLocator = NULL
   .new pIWbemServices:ptr IWbemServices = NULL
   .new pNamespace:BSTR = NULL

    ldr rdx,pdwAdapterRam
    mov DWORD ptr [rdx],0

    GetDeviceIDFromHMonitor( hMonitor, &strInputDeviceID, 512 )

    mov hrCoInitialize,CoInitialize(0)
    mov hr,CoCreateInstance(&CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, &pIWbemLocator)
ifdef PRINTF_DEBUGGING
    .if( FAILED( hr ) )
        printf( L"WMI: CoCreateInstance failed: 0x%0.8x\n", hr )
    .endif
endif

    .if ( SUCCEEDED( hr ) && pIWbemLocator )

        ;; Using the locator, connect to WMI in the given namespace.
        mov pNamespace,SysAllocString( L"\\\\.\\root\\cimv2" )

        mov hr,pIWbemLocator.ConnectServer( pNamespace, NULL, NULL, 0,
                                           0, NULL, NULL, &pIWbemServices )
ifdef PRINTF_DEBUGGING
        .if( FAILED( hr ) )
            printf( L"WMI: pIWbemLocator->ConnectServer failed: 0x%0.8x\n", hr )
        .endif
endif
        .if( SUCCEEDED( hr ) && pIWbemServices != NULL )

            .new hinstOle32:HINSTANCE = NULL

            mov hinstOle32,LoadLibraryW( L"ole32.dll" )
            .if rax

                .new pfnCoSetProxyBlanket:PfnCoSetProxyBlanket = NULL

                mov pfnCoSetProxyBlanket,GetProcAddress( hinstOle32, "CoSetProxyBlanket" )
                .if rax

                    ;; Switch security level to IMPERSONATE.
                    pfnCoSetProxyBlanket( pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
                                          RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0 )
                .endif

                FreeLibrary( hinstOle32 )
            .endif

            .new pEnumVideoControllers:ptr IEnumWbemClassObject = NULL
            .new pClassName:BSTR = NULL

            mov pClassName,SysAllocString( L"Win32_VideoController" )

            mov hr,pIWbemServices.CreateInstanceEnum( pClassName, 0,
                                                     NULL, &pEnumVideoControllers )
ifdef PRINTF_DEBUGGING
            .if( FAILED( hr ) )
                printf( L"WMI: pIWbemServices->CreateInstanceEnum failed: 0x%0.8x\n", hr )
            .endif
endif

            .if( SUCCEEDED( hr ) && pEnumVideoControllers )

                .new pVideoControllers[10]:ptr IWbemClassObject
                 ZeroMemory(&pVideoControllers, sizeof(pVideoControllers))
                .new uReturned:DWORD = 0
                .new pPropName:BSTR = NULL

                ;; Get the first one in the list
                pEnumVideoControllers.Reset()
                mov hr,pEnumVideoControllers.Next(5000, ;; timeout in 5 seconds
                                                  10,   ;; return the first 10
                                                  &pVideoControllers,
                                                  &uReturned );
ifdef PRINTF_DEBUGGING
                .if( FAILED( hr ) )
                    printf( L"WMI: pEnumVideoControllers->Next failed: 0x%0.8x\n", hr )
                .endif
                .if( uReturned == 0 )
                    printf( L"WMI: pEnumVideoControllers uReturned == 0\n" )
                .endif
endif

                .new var:VARIANT
                .if( SUCCEEDED( hr ) )

                    .new pVC:ptr IWbemClassObject
                    .new bFound:BOOL = FALSE
                    .new iController:UINT
                    .for( iController = 0: iController < uReturned: iController++ )

                        mov pPropName,SysAllocString( L"PNPDeviceID" )

                        mov ecx,iController
                        mov pVC,pVideoControllers[rcx*8]

                        mov hr,pVC.Get( pPropName, 0, &var, NULL, NULL )
ifdef PRINTF_DEBUGGING
                        .if( FAILED( hr ) )
                            printf( L"WMI: pVideoControllers[iController]->Get PNPDeviceID failed: 0x%0.8x\n", hr )
                        .endif
endif
                        .if( SUCCEEDED( hr ) )

                            .if( wcsstr( var.bstrVal, &strInputDeviceID ) != 0 )
                                mov bFound,TRUE
                            .endif
                        .endif
                        VariantClear( &var )
                        .if( pPropName )
                            SysFreeString( pPropName )
                        .endif

                        .if( bFound )

                            mov pPropName,SysAllocString( L"AdapterRAM" )
                            mov hr,pVC.Get( pPropName, 0, &var, NULL, NULL )
ifdef PRINTF_DEBUGGING
                            .if( FAILED( hr ) )
                                printf( L"WMI: pVideoControllers[iController]->Get AdapterRAM failed: 0x%0.8x\n",
                                         hr )
                            .endif
endif
                            .if( SUCCEEDED( hr ) )

                                mov bGotMemory,TRUE
                                mov rcx,pdwAdapterRam
                                mov [rcx],var.ulVal
                            .endif
                            VariantClear( &var )
                            .if( pPropName )
                                SysFreeString( pPropName )
                            .endif
                            .break
                        .endif
                        SafeRelease( pVC )
                    .endf
                .endif
            .endif

            .if( pClassName )
                SysFreeString( pClassName )
            .endif
            SafeRelease( pEnumVideoControllers )
        .endif

        .if( pNamespace )
            SysFreeString( pNamespace )
        .endif
        SafeRelease( pIWbemServices )
    .endif
    SafeRelease( pIWbemLocator )

    .if( SUCCEEDED( hrCoInitialize ) )
        CoUninitialize()
    .endif
    xor eax,eax
    .if ( eax == bGotMemory )
        mov eax,E_FAIL
    .endif
    ret

GetVideoMemoryViaWMI endp


; DxDiag internally uses both DirectDraw 7 and WMI and returns the rounded WMI
; value if WMI is available. Otherwise, it returns a rounded DirectDraw 7 value.

GetVideoMemoryViaDxDiag proc hMonitor:HMONITOR, pdwDisplayMemory:ptr DWORD

   .new strInputDeviceID[512]:WCHAR

    ldr rcx,hMonitor
    ldr rdx,pdwDisplayMemory

    mov DWORD ptr [rdx],0
    GetDeviceIDFromHMonitor( rcx, &strInputDeviceID, 512 )

    .new hr:HRESULT
    .new hrCoInitialize:HRESULT = S_OK
    .new bGotMemory:BOOL = FALSE
    .new pDxDiagProvider:ptr IDxDiagProvider = NULL
    .new pDxDiagRoot:ptr IDxDiagContainer = NULL
    .new pDevices:ptr IDxDiagContainer = NULL
    .new pDevice:ptr IDxDiagContainer = NULL
    .new wszChildName[256]:WCHAR
    .new wszPropValue[256]:WCHAR
    .new dwDeviceCount:DWORD
    .new var:VARIANT

    mov hrCoInitialize,CoInitialize( 0 )
    VariantInit( &var )

    ;; CoCreate a IDxDiagProvider*
    mov hr,CoCreateInstance( &CLSID_DxDiagProvider,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           &IID_IDxDiagProvider,
                           &pDxDiagProvider )

    .if( SUCCEEDED( hr ) ) ;; if FAILED(hr) then it is likely DirectX 9 is not installed

       .new dxDiagInitParam:DXDIAG_INIT_PARAMS
        ZeroMemory( &dxDiagInitParam, sizeof( DXDIAG_INIT_PARAMS ) )
        mov dxDiagInitParam.dwSize,sizeof( DXDIAG_INIT_PARAMS )
        mov dxDiagInitParam.dwDxDiagHeaderVersion,DXDIAG_DX9_SDK_VERSION
        mov dxDiagInitParam.bAllowWHQLChecks,FALSE
        mov dxDiagInitParam.pReserved,NULL
        pDxDiagProvider.Initialize( &dxDiagInitParam )

        mov hr,pDxDiagProvider.GetRootContainer( &pDxDiagRoot )
        .if( SUCCEEDED( hr ) )

            mov hr,pDxDiagRoot.GetChildContainer( L"DxDiag_DisplayDevices", &pDevices )
            .if( SUCCEEDED( hr ) )

                mov hr,pDevices.GetNumberOfChildContainers( &dwDeviceCount )
                .if( SUCCEEDED( hr ) )

                    .new iDevice:DWORD
                    .for( iDevice = 0: iDevice < dwDeviceCount: iDevice++ )

                       .new bFound:BOOL = FALSE
                        mov hr,pDevices.EnumChildContainerNames( iDevice, &wszChildName, 256 )
                        .if( SUCCEEDED( hr ) )

                            mov hr,pDevices.GetChildContainer( &wszChildName, &pDevice )
                            .if( SUCCEEDED( hr ) )

                                mov hr,pDevice.GetProp( L"szKeyDeviceID", &var );
                                .if( SUCCEEDED( hr ) )

                                    .if( var.vt == VT_BSTR )

                                        .if( wcsstr( var.bstrVal, &strInputDeviceID ) != 0 )
                                            mov bFound,TRUE
                                        .endif
                                    .endif
                                    VariantClear( &var )
                                .endif

                                .if( bFound )

                                    mov hr,pDevice.GetProp( L"szDisplayMemoryEnglish", &var )
                                    .if( SUCCEEDED( hr ) )

                                        .if( var.vt == VT_BSTR )

                                            mov bGotMemory,TRUE
                                            wcscpy_s( &wszPropValue, 256, var.bstrVal )

                                            ;; wszPropValue should be something
                                            ;; like "256.0 MB" so _wtoi will convert it correctly

                                            _wtoi( &wszPropValue )
                                            mov rcx,pdwDisplayMemory
                                            shl eax,20
                                            mov [rcx],eax
                                        .endif
                                        VariantClear( &var )
                                    .endif
                                .endif
                                SafeRelease( pDevice )
                            .endif
                        .endif
                    .endf
                .endif
                SafeRelease( pDevices )
            .endif
            SafeRelease( pDxDiagRoot )
        .endif
        SafeRelease( pDxDiagProvider )
    .endif

    .if( SUCCEEDED( hrCoInitialize ) )
        CoUninitialize()
    .endif
    xor eax,eax
    .if ( eax == bGotMemory )
        mov eax,E_FAIL
    .endif
    ret

GetVideoMemoryViaDxDiag endp


main proc

  ;; This sample loops over all d3d9 adapters and outputs info about them

    .new pD3D9:ptr IDirect3D9 = Direct3DCreate9( D3D_SDK_VERSION )

    .if rax

        .new iAdapter:UINT
        .new dwAdapterCount:UINT = pD3D9.GetAdapterCount()
        .for ( iAdapter = 0: iAdapter < dwAdapterCount: iAdapter++ )

           .new id:D3DADAPTER_IDENTIFIER9
            ZeroMemory( &id, sizeof( D3DADAPTER_IDENTIFIER9 ) )

            pD3D9.GetAdapterIdentifier( iAdapter, 0, &id )
            printf( "\nD3D9 Adapter: %d\nDriver: %s\nDescription: %s\n",
                iAdapter, &id.Driver, &id.Description )

           .new hMonitor:HMONITOR = pD3D9.GetAdapterMonitor( iAdapter )
            printf( "hMonitor: 0x%0.8x\n", hMonitor )

           .new mi:MONITORINFOEX
            mov mi.cbSize,sizeof( MONITORINFOEX )

            GetMonitorInfo( hMonitor, &mi )
            printf( "hMonitor Device Name: %s\n", &mi.szDevice )

           .new dwAvailableVidMem:DWORD
            GetVideoMemoryViaDirectDraw( hMonitor, &dwAvailableVidMem )

            .if( SUCCEEDED( eax ) )
                mov edx,dwAvailableVidMem
                shr edx,20
                printf( "\tGetVideoMemoryViaDirectDraw\n\t\tdwAvailableVidMem: %d MB (%d)\n",
                         edx, dwAvailableVidMem )
            .else
                printf( "\tGetVideoMemoryViaDirectDraw\n\t\tn/a\n" )
            .endif

           .new dwDisplayMemory:DWORD
            GetVideoMemoryViaDxDiag( hMonitor, &dwDisplayMemory )
            .if( SUCCEEDED( eax ) )
                mov edx,dwDisplayMemory
                shr edx,20
                printf( "\tGetVideoMemoryViaDxDiag\n\t\tdwDisplayMemory: %d MB (%d)\n",
                         edx, dwDisplayMemory )
            .else
                printf( "\tGetVideoMemoryViaDxDiag\n\t\tn/a\n" )
            .endif

           .new dwAdapterRAM:DWORD
            GetVideoMemoryViaWMI( hMonitor, &dwAdapterRAM )
            .if( SUCCEEDED( eax ) )
                mov edx,dwAdapterRAM
                shr edx,20
                printf( "\tGetVideoMemoryViaWMI\n\t\tdwAdapterRAM: %d MB (%d)\n",
                         edx, dwAdapterRAM )
            .else
                printf( "\tGetVideoMemoryViaWMI\n\t\tn/a\n" )
            .endif

           .new DedicatedVideoMemory:size_t
           .new DedicatedSystemMemory:size_t
           .new SharedSystemMemory:size_t
            GetVideoMemoryViaDXGI( hMonitor, &DedicatedVideoMemory, &DedicatedSystemMemory, &SharedSystemMemory )
            .if( SUCCEEDED( eax ) )

                mov rdx,DedicatedVideoMemory
                shr rdx,20
                mov rcx,DedicatedSystemMemory
                shr rcx,20
                mov rbx,SharedSystemMemory
                shr rbx,20
                printf(
                    "\tGetVideoMemoryViaDXGI\n\t\tDedicatedVideoMemory: %d MB (%d)\n"
                    "\t\tDedicatedSystemMemory: %d MB (%d)\n\t\tSharedSystemMemory: %d MB (%d)\n",
                    rdx, DedicatedVideoMemory,
                    rcx, DedicatedSystemMemory,
                    rbx, SharedSystemMemory )
            .else
                printf( "\tGetVideoMemoryViaDXGI\n\t\tn/a\n" )
            .endif

           .new dwAvailableTextureMem:UINT
            GetVideoMemoryViaD3D9( hMonitor, &dwAvailableTextureMem )
            .if( SUCCEEDED( eax ) )
                mov edx,dwAvailableTextureMem
                shr edx,20
                printf( "\tGetVideoMemoryViaD3D9\n\t\tdwAvailableTextureMem: %d MB (%d)\n",
                         edx, dwAvailableTextureMem )
            .else
                printf( "\tGetVideoMemoryViaD3D9\n\t\tn/a\n" )
            .endif
        .endf

        SafeRelease( pD3D9 )
        xor eax,eax

    .else

        printf( "Can't create D3D9 object\n" )
        mov eax,-1
    .endif
    ret

main endp

    end _tstart
