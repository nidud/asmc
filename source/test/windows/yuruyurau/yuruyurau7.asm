define _USE_MATH_DEFINES
define WIN32_LEAN_AND_MEAN

.pragma list(push, 0)

include windows.inc
include DirectX/d2d1.inc
include stdio.inc
include math.inc
include immintrin.inc
include tchar.inc

.pragma list(pop)

define CLASS_NAME <"MainWindowClass">
define WINDOW_NAME <"https://x.com/yuruyurau/status/2091536763152142373">

define WINDOWSTYLES WS_OVERLAPPEDWINDOW
define ID_TIMER     1
define MAXOBJ 10000
define STEPDIV 240
define TIMER 30

.class CApplication

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_rect          RECT <>
    m_size          D2D1_SIZE_U <>
    m_rc            RECT <>
    m_time          real4 ?
    m_DeltaX        real4 ?
    m_DeltaY        real4 ?
    m_radius        real4 ?
    m_step          int_t ?
    m_count         int_t ?
    m_texty         int_t ?
    m_timer         int_t ?
    m_intensity     int_t ?
    m_isFullScreen  BOOL ?
    m_pD2DFactory   ptr ID2D1Factory ?
    m_pRT           ptr ID2D1HwndRenderTarget ?
    m_brush         ptr ID2D1RadialGradientBrush ?

    CApplication    proc :HINSTANCE
    Release         proc
    Run             proc
    OnKeyDown       proc :WPARAM
    OnRender        proc
    OnSize          proc :UINT, :UINT
    OnClose         proc
    GoFullScreen    proc
    GoPartialScreen proc
    CreateDeviceResources proc
    RenderMainContent proc
    EnterMessageLoop proc
    CreateApplicationWindow proc
    ErrorMessage    proc :HRESULT, :LPTSTR
   .ends

.data
 IID_ID2D1Factory GUID {0x06152247,0x6f50,0x465a,{0x92,0x45,0x11,0x8b,0xfd,0x3b,0x60,0x07}}

.code

_mm_mag_ss macro a, b
    mulss a,a
    mulss b,b
    addss a,b
    sqrtss a,a
    retm<a>
    endm

_mm_sin_ss macro x
    sinf(x)
    retm<xmm0>
    endm

_mm_pow_ss macro x, i
    movss xmm1,x
    repeat i-1
      mulss x,xmm1
    endm
    retm<x>
    endm


 assume class:rbx

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
        ;GoFullScreen()
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
    divss xmm0,500.0
    divss xmm1,500.0
    movss m_DeltaX,xmm0
    movss m_DeltaY,xmm1

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


CApplication::OnKeyDown proc wParam:WPARAM

    .switch ldr(wParam)
    .case VK_UP
        mov eax,m_step
        mov ecx,20
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
        MessageBox(
            NULL,
            "F11\t\tToggle full screen\n"
            "Enter\t\tDefault\n"
            "Up/Down\t\tSpeed\n"
            "Left/Right\t\tIntensity\n"
            "Home/End\tPoint size\n"
            "PgUp/PgDn\tPoint Count\n",
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
    .endif
    .return hr
    endp


CApplication::RenderMainContent proc uses rsi rdi

   .new hr:HRESULT = S_OK
   .new ellipse:D2D1_ELLIPSE
   .new center:D2D1_POINT_2F
   .new x:real4, y

    xor eax,eax
    mov ecx,m_rc.bottom
    sub ecx,m_rc.top
    .return .ifs ( ecx < 100 )
    mov ecx,m_rc.right
    sub ecx,m_rc.left
    .return .ifs ( ecx < 100 )

    ; Create objects

    .if ( m_brush == NULL )

        .new pGradientStops:ptr ID2D1GradientStopCollection
        .new gradientStops[2]:D2D1_GRADIENT_STOP = {
                { 0.0, { 0.0, 0.0, 0.0, 0.0 } },
                { 1.3, { 0.0, 0.0, 0.0, 0.6 } } }
        .new gradisnBrushProperties:D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES = {
                { 250.0, 100.0 }, { 4.0, -4.0 }, 50.0, 50.0 }
        .new brushProperties:D2D1_BRUSH_PROPERTIES = {
                1.0, { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 } }

        movss xmm0,1.0
        movss gradientStops.color.r,xmm0
        movss gradientStops.color.g,xmm0
        movss gradientStops.color.b,xmm0
        mov eax,m_intensity
        _mm_move_ss(gradientStops[D2D1_GRADIENT_STOP].color.a, _mm_div_ss(_mm_cvt_si2ss(xmm0, eax), 255.0))

        mov hr,m_pRT.CreateGradientStopCollection(&gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops)

        .if (SUCCEEDED(hr))

            movss xmm0,m_radius
            movss gradisnBrushProperties.radiusX,xmm0
            movss gradisnBrushProperties.radiusY,xmm0
            mov hr,m_pRT.CreateRadialGradientBrush(&gradisnBrushProperties,
                            &brushProperties, pGradientStops, &m_brush)
            pGradientStops.Release()
        .endif
    .endif

    mov ecx,m_step
    _mm_div_ss(_mm_move_ss(xmm1, M_PI), _mm_cvt_si2ss(xmm2, ecx))
    _mm_move_ss(m_time, _mm_add_ss(_mm_move_ss(xmm0, m_time), xmm1))

    .for ( edi = 0 : edi < m_count : edi++ )

        _mm_move_ss(xmm8, _mm_div_ss(_mm_cvt_si2ss(xmm0, edi), 254.0))
        _mm_move_ss(xmm7, _mm_mul_ss(cosf(_mm_mul_ss(xmm0, 9.0)), 5.0))
        _mm_move_ss(xmm9, _mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm1, xmm8), 0.5), 15.0))
        _mm_move_ss(xmm6, _mm_div_ss(_mm_mag_ss(xmm0, xmm1), 3.0))
        _mm_move_ss(xmm10, _mm_add_ss(_mm_pow_ss(_mm_sin_ss(m_time), 4), xmm6))
        _mm_move_ss(xmm6, _mm_sub_ss(_mm_mul_ss(xmm0, 0.5), m_time))
        _mm_move_ss(xmm1, _mm_sin_ss(xmm0))
        _mm_add_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), xmm0), 79.0)
        _mm_move_ss(x, _mm_add_ss(_mm_mul_ss(xmm0, xmm1), 200.0))
        _mm_move_ss(xmm6, _mm_mul_ss(_mm_sin_ss(_mm_mul_ss(xmm6, 0.5)), 89.0))
        _mm_move_ss(xmm1, _mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm7), 2.0)))
        _mm_add_ss(_mm_add_ss(xmm6, _mm_mul_ss(_mm_div_ss(_mm_move_ss(xmm0, 7.0), xmm10), xmm1)), 200.0)
        _mm_sub_ss(_mm_mul_ss(_mm_move_ss(xmm0, m_time), 9.0), _mm_mul_ss(_mm_move_ss(xmm1, xmm10), 2.0))
        _mm_move_ss(xmm2, _mm_sin_ss(xmm0))
        _mm_add_ss(xmm6, _mm_mul_ss(_mm_div_ss(_mm_pow_ss(xmm10, 3), 6.0), xmm2))
        .if ( xmm8 < 6.0 )
            _mm_div_ss(xmm8, 7.0)
        .else
            _mm_sin_ss(_mm_mul_ss(_mm_move_ss(xmm0, xmm9), 0.5))
            _mm_div_ss(xmm8, _mm_add_ss(_mm_mul_ss(xmm0, 99.0), 1.0))
        .endif
        _mm_move_ss(y, _mm_add_ss(_mm_mul_ss(_mm_mul_ss(xmm7, xmm8), xmm9), xmm6))

        ; Draw objects

        .if (SUCCEEDED(hr))

            movss xmm2,m_radius
            _mm_move_ss(ellipse.point.x, _mm_mul_ss(_mm_move_ss(xmm0, x), m_DeltaX))
            _mm_move_ss(ellipse.point.y, _mm_mul_ss(_mm_move_ss(xmm1, y), m_DeltaY))
            movss ellipse.radiusX,xmm2
            movss ellipse.radiusY,xmm2
            movss center.x,xmm0
            movss center.y,xmm1
            m_brush.SetCenter(center)
            m_brush.SetRadiusY(ellipse.radiusY)
            m_brush.SetRadiusX(ellipse.radiusX)
            m_pRT.FillEllipse(&ellipse, m_brush)
        .endif
    .endf
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
    .case WM_KEYDOWN
        app.OnKeyDown(wParam)
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
       .return 0
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
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
            LoadCursor(NULL, IDC_ARROW),    ; .hCursor
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
        .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WINDOWSTYLES,
                rc.left, rc.top, rc.right, rc.bottom, NULL, NULL, m_hInstance, rbx)
            mov m_hwnd,rax
            mov hr,S_OK
        .endif
    .endif
    .return hr
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
    SafeRelease(m_brush)
    SafeRelease(m_pRT)
    SafeRelease(m_pD2DFactory)
    free(rbx)
    ret
    endp

; Provides the entry point to the application

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

    end _tstart
