;
; Translated from:
;  DirectX-SDK-samples/Tutorials/Tut04_Lights/Lights.cpp
;
include Windows.inc
include mmsystem.inc
include d3dx9.inc
include strsafe.inc
include tchar.inc

.data
g_pD3D LPDIRECT3D9 NULL
g_pd3dDevice LPDIRECT3DDEVICE9 NULL
g_pVB LPDIRECT3DVERTEXBUFFER9 NULL

CUSTOMVERTEX struct
position    D3DXVECTOR3 <>
normal      D3DXVECTOR3 <>
CUSTOMVERTEX ends

D3DFVF_CUSTOMVERTEX equ (D3DFVF_XYZ or D3DFVF_NORMAL)

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

    g_pd3dDevice.SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE )
    g_pd3dDevice.SetRenderState( D3DRS_ZENABLE, TRUE )

    .return S_OK

InitD3D endp

InitGeometry proc uses rdi rbx

    g_pd3dDevice.CreateVertexBuffer( 50 * 2 * sizeof( CUSTOMVERTEX ),
                                     0, D3DFVF_CUSTOMVERTEX,
                                     D3DPOOL_DEFAULT, &g_pVB, NULL )
    .return E_FAIL .if FAILED(eax)

    .new pVertices:ptr CUSTOMVERTEX
     g_pVB._Lock( 0, 0, &pVertices, 0 )
    .return E_FAIL .if FAILED(eax)

    assume rdi:ptr CUSTOMVERTEX

    .for( ebx = 0: ebx < 50: ebx++ )

       .new theta:FLOAT
        cvtsi2ss xmm0,ebx
        mulss xmm0,2.0 * D3DX_PI
        divss xmm0,50.0 - 1.0
        movss theta,xmm0

        lea  rax,[rbx*2]
        imul rdi,rax,CUSTOMVERTEX
        add  rdi,pVertices

        sinf(xmm0)
        movss [rdi].position.x,xmm0
        movss [rdi].normal.x,xmm0
        movss [rdi+CUSTOMVERTEX].position.x,xmm0
        movss [rdi+CUSTOMVERTEX].normal.x,xmm0
        mov   [rdi].position.y,-1.0
        mov   [rdi].normal.y,0.0
        mov   [rdi+CUSTOMVERTEX].position.y,1.0
        mov   [rdi+CUSTOMVERTEX].normal.y,0.0
        cosf(theta)
        movss [rdi].position.z,xmm0
        movss [rdi].normal.z,xmm0
        movss [rdi+CUSTOMVERTEX].position.z,xmm0
        movss [rdi+CUSTOMVERTEX].normal.z,xmm0

    .endf
    g_pVB.Unlock()
   .return S_OK

InitGeometry endp

Cleanup proc

    .if( g_pVB != NULL )
        g_pVB.Release()
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
    divss xmm1,500.0
    D3DXMatrixRotationX( &matWorld, xmm1 )
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

SetupLights proc

   .new mtrl:D3DMATERIAL9
    ZeroMemory( &mtrl, sizeof( D3DMATERIAL9 ) )
    mov mtrl.Diffuse.r,1.0
    mov mtrl.Ambient.r,1.0
    mov mtrl.Diffuse.g,1.0
    mov mtrl.Ambient.g,1.0
    mov mtrl.Diffuse.b,0.0
    mov mtrl.Ambient.b,0.0
    mov mtrl.Diffuse.a,1.0
    mov mtrl.Ambient.a,1.0
    g_pd3dDevice.SetMaterial( &mtrl )

   .new vecDir:D3DXVECTOR3
   .new light:D3DLIGHT9
    ZeroMemory( &light, sizeof( D3DLIGHT9 ) )
    mov light.Type,D3DLIGHT_DIRECTIONAL
    mov light.Diffuse.r,1.0
    mov light.Diffuse.g,1.0
    mov light.Diffuse.b,1.0

    timeGetTime()
    cvtsi2ss xmm0,eax
    divss xmm0,350.0
    cosf(xmm0)
    movss vecDir.x,xmm0
    mov vecDir.y,1.0
    timeGetTime()
    cvtsi2ss xmm0,eax
    divss xmm0,350.0
    sinf(xmm0)
    movss vecDir.z,xmm0

    D3DXVec3Normalize( &light.Direction, &vecDir )
    mov light.Range,1000.0
    g_pd3dDevice.SetLight( 0, &light )
    g_pd3dDevice.LightEnable( 0, TRUE )
    g_pd3dDevice.SetRenderState( D3DRS_LIGHTING, TRUE )
    g_pd3dDevice.SetRenderState( D3DRS_AMBIENT, 0x00202020 )
    ret

SetupLights endp

Render proc

    g_pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET or D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0, 0 )
    g_pd3dDevice.BeginScene()

    .if SUCCEEDED(eax)

        SetupLights()
        SetupMatrices()

        g_pd3dDevice.SetStreamSource( 0, g_pVB, 0, CUSTOMVERTEX )
        g_pd3dDevice.SetFVF( D3DFVF_CUSTOMVERTEX )
        g_pd3dDevice.DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2 )

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
            L"D3D Tutorial 04: Lights",
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
