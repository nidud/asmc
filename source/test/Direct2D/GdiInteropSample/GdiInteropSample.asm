;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/
;    Win7Samples/multimedia/Direct2D/GdiInteropSample
;
include GdiInteropSample.inc

.pragma warning(disable: 6004) ; procedure argument or local not referenced
.pragma warning(disable: 7007) ; .CASE without .ENDC: assumed fall through

.code
;******************************************************************
;*                                                                *
;*  WinMain                                                       *
;*                                                                *
;*  Application entrypoint                                        *
;*                                                                *
;******************************************************************

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

;******************************************************************
;*                                                                *
;*  DemoApp::DemoApp constructor                                  *
;*                                                                *
;*  Initialize member data                                        *
;*                                                                *
;******************************************************************

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
           OnRender>
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
    SafeRelease(&[rsi].m_pDCRT, ID2D1DCRenderTarget)
    SafeRelease(&[rsi].m_pBlackBrush, ID2D1SolidColorBrush)
    ret

DemoApp::Release endp

;*******************************************************************
;*                                                                 *
;*  DemoApp::Initialize                                            *
;*                                                                 *
;*  Create the application window and device-independent resources *
;*                                                                 *
;*******************************************************************

DemoApp::Initialize proc uses rsi

  local wcex:WNDCLASSEX
  local dpiX:FLOAT, dpiY:FLOAT

    mov rsi,rcx

    ;; Initialize device-indpendent resources, such
    ;; as the Direct2D factory.

    .ifd !this.CreateDeviceIndependentResources()

        ;; Register the window class.

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

        ;; Create the application window.
        ;;
        ;; Because the CreateWindow function takes its size in pixels, we
        ;; obtain the system DPI and use it to scale the window size.

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

        .if CreateWindowEx(
            0,
            L"D2DDemoApp",
            L"Direct2D Demo App",
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
            ShowWindow([rsi].m_hwnd, SW_SHOWNORMAL)
            UpdateWindow([rsi].m_hwnd)
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret

DemoApp::Initialize endp

;******************************************************************
;*                                                                *
;*  DemoApp::CreateDeviceIndependentResources                     *
;*                                                                *
;*  This method is used to create resources which are not bound   *
;*  to any device. Their lifetime effectively extends for the     *
;*  duration of the app.                                          *
;*                                                                *
;******************************************************************

DemoApp::CreateDeviceIndependentResources proc

    ;; Create D2D factory
    D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &IID_ID2D1Factory,
        NULL,
        &[rcx].DemoApp.m_pD2DFactory
        )
    ret

DemoApp::CreateDeviceIndependentResources endp

;******************************************************************
;*                                                                *
;*  DemoApp::CreateDeviceResources                                *
;*                                                                *
;*  This method creates resources which are bound to a particular *
;*  D3D device. It's all centralized here, in case the resources  *
;*  need to be recreated in case of D3D device loss (eg. display  *
;*  change, remoting, removal of video card, etc).                *
;*                                                                *
;******************************************************************

DemoApp::CreateDeviceResources proc uses rsi

  local hr:HRESULT

    mov rsi,rcx
    mov hr,S_OK

    .if ![rsi].m_pDCRT

        ;; Create a DC render target.

        mov rdx,D2D1_PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)
        mov rdx,D2D1_RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, rdx, 0, 0,
                D2D1_RENDER_TARGET_USAGE_NONE, D2D1_FEATURE_LEVEL_DEFAULT)

        mov hr,this.m_pD2DFactory.CreateDCRenderTarget(rdx, &[rsi].m_pDCRT)
        .if (SUCCEEDED(hr))

            ;; Create a black brush.

            mov rdx,D3DCOLORVALUE(Black, 1.0)
            mov hr,this.m_pDCRT.CreateSolidColorBrush(rdx, NULL, &[rsi].m_pBlackBrush)
        .endif
    .endif

    .return hr

DemoApp::CreateDeviceResources endp

;******************************************************************
;*                                                                *
;*  DemoApp::DiscardDeviceResources                               *
;*                                                                *
;*  Discard device-specific resources which need to be recreated  *
;*  when a D3D device is lost                                     *
;*                                                                *
;******************************************************************

DemoApp::DiscardDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pDCRT, ID2D1DCRenderTarget)
    SafeRelease(&[rsi].m_pBlackBrush, ID2D1SolidColorBrush)
    ret

DemoApp::DiscardDeviceResources endp

;******************************************************************
;*                                                                *
;*  DemoApp::RunMessageLoop                                       *
;*                                                                *
;*  Main window message loop                                      *
;*                                                                *
;******************************************************************

DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

DemoApp::RunMessageLoop endp


;*******************************************************************
;*                                                                 *
;*  DemoApp::OnRender                                              *
;*                                                                 *
;*  This method draws Direct2D content to a GDI HDC.               *
;*                                                                 *
;*  This method will automatically discard device-specific         *
;*  resources if the D3D device disappears during function         *
;*  invocation, and will recreate the resources the next time it's *
;*  invoked.                                                       *
;*                                                                 *
;*******************************************************************

DemoApp::OnRender proc uses rsi rdi rbx ps:PAINTSTRUCT


  local hr:HRESULT
  local rc:RECT
  local original:HGDIOBJ
  local blackPen:HPEN
  local pntArray1[2]:POINT
  local pntArray2[2]:POINT
  local pntArray3[2]:POINT
  local hdc:HDC
  local m:Matrix3x2F
  local p:ptr ID2D1DCRenderTarget
  local c:D3DCOLORVALUE

    mov rsi,rcx
    mov hdc,[rdx].PAINTSTRUCT.hdc

    ;; Get the dimensions of the client drawing area.

    GetClientRect([rsi].m_hwnd, &rc)

    ;;
    ;; Draw the pie chart with Direct2D.
    ;;

    ;; Create the DC render target.

    mov hr,[rsi].CreateDeviceResources()
    mov p,[rsi].m_pDCRT

    .if (SUCCEEDED(hr))

        ;; Bind the DC to the DC render target.

        mov hr,p.BindDC(hdc, &rc)

        m.Identity()
        c.Init(White, 1.0)
        p.BeginDraw()
        p.SetTransform(&m)
        p.Clear(&c)

       .new e:D2D1_ELLIPSE = { { 150.0, 150.0 }, 100.0, 100.0 }

        mov rdi,[rsi].m_pBlackBrush

        p.DrawEllipse(&e, rdi, 3.0, NULL)

        mov rbx,e.point
        mov e.point.x,150.0 + 100.0 * 0.15425
        mov e.point.y,150.0 - 100.0 * 0.988
        p.DrawLine(rbx, e.point, rdi, 3.0, NULL)

        mov e.point.x,150.0 + 100.0 * 0.525
        mov e.point.y,150.0 + 100.0 * 0.8509
        p.DrawLine(rbx, e.point, rdi, 3.0, NULL)

        mov e.point.x,150.0 - 100.0 * 0.988
        mov e.point.y,150.0 - 100.0 * 0.15425
        p.DrawLine(rbx, e.point, rdi, 3.0, NULL)

        mov hr,p.EndDraw(NULL, NULL)

        .if (SUCCEEDED(hr))

            ;;
            ;; Draw the pie chart with GDI.
            ;;

            ;; Save the original object.

            mov original,SelectObject(hdc, GetStockObject(DC_PEN))

            mov blackPen,CreatePen(PS_SOLID, 3, 0)
            SelectObject(hdc, blackPen)

            Ellipse(hdc, 300, 50, 500, 250)

            static_cast macro val
              local n
                n textequ <>
              % forc c,<@CatStr(%val)>
                ifidn <c>,<.>
                  exitm
                endif
                  n CatStr n,<c>
                  endm
                exitm<n>
                endm

            mov pntArray1[0*POINT].x,400
            mov pntArray1[0*POINT].y,150
            mov pntArray1[1*POINT].x,static_cast(400.0 + 100.0 * 0.15425)
            mov pntArray1[1*POINT].y,static_cast(150.0 - 100.0 * 0.9885)

            mov pntArray2[0*POINT].x,400
            mov pntArray2[0*POINT].y,150
            mov pntArray2[1*POINT].x,static_cast(400.0 + 100.0 * 0.525)
            mov pntArray2[1*POINT].y,static_cast(150.0 + 100.0 * 0.8509)

            mov pntArray3[0*POINT].x,400
            mov pntArray3[0*POINT].y,150
            mov pntArray3[1*POINT].x,static_cast(400.0 - 100.0 * 0.988)
            mov pntArray3[1*POINT].y,static_cast(150.0 - 100.0 * 0.15425)

            Polyline(hdc, &pntArray1, 2)
            Polyline(hdc, &pntArray2, 2)
            Polyline(hdc, &pntArray3, 2)

            DeleteObject(blackPen)

            ;; Restore the original object.
            SelectObject(hdc, original)
        .endif
    .endif

    .if (hr == D2DERR_RECREATE_TARGET)

        mov hr,S_OK
        this.DiscardDeviceResources()
    .endif

    .return hr

DemoApp::OnRender endp


;******************************************************************
;*                                                                *
;*  WndProc                                                       *
;*                                                                *
;*  Window message handler                                        *
;*                                                                *
;******************************************************************

WndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local result:LRESULT
  local pDemoApp:ptr DemoApp
  local wasHandled:BOOL
  local ps:PAINTSTRUCT

    mov wasHandled,FALSE
    mov result,0

    .if edx == WM_CREATE

        mov r8,[r9].CREATESTRUCT.lpCreateParams
        SetWindowLongPtrW(rcx, GWLP_USERDATA, PtrToUlong(r8))
        mov result,1

    .else

        mov pDemoApp,GetWindowLongPtrW(rcx, GWLP_USERDATA)
        mov wasHandled,FALSE

        .if rax

            .switch message

            .case WM_PAINT
            .case WM_DISPLAYCHANGE

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
