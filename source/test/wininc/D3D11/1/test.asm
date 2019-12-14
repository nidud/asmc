;
; https://code.msdn.microsoft.com/windowsdesktop/Direct3D-Tutorial-Win32-829979ef
;
;;--------------------------------------------------------------------------------------
;; File: Tutorial01.cpp
;;
;; This application demonstrates creating a Direct3D 11 device
;;
;; http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx
;;
;; THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
;; ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
;; THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
;; PARTICULAR PURPOSE.
;;
;; Copyright (c) Microsoft Corporation. All rights reserved.
;;--------------------------------------------------------------------------------------

include windows.inc
include SpecStrings.inc
include d3d11_1.inc
include tchar.inc

ifndef _WIN64
    .686
    .xmm
endif
    .data

;;--------------------------------------------------------------------------------------
;; Global Variables
;;--------------------------------------------------------------------------------------

g_hInst                     HINSTANCE NULL
g_hWnd                      HWND NULL
g_driverType                D3D_DRIVER_TYPE D3D_DRIVER_TYPE_NULL
g_featureLevel              D3D_FEATURE_LEVEL D3D_FEATURE_LEVEL_11_0
g_pd3dDevice                LPID3D11Device NULL
g_pd3dDevice1               LPID3D11Device1 NULL
g_pImmediateContext         LPID3D11DeviceContext NULL
g_pImmediateContext1        LPID3D11DeviceContext1 NULL
g_pSwapChain                LPIDXGISwapChain NULL
g_pSwapChain1               LPIDXGISwapChain1 NULL
g_pRenderTargetView         LPID3D11RenderTargetView NULL

ifdef __PE__

 IID_IDXGIFactory1          GUID _IID_IDXGIFactory1
 IID_IDXGIDevice            GUID _IID_IDXGIDevice
 IID_IDXGIFactory2          GUID _IID_IDXGIFactory2
 IID_ID3D11Device1          GUID _IID_ID3D11Device1
 IID_ID3D11DeviceContext1   GUID _IID_ID3D11DeviceContext1
 IID_IDXGISwapChain         GUID _IID_IDXGISwapChain
 IID_ID3D11Texture2D        GUID _IID_ID3D11Texture2D

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

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

  local msg:MSG

    .return 0 .ifd InitWindow( hInstance, nCmdShow ) != S_OK

    .ifd InitDevice() != S_OK

        CleanupDevice()
        .return 0
    .endif

    ;; Main message loop
    mov msg.message,0

    .while ( msg.message != WM_QUIT )

        .ifd PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .else
            Render()
        .endif
    .endw

    CleanupDevice()
    mov rax,msg.wParam
    ret

wWinMain endp


;;--------------------------------------------------------------------------------------
;; Register class and create window
;;--------------------------------------------------------------------------------------

InitWindow proc uses rsi rdi hInstance:HINSTANCE, nCmdShow:SINT

  local wcex:WNDCLASSEX
  local rc:RECT

    ;; Register class

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    0
    mov wcex.hInstance,     hInstance
    mov wcex.hIcon,         LoadIcon(hInstance, IDI_APPLICATION)
    mov wcex.hIconSm,       rax
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, COLOR_WINDOW + 1
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr("TutorialWindowClass")

    .return E_FAIL .if !RegisterClassEx(&wcex)

    ;; Create window

    mov g_hInst,hInstance
    mov rc.left,0
    mov rc.top,0
    mov rc.right,800
    mov rc.bottom,600

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE)

    mov esi,rc.right
    sub esi,rc.left
    mov edi,rc.bottom
    sub edi,rc.top

    .if CreateWindowEx(
            0,
            "TutorialWindowClass",
            "Direct3D 11 Tutorial 1: Direct3D 11 Basics",
            WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            esi,
            edi,
            NULL,
            NULL,
            hInstance,
            NULL )

        mov g_hWnd,rax
        ShowWindow(rax, nCmdShow)
        mov eax,S_OK
    .else
        mov eax,E_FAIL
    .endif
    ret

InitWindow endp


;;--------------------------------------------------------------------------------------
;; Called every time the application receives a message
;;--------------------------------------------------------------------------------------

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local hdc:HDC
  local ps:PAINTSTRUCT

    .switch message

    .case WM_PAINT
        mov hdc,BeginPaint(hWnd, &ps)
        EndPaint(hWnd, &ps)
        .return 0

    .case WM_DESTROY
        PostQuitMessage(0)
        .return 0

        ;; Note that this tutorial does not handle resizing (WM_SIZE) requests,
        ;; so we created the window without the resize border.

    .default
        .return DefWindowProc( hWnd, message, wParam, lParam )
    .endsw
    ret

WndProc endp


;;--------------------------------------------------------------------------------------
;; Create Direct3D device and swap chain
;;--------------------------------------------------------------------------------------

InitDevice proc uses rsi rdi rbx

  local hr                  : HRESULT
  local rc                  : RECT
  local width               : UINT
  local height              : UINT
  local vp                  : D3D11_VIEWPORT
  local numFeatureLevels    : UINT
  local numDriverTypes      : UINT
  local driverTypes[3]      : D3D_DRIVER_TYPE
  local featureLevels[4]    : D3D_FEATURE_LEVEL
  local dxgiFactory         : LPIDXGIFactory1
  local dxgiDevice          : LPIDXGIDevice
  local pBackBuffer         : ptr ID3D11Texture2D
  local adapter             : ptr IDXGIAdapter
  local dxgiFactory2        : ptr IDXGIFactory2
  local sd                  : DXGI_SWAP_CHAIN_DESC1
  local sd2                 : DXGI_SWAP_CHAIN_DESC
  local createDeviceFlags   : UINT

    GetClientRect(g_hWnd, &rc)

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
    mov numFeatureLevels,4;ARRAYSIZE( featureLevels )

    .for ( ebx = 0 : ebx < numDriverTypes : ebx++ )

        lea rsi,driverTypes
        mov eax,[rsi+rbx*4]
        mov g_driverType,eax

        .ifd D3D11CreateDevice(
                NULL,
                g_driverType,
                NULL,
                createDeviceFlags,
                &featureLevels,
                numFeatureLevels,
                D3D11_SDK_VERSION,
                &g_pd3dDevice,
                &g_featureLevel,
                &g_pImmediateContext ) == E_INVALIDARG

            ;; DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1
            ;; so we need to retry without it

            mov edi,numFeatureLevels
            dec edi
            lea rsi,featureLevels
            add rsi,4

            D3D11CreateDevice(
                NULL,
                g_driverType,
                NULL,
                createDeviceFlags,
                rsi,
                edi,
                D3D11_SDK_VERSION,
                &g_pd3dDevice,
                &g_featureLevel,
                &g_pImmediateContext )
        .endif

        .break .if eax == S_OK
    .endf

    .return .if eax != S_OK

    ;; Obtain DXGI factory from device (since we used nullptr for pAdapter above)

    mov dxgiFactory,NULL
    mov dxgiDevice,NULL

    .ifd g_pd3dDevice.QueryInterface(&IID_IDXGIDevice, &dxgiDevice ) == S_OK

        mov hr,eax
        mov adapter,NULL
        .ifd dxgiDevice.GetAdapter(&adapter) == S_OK

            adapter.GetParent( &IID_IDXGIFactory1, &dxgiFactory )
            mov hr,eax
            adapter.Release()
        .endif
        dxgiDevice.Release()
    .else
        mov hr,eax
    .endif

    mov eax,hr
    .return .if eax != S_OK

    ;; Create swap chain

    mov dxgiFactory2,NULL
    dxgiFactory.QueryInterface(&IID_IDXGIFactory2, &dxgiFactory2)
    mov hr,eax

    .if ( dxgiFactory2 )

        ;; DirectX 11.1 or later
        g_pd3dDevice.QueryInterface(&IID_ID3D11Device1, &g_pd3dDevice1)
        mov hr,eax
        .if eax == S_OK

            g_pImmediateContext.QueryInterface(&IID_ID3D11DeviceContext1, &g_pImmediateContext1)
        .endif

        ZeroMemory(&sd, sizeof(sd))
        mov eax,width
        mov sd.Width,eax
        mov eax,height
        mov sd.Height,eax
        mov sd.Format,DXGI_FORMAT_R8G8B8A8_UNORM
        mov sd.SampleDesc.Count,1
        mov sd.SampleDesc.Quality,0
        mov sd.BufferUsage,DXGI_USAGE_RENDER_TARGET_OUTPUT
        mov sd.BufferCount,1

        dxgiFactory2.CreateSwapChainForHwnd( g_pd3dDevice, g_hWnd, &sd, NULL, NULL, &g_pSwapChain1 )
        mov hr,eax
        .if eax == S_OK

        g_pSwapChain1.QueryInterface( &IID_IDXGISwapChain, &g_pSwapChain )
        .endif

        dxgiFactory2.Release()

    .else

        ;; DirectX 11.0 systems

        lea rdi,sd2
        mov ecx,sizeof(sd2)
        xor eax,eax
        rep stosb

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

        dxgiFactory.CreateSwapChain(g_pd3dDevice, &sd2, &g_pSwapChain)
        mov hr,eax
    .endif

    ;; Note this tutorial doesn't handle full-screen swapchains so we block
    ;; the ALT+ENTER shortcut

    dxgiFactory.MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER)
    dxgiFactory.Release()

    mov eax,hr
    .return .if eax != S_OK

    ;; Create a render target view

    mov pBackBuffer,NULL
    .return .ifd g_pSwapChain.GetBuffer(0, &IID_ID3D11Texture2D, &pBackBuffer) != S_OK

    g_pd3dDevice.CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView)
    mov hr,eax
    pBackBuffer.Release()
    mov eax,hr
    .return .if eax != S_OK

    g_pImmediateContext.OMSetRenderTargets(1, &g_pRenderTargetView, NULL)

    ;; Setup the viewport

    cvtsi2ss xmm0,width
    movss vp.Width,xmm0
    cvtsi2ss xmm0,height
    movss vp.Height,xmm0
    mov vp.MinDepth,0.0
    mov vp.MaxDepth,1.0
    mov vp.TopLeftX,0.0
    mov vp.TopLeftY,0.0
    g_pImmediateContext.RSSetViewports( 1, &vp )

    mov eax,S_OK
    ret

InitDevice endp


;;--------------------------------------------------------------------------------------
;; Render the frame
;;--------------------------------------------------------------------------------------

Render proc

  local ColorRGBA[4]:FLOAT

    mov ColorRGBA[0*4],0.098039225
    mov ColorRGBA[1*4],0.098039225
    mov ColorRGBA[2*4],0.439215720
    mov ColorRGBA[3*4],1.000000000

    ;; Just clear the backbuffer

    g_pImmediateContext.ClearRenderTargetView( g_pRenderTargetView, &ColorRGBA )
    g_pSwapChain.Present( 0, 0 )

    ret

Render endp


;;--------------------------------------------------------------------------------------
;; Clean up the objects we've created
;;--------------------------------------------------------------------------------------

CleanupDevice proc

    .if ( g_pImmediateContext )
        g_pImmediateContext.ClearState()
    .endif
    .if ( g_pRenderTargetView )
        g_pRenderTargetView.Release()
    .endif
    .if ( g_pSwapChain1 )
        g_pSwapChain1.Release()
    .endif
    .if ( g_pSwapChain )
        g_pSwapChain.Release()
    .endif
    .if ( g_pImmediateContext1 )
        g_pImmediateContext1.Release()
    .endif
    .if ( g_pImmediateContext )
        g_pImmediateContext.Release()
    .endif
    .if ( g_pd3dDevice1 )
        g_pd3dDevice1.Release()
    .endif
    .if ( g_pd3dDevice )
        g_pd3dDevice.Release()
    .endif
    ret

CleanupDevice endp

    end _tstart
