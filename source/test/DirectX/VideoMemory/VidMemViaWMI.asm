;;----------------------------------------------------------------------------
;; File: VidMemViaWMI.asm
;;
;; This method queries the Windows Management Instrumentation (WMI) interfaces
;; to determine the amount of video memory. On a discrete video card, this is
;; often close to the amount of dedicated video memory and usually does not take
;; into account the amount of shared system memory.
;;
;;-----------------------------------------------------------------------------

include windows.inc
include string.inc
include stdio.inc
include assert.inc
include oleauto.inc
include wbemidl.inc

PRINTF_DEBUGGING equ 1

;;-----------------------------------------------------------------------------
;; Defines, and constants
;;-----------------------------------------------------------------------------
ifndef SAFE_RELEASE
SAFE_RELEASE proto p:abs {
    .if p
        p.Release()
        mov p,NULL
    .endif
    }
endif

GetDeviceIDFromHMonitor proto :HMONITOR, :ptr WCHAR, :int_t ;; from vidmemviaddraw.cpp
CALLBACK(PfnCoSetProxyBlanket, :ptr IUnknown, :DWORD, :DWORD, :ptr OLECHAR, :DWORD, :DWORD, :RPC_AUTH_IDENTITY_HANDLE, :DWORD)

.code

GetVideoMemoryViaWMI proc hMonitor:HMONITOR, pdwAdapterRam:ptr DWORD

    mov DWORD ptr [rdx],0

    .new strInputDeviceID[512]:WCHAR
    GetDeviceIDFromHMonitor( hMonitor, &strInputDeviceID, 512 )

    .new hr:HRESULT
    .new bGotMemory:BOOL = FALSE
    .new hrCoInitialize:HRESULT = S_OK
    .new pIWbemLocator:ptr IWbemLocator = NULL
    .new pIWbemServices:ptr IWbemServices = NULL
    .new pNamespace:BSTR = NULL


    mov hrCoInitialize,CoInitialize( 0 )
    mov hr,CoCreateInstance( &CLSID_WbemLocator,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           &IID_IWbemLocator,
                           &pIWbemLocator )
ifdef PRINTF_DEBUGGING
    .if( FAILED( hr ) )
        wprintf( L"WMI: CoCreateInstance failed: 0x%0.8x\n", hr )
    .endif
endif

    .if( SUCCEEDED( hr ) && pIWbemLocator )

        ;; Using the locator, connect to WMI in the given namespace.
        mov pNamespace,SysAllocString( L"\\\\.\\root\\cimv2" )

        mov hr,pIWbemLocator.ConnectServer( pNamespace, NULL, NULL, 0,
                                           0, NULL, NULL, &pIWbemServices )
ifdef PRINTF_DEBUGGING
        .if( FAILED( hr ) )
            wprintf( L"WMI: pIWbemLocator->ConnectServer failed: 0x%0.8x\n", hr )
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
                wprintf( L"WMI: pIWbemServices->CreateInstanceEnum failed: 0x%0.8x\n", hr )
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
                    wprintf( L"WMI: pEnumVideoControllers->Next failed: 0x%0.8x\n", hr )
                .endif
                .if( uReturned == 0 )
                    wprintf( L"WMI: pEnumVideoControllers uReturned == 0\n" )
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
                            wprintf( L"WMI: pVideoControllers[iController]->Get PNPDeviceID failed: 0x%0.8x\n", hr )
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
                                wprintf( L"WMI: pVideoControllers[iController]->Get AdapterRAM failed: 0x%0.8x\n",
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
                        SAFE_RELEASE( pVC )
                    .endf
                .endif
            .endif

            .if( pClassName )
                SysFreeString( pClassName )
            .endif
            SAFE_RELEASE( pEnumVideoControllers )
        .endif

        .if( pNamespace )
            SysFreeString( pNamespace )
        .endif
        SAFE_RELEASE( pIWbemServices )
    .endif

    SAFE_RELEASE( pIWbemLocator )

    .if( SUCCEEDED( hrCoInitialize ) )
        CoUninitialize()
    .endif
    xor eax,eax
    mov ecx,E_FAIL
    cmp eax,bGotMemory
    cmove eax,ecx
    ret

GetVideoMemoryViaWMI endp

    end
