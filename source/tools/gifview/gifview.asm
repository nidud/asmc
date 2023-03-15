; GIFVIEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define WIN32_LEAN_AND_MEAN

include windows.inc
include wincodec.inc
include commdlg.inc
include DirectX/d2d1.inc
include tchar.inc

define DEFAULT_DPI 96.0
define DELAY_TIMER_ID 1

.enum DISPOSAL_METHODS {
    DM_UNDEFINED  = 0,
    DM_NONE       = 1,
    DM_BACKGROUND = 2,
    DM_PREVIOUS   = 3
    }

.class GifView

    m_hWnd              HWND ?
    m_FileName          LPWSTR ?

    m_pD2DFactory       ptr ID2D1Factory ?
    m_pHwndRT           ptr ID2D1HwndRenderTarget ?
    m_pFrameComposeRT   ptr ID2D1BitmapRenderTarget ?
    m_pRawFrame         ptr ID2D1Bitmap ?
    m_pSavedFrame       ptr ID2D1Bitmap ? ;; The temporary bitmap used for disposal 3 method
    m_backgroundColor   D2D1_COLOR_F <>

    m_pIWICFactory      ptr IWICImagingFactory ?
    m_pDecoder          ptr IWICBitmapDecoder ?

    m_uNextFrameIndex   UINT ?
    m_uTotalLoopCount   UINT ? ; The number of loops for which the animation will be played
    m_uLoopNumber       UINT ? ; The current animation loop number (e.g. 1 when the animation is first played)
    m_fHasLoop          BOOL ? ; Whether the gif has a loop
    m_cFrames           UINT ? ;
    m_uFrameDisposal    UINT ?
    m_uFrameDelay       UINT ?
    m_cxGifImage        UINT ?
    m_cyGifImage        UINT ?
    m_cxGifImagePixel   UINT ? ; Width of the displayed image in pixel calculated using pixel aspect ratio
    m_cyGifImagePixel   UINT ? ; Height of the displayed image in pixel calculated using pixel aspect ratio
    m_framePosition     D2D1_RECT_F <>

    GifView             proc
    Release             proc

    Initialize          proc :HINSTANCE, :LPWSTR

    CreateDeviceResources proc
    RecoverDeviceResources proc

    OnResize            proc :UINT, :UINT
    OnRender            proc

    SelectAndDisplayGif proc
    GetRawFrame         proc :UINT
    GetGlobalMetadata   proc
    GetBackgroundColor  proc :ptr IWICMetadataQueryReader

    ComposeNextFrame    proc
    DisposeCurrentFrame proc
    OverlayNextFrame    proc

    SaveComposedFrame   proc
    RestoreSavedFrame   proc
    ClearCurrentFrameArea proc
    CalculateDrawRectangle proc :ptr D2D1_RECT_F

    .inline IsLastFrame {
        mov edx,1
        xor eax,eax
        cmp [this].GifView.m_uNextFrameIndex,0
        cmovnz eax,edx
        }

    .inline EndOfAnimation {
        .if [this].GifView.IsLastFrame()
            xor eax,eax
            .if eax != [this].GifView.m_fHasLoop
                mov edx,[this].GifView.m_uTotalLoopCount
                inc edx
                .if edx == [this].GifView.m_uLoopNumber
                    mov eax,TRUE
                .endif
            .endif
        .endif
        }

    .ends

    .data

    IID_ID2D1Factory              GUID {0x06152247,0x6f50,0x465a,{0x92,0x45,0x11,0x8b,0xfd,0x3b,0x60,0x07}}
    IID_IWICImagingFactory        GUID {0xec5ec8a9,0xc395,0x4314,{0x9c,0x77,0x54,0xd7,0xa9,0x35,0xff,0x70}}
    CLSID_WICImagingFactory       GUID {0xcacaf262,0x9370,0x4615,{0xa1,0x3b,0x9f,0x55,0x39,0xda,0x4c,0x0a}}
    GUID_WICPixelFormat32bppPBGRA GUID {0x6fddc324,0x4e03,0x4bfe,{0xb1,0x85,0x3d,0x77,0x76,0x8d,0xc9,0x10}}


    .code

    option proc:private

    assume rsi:ptr GifView


GifView::CreateDeviceResources proc uses rsi

   .new hr:HRESULT = S_OK
   .new rc:RECT
   .new size:D2D1_SIZE_U

    mov rsi,rcx
    .if !GetClientRect([rsi].m_hWnd, &rc)

        mov hr,HRESULT_FROM_WIN32R(GetLastError())
    .endif

    .if (SUCCEEDED(hr))

        .if ( [rsi].m_pHwndRT == NULL )

           .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES()
            mov renderTargetProperties.dpiX,DEFAULT_DPI
            mov renderTargetProperties.dpiY,DEFAULT_DPI
            mov r8d,rc.right
            sub r8d,rc.left
            mov r9d,rc.bottom
            sub r9d,rc.top
           .new hwndRenderTragetproperties:D2D1_HWND_RENDER_TARGET_PROPERTIES([rsi].m_hWnd, r8d, r9d)
            mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(&renderTargetProperties,
                    &hwndRenderTragetproperties, &[rsi].m_pHwndRT)

        .else

            mov size.width,rc.Width()
            mov size.height,rc.Height()
            mov hr,this.m_pHwndRT.Resize(&size)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        SafeRelease([rsi].m_pFrameComposeRT)

        cvtsi2ss xmm0,[rsi].m_cxGifImage
        cvtsi2ss xmm1,[rsi].m_cyGifImage
        movss size.width,xmm0
        movss size.height,xmm1
        mov hr,this.m_pHwndRT.CreateCompatibleRenderTarget(&size, NULL, NULL,
                D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE, &[rsi].m_pFrameComposeRT)
    .endif
    .return hr

GifView::CreateDeviceResources endp


GifView::OnRender proc

   .new hr:HRESULT = S_OK
   .new pFrameToRender:ptr ID2D1Bitmap = NULL
   .new pRT:ptr ID2D1HwndRenderTarget = [rcx].GifView.m_pHwndRT

    .if ( pRT && [rcx].GifView.m_pFrameComposeRT )

        .if (SUCCEEDED(hr))

            pRT.CheckWindowState()

            .if !( eax & D2D1_WINDOW_STATE_OCCLUDED )

               .new drawRect:D2D1_RECT_F
                mov hr,this.CalculateDrawRectangle(&drawRect)

                .if (SUCCEEDED(hr))

                    mov hr,this.m_pFrameComposeRT.GetBitmap(&pFrameToRender)
                .endif

                .if (SUCCEEDED(hr))

                   .new color:D3DCOLORVALUE(Black, 0.0)
                    pRT.BeginDraw()
                    pRT.Clear(&color)
                    pRT.DrawBitmap(pFrameToRender, &drawRect, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL)
                    mov hr,pRT.EndDraw(NULL, NULL)
                .endif
            .endif
        .endif
    .endif

    SafeRelease(pFrameToRender)
   .return hr

GifView::OnRender endp


GifView::OnResize proc uWidth:UINT, uHeight:UINT

    .new hr:HRESULT = S_OK
    .if ( [rcx].GifView.m_pHwndRT )

       .new size:D2D1_SIZE_U
        mov size.width,edx
        mov size.height,r8d
        mov hr,this.m_pHwndRT.Resize(&size)
    .endif
   .return hr

GifView::OnResize endp


GifView::GetGlobalMetadata proc uses rsi

   .new propValue:PROPVARIANT
   .new pMetadataQueryReader:ptr IWICMetadataQueryReader = NULL

    mov rsi,rcx
    PropVariantInit(&propValue)

    .new hr:HRESULT = this.m_pDecoder.GetFrameCount(&[rsi].m_cFrames)
    .if (SUCCEEDED(hr))

        mov hr,this.m_pDecoder.GetMetadataQueryReader(&pMetadataQueryReader)
    .endif

    .if (SUCCEEDED(hr))

        this.GetBackgroundColor(pMetadataQueryReader)

        .if(FAILED(eax))

            lea rcx,[rsi].m_backgroundColor
            [rcx].D3DCOLORVALUE.Init(0, 0.0)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/Width", &propValue)

        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_cxGifImage,propValue.uiVal
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/Height", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_cyGifImage,propValue.uiVal
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/PixelAspectRatio", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if ( propValue.vt == VT_UI1 )
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                .new uPixelAspRatio:UINT
                 mov uPixelAspRatio,propValue.bVal

                .if ( uPixelAspRatio != 0 )

                   .new pixelAspRatio:FLOAT
                    cvtsi2ss xmm0,uPixelAspRatio
                    addss xmm0,15.0
                    divss xmm0,64.0
                    comiss xmm0,1.0
                    .ifa

                        cvtsi2ss xmm1,[rsi].m_cyGifImage
                        divss xmm1,xmm0
                        cvtss2si eax,xmm1
                        mov [rsi].m_cyGifImagePixel,eax
                        mov [rsi].m_cxGifImagePixel,[rsi].m_cxGifImage

                    .else
                        cvtsi2ss xmm1,[rsi].m_cxGifImage
                        mulss xmm0,xmm1
                        cvtss2si eax,xmm0
                        mov [rsi].m_cxGifImagePixel,eax
                        mov [rsi].m_cyGifImagePixel,[rsi].m_cyGifImage
                    .endif

                .else

                    mov [rsi].m_cxGifImagePixel,[rsi].m_cxGifImage
                    mov [rsi].m_cyGifImagePixel,[rsi].m_cyGifImage
                .endif
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        pMetadataQueryReader.GetMetadataByName(L"/appext/application", &propValue)

        .if ( !eax && ( propValue.vt == (VT_UI1 or VT_VECTOR) ) && propValue.caub.cElems == 11 )

            .ifd memcmp(propValue.caub.pElems, "NETSCAPE2.0", 11)
                 memcmp(propValue.caub.pElems, "ANIMEXTS1.0", 11)
            .endif

            .if (SUCCEEDED(eax))

                PropVariantClear(&propValue)
                mov hr,pMetadataQueryReader.GetMetadataByName(L"/appext/data", &propValue)

                .if (SUCCEEDED(hr))

                    mov rdx,propValue.caub.pElems
                    .if ( propValue.vt == ( VT_UI1 or VT_VECTOR ) && propValue.caub.cElems >= 4 &&
                            byte ptr [rdx][0] > 0 && byte ptr [rdx][1] == 1 )

                        movzx eax,byte ptr [rdx][2]
                        mov ah,byte ptr [rdx][3]
                        mov [rsi].m_uTotalLoopCount,eax
                        .if ( eax )

                            mov [rsi].m_fHasLoop,TRUE
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif

    PropVariantClear(&propValue)
    SafeRelease(pMetadataQueryReader)
   .return hr

GifView::GetGlobalMetadata endp


GifView::GetRawFrame proc uses rsi uFrameIndex:UINT

   .new hr:HRESULT
   .new pConverter:ptr IWICFormatConverter = NULL
   .new pWicFrame:ptr IWICBitmapFrameDecode = NULL
   .new pFrameMetadataQueryReader:ptr IWICMetadataQueryReader = NULL
   .new propValue:PROPVARIANT

    mov rsi,rcx

    PropVariantInit(&propValue)
    mov hr,this.m_pDecoder.GetFrame(uFrameIndex, &pWicFrame)

    .if (SUCCEEDED(hr))

        mov hr,this.m_pIWICFactory.CreateFormatConverter(&pConverter)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pConverter.Initialize(pWicFrame, &GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
                NULL, 0.0, WICBitmapPaletteTypeCustom)
    .endif

    .if (SUCCEEDED(hr))

        SafeRelease([rsi].m_pRawFrame)
        mov hr,this.m_pHwndRT.CreateBitmapFromWicBitmap(pConverter, NULL, &[rsi].m_pRawFrame)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pWicFrame.GetMetadataQueryReader(&pFrameMetadataQueryReader)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Left", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                movss [rsi].m_framePosition.left,xmm0
            .endif
            PropVariantClear(&propValue);
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Top", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                movss [rsi].m_framePosition.top,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Width", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                addss xmm0,[rsi].m_framePosition.left
                movss [rsi].m_framePosition.right,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Height", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                addss xmm0,[rsi].m_framePosition.top
                movss [rsi].m_framePosition.bottom,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        pFrameMetadataQueryReader.GetMetadataByName(L"/grctlext/Delay", &propValue)
        .if (SUCCEEDED(eax))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov hr,UIntMult(propValue.uiVal, 10, &[rsi].m_uFrameDelay)
            .endif
            PropVariantClear(&propValue)

        .else

            mov [rsi].m_uFrameDelay,0
        .endif

        .if (SUCCEEDED(hr))

            .if ( [rsi].m_uFrameDelay < 90 )

                mov [rsi].m_uFrameDelay,90
            .endif
        .endif
    .endif

    .if (SUCCEEDED(hr))

        pFrameMetadataQueryReader.GetMetadataByName(L"/grctlext/Disposal", &propValue)
        .if (SUCCEEDED(eax))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI1
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_uFrameDisposal,propValue.bVal
            .endif
        .else

            mov [rsi].m_uFrameDisposal,DM_UNDEFINED
        .endif
    .endif

    PropVariantClear(&propValue)
    SafeRelease(pConverter)
    SafeRelease(pWicFrame)
    SafeRelease(pFrameMetadataQueryReader)
   .return hr

GifView::GetRawFrame endp


GifView::GetBackgroundColor proc uses rsi pMetadataQueryReader:ptr IWICMetadataQueryReader

   .new hr:HRESULT
   .new dwBGColor:DWORD
   .new backgroundIndex:BYTE = 0
   .new rgColors[256]:WICColor
   .new cColorsCopied:UINT = 0
   .new propVariant:PROPVARIANT
   .new pWicPalette:ptr IWICPalette = NULL

    mov rsi,rcx
    PropVariantInit(&propVariant)

    mov hr,pMetadataQueryReader.GetMetadataByName("/logscrdesc/GlobalColorTableFlag", &propVariant)
    .if (SUCCEEDED(hr))

        mov hr,S_OK
        .if (propVariant.vt != VT_BOOL || !propVariant.boolVal)
            mov hr,E_FAIL
        .endif

        PropVariantClear(&propVariant)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pMetadataQueryReader.GetMetadataByName("/logscrdesc/BackgroundColorIndex", &propVariant)
        .if (SUCCEEDED(hr))

            mov hr,S_OK
            .if propVariant.vt != VT_UI1
                mov hr,E_FAIL
            .endif

            .if (SUCCEEDED(hr))

                mov backgroundIndex,propVariant.bVal
            .endif
            PropVariantClear(&propVariant)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.m_pIWICFactory.CreatePalette(&pWicPalette)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.m_pDecoder.CopyPalette(pWicPalette)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pWicPalette.GetColors(ARRAYSIZE(rgColors),  &rgColors, &cColorsCopied)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,S_OK
        .if ( backgroundIndex >= cColorsCopied )
            mov hr,E_FAIL
        .endif
    .endif

    .if (SUCCEEDED(hr))

        movzx ecx,backgroundIndex
        mov dwBGColor,rgColors[rcx*4]

       .new alpha:FLOAT
        shr eax,24
        cvtsi2ss xmm0,eax
        divss xmm0,255.0
        movss alpha,xmm0
        lea rcx,[rsi].m_backgroundColor
        [rcx].D3DCOLORVALUE.Init(dwBGColor, alpha)
    .endif
    SafeRelease(pWicPalette)
   .return(hr)

GifView::GetBackgroundColor endp


    assume rbx:ptr D2D1_RECT_F

GifView::CalculateDrawRectangle proc uses rsi rbx drawRect:ptr D2D1_RECT_F

   .new hr:HRESULT = S_OK
   .new rcClient:RECT

    mov rsi,rcx
    mov rbx,rdx

    .if !GetClientRect([rsi].m_hWnd, &rcClient)

        mov hr,HRESULT_FROM_WIN32R(GetLastError())
    .endif

    .if (SUCCEEDED(hr))

        cvtsi2ss xmm1,[rsi].m_cxGifImagePixel
        cvtsi2ss xmm2,[rsi].m_cyGifImagePixel
        cvtsi2ss xmm0,rcClient.right
        subss    xmm0,xmm1
        divss    xmm0,2.0
        movss    [rbx].left,xmm0
        cvtsi2ss xmm0,rcClient.bottom
        subss    xmm0,xmm2
        divss    xmm0,2.0
        movss    [rbx].top,xmm0
        addss    xmm1,[rbx].left
        movss    [rbx].right,xmm1
        addss    xmm0,xmm2
        movss    [rbx].bottom,xmm0

        cvtsi2ss xmm1,[rsi].m_cxGifImagePixel
        divss    xmm1,xmm2
        movss    xmm0,[rbx].left
        comiss   xmm0,0.0

        .ifb
            mov      [rbx].left,0.0
            cvtsi2ss xmm0,rcClient.right
            movss    [rbx].right,xmm0
            divss    xmm0,xmm1
            cvtsi2ss xmm2,rcClient.bottom
            subss    xmm2,xmm0
            divss    xmm2,2.0
            movss    [rbx].top,xmm2
            addss    xmm2,xmm0
            movss    [rbx].bottom,xmm2
        .endif

        movss  xmm0,[rbx].top
        comiss xmm0,0.0
        .ifb
            cvtsi2ss xmm0,rcClient.bottom
            mov      [rbx].top,0.0
            movss    [rbx].bottom,xmm0
            mulss    xmm0,xmm1
            cvtsi2ss xmm1,rcClient.right
            subss    xmm1,xmm0
            divss    xmm1,2.0
            movss    [rbx].left,xmm1
            addss    xmm0,xmm1
            movss   [rbx].right,xmm0
        .endif
    .endif
    .return(hr)

GifView::CalculateDrawRectangle endp


    assume rbx:nothing
    assume rcx:ptr GifView

GifView::RestoreSavedFrame proc

   .new hr:HRESULT = E_FAIL
   .new pFrameToCopyTo:ptr ID2D1Bitmap = NULL

    .if ( [rcx].m_pSavedFrame )

        mov hr,this.m_pFrameComposeRT.GetBitmap(&pFrameToCopyTo)
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov hr,pFrameToCopyTo.CopyFromBitmap(NULL, [rcx].m_pSavedFrame, NULL)
    .endif
    SafeRelease(pFrameToCopyTo)
   .return(hr)

GifView::RestoreSavedFrame endp


GifView::ClearCurrentFrameArea proc uses rsi

   .new pRT:ptr ID2D1BitmapRenderTarget = [rcx].m_pFrameComposeRT

    mov rsi,rcx
    pRT.BeginDraw()
    pRT.PushAxisAlignedClip(&[rsi].m_framePosition, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE)
    pRT.Clear(&[rsi].m_backgroundColor)
    pRT.PopAxisAlignedClip()
    pRT.EndDraw(NULL, NULL)
    ret

GifView::ClearCurrentFrameArea endp


GifView::DisposeCurrentFrame proc

    .new hr:HRESULT = S_OK
    .switch [rcx].m_uFrameDisposal
    .case DM_UNDEFINED
    .case DM_NONE
        .endc
    .case DM_BACKGROUND
        mov hr,this.ClearCurrentFrameArea()
        .endc
    .case DM_PREVIOUS
        mov hr,this.RestoreSavedFrame()
        .endc
    .default
        mov hr,E_FAIL
    .endsw
    .return hr

GifView::DisposeCurrentFrame endp


GifView::OverlayNextFrame proc uses rsi rbx

    mov rsi,rcx

    .new pRT:ptr ID2D1BitmapRenderTarget = [rcx].m_pFrameComposeRT
    .new hr:HRESULT = this.GetRawFrame([rsi].m_uNextFrameIndex)
    .if (SUCCEEDED(hr))

        .if ( [rsi].m_uFrameDisposal == DM_PREVIOUS )

            mov hr,this.SaveComposedFrame()
        .endif
    .endif

    .if (SUCCEEDED(hr))

        pRT.BeginDraw()

        .if ( [rsi].m_uNextFrameIndex == 0 )

            pRT.Clear(&[rsi].m_backgroundColor)
            inc [rsi].m_uLoopNumber
        .endif

        pRT.DrawBitmap([rsi].m_pRawFrame, &[rsi].m_framePosition, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL)
        mov hr,pRT.EndDraw(NULL, NULL)
    .endif

    .if (SUCCEEDED(hr))

        inc [rsi].m_uNextFrameIndex
        mov eax,[rsi].m_uNextFrameIndex
        cdq
        div [rsi].m_cFrames
        mov [rsi].m_uNextFrameIndex,edx
    .endif
    .return(hr)

GifView::OverlayNextFrame endp

    assume rcx:nothing


GifView::SaveComposedFrame proc uses rsi

    mov rsi,rcx

    .new pFrameToBeSaved:ptr ID2D1Bitmap = NULL
    .new hr:HRESULT = this.m_pFrameComposeRT.GetBitmap(&pFrameToBeSaved)
    .if (SUCCEEDED(hr))

        .if ( [rsi].m_pSavedFrame == NULL )

           .new bitmapSize:D2D1_SIZE_U
           .new bitmapProp:D2D1_BITMAP_PROPERTIES

            pFrameToBeSaved.GetPixelSize(&bitmapSize)
            pFrameToBeSaved.GetDpi(&bitmapProp.dpiX, &bitmapProp.dpiY)
            pFrameToBeSaved.GetPixelFormat(&bitmapProp.pixelFormat)
            mov hr,this.m_pFrameComposeRT.CreateBitmap(bitmapSize, NULL, 0, &bitmapProp, &[rsi].m_pSavedFrame)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.m_pSavedFrame.CopyFromBitmap(NULL, pFrameToBeSaved, NULL)
    .endif

    SafeRelease(pFrameToBeSaved)
   .return(hr)

GifView::SaveComposedFrame endp


GifView::SelectAndDisplayGif proc uses rsi

   .new hr:HRESULT    = S_OK
   .new rcClient:RECT = {0}
   .new rcWindow:RECT = {0}

    mov rsi,rcx
    mov [rsi].m_uNextFrameIndex,0
    mov [rsi].m_uFrameDisposal,DM_NONE
    mov [rsi].m_uLoopNumber,0
    mov [rsi].m_fHasLoop,FALSE

    SafeRelease([rsi].m_pSavedFrame)
    SafeRelease([rsi].m_pDecoder)

    mov hr,this.m_pIWICFactory.CreateDecoderFromFilename([rsi].m_FileName, NULL,
            GENERIC_READ, WICDecodeMetadataCacheOnLoad, &[rsi].m_pDecoder)

    .if (SUCCEEDED(hr))

        mov hr,this.GetGlobalMetadata()
    .endif

    .if (SUCCEEDED(hr))

        mov rcClient.right,[rsi].m_cxGifImagePixel
        mov rcClient.bottom,[rsi].m_cyGifImagePixel

        .if !AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, TRUE)

            mov hr,HRESULT_FROM_WIN32R(GetLastError())
        .endif
    .endif

    .if (SUCCEEDED(hr))

        .if !GetWindowRect([rsi].m_hWnd, &rcWindow)

            mov hr,HRESULT_FROM_WIN32R(GetLastError())
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov r9d,rcClient.right
        sub r9d,rcClient.left
        MoveWindow([rsi].m_hWnd, rcWindow.left, rcWindow.top, r9d, rcClient.Height(), TRUE)

        mov hr,this.CreateDeviceResources()
    .endif

    .if (SUCCEEDED(hr))

        .if ( [rsi].m_cFrames > 0 )

            mov hr,this.ComposeNextFrame()
            InvalidateRect([rsi].m_hWnd, NULL, FALSE)
        .endif
    .endif
    .return(hr)

GifView::SelectAndDisplayGif endp


GifView::ComposeNextFrame proc uses rsi

   .new hr:HRESULT = S_OK

    mov rsi,rcx
    .if ( [rsi].m_pHwndRT && [rsi].m_pFrameComposeRT )

        KillTimer([rsi].m_hWnd, DELAY_TIMER_ID)

        mov hr,this.DisposeCurrentFrame()
        .if (SUCCEEDED(hr))

            mov hr,this.OverlayNextFrame()
        .endif

        .while SUCCEEDED(hr) && [rsi].m_uFrameDelay == 0 && !this.IsLastFrame()

            mov hr,this.DisposeCurrentFrame()
            .if (SUCCEEDED(hr))

                mov hr,this.OverlayNextFrame()
            .endif
        .endw

        .if ( !this.EndOfAnimation() && [rsi].m_cFrames > 1 )

            SetTimer([rsi].m_hWnd, DELAY_TIMER_ID, [rsi].m_uFrameDelay, NULL)
        .endif
    .endif
    .return hr

GifView::ComposeNextFrame endp


GifView::RecoverDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_pHwndRT)
    SafeRelease([rsi].m_pFrameComposeRT)
    SafeRelease([rsi].m_pSavedFrame)

    mov [rsi].m_uNextFrameIndex,0
    mov [rsi].m_uFrameDisposal,DM_NONE
    mov [rsi].m_uLoopNumber,0

    .new hr:HRESULT = this.CreateDeviceResources()
    .if (SUCCEEDED(hr))

        .if ( [rsi].m_cFrames > 0 )

            mov hr,this.ComposeNextFrame()
            InvalidateRect([rsi].m_hWnd, NULL, FALSE)
        .endif
    .endif
    .return hr

GifView::RecoverDeviceResources endp


WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
       .return(1)
    .endif

    .new this:ptr GifView = GetWindowLongPtr(rcx, GWLP_USERDATA)
    .new hr:HRESULT = S_OK

    .switch ( uMsg )

    .case WM_SIZE
        movzx edx,word ptr lParam
        movzx r8d,word ptr lParam[2]
        mov hr,this.OnResize(edx, r8d)
       .endc
    .case WM_PAINT
        mov hr,this.OnRender()
        ValidateRect(hWnd, NULL)
       .endc
    .case WM_DISPLAYCHANGE
        InvalidateRect(hWnd, NULL, FALSE)
       .endc
    .case WM_DESTROY
        PostQuitMessage(0)
       .return 0
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if ( dword ptr wParam == VK_ESCAPE )
        .endc
    .case WM_TIMER
        mov hr,this.ComposeNextFrame()
        InvalidateRect(hWnd, NULL, FALSE)
       .endc
    .default
        .return DefWindowProc(hWnd, uMsg, wParam, lParam)
    .endsw

    .if ( hr == D2DERR_RECREATE_TARGET )

        mov hr,this.RecoverDeviceResources()
        .if (FAILED(hr))

            MessageBox(hWnd, L"Device loss recovery failed. Exiting application.", L"Error", MB_OK)
            PostQuitMessage(1)
        .endif
    .endif
    .return 0

WndProc endp


GifView::Initialize proc uses rsi rdi hInstance:HINSTANCE, file:LPWSTR

    mov rsi,rcx
    mov rdi,rdx
    mov [rsi].m_FileName,r8

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WndProc,                       ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        rdi,                            ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        COLOR_ACTIVEBORDER,             ; .hbrBackground
        NULL,                           ; .lpszMenuName
        "GIFVIEW",                      ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .new hr:HRESULT = E_FAIL
    .ifd RegisterClassEx(&wc)
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                &IID_ID2D1Factory, NULL, &[rsi].m_pD2DFactory)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
                &IID_IWICImagingFactory, &[rsi].m_pIWICFactory)
    .endif

    .if (SUCCEEDED(hr))

        mov [rsi].m_hWnd,CreateWindowEx(0, "GIFVIEW", "GifViwe", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, rdi, rsi)

        mov hr,E_FAIL
        .if rax
            mov hr,S_OK
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,[rsi].SelectAndDisplayGif()
        .if (FAILED(hr))

            DestroyWindow([rsi].m_hWnd)
        .endif
    .endif
    .return(hr)

GifView::Initialize endp


GifView::Release proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_pD2DFactory)
    SafeRelease([rsi].m_pHwndRT)
    SafeRelease([rsi].m_pFrameComposeRT)
    SafeRelease([rsi].m_pRawFrame)
    SafeRelease([rsi].m_pSavedFrame)
    SafeRelease([rsi].m_pIWICFactory)
    SafeRelease([rsi].m_pDecoder)
    free(rsi)
    ret

GifView::Release endp


GifView::GifView proc

    @ComAlloc(GifView)
    ret

GifView::GifView endp


GetFileName proc uses rsi pszCmdLine:LPWSTR

    mov rsi,rcx
    lodsw
    .while ax

        xor ecx,ecx
        xor edx,edx
        .for ( : ax == ' ' || ( ax >= 9 && ax <= 13 ) : )
            lodsw
        .endf
        .break .if !ax
        .if ax == '"'
            lodsw
            inc edx
        .endif
        .while ax == '"'
            lodsw
            inc ecx
        .endw

        .while ax

            .break .if ( !edx && !ecx && ( ax == ' ' || ( ax >= 9 && ax <= 13 ) ) )

            .if ax == '"'
                .if ecx
                    dec ecx
                .elseif edx
                    mov ax,[rsi]
                    .break .if ( ax == ' ' )
                    .break .if ( ax >= 9 && ax <= 13 )
                    dec edx
                .else
                    inc ecx
                .endif
            .endif
            lodsw
        .endw
        .for ( : byte ptr [rsi] == ' ' : )
            lodsw
        .endf
        .break
    .endw
    .if ( ax )
        .return(rsi)
    .endif
    .return(NULL)

GetFileName endp


wWinMain proc public hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPWSTR, nCmdShow:SINT

    .new file:wstring_t = GetFileName(r8)
    .if ( rax == NULL )
        .return(1)
    .endif

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .ifd CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE) == S_OK

        .new app:ptr GifView()
        .ifd app.Initialize(hInstance, file) == S_OK

            .new msg:MSG
            .whiles GetMessage(&msg, NULL, 0, 0) > 0

                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
        .endif
        app.Release()
        CoUninitialize()
    .endif
    .return(0)

wWinMain endp

    end _tstart
