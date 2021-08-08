
;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER               ;; Allow use of features specific to Windows 7 or later.
WINVER equ 0x0501           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows 7 or later.
_WIN32_WINNT equ 0x0501     ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINDOWS       ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410   ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE            ;; Allow use of features specific to IE 6.0 or later.
_WIN32_IE equ 0x0600        ;; Change this to the appropriate value to target other versions of IE.
endif

ifndef _UNICODE
_UNICODE equ 1
endif

;; Windows Header Files:
include windows.inc

;; C RunTime Header Files
include stdlib.inc
include malloc.inc
include memory.inc
include wchar.inc

include wininet.inc
include stdio.inc

include d2d1.inc
include d2d1helper.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none

SafeRelease proto :ptr, :abs {

    mov rax,[_1]
    .if rax
        mov qword ptr [_1],NULL
        [rax]._2.Release()
    .endif
    }

ifndef HINST_THISCOMPONENT
ifndef _MSVCRT
extern __ImageBase:byte
endif
HINST_THISCOMPONENT equ <&__ImageBase>
endif

    .data
ifdef _MSVCRT
    IID_ID2D1Factory                IID _IID_ID2D1Factory
    IID_IDWriteFactory              IID _IID_IDWriteFactory
    IID_IWICImagingFactory          IID _IID_IWICImagingFactory
    CLSID_WICImagingFactory         IID _CLSID_WICImagingFactory
    GUID_WICPixelFormat32bppBGR     IID _GUID_WICPixelFormat32bppBGR
    GUID_ContainerFormatPng         IID _GUID_ContainerFormatPng
    GUID_WICPixelFormatDontCare     IID _GUID_WICPixelFormatDontCare
endif
    stops D2D1_GRADIENT_STOP {0.0,{0.0,1.0,1.0,1.0}},{1.0,{0.0,0.0,1.0,1.0}}


    .code

SaveToImageFile proc

    local hr:HRESULT


    ;;
    ;; Create Factories
    ;;

    local pWICFactory:ptr IWICImagingFactory
    local pD2DFactory:ptr ID2D1Factory
    local pDWriteFactory:ptr IDWriteFactory
    local pWICBitmap:ptr IWICBitmap
    local pRT:ptr ID2D1RenderTarget
    local pTextFormat:ptr IDWriteTextFormat
    local pPathGeometry:ptr ID2D1PathGeometry
    local pSink:ptr ID2D1GeometrySink
    local pGradientStops:ptr ID2D1GradientStopCollection
    local pLGBrush:ptr ID2D1LinearGradientBrush
    local pBlackBrush:ptr ID2D1SolidColorBrush
    local pEncoder:ptr IWICBitmapEncoder
    local pFrameEncode:ptr IWICBitmapFrameEncode
    local pStream:ptr IWICStream
    local Color:D3DCOLORVALUE
    local rtSize:D2D1_SIZE_F
    local Matrix:Matrix3x2F
    local size:D2D1_SIZE_F
    local rc:D2D1_RECT_F
    local b:D2D1_BEZIER_SEGMENT
    local lg:D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES

    mov hr,S_OK

    xor eax,eax
    mov pWICFactory,rax
    mov pD2DFactory,rax
    mov pDWriteFactory,rax
    mov pWICBitmap,rax
    mov pRT,rax
    mov pTextFormat,rax
    mov pPathGeometry,rax
    mov pSink,rax
    mov pGradientStops,rax
    mov pLGBrush,rax
    mov pBlackBrush,rax
    mov pEncoder,rax
    mov pFrameEncode,rax
    mov pStream,rax


    mov hr,CoCreateInstance(
        &CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        &IID_IWICImagingFactory,
        &pWICFactory
        )

    .if (SUCCEEDED(hr))

        mov hr,D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory,
            NULL,
            &pD2DFactory)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            &IID_IDWriteFactory,
            &pDWriteFactory
            )
    .endif

    ;;
    ;; Create IWICBitmap and RT
    ;;

    sc_bitmapWidth  equ 640
    sc_bitmapHeight equ 480

    .if (SUCCEEDED(hr))

        mov hr,pWICFactory.CreateBitmap(
            sc_bitmapWidth,
            sc_bitmapHeight,
            &GUID_WICPixelFormat32bppBGR,
            WICBitmapCacheOnLoad,
            &pWICBitmap
            )
    .endif

    .if (SUCCEEDED(hr))

        mov r8,D2D1::RenderTargetProperties()
        mov hr,pD2DFactory.CreateWicBitmapRenderTarget(
            pWICBitmap,
            r8,
            &pRT
            )
    .endif


    .if (SUCCEEDED(hr))

        ;;
        ;; Create text format
        ;;

        sc_fontName equ <L"Calibri">
        sc_fontSize equ 50.0

        mov hr,pDWriteFactory.CreateTextFormat(
            sc_fontName,
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            sc_fontSize,
            L"", ;;locale
            &pTextFormat
            )
    .endif

    .if (SUCCEEDED(hr))

        pTextFormat.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)

        pTextFormat.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)

        ;;
        ;; Create a path geometry representing an hour glass
        ;;

        mov hr,pD2DFactory.CreatePathGeometry(&pPathGeometry)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pPathGeometry.Open(&pSink)
    .endif

    .if (SUCCEEDED(hr))

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

    .if (SUCCEEDED(hr))

        ;;
        ;; Create a linear-gradient brush
        ;;

        mov hr,pRT.CreateGradientStopCollection(
            &stops,
            2,
            D2D1_GAMMA_2_2,
            D2D1_EXTEND_MODE_CLAMP,
            &pGradientStops
            )
    .endif

    .if (SUCCEEDED(hr))

        mov lg.startPoint.x,100.0
        mov lg.startPoint.y,0.0
        mov lg.endPoint.x,100.0
        mov lg.endPoint.y,200.0

        mov r8,D2D1::BrushProperties()

        mov hr,pRT.CreateLinearGradientBrush(
            &lg,
            r8,
            pGradientStops,
            &pLGBrush
            )
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pRT.CreateSolidColorBrush(
            Color.Init(Black, 1.0),
            NULL,
            &pBlackBrush
            )
    .endif

    .if (SUCCEEDED(hr))

        ;;
        ;; Render into the bitmap
        ;;

        pRT.BeginDraw()

        pRT.Clear(Color.Init(White, 1.0))

        pRT.GetSize(&rtSize)

        movss xmm0,rtSize.width
        divss xmm0,2.0
        movss size.width,xmm0
        movss xmm0,rtSize.height
        divss xmm0,2.0
        movss size.height,xmm0

        Matrix.Rotation(45.0, size)

        ;; Set the world transform to a 45 degree rotation at the center of the render target
        ;; and write "Hello, World".

        pRT.SetTransform(&Matrix)

        sc_helloWorld equ <L"Hello, World!">

        mov rc.left,0.0
        mov rc.top,0.0
        mov rc.right,rtSize.width
        mov rc.bottom,rtSize.height

        pRT.DrawText(
            sc_helloWorld,
            13,
            pTextFormat,
            &rc,
            pBlackBrush,
            D2D1_DRAW_TEXT_OPTIONS_NONE,
            DWRITE_MEASURING_MODE_NATURAL
            )

        ;;
        ;; Reset back to the identity transform
        ;;
        movss xmm2,rtSize.height
        subss xmm2,200.0
        Matrix.Translation(0.0, xmm2)
        pRT.SetTransform(&Matrix)

        pRT.FillGeometry(pPathGeometry, pLGBrush, NULL)

        movss xmm1,rtSize.width
        subss xmm1,200.0
        Matrix.Translation(xmm1, 0.0)
        pRT.SetTransform(&Matrix)

        pRT.FillGeometry(pPathGeometry, pLGBrush, NULL)

        mov hr,pRT.EndDraw(NULL, NULL)
    .endif

    .if (SUCCEEDED(hr))

        ;;
        ;; Save image to file
        ;;

        mov hr,pWICFactory.CreateStream(&pStream)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pStream.InitializeFromFilename(L"output.png", GENERIC_WRITE)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pWICFactory.CreateEncoder(&GUID_ContainerFormatPng, NULL, &pEncoder)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pEncoder.Initialize(pStream, WICBitmapEncoderNoCache)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pEncoder.CreateNewFrame(&pFrameEncode, NULL)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameEncode.Initialize(NULL)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameEncode.SetSize(sc_bitmapWidth, sc_bitmapHeight)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameEncode.SetPixelFormat(&GUID_WICPixelFormatDontCare)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameEncode.WriteSource(pWICBitmap, NULL)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameEncode.Commit()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pEncoder.Commit()
    .endif

    SafeRelease(&pWICFactory,       IWICImagingFactory)
    SafeRelease(&pD2DFactory,       ID2D1Factory)
    SafeRelease(&pDWriteFactory,    IDWriteFactory)
    SafeRelease(&pWICBitmap,        IWICBitmap)
    SafeRelease(&pRT,               ID2D1RenderTarget)
    SafeRelease(&pTextFormat,       IDWriteTextFormat)
    SafeRelease(&pPathGeometry,     ID2D1PathGeometry)
    SafeRelease(&pSink,             ID2D1GeometrySink)
    SafeRelease(&pGradientStops,    ID2D1GradientStopCollection)
    SafeRelease(&pLGBrush,          ID2D1LinearGradientBrush)
    SafeRelease(&pBlackBrush,       ID2D1SolidColorBrush)
    SafeRelease(&pEncoder,          IWICBitmapEncoder)
    SafeRelease(&pFrameEncode,      IWICBitmapFrameEncode)
    SafeRelease(&pStream,           IWICStream)

    .return hr

SaveToImageFile endp


;/*=========================================================================*\
;    Main
;\*=========================================================================*/

wmain proc

    ;; Ignoring the return value because we want to continue running even in the
    ;; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .ifd CoInitialize(NULL) == S_OK

        .ifd SaveToImageFile()

            wprintf(L"Unexpected error: 0x%x", eax)
        .endif

        CoUninitialize()
    .endif

    .return 0

wmain endp

    end _tstart
