
include SimpleDirect2dApplication.inc

.code

;;
;; Provides the entry point to the application.
;;

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

;;
;; Initialize members.
;;

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
           CreateGridPatternBrush,
           DiscardDeviceResources,
           OnRender,
           OnResize,
           LoadResourceBitmap,
           LoadBitmapFromFile>
        lea rax,DemoApp_&q
        stosq
        endm
    ret

DemoApp::DemoApp endp


    assume rsi:ptr DemoApp

;;
;; Release resources.
;;

DemoApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pD2DFactory,             ID2D1Factory)
    SafeRelease(&[rsi].m_pWICFactory,             IWICImagingFactory)
    SafeRelease(&[rsi].m_pDWriteFactory,          IDWriteFactory)
    SafeRelease(&[rsi].m_pRenderTarget,           ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pTextFormat,             IDWriteTextFormat)
    SafeRelease(&[rsi].m_pPathGeometry,           ID2D1PathGeometry)
    SafeRelease(&[rsi].m_pLinearGradientBrush,    ID2D1LinearGradientBrush)
    SafeRelease(&[rsi].m_pBlackBrush,             ID2D1SolidColorBrush)
    SafeRelease(&[rsi].m_pGridPatternBitmapBrush, ID2D1BitmapBrush)
    SafeRelease(&[rsi].m_pBitmap,                 ID2D1Bitmap)
    ;SafeRelease(&[rsi].m_pAnotherBitmap,          ID2D1Bitmap)
    ret

DemoApp::Release endp


;;
;; Creates the application window and initializes
;; device-independent resources.
;;
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
            L"Direct2D Demo Application",
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
        .endif
    .endif
    ret

DemoApp::Initialize endp


;;
;; Create resources which are not bound
;; to any device. Their lifetime effectively extends for the
;; duration of the app. These resources include the Direct2D,
;; DirectWrite, and WIC factories; and a DirectWrite Text Format object
;; (used for identifying particular font characteristics) and
;; a Direct2D geometry.
;;

DemoApp::CreateDeviceIndependentResources proc uses rsi

  local hr:HRESULT
  local pSink:ptr ID2D1GeometrySink

    mov pSink,NULL
    mov rdi,rcx

    ;; Create a Direct2D factory.

    mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &IID_ID2D1Factory, NULL, &[rsi].m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ;; Create WIC factory.

        mov hr,CoCreateInstance(
            &CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IWICImagingFactory,
            &[rsi].m_pWICFactory
            )
    .endif

    .if (SUCCEEDED(hr))

        ;; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            &IID_IDWriteFactory,
            &[rsi].m_pDWriteFactory
            )
    .endif

    .if (SUCCEEDED(hr))

        ;; Create a DirectWrite text format object.

        mov hr,this.m_pDWriteFactory.CreateTextFormat(
            L"Verdana",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            50.0,
            L"",
            &[rsi].m_pTextFormat
            )
    .endif

    .if (SUCCEEDED(hr))

        ;; Center the text horizontally and vertically.

        this.m_pTextFormat.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
        this.m_pTextFormat.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)

        ;; Create a path geometry.

        mov hr,this.m_pD2DFactory.CreatePathGeometry(&[rsi].m_pPathGeometry)
    .endif

    .if (SUCCEEDED(hr))

        ;; Use the geometry sink to write to the path geometry.

        mov hr,this.m_pPathGeometry.Open(&pSink)
    .endif

    .if (SUCCEEDED(hr))

       .new b:D2D1_BEZIER_SEGMENT

        pSink.SetFillMode(D2D1_FILL_MODE_ALTERNATE)
        pSink.BeginFigure(0, D2D1_FIGURE_BEGIN_FILLED)

        mov b.point1.x,200.0
        mov b.point1.y,0.0
        pSink.AddLine(b.point1)

        mov b.point1.x,150.0
        mov b.point1.y,50.0
        mov b.point2.x,150.0
        mov b.point2.y,150.0
        mov b.point3.x,200.0
        mov b.point3.y,200.0
        pSink.AddBezier(&b)

        mov b.point1.x,0.0
        mov b.point1.y,200.0
        pSink.AddLine(b.point1)

        mov b.point1.x,50.0
        mov b.point1.y,150.0
        mov b.point2.x,50.0
        mov b.point2.y,50.0
        mov b.point3.x,0.0
        mov b.point3.y,0.0
        pSink.AddBezier(&b)

        pSink.EndFigure(D2D1_FIGURE_END_CLOSED)
        mov hr,pSink.Close()
    .endif

    pSink.Release()

    .return hr

DemoApp::CreateDeviceIndependentResources endp

;;
;;  This method creates resources which are bound to a particular
;;  Direct3D device. It's all centralized here, in case the resources
;;  need to be recreated in case of Direct3D device loss (eg. display
;;  change, remoting, removal of video card, etc).
;;

GetSampleFile proc

  local wsaData:WSADATA
  local hINet:HINTERNET
  local hFile:HANDLE
  local dwNumberOfBytesRead:uint_t
  local fp:LPFILE
  local buffer[1024]:char_t
  local hr:HRESULT

    .return S_OK   .ifd GetFileAttributes(".\\sampleImage.jpg") != -1
    .return E_FAIL .ifd WSAStartup(2, &wsaData)
    .return E_FAIL .if !InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)

    mov hINet,rax
    mov hr,S_OK

    .if InternetOpenUrl(hINet,
            "https://github.com/microsoft/Windows-classic-samples/raw/master/Samples/"
            "Win7Samples/multimedia/Direct2D/SimpleDirect2DApplication/sampleImage.jpg",
            NULL, 0, 0, 0 )

        mov hFile,rax
        .if _wfopen(".\\sampleImage.jpg", "wb")

            mov fp,rax
            .while 1

                InternetReadFile(hFile, &buffer, 1024, &dwNumberOfBytesRead)
                .break .if !dwNumberOfBytesRead
                fwrite(&buffer, dwNumberOfBytesRead, 1, fp)
            .endw
            fclose(fp)
        .else
            mov hr,E_FAIL
        .endif
    .endif

    InternetCloseHandle(hINet)
    WSACleanup()

    .return hr

GetSampleFile endp

DemoApp::CreateDeviceResources proc uses rsi rdi rbx

  local hr:HRESULT
  local rc:RECT
  local size:D2D1_SIZE_U

    mov rsi,rcx
    mov hr,S_OK

    .if (![rsi].m_pRenderTarget)

        GetClientRect([rsi].m_hwnd, &rc)

        mov eax,rc.right
        sub eax,rc.left
        mov size.width,eax
        mov eax,rc.bottom
        sub eax,rc.top
        mov size.height,eax

        ;; Create a Direct2D render target.

        mov rdi,D2D1::RenderTargetProperties()
        mov r8,D2D1::HwndRenderTargetProperties([rsi].m_hwnd, size)
        mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(rdi, r8, &[rsi].m_pRenderTarget)

        .if (SUCCEEDED(hr))

            ;; Create a black brush.

            mov rdx,D3DCOLORVALUE(Black, 1.0)
            mov rdi,[rsi].m_pRenderTarget
            mov hr,[rdi].ID2D1HwndRenderTarget.CreateSolidColorBrush(rdx, NULL, &[rsi].m_pBlackBrush)
        .endif

        .if (SUCCEEDED(hr))

           .new pGradientStops:ptr ID2D1GradientStopCollection

            mov pGradientStops,NULL

            ;; Create a linear gradient.

           .new stops[2]:D2D1_GRADIENT_STOP

            mov stops.position,0.0
            mov stops.color.r,0.0
            mov stops.color.g,1.0
            mov stops.color.b,1.0
            mov stops.color.a,0.25
            mov stops[D2D1_GRADIENT_STOP].position,1.0
            mov stops[D2D1_GRADIENT_STOP].color.r,0.0
            mov stops[D2D1_GRADIENT_STOP].color.g,0.0
            mov stops[D2D1_GRADIENT_STOP].color.b,1.0
            mov stops[D2D1_GRADIENT_STOP].color.a,1.0

            mov hr,[rdi].ID2D1HwndRenderTarget.CreateGradientStopCollection(
                &stops, ARRAYSIZE(stops), D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops )

            .if (SUCCEEDED(hr))

               .new lg:D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES

                mov lg.startPoint.x,100.0
                mov lg.startPoint.y,0.0
                mov lg.endPoint.x,100.0
                mov lg.endPoint.y,200.0

                mov r8,D2D1::BrushProperties()
                mov hr,[rdi].ID2D1HwndRenderTarget.CreateLinearGradientBrush(
                        &lg, r8, pGradientStops, &[rsi].m_pLinearGradientBrush )

                pGradientStops.Release()
            .endif
        .endif

        ;; Create a bitmap from an application resource.

        ;; get the image from git..

        mov hr,GetSampleFile()

        .if (SUCCEEDED(hr))

            mov hr,this.LoadBitmapFromFile(
                [rsi].m_pRenderTarget,
                [rsi].m_pWICFactory,
                L".\\sampleImage.jpg",
                100,
                0,
                &[rsi].m_pBitmap
                )
        .endif

        .if (SUCCEEDED(hr))

            ;; Create a bitmap by loading it from a file.

            mov [rsi].m_pAnotherBitmap,[rsi].m_pBitmap
        .endif

        .if (SUCCEEDED(hr))

            mov hr,[rsi].CreateGridPatternBrush([rsi].m_pRenderTarget, &[rsi].m_pGridPatternBitmapBrush)
        .endif
    .endif

    .return hr

DemoApp::CreateDeviceResources endp

;;
;; Creates a pattern brush.
;;
DemoApp::CreateGridPatternBrush proc pRenderTarget:ptr ID2D1RenderTarget,
        ppBitmapBrush:ptr ptr ID2D1BitmapBrush

  local hr:HRESULT
  local pCompatibleRenderTarget:ptr ID2D1BitmapRenderTarget

    mov hr,S_OK

    ;; Create a compatible render target.

    mov pCompatibleRenderTarget,NULL
    mov rdx,D2D1::SizeF(10.0, 10.0)
    mov hr,pRenderTarget.CreateCompatibleRenderTarget(
        rdx,
        NULL,
        NULL,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
        &pCompatibleRenderTarget
        )

    .if (SUCCEEDED(hr))

        ;; Draw a pattern.

        .new pGridBrush:ptr ID2D1SolidColorBrush
        .new color:D3DCOLORVALUE

        mov color.r,0.93
        mov color.g,0.94
        mov color.b,0.96
        mov color.a,1.0
        mov pGridBrush,NULL

        mov hr,pCompatibleRenderTarget.CreateSolidColorBrush(
            &color,
            NULL,
            &pGridBrush
            )

        .if (SUCCEEDED(hr))

            pCompatibleRenderTarget.BeginDraw()
            pCompatibleRenderTarget.FillRectangle(D2D1::RectF(0.0, 0.0, 10.0, 1.0), pGridBrush)
            pCompatibleRenderTarget.FillRectangle(D2D1::RectF(0.0, 0.1, 1.0, 10.0), pGridBrush)
            pCompatibleRenderTarget.EndDraw(NULL, NULL)

            ;; Retrieve the bitmap from the render target.

           .new pGridBitmap:ptr ID2D1Bitmap

            mov pGridBitmap,NULL
            mov hr,pCompatibleRenderTarget.GetBitmap(&pGridBitmap)

            .if (SUCCEEDED(hr))

                ;; Choose the tiling mode for the bitmap brush.

                mov r8,D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP)

                ;; Create the bitmap brush.

                mov hr,this.m_pRenderTarget.CreateBitmapBrush(
                        pGridBitmap,
                        r8,
                        NULL,
                        ppBitmapBrush
                        )

                pGridBitmap.Release()
            .endif
            pGridBrush.Release()
        .endif

        pCompatibleRenderTarget.Release()
    .endif

    .return hr

DemoApp::CreateGridPatternBrush endp

;;
;;  Discard device-specific resources which need to be recreated
;;  when a Direct3D device is lost
;;

DemoApp::DiscardDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pRenderTarget, ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pBitmap, ID2D1Bitmap)
    SafeRelease(&[rsi].m_pBlackBrush, ID2D1SolidColorBrush)
    SafeRelease(&[rsi].m_pLinearGradientBrush, ID2D1LinearGradientBrush)
    ;SafeRelease(&[rsi].m_pAnotherBitmap, ID2D1Bitmap)
    SafeRelease(&[rsi].m_pGridPatternBitmapBrush, ID2D1BitmapBrush)
    ret

DemoApp::DiscardDeviceResources endp

;;
;; The main window message loop.
;;

DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

DemoApp::RunMessageLoop endp


;;
;;  Called whenever the application needs to display the client
;;  window. This method draws a bitmap a couple times, draws some
;;  geometries, and writes "Hello, World"
;;
;;  Note that this function will not render anything if the window
;;  is occluded (e.g. when the screen is locked).
;;  Also, this function will automatically discard device-specific
;;  resources if the Direct3D device disappears during function
;;  invocation, and will recreate the resources the next time it's
;;  invoked.
;;

sc_helloWorld equ <L"Hello, World!">

DemoApp::OnRender proc uses rsi

  local hr:HRESULT
  local m:Matrix3x2F
  local r:D2D1_RECT_F
  local rotation:Matrix3x2F
  local pRT:ptr ID2D1HwndRenderTarget

    mov rsi,rcx

    mov hr,this.CreateDeviceResources()
    .return .if eax

    mov pRT,[rsi].m_pRenderTarget

    .if ( !( pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED ) )


        ;; Retrieve the size of the render target.

       .new renderTargetSize:D2D1_SIZE_F
       .new size:D2D1_SIZE_F

        pRT.GetSize(&renderTargetSize)
        pRT.BeginDraw()
        pRT.SetTransform(m.Identity())
        pRT.Clear(D3DCOLORVALUE(White, 1.0))

        ;; Paint a grid background.

        mov r.left,   0.0
        mov r.top,    0.0
        mov r.right,  renderTargetSize.width
        mov r.bottom, renderTargetSize.height

        pRT.FillRectangle(&r, [rsi].m_pGridPatternBitmapBrush)

        this.m_pBitmap.GetSize(&size)

        ;; Draw a bitmap in the upper-left corner of the window.

        mov r.right,  size.width
        mov r.bottom, size.height
        pRT.DrawBitmap([rsi].m_pBitmap, &r, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL)

        ;; Draw a bitmap at the lower-right corner of the window.

        this.m_pAnotherBitmap.GetSize(&size)

        movss xmm0,renderTargetSize.width
        subss xmm0,size.width
        movss xmm1,renderTargetSize.height
        subss xmm1,size.height
        movss r.left,xmm0
        movss r.top,xmm1
        mov   r.right,renderTargetSize.width
        mov   r.bottom,renderTargetSize.height

        pRT.DrawBitmap([rsi].m_pAnotherBitmap, &r, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL)

        ;; Set the world transform to a 45 degree rotation at the center of the render target
        ;; and write "Hello, World".

        movss xmm0,renderTargetSize.width
        divss xmm0,2.0
        movss xmm1,renderTargetSize.height
        divss xmm1,2.0
        movss size.width,xmm0
        movss size.height,xmm1
        rotation.Rotation(45.0, size)

        pRT.SetTransform(&rotation)

        mov r.left, 0.0
        mov r.top,  0.0

        pRT.DrawText(
            sc_helloWorld,
            13,
            [rsi].m_pTextFormat,
            &r,
            [rsi].m_pBlackBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

        ;;
        ;; Reset back to the identity transform
        ;;

        movss xmm0,renderTargetSize.height
        subss xmm0,200.0
        movss m._32,xmm0
        pRT.SetTransform(&m)

        ;; Fill the hour glass geometry with a gradient.

        pRT.FillGeometry(
            [rsi].m_pPathGeometry,
            [rsi].m_pLinearGradientBrush,
            NULL
            )

        mov   m._32,0.0
        movss xmm0,renderTargetSize.width
        subss xmm0,200.0
        movss m._31,xmm0
        pRT.SetTransform(&m)

        ;; Fill the hour glass geometry with a gradient.

        pRT.FillGeometry(
            [rsi].m_pPathGeometry,
            [rsi].m_pLinearGradientBrush,
            NULL
            )

        mov hr,pRT.EndDraw(NULL, NULL)
        .if (hr == D2DERR_RECREATE_TARGET)

            mov hr,S_OK
            this.DiscardDeviceResources()
        .endif
    .endif

    .return hr

DemoApp::OnRender endp

;;
;;  If the application receives a WM_SIZE message, this method
;;  resize the render target appropriately.
;;

DemoApp::OnResize proc width:UINT, height:UINT

    mov rcx,[rcx].DemoApp.m_pRenderTarget
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


;;
;; The window message handler.
;;

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
                pDemoApp.OnRender()
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

;;
;; Creates a Direct2D bitmap from a resource in the
;; application resource file.
;;

DemoApp::LoadResourceBitmap proc \
    pRenderTarget:      ptr ID2D1RenderTarget,
    pIWICFactory:       ptr IWICImagingFactory,
    resourceName:       PCWSTR,
    resourceType:       PCWSTR,
    destinationWidth:   UINT,
    destinationHeight:  UINT,
    ppBitmap:           ptr ptr ID2D1Bitmap


  local hr:             HRESULT
  local pDecoder:       ptr IWICBitmapDecoder
  local pSource:        ptr IWICBitmapFrameDecode
  local pStream:        ptr IWICStream
  local pConverter:     ptr IWICFormatConverter
  local pScaler:        ptr IWICBitmapScaler

  local imageResHandle: HRSRC
  local imageResDataHandle: HGLOBAL
  local pImageFile:     PVOID
  local imageFileSize:  DWORD

    xor eax,eax
    mov hr,eax
    mov pDecoder,rax
    mov pSource,rax
    mov pStream,rax
    mov pConverter,rax
    mov pScaler,rax

    mov imageResHandle,rax
    mov imageResDataHandle,rax
    mov pImageFile,rax
    mov imageFileSize,eax

    ;; Locate the resource.

    mov imageResHandle,FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType)
    mov hr,E_FAIL
    .if rax
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        ;; Load the resource.

        mov imageResDataHandle,LoadResource(HINST_THISCOMPONENT, imageResHandle)
        mov hr,E_FAIL
        .if rax
            mov hr,S_OK
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Lock it to get a system memory pointer.

        mov pImageFile,LockResource(imageResDataHandle)
        mov hr,E_FAIL
        .if rax
            mov hr,S_OK
        .endif

    .endif

    .if (SUCCEEDED(hr))

        ;; Calculate the size.

        mov imageFileSize,SizeofResource(HINST_THISCOMPONENT, imageResHandle)
        mov hr,E_FAIL
        .if rax
            mov hr,S_OK
        .endif

    .endif

    .if (SUCCEEDED(hr))

        ;; Create a WIC stream to map onto the memory.

        mov hr,pIWICFactory.CreateStream(&pStream)

    .endif

    .if (SUCCEEDED(hr))

        ;; Initialize the stream with the memory pointer and size.

        mov hr,pStream.InitializeFromMemory(
            pImageFile,
            imageFileSize
            )
    .endif

    .if (SUCCEEDED(hr))

        ;; Create a decoder for the stream.

        mov hr,pIWICFactory.CreateDecoderFromStream(
            pStream,
            NULL,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
            )
    .endif

    .if (SUCCEEDED(hr))

        ;; Create the initial frame.

        mov hr,pDecoder.GetFrame(0, &pSource)
    .endif

    .if (SUCCEEDED(hr))

        ;; Convert the image format to 32bppPBGRA
        ;; (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).

        mov hr,pIWICFactory.CreateFormatConverter(&pConverter)
    .endif

    .if (SUCCEEDED(hr))

        ;; If a new width or height was specified, create an
        ;; IWICBitmapScaler and use it to resize the image.

        .if (destinationWidth != 0 || destinationHeight != 0)

           .new originalWidth:UINT, originalHeight:UINT

            mov hr,pSource.GetSize(&originalWidth, &originalHeight)

            .if (SUCCEEDED(hr))

                .if (destinationWidth == 0)

                    cvtsi2ss xmm0,destinationHeight
                    cvtsi2ss xmm1,originalHeight
                    divss    xmm0,xmm1
                    cvtsi2ss xmm1,originalWidth
                    mulss    xmm0,xmm1
                    cvtss2si eax,xmm0
                    mov destinationWidth,eax

                .elseif (destinationHeight == 0)


                    cvtsi2ss xmm0,destinationWidth
                    cvtsi2ss xmm1,originalWidth
                    divss    xmm0,xmm1
                    cvtsi2ss xmm1,originalHeight
                    mulss    xmm0,xmm1
                    cvtss2si eax,xmm0
                    mov destinationHeight,eax

                .endif

                mov hr,pIWICFactory.CreateBitmapScaler(&pScaler)
                .if (SUCCEEDED(hr))

                    mov hr,pScaler.Initialize(
                            pSource,
                            destinationWidth,
                            destinationHeight,
                            WICBitmapInterpolationModeCubic
                            )
                    .if (SUCCEEDED(hr))

                        mov hr,pConverter.Initialize(
                            pScaler,
                            &GUID_WICPixelFormat32bppPBGRA,
                            WICBitmapDitherTypeNone,
                            NULL,
                            0.0,
                            WICBitmapPaletteTypeMedianCut
                            )
                    .endif
                .endif
            .endif

        .else

            mov hr,pConverter.Initialize(
                pSource,
                &GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.0,
                WICBitmapPaletteTypeMedianCut
                )
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;;create a Direct2D bitmap from the WIC bitmap.

        mov hr,pRenderTarget.CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
            ppBitmap
            )
    .endif

    SafeRelease(&pDecoder,      IWICBitmapDecoder)
    SafeRelease(&pSource,       IWICBitmapFrameDecode)
    SafeRelease(&pStream,       IWICStream)
    SafeRelease(&pConverter,    IWICFormatConverter)
    SafeRelease(&pScaler,       IWICBitmapScaler)

    .return hr

DemoApp::LoadResourceBitmap endp

;;
;; Creates a Direct2D bitmap from the specified
;; file name.
;;

DemoApp::LoadBitmapFromFile proc \
    pRenderTarget:      ptr ID2D1RenderTarget,
    pIWICFactory:       ptr IWICImagingFactory,
    uri:                PCWSTR,
    destinationWidth:   UINT,
    destinationHeight:  UINT,
    ppBitmap:           ptr ptr ID2D1Bitmap


  local hr:             HRESULT
  local pDecoder:       ptr IWICBitmapDecoder
  local pSource:        ptr IWICBitmapFrameDecode
  local pStream:        ptr IWICStream
  local pConverter:     ptr IWICFormatConverter
  local pScaler:        ptr IWICBitmapScaler

    mov hr,S_OK

    mov pDecoder,NULL
    mov pSource,NULL
    mov pStream,NULL
    mov pConverter,NULL
    mov pScaler,NULL

    mov hr,pIWICFactory.CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
        )
    .if (SUCCEEDED(hr))


        ;; Create the initial frame.

        mov hr,pDecoder.GetFrame(0, &pSource)
    .endif

    .if (SUCCEEDED(hr))

        ;; Convert the image format to 32bppPBGRA
        ;; (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).

        mov hr,pIWICFactory.CreateFormatConverter(&pConverter)
    .endif

    .if (SUCCEEDED(hr))

        ;; If a new width or height was specified, create an
        ;; IWICBitmapScaler and use it to resize the image.

        .if (destinationWidth != 0 || destinationHeight != 0)

            .new originalWidth:UINT, originalHeight:UINT

            mov hr,pSource.GetSize(&originalWidth, &originalHeight)

            .if (SUCCEEDED(hr))

                .if (destinationWidth == 0)

                    cvtsi2ss xmm0,destinationHeight
                    cvtsi2ss xmm1,originalHeight
                    divss    xmm0,xmm1
                    cvtsi2ss xmm1,originalWidth
                    mulss    xmm0,xmm1
                    cvtss2si eax,xmm0
                    mov destinationWidth,eax

                .elseif (destinationHeight == 0)

                    cvtsi2ss xmm0,destinationWidth
                    cvtsi2ss xmm1,originalWidth
                    divss    xmm0,xmm1
                    cvtsi2ss xmm1,originalHeight
                    mulss    xmm0,xmm1
                    cvtss2si eax,xmm0
                    mov destinationHeight,eax

                .endif

                mov hr,pIWICFactory.CreateBitmapScaler(&pScaler)
                .if (SUCCEEDED(hr))

                    mov hr,pScaler.Initialize(
                            pSource,
                            destinationWidth,
                            destinationHeight,
                            WICBitmapInterpolationModeCubic
                            )
                .endif
                .if (SUCCEEDED(hr))

                    mov hr,pConverter.Initialize(
                        pScaler,
                        &GUID_WICPixelFormat32bppPBGRA,
                        WICBitmapDitherTypeNone,
                        NULL,
                        0.0,
                        WICBitmapPaletteTypeMedianCut
                        )
                .endif
            .endif

        .else ;; Don't scale the image.

            mov hr,pConverter.Initialize(
                pSource,
                &GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.0,
                WICBitmapPaletteTypeMedianCut
                )
        .endif
    .endif
    .if (SUCCEEDED(hr))

        ;; Create a Direct2D bitmap from the WIC bitmap.

        mov hr,pRenderTarget.CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
            ppBitmap
            )
    .endif

    SafeRelease(&pDecoder,      IWICBitmapDecoder)
    SafeRelease(&pSource,       IWICBitmapFrameDecode)
    SafeRelease(&pStream,       IWICStream)
    SafeRelease(&pConverter,    IWICFormatConverter)
    SafeRelease(&pScaler,       IWICBitmapScaler)

    .return hr

DemoApp::LoadBitmapFromFile endp

    end _tstart
