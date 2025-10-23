
include thread.inc

    .code

BoundRand proc b:uint_t

    mov eax,ecx
    neg eax
    xor edx,edx
    div ecx
    .repeat
        rdrand eax
        .continue(0) .if (eax < edx)
    .until 1
    xor edx,edx
    div ecx
    mov eax,edx
    ret

    endp

RangeRand proc b:uint_t, m:uint_t

    .whiled ( BoundRand(ecx) <= m )
    .endw
    ret

    endp

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

    endp


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

    endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc

    .new hr:HRESULT = this.CreateApplicationWindow()

    .return hr

    endp


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

    endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc

    this.DestroyApplicationWindow()
    ret

    endp


    assume rdi:ptr CApplication


; Thread timer

CApplication::Thread proc uses rdi

    mov rdi,rcx

    .while ( [rdi].m_stop == FALSE )

        .while ( [rdi].m_suspend )

            Sleep(2)
        .endw

        this.OnTimer()
        .if ( [rdi].m_delay )
            Sleep([rdi].m_delay)
        .endif
    .endw
    ret

    endp


; Shows the application window

CApplication::ShowApplicationWindow proc uses rdi

   .new bSucceeded:BOOL = TRUE

    mov rdi,rcx
    .if ( [rdi].m_hwnd == NULL )

        mov bSucceeded,FALSE
    .endif

    .if ( bSucceeded )

        ShowWindow([rdi].m_hwnd, SW_SHOW)
        UpdateWindow([rdi].m_hwnd)

        CreateThread(NULL, NULL, &CApplication_Thread, rdi, NORMAL_PRIORITY_CLASS, NULL)
        CloseHandle(rax)
    .endif

    .return bSucceeded

    endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,rcx
    .if ( [rdi].m_hwnd != NULL )

        lock or [rdi].m_stop,1
        Sleep(2)
        .if ( [rdi].m_bitmap )
            DeleteObject( [rdi].m_bitmap )
        .endif
        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

    endp


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

    endp


; Makes the host window resizable and focusable.

define RESTOREDWINDOWSTYLES WS_SIZEBOX or WS_SYSMENU or WS_CLIPCHILDREN or WS_CAPTION or WS_MAXIMIZEBOX

CApplication::GoPartialScreen proc uses rdi

    mov rdi,rcx
    mov [rdi].m_isFullScreen,FALSE

    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong([rdi].m_hwnd, GWL_STYLE, RESTOREDWINDOWSTYLES)
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST,
        [rdi].m_rect.left, [rdi].m_rect.top, [rdi].m_rect.right, [rdi].m_rect.bottom,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

    endp


    assume rsi:ptr object

CApplication::OnSize proc uses rdi lParam:LPARAM

    mov rdi,rcx
    movzx eax,dx
    shr edx,16
    mov [rdi].m_width,eax
    mov [rdi].m_height,edx

    .if ( [rdi].m_bitmap )

        DeleteObject([rdi].m_bitmap)
        mov [rdi].m_bitmap,NULL
    .endif
    .return 1

    endp


CApplication::OnTimer proc uses rsi rdi rbx

    mov rdi,rcx
   .return 0 .if ( [rdi].m_bitmap == NULL )

   .new hdc:HDC = GetDC([rdi].m_hwnd)
   .new mem:HDC = CreateCompatibleDC(hdc)

    SelectObject(mem, [rdi].m_bitmap)

   .new g:Graphics(mem)
    g.SetSmoothingMode(SmoothingModeHighQuality)
    g.Clear(ColorAlpha(Black, 230))

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

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

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    BitBlt(hdc, [rdi].m_rc.left, [rdi].m_rc.top, ecx, edx, mem, 0, 0, SRCCOPY)
    ReleaseDC([rdi].m_hwnd, hdc)
    DeleteDC(mem)

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

    endp


; Handles the WM_KEYDOWN message

    assume rcx:ptr CApplication

CApplication::OnKeyDown proc wParam:WPARAM

    .switch edx
    .case VK_DOWN
        inc [rcx].m_delay
        .endc
    .case VK_UP
        .if ( [rcx].m_delay )
            dec [rcx].m_delay
        .endif
        .endc
    .case VK_RETURN
        this.InitObjects()
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

    endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

    .if ( [rcx].m_hwnd != NULL )

        DestroyWindow( [rcx].m_hwnd )

        mov rcx,this
        mov [rcx].m_hwnd,NULL
    .endif
    .return 0

    endp


; Handles the WM_DESTROY message

CApplication::OnDestroy proc

    PostQuitMessage(0)

    .return 0

    endp


; Handles the WM_PAINT message

CApplication::OnPaint proc uses rsi rdi rbx

   .new rcClient:RECT
   .new ps:PAINTSTRUCT
   .new height:int_t = 0

    mov rdi,rcx

   .new hdc:HDC = BeginPaint([rdi].m_hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect([rdi].m_hwnd, &rcClient)

    .if ( [rdi].m_isFullScreen == TRUE )

        mov [rdi].m_rc.left,0
        mov [rdi].m_rc.top,0
        mov eax,rcClient.right
        sub eax,rcClient.left
        mov [rdi].m_rc.right,eax
        mov eax,rcClient.bottom
        sub eax,rcClient.top
        mov [rdi].m_rc.bottom,eax

        jmp full_screen
    .endif

    mov [rdi].m_rc.left,50
    mov eax,[rdi].m_width
    sub eax,50
    mov [rdi].m_rc.right,eax

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
        mov [rdi].m_rc.top,eax
        mov eax,[rdi].m_height
        sub eax,100
        mov rcClient.top,eax
        sub eax,16
        mov [rdi].m_rc.bottom,eax
        mov eax,[rdi].m_width
        shr eax,1
        mov rcClient.left,eax

        DrawText(hdc,
            "A) Use keys UP or DOWN for delay.\n"
            "C) Use Enter to reset.", -1, &rcClient,
            DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif

full_screen:

    EndPaint([rdi].m_hwnd, &ps)

    .return 1 .if ( [rdi].m_bitmap )

    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    .ifs ( edx > 100 )
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        .ifs ( ecx > 100 )

            mov hdc,GetDC([rdi].m_hwnd)
            mov ecx,[rdi].m_rc.right
            sub ecx,[rdi].m_rc.left
            mov edx,[rdi].m_rc.bottom
            sub edx,[rdi].m_rc.top
            mov [rdi].m_bitmap,CreateCompatibleBitmap(hdc, ecx, edx)
            ReleaseDC([rdi].m_hwnd, hdc)
            [rdi].InitObjects()
        .endif
    .endif
   .return 1

    endp


CApplication::InitObjects proc uses rsi rdi rbx

    mov rdi,rcx

    lock or [rdi].m_suspend,1
    Sleep(2)

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
    lock and [rdi].m_suspend,0
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

    mov [rdi].m_rect.left,0
    mov [rdi].m_rect.top,0
    mov [rdi].m_rect.right,[rdi].m_width
    mov [rdi].m_rect.bottom,[rdi].m_height

    AdjustWindowRect(&[rdi].m_rect, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,[rdi].m_rect.right
    sub eax,[rdi].m_rect.left
    mov [rdi].m_width,eax

    mov eax,[rdi].m_rect.bottom
    sub eax,[rdi].m_rect.top
    mov [rdi].m_height,eax

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME,
           WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT,
           [rdi].m_width, [rdi].m_height,
           NULL, NULL, [rdi].m_hInstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi].m_hwnd,rax
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
