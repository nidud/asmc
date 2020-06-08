;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearcolormatrices
;
include windows.inc
include gdiplus.inc
include tchar.inc

    .data

    defaultColorMatrix ColorMatrix { ;; Multiply red component by 1.5.
        {
            1.5,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.0,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.0,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    defaultGrayMatrix ColorMatrix {  ;; Multiply green component by 1.5.
        {
            1.0,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.5,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.0,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    penColorMatrix ColorMatrix {     ;; Multiply blue component by 1.5.
        {
            1.0,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.0,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.5,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    penGrayMatrix ColorMatrix {      ;; Multiply all components by 1.5.
        {
            1.5,  0.0,  0.0,  0.0,  0.0,
            0.0,  1.5,  0.0,  0.0,  0.0,
            0.0,  0.0,  1.5,  0.0,  0.0,
            0.0,  0.0,  0.0,  1.0,  0.0,
            0.0,  0.0,  0.0,  0.0,  1.0
        }
    }
    MetafileCreated BOOL FALSE

    .code

DrawEllipse proto :abs, :abs, :abs {

   .new p:GraphicsPath()

    p.AddEllipse(this, 40, 100, 30)

    ifnb <_2>
       .new a:Pen(_1, 4.0)
        g.DrawPath(&a, &p)
        a.Release()
    else
       .new b:PathGradientBrush(&p)
        b.SetCenterColor(_1)
        mov count,1
        mov FullTranslucent,_1
        b.SetSurroundColors(&FullTranslucent, &count)
        g.FillEllipse(&b, this, 40, 100, 30)
        b.Release()
    endif
    p.Release()
    }

CreateMetafile proc hdc:HDC

  local count:SINT
  local FullTranslucent:ARGB

   .new m:Metafile(L"TestMetafile6.emf", hdc)
   .new g:Graphics(&m)

    g.SetSmoothingMode(SmoothingModeAntiAlias)

    DrawEllipse( 20, Gray, p)
    DrawEllipse(150, Gray)
    DrawEllipse(280, Olive, p)
    DrawEllipse(410, Olive)

    g.Release()
    m.Release()

    mov MetafileCreated,TRUE
    ret

CreateMetafile endp

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

        .if MetafileCreated == FALSE

            CreateMetafile(rax)
            mov rax,ps.hdc
        .endif

       .new g:Graphics(rax)
       .new i:Image(L"TestMetafile6.emf")
       .new imAtt:ImageAttributes()
       .new rect:RectF
       .new unit:Unit

        i.GetBounds(&rect, &unit)

       .new r1:RectF(10.0,  50.0, rect.Width, rect.Height)
       .new r2:RectF(10.0,  90.0, rect.Width, rect.Height)
       .new r3:RectF(10.0, 130.0, rect.Width, rect.Height)

        ;; Set the default color- and grayscale-adjustment matrices.
        imAtt.SetColorMatrices(&defaultColorMatrix, &defaultGrayMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypeDefault)
        g.DrawImage(&i, 10.0, 10.0, rect.Width, rect.Height)
        g.DrawImage(&i, &r1, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)

        ;; Set the pen color- and grayscale-adjustment matrices.
        imAtt.SetColorMatrices(&penColorMatrix, &penGrayMatrix, ColorMatrixFlagsAltGray, ColorAdjustTypePen)
        g.DrawImage(&i, &r2, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)
        imAtt.ClearColorMatrices(ColorAdjustTypePen)
        g.DrawImage(&i, &r3, rect.X, rect.Y, rect.Width, rect.Height, UnitPixel, &imAtt)

        i.Release()
        g.Release()
        EndPaint(hWnd, &ps)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if r8d == VK_ESCAPE
        .endc
    .default
        .return DefWindowProc(rcx, edx, r8, r9)
    .endsw
    xor eax,eax
    ret

WndProc endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hInstance,       rcx
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("ClearColorMatrices")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "ClearColorMatrices", "ClearColorMatrices", WS_OVERLAPPEDWINDOW,
                100, 80, 610, 300, NULL, NULL, hInstance, 0)

            mov hwnd,rax

           ;; Initialize GDI+.
           .new gdiplus:GdiPlus()

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)
            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            gdiplus.Release()
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart

