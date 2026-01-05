
include rdrand.inc

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define ID_TIMER     1

   .code

    assume class:rbx


CApplication::BoundRand proc b:uint_t

    ldr ecx,b
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
    endp


CApplication::RangeRand proc b:uint_t, m:uint_t
    .whiled ( BoundRand(b) <= m )
    .endw
    ret
    endp


CApplication::RandRGB proc uses rsi

    mov esi,BoundRand(0xFF)
    shl esi,8
    BoundRand(0xFF)
    or  esi,eax
    shl esi,8
    BoundRand(0xFF)
    or  eax,esi
    or  eax,0xFF000000
    ret
    endp


; Runs the application

CApplication::Run proc

    .new hr:HRESULT = S_OK
    .new gdiplus:GdiPlus()
    .if SUCCEEDED(BeforeEnteringMessageLoop())
        mov hr,EnterMessageLoop()
    .else
        MessageBox(NULL, "An error occuring when running the sample", NULL, MB_OK)
    .endif
    AfterLeavingMessageLoop()
    mov eax,hr
    ret
    endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc
    CreateApplicationWindow()
    ret
    endp


; Message loop

CApplication::EnterMessageLoop proc

    .new msg:MSG

    .if ( ShowApplicationWindow() )

        .while ( GetMessage( &msg, NULL, 0, 0 ) )

            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw
        mov rax,msg.wParam
    .endif
    ret
    endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc
    DestroyApplicationWindow()
    ret
    endp


; Shows the application window

CApplication::ShowApplicationWindow proc
    mov rax,m_hwnd
    .if ( rax )
        ShowWindow(m_hwnd, SW_SHOW)
        UpdateWindow(m_hwnd)
        SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        GetWindowRect(m_hwnd, &m_rect)
        GdipCreateStringFormat(StringFormatFlagsNoWrap, LANG_NEUTRAL, &m_fontformat)
        SetFont(IDS_FONT_TYPEFACE, 12.0, Gray)
        GoPartialScreen()
        mov eax,TRUE
    .endif
    ret
    endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc

    .if ( m_hwnd != NULL )
        .if ( m_g )
            GdipDeleteGraphics(m_g)
        .endif
        .if ( m_gm )
            GdipDeleteGraphics(m_gm)
        .endif
        .if ( m_mem )
            DeleteDC(m_mem)
        .endif
        .if ( m_hdc )
            ReleaseDC(m_hwnd, m_hdc)
        .endif
        .if ( m_font )
            GdipDeleteFont(m_font)
        .endif
        .if ( m_fontfamily )
            GdipDeleteFontFamily(m_fontfamily)
        .endif
        .if ( m_fontformat )
            GdipDeleteStringFormat(m_fontformat)
        .endif
        .if ( m_bitmap )
            DeleteObject( m_bitmap )
        .endif
        KillTimer( m_hwnd, ID_TIMER )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    ret
    endp


; Makes the host window full-screen by placing non-client elements outside the display.

CApplication::GoFullScreen proc

    mov m_isFullScreen,TRUE

    ; The window must be styled as layered for proper rendering.
    ; It is styled as transparent so that it does not capture mouse clicks.

    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED or WS_EX_TRANSPARENT)

    ; Give the window a system menu so it can be closed on the taskbar.

    SetWindowLong(m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

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
    SetWindowPos(m_hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


; Makes the host window resizable and focusable.

CApplication::GoPartialScreen proc

    mov m_isFullScreen,FALSE
    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong(m_hwnd, GWL_STYLE, RESTOREDWINDOWSTYLES)
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


CApplication::OnSize proc lParam:LPARAM

    movzx eax,dx
    shr edx,16
    mov m_rc.top,0
    mov m_rc.left,0
    mov m_rc.right,eax
    mov m_rc.bottom,edx

    .if ( m_isFullScreen == FALSE )
        mov m_rc.top,130
        mov m_rc.left,50
        sub m_rc.right,50
        sub m_rc.bottom,100
    .endif
    .if ( m_mem )
        DeleteDC(m_mem)
    .endif
    .if ( m_hdc )
        ReleaseDC(m_hwnd, m_hdc)
    .endif
    .if ( m_bitmap )
        DeleteObject(m_bitmap)
        mov m_bitmap,NULL
    .endif
    mov m_hdc,GetDC(m_hwnd)
    mov m_mem,CreateCompatibleDC(m_hdc)
    .if ( m_g )
        GdipDeleteGraphics(m_g)
    .endif
    .if ( m_gm )
        GdipDeleteGraphics(m_gm)
    .endif
    GdipCreateFromHDC(m_hdc, &m_g)
    mov edx,m_rc.bottom
    sub edx,m_rc.top
    .ifs ( edx > 100 )
        mov ecx,m_rc.right
        sub ecx,m_rc.left
        .ifs ( ecx > 100 )
            mov m_bitmap,CreateCompatibleBitmap(m_hdc, ecx, edx)
            InitObjects()
            SelectObject(m_mem, m_bitmap)
            GdipCreateFromHDC(m_mem, &m_gm)
            GdipSetSmoothingMode(m_gm, SmoothingModeHighQuality)
        .endif
    .endif
    .return 1
    endp


    assume rsi:ptr object

CApplication::OnTimer proc uses rsi

   .return 0 .if ( m_bitmap == NULL )

    GdipGraphicsClear(m_gm, ColorAlpha(Black, 230))

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)
   .new p:ptr
   .new b:ptr

    GdipCreatePath(FillModeAlternate, &p)

    .for ( rsi = &m_obj, edi = 0: edi < m_count: edi++, rsi += sizeof(object) )

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
        GdipFillEllipseI(m_gm, b, r8d, r9d, ecx, ecx)
        GdipDeleteBrush(b)
        GdipResetPath(p)
    .endf
    GdipDeletePath(p)

    mov ecx,m_rc.right
    sub ecx,m_rc.left
    shr ecx,4
    mov edx,m_rc.bottom
    sub edx,m_rc.top
    sub edx,26
    DrawString(m_gm, ecx, edx, "Timer: %d - the default minimum value is 10", m_timer)

    mov ecx,m_rc.right
    sub ecx,m_rc.left
    mov edx,m_rc.bottom
    sub edx,m_rc.top
    BitBlt(m_hdc, m_rc.left, m_rc.top, ecx, edx, m_mem, 0, 0, SRCCOPY)

   .for ( rsi = &m_obj, edi = 0: edi < m_count: edi++, rsi += sizeof(object) )

        add [rsi].m_pos.x,[rsi].m_mov.x
        add [rsi].m_pos.y,[rsi].m_mov.y

        mov eax,m_rc.right
        sub eax,m_rc.left
        mov ecx,[rsi].m_pos.x
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.x <= [rsi].m_radius )
            neg [rsi].m_mov.x
        .endif
        mov eax,m_rc.bottom
        sub eax,m_rc.top
        mov ecx,[rsi].m_pos.y
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.y <= [rsi].m_radius )
            neg [rsi].m_mov.y
        .endif
    .endf
    .return 1

    endp


; Handles the WM_KEYDOWN message

CApplication::OnKeyDown proc wParam:WPARAM

    .switch edx
    .case VK_DOWN
        .for ( rdx = &m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
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
        .for ( rdx = &m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
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
        InitObjects()
       .endc
    .case VK_NEXT
        .if ( m_timer > 10 )
            dec m_timer
            SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        .endif
        .endc
    .case VK_PRIOR
        inc m_timer
        SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        .endc
    .case VK_F11
        .if ( m_isFullScreen )
            GoPartialScreen()
        .else
            GoFullScreen()
        .endif
        .endc
    .endsw
    .return 0
    endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

    .if ( m_hwnd != NULL )

        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    .return 0
    endp


; Handles the WM_DESTROY message

CApplication::OnDestroy proc
    PostQuitMessage(0)
    .return 0
    endp


; Handles the WM_PAINT message

CApplication::OnPaint proc

  local ps:PAINTSTRUCT

    BeginPaint(m_hwnd, &ps)

    .if ( m_isFullScreen == FALSE )

        this.SetFont(NULL, 20.0, 0)
        this.DrawString(m_g, 50, 32, "CApplication RDRAND")
        this.SetFont(NULL, 12.0, 0)
        this.DrawString(m_g, 50, 10, "Windows samples")
        this.DrawString(m_g, 50, 73,
                "This sample use the CApplication class and GDI+\n"
                "Random Count, Speed, Color, and Size")
        mov ecx,m_rc.bottom
        add ecx,8
        mov edx,m_rc.right
        shr edx,1
        this.DrawString(m_g, edx, ecx,
                "Use keys UP or DOWN to adjust the speed.\n"
                "Use keys PGUP or PGDN to adjust the timer.\n"
                "Use Enter to reset and F11 to toggle full screen.")
    .endif
    EndPaint(m_hwnd, &ps)
    .return 1
    endp


CApplication::InitObjects proc uses rsi rdi

    mov m_count,RangeRand(MAXOBJ, 1)

    .for ( rsi = &m_obj, edi = 0: edi < m_count: edi++, rsi += sizeof(object) )

        mov ecx,m_rc.right
        mov edx,m_rc.bottom
        cmp ecx,edx
        cmova ecx,edx
        shr ecx,3
        mov [rsi].m_radius,RangeRand(ecx, 8)
        mov [rsi].m_mov.x,RangeRand(10, 1)
        mov [rsi].m_mov.y,RangeRand(10, 1)
        mov [rsi].m_color,RandRGB()
        mov ecx,m_rc.right
        sub ecx,m_rc.left
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.x,RangeRand(ecx, [rsi].object.m_radius)
        mov ecx,m_rc.bottom
        sub ecx,m_rc.top
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.y,RangeRand(ecx, [rsi].object.m_radius)
    .endf
    ret
    endp


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

    endp


; Creates the application window

CApplication::CreateApplicationWindow proc

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WindowProc,                    ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        m_hInstance,                    ; .hInstance
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
    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, RESTOREDWINDOWSTYLES, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, m_hInstance, rbx) == NULL
        .return E_UNEXPECTED
    .endif
    mov m_hwnd,rax
    xor eax,eax
    ret
    endp


; Provides the entry point to the application

CApplication::SetFont proc name:ptr wchar_t, size:real4, color:ARGB

    .if ( r9d )
        mov m_fontcolor,r9d
    .endif
    .if ( rdx )
        .if ( m_fontfamily )
            GdipDeleteFontFamily(m_fontfamily)
        .endif
        GdipCreateFontFamilyFromName(name, NULL, &m_fontfamily)
    .endif
    .if ( m_font )
        GdipDeleteFont(m_font)
    .endif
    GdipCreateFont(m_fontfamily, size, m_fontstyle, m_fontunit, &m_font)
    ret
    endp


CApplication::DrawString proc gdi:ptr, x:int_t, y:int_t, format:ptr wchar_t, argptr:vararg

    local buffer[512]:wchar_t
    local rc:RectF
    local brush:ptr

    cvtsi2ss xmm0,r8d
    movss rc.X,xmm0
    cvtsi2ss xmm0,r9d
    movss rc.Y,xmm0
    cvtsi2ss xmm0,m_rect.right
    movss rc.Width,xmm0
    cvtsi2ss xmm0,m_rect.bottom
    movss rc.Height,xmm0

    vswprintf(&buffer, format, &argptr)
    GdipCreateSolidFill(m_fontcolor, &brush)
    GdipDrawString(gdi, &buffer, -1, m_font, &rc, m_fontformat, brush)
    GdipDeleteBrush(brush)
    ret
    endp


CApplication::CApplication proc instance:HINSTANCE

    mov rbx,@ComAlloc(CApplication)
    mov m_hInstance,instance
    mov m_timer,10
    mov m_fontstyle,FontStyleRegular
    mov m_fontunit,UnitPoint
    mov m_fontcolor,LightGray
    mov rax,rbx
    ret
    endp


_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

    endp

    end _tstart
