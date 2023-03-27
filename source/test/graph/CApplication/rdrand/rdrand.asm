
include rdrand.inc

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define ID_TIMER     1

    .code

BoundRand proc b:uint_t

    mov eax,ecx
    neg eax
    xor edx,edx
    div ecx
    .while 1
        rdrand eax
        .break .if ( eax >= edx )
    .endw
    xor edx,edx
    div ecx
    mov eax,edx
    ret

BoundRand endp

RangeRand proc b:uint_t, m:uint_t

    .whiled ( BoundRand(ecx) <= m )
    .endw
    ret

RangeRand endp

RandRGB proc

    mov r8d,BoundRand(0xFF)
    shl r8d,8
    BoundRand(0xFF)
    mov r8b,al
    shl r8d,8
    BoundRand(0xFF)
    or  eax,r8d
    or  eax,0xFF000000
    ret

RandRGB endp


; Runs the application

CApplication::Run proc

    .new result:int_t = 0
    .new gdiplus:GdiPlus()

    this.BeforeEnteringMessageLoop()

    .if (SUCCEEDED(eax))

        mov result,this.EnterMessageLoop()
    .else

        MessageBox(NULL, "An error occuring when running the sample", NULL, MB_OK)
    .endif

    this.AfterLeavingMessageLoop()

    .return result

CApplication::Run endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc

    .new hr:HRESULT = this.CreateApplicationWindow()

    .return hr

CApplication::BeforeEnteringMessageLoop endp


; Message loop

CApplication::EnterMessageLoop proc

    .new result:int_t = 0

    .if ( this.ShowApplicationWindow() )

        .new msg:MSG

        .while ( GetMessage( &msg, NULL, 0, 0 ) )

            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw

        mov result, msg.wParam
    .endif

    .return result

CApplication::EnterMessageLoop endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc

    this.DestroyApplicationWindow()
    ret

CApplication::AfterLeavingMessageLoop endp


; Shows the application window

    assume rdi:ptr CApplication

CApplication::ShowApplicationWindow proc uses rdi

   .new bSucceeded:BOOL = TRUE

    mov rdi,rcx
    .if ( [rdi].m_hwnd == NULL )

        mov bSucceeded,FALSE
    .endif

    .if ( bSucceeded )

        ShowWindow([rdi].m_hwnd, SW_SHOW)
        UpdateWindow([rdi].m_hwnd)
        SetTimer([rdi].m_hwnd, ID_TIMER, [rdi].m_timer, NULL)
        GetWindowRect([rdi].m_hwnd, &[rdi].m_rect)
        GdipCreateStringFormat(StringFormatFlagsNoWrap,
                LANG_NEUTRAL, &[rdi].m_fontformat)
        this.SetFont(IDS_FONT_TYPEFACE, 12.0, Gray)
        this.GoPartialScreen()
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,rcx
    .if ( [rdi].m_hwnd != NULL )

        .if ( [rdi].m_g )
            GdipDeleteGraphics([rdi].m_g)
        .endif
        .if ( [rdi].m_gm )
            GdipDeleteGraphics([rdi].m_gm)
        .endif
        .if ( [rdi].m_mem )
            DeleteDC([rdi].m_mem)
        .endif
        .if ( [rdi].m_hdc )
            ReleaseDC([rdi].m_hwnd, [rdi].m_hdc)
        .endif
        .if ( [rdi].m_font )
            GdipDeleteFont([rdi].m_font)
        .endif
        .if ( [rdi].m_fontfamily )
            GdipDeleteFontFamily([rdi].m_fontfamily)
        .endif
        .if ( [rdi].m_fontformat )
            GdipDeleteStringFormat([rdi].m_fontformat)
        .endif
        .if ( [rdi].m_bitmap )
            DeleteObject( [rdi].m_bitmap )
        .endif
        KillTimer( [rdi].m_hwnd, ID_TIMER )
        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


; Makes the host window full-screen by placing non-client elements outside the display.

CApplication::GoFullScreen proc uses rdi

    mov rdi,rcx
    mov [rdi].m_isFullScreen,TRUE

    ; The window must be styled as layered for proper rendering.
    ; It is styled as transparent so that it does not capture mouse clicks.
    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED or WS_EX_TRANSPARENT)

    ; Give the window a system menu so it can be closed on the taskbar.
    SetWindowLong([rdi].m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    ; Calculate the span of the display area.
   .new hDC:HDC = GetDC(NULL)
   .new xSpan:int_t = GetSystemMetrics(SM_CXSCREEN)
   .new ySpan:int_t = GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(NULL, hDC)

    ; Calculate the size of system elements.
   .new xBorder:int_t = GetSystemMetrics(SM_CXFRAME)
   .new yCaption:int_t = GetSystemMetrics(SM_CYCAPTION)
   .new yBorder:int_t = GetSystemMetrics(SM_CYFRAME)

    ; Calculate the window origin and span for full-screen mode.
    mov eax,xBorder
    neg eax
   .new xOrigin:int_t = eax
    mov eax,yBorder
    neg eax
    sub eax,yCaption
   .new yOrigin:int_t = eax
    imul eax,xBorder,2
    add xSpan,eax
    imul eax,yBorder,2
    add eax,yCaption
    add ySpan,eax
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

CApplication::GoFullScreen endp


; Makes the host window resizable and focusable.

CApplication::GoPartialScreen proc uses rdi

    mov rdi,rcx
    mov [rdi].m_isFullScreen,FALSE

    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong([rdi].m_hwnd, GWL_STYLE, RESTOREDWINDOWSTYLES)
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST,
        [rdi].m_rect.left, [rdi].m_rect.top, [rdi].m_rect.right, [rdi].m_rect.bottom,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

CApplication::GoPartialScreen endp


CApplication::OnSize proc uses rdi lParam:LPARAM

    mov rdi,this;rcx
    movzx eax,dx
    shr edx,16
    mov [rdi].m_rc.top,0
    mov [rdi].m_rc.left,0
    mov [rdi].m_rc.right,eax
    mov [rdi].m_rc.bottom,edx

    .if ( [rdi].m_isFullScreen == FALSE )
        mov [rdi].m_rc.top,130
        mov [rdi].m_rc.left,50
        sub [rdi].m_rc.right,50
        sub [rdi].m_rc.bottom,100
    .endif
    .if ( [rdi].m_mem )
        DeleteDC([rdi].m_mem)
    .endif
    .if ( [rdi].m_hdc )
        ReleaseDC([rdi].m_hwnd, [rdi].m_hdc)
    .endif
    .if ( [rdi].m_bitmap )
        DeleteObject([rdi].m_bitmap)
        mov [rdi].m_bitmap,NULL
    .endif
    mov [rdi].m_hdc,GetDC([rdi].m_hwnd)
    mov [rdi].m_mem,CreateCompatibleDC([rdi].m_hdc)
    .if ( [rdi].m_g )
        GdipDeleteGraphics([rdi].m_g)
    .endif
    .if ( [rdi].m_gm )
        GdipDeleteGraphics([rdi].m_gm)
    .endif
    GdipCreateFromHDC([rdi].m_hdc, &[rdi].m_g)
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    .ifs ( edx > 100 )
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        .ifs ( ecx > 100 )
            mov [rdi].m_bitmap,CreateCompatibleBitmap([rdi].m_hdc, ecx, edx)
            [rdi].InitObjects()
            SelectObject([rdi].m_mem, [rdi].m_bitmap)
            GdipCreateFromHDC([rdi].m_mem, &[rdi].m_gm)
            GdipSetSmoothingMode([rdi].m_gm, SmoothingModeHighQuality)
        .endif
    .endif
    .return 1

CApplication::OnSize endp


    assume rsi:ptr object

CApplication::OnTimer proc uses rsi rdi rbx

    mov rdi,rcx
   .return 0 .if ( [rdi].m_bitmap == NULL )

    GdipGraphicsClear([rdi].m_gm, ColorAlpha(Black, 230))

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)
   .new p:ptr
   .new b:ptr

    GdipCreatePath(FillModeAlternate, &p)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        mov ecx,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,ecx
        mov r8d,[rsi].m_pos.y
        sub r8d,ecx
        add ecx,ecx
        GdipAddPathEllipseI(p, edx, r8d, ecx, ecx)
        GdipCreatePathGradientFromPath(p, &b)
        GdipSetPathGradientCenterColor(b, [rsi].m_color)
        GdipSetPathGradientSurroundColorsWithCount(b, &FullTranslucent, &count)
        mov ecx,[rsi].m_radius
        mov r8d,[rsi].m_pos.x
        sub r8d,ecx
        mov r9d,[rsi].m_pos.y
        sub r9d,ecx
        add r8d,2
        add r9d,2
        add ecx,ecx
        sub ecx,4
        GdipFillEllipseI([rdi].m_gm, b, r8d, r9d, ecx, ecx)
        GdipDeleteBrush(b)
        GdipResetPath(p)
    .endf
    GdipDeletePath(p)

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    shr ecx,4
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    sub edx,26
    this.DrawString([rdi].m_gm, ecx, edx,
        "Timer: %d - the default minimum value is 10", [rdi].m_timer)

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    BitBlt([rdi].m_hdc, [rdi].m_rc.left, [rdi].m_rc.top, ecx, edx, [rdi].m_mem, 0, 0, SRCCOPY)

   .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        add [rsi].m_pos.x,[rsi].m_mov.x
        add [rsi].m_pos.y,[rsi].m_mov.y

        mov eax,[rdi].m_rc.right
        sub eax,[rdi].m_rc.left
        mov ecx,[rsi].m_pos.x
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.x <= [rsi].m_radius )
            neg [rsi].m_mov.x
        .endif
        mov eax,[rdi].m_rc.bottom
        sub eax,[rdi].m_rc.top
        mov ecx,[rsi].m_pos.y
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.y <= [rsi].m_radius )
            neg [rsi].m_mov.y
        .endif
    .endf
    .return 1

CApplication::OnTimer endp


; Handles the WM_KEYDOWN message

    assume rcx:ptr CApplication

CApplication::OnKeyDown proc wParam:WPARAM

    .switch edx
    .case VK_DOWN
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            mov eax,[rdx].object.m_mov.x
            .ifs ( eax > 1 || eax < -1 )
                .if ( [rdx].object.m_mov.x < 0 )
                    inc [rdx].object.m_mov.x
                .else
                    dec [rdx].object.m_mov.x
                .endif
                .if ( [rdx].object.m_mov.y < 0 )
                    inc [rdx].object.m_mov.y
                .else
                    dec [rdx].object.m_mov.y
                .endif
            .endif
        .endf
        .endc
    .case VK_UP
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            .if ( [rdx].object.m_mov.x < 30 && [rdx].object.m_mov.x > -30 )
                .if ( [rdx].object.m_mov.x < 0 )
                    dec [rdx].object.m_mov.x
                .else
                    inc [rdx].object.m_mov.x
                .endif
                .if ( [rdx].object.m_mov.y < 0 )
                    dec [rdx].object.m_mov.y
                .else
                    inc [rdx].object.m_mov.y
                .endif
            .endif
        .endf
        .endc
    .case VK_RETURN
        this.InitObjects()
        .endc
    .case VK_NEXT
        .if ( [rcx].m_timer > 10 )
            dec [rcx].m_timer
            SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endif
        .endc
    .case VK_PRIOR
        inc [rcx].m_timer
        SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endc
    .case VK_F11
        .if ( [rcx].m_isFullScreen )
            this.GoPartialScreen()
        .else
            this.GoFullScreen()
        .endif
        .endc
    .endsw
    .return 0

CApplication::OnKeyDown endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

    .if ( [rcx].m_hwnd != NULL )

        DestroyWindow( [rcx].m_hwnd )

        mov rcx,this
        mov [rcx].m_hwnd,NULL
    .endif
    .return 0

CApplication::OnClose endp


; Handles the WM_DESTROY message

CApplication::OnDestroy proc

    PostQuitMessage(0)

    .return 0

CApplication::OnDestroy endp


; Handles the WM_PAINT message

    assume rcx:nothing

CApplication::OnPaint proc uses rdi

  local ps:PAINTSTRUCT

    mov rdi,rcx
    BeginPaint([rdi].m_hwnd, &ps)

    .if ( [rdi].m_isFullScreen == FALSE )

        this.SetFont(NULL, 20.0, 0)
        this.DrawString([rdi].m_g, 50, 32, "CApplication RDRAND")
        this.SetFont(NULL, 12.0, 0)
        this.DrawString([rdi].m_g, 50, 10, "Windows samples")
        this.DrawString([rdi].m_g, 50, 73,
                "This sample use the CApplication class and GDI+\n"
                "Random Count, Speed, Color, and Size")
        mov ecx,[rdi].m_rc.bottom
        add ecx,8
        mov edx,[rdi].m_rc.right
        shr edx,1
        this.DrawString([rdi].m_g, edx, ecx,
                "Use keys UP or DOWN to adjust the speed.\n"
                "Use keys PGUP or PGDN to adjust the timer.\n"
                "Use Enter to reset and F11 to toggle full screen.")
    .endif
    EndPaint([rdi].m_hwnd, &ps)
   .return 1

CApplication::OnPaint endp


CApplication::InitObjects proc uses rsi rdi rbx

    mov rdi,rcx
    mov [rdi].m_count,RangeRand(MAXOBJ, 1)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        mov ecx,[rdi].m_rc.right
        mov edx,[rdi].m_rc.bottom
        cmp ecx,edx
        cmova ecx,edx
        shr ecx,3
        mov [rsi].m_radius,RangeRand(ecx, 8)
        mov [rsi].m_mov.x,RangeRand(10, 1)
        mov [rsi].m_mov.y,RangeRand(10, 1)
        mov [rsi].m_color,RandRGB()
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.x,RangeRand(ecx, [rsi].object.m_radius)
        mov ecx,[rdi].m_rc.bottom
        sub ecx,[rdi].m_rc.top
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.y,RangeRand(ecx, [rsi].object.m_radius)
    .endf
    ret

CApplication::InitObjects endp

; Main Window procedure

WindowProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new Application:ptr CApplication = GetWindowLongPtr(rcx, GWLP_USERDATA)

    .switch ( message )
    .case WM_SIZE
        Application.OnSize(lParam)
        .endc
    .case WM_KEYDOWN
        Application.OnKeyDown(wParam)
        .endc
    .case WM_CLOSE
        Application.OnClose()
        .endc
    .case WM_DESTROY
        Application.OnDestroy()
        .endc
    .case WM_PAINT
        Application.OnPaint()
        .endc
    .case WM_TIMER
        Application.OnTimer()
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .default
        DefWindowProc(hwnd, message, wParam, lParam)
    .endsw
    ret

WindowProc endp


; Creates the application window

CApplication::CreateApplicationWindow proc uses rdi

    mov rdi,rcx

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WindowProc,                    ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        [rdi].m_hInstance,              ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        GetStockObject(BLACK_BRUSH),    ; .hbrBackground
        NULL,                           ; .lpszMenuName
        CLASS_NAME,                     ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .if ( RegisterClassEx( &wc ) == 0 )
        .return E_FAIL
    .endif

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, RESTOREDWINDOWSTYLES,
           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
           NULL, NULL, [rdi].m_hInstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi].m_hwnd,rax
   .return S_OK

CApplication::CreateApplicationWindow endp


; Provides the entry point to the application

    assume rcx:ptr CApplication

CApplication::SetFont proc uses rdi name:ptr wchar_t, size:real4, color:ARGB

    mov rdi,rcx
    .if ( r9d )
        mov [rdi].m_fontcolor,r9d
    .endif
    .if ( rdx )
        .if ( [rdi].m_fontfamily )
            GdipDeleteFontFamily([rdi].m_fontfamily)
        .endif
        GdipCreateFontFamilyFromName(name, NULL, &[rdi].m_fontfamily)
    .endif
    .if ( [rdi].m_font )
        GdipDeleteFont([rdi].m_font)
    .endif
    GdipCreateFont([rdi].m_fontfamily, size, [rdi].m_fontstyle, [rdi].m_fontunit, &[rdi].m_font)
    ret

CApplication::SetFont endp

CApplication::DrawString proc uses rsi rdi rbx gdi:ptr, x:int_t, y:int_t, format:ptr wchar_t, argptr:vararg

 local buffer[512]:wchar_t
 local rc:RectF
 local brush:ptr

    mov rdi,rcx
    cvtsi2ss xmm0,r8d
    movss rc.X,xmm0
    cvtsi2ss xmm0,r9d
    movss rc.Y,xmm0
    cvtsi2ss xmm0,[rdi].m_rect.right
    movss rc.Width,xmm0
    cvtsi2ss xmm0,[rdi].m_rect.bottom
    movss rc.Height,xmm0

    vswprintf(&buffer, format, &argptr)
    GdipCreateSolidFill([rdi].m_fontcolor, &brush)
    GdipDrawString(gdi, &buffer, -1, [rdi].m_font, &rc, [rdi].m_fontformat, brush)
    GdipDeleteBrush(brush)
    ret

CApplication::DrawString endp

CApplication::CApplication proc instance:HINSTANCE

    @ComAlloc(CApplication)

    mov rcx,rax
    mov [rcx].m_hInstance,instance
    mov [rcx].m_timer,10
    mov [rcx].m_fontstyle,FontStyleRegular
    mov [rcx].m_fontunit,UnitPoint
    mov [rcx].m_fontcolor,LightGray
    mov rax,rcx
    ret

CApplication::CApplication endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

_tWinMain endp

    end _tstart
