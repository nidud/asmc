;
; https://github.com/microsoft/Windows-classic-samples/
;
include Direct2DHelloWorld.inc

.pragma warning(disable: 6004) ; procedure argument or local not referenced
.pragma warning(disable: 7007) ; .CASE without .ENDC: assumed fall through

.code


; Provides the entry point to the application.

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, inCmdShow:int_t

    ; Ignore the return value because we want to run the program even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)


    .if (SUCCEEDED(CoInitialize(NULL)))

        .new app:ptr DemoApp()

        .if (SUCCEEDED(app.Initialize()))

            app.RunMessageLoop()
        .endif
        app.Release()
        CoUninitialize()
    .endif
    .return 0
    endp


; Initialize members.

DemoApp::DemoApp proc

    @ComAlloc(DemoApp)
    ret
    endp


; Release resources.

    assume class:rbx

DemoApp::Release proc

    SafeRelease(m_pD2DFactory)
    SafeRelease(m_pDWriteFactory)
    SafeRelease(m_pRenderTarget)
    SafeRelease(m_pTextFormat)
    SafeRelease(m_pBlackBrush)
    ret
    endp


; Creates the application window and initializes
; device-independent resources.

DemoApp::Initialize proc

  local dpiX:FLOAT, dpiY:FLOAT

    ; Initialize device-indpendent resources, such
    ; as the Direct2D factory.

    .if SUCCEEDED(CreateDeviceIndependentResources())

        ; Register the window class.

        .new wc:WNDCLASSEX = {
            WNDCLASSEX,                     ; .cbSize
            CS_HREDRAW or CS_VREDRAW,       ; .style
            &WndProc,                       ; .lpfnWndProc
            0,                              ; .cbClsExtra
            sizeof(LONG_PTR),               ; .cbWndExtra
            HINST_THISCOMPONENT,            ; .hInstance
            NULL,                           ; .hIcon
            LoadCursor(NULL, IDC_ARROW),    ; .hCursor
            NULL,                           ; .hbrBackground
            NULL,                           ; .lpszMenuName
            "D2DDemoApp",                   ; .lpszClassName
            NULL                            ; .hIconSm
            }

        RegisterClassEx(&wc)


        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.

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

        .if CreateWindowEx(0, "D2DDemoApp", "Direct2D Demo Application", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, ecx, edx, NULL, NULL, HINST_THISCOMPONENT, rbx)

            mov m_hwnd,rax
            ShowWindow(rax, SW_SHOWNORMAL)
            UpdateWindow(m_hwnd)
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret
    endp


; Create resources which are not bound
; to any device. Their lifetime effectively extends for the
; duration of the app. These resources include the Direct2D and
; DirectWrite factories,  and a DirectWrite Text Format object
; (used for identifying particular font characteristics).

DemoApp::CreateDeviceIndependentResources proc

  .new hr:HRESULT
  .new pSink:ptr ID2D1GeometrySink = NULL

    ; Create a Direct2D factory.

    mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &IID_ID2D1Factory, NULL, &m_pD2DFactory)

    .if (SUCCEEDED(eax))

        ; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory, &m_pDWriteFactory)

    .endif

    .if (SUCCEEDED(eax))

        ; Create a DirectWrite text format object.

        mov hr,m_pDWriteFactory.CreateTextFormat(L"Verdana", NULL, DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50.0, L"", &m_pTextFormat)
    .endif

    .if (SUCCEEDED(eax))

        ; Center the text horizontally and vertically.

        m_pTextFormat.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
        m_pTextFormat.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
    .endif

    SafeRelease(pSink)
    mov eax,hr
    ret
    endp


;  This method creates resources which are bound to a particular
;  Direct3D device. It's all centralized here, in case the resources
;  need to be recreated in case of Direct3D device loss (eg. display
;  change, remoting, removal of video card, etc).

DemoApp::CreateDeviceResources proc

    .new hr:HRESULT = S_OK
    .new rc:RECT
    .new HwndRenderTargetProperties:D2D1_HWND_RENDER_TARGET_PROPERTIES

    .if ( !m_pRenderTarget )

        mov rcx,m_hwnd
        mov HwndRenderTargetProperties.hwnd,rcx
        GetClientRect(rcx, &rc)
        mov eax,rc.right
        sub eax,rc.left
        mov HwndRenderTargetProperties.pixelSize.width,eax
        mov eax,rc.bottom
        sub eax,rc.top
        mov HwndRenderTargetProperties.pixelSize.height,eax
        mov HwndRenderTargetProperties.presentOptions,D2D1_PRESENT_OPTIONS_NONE

        ; Create a Direct2D render target.

       .new RenderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES()
        mov hr,m_pD2DFactory.CreateHwndRenderTarget(&RenderTargetProperties, &HwndRenderTargetProperties, &m_pRenderTarget)

        .if (SUCCEEDED(eax))

            ; Create a black brush.

            mov rdx,D3DCOLORVALUE(Black, 1.0)
            mov hr,m_pRenderTarget.CreateSolidColorBrush(rdx, NULL, &m_pBlackBrush)
        .endif
    .endif
    .return( hr )
    endp


;  Discard device-specific resources which need to be recreated
;  when a Direct3D device is lost

DemoApp::DiscardDeviceResources proc

    SafeRelease(m_pRenderTarget)
    SafeRelease(m_pBlackBrush)
    ret
    endp


; The main window message loop.

DemoApp::RunMessageLoop proc

    .new msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret
    endp


;  Called whenever the application needs to display the client
;  window. This method writes "Hello, World"
;
;  Note that this function will not render anything if the window
;  is occluded (e.g. when the screen is locked).
;  Also, this function will automatically discard device-specific
;  resources if the Direct3D device disappears during function
;  invocation, and will recreate the resources the next time it's
;  invoked.


DemoApp::OnRender proc

  local hr:HRESULT, m:Matrix3x2F, c:D3DCOLORVALUE

    mov hr,CreateDeviceResources()
    m_pRenderTarget.CheckWindowState()

    .if (SUCCEEDED(hr) && !(eax & D2D1_WINDOW_STATE_OCCLUDED))

        ; Retrieve the size of the render target.

       .new rc:RECT = { 0, 0 }

        m_pRenderTarget.GetSize(&rc[8])
        m_pRenderTarget.BeginDraw()
        m_pRenderTarget.SetTransform(m.Identity())
        m_pRenderTarget.Clear(c.Init(White, 1.0))
        m_pRenderTarget.DrawText("Hello, World!", 13, m_pTextFormat, &rc, m_pBlackBrush,
                D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL)

        mov hr,m_pRenderTarget.EndDraw(NULL, NULL)
        .if ( hr == D2DERR_RECREATE_TARGET )

            mov hr,S_OK
            DiscardDeviceResources()
        .endif
    .endif
    .return hr
    endp


;  If the application receives a WM_SIZE message, this method
;  resizes the render target appropriately.

DemoApp::OnResize proc width:UINT, height:UINT

  local size:D2D1_SIZE_U

    .if ( m_pRenderTarget )

        mov size.width,ldr(width)
        mov size.height,ldr(height)

        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.

        m_pRenderTarget.Resize(&size)
    .endif
    ret
    endp



; The window message handler.

WndProc proc WINAPI hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .new result:LRESULT = 0
    .new wasHandled:BOOL = FALSE
    .new pDemoApp:ptr DemoApp

    .if ( ldr(message) == WM_CREATE )

        ldr rdx,lParam
        SetWindowLongPtrW(ldr(hwnd), GWLP_USERDATA, [rdx].CREATESTRUCT.lpCreateParams)
        mov result,1

    .else

        mov pDemoApp,GetWindowLongPtrW(ldr(hwnd), GWLP_USERDATA)

        .if pDemoApp

            .switch message
            .case WM_SIZE
                movzx edx,word ptr lParam
                movzx ecx,word ptr lParam[2]
                pDemoApp.OnResize(edx, ecx)
                mov wasHandled,TRUE
                mov result,0
               .endc
            .case WM_PAINT
            .case WM_DISPLAYCHANGE
               .new ps:PAINTSTRUCT
                BeginPaint(hwnd, &ps)
                pDemoApp.OnRender()
                EndPaint(hwnd, &ps)
                mov wasHandled,TRUE
                mov result,0
               .endc
            .case WM_DESTROY
                PostQuitMessage(0)
                mov wasHandled,TRUE
                mov result,1
               .endc
            .case WM_CHAR
                .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
                .endc
            .endsw
        .endif
        .if !wasHandled
            mov result,DefWindowProc(hwnd, message, wParam, lParam)
        .endif
    .endif
    .return result

    endp

    end _tstart
