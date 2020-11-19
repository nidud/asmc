;
; Translated from:
;  DirectX-SDK-samples/Tutorials/Tut06_Meshes/Meshes.cpp
;
include Windows.inc
include mmsystem.inc
include d3dx9.inc
include strsafe.inc
include tchar.inc

LPD3DMATERIAL9          typedef ptr D3DMATERIAL9
LPLPDIRECT3DTEXTURE9    typedef ptr LPDIRECT3DTEXTURE9
.data
g_pD3D                  LPDIRECT3D9 NULL
g_pd3dDevice            LPDIRECT3DDEVICE9 NULL
g_pMesh                 LPD3DXMESH NULL
g_pMeshMaterials        LPD3DMATERIAL9 NULL
g_pMeshTextures         LPLPDIRECT3DTEXTURE9 NULL
g_dwNumMaterials        DWORD 0

.code

InitD3D proc hWnd:HWND

    mov g_pD3D,Direct3DCreate9( D3D_SDK_VERSION )
   .return E_FAIL .if !rax

   .new d3dpp:D3DPRESENT_PARAMETERS
    ZeroMemory( &d3dpp, sizeof( d3dpp ) )
    mov d3dpp.Windowed,TRUE
    mov d3dpp.SwapEffect,D3DSWAPEFFECT_DISCARD
    mov d3dpp.BackBufferFormat,D3DFMT_UNKNOWN
    mov d3dpp.EnableAutoDepthStencil,TRUE
    mov d3dpp.AutoDepthStencilFormat,D3DFMT_D16

    g_pD3D.CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                         &d3dpp, &g_pd3dDevice )
    .return E_FAIL .if FAILED(eax)

    g_pd3dDevice.SetRenderState( D3DRS_ZENABLE, TRUE )
    g_pd3dDevice.SetRenderState( D3DRS_AMBIENT, 0xffffffff )
   .return S_OK

InitD3D endp

InitGeometry proc uses rsi rdi rbx

    .new pD3DXMtrlBuffer:LPD3DXBUFFER

    .ifsd D3DXLoadMeshFromX( L"Tiger.x", D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL,
            &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh ) < 0

        MessageBox( NULL, L"Could not find tiger.x", L"Meshes.exe", MB_OK )
        .return E_FAIL
    .endif

   .new d3dxMaterials:ptr D3DXMATERIAL = pD3DXMtrlBuffer.GetBufferPointer()

    mov rsi,GetProcessHeap()
    imul r8d,g_dwNumMaterials,D3DMATERIAL9
    mov g_pMeshMaterials,HeapAlloc(rsi, 0, r8)
    .return E_OUTOFMEMORY .if rax == NULL

    imul r8d,g_dwNumMaterials,LPDIRECT3DTEXTURE9
    mov g_pMeshTextures,HeapAlloc(rsi, 0, r8)
    .return E_OUTOFMEMORY .if rax == NULL

    .for( ebx = 0: ebx < g_dwNumMaterials: ebx++ )

        imul esi,ebx,D3DXMATERIAL
        add rsi,d3dxMaterials

        imul ecx,ebx,D3DMATERIAL9
        add rcx,g_pMeshMaterials
        mov [rcx],[rsi].D3DXMATERIAL.MatD3D
        mov [rcx].D3DMATERIAL9.Ambient,[rcx].D3DMATERIAL9.Diffuse

        mov rax,g_pMeshTextures
        lea rdi,[rax+rbx*8]
        mov qword ptr [rdi],NULL

        .if [rsi].D3DXMATERIAL.pTextureFilename != NULL
            .if lstrlenA( [rsi].D3DXMATERIAL.pTextureFilename ) > 0

                D3DXCreateTextureFromFileA(g_pd3dDevice, [rsi].D3DXMATERIAL.pTextureFilename, rdi)
                .if FAILED(eax)

                   .new strTexture[MAX_PATH]:char_t
                    strcpy_s( &strTexture, MAX_PATH, "..\\" )
                    strcat_s( &strTexture, MAX_PATH, [rsi].D3DXMATERIAL.pTextureFilename )
                    D3DXCreateTextureFromFileA( g_pd3dDevice, &strTexture, rdi )

                    .if FAILED(eax)

                        MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK )
                    .endif
                .endif
            .endif
        .endif
    .endf

    pD3DXMtrlBuffer.Release()

    .return S_OK
InitGeometry endp

Cleanup proc uses rsi rdi

    .if( g_pMeshMaterials != NULL )
        HeapFree(GetProcessHeap(), 0, g_pMeshMaterials)
    .endif
    .if( g_pMeshTextures )
        .for( rsi = g_pMeshTextures, edi = 0: edi < g_dwNumMaterials: edi++ )
            lodsq
            .if( rax )
                [rax].IDirect3DTexture9.Release()
            .endif
        .endf
        HeapFree(GetProcessHeap(), 0, g_pMeshTextures)
    .endif
    .if( g_pMesh != NULL )
        g_pMesh.Release()
    .endif
    .if( g_pd3dDevice != NULL )
        g_pd3dDevice.Release()
    .endif
    .if( g_pD3D != NULL )
        g_pD3D.Release()
    .endif
    ret

Cleanup endp

SetupMatrices proc

   .new matWorld:D3DXMATRIX
    D3DXMatrixIdentity( &matWorld )

    timeGetTime()
    cvtsi2ss xmm1,eax
    divss xmm1,1000.0
    D3DXMatrixRotationY( &matWorld, xmm1 )
    g_pd3dDevice.SetTransform( D3DTS_WORLD, &matWorld )

   .new vEyePt:D3DVECTOR( 0.0, 3.0,-5.0 )
   .new vLookatPt:D3DVECTOR( 0.0, 0.0, 0.0 )
   .new vUpVec:D3DVECTOR( 0.0, 1.0, 0.0 )

   .new matView:D3DXMATRIX
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec )
    g_pd3dDevice.SetTransform( D3DTS_VIEW, &matView )

   .new matProj:D3DXMATRIX
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4.0, 1.0, 1.0, 100.0 )
    g_pd3dDevice.SetTransform( D3DTS_PROJECTION, &matProj )
    ret

SetupMatrices endp

Render proc uses rbx

    g_pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET or D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0, 0 )
    g_pd3dDevice.BeginScene()

    .if SUCCEEDED(eax)

        SetupMatrices()

        .for( ebx = 0: ebx < g_dwNumMaterials: ebx++ )

            imul edx,ebx,D3DMATERIAL9
            add rdx,g_pMeshMaterials
            g_pd3dDevice.SetMaterial(rdx)
            mov rax,g_pMeshTextures
            mov r8,[rax+rbx*8]
            g_pd3dDevice.SetTexture(0, r8)
            g_pMesh.DrawSubset(ebx)
        .endf

        g_pd3dDevice.EndScene()
    .endif
    g_pd3dDevice.Present( NULL, NULL, NULL, NULL )
    ret

Render endp

MsgProc proc hWnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch( msg )
    .case WM_DESTROY
        Cleanup()
        PostQuitMessage( 0 )
        .return 0
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .endsw
    .return DefWindowProc( hWnd, msg, wParam, lParam )
MsgProc endp

wWinMain proc hInst:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nShowCmd:SINT

   .new wc:WNDCLASSEX
    ZeroMemory(&wc, WNDCLASSEX)
    mov wc.cbSize,WNDCLASSEX
    mov wc.style,CS_CLASSDC
    mov wc.lpfnWndProc,&MsgProc
    mov wc.lpszClassName,&@CStr(L"D3D Tutorial")
    mov wc.hInstance,GetModuleHandle(NULL)

    RegisterClassEx( &wc )

   .new hWnd:HWND
    mov hWnd,CreateWindowEx(0,
            L"D3D Tutorial",
            L"D3D Tutorial 06: Meshes",
            WS_OVERLAPPEDWINDOW,
            100, 100, 300, 300,
            NULL, NULL, wc.hInstance, NULL)

    InitD3D(hWnd)
    .if SUCCEEDED(eax)

        InitGeometry()
        .if SUCCEEDED(eax)

            ShowWindow( hWnd, SW_SHOWDEFAULT )
            UpdateWindow( hWnd )

           .new msg:MSG
            ZeroMemory( &msg, sizeof( msg ) )

            .while( msg.message != WM_QUIT )

                .if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )

                    TranslateMessage( &msg )
                    DispatchMessage( &msg )
                .else
                    Render()
                .endif
            .endw
        .endif
    .endif

    UnregisterClass( L"D3D Tutorial", wc.hInstance )
    .return 0

wWinMain endp

    end _tstart
