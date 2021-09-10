;;----------------------------------------------------------------------------
;; File: VidMemViaDXDiag.asm
;;
;; DxDiag internally uses both DirectDraw 7 and WMI and returns the rounded WMI
;; value if WMI is available. Otherwise, it returns a rounded DirectDraw 7 value.
;;
;;-----------------------------------------------------------------------------
WIN32_LEAN_AND_MEAN equ 1
include windows.inc
include string.inc
include stdio.inc
include assert.inc
include dxdiag.inc

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

GetDeviceIDFromHMonitor proto :HMONITOR, :ptr WCHAR, cchDeviceID:int_t

ifdef __CV8__
.data
IID_IDxDiagProvider  GUID {0x9C6B4CB0,0x23F8,0x49CC,{0xA3,0xED,0x45,0xA5,0x50,0x00,0xA6,0xD2}}
CLSID_DxDiagProvider GUID {0xA65B8071,0x3BFE,0x4213,{0x9A,0x5B,0x49,0x1D,0xA4,0x46,0x1C,0xA7}}
endif
.code

GetVideoMemoryViaDxDiag proc hMonitor:HMONITOR, pdwDisplayMemory:ptr DWORD

    mov DWORD ptr [rdx],0

    .new strInputDeviceID[512]:WCHAR

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
                                SAFE_RELEASE( pDevice )
                            .endif
                        .endif
                    .endf
                .endif
                SAFE_RELEASE( pDevices )
            .endif
            SAFE_RELEASE( pDxDiagRoot )
        .endif
        SAFE_RELEASE( pDxDiagProvider )
    .endif

    .if( SUCCEEDED( hrCoInitialize ) )
        CoUninitialize()
    .endif
    xor eax,eax
    mov ecx,E_FAIL
    cmp eax,bGotMemory
    cmove eax,ecx
    ret

GetVideoMemoryViaDxDiag endp

    end
