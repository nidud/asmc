;
; http://ube43.wix.com/directxers/apps/blog/directx-9-tutorial-1-ein-fenster
;

;; Every windows application needs to include this
include windows.inc
include tchar.inc

;; Every Direct3D application this
include d3d9.inc

.data
g_bContinue dd TRUE

.code


;; Besides the main function, there must be a message processing function
MsgProc proc WINAPI hWnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch(msg)
      .case WM_DESTROY:
        PostQuitMessage( 0 )
        mov g_bContinue,FALSE
        .endc
      .default
        DefWindowProc( hWnd, msg, wParam, lParam )
    .endsw
    ret

MsgProc endp

;; The entry point of a windows application is the WinMain function
WinMain proc WINAPI uses rsi rdi rbx r12 hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

    ;; Create a window class.
    local wc:WNDCLASSEX
    local hWnd:HWND
    ;local pD3D:LPDIRECT3D9
    local d3dpp:D3DPRESENT_PARAMETERS
    local pd3dDevice:LPDIRECT3DDEVICE9
    local msg:MSG

    xor eax,eax
    mov pd3dDevice,rax
    lea rdi,wc
    mov ecx,sizeof(WNDCLASSEX)
    rep stosb
    mov wc.cbSize,sizeof(WNDCLASSEX)
    mov wc.style,CS_CLASSDC
    lea rax,MsgProc
    mov wc.lpfnWndProc,rax
    lea rax,@CStr("Direct3D Window")
    mov wc.lpszClassName,rax
    mov wc.hInstance,GetModuleHandle(NULL)

    ;;Register the window class.
    RegisterClassEx( &wc );

    ;; Create the application's window.
    mov hWnd,CreateWindowEx(0, "Direct3D Window", "DirectXers - D3D9 Tutorial 1",
        WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, GetDesktopWindow(), NULL, wc.hInstance, NULL )

    ShowWindow(hWnd,SW_SHOW)

    .repeat

        ;; Create the Direct3D Object

        .if !Direct3DCreate9(D3D_SDK_VERSION)

            mov eax,E_FAIL
            .break
        .endif

        mov rbx,rax
        mov rdi,[rax]
        assume rdi: ptr IDirect3D9

        ;; Setup the device presentation parameters

        ZeroMemory( &d3dpp, sizeof(d3dpp) )
        mov d3dpp.Windowed,TRUE
        mov d3dpp.SwapEffect,D3DSWAPEFFECT_DISCARD
        mov d3dpp.BackBufferFormat,D3DFMT_UNKNOWN

        ;; The final step is to use the IDirect3D9::CreateDevice method to create the Direct3D device, as illustrated in the
        ;; following code example.

        .ifs [rdi].CreateDevice(rbx, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice ) < 0

            MessageBox(hWnd, "No HAL HARDWARE_VERTEXPROCESSING! Sample will exit!", NULL, 0);
            [rdi].Release(rbx)
            mov eax,E_FAIL
            .break
        .endif

        mov rax,pd3dDevice
        mov rsi,[rax]
        mov r12,rax
        assume rsi: ptr IDirect3DDevice9

        .while ( g_bContinue )

            ;; Clear render region with blue
            [rsi].Clear( r12, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0, 0 )

            ;; before rendering something, you have to call this
            [rsi].BeginScene( r12 );

            ;;
            ;; rendering of scene objects happens her
            ;;

            ;; now end the scene
            [rsi].EndScene( r12 );

            ;; update screen = swap front and backbuffer
            [rsi].Present( r12, NULL, NULL, NULL, NULL)

            ;; A window has to handle its messages.
            TranslateMessage( &msg );
            DispatchMessage( &msg );
            PeekMessage(&msg, 0, 0, 0, PM_REMOVE)
        .endw

        ;; Do not forget to clean up here

        [rsi].Release( r12 );
        [rdi].Release( rbx )
        xor eax,eax
    .until 1
    ret

WinMain endp

    end _tstart
