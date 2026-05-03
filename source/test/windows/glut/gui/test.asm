include windows.inc
include gl/glut.inc
include tchar.inc

    .data
     hdc     HDC 0
     hglrc   HGLRC 0

    .code

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message
    .case WM_CREATE

       .new pf:PIXELFORMATDESCRIPTOR
        ZeroMemory(&pf, PIXELFORMATDESCRIPTOR)

        mov hdc,GetDC(hWnd)
        mov pf.nSize,       PIXELFORMATDESCRIPTOR
        mov pf.nVersion,    1
        mov pf.dwFlags,     PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER
        mov pf.iPixelType,  PFD_TYPE_RGBA
        mov pf.cColorBits,  32
        mov pf.cDepthBits,  24
        mov pf.cStencilBits,8
        mov pf.iLayerType,  PFD_MAIN_PLANE

       .new pixelformat:SINT
        mov pixelformat,ChoosePixelFormat(hdc, &pf)
        SetPixelFormat(hdc, pixelformat, &pf)
        mov hglrc,wglCreateContext(hdc)
        wglMakeCurrent(hdc, hglrc)
        .endc

    .case WM_DESTROY
        wglMakeCurrent(NULL, NULL)
        wglDeleteContext(hglrc)
        ReleaseDC(hWnd, hdc)
        PostQuitMessage(0)
        .endc

    .case WM_SIZE
        movzx eax,word ptr lParam
        movzx ecx,word ptr lParam[2]
        glViewport(0, 0, eax, ecx)
        .endc

    .case WM_PAINT
       .new ps:PAINTSTRUCT
        BeginPaint(hWnd, &ps)
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_TRIANGLES)
        glVertex3f(-0.5, -0.5, 0.0)
        glVertex3f(0.5, 0.0, 0.0)
        glVertex3f(0.0, 0.5, 0.0)
        glEnd()
        glFlush()
        SwapBuffers(hdc)
        EndPaint(hWnd, &ps)
        .endc

    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
        .endc
    .default
        .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    xor eax,eax
    ret

WndProc endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    ZeroMemory(&wc, WNDCLASSEX)

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_OWNDC
    mov wc.hbrBackground,   COLOR_BACKGROUND
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("GLUT")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "GLUT", "Simple GLUT", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 640, 480, NULL, NULL, hInstance, 0)

            mov hwnd,rax
            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)

            .while GetMessage(&msg,0,0,0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
