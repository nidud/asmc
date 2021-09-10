; GEOMETRYREALIZATIONSAMPLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; From: https://github.com/microsoft/Windows-classic-samples/
;

include stdafx.inc
ifdef _MSVCRT
include GeometryRealization.asm
endif

sc_fontName             equ <"Calibri">
sc_fontSize             equ 20.0
sc_textInfoBox          equ <10.0, 10.0, 350.0, 200.0>
sc_textInfoBoxInset     equ 10.0
sc_defaultNumSquares    equ 16
sc_minNumSquares        equ 1
sc_maxNumSquares        equ 1024
sc_boardWidth           equ 900.0
sc_rotationSpeed        equ 3.0
sc_loupeInset           equ 20.0
sc_maxZoom              equ 15.0
sc_minZoom              equ 1.0
sc_zoomStep             equ 1.5
sc_zoomSubStep          equ 1.1
sc_strokeWidth          equ 1.0

; This determines that maximum texture size we will
; generate for our realizations.

sc_maxRealizationDimension equ 2000

.code

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

  local vtable:DemoAppVtbl
  local tmring:RingBuffer

    ; Ignore the return value because we want to continue running even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .if (SUCCEEDED(CoInitialize(NULL)))

        .new app:DemoApp(&vtable, &tmring)

        .if (SUCCEEDED(app.Initialize()))

            app.RunMessageLoop()
        .endif
        app.Release()
        CoUninitialize()
    .endif
    .return 0

wWinMain endp


    assume rsi:ptr DemoApp

DemoApp::DemoApp proc uses rdi rsi vtable:ptr, tmring:ptr

  local time:LARGE_INTEGER

    mov rsi,rcx
    mov [rcx].DemoApp.lpVtbl,rdx
    lea rdi,[rcx+8]
    xor eax,eax
    mov ecx,(DemoApp - 8) / 8
    rep stosq
    mov [r8],rax
    mov [rsi].m_times,r8

    mov rdi,rdx
    for q,<Release,
           Initialize,
           RunMessageLoop,
           CreateDeviceIndependentResources,
           CreateGeometries,
           CreateDeviceResources,
           DiscardDeviceResources,
           DiscardGeometryData,
           RenderMainContent,
           RenderTextInfo,
           OnRender,
           OnResize,
           OnMouseMove,
           OnKeyDown,
           OnWheel>
        lea rax,DemoApp_&q
        stosq
        endm

    mov [rsi].m_updateRealization,TRUE
    ;mov [rsi].m_drawStroke,TRUE
    mov [rsi].m_autoGeometryRegen,TRUE
    mov [rsi].m_numSquares,sc_defaultNumSquares
    mov [rsi].m_targetZoomFactor,1.0
    mov [rsi].m_currentZoomFactor,1.0

    QueryPerformanceCounter(&time)
    mov rax,time.QuadPart
    neg rax
    mov [rsi].m_timeDelta,rax
    ret

DemoApp::DemoApp endp


DemoApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_pD2DFactory)
    SafeRelease([rsi].m_pWICFactory)
    SafeRelease([rsi].m_pDWriteFactory)
    SafeRelease([rsi].m_pRT)
    SafeRelease([rsi].m_pTextFormat)
    SafeRelease([rsi].m_pSolidColorBrush)
    SafeRelease([rsi].m_pRealization)
    SafeRelease([rsi].m_pGeometry)
    ret

DemoApp::Release endp


DemoApp::Initialize proc uses rsi

  local wcex:WNDCLASSEX
  local dpiX:float, dpiY:float

    mov rsi,rcx

    ; Initialize device-indpendent resources, such
    ; as the Direct2D factory.

    .ifd ( !this.CreateDeviceIndependentResources() )

        ; Register the window class.

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
        mov wcex.lpszClassName, &@CStr("D2DDemoApp")

        RegisterClassEx(&wcex)

        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.

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

        .if CreateWindowEx(0, "D2DDemoApp", "D2D Demo App",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, ecx, edx,
                NULL, NULL, HINST_THISCOMPONENT, this)

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

;
;  This method is used to create resources which are not bound
;  to any device. Their lifetime effectively extends for the
;  duration of the app. These resources include the D2D,
;  DWrite, and WIC factories; and a DWrite Text Format object
;  (used for identifying particular font characteristics) and
;  a D2D geometry.
;

DemoApp::CreateDeviceIndependentResources proc uses rsi

  local hr:HRESULT

    mov rsi,rcx

    ; Create the Direct2D factory.

    mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &IID_ID2D1Factory, NULL, &[rsi].m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ; Create WIC factory.

        mov hr,CoCreateInstance(
            &CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IWICImagingFactory,
            &[rsi].m_pWICFactory
            )
    .endif

    .if (SUCCEEDED(hr))

        ; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            &IID_IDWriteFactory,
            &[rsi].m_pDWriteFactory
            )
    .endif


    .if (SUCCEEDED(hr))

        ; Create a DirectWrite text format object.

        mov hr,this.m_pDWriteFactory.CreateTextFormat(
            sc_fontName,
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            sc_fontSize,
            L"",
            &[rsi].m_pTextFormat
            )
    .endif
    .return hr

DemoApp::CreateDeviceIndependentResources endp

;
;  This method creates resources which are bound to a particular
;  D3D device. It's all centralized here, in case the resources
;  need to be recreated in case of D3D device loss (eg. display
;  change, remoting, removal of video card, etc).
;

DemoApp::CreateDeviceResources proc uses rsi

  .new hr:HRESULT = S_OK
  .new rc:RECT
  .new pRealizationFactory:ptr IGeometryRealizationFactory = NULL

    mov rsi,rcx

    .if ( ![rsi].m_pRT )

        GetClientRect([rsi].m_hwnd, &rc)

        ; Create a Direct2D render target.

       .new p:D2D1_RENDER_TARGET_PROPERTIES
        mov p.type,     D2D1_RENDER_TARGET_TYPE_DEFAULT
        mov p.dpiX,     0.0
        mov p.dpiY,     0.0
        mov p.usage,    D2D1_RENDER_TARGET_USAGE_NONE
        mov p.minLevel, D2D1_FEATURE_LEVEL_DEFAULT
        mov p.pixelFormat.format,DXGI_FORMAT_UNKNOWN
        mov p.pixelFormat.alphaMode,D2D1_ALPHA_MODE_UNKNOWN

       .new h:D2D1_HWND_RENDER_TARGET_PROPERTIES
        mov h.hwnd,[rsi].m_hwnd
        mov eax,rc.bottom
        sub eax,rc.top
        mov h.pixelSize.height,eax
        mov eax,rc.right
        sub eax,rc.left
        mov h.pixelSize.width,eax
        mov h.presentOptions,D2D1_PRESENT_OPTIONS_NONE

        mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(&p, &h, &[rsi].m_pRT)

        .if (SUCCEEDED(hr))

            ; Create brushes.

           .new color:D3DCOLORVALUE(White, 1.0)

            mov hr,this.m_pRT.CreateSolidColorBrush(
                &color,
                NULL,
                &[rsi].m_pSolidColorBrush
                )
        .endif

        .if (SUCCEEDED(hr))

            mov hr,CreateGeometryRealizationFactory(
                [rsi].m_pRT,
                sc_maxRealizationDimension,
                &pRealizationFactory
                )
        .endif
        .if (SUCCEEDED(hr))

            mov hr,pRealizationFactory.CreateGeometryRealization(
                &[rsi].m_pRealization
                )
        .endif
        .if (SUCCEEDED(hr))

            mov [rsi].m_updateRealization,TRUE
        .endif
        SafeRelease(pRealizationFactory)
    .endif
    .return hr

DemoApp::CreateDeviceResources endp

;
; Discard device-specific resources which need to be recreated
; when a Direct3D device is lost.
;

DemoApp::DiscardDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_pRT)
    SafeRelease([rsi].m_pSolidColorBrush)
    SafeRelease([rsi].m_pRealization)
    ret

DemoApp::DiscardDeviceResources endp


DemoApp::DiscardGeometryData proc

    mov [rcx].DemoApp.m_updateRealization,TRUE
    SafeRelease([rcx].DemoApp.m_pGeometry)
    ret

DemoApp::DiscardGeometryData endp


DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

DemoApp::RunMessageLoop endp


DemoApp::CreateGeometries proc uses rsi

  .new hr:HRESULT = S_OK

    mov rsi,rcx

    .if ( [rsi].m_pGeometry == NULL )

       .new squareWidth:float
       .new pFactory:ptr ID2D1Factory
       .new pRealization:ptr IGeometryRealization = NULL
       .new pGeometry:ptr ID2D1TransformedGeometry = NULL
       .new pPathGeometry:ptr ID2D1PathGeometry = NULL
       .new pSink:ptr ID2D1GeometrySink = NULL

        movss       xmm0,0.9 * sc_boardWidth
        cvtsi2ss    xmm1,[rsi].m_numSquares
        divss       xmm0,xmm1
        movss       squareWidth,xmm0
        mov         pFactory,[rsi].m_pD2DFactory

        ; Create the path geometry.

        mov hr,pFactory.CreatePathGeometry(&pPathGeometry)

        .if (SUCCEEDED(hr))

            ; Write to the path geometry using the geometry sink to
            ; create an hour glass shape.

            mov hr,pPathGeometry.Open(&pSink)
        .endif

        .if (SUCCEEDED(hr))

            pSink.SetFillMode(D2D1_FILL_MODE_ALTERNATE)
            pSink.BeginFigure(0, D2D1_FIGURE_BEGIN_FILLED)

            mov edx,1.0
            pSink.AddLine(rdx)

           .new b:D2D1_BEZIER_SEGMENT = {
                { 0.75, 0.25 },
                { 0.75, 0.75 },
                { 1.0, 1.0 } }

            pSink.AddBezier(&b)

            mov edx,1.0
            shl rdx,32
            pSink.AddLine(rdx)

            mov b.point1.x,0.25
            mov b.point1.y,0.75
            mov b.point2.x,0.25
            mov b.point2.y,0.25
            mov b.point3.x,0.0
            mov b.point3.y,0.0
            pSink.AddBezier(&b)

            pSink.EndFigure(D2D1_FIGURE_END_CLOSED)

            mov hr,pSink.Close()
        .endif

        .if (SUCCEEDED(hr))

           .new scale:Matrix3x2F
           .new translation:Matrix3x2F

            scale.Scale(squareWidth, squareWidth)

            movss xmm0,squareWidth
            movss xmm1,-0.0
            xorps xmm0,xmm1
            divss xmm0,2.0

            translation.Translation(xmm0, xmm0)
            translation.SetProduct(&scale, &translation)
            mov hr,pFactory.CreateTransformedGeometry(
                    pPathGeometry,
                    &translation,
                    &pGeometry
                    )
        .endif

        .if (SUCCEEDED(hr))

            ; Transfer the reference.
            mov [rsi].m_pGeometry,pGeometry
            mov pGeometry,NULL
        .endif

        SafeRelease(pRealization)
        SafeRelease(pGeometry)
        SafeRelease(pPathGeometry)
        SafeRelease(pSink)
    .endif
    .return hr

DemoApp::CreateGeometries endp


DemoApp::RenderMainContent proc uses rsi rdi rbx time:float

  local hr                  : HRESULT
  local rtSize              : D2D1_SIZE_F
  local squareWidth         : float
  local currentTransform    : Matrix3x2F
  local worldTransform      : Matrix3x2F
  local m                   : Matrix3x2F
  local point               : D2D1_POINT_2F
  local color               : D3DCOLORVALUE
  local pRT                 : ptr ID2D1HwndRenderTarget
  local pSB                 : ptr ID2D1SolidColorBrush
  local pRZ                 : ptr IGeometryRealization

    .data
     dwTimeStart dd 0
     dwTimeLast  dd 0
    .code

    mov         hr,S_OK
    mov         rsi,rcx
    mov         pRT,[rsi].m_pRT
    movss       xmm0,sc_boardWidth
    cvtsi2ss    xmm1,[rsi].m_numSquares
    divss       xmm0,xmm1
    movss       squareWidth,xmm0

    color.Init(Black, 1.0)
    pRT.GetSize(&rtSize)
    pRT.SetAntialiasMode([rsi].m_antialiasMode)
    pRT.Clear(&color)
    pRT.GetTransform(&currentTransform)

    cvtsi2ss    xmm0,[rsi].m_numSquares
    mulss       xmm0,squareWidth
    movss       xmm1,rtSize.width
    subss       xmm1,xmm0
    mulss       xmm1,0.5
    movss       xmm2,rtSize.height
    subss       xmm2,xmm0
    mulss       xmm2,0.5

    m.Translation(xmm1, xmm2)
    worldTransform.SetProduct(&m, &currentTransform)

    .for (ebx = 0 : hr == S_OK && ebx < [rsi].m_numSquares : ++ebx)

        .for (edi = 0 : hr == S_OK && edi < [rsi].m_numSquares : ++edi)

           .new x           : float
           .new y           : float
           .new length      : float
           .new intensity   : float

            cvtsi2ss    xmm1,[rsi].m_numSquares
            mulss       xmm1,0.5
            cvtsi2ss    xmm0,ebx
            addss       xmm0,0.5
            subss       xmm0,xmm1
            movss       x,xmm0
            cvtsi2ss    xmm0,edi
            addss       xmm0,0.5
            subss       xmm0,xmm1
            movss       y,xmm0

            cvtsi2ss    xmm0,[rsi].m_numSquares
            mulss       xmm0,1.4142135623730950488016887242097
            movss       length,xmm0

            ;
            ; The intensity variable determines the color and speed of rotation of the
            ; realization instance. We choose a function that is rotationaly
            ; symmetric about the center of the grid, which produces a nice
            ; effect.
            ;

            movss       xmm0,x
            mulss       xmm0,xmm0
            movss       xmm1,y
            mulss       xmm1,xmm1
            addss       xmm0,xmm1
            sqrtss      xmm0,xmm0
            mulss       xmm0,10.0
            divss       xmm0,length
            movss       xmm1,0.2
            mulss       xmm1,time
            addss       xmm0,xmm1
            sinf(xmm0)
            addss       xmm0,1.0
            mulss       xmm0,0.5
            movss       intensity,xmm0

           .new rotateTransform:Matrix3x2F

            mulss       xmm0,sc_rotationSpeed
            mulss       xmm0,time
            mulss       xmm0,360.0
            mulss       xmm0,M_PI / 180.0

            rotateTransform.Rotation(xmm0)

           .new newWorldTransform:Matrix3x2F

            cvtsi2ss    xmm1,ebx
            addss       xmm1,0.5
            mulss       xmm1,squareWidth
            cvtsi2ss    xmm2,edi
            addss       xmm2,0.5
            mulss       xmm2,squareWidth

            m.Translation(xmm1, xmm2)
            m.SetProduct(&rotateTransform, &m)
            newWorldTransform.SetProduct(&m, &worldTransform)

            mov pRZ,[rsi].m_pRealization

            .if [rsi].m_updateRealization

                ;
                ; Note: It would actually be a little simpler to generate our
                ; realizations prior to entering RenderMainContent. We instead
                ; generate the realizations based on the top-left primitive in
                ; the grid, so we can illustrate the fact that realizations
                ; appear identical to their unrealized counter-parts when the
                ; exact same world transform is supplied. Only the top left
                ; realization will look identical, though, as shifting or
                ; rotating an AA realization can introduce fuzziness.
                ;
                ; Realizations are regenerated every frame, so to
                ; demonstrate that the realization geometry produces identical
                ; results, you actually need to pause (<space>), which forces
                ; a regeneration.
                ;

                mov hr,pRZ.Update(
                    [rsi].m_pGeometry,
                    REALIZATION_CREATION_OPTIONS_ANTI_ALIASED or \
                    REALIZATION_CREATION_OPTIONS_ALIASED or \
                    REALIZATION_CREATION_OPTIONS_FILLED or \
                    REALIZATION_CREATION_OPTIONS_STROKED or \
                    REALIZATION_CREATION_OPTIONS_UNREALIZED,
                    &newWorldTransform,
                    sc_strokeWidth,
                    NULL ;;pIStrokeStyle
                    )

                .if (SUCCEEDED(hr))

                    mov [rsi].m_updateRealization,FALSE
                .endif
            .endif

            .if (SUCCEEDED(hr))

                pRT.SetTransform(&newWorldTransform)

                mov     color.r,0.0
                mov     color.g,intensity
                mov     color.a,1.0
                movss   xmm0,1.0
                subss   xmm0,intensity
                movss   color.b,xmm0
                mov     pSB,[rsi].m_pSolidColorBrush

                pSB.SetColor(&color)

                mov     r9d,REALIZATION_RENDER_MODE_DEFAULT
                mov     eax,REALIZATION_RENDER_MODE_FORCE_UNREALIZED
                cmp     [rsi].m_useRealizations,0
                cmove   r9d,eax

                mov hr,pRZ.Fill(pRT, pSB, r9d)

                .if SUCCEEDED(hr) && [rsi].m_drawStroke

                    color.Init(White, 1.0)
                    pSB.SetColor(&color)

                    mov     r9d,REALIZATION_RENDER_MODE_DEFAULT
                    mov     eax,REALIZATION_RENDER_MODE_FORCE_UNREALIZED
                    cmp     [rsi].m_useRealizations,NULL
                    cmove   r9d,eax

                    mov hr,pRZ.Draw(pRT, pSB, r9d)
                .endif
            .endif
        .endf
    .endf
    .return hr

DemoApp::RenderMainContent endp

;
;  Called whenever the application needs to display the client
;  window. This method draws the main content (a 2D array of
;  spinning geometries) and some perf statistics.
;
;  Note that this function will not render anything if the window
;  is occluded (e.g. when the screen is locked).
;  Also, this function will automatically discard device-specific
;  resources if the D3D device disappears during function
;  invocation, and will recreate the resources the next time it's
;  invoked.
;

DemoApp::OnRender proc uses rsi rdi

  .new hr:HRESULT = S_OK
  .new time:LARGE_INTEGER
  .new frequency:LARGE_INTEGER
  .new floatTime:float

    mov rsi,rcx

    QueryPerformanceCounter(&time)
    QueryPerformanceFrequency(&frequency)

    mov hr,[rsi].CreateDeviceResources()

    .if (SUCCEEDED(hr))

        cmp         [rsi].m_paused,0
        mov         rax,[rsi].m_pausedTime
        cmove       rax,time.QuadPart
        add         rax,[rsi].m_timeDelta
        cvtsi2sd    xmm0,rax
        cvtsi2sd    xmm1,frequency.QuadPart
        divsd       xmm0,xmm1
        cvtsd2ss    xmm0,xmm0
        movss       floatTime,xmm0

        this.m_times.AddT(time.QuadPart)

        movss   xmm0,[rsi].m_currentZoomFactor
        comiss  xmm0,[rsi].m_targetZoomFactor

        .ifb

            mulss   xmm0,sc_zoomSubStep
            movss   [rsi].m_currentZoomFactor,xmm0
            comiss  xmm0,[rsi].m_targetZoomFactor

            .ifa
                mov [rsi].m_currentZoomFactor,[rsi].m_targetZoomFactor
                .if ([rsi].m_autoGeometryRegen)
                    mov [rsi].m_updateRealization,TRUE
                .endif
            .endif

        .elseif !ZERO?

            divss   xmm0,sc_zoomSubStep
            movss   [rsi].m_currentZoomFactor,xmm0
            comiss  xmm0,[rsi].m_targetZoomFactor

            .ifb
                mov [rsi].m_currentZoomFactor,[rsi].m_targetZoomFactor
                .if ([rsi].m_autoGeometryRegen)
                    mov [rsi].m_updateRealization,TRUE
                .endif
            .endif
        .endif

       .new m:Matrix3x2F

        assume rdi:ptr ID2D1HwndRenderTarget

        mov rdi,[rsi].m_pRT
        [rdi].SetTransform(
            m.Scale(
                [rsi].m_currentZoomFactor,
                [rsi].m_currentZoomFactor,
                [rsi].m_mousePos.x,
                [rsi].m_mousePos.y
                )
            )

        mov hr,[rsi].CreateGeometries()

        .if SUCCEEDED(hr)

            .if !( [rdi].CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED )

                [rdi].BeginDraw()

                mov hr,[rsi].RenderMainContent(floatTime)
                .if (SUCCEEDED(hr))

                    mov hr,[rsi].RenderTextInfo()
                    .if (SUCCEEDED(hr))

                        mov hr,[rdi].EndDraw(NULL, NULL)
                        .if (SUCCEEDED(hr))

                            .if (hr == D2DERR_RECREATE_TARGET)

                                [rsi].DiscardDeviceResources()
                            .endif
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

DemoApp::OnRender endp

;
;  Draw the stats text (AA type, fps, etc...).
;

DemoApp::RenderTextInfo proc uses rsi rdi rbx

  .new hr:HRESULT = S_OK
  .new textBuffer[400]:WCHAR
  .new frequency:LARGE_INTEGER
  .new fps:float = 0.0
  .new primsPerSecond:float = 0.0
  .new numPrimitives:UINT
  .new pRB:ptr RingBuffer

    mov rsi,rcx

    QueryPerformanceFrequency(&frequency)

    mov eax,[rsi].m_numSquares
    mul [rsi].m_numSquares
    .if [rsi].m_drawStroke
        shl eax,1
    .endif
    mov numPrimitives,eax
    mov pRB,[rsi].m_times

    .if (pRB.GetCount() > 0)

        dec         eax
        mul         frequency.QuadPart
        cvtsi2ss    xmm0,eax
        mov         edi,pRB.GetLast()
        sub         edi,pRB.GetFirst()
        cvtsi2ss    xmm1,edi
        divss       xmm0,xmm1
        movss       fps,xmm0
        cvtsi2ss    xmm1,numPrimitives
        mulss       xmm0,xmm1
        movss       primsPerSecond,xmm0
    .endif

    cmp         [rsi].m_antialiasMode,D2D1_ANTIALIAS_MODE_ALIASED
    lea         rax,@CStr("Aliased")
    lea         rcx,@CStr("PerPrimitive")
    cmove       rcx,rax
    cmp         [rsi].m_useRealizations,0
    lea         rdx,@CStr("Realized")
    lea         rax,@CStr("Unrealized")
    cmove       rdx,rax
    cmp         [rsi].m_autoGeometryRegen,0
    lea         r8,@CStr("Auto Realization Regeneration")
    lea         rax,@CStr("No Auto Realization Regeneration")
    cmove       r8,rax
    cmp         [rsi].m_drawStroke,0
    lea         rax,@CStr("")
    lea         r9,@CStr(" x 2")
    cmove       r9,rax

    movss       xmm0,fps
    cvtss2sd    xmm0,xmm0
    movq        r10,xmm0

    movss       xmm0,primsPerSecond
    cvtss2sd    xmm0,xmm0
    movq        r11,xmm0

    mov hr,swprintf(
            &textBuffer,
            "%s\n"
            "%s\n"
            "%s\n"
            "# primitives: %d x %d%s = %d\n"
            "Fps: %.2f\n"
            "Primitives / sec : %.0f",
            rcx,
            rdx,
            r8,
            [rsi].m_numSquares,
            [rsi].m_numSquares,
            r9,
            numPrimitives,
            r10,
            r11
            )

    .if (SUCCEEDED(hr))

        mov rdi,[rsi].m_pRT

       .new m:Matrix3x2F
        [rdi].SetTransform(
            m.Identity()
            )

       .new c:D3DCOLORVALUE(Black, 0.5)
        mov rbx,[rsi].m_pSolidColorBrush
        [rbx].ID2D1SolidColorBrush.SetColor(&c)

       .new rr:D2D1_ROUNDED_RECT = {
            { 10.0, 10.0, 350.0, 200.0 },
            sc_textInfoBoxInset,
            sc_textInfoBoxInset
            }

        [rdi].FillRoundedRectangle(
            &rr,
            [rsi].m_pSolidColorBrush
            )

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

        [rbx].ID2D1SolidColorBrush.SetColor(c.Init(White, 1.0))
        mov r8,wcsnlen(&textBuffer, ARRAYSIZE(textBuffer))
        [rdi].DrawText(
            &textBuffer,
            r8d,
            [rsi].m_pTextFormat,
            &rr,
            [rsi].m_pSolidColorBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

    .endif
    .return hr

DemoApp::RenderTextInfo endp

;
;  If the application receives a WM_SIZE message, this method
;  resizes the render target appropriately.
;

DemoApp::OnResize proc width:UINT, height:UINT

    mov rcx,[rcx].DemoApp.m_pRT
    .if rcx

       .new size:D2D1_SIZE_U

        mov size.width,edx
        mov size.height,r8d

        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.

        [rcx].ID2D1HwndRenderTarget.Resize(&size)
    .endif
    ret

DemoApp::OnResize endp


    assume rcx:ptr DemoApp

DemoApp::OnKeyDown proc vkey:SWORD

    .switch dx

    .case 'A'
        mov     edx,D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
        mov     eax,D2D1_ANTIALIAS_MODE_ALIASED
        cmp     [rcx].m_antialiasMode,D2D1_ANTIALIAS_MODE_ALIASED
        cmove   eax,edx
        mov     [rcx].m_antialiasMode,eax
        .endc

    .case 'R'
        xor [rcx].m_useRealizations,1
        .endc

    .case 'G'
        xor [rcx].m_autoGeometryRegen,1
        .endc

    .case 'S'
        xor [rcx].m_drawStroke,1
        .endc

    .case VK_SPACE

       .new time:LARGE_INTEGER
        QueryPerformanceCounter(&time)

        mov rcx,this
        .if ![rcx].m_paused
            mov [rcx].m_pausedTime,time.QuadPart
        .else
            mov rax,[rcx].m_pausedTime
            sub rax,time.QuadPart
            add [rcx].m_timeDelta,rax
        .endif
        xor [rcx].m_paused,1
        mov [rcx].m_updateRealization,TRUE
        .endc

    .case VK_UP
        mov eax,[rcx].m_numSquares
        shl eax,1
        .if eax > sc_maxNumSquares
            mov eax,sc_maxNumSquares
        .endif
        mov [rcx].m_numSquares,eax

        ; Regenerate the geometries.
        [rcx].DiscardGeometryData()
        .endc

    .case VK_DOWN
        mov eax,[rcx].m_numSquares
        shr eax,1
        .if eax < sc_minNumSquares
            mov eax,sc_minNumSquares
        .endif
        mov [rcx].m_numSquares,eax

        ; Regenerate the geometries.
        [rcx].DiscardGeometryData()
        .endc
    .endsw
    ret

DemoApp::OnKeyDown endp


DemoApp::OnMouseMove proc lParam:LPARAM

  local dpiX:float
  local dpiY:float

    mov dpiX,96.0
    mov dpiY,96.0

    .if [rcx].m_pRT

        this.m_pRT.GetDpi(&dpiX, &dpiY)
        mov rcx,this
    .endif

    movsx       eax,word ptr lParam
    cvtsi2ss    xmm0,eax
    mulss       xmm0,96.0
    divss       xmm0,dpiX
    movss       [rcx].m_mousePos.x,xmm0

    movsx       eax,word ptr lParam[2]
    cvtsi2ss    xmm0,eax
    mulss       xmm0,96.0
    divss       xmm0,dpiY
    movss       [rcx].m_mousePos.y,xmm0
    ret

DemoApp::OnMouseMove endp


DemoApp::OnWheel proc wParam:WPARAM

    shr         edx,16
    movsx       rdx,dx
    cvtsi2sd    xmm1,rdx
    divsd       xmm1,120.0
    pow(sc_zoomStep, xmm1)
    cvtsd2ss    xmm0,xmm0

    mov         rcx,this
    mulss       xmm0,[rcx].m_targetZoomFactor
    movss       xmm1,sc_minZoom
    maxss       xmm0,xmm1
    movss       xmm1,sc_maxZoom
    minss       xmm0,xmm1
    movss       [rcx].m_targetZoomFactor,xmm0
    ret

DemoApp::OnWheel endp


WndProc proc WINAPI hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local result:LRESULT
  local wasHandled:BOOL
  local pDemoApp:ptr DemoApp

     mov result,0

    .if edx == WM_CREATE

        SetWindowLongPtrW(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
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
                InvalidateRect(hwnd, NULL, FALSE)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_KEYDOWN
                movzx edx,word ptr wParam
                pDemoApp.OnKeyDown(dx)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_MOUSEMOVE
                pDemoApp.OnMouseMove(lParam)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_MOUSEWHEEL
                pDemoApp.OnWheel(wParam)

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
