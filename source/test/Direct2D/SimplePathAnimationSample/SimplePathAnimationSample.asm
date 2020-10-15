
include SimplePathAnimationSample.inc

.code
;/******************************************************************
;*                                                                 *
;*  WinMain                                                        *
;*                                                                 *
;*  Application entrypoint                                         *
;*                                                                 *
;******************************************************************/

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

  local vtable:DemoAppVtbl

    ;; Ignore the return value because we want to run the program even in the
    ;; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    CoInitialize(NULL)
    .if (SUCCEEDED(eax))

       .new app:DemoApp(&vtable)

        app.Initialize()

        .if (SUCCEEDED(eax))

            app.RunMessageLoop()
        .endif
        CoUninitialize()
    .endif

    .return 0

wWinMain endp


;/******************************************************************
;*                                                                 *
;*  DemoApp::DemoApp constructor                                   *
;*                                                                 *
;*  Initialize member data                                         *
;*                                                                 *
;******************************************************************/

DemoApp::DemoApp proc uses rdi vtable:ptr

    mov [rcx].DemoApp.lpVtbl,rdx
    lea rdi,[rcx+8]
    xor eax,eax
    mov ecx,(DemoApp - 8) / 8
    rep stosq
    mov rdi,rdx
    for q,<Release,
           Initialize,
           RunMessageLoop,
           CreateDeviceIndependentResources,
           CreateDeviceResources,
           DiscardDeviceResources,
           OnRender,
           OnResize>
        lea rax,DemoApp_&q
        stosq
        endm
    ret

DemoApp::DemoApp endp

    assume rsi:ptr DemoApp

;******************************************************************
;*                                                                *
;*  DemoApp::Release destructor                                   *
;*                                                                *
;*  Tear down resources                                           *
;*                                                                *
;******************************************************************

DemoApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pD2DFactory, ID2D1Factory)
    SafeRelease(&[rsi].m_pRT, ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pPathGeometry, ID2D1PathGeometry)
    SafeRelease(&[rsi].m_pObjectGeometry, ID2D1PathGeometry)
    SafeRelease(&[rsi].m_pRedBrush, ID2D1SolidColorBrush)
    SafeRelease(&[rsi].m_pYellowBrush, ID2D1SolidColorBrush)
    ret

DemoApp::Release endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::Initialize                                            *
;*                                                                 *
;*  Create application window and device-independent resources     *
;*                                                                 *
;******************************************************************/

DemoApp::Initialize proc uses rsi

  local wcex:WNDCLASSEX
  local dpiX:FLOAT, dpiY:FLOAT

    mov rsi,rcx

    ;;register window class

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

    .ifd !this.CreateDeviceIndependentResources()

        ;; Create the application window.
        ;;
        ;; Because the CreateWindow function takes its size in pixels, we
        ;; obtain the system DPI and use it to scale the window size.

        this.m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

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

        .if CreateWindowEx(
            0,
            L"D2DDemoApp",
            L"D2D Simple Path Animation Sample",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            ecx,
            edx,
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
            )
            mov [rsi].m_hwnd,rax

           .new length:float

            .ifd !this.m_pPathGeometry.ComputeLength(NULL, 0.25, &length)

                mov [rsi].m_Animation.m_Start,0.0       ;;start at beginning of path
                mov [rsi].m_Animation.m_End,length      ;;length at end of path
                mov [rsi].m_Animation.m_Duration,15.0   ;;seconds

                ZeroMemory(&[rsi].m_DwmTimingInfo, DWM_TIMING_INFO)
                mov [rsi].m_DwmTimingInfo.cbSize,DWM_TIMING_INFO

                ;; Get the composition refresh rate. If the DWM isn't running,
                ;; get the refresh rate from GDI -- probably going to be 60Hz

                DwmGetCompositionTimingInfo(NULL, &[rsi].m_DwmTimingInfo)

                .if (FAILED(eax))

                   .new hdc:HDC

                    mov hdc,GetDC([rsi].m_hwnd)
                    mov [rsi].m_DwmTimingInfo.rateCompose.uiDenominator,1
                    GetDeviceCaps(hdc, VREFRESH)
                    mov [rsi].m_DwmTimingInfo.rateCompose.uiNumerator,eax
                    ReleaseDC([rsi].m_hwnd, hdc)
                .endif

                ShowWindow([rsi].m_hwnd, SW_SHOWNORMAL)
                UpdateWindow([rsi].m_hwnd)
                mov eax,S_OK
            .endif
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret

DemoApp::Initialize endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::CreateDeviceIndependentResources                      *
;*                                                                 *
;*  This method is used to create resources which are not bound    *
;*  to any device. Their lifetime effectively extends for the      *
;*  duration of the app.                                           *
;*                                                                 *
;******************************************************************/

DemoApp::CreateDeviceIndependentResources proc uses rsi rbx

  local hr:HRESULT
  local pSink:ptr ID2D1GeometrySink

    mov rsi,rcx
    mov pSink,NULL

    ;; Create a Direct2D factory.
    mov hr,D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory,
            NULL,
            &[rsi].m_pD2DFactory
            )

    .if (SUCCEEDED(hr))

        ;; Create the path geometry.

        mov hr,this.m_pD2DFactory.CreatePathGeometry(&[rsi].m_pPathGeometry)
    .endif

    .if (SUCCEEDED(hr))

        ;; Write to the path geometry using the geometry sink. We are going to create a
        ;; spiral

        mov hr,this.m_pPathGeometry.Open(&pSink)
    .endif

    .if (SUCCEEDED(hr))

        .new radius:float
        .new locDelta:D2D1_POINT_2F
        .new currentLocation:D2D1_POINT_2F

        mov currentLocation.x,0.0
        mov currentLocation.y,0.0

        pSink.BeginFigure(currentLocation, D2D1_FIGURE_BEGIN_FILLED)

        mov locDelta.x,2.0
        mov locDelta.y,2.0
        mov radius,3.0

        .for (ebx = 0: ebx < 30: ++ebx)

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

        ;; Create the path geometry.

        mov hr,this.m_pD2DFactory.CreatePathGeometry(&[rsi].m_pObjectGeometry)
    .endif

    .if (SUCCEEDED(hr))

        ;; Write to the object geometry using the geometry sink.
        ;; We are going to create a simple triangle

        mov hr,this.m_pObjectGeometry.Open(&pSink)
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

DemoApp::CreateDeviceIndependentResources endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::CreateDeviceResources                                 *
;*                                                                 *
;*  This method creates resources which are bound to a particular  *
;*  D3D device. It's all centralized here, in case the resources   *
;*  need to be recreated in case of D3D device loss (eg. display   *
;*  change, remoting, removal of video card, etc).                 *
;*                                                                 *
;******************************************************************/

DemoApp::CreateDeviceResources proc uses rsi

    mov rsi,rcx
    xor eax,eax

    .if rax == [rsi].m_pRT

       .new rc:RECT

        GetClientRect([rsi].m_hwnd, &rc)

       .new size:D2D1_SIZE_U

        mov eax,rc.right
        sub eax,rc.left
        mov size.width,eax
        mov eax,rc.bottom
        sub eax,rc.top
        mov size.height,eax

        ;; Create a Direct2D render target

        mov r8, D2D1_HwndRenderTargetProperties([rsi].m_hwnd, size)
        mov rdx,D2D1_RenderTargetProperties()

        .ifd !this.m_pD2DFactory.CreateHwndRenderTarget(rdx, r8, &[rsi].m_pRT)

            ;; Create a red brush.

            mov rdx,D3DCOLORVALUE(Red, 1.0)
            .ifd !this.m_pRT.CreateSolidColorBrush(rdx, NULL, &[rsi].m_pRedBrush)

                ;; Create a yellow brush.

                mov rdx,D3DCOLORVALUE(Yellow, 1.0)
                this.m_pRT.CreateSolidColorBrush(rdx, NULL, &[rsi].m_pYellowBrush)
            .endif
        .endif
    .endif
    ret

DemoApp::CreateDeviceResources endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::DiscardDeviceResources                                *
;*                                                                 *
;*  Discard device-specific resources which need to be recreated   *
;*  when a D3D device is lost                                      *
;*                                                                 *
;******************************************************************/

DemoApp::DiscardDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pRT, ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pRedBrush, ID2D1SolidColorBrush)
    SafeRelease(&[rsi].m_pYellowBrush, ID2D1SolidColorBrush)
    ret

DemoApp::DiscardDeviceResources endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::RunMessageLoop                                        *
;*                                                                 *
;*  Main window message loop                                       *
;*                                                                 *
;******************************************************************/

DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

DemoApp::RunMessageLoop endp

;/******************************************************************
;*                                                                 *
;*  DemoApp::OnRender                                              *
;*                                                                 *
;*  Called whenever the application needs to display the client    *
;*  window. This method draws a single frame of animated content   *
;*                                                                 *
;*  Note that this function will not render anything if the window *
;*  is occluded (e.g. when the screen is locked).                  *
;*  Also, this function will automatically discard device-specific *
;*  resources if the D3D device disappears during function         *
;*  invocation, and will recreate the resources the next time it's *
;*  invoked.                                                       *
;*                                                                 *
;******************************************************************/

DemoApp::OnRender proc uses rsi ps:PAINTSTRUCT

  local hr:HRESULT
  local hdc:HDC
  local pRT:ptr ID2D1HwndRenderTarget

    mov rsi,rcx

    mov hdc,[rdx].PAINTSTRUCT.hdc
    mov hr, this.CreateDeviceResources()
    mov pRT,[rsi].m_pRT

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

        ;; Prepare to draw.
        pRT.BeginDraw()

        ;; Reset to identity transform
        pRT.SetTransform(m.Identity())

        ;;clear the render target contents
        pRT.Clear(D3DCOLORVALUE(Black, 1.0))

        ;;center the path
        m.SetProduct(&scale, &translation)
        pRT.SetTransform(&m)

        ;;draw the path in red
        pRT.DrawGeometry([rsi].m_pPathGeometry, [rsi].m_pRedBrush, 0.6, NULL)

        lea rcx,[rsi].m_Animation
        [rcx].Animation.GetValue([rsi].m_Time, EaseInOutExponentialAnimation)

        ;; Ask the geometry to give us the point that corresponds with the
        ;; length at the current time.

        mov hr,this.m_pPathGeometry.ComputePointAtLength(xmm0, NULL, 1.0, &point, &tangent)

        .assert(SUCCEEDED(hr))

        ;; Reorient the triangle so that it follows the
        ;; direction of the path.

        mov triangleMatrix._11,tangent.x
        mov triangleMatrix._12,tangent.y
        xor eax,0x80000000
        mov triangleMatrix._21,eax
        mov triangleMatrix._22,tangent.x
        mov triangleMatrix._31,point.x
        mov triangleMatrix._32,point.y
        m.SetProduct(&triangleMatrix, &m)

        pRT.SetTransform(&m)

        ;; Draw the yellow triangle.
        pRT.FillGeometry([rsi].m_pObjectGeometry, [rsi].m_pYellowBrush, NULL)

        ;; Commit the drawing operations.
        mov hr,pRT.EndDraw(NULL, NULL)

        .if (hr == D2DERR_RECREATE_TARGET)

            mov hr,S_OK
            this.DiscardDeviceResources()
        .endif

        ;; When we reach the end of the animation, loop back to the beginning.

        movss  xmm0,[rsi].m_Time
        comiss xmm0,[rsi].m_Animation.m_Duration

        .ifnb ;(float_time >= [rsi].m_Animation.GetDuration())

            mov [rsi].m_Time,0.0

        .else

            cvtsi2ss xmm1,[rsi].m_DwmTimingInfo.rateCompose.uiDenominator
            cvtsi2ss xmm2,[rsi].m_DwmTimingInfo.rateCompose.uiNumerator
            divss xmm1,xmm2
            addss xmm0,xmm1
            movss [rsi].m_Time,xmm0

        .endif
    .endif

    InvalidateRect([rsi].m_hwnd, NULL, FALSE)

    .return hr

DemoApp::OnRender endp


;/******************************************************************
;*                                                                 *
;*  DemoApp::OnResize                                              *
;*                                                                 *
;*  If the application receives a WM_SIZE message, this method     *
;*  resize the render target appropriately.                        *
;*                                                                 *
;******************************************************************/

DemoApp::OnResize proc width:UINT, height:UINT

    mov rcx,[rcx].DemoApp.m_pRT
    .if rcx

       .new size:D2D1_SIZE_U

        mov size.width,edx
        mov size.height,r8d

        ;; Note: This method can fail, but it's okay to ignore the
        ;; error here -- it will be repeated on the next call to
        ;; EndDraw.

        [rcx].ID2D1HwndRenderTarget.Resize(&size)
    .endif
    ret

DemoApp::OnResize endp


;/******************************************************************
;*                                                                 *
;*  DemoApp::WndProc                                               *
;*                                                                 *
;*  Window message handler                                         *
;*                                                                 *
;******************************************************************/

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
