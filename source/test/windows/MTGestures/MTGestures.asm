
include windows.inc
include DrawingObject.inc
include MyGestureEngine.inc

IDM_EXIT                equ 105
IDC_MTGESTURES          equ <"MTGESTURES">
IDS_APP_TITLE           equ <"MTGestures">
MAX_LOADSTRING          equ 100

    .data
    g_cRect             ptr CDrawingObject 0
    g_cGestureEngine    ptr CMyGestureEngine 0
    g_hInst             HINSTANCE 0

    .code

MyRegisterClass proc hInstance:HINSTANCE

  local wcex:WNDCLASSEX

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    0
    mov wcex.hInstance,     ldr(hInstance)
    mov wcex.hIcon,         LoadIcon(0, IDI_APPLICATION)
    mov wcex.hIconSm,       rax
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, COLOR_WINDOW+1
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr(IDC_MTGESTURES)
    RegisterClassEx(&wcex)
    ret
    endp

InitInstance proc hInstance:HINSTANCE, nCmdShow:int_t

  local hWnd:HWND

    mov g_hInst,ldr(hInstance)
    .if CreateWindowEx(0, IDC_MTGESTURES, IDS_APP_TITLE, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, ldr(hInstance), NULL)
        mov hWnd,rax
        ShowWindow(hWnd, nCmdShow)
        UpdateWindow(hWnd)
        mov eax,TRUE
    .endif
    ret
    endp


wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:int_t

  local msg:MSG

    mov g_cGestureEngine,CMyGestureEngine(&g_cRect)
    MyRegisterClass(hInstance)
    .repeat
        .break .if !InitInstance(hInstance, nCmdShow)
        .whiled GetMessage(&msg, NULL, 0, 0)
            .ifd !TranslateAccelerator(msg.hwnd, NULL, &msg)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endif
        .endw
        mov rax,msg.wParam
    .until 1
    ret
    endp


WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local wmId:int_t
  local ps:PAINTSTRUCT
  local hdc:HDC
  local gc:GESTURECONFIG

    .switch ldr(message)
    .case WM_GESTURENOTIFY
        mov gc.dwID,0
        mov gc.dwWant,GC_ALLGESTURES
        mov gc.dwBlock,0
        .ifd !SetGestureConfig(ldr(hWnd), 0, 1, &gc, sizeof(GESTURECONFIG))
            .assert("Error in execution of SetGestureConfig" && 0)
        .endif
        .endc
    .case WM_GESTURE
        g_cGestureEngine.WndProc(ldr(hWnd), ldr(wParam), ldr(lParam))
       .return
    .case WM_SIZE
        ldr rax,lParam
        movzx edx,ax
        shr eax,16
        g_cRect.ResetObject(edx, eax)
       .endc
    .case WM_COMMAND
        ldr rax,wParam
        movzx eax,ax
        .switch eax
        .case IDM_EXIT
            DestroyWindow(ldr(hWnd))
            .endc
        .default
            .return DefWindowProc(ldr(hWnd), ldr(message), ldr(wParam), ldr(lParam))
        .endsw
        .endc
    .case WM_PAINT
        mov hdc,BeginPaint(ldr(hWnd), &ps)
        g_cRect.Paint(hdc)
        EndPaint(hWnd, &ps)
       .endc
    .case WM_DESTROY
        PostQuitMessage(0)
       .endc
    .default
        .return DefWindowProc(ldr(hWnd), ldr(message), ldr(wParam), ldr(lParam))
    .endsw
    xor eax,eax
    ret
    endp

    end
