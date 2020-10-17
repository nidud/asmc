
IDR_WICANIMATEDGIF equ 103
IDM_EXIT    equ 105
IDM_FILE    equ 106

DEFAULT_DPI equ 96.0    ;; Default DPI that maps image resolution directly to screen resoltuion

.enum DISPOSAL_METHODS {
    DM_UNDEFINED  = 0,
    DM_NONE       = 1,
    DM_BACKGROUND = 2,
    DM_PREVIOUS   = 3
    }

    LPID2D1Factory              typedef ptr ID2D1Factory
    LPID2D1HwndRenderTarget     typedef ptr ID2D1HwndRenderTarget
    LPID2D1BitmapRenderTarget   typedef ptr ID2D1BitmapRenderTarget
    LPID2D1Bitmap               typedef ptr ID2D1Bitmap
    LPIWICImagingFactory        typedef ptr IWICImagingFactory
    LPIWICBitmapDecoder         typedef ptr IWICBitmapDecoder

.class DemoApp

    m_hWnd              HWND ?

    m_pD2DFactory       LPID2D1Factory ?
    m_pHwndRT           LPID2D1HwndRenderTarget ?
    m_pFrameComposeRT   LPID2D1BitmapRenderTarget ?
    m_pRawFrame         LPID2D1Bitmap ?
    m_pSavedFrame       LPID2D1Bitmap ? ;; The temporary bitmap used for disposal 3 method
    m_backgroundColor   D2D1_COLOR_F <>

    m_pIWICFactory      LPIWICImagingFactory ?
    m_pDecoder          LPIWICBitmapDecoder ?

    m_uNextFrameIndex   UINT ?
    m_uTotalLoopCount   UINT ? ;; The number of loops for which the animation will be played
    m_uLoopNumber       UINT ? ;; The current animation loop number (e.g. 1 when the animation is first played)
    m_fHasLoop          BOOL ? ;; Whether the gif has a loop
    m_cFrames           UINT ? ;;
    m_uFrameDisposal    UINT ?
    m_uFrameDelay       UINT ?
    m_cxGifImage        UINT ?
    m_cyGifImage        UINT ?
    m_cxGifImagePixel   UINT ? ;; Width of the displayed image in pixel calculated using pixel aspect ratio
    m_cyGifImagePixel   UINT ? ;; Height of the displayed image in pixel calculated using pixel aspect ratio
    m_framePosition     D2D1_RECT_F <>

    DemoApp proc :ptr
    Release proc

    Initialize proc :HINSTANCE

    CreateDeviceResources proc
    RecoverDeviceResources proc

    OnResize proc :UINT, :UINT
    OnRender proc

    GetFileOpen proc :ptr WCHAR, :DWORD
    SelectAndDisplayGif proc

    GetRawFrame proc :UINT
    GetGlobalMetadata proc
    GetBackgroundColor proc :ptr IWICMetadataQueryReader

    ComposeNextFrame proc
    DisposeCurrentFrame proc
    OverlayNextFrame proc

    SaveComposedFrame proc
    RestoreSavedFrame proc
    ClearCurrentFrameArea proc
    CalculateDrawRectangle proc :ptr D2D1_RECT_F
    WndProc proc :HWND, :UINT, :WPARAM, :LPARAM

    .operator IsLastFrame {

        mov edx,1
        xor eax,eax
        cmp [this].DemoApp.m_uNextFrameIndex,0
        cmovnz eax,edx
        }

    .operator EndOfAnimation {

        .if [this].DemoApp.IsLastFrame()

            xor eax,eax
            .if eax != [this].DemoApp.m_fHasLoop

                mov edx,[this].DemoApp.m_uTotalLoopCount
                inc edx
                .if edx == [this].DemoApp.m_uLoopNumber
                    mov eax,TRUE
                .endif
            .endif
        .endif
        }

    .ends

ifdef _MSVCRT

    .data

    IID_ID2D1Factory              IID _IID_ID2D1Factory
    IID_IWICImagingFactory        IID _IID_IWICImagingFactory
    CLSID_WICImagingFactory       IID _CLSID_WICImagingFactory
    GUID_WICPixelFormat32bppPBGRA IID _GUID_WICPixelFormat32bppPBGRA

    @CurSeg ends

endif
