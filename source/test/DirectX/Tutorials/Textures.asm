;
; Translated from:
;  DirectX-SDK-samples/Tutorials/Tut05_Texture/Texture.cpp
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
g_pTexture LPDIRECT3DTEXTURE9 NULL

CUSTOMVERTEX	struct
position	D3DXVECTOR3 <>
color		D3DCOLOR ?
ifndef SHOW_HOW_TO_USE_TCI
tu		FLOAT ?
tv		FLOAT ?
endif
CUSTOMVERTEX	ends

ifdef SHOW_HOW_TO_USE_TCI
D3DFVF_CUSTOMVERTEX equ (D3DFVF_XYZ or D3DFVF_DIFFUSE)
else
D3DFVF_CUSTOMVERTEX equ (D3DFVF_XYZ or D3DFVF_DIFFUSE or D3DFVF_TEX1)
endif

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
    g_pd3dDevice.SetRenderState( D3DRS_LIGHTING, FALSE )
    g_pd3dDevice.SetRenderState( D3DRS_ZENABLE, TRUE )

    .return S_OK

InitD3D endp

InitGeometry proc uses rdi rbx

    D3DXCreateTextureFromFile( g_pd3dDevice, L"banana.bmp", &g_pTexture )
    .if FAILED(eax)

	MessageBox( NULL, L"Could not find banana.bmp", L"Textures.exe", MB_OK )
	.return E_FAIL
    .endif

     g_pd3dDevice.CreateVertexBuffer(
	50 * 2 * CUSTOMVERTEX, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL )
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
	mov   [rdi].position.y,-1.0
	movss [rdi+CUSTOMVERTEX].position.x,xmm0
	mov   [rdi+CUSTOMVERTEX].position.y,1.0
	cosf(theta)
	movss [rdi].position.z,xmm0
	movss [rdi+CUSTOMVERTEX].position.z,xmm0
	mov   [rdi].color,0xffffffff
	mov   [rdi+CUSTOMVERTEX].color,0xff808080
ifndef SHOW_HOW_TO_USE_TCI
	cvtsi2ss xmm0,ebx
	divss xmm0,50.0 - 1.0
	movss [rdi].tu,xmm0
	movss [rdi+CUSTOMVERTEX].tu,xmm0
	mov   [rdi].tv,1.0
	mov   [rdi+CUSTOMVERTEX].tv,0.0
endif
    .endf
    g_pVB.Unlock()
   .return S_OK

InitGeometry endp

Cleanup proc

    .if( g_pTexture != NULL )
	g_pTexture.Release()
    .endif
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
    divss xmm1,1000.0
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

Render proc

    g_pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET or D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0, 0 )
    g_pd3dDevice.BeginScene()

    .if SUCCEEDED(eax)

	SetupMatrices()

	g_pd3dDevice.SetTexture( 0, g_pTexture )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE )

ifdef SHOW_HOW_TO_USE_TCI
	.new mTextureTransform:D3DXMATRIX
	.new mProj:D3DXMATRIX
	.new mTrans:D3DXMATRIX
	.new mScale:D3DXMATRIX

	g_pd3dDevice.GetTransform( D3DTS_PROJECTION, &mProj )
	D3DXMatrixTranslation( &mTrans, 0.5, 0.5, 0.0 )
	D3DXMatrixScaling( &mScale, 0.5, -0.5, 1.0 )
	mTextureTransform = mProj * mScale * mTrans

	g_pd3dDevice.SetTransform( D3DTS_TEXTURE0, &mTextureTransform )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT4 or D3DTTFF_PROJECTED )
	g_pd3dDevice.SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION )
endif
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
	    L"D3D Tutorial 05: Textures",
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
