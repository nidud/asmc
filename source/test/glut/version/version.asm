include windows.inc
include gl/glut.inc
include tchar.inc

    .code

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message

    .case WM_CREATE

       .new hdc:HDC
       .new hrc:HGLRC
       .new pfd:PIXELFORMATDESCRIPTOR
       .new pixelformat:SINT

        ZeroMemory(&pfd, PIXELFORMATDESCRIPTOR)

        mov pfd.nSize,PIXELFORMATDESCRIPTOR
        mov pfd.nVersion,1
        mov pfd.dwFlags,PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER
        mov pfd.iPixelType,PFD_TYPE_RGBA
        mov pfd.cColorBits,32
        mov pfd.cDepthBits,24
        mov pfd.cStencilBits,8
        mov pfd.iLayerType,PFD_MAIN_PLANE
        mov hdc,GetDC(hWnd)
        mov pixelformat,ChoosePixelFormat(hdc, &pfd)
        SetPixelFormat(hdc, pixelformat, &pfd)
        mov hrc,wglCreateContext(hdc)
        wglMakeCurrent(hdc, hrc)
        MessageBox(0, glGetString(GL_VERSION), "OPENGL VERSION",0)
        wglDeleteContext(hrc)
        PostQuitMessage(0)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .default
        .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    .return 0

WndProc endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG

    ZeroMemory(&wc, WNDCLASSEX)

    mov wc.cbSize,WNDCLASSEX
    mov wc.hInstance,hInstance
    mov wc.lpfnWndProc,&WndProc
    mov wc.lpszClassName,&@CStr("GLVersionCheck")

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0,
                "GLVersionCheck",
                "GLVersionCheck",
                WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                hInstance,
                0)

            .while GetMessage(&msg, 0, 0, 0)

                DispatchMessage(&msg)
            .endw
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
