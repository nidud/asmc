
include CApplication.inc

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">

    .data
     CLSID_AppVisibility GUID { 0x7E5FE3D9, 0x985F, 0x4908, { 0x91, 0xF9, 0xEE, 0x19, 0xF9, 0xFD, 0x15, 0x14 } }
     IID_IAppVisibility  GUID { 0x2246EA2D, 0xCAEA, 0x4444, { 0xA3, 0xC4, 0x6D, 0xE8, 0x27, 0xE4, 0x43, 0x13 } }
     IID_IAppVisibilityEvents GUID { 0x6584CE6B, 0x7D82, 0x49C2, { 0x89, 0xC9, 0xC6, 0xBC, 0x02, 0xBA, 0x8C, 0x38 } }

    .code

    assume rcx:ptr CApplication
    assume rdi:ptr CApplication


; --- Implementation of IAppVisibilityEvents ---

CApplication::QueryInterface proc riid:LPIID, ppv:ptr ptr

    mov rax,[rdx]
    .if ( rax == qword ptr IID_IAppVisibilityEvents || rax == 0 )

        mov [r8],rcx
        inc [rcx].m_refcnt
        .return NOERROR
    .endif
    xor eax,eax
    mov [r8],rax
   .return E_INVALIDARG

CApplication::QueryInterface endp


CApplication::AddRef proc

    lock inc [rcx].m_refcnt
   .return [rcx].m_refcnt

CApplication::AddRef endp


CApplication::Release proc

    lock dec [rcx].m_refcnt
   .return [rcx].m_refcnt

CApplication::Release endp

CApplication::AppVisibilityOnMonitorChanged proc hMonitor:HMONITOR,
        previousAppVisibility:MONITOR_APP_VISIBILITY, currentAppVisibility:MONITOR_APP_VISIBILITY

    .return S_OK

CApplication::AppVisibilityOnMonitorChanged endp


CApplication::LauncherVisibilityChange proc currentVisibleState:BOOL

    .if ( edx )
        inc [rcx].m_launchcnt
    .endif
    .if ( [rcx].m_launchcnt == 5 )
        PostQuitMessage(0)
    .else
        this.Update(edx)
    .endif
   .return S_OK

CApplication::LauncherVisibilityChange endp

; --- End IAppVisibilityEvents ---


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

CApplication::BeforeEnteringMessageLoop proc uses rdi

    mov rdi,rcx

    .new hr:HRESULT = this.CreateApplicationWindow()

    .if (SUCCEEDED(hr))

        .new hr:HRESULT = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED )

        .if (SUCCEEDED(hr))

            mov hr,CoCreateInstance(&CLSID_AppVisibility, NULL, CLSCTX_INPROC_SERVER,
                    &IID_IAppVisibility, &[rdi].m_AppVisibility)

            .if (SUCCEEDED(hr))

                mov hr,this.m_AppVisibility.Advise( rdi, &[rdi].m_cookie )
            .endif
        .endif
    .endif
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

    .if ( [rcx].m_AppVisibility )
        this.m_AppVisibility.Unadvise([rcx].m_cookie)
    .endif
    CoUninitialize()
    this.DestroyApplicationWindow()
    ret

CApplication::AfterLeavingMessageLoop endp


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
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,rcx
    .if ( [rdi].m_hwnd != NULL )

        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


    assume rcx:nothing

CApplication::Update proc uses rsi rdi rbx Visible:BOOL

    mov rdi,rcx

   .new hdc:HDC = GetDC([rdi].m_hwnd)
   .new g:Graphics(hdc)
    g.SetSmoothingMode(SmoothingModeHighQuality)

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)

   .new p:GraphicsPath()

    mov ebx,[rdi].m_yoffs
    add ebx,8
    p.AddEllipse(50, ebx, 50, 50)

   .new b:PathGradientBrush(&p)
    b.SetCenterColor(ColorAlpha(Blue, 180))
    b.SetSurroundColors(&FullTranslucent, &count)
    g.FillEllipse(&b, 50, ebx, 50, 50)

    b.Release()
    p.Release()

   .new p:GraphicsPath()

    add ebx,60
    p.AddEllipse(50, ebx, 50, 50)

   .new b:PathGradientBrush(&p)
    mov edx,ColorAlpha(Red, 180)
    .if ( Visible )
        mov edx,ColorAlpha(Green, 180)
    .endif
    b.SetCenterColor(edx)
    b.SetSurroundColors(&FullTranslucent, &count)
    g.FillEllipse(&b, 50, ebx, 50, 50)
    b.Release()
    p.Release()

   .new pt:PointF(65.0, 138.0)
   .new b:SolidBrush(LightGray)
   .new f:Font(IDS_FONT_TYPEFACE, 16.0)
   .new t[4]:wchar_t

    mov eax,[rdi].m_launchcnt
    add al,'0'
    mov dword ptr t,eax
    g.DrawString( &t, 1, &f, pt, NULL, &b)

    b.Release()
    f.Release()
    g.Release()
    ReleaseDC([rdi].m_hwnd, hdc)
   .return 1

CApplication::Update endp

CApplication::OnSize proc lParam:LPARAM

    .return 1

CApplication::OnSize endp


; Handles the WM_KEYDOWN message

CApplication::OnKeyDown proc wParam:WPARAM

    .return 0

CApplication::OnKeyDown endp


; Handles the WM_CLOSE message

    assume rcx:ptr CApplication

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

CApplication::OnPaint proc uses rdi

   .new rcClient:RECT
   .new ps:PAINTSTRUCT
   .new height:int_t = 0

    mov rdi,rcx

   .new hdc:HDC = BeginPaint([rdi].m_hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect([rdi].m_hwnd, &rcClient)

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

        mov height,DrawText(hdc, "CApplication : public IAppVisibilityEvents", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(htitle)
    .endif

    ; Description

   .new hdescription:HFONT

    xor ecx,ecx
    mov hdescription,CreateFont(IDS_FONT_HEIGHT_DESCRIPTION, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx,
            IDS_FONT_TYPEFACE) ; Description Font and Size

    .if ( hdescription != NULL )

       .new hOldFont:HFONT = SelectObject(hdc, hdescription)

        mov eax,height
        add eax,40
        mov rcClient.top,eax
        mov rcClient.left,50

        DrawText(hdc,
            "This sample use the IAppVisibility class to trap the Start menu",
             -1, &rcClient, DT_WORDBREAK)

        add eax,rcClient.top
        add eax,10
        mov [rdi].m_yoffs,eax
        mov rcClient.top,eax
        mov eax,[rdi].m_width
        shr eax,3
        mov rcClient.left,eax
        DrawText(hdc, "\nLaunch count\n\n\nStart menu visible", -1, &rcClient, DT_WORDBREAK)

        mov eax,[rdi].m_height
        sub eax,100
        mov rcClient.top,eax
        mov eax,[rdi].m_width
        shr eax,1
        mov rcClient.left,eax

        DrawText(hdc,
            "Toggle Start menu visibility 5 times to exit.\n",
            -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif
    EndPaint([rdi].m_hwnd, &ps)

    this.Update(0)
   .return 1

CApplication::OnPaint endp


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

    .new rect:RECT( 0, 0, [rdi].m_width, [rdi].m_height )

    AdjustWindowRect(&rect, WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,rect.right
    sub eax,rect.left
    mov [rdi].m_width,eax

    mov eax,rect.bottom
    sub eax,rect.top
    mov [rdi].m_height,eax

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME,
           WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT,
           [rdi].m_width, [rdi].m_height,
           NULL, NULL, [rdi].m_hInstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi].m_hwnd,rax
   .return S_OK

CApplication::CreateApplicationWindow endp


; Provides the entry point to the application

CApplication::CApplication proc instance:HINSTANCE

    @ComAlloc(CApplication)

    mov rcx,instance
    mov [rax].CApplication.m_hInstance,rcx
    mov [rax].CApplication.m_width,900
    mov [rax].CApplication.m_height,600
    ret

CApplication::CApplication endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

_tWinMain endp

    end _tstart
