
; -- CApplication --

; Runs the application

CApplication::Run proc
    .new hr:HRESULT = CreateApplicationWindow()
    .if (SUCCEEDED(hr))
        mov hr,EnterMessageLoop()
    .else
        ErrorMessage(hr, "An error occuring when running the sample" )
    .endif
    .if ( m_hwnd != NULL )
        KillTimer( m_hwnd, ID_TIMER )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    .return( hr )
    endp


CApplication::EnterMessageLoop proc
    .new result:int_t = 0
    .if ( m_hwnd )
        ShowWindow(m_hwnd, SW_SHOWNORMAL)
        UpdateWindow(m_hwnd)
        GetWindowRect(m_hwnd, &m_rect)
        SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        GoFullScreen()
        .new msg:MSG
        .while ( GetMessage( &msg, NULL, 0, 0 ) )
            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw
        mov result,msg.wParam
    .endif
    .return result
    endp


CApplication::OnSize proc width:UINT, height:UINT

    ldr edx,width
    ldr eax,height

    cvtsi2ss xmm0,edx
    cvtsi2ss xmm1,eax
    divss xmm0,400.0
    divss xmm1,400.0
    movss m_DeltaX,xmm0
    movss m_DeltaY,xmm1

    mov m_size.width,edx
    mov m_size.height,eax
    .if ( CreateDeviceResources() )
        .if ( eax != 0x80070578 )
            ErrorMessage(eax, "CreateDeviceResources()" )
        .endif
        .return
    .endif

    .if ( m_pRT )
        ;
        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.
        ;
        m_pRT.Resize(&m_size)
    .endif
    .return 0
    endp


CApplication::OnRender proc
    .new hr:HRESULT = CreateDeviceResources()
    .if (SUCCEEDED(hr))
        .if !( m_pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED )
           .new color:D3DCOLORVALUE
           .new matrix:Matrix3x2F
            color.Init(Black, 1.0)
            matrix.Identity()
            m_pRT.BeginDraw()
            m_pRT.SetTransform(&matrix)
            m_pRT.Clear(&color)
            mov hr,RenderMainContent()
            .if (SUCCEEDED(hr))
                mov hr,m_pRT.EndDraw(NULL, NULL)
                .if (SUCCEEDED(hr))
                    .if (hr == D2DERR_RECREATE_TARGET)
                        SafeRelease(m_pRT)
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr
    endp


SysLinkDlgProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(message)
    .case WM_INITDIALOG
        .new ic:INITCOMMONCONTROLSEX = { INITCOMMONCONTROLSEX, ICC_LINK_CLASS }
        .ifd !InitCommonControlsEx(&ic)
            .return( FALSE )
        .endif
        CreateWindowEx(0, WC_LINK, "Source: <a href=\"" X_LINK "\">x.com/yuruyurau</A>",
            WS_VISIBLE or WS_CHILD, 20, 180, 180, 20,
            hWnd, IDC_SYSLINK, HINST_THISCOMPONENT, NULL)
        .return( TRUE )
    .case WM_COMMAND
    .case WM_CLOSE
        EndDialog(ldr(hWnd), 0)
       .return( TRUE )
    .case WM_NOTIFY
        ldr rdx,wParam
        ldr rcx,lParam
        .if ( edx != IDC_SYSLINK )
            .return( FALSE )
        .endif
        .switch [rcx].NMHDR.code
        .case NM_CLICK
        .case NM_RETURN
            .if ( [rcx].NMLINK.item.iLink == 0 )
                ShellExecute(NULL, L"open", &[rcx].NMLINK.item.szUrl, NULL, NULL, SW_SHOW)
            .endif
        .endsw
    .endsw
    .return( 0 )
    endp


CApplication::OnKeyDown proc wParam:WPARAM

    .switch ldr(wParam)
    .case VK_UP
        mov eax,m_step
        mov ecx,2
        sub eax,5
        cmp eax,ecx
        cmovl eax,ecx
        mov m_step,eax
       .endc
    .case VK_DOWN
        mov eax,m_step
        mov ecx,1000
        add eax,5
        cmp eax,ecx
        cmovg eax,ecx
        mov m_step,eax
       .endc
    .case VK_RETURN
        mov m_intensity,100
        mov m_step,STEPDIV
        mov m_radius,1.0
        mov m_count,MAXOBJ
        SafeRelease(m_brush)
       .endc
    .case VK_RIGHT
        .if ( m_intensity < 255 )
            add m_intensity,5
            SafeRelease(m_brush)
        .endif
        .endc
    .case VK_LEFT
        .if ( m_intensity > 5 )
            sub m_intensity,5
            SafeRelease(m_brush)
        .endif
        .endc
    .case VK_NEXT
        .if ( m_count > 500 )
            sub m_count,100
        .endif
        .endc
    .case VK_END
        movss xmm0,m_radius
        subss xmm0,0.1
        maxss xmm0,0.2
        movss m_radius,xmm0
       .endc
    .case VK_PRIOR
        .if ( m_count < 40000 )
            add m_count,100
        .endif
        .endc
    .case VK_HOME
        movss xmm0,m_radius
        addss xmm0,0.1
        minss xmm0,10.0
        movss m_radius,xmm0
       .endc
    .case VK_F11
        .if ( m_isFullScreen )
            GoPartialScreen()
        .else
            GoFullScreen()
        .endif
        .endc
    .case VK_F1
        DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_HELP), NULL, &SysLinkDlgProc)
    .endsw
    .return( 0 )
    endp


CApplication::OnClose proc
    .if ( m_hwnd != NULL )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    xor eax,eax
    ret
    endp


CApplication::GoFullScreen proc uses rdi

   .new xSpan:int_t
   .new ySpan:int_t
   .new xBorder:int_t
   .new yCaption:int_t
   .new yBorder:int_t
   .new xOrigin:int_t
   .new yOrigin:int_t

    mov m_isFullScreen,TRUE

    SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLongPtr(m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    mov rdi,GetDC(NULL)
    mov xSpan,GetSystemMetrics(SM_CXSCREEN)
    mov ySpan,GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(NULL, rdi)

    ; Calculate the size of system elements.

    mov xBorder,GetSystemMetrics(SM_CXFRAME)
    mov yCaption,GetSystemMetrics(SM_CYCAPTION)
    mov yBorder,GetSystemMetrics(SM_CYFRAME)

    ; Calculate the window origin and span for full-screen mode.

    mov  eax,xBorder
    neg  eax
    mov  xOrigin,eax
    mov  eax,yBorder
    neg  eax
    sub  eax,yCaption
    mov  yOrigin,eax
    imul eax,xBorder,2
    add  xSpan,eax
    imul eax,yBorder,2
    add  eax,yCaption
    add  ySpan,eax

    SetWindowPos(m_hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


CApplication::GoPartialScreen proc
    mov m_isFullScreen,FALSE
    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED); or WS_EX_TRANSPARENT)
    SetWindowLong(m_hwnd, GWL_STYLE, WINDOWSTYLES)
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_rect.left, m_rect.top,
            m_rect.right, m_rect.bottom, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


CApplication::CreateDeviceResources proc

    xor eax,eax
    .if ( rax == m_pRT )

        ; Create a Direct2D render target.

       .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES = {
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            { DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN },
            0.0, 0.0, D2D1_RENDER_TARGET_USAGE_NONE, D2D1_FEATURE_LEVEL_DEFAULT }
       .new hwndRenderTargetProperties:D2D1_HWND_RENDER_TARGET_PROPERTIES = {
            m_hwnd, { m_size.width, m_size.height }, D2D1_PRESENT_OPTIONS_NONE }
        m_pD2DFactory.CreateHwndRenderTarget(&renderTargetProperties, &hwndRenderTargetProperties, &m_pRT)
    .endif
    ret
    endp


CApplication::RenderMainContent proc uses rsi

   .new hr:HRESULT = S_OK
   .new ellipse:D2D1_ELLIPSE

    xor eax,eax
    .ifs ( m_size.width < 100 || m_size.height < 100 )
        .return
    .endif

    ; Create objects

    .if ( m_brush == NULL )

        .new pGradientStops:ptr ID2D1GradientStopCollection
        .new gradientStops[2]:D2D1_GRADIENT_STOP = {
                { 0.0, { 0.8, 0.8, 0.8, 1.0 } },
                { 2.0, { 0.5, 0.5, 0.5, 0.6 } } }
        .new gradisnBrushProperties:D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES = {
                { 250.0, 100.0 }, { 4.0, -4.0 }, 50.0, 50.0 }
        .new brushProperties:D2D1_BRUSH_PROPERTIES = {
                1.0, { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 } }

        mov eax,m_intensity
        _mm_move_ss(gradientStops[D2D1_GRADIENT_STOP].color.a, _mm_div_ss(_mm_cvt_si2ss(xmm0, eax), 255.0))
        mov hr,m_pRT.CreateGradientStopCollection(&gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops)
        .if (SUCCEEDED(hr))
            movss xmm0,m_radius
            movss gradisnBrushProperties.radiusX,xmm0
            movss gradisnBrushProperties.radiusY,xmm0
            mov hr,m_pRT.CreateRadialGradientBrush(&gradisnBrushProperties, &brushProperties, pGradientStops, &m_brush)
            pGradientStops.Release()
        .endif
    .endif

    mov ecx,m_step
    _mm_div_ss(_mm_move_ss(xmm1, M_PI), _mm_cvt_si2ss(xmm2, ecx))
    _mm_move_ss(m_time, _mm_add_ss(_mm_move_ss(xmm0, m_time), xmm1))

    .if (SUCCEEDED(hr))

        ; Draw objects

        .for ( esi = 0 : esi < m_count : esi++ )

            Point(esi)

            _mm_move_ss(ellipse.point.x, _mm_mul_ss(xmm0, m_DeltaX))
            _mm_move_ss(ellipse.point.y, _mm_mul_ss(xmm1, m_DeltaY))
            _mm_move_ss(ellipse.radiusX, _mm_move_ss(xmm0, m_radius))
            _mm_move_ss(ellipse.radiusY, xmm0)
            m_pRT.FillEllipse(&ellipse, m_brush)
        .endf
    .endif
    .return hr
    endp


; Main Window procedure

WindowProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .if ( ldr(message) == WM_CREATE )
        ldr rax,lParam
        SetWindowLongPtr(ldr(hwnd), GWLP_USERDATA, [rax].CREATESTRUCT.lpCreateParams)
       .return( 1 )
    .endif
    .new app:ptr CApplication = GetWindowLongPtr(ldr(hwnd), GWLP_USERDATA)
    .switch ( message )
    .case WM_SIZE
        movzx edx,word ptr lParam
        movzx eax,word ptr lParam[2]
        app.OnSize(edx, eax)
       .endc
    .case WM_LBUTTONDOWN
        ReleaseCapture()
        SendMessageW(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0)
       .return( 0 )
    .case WM_KEYDOWN
        app.OnKeyDown(wParam)
       .endc
    .case WM_RBUTTONDOWN
        app.OnKeyDown(VK_F1)
       .endc
    .case WM_CLOSE
        app.OnClose()
       .endc
    .case WM_DESTROY
        PostQuitMessage( 0 )
       .return( 0 )
    .case WM_TIMER
        app.OnRender()
       .endc
    .case WM_PAINT
    .case WM_DISPLAYCHANGE
       .new ps:PAINTSTRUCT
        BeginPaint(hwnd, &ps)
        EndPaint(hwnd, &ps)
       .return( 0 )
    .case WM_CHAR
       .gotosw(WM_DESTROY) .if ( wParam == VK_ESCAPE )
    .default
        DefWindowProc(hwnd, message, wParam, lParam)
    .endsw
    ret
    endp


; Creates the application window

CApplication::CreateApplicationWindow proc uses rdi

    .new hr:HRESULT = D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory,
            NULL,
            &m_pD2DFactory
            )

    .if (SUCCEEDED(hr))

        .new wc:WNDCLASSEX = {
            WNDCLASSEX,                     ; .cbSize
            CS_HREDRAW or CS_VREDRAW,       ; .style
            &WindowProc,                    ; .lpfnWndProc
            0,                              ; .cbClsExtra
            sizeof(LONG_PTR),               ; .cbWndExtra
            m_hInstance,                    ; .hInstance
            NULL,                           ; .hIcon
            LoadCursor(NULL, IDC_HAND),     ; .hCursor
            GetStockObject(BLACK_BRUSH),    ; .hbrBackground
            NULL,                           ; .lpszMenuName
            CLASS_NAME,                     ; .lpszClassName
            NULL                            ; .hIconSm
            }

        mov edi,RegisterClassEx(&wc)

        ;
        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.
        ;

       .new dpiX:float, dpiY:float
        m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

        movss       xmm0,dpiX
        mulss       xmm0,640.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   ecx,xmm0
        sub         ecx,eax
        neg         ecx

        movss       xmm0,dpiY
        mulss       xmm0,480.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   edx,xmm0
        sub         edx,eax
        neg         edx

       .new rc:RECT = { 100, 100, ecx, edx }
        AdjustWindowRect(&rc, WINDOWSTYLES, FALSE)
        mov hr,E_UNEXPECTED
        .if CreateWindowEx(0, CLASS_NAME, X_LINK, WINDOWSTYLES,
                rc.left, rc.top, rc.right, rc.bottom, NULL, NULL, m_hInstance, rbx)
            mov m_hwnd,rax
            mov hr,S_OK
        .endif
    .endif
    .return( hr )
    endp


CApplication::ErrorMessage proc hr:HRESULT, format:LPTSTR
  local message[512]:wchar_t, buffer[16]:wchar_t, szMessage:LPTSTR
    ldr edx,hr
    .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
        mov hr,HRESULT_CODE(edx)
    .endif
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &szMessage, 0, NULL)
    _swprintf(&message, "%s\n\nError code: %#X\n\n%s", format, hr, szMessage)
    MessageBox(NULL, &message, "Error", MB_OK or MB_ICONERROR)
    LocalFree(szMessage)
   .return hr
    endp


CApplication::Release proc
    SafeRelease(m_brush)
    SafeRelease(m_pRT)
    SafeRelease(m_pD2DFactory)
    free(rbx)
    ret
    endp


CApplication::CApplication proc hInstance:HINSTANCE
    .if @ComAlloc(CApplication)
        mov rbx,rax
        mov rcx,hInstance
        mov m_hInstance,rcx
        mov m_timer,TIMER
        mov m_intensity,100
        mov m_step,STEPDIV
        mov m_radius,1.0
        mov m_count,MAXOBJ
    .endif
    ret
    endp


_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)
    .new hr:HRESULT = CoInitialize(NULL)
    .if (SUCCEEDED(hr))
       .new app:ptr CApplication(hInstance)
        mov hr,app.Run()
        app.Release()
        CoUninitialize()
    .endif
    .return( hr )
    endp

    RCBEGIN
    RCTYPES 1
    RCENTRY RT_DIALOG
    RCENUMN 1
    RCENUMX IDD_HELP
    RCLANGX LANGID_US
    STYLE equ DS_SETFONT or DS_MODALFRAME or DS_FIXEDSYS or WS_POPUP or WS_CAPTION or WS_SYSMENU
    DIALOGEX STYLE, 4, 100, 100, 160, 130
    CAPTION "Windows samples"
    FONT 12, "MS Shell Dlg", 400, 0, 1
    LTEXT "Funcion Keys",IDC_STATIC,10,10,50,12
    LTEXT "Enter\nUp/Down\nLeft/Right\nPgUp/PgDn\nHome/End\nF11",IDC_STATIC,15,20,40,60
    LTEXT "Default\nSpeed\nIntensity\nPoint Count\nPoint size\nToggle full screen",IDC_STATIC,70,20,60,60
    DEFPUSHBUTTON "OK",IDOK,60,100,39,12
    DLGEND
    RCEND

    end _tstart
