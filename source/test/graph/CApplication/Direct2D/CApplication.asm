
include CApplication.inc

    .code

ErrorMessage proc hr:HRESULT, format:LPTSTR, args:vararg

  local szMessage:LPTSTR
  local buffer[512]:wchar_t
  local message[512]:wchar_t

    vswprintf(&buffer, format, &args)

    mov edx,hr
    .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)

        mov hr,HRESULT_CODE(edx)
    .endif

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER or \
        FORMAT_MESSAGE_FROM_SYSTEM or \
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        &szMessage,
        0,
        NULL)

    swprintf(&message, "%s\n\nError code: %08X\n\n%s", &buffer, hr, szMessage)
    MessageBox(NULL, &message, "Error", MB_OK or MB_ICONERROR)
    LocalFree(szMessage)
   .return hr

ErrorMessage endp

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

RandRGB proc cv:ptr D3DCOLORVALUE, i:int_t

    mov r8,rcx
    cvtsi2ss xmm0,edx
    divss xmm0,255.0
    movss [r8].D3DCOLORVALUE.a,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [r8].D3DCOLORVALUE.r,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [r8].D3DCOLORVALUE.g,xmm0
    BoundRand(0xFF)
    cvtsi2ss xmm0,eax
    divss xmm0,255.0
    movss [r8].D3DCOLORVALUE.b,xmm0
    BoundRand(0xFF)
    mov rax,r8
    ret

RandRGB endp

; -- CApplication --

; Runs the application

CApplication::Run proc

    .new result:int_t = 0

    .new hr:HRESULT = this.BeforeEnteringMessageLoop()

    .if (SUCCEEDED(hr))

        mov result,this.EnterMessageLoop()
    .else

        ErrorMessage(hr, "An error occuring when running the sample" )
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

    mov rdi,this;rcx
    .if ( [rdi].m_hwnd == NULL )

        mov bSucceeded,FALSE
    .endif

    .if ( bSucceeded )

        ShowWindow([rdi].m_hwnd, SW_SHOWNORMAL)
        UpdateWindow([rdi].m_hwnd)
        GetWindowRect([rdi].m_hwnd, &[rdi].m_rect)
        SetTimer([rdi].m_hwnd, ID_TIMER, [rdi].m_timer, NULL)
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,rcx
    .if ( [rdi].m_hwnd != NULL )

        KillTimer( [rdi].m_hwnd, ID_TIMER )
        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


CApplication::OnSize proc uses rdi width:UINT, height:UINT

    mov rdi,rcx

    mov [rdi].m_size.width,edx
    mov [rdi].m_size.height,r8d

    mov [rdi].m_rc.top,0
    mov [rdi].m_rc.left,0
    mov [rdi].m_rc.right,edx
    mov [rdi].m_rc.bottom,r8d

    .if ( [rdi].m_isFullScreen == FALSE )

        mov [rdi].m_rc.top,130
        mov [rdi].m_rc.left,50
        sub [rdi].m_rc.right,50
        sub [rdi].m_rc.bottom,100
    .endif

    .if ( this.CreateDeviceResources() )

        .return ErrorMessage(eax, "CreateDeviceResources()" )
    .endif

    .if ( [rdi].m_pRT )

        ;
        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.
        ;

        this.m_pRT.Resize(&[rdi].m_size)
        this.InitObjects()
    .endif
    .return 0

CApplication::OnSize endp


CApplication::OnRender proc

   .new hr:HRESULT = this.CreateDeviceResources()

    .if (SUCCEEDED(hr))

        .if !( this.m_pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED )

           .new color:D3DCOLORVALUE
           .new matrix:Matrix3x2F
            color.Init(Black, 1.0)
            matrix.Identity()

            this.m_pRT.BeginDraw()
            this.m_pRT.SetTransform(&matrix)
            this.m_pRT.Clear(&color)

            mov hr,this.RenderMainContent()
            .if (SUCCEEDED(hr))

                mov hr,this.RenderTextInfo()
                .if (SUCCEEDED(hr))

                    mov hr,this.m_pRT.EndDraw(NULL, NULL)
                    .if (SUCCEEDED(hr))

                        .if (hr == D2DERR_RECREATE_TARGET)

                            this.DiscardDeviceResources()
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

CApplication::OnRender endp

    assume rcx:ptr CApplication

CApplication::OnKeyDown proc wParam:WPARAM

    .switch edx
    .case VK_SPACE
        .endc
    .case VK_DOWN
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            .if ( ( [rdx].object.m_mov.x > 1 || [rdx].object.m_mov.x < -1 ) && \
                  ( [rdx].object.m_mov.y > 1 || [rdx].object.m_mov.y < -1 ) )
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
            .if ( ( [rdx].object.m_mov.x < 30 && [rdx].object.m_mov.x > -30 ) && \
                  ( [rdx].object.m_mov.y < 30 && [rdx].object.m_mov.y > -30 ) )
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
    .case VK_RIGHT
        inc [rcx].m_intensity
        .endc
    .case VK_LEFT
        .if ( [rcx].m_intensity )
            dec [rcx].m_intensity
        .endif
        .endc
    .case VK_NEXT
        inc [rcx].m_timer
        SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endc
    .case VK_PRIOR
        .if ( [rcx].m_timer )
            dec [rcx].m_timer
            SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endif
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


CApplication::OnClose proc

    .if ( [rcx].m_hwnd != NULL )

        DestroyWindow( [rcx].m_hwnd )

        mov rcx,this
        mov [rcx].m_hwnd,NULL
    .endif
    .return 0

CApplication::OnClose endp


CApplication::OnDestroy proc

    PostQuitMessage(0)
   .return 0

CApplication::OnDestroy endp


; Handles the WM_PAINT message

    assume rcx:nothing
    assume rsi:ptr object

CApplication::InitObjects proc uses rsi rdi rbx

    mov rdi,rcx

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += object )

        SafeRelease([rsi].m_brush)
    .endf

    mov eax,[rdi].m_rc.bottom
    sub eax,[rdi].m_rc.top
    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left

    .ifs ( ecx < 100 || eax < 100 )

        mov [rdi].m_count,0
        .return 0
    .endif

    mov [rdi].m_count,RangeRand(MAXOBJ, 1)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        mov ecx,[rdi].m_rc.right
        mov edx,[rdi].m_rc.bottom
        cmp ecx,edx
        cmova ecx,edx
        shr ecx,3
        mov [rsi].m_radius,RangeRand(ecx, 8)
        mov [rsi].m_mov.x,RangeRand(9, 1)
        mov [rsi].m_mov.y,RangeRand(9, 1)
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.x,RangeRand(ecx, [rsi].m_radius)
        mov ecx,[rdi].m_rc.bottom
        sub ecx,[rdi].m_rc.top
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.y,RangeRand(ecx, [rsi].m_radius)
        RandRGB(&[rsi].m_color, [rdi].m_intensity)
    .endf
    .return 0

CApplication::InitObjects endp

    assume rsi:nothing

CApplication::GoFullScreen proc uses rdi rbx

    mov rdi,rcx
    mov [rdi].m_isFullScreen,TRUE

    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED); or WS_EX_TRANSPARENT)
    SetWindowLong([rdi].m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    mov rbx,GetDC(NULL)
   .new xSpan:int_t = GetSystemMetrics(SM_CXSCREEN)
   .new ySpan:int_t = GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(NULL, rbx)

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
    SetWindowLong([rdi].m_hwnd, GWL_STYLE, WINDOWSTYLES)
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST, [rdi].m_rect.left, [rdi].m_rect.top,
            [rdi].m_rect.right, [rdi].m_rect.bottom,
            SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

CApplication::GoPartialScreen endp


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

CApplication::CreateDeviceIndependentResources proc uses rdi

    mov rdi,rcx

    ; Create the Direct2D factory.

    .new hr:HRESULT = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory, NULL, &[rdi].m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                &IID_IDWriteFactory, &[rdi].m_pDWriteFactory)
    .endif


    .if (SUCCEEDED(hr))

        ; Create a DirectWrite text format object.

        mov hr,this.m_pDWriteFactory.CreateTextFormat(
                IDS_TEXTFONT,
                NULL,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                14.0,
                "",
                &[rdi].m_pTextFont)

        .if (SUCCEEDED(hr))

            mov hr,this.m_pDWriteFactory.CreateTextFormat(
                    IDS_TEXTFONT,
                    NULL,
                    DWRITE_FONT_WEIGHT_NORMAL,
                    DWRITE_FONT_STYLE_NORMAL,
                    DWRITE_FONT_STRETCH_NORMAL,
                    30.0,
                    "",
                    &[rdi].m_pTextFont2)
        .endif

        .if (SUCCEEDED(hr))

            mov hr,this.m_pTextFont.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP)
            mov hr,this.m_pTextFont2.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.m_pDWriteFactory.CreateTextFormat(
                IDS_MONOFONT,
                NULL,
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                12.0,
                "",
                &[rdi].m_pMonoFont)
    .endif
    .return hr

CApplication::CreateDeviceIndependentResources endp


;
;  CreateDeviceResources
;
;  This method creates resources which are bound to a particular
;  D3D device. It's all centralized here, in case the resources
;  need to be recreated in case of D3D device loss (eg. display
;  change, remoting, removal of video card, etc).
;

CApplication::CreateDeviceResources proc uses rdi

    mov rdi,rcx
   .new hr:HRESULT = S_OK

    .if ( ![rdi].m_pRT )

        ; Create a Direct2D render target.

       .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES = {
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            { DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN },
            0.0, 0.0,
            D2D1_RENDER_TARGET_USAGE_NONE,
            D2D1_FEATURE_LEVEL_DEFAULT
            }

       .new hwndRenderTargetProperties:D2D1_HWND_RENDER_TARGET_PROPERTIES = {
            [rdi].m_hwnd,
            { [rdi].m_size.width, [rdi].m_size.height },
            D2D1_PRESENT_OPTIONS_NONE
            }

        mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(
            &renderTargetProperties,
            &hwndRenderTargetProperties,
            &[rdi].m_pRT
            )

        .if (SUCCEEDED(hr))

            ; Create brushes.

           .new color:D3DCOLORVALUE(White, 1.0)
            mov hr,this.m_pRT.CreateSolidColorBrush(&color, NULL, &[rdi].m_pSolidColorBrush)
        .endif
    .endif
    .return hr

CApplication::CreateDeviceResources endp


    assume rsi:ptr object

CApplication::RenderMainContent proc uses rsi rdi rbx

    mov rdi,this;rcx
    xor eax,eax

    .new hr:HRESULT = eax;S_OK

    mov ecx,[rdi].m_rc.bottom
    sub ecx,[rdi].m_rc.top
    .return .ifs ( ecx < 100 )
    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    .return .ifs ( ecx < 100 )

    .new pRT:ptr ID2D1HwndRenderTarget = [rdi].m_pRT
    .new ellipse:D2D1_ELLIPSE
    .new brush:ptr ID2D1RadialGradientBrush
    .new center:D2D1_POINT_2F

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += object )

        mov brush,[rsi].m_brush

        ; Create objects

        .if ( rax == NULL )

            .new pGradientStops:ptr ID2D1GradientStopCollection
            .new gradientStops[2]:D2D1_GRADIENT_STOP = {
                    { 0.0, { 0.0, 0.0, 0.0, 0.0 } },
                    { 1.0, { 0.0, 0.0, 0.0, 0.6 } } }
            .new gradisnBrushProperties:D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES = {
                    { 250.0, 100.0 }, { 4.0, -4.0 }, 50.0, 50.0 }
            .new brushProperties:D2D1_BRUSH_PROPERTIES = {
                    1.0, { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 } }

            cvtsi2ss xmm0,[rdi].m_intensity
            divss xmm0,255.0
            movss gradientStops[D2D1_GRADIENT_STOP].color.a,xmm0
            mov gradientStops.color,[rsi].m_color
            mov hr,pRT.CreateGradientStopCollection(
                    &gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops )

            .if (SUCCEEDED(hr))

                cvtsi2ss xmm0,[rsi].m_pos.x
                cvtsi2ss xmm1,[rsi].m_pos.y
                cvtsi2ss xmm2,[rsi].m_radius

                movss gradisnBrushProperties.center.x,xmm0
                movss gradisnBrushProperties.center.y,xmm1
                movss gradisnBrushProperties.radiusX,xmm2
                movss gradisnBrushProperties.radiusY,xmm2

                mov hr,pRT.CreateRadialGradientBrush(&gradisnBrushProperties,
                            &brushProperties, pGradientStops, &brush)

                mov [rsi].m_brush,brush
                pGradientStops.Release()
            .endif
        .endif

        ; Draw objects

        .if (SUCCEEDED(hr))

            mov eax,[rsi].m_pos.x
            add eax,[rdi].m_rc.left
            cvtsi2ss xmm0,eax
            mov eax,[rsi].m_pos.y
            add eax,[rdi].m_rc.top
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

            pRT.FillEllipse(&ellipse, brush)
        .endif

        ; Move objects

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
    .return hr

CApplication::RenderMainContent endp

    assume rsi:nothing

sc_textInfoBoxInset equ 14.0

CApplication::RenderTextInfo proc uses rdi

   .new hr:HRESULT = S_OK
   .new textBuffer[400]:WCHAR

    mov rdi,rcx

    .new pRT:ptr ID2D1HwndRenderTarget = [rdi].m_pRT

    swprintf(
        &textBuffer,
        "primitives %d\n"
        "intensity  %d\n"
        "timer      %d",
        [rdi].m_count,
        [rdi].m_intensity,
        [rdi].m_timer)

   .new m:Matrix3x2F
    this.m_pRT.SetTransform(m.Identity())

   .new c:D3DCOLORVALUE(Black, 0.5)
    this.m_pSolidColorBrush.SetColor(&c)

   .new rr:D2D1_ROUNDED_RECT = { { 30.0, 10.0, 250.0, 100.0 }, 10.0, 10.0 }

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    shr ecx,4
    mov edx,[rdi].m_rc.bottom
    sub edx,65

    cvtsi2ss xmm0,ecx
    cvtsi2ss xmm1,edx
    movss rr.rect.left,xmm0
    movss rr.rect.top,xmm1
    addss xmm0,130.0
    addss xmm1,60.0
    movss rr.rect.right,xmm0
    movss rr.rect.bottom,xmm1

    pRT.FillRoundedRectangle(&rr, [rdi].m_pSolidColorBrush)

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

    this.m_pSolidColorBrush.SetColor(c.Init(Gray, 0.8))
    mov r8,wcsnlen(&textBuffer, ARRAYSIZE(textBuffer))
    pRT.DrawText(
            &textBuffer,
            r8d,
            [rdi].m_pMonoFont,
            &rr,
            [rdi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

    .if ( [rdi].m_isFullScreen == FALSE )

       .new rc:RECT
        pRT.GetSize(&rc[8])

        mov rc.left,50.0
        mov rc.top,10.0

        pRT.DrawText("Windows samples", lengthof(@CStr(-1))-1, [rdi].m_pTextFont, &rc,
            [rdi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )
        mov rc.top,26.0
        pRT.DrawText("CApplication::Direct2D", lengthof(@CStr(-1))-1, [rdi].m_pTextFont2, &rc,
            [rdi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )
        mov rc.top,70.0
        pRT.DrawText(
            "This sample use the CApplication class\n"
            "Random Count, Speed, Color, and Size",
            lengthof(@CStr(-1))-1,
            [rdi].m_pTextFont,
            &rc,
            [rdi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

        mov eax,[rdi].m_rc.bottom
        add eax,8
        cvtsi2ss xmm0,eax
        movss rc.top,xmm0
        mov eax,[rdi].m_rc.right
        shr eax,1
        cvtsi2ss xmm0,eax
        movss rc.left,xmm0

        pRT.DrawText(
            "Use keys UP/DOWN for speed\n"
            "LEFT/RIGHT for intensity, PGUP/PGDN timer\n"
            "ENTER reset, and F11 to toggle full screen",
            lengthof(@CStr(-1))-1,
            [rdi].m_pTextFont,
            &rc,
            [rdi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

    .endif
    .return hr

CApplication::RenderTextInfo endp

;
;  DiscardDeviceResources()
;
;  Discard device-specific resources which need to be recreated
;  when a Direct3D device is lost.
;

CApplication::DiscardDeviceResources proc uses rdi

    mov rdi,rcx
    SafeRelease([rdi].m_pRT)
    SafeRelease([rdi].m_pSolidColorBrush)
    ret

CApplication::DiscardDeviceResources endp

; Main Window procedure

WindowProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new app:ptr CApplication = GetWindowLongPtr(rcx, GWLP_USERDATA)

    .switch ( message )
    .case WM_SIZE
        movzx edx,word ptr lParam
        movzx r8d,word ptr lParam[2]
        app.OnSize(edx, r8d)
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

WindowProc endp

; Creates the application window

CApplication::CreateApplicationWindow proc uses rdi

    mov rdi,rcx

    .new hr:HRESULT = this.CreateDeviceIndependentResources()

    .if (SUCCEEDED(hr))

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

        RegisterClassEx(&wc)

        .new dpiX:float, dpiY:float

        ;
        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.
        ;

        this.m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

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
                rc.left, rc.top, rc.right, rc.bottom,
                NULL, NULL, [rdi].m_hInstance, rdi)

            mov [rdi].m_hwnd,rax
            mov hr,S_OK
        .endif
    .endif
    .return hr

CApplication::CreateApplicationWindow endp


; Provides the entry point to the application

CApplication::CApplication proc uses rdi hInstance:HINSTANCE

    mov rdi,@ComAlloc(CApplication)
    mov [rdi].m_hInstance,hInstance
    mov [rdi].m_timer,30
    mov [rdi].m_intensity,300
    mov rax,rdi
    ret

CApplication::CApplication endp


    assume rsi:ptr object

CApplication::Release proc uses rsi rdi rbx

    mov rdi,rcx
    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += object )
        SafeRelease([rsi].m_brush)
    .endf
    SafeRelease([rdi].m_pSolidColorBrush)
    SafeRelease([rdi].m_pTextFont)
    SafeRelease([rdi].m_pTextFont2)
    SafeRelease([rdi].m_pMonoFont)
    SafeRelease([rdi].m_pRT)
    SafeRelease([rdi].m_pDWriteFactory)
    SafeRelease([rdi].m_pD2DFactory)
    free(rdi)
    ret

CApplication::Release endp

    assume rsi:nothing

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

wWinMain endp

    end _tstart
