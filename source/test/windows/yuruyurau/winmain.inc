
; This is modified from @bitRAKE's implementation for FASM

.data
 hdcMem HDC 0

.code

WndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(message)
    .case WM_LBUTTONDOWN
        ReleaseCapture()
        SendMessageW(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0)
       .return(0)
    .case WM_ERASEBKGND
        .return( 1 )
    .case WM_DESTROY
        PostQuitMessage(0)
       .return(0)
    .case WM_PAINT
       .new ps:PAINTSTRUCT
       .new hdc:HDC = BeginPaint(hwnd, &ps)
        .if ( hdcMem )
            BitBlt(hdc, 0, 0, W, W, hdcMem, 0, 0, SRCCOPY)
        .endif
        EndPaint(hwnd, &ps)
       .return(0)
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if ldr(wParam) == VK_ESCAPE
    .default
        DefWindowProc(hwnd, ldr(message), ldr(wParam), ldr(lParam))
    .endsw
    ret
    endp


_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WndProc,                       ; .lpfnWndProc
        0,                              ; .cbClsExtra
        0,                              ; .cbWndExtra
        hInstance,                      ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_HAND),     ; .hCursor
        NULL,                           ; .hbrBackground
        NULL,                           ; .lpszMenuName
        "yuruyurau",                    ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .if RegisterClassEx(&wc)
        movzx edx,ax
        .if CreateWindowEx(0, rdx, 0, WS_VISIBLE or WS_POPUP, 100, 100, W, W, 0, 0, hInstance , 0)

           .new hWnd:HWND = rax
           .new dibBits:ptr = NULL
           .new color[4]:DWORD = { 0x090909, 0x666666, 0xDADADA, 0xFDFDFD }
           .new bmi:BITMAPINFOHEADER = { BITMAPINFOHEADER, W, -W, 1, 8, BI_RGB, W*W, 0, 0, 4 }
            mov hdcMem,CreateCompatibleDC(0)
           .new dibBitmap:HANDLE = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &dibBits, 0, 0)
           .new oldBitmap:HANDLE = SelectObject(hdcMem, dibBitmap)
           .new t:real8 = 0.0
           .new i:real8, m, x, y, k, e, d, c, p
           .new msg:MSG

            .if ( dibBits == NULL )
                .return(-1)
            .endif

            .while ( msg.message != WM_QUIT )

                TranslateMessage(&msg)
                DispatchMessage(&msg)

                .continue .ifd PeekMessage(&msg, 0, 0, 0, PM_REMOVE)

                mov ecx,W*W/4
                mov rdi,dibBits
                xor eax,eax
                mov rdx,rdi
                rep stosd
                mov rdi,rdx
                T()
                .fors ( ebx = I-1 : ebx >= 0 : ebx-- )
                    A()
                    cvtsd2si eax,x
                    cvtsd2si ecx,y
                    imul ecx,ecx,W
                    add eax,ecx
                    .if ( eax < W*W && byte ptr [rdi+rax] < lengthof(color)-1 )
                        inc byte ptr [rdi+rax]
                    .endif
                .endf
                InvalidateRect(hWnd, 0, 0)
                UpdateWindow(hWnd)
                Sleep(D)
            .endw
            SelectObject(hdcMem, oldBitmap)
            DeleteObject(dibBitmap)
            DeleteDC(hdcMem)
            xor eax,eax
        .endif
    .endif
    ret
    endp
    end _tstart
