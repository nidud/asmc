
include thread.inc

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


; Thread timer

CApplication::Thread proc

    .while ( m_stop == FALSE )

        .while ( m_suspend )
            Sleep(2)
        .endw
        OnTimer()
        .if ( m_delay )
            Sleep(m_delay)
        .endif
    .endw
    ret
    endp


; Shows the application window

CApplication::ShowApplicationWindow proc

    mov rax,m_hwnd
    .if ( rax )
        ShowWindow(m_hwnd, SW_SHOW)
        UpdateWindow(m_hwnd)
        CloseHandle(CreateThread(NULL, NULL, &CApplication_Thread, rbx, NORMAL_PRIORITY_CLASS, NULL))
    .endif
    ret
    endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc

    .if ( m_hwnd != NULL )

        lock or m_stop,1
        Sleep(2)
        .if ( m_bitmap )
            DeleteObject( m_bitmap )
        .endif
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

define RESTOREDWINDOWSTYLES WS_SIZEBOX or WS_SYSMENU or WS_CLIPCHILDREN or WS_CAPTION or WS_MAXIMIZEBOX

CApplication::GoPartialScreen proc

    mov m_isFullScreen,FALSE
    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong(m_hwnd, GWL_STYLE, RESTOREDWINDOWSTYLES)
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


CApplication::OnSize proc lParam:LPARAM

    movzx eax,dx
    shr edx,16
    mov m_width,eax
    mov m_height,edx
    .if ( m_bitmap )

        DeleteObject(m_bitmap)
        mov m_bitmap,NULL
    .endif
    .return 1
    endp

    assume rsi:ptr object

CApplication::OnTimer proc uses rsi rdi

   .return 0 .if ( m_bitmap == NULL )

   .new hdc:HDC = GetDC(m_hwnd)
   .new mem:HDC = CreateCompatibleDC(hdc)

    SelectObject(mem, m_bitmap)

   .new g:Graphics(mem)
    g.SetSmoothingMode(SmoothingModeHighQuality)
    g.Clear(ColorAlpha(Black, 230))

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)

    .for ( rsi = &m_obj, edi = 0: edi < m_count: edi++, rsi += sizeof(object) )

       .new p:GraphicsPath()
        mov ecx,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,ecx
        mov r8d,[rsi].m_pos.y
        sub r8d,ecx
        add ecx,ecx
        p.AddEllipse(edx, r8d, ecx, ecx)

       .new b:PathGradientBrush(&p)
        b.SetCenterColor([rsi].m_color)
        b.SetSurroundColors(&FullTranslucent, &count)

        mov eax,[rsi].m_radius
        mov r8d,[rsi].m_pos.x
        sub r8d,eax
        mov r9d,[rsi].m_pos.y
        sub r9d,eax
        add r8d,2
        add r9d,2
        add eax,eax
        sub eax,4
        g.FillEllipse(&b, r8d, r9d, eax, eax)
        b.Release()
        p.Release()
    .endf

    g.Release()

    mov ecx,m_rc.right
    sub ecx,m_rc.left
    mov edx,m_rc.bottom
    sub edx,m_rc.top
    BitBlt(hdc, m_rc.left, m_rc.top, ecx, edx, mem, 0, 0, SRCCOPY)
    ReleaseDC(m_hwnd, hdc)
    DeleteDC(mem)

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
        inc m_delay
        .endc
    .case VK_UP
        .if ( m_delay )
            dec m_delay
        .endif
        .endc
    .case VK_RETURN
        InitObjects()
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

   .new rcClient:RECT
   .new ps:PAINTSTRUCT
   .new height:int_t = 0

   .new hdc:HDC = BeginPaint(m_hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect(m_hwnd, &rcClient)

    .if ( m_isFullScreen == TRUE )

        mov m_rc.left,0
        mov m_rc.top,0
        mov eax,rcClient.right
        sub eax,rcClient.left
        mov m_rc.right,eax
        mov eax,rcClient.bottom
        sub eax,rcClient.top
        mov m_rc.bottom,eax
        jmp full_screen
    .endif

    mov m_rc.left,50
    mov eax,m_width
    sub eax,50
    mov m_rc.right,eax

    ; Logo

    xor ecx,ecx
    .new hlogo:HFONT = CreateFont(IDS_FONT_HEIGHT_LOGO, ecx, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Logo Font and Size

    .if ( hlogo != NULL )

       .new hOldFont:HFONT = SelectObject(hdc, hlogo)

        SetTextColor(hdc, GetSysColor(COLOR_GRAYTEXT))
        SetBkMode(hdc, TRANSPARENT)

        mov rcClient.top,10
        mov rcClient.left,50
        mov height,DrawText(hdc, "Windows samples", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hlogo)
    .endif

    ; Title

    xor ecx,ecx
   .new htitle:HFONT = CreateFont(IDS_FONT_HEIGHT_TITLE, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Title Font and Size

    .if (htitle != NULL)

       .new hOldFont:HFONT = SelectObject(hdc, htitle)

        mov eax,height
        add eax,10
        mov rcClient.top,eax
        mov rcClient.left,50

        mov height,DrawText(hdc, "CApplication Class :: Thread", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(htitle)
    .endif

    ; Description

   .new hdescription:HFONT

    xor ecx,ecx
    mov hdescription,CreateFont(IDS_FONT_HEIGHT_DESCRIPTION, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx,
            IDS_FONT_TYPEFACE) ; Description Font and Size

    .if (hdescription != NULL)

       .new hOldFont:HFONT = SelectObject(hdc, hdescription)

        mov eax,height
        add eax,40
        mov rcClient.top,eax
        mov rcClient.left,50

        DrawText(hdc,
            "This sample use the CApplication class and GDI+\n"
            "Random Count, Speed, Color, and Size",
            -1, &rcClient, DT_WORDBREAK)

        add eax,rcClient.top
        add eax,6
        mov m_rc.top,eax
        mov eax,m_height
        sub eax,100
        mov rcClient.top,eax
        sub eax,16
        mov m_rc.bottom,eax
        mov eax,m_width
        shr eax,1
        mov rcClient.left,eax

        DrawText(hdc,
            "A) Use keys UP or DOWN for delay.\n"
            "C) Use Enter to reset.", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif

full_screen:

    EndPaint(m_hwnd, &ps)

    .return 1 .if ( m_bitmap )

    mov edx,m_rc.bottom
    sub edx,m_rc.top
    .ifs ( edx > 100 )
        mov ecx,m_rc.right
        sub ecx,m_rc.left
        .ifs ( ecx > 100 )

            mov hdc,GetDC(m_hwnd)
            mov ecx,m_rc.right
            sub ecx,m_rc.left
            mov edx,m_rc.bottom
            sub edx,m_rc.top
            mov m_bitmap,CreateCompatibleBitmap(hdc, ecx, edx)
            ReleaseDC(m_hwnd, hdc)
            InitObjects()
        .endif
    .endif
   .return 1

    endp


CApplication::InitObjects proc uses rsi rdi

    lock or m_suspend,1
    Sleep(2)

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
    lock and m_suspend,0
    ret
    endp


; Main Window procedure

WindowProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new app:ptr CApplication = GetWindowLongPtr(rcx, GWLP_USERDATA)

    .switch ( message )
    .case WM_SIZE
        app.OnSize(lParam)
        .endc
    .case WM_KEYDOWN
        app.OnKeyDown(wParam)
        .endc
    .case WM_CLOSE
        app.OnClose()
        .endc
    .case WM_DESTROY
        app.OnDestroy()
        .endc
    .case WM_PAINT
        app.OnPaint()
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

    mov m_rect.left,0
    mov m_rect.top,0
    mov m_rect.right,m_width
    mov m_rect.bottom,m_height

    AdjustWindowRect(&m_rect, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,m_rect.right
    sub eax,m_rect.left
    mov m_width,eax

    mov eax,m_rect.bottom
    sub eax,m_rect.top
    mov m_height,eax

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, NULL, NULL, m_hInstance, rbx) == NULL
        .return E_UNEXPECTED
    .endif
    mov m_hwnd,rax
    .return S_OK
    endp


; Provides the entry point to the application

CApplication::CApplication proc instance:HINSTANCE

    @ComAlloc(CApplication)

    mov rcx,instance
    mov [rax].CApplication.m_hInstance,rcx
    mov [rax].CApplication.m_width,900
    mov [rax].CApplication.m_height,600
    ret

    endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

    endp

    end _tstart
