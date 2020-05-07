include windows.inc
include winres.inc
include gdiplus.inc
include tchar.inc

IDM_INSERT      equ 1
IDM_DRAW        equ 2
IDM_GRADIENT    equ 3
IDM_SPHERE      equ 4
IDM_EXIT        equ 5
IDR_MAINMENU    equ 30

    .data
    MenuId SINT IDM_SPHERE

    .code

Sphere proc hdc:HDC

  local count:SINT
  local FullTranslucent:ARGB

   .new G:Graphics()

    .if G.FromHDC2(hdc, rax) == Ok

       .new P:GraphicsPath()
       .new B:PathGradientBrush()

        mov count,1

        P.CreatePath(FillModeAlternate)
        B.CreateFromPath(&P)
        P.AddPathEllipseI(200, 0, 200, 200)
        B.SetCenterColor(ColorAlpha(Green, 180))
        mov FullTranslucent,ColorAlpha(Black, 230)
        B.SetSurroundColors(&FullTranslucent, &count)
        G.SetSmoothingMode(SmoothingModeAntiAlias)
        G.FillEllipseI(&B, 200 + 2, 0 + 2, 200 - 4, 200 - 4)
        B.Release()
        P.Release()

        P.CreatePath(FillModeAlternate)
        P.AddPathEllipseI(200, 100, 150, 150)
        B.CreateFromPath(&P)
        B.SetCenterColor(ColorAlpha(Yellow, 180))
        mov FullTranslucent,ColorAlpha(Red, 200)
        B.SetSurroundColors(&FullTranslucent, &count)
        G.FillEllipseI(&B, 200 + 2, 100 + 2, 150 - 4, 150 - 4)
        B.Release()
        P.Release()
    .endif
    G.Release()
    ret

Sphere endp

Gradient proc hdc:HDC

   .new G:Graphics()

    .if G.FromHDC2(hdc, rax) == Ok

       .new P1:Pen()
       .new P2:Pen()
       .new PT1:PointF(0.0, 0.0)
       .new PT2:PointF(200.0, 200.0)
       .new B:LinearGradientBrush()

        P1.CreatePen(Red, 7.0)
        P2.CreatePen(Aqua, 7.0)
        B.Create(&PT1, &PT2, Red, Blue)
        G.DrawLine(&P2, 225.0, 15.0, 360.0, 190.0)
        G.DrawEllipse(&P1, 230.0, 10.0, 110.0, 180.0)
        G.FillRectangleI(&B, 0, 0, 200, 200)
        B.Release()
        P1.Release()
        P2.Release()
    .endif
    G.Release()
    ret

Gradient endp

Insert proc hdc:HDC

    .new g:Graphics()

    .if g.FromHDC2(hdc, rax) == Ok

        .new i:ptr Image()

        i.FromFile("..\\image.png", FALSE)
        g.DrawImage(i, 10, 10)
        i.Release()
    .endif
    g.Release()
    ret

Insert endp

Draw proc hdc:HDC

    .new g:ptr Graphics()

    .if g.FromHDC2(hdc, rax) == Ok

        .new p:ptr Pen()
        .new b:ptr HatchBrush(HatchStyleCross, Goldenrod, Blue)

        p.CreatePen(DarkTurquoise, 3.0)
        g.FillRectangleI(b, 250, 50, 40, 30)
        g.DrawRectangleI(p, 250, 50, 80, 30)
        b.Release()

        p.NewPen(Red, 2.0)
        g.DrawLineI(p, 20, 10, 200, 100)
        g.DrawBezierI(p, 200, 100, 300, 80, 180, 150, 150, 10)

        p.Release()
        g.Release()
    .endif
    ret

Draw endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

        .switch pascal MenuId
        .case IDM_INSERT
            Insert(ps.hdc)
        .case IDM_DRAW
            Draw(ps.hdc)
        .case IDM_GRADIENT
            Gradient(ps.hdc)
        .case IDM_SPHERE
            Sphere(ps.hdc)
        .endsw

        EndPaint(hWnd, &ps)
        .endc

      .case WM_COMMAND
        .if !r9
            .switch pascal r8w
            .case IDM_INSERT
                mov MenuId,IDM_INSERT
                InvalidateRect(rcx, NULL, TRUE)
            .case IDM_DRAW
                mov MenuId,IDM_DRAW
                InvalidateRect(rcx, NULL, TRUE)
            .case IDM_GRADIENT
                mov MenuId,IDM_GRADIENT
                InvalidateRect(rcx, NULL, TRUE)
            .case IDM_SPHERE
                mov MenuId,IDM_SPHERE
                InvalidateRect(rcx, NULL, TRUE)
            .case IDM_EXIT
                DestroyWindow(rcx)
                .endc
            .endsw
        .endif
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

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    IDR_MAINMENU
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("GdiPlus")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "GdiPlus", "GdiPlus::GdiPlus()", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, 0)

            mov hwnd,rax

            ;; Initialize GDI+.
            .new gdiplus:ptr GdiPlus()

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)

            .while GetMessage(&msg,0,0,0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            gdiplus.Release()
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

RCBEGIN
    RCTYPES 1
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCLANGX LANGID_US
    MENUBEGIN
     MENUNAME "&File", MF_END
      MENUITEM IDM_INSERT, "&Insert"
      MENUITEM IDM_DRAW, "&Draw"
      MENUITEM IDM_GRADIENT, "&Gradient"
      MENUITEM IDM_SPHERE, "&Sphere"
      SEPARATOR
      MENUITEM IDM_EXIT, "&Exit", MF_END
    MENUEND
RCEND

    end _tstart
