
include CApplication.inc

    .code

    assume class:rbx

; -- Bounce Class --

Bounce::Bounce proc
    @ComAlloc(Bounce)
    ret
    endp


Bounce::Release proc
    .while ( rbx )
        SafeRelease(m_brush)
        mov rcx,rbx
        mov rbx,m_next
        free(rcx)
    .endw
    ret
    endp


Bounce::New proc
    .while ( m_next )
        mov rbx,m_next
    .endw
    mov m_next,Bounce()
    ret
    endp


Bounce::Up proc
    .while ( rbx )
        .if ( m_mov.x < 30 && m_mov.x > -30 && m_mov.y < 30 && m_mov.y > -30 )
            .if ( m_mov.x < 0 )
                dec m_mov.x
            .else
                inc m_mov.x
            .endif
            .if ( m_mov.y < 0 )
                dec m_mov.y
            .else
                inc m_mov.y
            .endif
        .endif
        mov rbx,m_next
    .endw
    ret
    endp


Bounce::Down proc
    .while ( rbx )
        .if ( ( m_mov.x > 1 || m_mov.x < -1 ) && ( m_mov.y > 1 || m_mov.y < -1 ) )
            .if ( m_mov.x < 0 )
                inc m_mov.x
            .else
                dec m_mov.x
            .endif
            .if ( m_mov.y < 0 )
                inc m_mov.y
            .else
                dec m_mov.y
            .endif
        .endif
        mov rbx,m_next
    .endw
    ret
    endp


; -- CApplication --

; Runs the application

CApplication::Run proc
    .new hr:HRESULT = 0
    .if (SUCCEEDED(BeforeEnteringMessageLoop()))
        mov hr,EnterMessageLoop()
    .else
        ErrorMessage(hr, "An error occuring when running the sample" )
    .endif
    AfterLeavingMessageLoop()
    .return( hr )
    endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc
    CreateApplicationWindow()
    ret
    endp


; Message loop

CApplication::EnterMessageLoop proc
    .new result:int_t = 0
    .if ( ShowApplicationWindow() )
        .new msg:MSG
        .while ( GetMessage( &msg, NULL, 0, 0 ) )
            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw
        mov result,msg.wParam
    .endif
    .return result
    endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc
    DestroyApplicationWindow()
    ret
    endp


; Shows the application window

CApplication::ShowApplicationWindow proc
    mov rax,m_hwnd
    .if (  rax )
        ShowWindow(m_hwnd, SW_SHOWNORMAL)
        UpdateWindow(m_hwnd)
        GetWindowRect(m_hwnd, &m_rect)
        SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        mov eax,TRUE
    .endif
    ret
    endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc
    .if ( m_hwnd != NULL )
        KillTimer( m_hwnd, ID_TIMER )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    ret
    endp


CApplication::OnSize proc width:UINT, height:UINT

    ldr edx,width
    ldr eax,height

    mov m_size.width,edx
    mov m_size.height,eax
    mov m_rc.top,0
    mov m_rc.left,0
    mov m_rc.right,edx
    mov m_rc.bottom,eax

    .if ( m_isFullScreen == FALSE )

        mov m_rc.top,130
        mov m_rc.left,50
        sub m_rc.right,50
        sub m_rc.bottom,100
    .endif
    .if ( CreateDeviceResources() )
        .return ErrorMessage(eax, "CreateDeviceResources()" )
    .endif

    .if ( m_pRT )

        ;
        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.
        ;

        m_pRT.Resize(&m_size)
        InitObjects()
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
                mov hr,RenderTextInfo()
                .if (SUCCEEDED(hr))
                    mov hr,m_pRT.EndDraw(NULL, NULL)
                    .if (SUCCEEDED(hr))
                        .if (hr == D2DERR_RECREATE_TARGET)
                            DiscardDeviceResources()
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr
    endp


CApplication::OnKeyDown proc wParam:WPARAM

    .switch ldr(wParam)
    .case VK_SPACE
        .endc
    .case VK_DOWN
        m_obj.Down()
       .endc
    .case VK_UP
        m_obj.Up()
       .endc
    .case VK_F3
        .if ( m_rand < 2 )
            inc m_rand
        .else
            mov m_rand,0
        .endif
    .case VK_RETURN
        InitObjects()
       .endc
    .case VK_RIGHT
        inc m_intensity
       .endc
    .case VK_LEFT
        .if ( m_intensity )
            dec m_intensity
        .endif
        .endc
    .case VK_NEXT
        inc m_timer
        SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
       .endc
    .case VK_PRIOR
        .if ( m_timer )
            dec m_timer
            SetTimer(m_hwnd, ID_TIMER, m_timer, NULL)
        .endif
        .endc
    .case VK_F11
        .if ( m_isFullScreen )
            GoPartialScreen()
        .else
            GoFullScreen()
        .endif
        .endc
    .case VK_F1
        MessageBox(NULL,
                   "Enter\t\tRecalculate\n"
                   "F3\t\tToggle rand-type\n"
                   "F11\t\tToggle full screen\n"
                   "Up/Down\tSpeed\n"
                   "Left/Right\tIntensity\n"
                   "PGUP/PGDN\tTimer\n",
                   "Function Keys", MB_OK)
    .endsw
    .return 0
    endp


CApplication::OnClose proc
    .if ( m_hwnd != NULL )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    xor eax,eax
    ret
    endp


CApplication::OnDestroy proc
    PostQuitMessage(0)
    xor eax,eax
    ret
    endp


; Handles the WM_PAINT message

    assume rsi:pball_t

CApplication::InitObjects proc uses rsi rdi

    SafeRelease(m_obj)

    mov eax,m_rc.bottom
    sub eax,m_rc.top
    mov ecx,m_rc.right
    sub ecx,m_rc.left

    .ifs ( ecx < 100 || eax < 100 )

        mov m_count,0
       .return 0
    .endif

    mov m_count,RangeRand(MAXOBJ, 1)
    mov m_obj,Bounce()

    .for ( rsi = rax, edi = 0 : rsi && edi < m_count : edi++, rsi = [rsi].New() )

        mov     ecx,m_rc.right
        mov     edx,m_rc.bottom
        cmp     ecx,edx
        cmova   ecx,edx
        shr     ecx,3
        mov     [rsi].m_radius,RangeRand(ecx, 8)
        mov     [rsi].m_mov.x,RangeRand(9, 1)
        mov     [rsi].m_mov.y,RangeRand(9, 1)
        mov     ecx,m_rc.right
        sub     ecx,m_rc.left
        sub     ecx,[rsi].m_radius
        mov     [rsi].m_pos.x,RangeRand(ecx, [rsi].m_radius)
        mov     ecx,m_rc.bottom
        sub     ecx,m_rc.top
        sub     ecx,[rsi].m_radius
        mov     [rsi].m_pos.y,RangeRand(ecx, [rsi].m_radius)
        RandRGB(&[rsi].m_color, m_intensity)
    .endf
    .return 0
    endp

    assume rsi:nothing


CApplication::GoFullScreen proc uses rdi

   .new xSpan:int_t
   .new ySpan:int_t
   .new xBorder:int_t
   .new yCaption:int_t
   .new yBorder:int_t
   .new xOrigin:int_t
   .new yOrigin:int_t

    mov m_isFullScreen,TRUE

    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED); or WS_EX_TRANSPARENT)
    SetWindowLong(m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    mov rdi,GetDC(NULL)
    mov xSpan,GetSystemMetrics(SM_CXSCREEN)
    mov ySpan,GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(NULL, rdi)

    ; Calculate the size of system elements.

    mov xBorder,GetSystemMetrics(SM_CXFRAME)
    mov yCaption,GetSystemMetrics(SM_CYCAPTION)
    mov yBorder,GetSystemMetrics(SM_CYFRAME)

    ; Calculate the window origin and span for full-screen mode.

    mov     eax,xBorder
    neg     eax
    mov     xOrigin,eax
    mov     eax,yBorder
    neg     eax
    sub     eax,yCaption
    mov     yOrigin,eax
    imul    eax,xBorder,2
    add     xSpan,eax
    imul    eax,yBorder,2
    add     eax,yCaption
    add     ySpan,eax

    SetWindowPos(m_hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


; Makes the host window resizable and focusable.

CApplication::GoPartialScreen proc

    mov m_isFullScreen,FALSE
    SetWindowLong(m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED); or WS_EX_TRANSPARENT)
    SetWindowLong(m_hwnd, GWL_STYLE, WINDOWSTYLES)
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_rect.left, m_rect.top,
            m_rect.right, m_rect.bottom, SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret
    endp


;
; CreateDeviceIndependentResources
;
;  This method is used to create resources which are not bound
;  to any device. Their lifetime effectively extends for the
;  duration of the app. These resources include the D2D,
;  DWrite, and WIC factories; and a DWrite Text Format object
;  (used for identifying particular font characteristics) and
;  a D2D geometry.
;

CApplication::CreateDeviceIndependentResources proc

    ; Create the Direct2D factory.

    .new hr:HRESULT = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &IID_ID2D1Factory, NULL, &m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory, &m_pDWriteFactory)
    .endif


    .if (SUCCEEDED(hr))

        ; Create a DirectWrite text format object.

        mov hr,m_pDWriteFactory.CreateTextFormat(IDS_TEXTFONT, NULL, DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0, "", &m_pTextFont)

        .if (SUCCEEDED(hr))
            mov hr,m_pDWriteFactory.CreateTextFormat(IDS_TEXTFONT, NULL, DWRITE_FONT_WEIGHT_NORMAL,
                    DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30.0, "", &m_pTextFont2)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,m_pTextFont.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP)
            mov hr,m_pTextFont2.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP)
        .endif
    .endif

    .if (SUCCEEDED(hr))
        mov hr,m_pDWriteFactory.CreateTextFormat(IDS_MONOFONT, NULL, DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0, "", &m_pMonoFont)
    .endif
    .return hr
    endp


;
;  CreateDeviceResources
;
;  This method creates resources which are bound to a particular
;  D3D device. It's all centralized here, in case the resources
;  need to be recreated in case of D3D device loss (eg. display
;  change, remoting, removal of video card, etc).
;

CApplication::CreateDeviceResources proc

   .new hr:HRESULT = S_OK

    .if ( !m_pRT )

        ; Create a Direct2D render target.

       .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES = {
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                { DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN },
                0.0, 0.0,
                D2D1_RENDER_TARGET_USAGE_NONE,
                D2D1_FEATURE_LEVEL_DEFAULT
                }

       .new hwndRenderTargetProperties:D2D1_HWND_RENDER_TARGET_PROPERTIES = {
                m_hwnd,
                { m_size.width, m_size.height },
                D2D1_PRESENT_OPTIONS_NONE
                }

        mov hr,m_pD2DFactory.CreateHwndRenderTarget(
                &renderTargetProperties,
                &hwndRenderTargetProperties,
                &m_pRT
                )

        .if (SUCCEEDED(hr))

            ; Create brushes.

           .new color:D3DCOLORVALUE(White, 1.0)
            mov hr,m_pRT.CreateSolidColorBrush(&color, NULL, &m_pSolidColorBrush)
        .endif
    .endif
    .return hr
    endp


    assume rsi:pball_t

CApplication::RenderMainContent proc uses rsi

   .new hr:HRESULT = S_OK

    xor eax,eax
    mov ecx,m_rc.bottom
    sub ecx,m_rc.top
    .return .ifs ( ecx < 100 )
    mov ecx,m_rc.right
    sub ecx,m_rc.left
    .return .ifs ( ecx < 100 )

    .new ellipse:D2D1_ELLIPSE
    .new brush:ptr ID2D1RadialGradientBrush
    .new center:D2D1_POINT_2F

    .for ( rsi = m_obj : rsi : rsi = [rsi].m_next )

        mov brush,[rsi].m_brush

        ; Create objects

        .if ( rax == NULL )

            .new pGradientStops:ptr ID2D1GradientStopCollection
            .new gradientStops[2]:D2D1_GRADIENT_STOP = {
                    { 0.0, { 0.0, 0.0, 0.0, 0.0 } },
                    { 1.3, { 0.0, 0.0, 0.0, 0.6 } } }
            .new gradisnBrushProperties:D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES = {
                    { 250.0, 100.0 }, { 4.0, -4.0 }, 50.0, 50.0 }
            .new brushProperties:D2D1_BRUSH_PROPERTIES = {
                    1.0, { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 } }

            cvtsi2ss xmm0,m_intensity
            divss xmm0,255.0
            movss gradientStops[D2D1_GRADIENT_STOP].color.a,xmm0
            mov gradientStops.color,[rsi].m_color
            mov hr,m_pRT.CreateGradientStopCollection(
                    &gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops )

            .if (SUCCEEDED(hr))

                cvtsi2ss xmm0,[rsi].m_pos.x
                cvtsi2ss xmm1,[rsi].m_pos.y
                cvtsi2ss xmm2,[rsi].m_radius

                movss gradisnBrushProperties.center.x,xmm0
                movss gradisnBrushProperties.center.y,xmm1
                movss gradisnBrushProperties.radiusX,xmm2
                movss gradisnBrushProperties.radiusY,xmm2

                mov hr,m_pRT.CreateRadialGradientBrush(&gradisnBrushProperties,
                            &brushProperties, pGradientStops, &brush)

                mov [rsi].m_brush,brush
                pGradientStops.Release()
            .endif
        .endif

        ; Draw objects

        .if (SUCCEEDED(hr))

            mov eax,[rsi].m_pos.x
            add eax,m_rc.left
            cvtsi2ss xmm0,eax
            mov eax,[rsi].m_pos.y
            add eax,m_rc.top
            cvtsi2ss xmm1,eax
            cvtsi2ss xmm2,[rsi].m_radius

            movss ellipse.point.x,xmm0
            movss ellipse.point.y,xmm1
            movss ellipse.radiusX,xmm2
            movss ellipse.radiusY,xmm2

            movss center.x,xmm0
            movss center.y,xmm1
            brush.SetCenter(center)
            brush.SetRadiusY(ellipse.radiusY)
            brush.SetRadiusX(ellipse.radiusX)

            m_pRT.FillEllipse(&ellipse, brush)
        .endif

        ; Move objects

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
    .return hr
    endp

    assume rsi:nothing

sc_textInfoBoxInset equ 14.0


CApplication::RenderTextInfo proc

   .new hr:HRESULT = S_OK
   .new textBuffer[400]:WCHAR
   .new n[16]:WCHAR
   .new m:Matrix3x2F
   .new c:D3DCOLORVALUE(Black, 0.5)
   .new rc:RECT
   .new rr:D2D1_ROUNDED_RECT = { { 30.0, 10.0, 250.0, 100.0 }, 10.0, 10.0 }
   .new rd[3]:LPWSTR = { "CPU", "LIBC", "PCG32" }

    mov ecx,m_rand
    and ecx,3
    _swprintf(&textBuffer,
        "primitives %u\n"
        "intensity  %u\n"
        "timer      %u\n"
        "%s", m_count, m_intensity, m_timer, rd[rcx*LPWSTR] )

    m_pRT.SetTransform(m.Identity())
    m_pSolidColorBrush.SetColor(&c)

    mov ecx,m_rc.right
    sub ecx,m_rc.left
    shr ecx,4
    mov edx,m_rc.bottom
    sub edx,65

    cvtsi2ss xmm0,ecx
    cvtsi2ss xmm1,edx
    movss rr.rect.left,xmm0
    movss rr.rect.top,xmm1
    addss xmm0,130.0
    addss xmm1,60.0
    movss rr.rect.right,xmm0
    movss rr.rect.bottom,xmm1

    m_pRT.FillRoundedRectangle(&rr, m_pSolidColorBrush)

    movss xmm0,rr.rect.left
    addss xmm0,sc_textInfoBoxInset
    movss rr.rect.left,xmm0
    movss xmm0,rr.rect.top
    addss xmm0,sc_textInfoBoxInset
    movss rr.rect.top,xmm0
    movss xmm0,rr.rect.right
    subss xmm0,sc_textInfoBoxInset
    movss rr.rect.right,xmm0
    movss xmm0,rr.rect.bottom
    subss xmm0,sc_textInfoBoxInset
    movss rr.rect.bottom,xmm0

    m_pSolidColorBrush.SetColor(c.Init(Gray, 0.8))
    mov ecx,wcsnlen(&textBuffer, ARRAYSIZE(textBuffer))
    m_pRT.DrawText(&textBuffer, ecx, m_pMonoFont, &rr, m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL)

    .if ( m_isFullScreen == FALSE )

        m_pRT.GetSize(&rc[8])
        mov rc.left,50.0
        mov rc.top,10.0
        m_pRT.DrawText(
            "Windows samples",
            lengthof(@CStr(-1))-1,
            m_pTextFont, &rc,
            m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )
        mov rc.top,26.0
        m_pRT.DrawText(
            "CApplication::Direct2D",
            lengthof(@CStr(-1))-1,
            m_pTextFont2, &rc,
            m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )
        mov rc.top,70.0
        m_pRT.DrawText(
            "This sample use the CApplication class\nRandom Count, Speed, Color, and Size",
            lengthof(@CStr(-1))-1,
            m_pTextFont, &rc,
            m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )
    .endif
    .return hr
    endp

;
;  DiscardDeviceResources()
;
;  Discard device-specific resources which need to be recreated
;  when a Direct3D device is lost.
;

CApplication::DiscardDeviceResources proc
    SafeRelease(m_pRT)
    SafeRelease(m_pSolidColorBrush)
    ret
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
    .case WM_KEYDOWN
        app.OnKeyDown(wParam)
        .endc
    .case WM_CLOSE
        app.OnClose()
        .endc
    .case WM_DESTROY
        app.OnDestroy()
        .endc
    .case WM_TIMER
        app.OnRender()
        .endc
    .case WM_PAINT
    .case WM_DISPLAYCHANGE
       .new ps:PAINTSTRUCT
        BeginPaint(hwnd, &ps)
        EndPaint(hwnd, &ps)
       .return 0
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .default
        DefWindowProc(hwnd, message, wParam, lParam)
    .endsw
    ret
    endp


; Creates the application window

CApplication::CreateApplicationWindow proc

    .new hr:HRESULT = CreateDeviceIndependentResources()

    .if (SUCCEEDED(hr))

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

        RegisterClassEx(&wc)

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
        .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WINDOWSTYLES,
                rc.left, rc.top, rc.right, rc.bottom, NULL, NULL, m_hInstance, rbx)
            mov m_hwnd,rax
            mov hr,S_OK
        .endif
    .endif
    .return hr
    endp


CApplication::BoundRand proc uses rsi rdi b:uint_t

    ldr esi,b

    mov eax,esi
    neg eax
    xor edx,edx
    div esi
    mov edi,edx
    .while 1
        .if ( m_rand == 0 )
            rdrand eax
        .elseif ( m_rand == 1 )
            rand()
        .else
            pcg32_random()
        .endif
        .break .ifd ( eax >= edi )
    .endw
    xor edx,edx
    div esi
    mov eax,edx
    ret
    endp


CApplication::RangeRand proc b:uint_t, m:uint_t
    .for ( :: )
        .break .ifd ( BoundRand(b) > m )
    .endf
    .return
    endp


CApplication::RandRGB proc uses rsi cv:ptr D3DCOLORVALUE, i:int_t

    ldr rsi,cv
    ldr edx,i

    cvtsi2ss xmm0,edx
    divss xmm0,255.0
    movss [rsi].D3DCOLORVALUE.a,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [rsi].D3DCOLORVALUE.r,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [rsi].D3DCOLORVALUE.g,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [rsi].D3DCOLORVALUE.b,xmm0
    BoundRand(0xFF)
    mov rax,rsi
    ret
    endp


CApplication::ErrorMessage proc hr:HRESULT, format:LPTSTR

  local message[512]:wchar_t
  local buffer[16]:wchar_t
  local szMessage:LPTSTR

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

    SafeRelease(m_obj)
    SafeRelease(m_pSolidColorBrush)
    SafeRelease(m_pTextFont)
    SafeRelease(m_pTextFont2)
    SafeRelease(m_pMonoFont)
    SafeRelease(m_pRT)
    SafeRelease(m_pDWriteFactory)
    SafeRelease(m_pD2DFactory)
    free(rbx)
    ret
    endp

    assume class:nothing, uses:nothing


; Provides the entry point to the application

CApplication::CApplication proc hInstance:HINSTANCE
    .if @ComAlloc(CApplication)
        mov rcx,hInstance
        mov [rax].CApplication.m_hInstance,rcx
        mov [rax].CApplication.m_timer,30
        mov [rax].CApplication.m_intensity,300
    .endif
    ret
    endp


wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPWSTR, iCmdShow:int_t

    ; Ignore the return value because we want to continue running even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .new hr:HRESULT = CoInitialize(NULL)
    .if (SUCCEEDED(hr))

       .new app:ptr CApplication(hInstance)
        mov hr,app.Run()
        app.Release()
        CoUninitialize()
    .endif
    .return hr
    endp

    end
