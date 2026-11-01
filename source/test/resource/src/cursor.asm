include windows.inc
include tchar.inc
include res/cursor.inc

define IDR_MYCURSOR 100
define CLASSNAME <"MyWindowCursor">

.code

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .switch uMsg
    .case WM_PAINT
       .new ps:PAINTSTRUCT
        BeginPaint(hWnd, &ps)
        EndPaint(hWnd, &ps)
        .return( 0 )
    .case WM_DESTROY
        PostQuitMessage(0)
        .return( 0 )
    .endsw
    .return DefWindowProc(hWnd, uMsg, wParam, lParam)
    endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance: HINSTANCE, lpCmdLine: LPTSTR, nCmdShow: SINT

   .new wc:WNDCLASSEX
    mov wc.cbSize,sizeof(WNDCLASSEX)
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,&WndProc
    mov wc.cbClsExtra,0
    mov wc.cbWndExtra,0
    mov wc.hInstance,hInstance
    mov wc.hIcon,LoadIcon(NULL, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(hInstance, IDR_MYCURSOR)
    mov wc.hbrBackground,NULL
    mov wc.lpszMenuName,NULL
    mov wc.lpszClassName,&@CStr(CLASSNAME)

    RegisterClassEx(&wc)
    CreateWindowEx(0, CLASSNAME, CLASSNAME, WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                NULL, NULL, hInstance, NULL)

    .new msg:MSG
    .while GetMessage(&msg, NULL, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    .return msg.wParam
    endp

 end _tstart
