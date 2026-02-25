;
; Translated from:
;  DirectX-SDK-samples/Tutorials/Tut01_CreateDevice/CreateDevice.cpp
;
include d3d9.inc
include strsafe.inc
include tchar.inc

.data
 g_pD3D LPDIRECT3D9 NULL
 g_pd3dDevice LPDIRECT3DDEVICE9 NULL

.code

InitD3D proc hWnd:HWND
    .new d3dpp:D3DPRESENT_PARAMETERS
    .if !Direct3DCreate9( D3D_SDK_VERSION )
        .return( E_FAIL )
    .endif
    mov g_pD3D,rax
    ZeroMemory( &d3dpp, sizeof( d3dpp ) )
    mov d3dpp.Windowed,TRUE
    mov d3dpp.SwapEffect,D3DSWAPEFFECT_DISCARD
    mov d3dpp.BackBufferFormat,D3DFMT_UNKNOWN
    .if FAILED(g_pD3D.CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                  D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice))
        .return( E_FAIL )
    .endif
    xor eax,eax
    ret
    endp


Cleanup proc
    SafeRelease(g_pd3dDevice)
    SafeRelease(g_pD3D)
    ret
    endp


Render proc
    g_pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0, 0 )
    .if SUCCEEDED(g_pd3dDevice.BeginScene())
        g_pd3dDevice.EndScene()
    .endif
    g_pd3dDevice.Present( NULL, NULL, NULL, NULL )
    ret
    endp


MsgProc proc hWnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(msg)
    .case WM_DESTROY
        Cleanup()
        PostQuitMessage( 0 )
       .return( 0 )
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if ( ldr(wParam) == VK_ESCAPE )
    .case WM_PAINT
        Render()
        ValidateRect( ldr(hWnd), NULL )
       .return( 0 )
    .endsw
    DefWindowProc( ldr(hWnd), ldr(msg), ldr(wParam), ldr(lParam) )
    ret
    endp


wWinMain proc hInst:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nShowCmd:SINT

   .new wc:WNDCLASSEX
   .new msg:MSG
   .new hWnd:HWND

    ZeroMemory(&wc, WNDCLASSEX)
    mov wc.cbSize,WNDCLASSEX
    mov wc.style,CS_CLASSDC
    mov wc.lpfnWndProc,&MsgProc
    mov wc.lpszClassName,&@CStr(L"D3D Tutorial")
    mov wc.hInstance,GetModuleHandle(NULL)
    RegisterClassEx( &wc )
    mov hWnd,CreateWindowEx(0, L"D3D Tutorial", L"D3D Tutorial 01: CreateDevice", WS_OVERLAPPEDWINDOW,
            100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL)
    .if SUCCEEDED(InitD3D(hWnd))
        ShowWindow( hWnd, SW_SHOWDEFAULT )
        UpdateWindow( hWnd )
        ZeroMemory( &msg, sizeof( msg ) )
        .while ( GetMessage( &msg, NULL, 0, 0 ) )
            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw
    .endif
    UnregisterClass( L"D3D Tutorial", wc.hInstance )
    xor eax,eax
    ret
    endp

    end _tstart
