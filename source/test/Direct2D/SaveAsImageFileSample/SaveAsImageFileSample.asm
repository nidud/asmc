ifndef WINVER
define WINVER 0x0501
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0501
endif
ifndef _WIN32_WINDOWS
define _WIN32_WINDOWS 0x0410
endif
ifndef _WIN32_IE
define _WIN32_IE 0x0600
endif

include windows.inc
include stdio.inc
include d2d1.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none


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

    xor eax,eax

    ;
    ; Create Factories
    ;

  .new hr:HRESULT = eax ; S_OK
  .new pWICFactory:ptr IWICImagingFactory = rax
  .new pD2DFactory:ptr ID2D1Factory = rax
  .new pDWriteFactory:ptr IDWriteFactory = rax
  .new pWICBitmap:ptr IWICBitmap = rax
  .new pRT:ptr ID2D1RenderTarget = rax
  .new pTextFormat:ptr IDWriteTextFormat = rax
  .new pPathGeometry:ptr ID2D1PathGeometry = rax
  .new pSink:ptr ID2D1GeometrySink = rax
  .new pGradientStops:ptr ID2D1GradientStopCollection = rax
  .new pLGBrush:ptr ID2D1LinearGradientBrush = rax
  .new pBlackBrush:ptr ID2D1SolidColorBrush = rax
  .new pEncoder:ptr IWICBitmapEncoder = rax
  .new pFrameEncode:ptr IWICBitmapFrameEncode = rax
  .new pStream:ptr IWICStream = rax
  .new Color:D3DCOLORVALUE
  .new rtSize:D2D1_SIZE_F
  .new Matrix:Matrix3x2F
  .new size:D2D1_SIZE_F
  .new rc:D2D1_RECT_F
  .new b:D2D1_BEZIER_SEGMENT
  .new lg:D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES


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

    ;
    ; Create IWICBitmap and RT
    ;

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

        ;
        ; Create text format
        ;

        sc_fontName equ <"Calibri">
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

        ;
        ; Create a path geometry representing an hour glass
        ;

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

        ;
        ; Create a linear-gradient brush
        ;

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

        ;
        ; Render into the bitmap
        ;

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

        ; Set the world transform to a 45 degree rotation at the center of the render target
        ; and write "Hello, World".

        pRT.SetTransform(&Matrix)

        sc_helloWorld equ <"Hello, World!">

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

        ;
        ; Reset back to the identity transform
        ;
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

        ;
        ; Save image to file
        ;

        mov hr,pWICFactory.CreateStream(&pStream)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pStream.InitializeFromFilename("output.png", GENERIC_WRITE)
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

    SafeRelease(pWICFactory)
    SafeRelease(pD2DFactory)
    SafeRelease(pDWriteFactory)
    SafeRelease(pWICBitmap)
    SafeRelease(pRT)
    SafeRelease(pTextFormat)
    SafeRelease(pPathGeometry)
    SafeRelease(pSink)
    SafeRelease(pGradientStops)
    SafeRelease(pLGBrush)
    SafeRelease(pBlackBrush)
    SafeRelease(pEncoder)
    SafeRelease(pFrameEncode)
    SafeRelease(pStream)
   .return hr

SaveToImageFile endp


wmain proc

    ; Ignoring the return value because we want to continue running even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .ifd CoInitialize(NULL) == S_OK

        .ifd SaveToImageFile()

            wprintf("Unexpected error: 0x%x", eax)
        .endif
        CoUninitialize()
    .endif
    .return 0

wmain endp

    end _tstart
