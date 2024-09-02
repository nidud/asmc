include windows.inc
include specstrings.inc
include directx/d3d11_1.inc
include directx/d3dcompiler.inc
include directx/directxmath.inc
include tchar.inc

SimpleVertex    struct
Pos             XMFLOAT3 <>
Color           XMFLOAT4 <>
SimpleVertex    ends

ConstantBuffer  struct
mWorld          XMMATRIX <>
mView           XMMATRIX <>
mProjection     XMMATRIX <>
ConstantBuffer  ends

    .data

LPID3D11VertexShader    typedef ptr ID3D11VertexShader
LPID3D11PixelShader     typedef ptr ID3D11PixelShader
LPID3D11InputLayout     typedef ptr ID3D11InputLayout
LPID3D11Buffer          typedef ptr ID3D11Buffer

g_hInst                 HINSTANCE NULL
g_hWnd                  HWND NULL
g_driverType            D3D_DRIVER_TYPE D3D_DRIVER_TYPE_NULL
g_featureLevel          D3D_FEATURE_LEVEL D3D_FEATURE_LEVEL_11_0
g_pd3dDevice            LPID3D11Device NULL
g_pd3dDevice1           LPID3D11Device1 NULL
g_pImmediateContext     LPID3D11DeviceContext NULL
g_pImmediateContext1    LPID3D11DeviceContext1 NULL
g_pSwapChain            LPIDXGISwapChain NULL
g_pSwapChain1           LPIDXGISwapChain1 NULL
g_pRenderTargetView     LPID3D11RenderTargetView NULL
g_pVertexShader         LPID3D11VertexShader NULL
g_pPixelShader          LPID3D11PixelShader NULL
g_pVertexLayout         LPID3D11InputLayout NULL
g_pVertexBuffer         LPID3D11Buffer NULL
g_pIndexBuffer          LPID3D11Buffer NULL
g_pConstantBuffer       LPID3D11Buffer NULL

Semantic                db "POSITION",0
Color                   db "COLOR",0
align 4
indices                 dw 3,1,0,2,1,3,0,5,4,1,5,0,3,4,7,0,4,3,1,6,5,2,6,1,2,7,6,3,7,2,6,4,5,7,4,6
t_time                  float 0.0
timeStart               size_t 0

align 16
g_World                 XMMATRIX <>
g_View                  XMMATRIX <>
g_Projection            XMMATRIX <>
Eye                     XMFLOAT4 { 0.0, 1.0, -5.0, 0.0 }
At                      XMFLOAT4 { 0.0, 1.0,  0.0, 0.0 }
Up                      XMFLOAT4 { 0.0, 1.0,  0.0, 0.0 }

layout                  D3D11_INPUT_ELEMENT_DESC <Semantic, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
                        D3D11_INPUT_PER_VERTEX_DATA, 0>
                        D3D11_INPUT_ELEMENT_DESC <Color, 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
                        D3D11_INPUT_PER_VERTEX_DATA, 0>
align 16
g_XMIdentityR0          XMVECTORF32 { { { 1.0, 0.0, 0.0, 0.0 } } }
g_XMIdentityR1          XMVECTORF32 { { { 0.0, 1.0, 0.0, 0.0 } } }
g_XMIdentityR2          XMVECTORF32 { { { 0.0, 0.0, 1.0, 0.0 } } }
g_XMIdentityR3          XMVECTORF32 { { { 0.0, 0.0, 0.0, 1.0 } } }
g_XMInfinity            XMVECTORI32 { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } }
g_XMMask3               XMVECTORU32 { { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 } } }
g_XMMaskY               XMVECTORU32 { { { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 } } }
g_XMNegateZ             XMVECTORF32 { { { 1.0, 1.0, -1.0, 1.0 } } }
g_XMSelect1110          XMVECTORU32 { { { XM_SELECT_1, XM_SELECT_1, XM_SELECT_1, XM_SELECT_0 } } }
g_XMQNaN                XMVECTORI32 { { { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } } }
RGBA_MidnightBlue       XMVECTORF32 { { { 0.098039225, 0.098039225, 0.439215720, 1.000000000 } } }
vertices SimpleVertex   {{ -1.0, 1.0, -1.0 }, {0.0, 0.0, 1.0, 1.0}},
                        {{  1.0, 1.0, -1.0 }, {0.0, 1.0, 0.0, 1.0}},
                        {{  1.0, 1.0,  1.0 }, {0.0, 1.0, 1.0, 1.0}},
                        {{ -1.0, 1.0,  1.0 }, {1.0, 0.0, 0.0, 1.0}},
                        {{ -1.0,-1.0, -1.0 }, {1.0, 0.0, 1.0, 1.0}},
                        {{  1.0,-1.0, -1.0 }, {1.0, 1.0, 0.0, 1.0}},
                        {{  1.0,-1.0,  1.0 }, {1.0, 1.0, 1.0, 1.0}},
                        {{ -1.0,-1.0,  1.0 }, {0.0, 0.0, 0.0, 1.0}}

ifdef __PE__
IID_IDXGIFactory1        IID _IID_IDXGIFactory1
IID_IDXGIDevice          IID _IID_IDXGIDevice
IID_IDXGIFactory2        IID _IID_IDXGIFactory2
IID_ID3D11Device1        IID _IID_ID3D11Device1
IID_ID3D11DeviceContext1 IID _IID_ID3D11DeviceContext1
IID_IDXGISwapChain       IID _IID_IDXGISwapChain
IID_ID3D11Texture2D      IID _IID_ID3D11Texture2D
option dllimport:none
endif

    .code

;;--------------------------------------------------------------------------------------
;; Forward declarations
;;--------------------------------------------------------------------------------------

InitWindow      proto :HINSTANCE, :SINT
InitDevice      proto
CleanupDevice   proto
WndProc         proto :HWND, :UINT, :WPARAM, :LPARAM
Render          proto


;;--------------------------------------------------------------------------------------
;; Entry point to the program. Initializes everything and goes into a message processing
;; loop. Idle time is used to render the scene.
;;--------------------------------------------------------------------------------------

WinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:SINT

  local msg:MSG

    .return 0 .ifd InitWindow( hInstance, nCmdShow ) != S_OK

    .ifd InitDevice() != S_OK

        CleanupDevice()
        .return 0
    .endif

    ;; Main message loop

    mov msg.message,0

    .while( msg.message != WM_QUIT )

        .if msg.message == WM_CHAR && msg.wParam == VK_ESCAPE
            SendMessage(msg.hwnd, WM_CLOSE, 0, 0)
        .endif

        .ifd PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )

            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .else
            Render()
        .endif
    .endw
    CleanupDevice()
    mov rax,msg.wParam
    ret

WinMain endp


;;--------------------------------------------------------------------------------------
;; Register class and create window
;;--------------------------------------------------------------------------------------

InitWindow proc hInstance:HINSTANCE, nCmdShow:SINT

  local wcex:WNDCLASSEX
  local rc:RECT

    ;; Register class
    ZeroMemory(&wcex, WNDCLASSEX)
    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.hInstance,     hInstance
    mov wcex.hIcon,         LoadIcon( hInstance, IDI_APPLICATION )
    mov wcex.hIconSm,       rax
    mov wcex.hCursor,       LoadCursor( NULL, IDC_ARROW )
    mov wcex.hbrBackground, COLOR_WINDOW + 1
    mov wcex.lpszClassName, &@CStr("TutorialWindowClass")

    .return E_FAIL .if !RegisterClassEx( &wcex )

    ;; Create window

    mov g_hInst,hInstance

    mov rc.left,    0
    mov rc.top,     0
    mov rc.right,   800
    mov rc.bottom,  600
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE )

    sub rc.right,rc.left
    sub rc.bottom,rc.top
    mov g_hWnd,CreateWindowEx(
            0,
            "TutorialWindowClass",
            "Direct3D 11 Tutorial 4: 3D Spaces",
            WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rc.right,
            rc.bottom,
            NULL,
            NULL,
            hInstance,
            NULL)

    .if rax
        ShowWindow( rax, nCmdShow )
        mov eax,S_OK
    .else
        mov eax,E_FAIL
    .endif
    ret

InitWindow endp


;;--------------------------------------------------------------------------------------
;; Helper for compiling shaders with D3DCompile
;;
;; With VS 11, we could load up prebuilt .cso files instead...
;;--------------------------------------------------------------------------------------

CompileShaderFromFile proc szFileName:LPWSTR, szEntryPoint:LPCSTR,
    szShaderModel:LPCSTR, ppBlobOut:ptr ptr ID3DBlob

  local pErrorBlob:ptr ID3DBlob
  local dwShaderFlags:DWORD
  local hr:HRESULT

    mov hr,S_OK
    mov dwShaderFlags,D3DCOMPILE_ENABLE_STRICTNESS
ifdef _DEBUG
    ;; Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    ;; Setting this flag improves the shader debugging experience, but still allows
    ;; the shaders to be optimized and to run exactly the way they will run in
    ;; the release configuration of this program.
    or dwShaderFlags,D3DCOMPILE_DEBUG

    ;; Disable optimizations to further improve shader debugging
    or dwShaderFlags,D3DCOMPILE_SKIP_OPTIMIZATION
endif
    mov pErrorBlob,NULL

    .ifd D3DCompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
                dwShaderFlags, 0, ppBlobOut, &pErrorBlob ) != S_OK

        mov hr,eax
        .if pErrorBlob

            OutputDebugStringA( pErrorBlob.GetBufferPointer() )
            pErrorBlob.Release()
        .endif
        .return hr
    .endif

    .if pErrorBlob

        pErrorBlob.Release()
    .endif

    mov eax,S_OK
    ret

CompileShaderFromFile endp


;;--------------------------------------------------------------------------------------
;; Create Direct3D device and swap chain
;;--------------------------------------------------------------------------------------

InitDevice proc uses rsi rdi rbx

  local hr                  :HRESULT,
        rc                  :RECT,
        width               :UINT,
        height              :UINT,
        vp                  :D3D11_VIEWPORT,
        numFeatureLevels    :UINT,
        numDriverTypes      :UINT,
        driverTypes[3]      :D3D_DRIVER_TYPE,
        featureLevels[4]    :D3D_FEATURE_LEVEL,
        dxgiFactory         :LPIDXGIFactory1,
        dxgiDevice          :LPIDXGIDevice,
        pBackBuffer         :ptr ID3D11Texture2D,
        adapter             :ptr IDXGIAdapter,
        dxgiFactory2        :ptr IDXGIFactory2,
        sd                  :DXGI_SWAP_CHAIN_DESC1,
        sd2                 :DXGI_SWAP_CHAIN_DESC,
        createDeviceFlags   :UINT,
        pVSBlob             :ptr ID3DBlob,
        numElements         :UINT,
        pPSBlob             :ptr ID3DBlob,
        bd                  :D3D11_BUFFER_DESC,
        stride              :UINT,
        offs                :UINT,
        InitData            :D3D11_SUBRESOURCE_DATA

    GetClientRect( g_hWnd, &rc )

    mov eax,rc.right
    sub eax,rc.left
    mov width,eax
    mov eax,rc.bottom
    sub eax,rc.top
    mov height,eax

    mov createDeviceFlags,0
ifdef _DEBUG
    mov createDeviceFlags,D3D11_CREATE_DEVICE_DEBUG
endif

    mov driverTypes[0],D3D_DRIVER_TYPE_HARDWARE
    mov driverTypes[4],D3D_DRIVER_TYPE_WARP
    mov driverTypes[8],D3D_DRIVER_TYPE_REFERENCE
    mov numDriverTypes,3;ARRAYSIZE( driverTypes )

    mov featureLevels[0],D3D_FEATURE_LEVEL_11_1
    mov featureLevels[4],D3D_FEATURE_LEVEL_11_0
    mov featureLevels[8],D3D_FEATURE_LEVEL_10_1
    mov featureLevels[12],D3D_FEATURE_LEVEL_10_0
    mov numFeatureLevels,4

    .for ( ebx = 0: ebx < numDriverTypes: ebx++ )

        lea rax,driverTypes
        mov eax,[rax+rbx*4]
        mov g_driverType,eax

        .ifd D3D11CreateDevice(NULL, g_driverType, NULL, createDeviceFlags, &featureLevels,
                numFeatureLevels, D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel,
                &g_pImmediateContext ) == E_INVALIDARG

            ;; DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1
            ;; so we need to retry without it
            mov edi,numFeatureLevels
            dec edi
            lea rsi,featureLevels
            add rsi,4
            D3D11CreateDevice(NULL, g_driverType, NULL, createDeviceFlags, rsi, edi,
                    D3D11_SDK_VERSION, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext )
        .endif
        .break .if eax == S_OK
    .endf

    .return .if eax != S_OK

    ;; Obtain DXGI factory from device (since we used nullptr for pAdapter above)

    mov dxgiFactory,rax
    mov dxgiDevice,rax

    .ifd g_pd3dDevice.QueryInterface( &IID_IDXGIDevice, &dxgiDevice ) == S_OK

        mov hr,eax
        mov adapter,NULL
        .ifd dxgiDevice.GetAdapter(&adapter) == S_OK

            mov hr,adapter.GetParent( &IID_IDXGIFactory1, &dxgiFactory )
            adapter.Release()
        .endif
        dxgiDevice.Release()
        mov eax,hr
    .endif
    .return .if eax != S_OK

    ;; Create swap chain

    mov dxgiFactory2,rax
    dxgiFactory.QueryInterface( &IID_IDXGIFactory2, &dxgiFactory2 )
    mov hr,eax

    .if ( dxgiFactory2 )

        ;; DirectX 11.1 or later

        mov hr,g_pd3dDevice.QueryInterface( &IID_ID3D11Device1, &g_pd3dDevice1 )

        .if eax == S_OK

            g_pImmediateContext.QueryInterface( &IID_ID3D11DeviceContext1, &g_pImmediateContext1 )
        .endif

        ZeroMemory(&sd, sizeof(sd))

        mov sd.Width,width
        mov sd.Height,height
        mov sd.Format,DXGI_FORMAT_R8G8B8A8_UNORM
        mov sd.SampleDesc.Count,1
        mov sd.SampleDesc.Quality,0
        mov sd.BufferUsage,DXGI_USAGE_RENDER_TARGET_OUTPUT
        mov sd.BufferCount,1

        mov hr,dxgiFactory2.CreateSwapChainForHwnd( g_pd3dDevice, g_hWnd, &sd,
                NULL, NULL, &g_pSwapChain1 )

        .if eax == S_OK

            g_pSwapChain1.QueryInterface( &IID_IDXGISwapChain, &g_pSwapChain )
        .endif

        dxgiFactory2.Release()

    .else

        ;; DirectX 11.0 systems

        ZeroMemory(&sd2, sizeof(sd2))

        mov sd2.BufferCount,1
        mov sd2.BufferDesc.Width,width
        mov sd2.BufferDesc.Height,height
        mov sd2.BufferDesc.Format,DXGI_FORMAT_R8G8B8A8_UNORM
        mov sd2.BufferDesc.RefreshRate.Numerator,60
        mov sd2.BufferDesc.RefreshRate.Denominator,1
        mov sd2.BufferUsage,DXGI_USAGE_RENDER_TARGET_OUTPUT
        mov sd2.OutputWindow,g_hWnd
        mov sd2.SampleDesc.Count,1
        mov sd2.SampleDesc.Quality,0
        mov sd2.Windowed,TRUE

        mov hr,dxgiFactory.CreateSwapChain( g_pd3dDevice, &sd2, &g_pSwapChain )
    .endif

    ;; Note this tutorial doesn't handle full-screen swapchains so we block
    ;; the ALT+ENTER shortcut

    dxgiFactory.MakeWindowAssociation( g_hWnd, DXGI_MWA_NO_ALT_ENTER )
    dxgiFactory.Release()

    mov eax,hr
    .return .if ( eax != S_OK )

    ;; Create a render target view

    mov pBackBuffer,NULL
    .return .ifd g_pSwapChain.GetBuffer(0, &IID_ID3D11Texture2D, &pBackBuffer ) != S_OK

    mov hr,g_pd3dDevice.CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView )
    pBackBuffer.Release()

    mov eax,hr
    .return .if eax != S_OK

    g_pImmediateContext.OMSetRenderTargets( 1, &g_pRenderTargetView, NULL )

    ;; Setup the viewport

    _mm_store_ss(vp.Width, _mm_cvt_si2ss(xmm0, width))
    _mm_store_ss(vp.Height, _mm_cvt_si2ss(xmm0, height))
    mov vp.MinDepth,0.0
    mov vp.MaxDepth,1.0
    mov vp.TopLeftX,0.0
    mov vp.TopLeftY,0.0
    g_pImmediateContext.RSSetViewports( 1, &vp )

    ;; Compile the vertex shader

    mov pVSBlob,NULL
    .ifd CompileShaderFromFile( L"Tutorial04.fx", "VS", "vs_4_0", &pVSBlob ) != S_OK

        mov hr,eax
        MessageBox(NULL, "The FX file cannot be compiled."
            " Please run this executable from the directory that contains the FX file.",
            "Error", MB_OK )
        .return(hr)
    .endif

    ;; Create the vertex shader

    mov rsi,pVSBlob.GetBufferPointer()
    mov rdi,pVSBlob.GetBufferSize()
    .ifd g_pd3dDevice.CreateVertexShader(rsi, rdi, NULL, &g_pVertexShader ) != S_OK

        pVSBlob.Release()
        .return(hr)
    .endif

    ;; Define the input layout

    mov numElements,2

    ;; Create the input layout

    mov rsi,pVSBlob.GetBufferPointer()
    mov rdi,pVSBlob.GetBufferSize()
    mov hr,g_pd3dDevice.CreateInputLayout( &layout, numElements, rsi, rdi, &g_pVertexLayout )
    pVSBlob.Release()

    mov eax,hr
    .return .if eax != S_OK

    ;; Set the input layout

    g_pImmediateContext.IASetInputLayout( g_pVertexLayout )

    ;; Compile the pixel shader

    mov pPSBlob,NULL
    .ifd CompileShaderFromFile( L"Tutorial04.fx", "PS", "ps_4_0", &pPSBlob ) != S_OK

        mov hr,eax
        MessageBox( NULL, "The FX file cannot be compiled."
            " Please run this executable from the directory that contains the FX file.",
            "Error", MB_OK )
        .return(hr)
    .endif

    ;; Create the pixel shader

    mov rsi,pPSBlob.GetBufferPointer()
    mov rdi,pPSBlob.GetBufferSize()
    g_pd3dDevice.CreatePixelShader( rsi, rdi, NULL, &g_pPixelShader )
    pPSBlob.Release()

    mov eax,hr
    .return .if eax != S_OK

        ;; Create vertex buffer

    ZeroMemory( &bd, sizeof(bd) )
    mov bd.Usage,D3D11_USAGE_DEFAULT
    mov bd.ByteWidth,sizeof(SimpleVertex) * 8
    mov bd.BindFlags,D3D11_BIND_VERTEX_BUFFER
    mov bd.CPUAccessFlags,0

    ZeroMemory( &InitData, sizeof(InitData) )
    lea rax,vertices
    mov InitData.pSysMem,rax
    .return .ifd g_pd3dDevice.CreateBuffer( &bd, &InitData, &g_pVertexBuffer ) != S_OK

    ;; Set vertex buffer

    mov stride,sizeof( SimpleVertex )
    mov offs,0
    g_pImmediateContext.IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offs )

    mov bd.Usage,D3D11_USAGE_DEFAULT
    mov bd.ByteWidth,sizeof( WORD ) * 36 ;; 36 vertices needed for 12 triangles in a triangle list
    mov bd.BindFlags,D3D11_BIND_INDEX_BUFFER
    mov bd.CPUAccessFlags,0

    lea rax,indices
    mov InitData.pSysMem,rax
    .return .ifd g_pd3dDevice.CreateBuffer( &bd, &InitData, &g_pIndexBuffer ) != S_OK

    ;; Set index buffer

    g_pImmediateContext.IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 )

    ;; Set primitive topology

    g_pImmediateContext.IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST )

    ;; Create the constant buffer

    mov bd.Usage,D3D11_USAGE_DEFAULT
    mov bd.ByteWidth,sizeof(ConstantBuffer)
    mov bd.BindFlags,D3D11_BIND_CONSTANT_BUFFER
    mov bd.CPUAccessFlags,0
    .return .ifd g_pd3dDevice.CreateBuffer( &bd, NULL, &g_pConstantBuffer ) != S_OK

    ;; Initialize the world matrix

    XMMatrixIdentity()
    XMStoreMatrix( &g_World )

    ;; Initialize the view matrix

    XMMatrixLookAtLH( Eye, At, Up )
    XMStoreMatrix( &g_View )

    ;; Initialize the projection matrix

    _mm_cvt_si2ss(xmm1, width)
    _mm_cvt_si2ss(xmm0, height)
    _mm_div_ss(xmm1, xmm0)
    XMMatrixPerspectiveFovLH( XM_PIDIV2, xmm1, 0.01, 100.0 )
    XMStoreMatrix( &g_Projection )
    mov eax,S_OK
    ret

InitDevice endp


;;--------------------------------------------------------------------------------------
;; Clean up the objects we've created
;;--------------------------------------------------------------------------------------

CleanupDevice proc

    .if ( g_pImmediateContext )
        g_pImmediateContext.ClearState()
    .endif
    .if ( g_pConstantBuffer )
        g_pConstantBuffer.Release()
    .endif
    .if( g_pIndexBuffer )
        g_pIndexBuffer.Release()
    .endif
    .if( g_pVertexBuffer )
        g_pVertexBuffer.Release()
    .endif
    .if( g_pVertexLayout )
        g_pVertexLayout.Release()
    .endif
    .if( g_pVertexShader )
        g_pVertexShader.Release()
    .endif
    .if( g_pPixelShader )
        g_pPixelShader.Release()
    .endif
    .if( g_pRenderTargetView )
        g_pRenderTargetView.Release()
    .endif
    .if( g_pSwapChain1 )
        g_pSwapChain1.Release()
    .endif
    .if( g_pSwapChain )
        g_pSwapChain.Release()
    .endif
    .if( g_pImmediateContext1 )
        g_pImmediateContext1.Release()
    .endif
    .if( g_pImmediateContext )
        g_pImmediateContext.Release()
    .endif
    .if( g_pd3dDevice1 )
        g_pd3dDevice1.Release()
    .endif
    .if( g_pd3dDevice )
        g_pd3dDevice.Release()
    .endif
    ret

CleanupDevice endp


;;--------------------------------------------------------------------------------------
;; Called every time the application receives a message
;;--------------------------------------------------------------------------------------

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local ps:PAINTSTRUCT
    local hdc:HDC

    .repeat
        .switch( message )
        .case WM_PAINT
            mov hdc,BeginPaint( hWnd, &ps )
            EndPaint( hWnd, &ps )
            .endc

        .case WM_DESTROY
            PostQuitMessage( 0 )
            .endc

            ;; Note that this tutorial does not handle resizing (WM_SIZE) requests,
            ;; so we created the window without the resize border.

        .default
            DefWindowProc( hWnd, message, wParam, lParam )
            .break
        .endsw
        xor eax,eax
    .until 1
    ret

WndProc endp


;;--------------------------------------------------------------------------------------
;; Render the frame
;;--------------------------------------------------------------------------------------

Render proc

  local cb:ConstantBuffer

    ;;
    ;; Update our time
    ;;
    .if g_driverType == D3D_DRIVER_TYPE_REFERENCE

        _mm_load_ss(xmm0, t_time)
        _mm_add_ss(xmm0, XM_PI * 0.0125)

    .else

        GetTickCount64()
        mov rcx,timeStart
        .if !rcx
            mov timeStart,rax
            mov rcx,rax
        .endif
        sub rax,rcx
        ifdef _WIN64
          _mm_cvtsi64_sd(xmm0, rax)
          _mm_cvtsd_ss(xmm0, xmm0)
        else
          _mm_cvtsi32_ss(xmm0, rax)
        endif
        _mm_div_ss(xmm0, 1000.0)
    .endif

    ;;
    ;; Animate the cube
    ;;
    XMMatrixRotationY( xmm0 )
    XMStoreMatrix( &g_World )

    ;;
    ;; Clear the back buffer
    ;;
    g_pImmediateContext.ClearRenderTargetView( g_pRenderTargetView, &RGBA_MidnightBlue )

    ;;
    ;; Update variables
    ;;
    XMMatrixTranspose( g_World.r[0x00], g_World.r[0x10], g_World.r[0x20], g_World.r[0x30] )
    XMStoreMatrix( &cb.mWorld )
    XMMatrixTranspose( g_View.r[0x00], g_View.r[0x10], g_View.r[0x20], g_View.r[0x30] )
    XMStoreMatrix( &cb.mView )

    XMMatrixTranspose( g_Projection.r[0x00], g_Projection.r[0x10], g_Projection.r[0x20], g_Projection.r[0x30] )
    XMStoreMatrix( &cb.mProjection )

    g_pImmediateContext.UpdateSubresource( g_pConstantBuffer, 0, NULL, &cb, 0, 0 )

    ;;
    ;; Renders a triangle
    ;;
    g_pImmediateContext.VSSetShader( g_pVertexShader, NULL, 0 )
    g_pImmediateContext.VSSetConstantBuffers( 0, 1, &g_pConstantBuffer )
    g_pImmediateContext.PSSetShader( g_pPixelShader, NULL, 0 )
    g_pImmediateContext.DrawIndexed( 36, 0, 0 ) ;; 36 vertices needed for 12 triangles in a triangle list

    ;;
    ;; Present our back buffer to our front buffer
    ;;
    g_pSwapChain.Present( 0, 0 )

    ret

Render endp

    end _tstart
