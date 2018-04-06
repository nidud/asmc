include windows.inc
include SpecStrings.inc
include d3d11.inc
include tchar.inc

    .code

MsgProc proc WINAPI hWnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch(msg)
      .case WM_DESTROY:
        PostQuitMessage( 0 )
        .endc
      .default
        DefWindowProc( hWnd, msg, wParam, lParam )
    .endsw
    ret

MsgProc endp

WinMain proc WINAPI uses rdi hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

    local wc:WNDCLASSEX
    local hWnd:HWND
    local msg:MSG

    local createDeviceFlags:UINT
    local featureLevel:D3D_FEATURE_LEVEL
    local device:ptr ID3D11Device
    local context:ptr ID3D11DeviceContext

    xor eax,eax
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
    RegisterClassEx( &wc )
    mov hWnd,CreateWindowEx(0, "Direct3D Window", "D3D11 Test 1",
        WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, GetDesktopWindow(), NULL, wc.hInstance, NULL )
    ShowWindow( hWnd, SW_SHOW )

    .repeat

        mov createDeviceFlags,0
ifdef _DEBUG
        mov createDeviceFlags,D3D11_CREATE_DEVICE_DEBUG
endif
        .ifd D3D11CreateDevice(
                0,
                D3D_DRIVER_TYPE_HARDWARE,
                0,
                createDeviceFlags,
                0,
                0,
                D3D11_SDK_VERSION,
                &device,
                &featureLevel,
                &context) != S_OK

            MessageBox(0, "D3D11CreateDevice Failed.", "D3D11 Test 1", 0)
            mov eax,E_FAIL
            .break
        .else
            device.Release()
            MessageBox(0, "D3D11CreateDevice Success.", "D3D11 Test 1", 0)
        .endif
        xor eax,eax
    .until 1
    ret

WinMain endp

    end _tstart
