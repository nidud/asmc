;;
;; This method queries D3D9 for the amount of available texture memory. On
;; Windows Vista, this number is typically the dedicated video memory plus
;; the shared system memory minus the amount of memory in use by textures
;; and render targets.
;;

WIN32_LEAN_AND_MEAN equ 1

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

.code

GetVideoMemoryViaD3D9 proc hMonitor:HMONITOR, pdwAvailableTextureMem:ptr UINT

  local hr:HRESULT

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
                SAFE_RELEASE(pd3dDevice)
            .endif
        .endf
        SAFE_RELEASE(pD3D9)
    .endif

    xor eax,eax
    mov ecx,E_FAIL
    cmp eax,bGotMemory
    cmove eax,ecx
    ret

GetVideoMemoryViaD3D9 endp


GetHMonitorFromD3D9Device proc pd3dDevice:ptr IDirect3DDevice9, hMonitor:ptr HMONITOR

   .new cp:D3DDEVICE_CREATION_PARAMETERS
   .new bFound:BOOL = FALSE

    mov qword ptr [rdx],NULL
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
    mov ecx,E_FAIL
    cmp eax,bFound
    cmove eax,ecx
    ret

GetHMonitorFromD3D9Device endp

    end

