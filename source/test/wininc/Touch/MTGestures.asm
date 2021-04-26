
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
    mov wcex.hInstance,     rcx
    mov wcex.hIcon,         LoadIcon(0, IDI_APPLICATION)
    mov wcex.hIconSm,       rax
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, COLOR_WINDOW+1
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr(IDC_MTGESTURES)

    RegisterClassEx(&wcex)
    ret

MyRegisterClass endp

InitInstance proc hInstance:HINSTANCE, nCmdShow:int_t

 local hWnd:HWND

    mov g_hInst,rcx
    .if CreateWindowEx(0, IDC_MTGESTURES, IDS_APP_TITLE, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL)

        mov hWnd,rax
        ShowWindow(hWnd, nCmdShow)
        UpdateWindow(hWnd)
        mov eax,TRUE
    .endif
    ret

InitInstance endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:int_t

  local msg:MSG

    CMyGestureEngine::CMyGestureEngine( &g_cGestureEngine, &g_cRect)
    MyRegisterClass(hInstance)

    .repeat

        .break .if !InitInstance(hInstance, nCmdShow)

        .while (GetMessage(&msg, NULL, 0, 0))

            .if (!TranslateAccelerator(msg.hwnd, NULL, &msg))

                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endif
        .endw

        mov eax,dword ptr msg.wParam
    .until 1
    ret

wWinMain endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local wmId:int_t
  local ps:PAINTSTRUCT
  local hdc:HDC
  local gc:GESTURECONFIG

    .switch (edx)

    .case WM_GESTURENOTIFY

        mov gc.dwID,0
        mov gc.dwWant,GC_ALLGESTURES
        mov gc.dwBlock,0

        .ifd !SetGestureConfig(hWnd, 0, 1, &gc, sizeof(GESTURECONFIG))

            .assert("Error in execution of SetGestureConfig" && 0)
        .endif
        .endc

    .case WM_GESTURE
        mov rdx,rcx
        g_cGestureEngine.WndProc(rdx, r8, r9)
        .return

    .case WM_SIZE
        movzx edx,r9w
        shr r9d,16
        g_cRect.ResetObject(edx, r9d)
        .endc

    .case WM_COMMAND
        movzx eax,r8w ; wParam
        .switch eax
        .case IDM_EXIT
            DestroyWindow(rcx)
            .endc
        .default
            .return DefWindowProc(rcx, edx, r8, r9)
        .endsw
        .endc

    .case WM_PAINT
        mov hdc,BeginPaint(hWnd, &ps)
        g_cRect.Paint(hdc)
        EndPaint(hWnd, &ps)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc

    .default
        .return DefWindowProc(rcx, edx, r8, r9)
    .endsw
    xor eax,eax
    ret

WndProc endp

    end

