
include SimplePathAnimationSample.inc

.code

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

    ; Ignore the return value because we want to run the program even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .ifd CoInitialize(NULL) == S_OK

       .new app:ptr DemoApp()

        .ifd app.Initialize() == S_OK
            app.RunMessageLoop()
        .endif
        CoUninitialize()
    .endif
    .return 0

wWinMain endp


DemoApp::DemoApp proc

    @ComAlloc(DemoApp)
    ret
    endp

    assume class:rbx

DemoApp::Release proc

    SafeRelease(m_pD2DFactory)
    SafeRelease(m_pRT)
    SafeRelease(m_pPathGeometry)
    SafeRelease(m_pObjectGeometry)
    SafeRelease(m_pRedBrush)
    SafeRelease(m_pYellowBrush)
    ret
    endp

DemoApp::Initialize proc

  local wcex:WNDCLASSEX
  local dpiX:FLOAT, dpiY:FLOAT

    ; register window class

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    sizeof(LONG_PTR)
    mov wcex.hInstance,     HINST_THISCOMPONENT
    mov wcex.hIcon,         NULL
    mov wcex.hIconSm,       NULL
    mov wcex.hbrBackground, NULL
    mov wcex.lpszMenuName,  NULL
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.lpszClassName, &@CStr(L"D2DDemoApp")

    RegisterClassEx(&wcex)

    .ifd !CreateDeviceIndependentResources()

        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.

        m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

        movss       xmm0,dpiX
        mulss       xmm0,512.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   ecx,xmm0
        sub         ecx,eax
        neg         ecx

        movss       xmm0,dpiY
        mulss       xmm0,512.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   edx,xmm0
        sub         edx,eax
        neg         edx

        .if CreateWindowEx(0, L"D2DDemoApp", L"D2D Simple Path Animation Sample", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, ecx, edx, NULL, NULL, HINST_THISCOMPONENT, rbx)

            mov m_hwnd,rax

           .new length:float

            .ifd !m_pPathGeometry.ComputeLength(NULL, 0.25, &length)

                mov m_Animation.m_Start,0.0       ;;start at beginning of path
                mov m_Animation.m_End,length      ;;length at end of path
                mov m_Animation.m_Duration,15.0   ;;seconds

                ZeroMemory(&m_DwmTimingInfo, DWM_TIMING_INFO)
                mov m_DwmTimingInfo.cbSize,DWM_TIMING_INFO

                ; Get the composition refresh rate. If the DWM isn't running,
                ; get the refresh rate from GDI -- probably going to be 60Hz

                DwmGetCompositionTimingInfo(NULL, &m_DwmTimingInfo)

                .if (FAILED(eax))

                   .new hdc:HDC

                    mov hdc,GetDC(m_hwnd)
                    mov m_DwmTimingInfo.rateCompose.uiDenominator,1
                    GetDeviceCaps(hdc, VREFRESH)
                    mov m_DwmTimingInfo.rateCompose.uiNumerator,eax
                    ReleaseDC(m_hwnd, hdc)
                .endif

                ShowWindow(m_hwnd, SW_SHOWNORMAL)
                UpdateWindow(m_hwnd)
                mov eax,S_OK
            .endif
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret
    endp

;
;  This method is used to create resources which are not bound
;  to any device. Their lifetime effectively extends for the
;  duration of the app.
;

DemoApp::CreateDeviceIndependentResources proc uses rsi

  local hr:HRESULT
  local pSink:ptr ID2D1GeometrySink

    mov pSink,NULL

    ; Create a Direct2D factory.
    mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &IID_ID2D1Factory, NULL, &m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ; Create the path geometry.

        mov hr,m_pD2DFactory.CreatePathGeometry(&m_pPathGeometry)
    .endif

    .if (SUCCEEDED(hr))

        ; Write to the path geometry using the geometry sink. We are going to create a
        ; spiral

        mov hr,m_pPathGeometry.Open(&pSink)
    .endif

    .if (SUCCEEDED(hr))

        .new currentLocation:D2D1_POINT_2F = { 0.0, 0.0 }

        pSink.BeginFigure(currentLocation, D2D1_FIGURE_BEGIN_FILLED)

        .new radius:float = 3.0
        .new locDelta:D2D1_POINT_2F = { 2.0, 2.0 }

        .for ( esi = 0: esi < 30: ++esi )

            movss xmm0,radius
            mulss xmm0,locDelta.x
            addss xmm0,currentLocation.x
            movss currentLocation.x,xmm0

            movss xmm0,radius
            mulss xmm0,locDelta.y
            addss xmm0,currentLocation.y
            movss currentLocation.y,xmm0

            movss xmm1,radius
            mulss xmm1,2.0

            D2D1::ArcSegment(
                &currentLocation,
                D2D1::SizeF(xmm1, xmm1), ;; radiusx/y
                0.0, ;; rotation angle
                D2D1_SWEEP_DIRECTION_CLOCKWISE,
                D2D1_ARC_SIZE_SMALL
                )
            pSink.AddArc(rax)

            movss xmm0,locDelta.x
            movss xmm1,locDelta.y
            movss xmm2,-0.0
            xorps xmm1,xmm2
            movss locDelta.x,xmm1
            movss locDelta.y,xmm0
            movss xmm0,radius
            addss xmm0,3.0
            movss radius,xmm0
        .endf

        pSink.EndFigure(D2D1_FIGURE_END_OPEN)
        mov hr,pSink.Close()
    .endif

    .if (SUCCEEDED(hr))

        ; Create the path geometry.

        mov hr,m_pD2DFactory.CreatePathGeometry(&m_pObjectGeometry)
    .endif

    .if (SUCCEEDED(hr))

        ; Write to the object geometry using the geometry sink.
        ; We are going to create a simple triangle

        mov hr,m_pObjectGeometry.Open(&pSink)
    .endif

    .if (SUCCEEDED(hr))

        .new m_Triangle[3]:D2D1_POINT_2F

        mov eax,-10.0
        mov m_Triangle[0*D2D1_POINT_2F].x,eax
        mov m_Triangle[0*D2D1_POINT_2F].y,eax
        mov m_Triangle[1*D2D1_POINT_2F].x,eax
        mov m_Triangle[1*D2D1_POINT_2F].y,10.0
        mov m_Triangle[2*D2D1_POINT_2F].x,0.0
        mov m_Triangle[2*D2D1_POINT_2F].y,0.0

        pSink.BeginFigure(0, D2D1_FIGURE_BEGIN_FILLED)
        pSink.AddLines(&m_Triangle, 3)
        pSink.EndFigure(D2D1_FIGURE_END_OPEN)
        mov hr,pSink.Close()
    .endif

    pSink.Release()
    .return hr
    endp

;
;  This method creates resources which are bound to a particular
;  D3D device. It's all centralized here, in case the resources
;  need to be recreated in case of D3D device loss (eg. display
;  change, remoting, removal of video card, etc).
;

DemoApp::CreateDeviceResources proc

    xor eax,eax
    .if ( rax == m_pRT )

       .new rc:RECT

        GetClientRect(m_hwnd, &rc)

       .new size:D2D1_SIZE_U

        mov eax,rc.right
        sub eax,rc.left
        mov size.width,eax
        mov eax,rc.bottom
        sub eax,rc.top
        mov size.height,eax

        ; Create a Direct2D render target

        mov r8, D2D1_HwndRenderTargetProperties(m_hwnd, size)
        mov rdx,D2D1_RenderTargetProperties()

        .ifd !m_pD2DFactory.CreateHwndRenderTarget(rdx, r8, &m_pRT)

            ; Create a red brush.

            mov rdx,D3DCOLORVALUE(Red, 1.0)
            .ifd !m_pRT.CreateSolidColorBrush(rdx, NULL, &m_pRedBrush)

                ; Create a yellow brush.

                mov rdx,D3DCOLORVALUE(Yellow, 1.0)
                m_pRT.CreateSolidColorBrush(rdx, NULL, &m_pYellowBrush)
            .endif
        .endif
    .endif
    ret
    endp

;
;  Discard device-specific resources which need to be recreated
;  when a D3D device is lost
;

DemoApp::DiscardDeviceResources proc

    SafeRelease(m_pRT)
    SafeRelease(m_pRedBrush)
    SafeRelease(m_pYellowBrush)
    ret
    endp


DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret
    endp

;
;  Called whenever the application needs to display the client
;  window. This method draws a single frame of animated content
;
;  Note that this function will not render anything if the window
;  is occluded (e.g. when the screen is locked).
;  Also, this function will automatically discard device-specific
;  resources if the D3D device disappears during function
;  invocation, and will recreate the resources the next time it's
;  invoked.
;

DemoApp::OnRender proc ps:PAINTSTRUCT

  local hr:HRESULT
  local hdc:HDC
  local pRT:ptr ID2D1HwndRenderTarget

    mov hdc,[rdx].PAINTSTRUCT.hdc
    mov hr, CreateDeviceResources()
    mov pRT,m_pRT

    .if ( SUCCEEDED(hr) && !( pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED ) )

       .new point:D2D1_POINT_2F
       .new tangent:D2D1_POINT_2F
       .new triangleMatrix:Matrix3x2F
       .new rtSize:D2D1_SIZE_F
       .new minWidthHeightScale:float
       .new scale:Matrix3x2F
       .new translation:Matrix3x2F
       .new m:Matrix3x2F

        pRT.GetSize(&rtSize)
        movss xmm0,rtSize.width
        minss xmm0,rtSize.height
        divss xmm0,512.0
        movss minWidthHeightScale,xmm0

        scale.Scale(xmm0, xmm0)

        movss xmm0,rtSize.width
        movss xmm1,rtSize.height
        divss xmm0,2.0
        divss xmm1,2.0
        movss point.x,xmm0
        movss point.y,xmm1
        translation.Translation(xmm0, xmm1)

        ; Prepare to draw.
        pRT.BeginDraw()

        ; Reset to identity transform
        pRT.SetTransform(m.Identity())

        ; clear the render target contents
        pRT.Clear(D3DCOLORVALUE(Black, 1.0))

        ; center the path
        m.SetProduct(&scale, &translation)
        pRT.SetTransform(&m)

        ; draw the path in red
        pRT.DrawGeometry(m_pPathGeometry, m_pRedBrush, 0.6, NULL)

        lea rcx,m_Animation
        [rcx].Animation.GetValue(m_Time, EaseInOutExponentialAnimation)

        ; Ask the geometry to give us the point that corresponds with the
        ; length at the current time.

        mov hr,m_pPathGeometry.ComputePointAtLength(xmm0, NULL, 1.0, &point, &tangent)

        .assert(SUCCEEDED(hr))

        ; Reorient the triangle so that it follows the
        ; direction of the path.

        mov triangleMatrix._11,tangent.x
        mov triangleMatrix._12,tangent.y
        xor eax,0x80000000
        mov triangleMatrix._21,eax
        mov triangleMatrix._22,tangent.x
        mov triangleMatrix._31,point.x
        mov triangleMatrix._32,point.y
        m.SetProduct(&triangleMatrix, &m)

        pRT.SetTransform(&m)

        ; Draw the yellow triangle.
        pRT.FillGeometry(m_pObjectGeometry, m_pYellowBrush, NULL)

        ; Commit the drawing operations.
        mov hr,pRT.EndDraw(NULL, NULL)

        .if (hr == D2DERR_RECREATE_TARGET)

            mov hr,S_OK
            DiscardDeviceResources()
        .endif

        ; When we reach the end of the animation, loop back to the beginning.

        movss  xmm0,m_Time
        comiss xmm0,m_Animation.m_Duration

        .ifnb ;(float_time >= [rsi].m_Animation.GetDuration())

            mov m_Time,0.0

        .else

            cvtsi2ss xmm1,m_DwmTimingInfo.rateCompose.uiDenominator
            cvtsi2ss xmm2,m_DwmTimingInfo.rateCompose.uiNumerator
            divss xmm1,xmm2
            addss xmm0,xmm1
            movss m_Time,xmm0

        .endif
    .endif

    InvalidateRect(m_hwnd, NULL, FALSE)

    .return hr

    endp


;
;  If the application receives a WM_SIZE message, this method
;  resize the render target appropriately.
;

DemoApp::OnResize proc width:UINT, height:UINT

    .if m_pRT

       .new size:D2D1_SIZE_U

        mov size.width,edx
        mov size.height,r8d

        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.

        m_pRT.Resize(&size)
    .endif
    ret
    endp


WndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local result:LRESULT
  local wasHandled:BOOL
  local pDemoApp:ptr DemoApp

     mov result,0

    .if edx == WM_CREATE

        mov r8,[r9].CREATESTRUCT.lpCreateParams
        SetWindowLongPtrW(rcx, GWLP_USERDATA, PtrToUlong(r8))
        mov result,1

    .else

        mov pDemoApp,GetWindowLongPtrW(rcx, GWLP_USERDATA)
        mov wasHandled,FALSE

        .if rax

            .switch(message)

            .case WM_SIZE

                movzx edx,word ptr lParam
                movzx r8d,word ptr lParam[2]
                pDemoApp.OnResize(edx, r8d)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_PAINT
            .case WM_DISPLAYCHANGE

                .new ps:PAINTSTRUCT
                BeginPaint(hwnd, &ps)

                pDemoApp.OnRender(&ps)
                EndPaint(hwnd, &ps)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_DESTROY

                PostQuitMessage(0)
                mov result,1
                mov wasHandled,TRUE
                .endc

            .case WM_CHAR
                .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
                .endc

            .endsw
        .endif

        .if (!wasHandled)

            mov result,DefWindowProc(hwnd, message, wParam, lParam)
        .endif
    .endif
    .return result

WndProc endp

    end _tstart
