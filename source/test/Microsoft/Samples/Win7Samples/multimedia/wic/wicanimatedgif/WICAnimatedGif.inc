
define IDR_WICANIMATEDGIF   103
define IDM_EXIT             105
define IDM_FILE             106

define DEFAULT_DPI          96.0    ; Default DPI that maps image resolution directly to screen resoltuion

.enum DISPOSAL_METHODS {
    DM_UNDEFINED  = 0,
    DM_NONE       = 1,
    DM_BACKGROUND = 2,
    DM_PREVIOUS   = 3
    }

.class DemoApp

    m_hWnd              HWND ?

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

    DemoApp             proc
    Release             proc

    Initialize          proc :HINSTANCE

    CreateDeviceResources proc
    RecoverDeviceResources proc

    OnResize            proc :UINT, :UINT
    OnRender            proc

    GetFileOpen         proc :LPTSTR, :DWORD
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
    WndProc             proc :HWND, :UINT, :WPARAM, :LPARAM

    .inline IsLastFrame {

        mov edx,1
        xor eax,eax
        cmp [this].DemoApp.m_uNextFrameIndex,0
        cmovnz eax,edx
        }

    .inline EndOfAnimation {

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
endif
