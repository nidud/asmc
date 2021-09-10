;
; Translated from:
;  DirectX-SDK-samples/Tutorials/Tut03_Matrices/Matrices.cpp
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
x           FLOAT ?
y           FLOAT ?
z           FLOAT ?
color       DWORD ?
CUSTOMVERTEX ends

D3DFVF_CUSTOMVERTEX equ D3DFVF_XYZ or D3DFVF_DIFFUSE

g_Vertices CUSTOMVERTEX \
        { -1.0,-1.0, 0.0, 0xffff0000 },
        {  1.0,-1.0, 0.0, 0xff0000ff },
        {  0.0, 1.0, 0.0, 0xffffffff }

.code

InitD3D proc hWnd:HWND

    mov g_pD3D,Direct3DCreate9( D3D_SDK_VERSION )
    .return E_FAIL .if !rax

    .new d3dpp:D3DPRESENT_PARAMETERS
    ZeroMemory( &d3dpp, sizeof( d3dpp ) )

    mov d3dpp.Windowed,TRUE
    mov d3dpp.SwapEffect,D3DSWAPEFFECT_DISCARD
    mov d3dpp.BackBufferFormat,D3DFMT_UNKNOWN

    g_pD3D.CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                         D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                         &d3dpp, &g_pd3dDevice )

    .return E_FAIL .if FAILED(eax)

    g_pd3dDevice.SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE )
    g_pd3dDevice.SetRenderState( D3DRS_LIGHTING, FALSE )

    .return S_OK

InitD3D endp


InitGeometry proc

    g_pd3dDevice.CreateVertexBuffer( 3 * sizeof( CUSTOMVERTEX ),
                                     0, D3DFVF_CUSTOMVERTEX,
                                     D3DPOOL_DEFAULT, &g_pVB, NULL )
    .return E_FAIL .if FAILED(eax)

    .new pVertices:ptr
     g_pVB._Lock( 0, sizeof( g_Vertices ), &pVertices, 0 )
    .return E_FAIL .if FAILED(eax)

    memcpy( pVertices, &g_Vertices, sizeof( g_Vertices ) )
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

   .new matWorld:D3DXMATRIX;_D3DXMATRIXA16
   .new iTime:UINT

    timeGetTime()
    mov ecx,1000
    cdq
    div ecx
    mov iTime,edx

   .new fAngle:FLOAT
    cvtsi2ss xmm0,edx
    mulss xmm0,( 2.0 * D3DX_PI ) / 1000.0
    movss fAngle,xmm0

    D3DXMatrixRotationY( &matWorld, fAngle )
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

Render proc

    g_pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0, 0 )
    g_pd3dDevice.BeginScene()

    .if SUCCEEDED(eax)

        SetupMatrices()

        g_pd3dDevice.SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) )
        g_pd3dDevice.SetFVF( D3DFVF_CUSTOMVERTEX )
        g_pd3dDevice.DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 1 )

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
            L"D3D Tutorial 03: Matrices",
            WS_OVERLAPPEDWINDOW,
            100, 100, 256, 256,
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
