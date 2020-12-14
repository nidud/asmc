
include windows.inc
include string.inc
include stdio.inc
include assert.inc
include d3d9.inc

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

GetVideoMemoryViaDxDiag         proto :HMONITOR, :ptr DWORD
GetVideoMemoryViaDirectDraw     proto :HMONITOR, :ptr DWORD
GetVideoMemoryViaWMI            proto :HMONITOR, :ptr DWORD
GetVideoMemoryViaDXGI           proto :HMONITOR, :ptr SIZE_T, :ptr SIZE_T, :ptr SIZE_T
GetVideoMemoryViaD3D9           proto :HMONITOR, :ptr UINT
GetHMonitorFromD3D9Device       proto :ptr IDirect3DDevice9, :ptr HMONITOR

ifdef __CV8__
.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")
.pragma comment(linker,"/DEFAULTLIB:\DirectX\Lib\x64\d3d9.lib")
.data
    IID_IDirectDraw7     GUID {0x15e65ec0,0x3b9c,0x11d2,{0xb9,0x2f,0x00,0x60,0x97,0x97,0xea,0x5b}}
    IID_IDxDiagProvider  GUID {0x9C6B4CB0,0x23F8,0x49CC,{0xA3,0xED,0x45,0xA5,0x50,0x00,0xA6,0xD2}}
    IID_IDXGIFactory     GUID {0x7b7166ec,0x21c7,0x44ae,{0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69}}
    CLSID_DxDiagProvider GUID {0xA65B8071,0x3BFE,0x4213,{0x9A,0x5B,0x49,0x1D,0xA4,0x46,0x1C,0xA7}}
    IID_IWbemLocator     GUID {0xdc12a687,0x737f,0x11cf,{0x88,0x4d,0x00,0xaa,0x00,0x4b,0x2e,0x24}}
    CLSID_WbemLocator    GUID {0x4590f811,0x1d3a,0x11d0,{0x89,0x1f,0x00,0xaa,0x00,0x4b,0x2e,0x24}}
    public IID_IDirectDraw7
    public IID_IDxDiagProvider
    public IID_IDXGIFactory
    public CLSID_DxDiagProvider
    public IID_IWbemLocator
    public CLSID_WbemLocator
endif
.code
;;-----------------------------------------------------------------------------

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

           .new DedicatedVideoMemory:SIZE_T
           .new DedicatedSystemMemory:SIZE_T
           .new SharedSystemMemory:SIZE_T
            GetVideoMemoryViaDXGI( hMonitor, &DedicatedVideoMemory, &DedicatedSystemMemory, &SharedSystemMemory )
            .if( SUCCEEDED( eax ) )

                mov rdx,DedicatedVideoMemory
                shr rdx,20
                mov rcx,DedicatedSystemMemory
                shr rcx,20
                mov r8,SharedSystemMemory
                shr r8,20
                printf(
                    "\tGetVideoMemoryViaDXGI\n\t\tDedicatedVideoMemory: %d MB (%d)\n"
                    "\t\tDedicatedSystemMemory: %d MB (%d)\n\t\tSharedSystemMemory: %d MB (%d)\n",
                    rdx, DedicatedVideoMemory,
                    rcx, DedicatedSystemMemory,
                    r8, SharedSystemMemory )
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

        SAFE_RELEASE( pD3D9 )
        xor eax,eax

    .else

        printf( "Can't create D3D9 object\n" )
        mov eax,-1
    .endif
    ret

main endp

    end
