
;/******************************************************************
;*                                                                 *
;*  DemoApp                                                        *
;*                                                                 *
;******************************************************************/

    LPID2D1Factory          typedef ptr ID2D1Factory
    LPIWICImagingFactory    typedef ptr IWICImagingFactory
    LPIDWriteFactory        typedef ptr IDWriteFactory
    LPID2D1HwndRenderTarget typedef ptr ID2D1HwndRenderTarget
    LPIDWriteTextFormat     typedef ptr IDWriteTextFormat
    LPID2D1SolidColorBrush  typedef ptr ID2D1SolidColorBrush
    LPIGeometryRealization  typedef ptr IGeometryRealization

.class DemoApp

    m_hwnd              HWND ?

    m_antialiasMode     D2D1_ANTIALIAS_MODE ?
    m_useRealizations   BOOL ?
    m_autoGeometryRegen BOOL ?
    m_drawStroke        BOOL ?
    m_paused            BOOL ?
    m_updateRealization BOOL ?
    m_numSquares        UINT ?
    m_mousePos          D2D1_POINT_2F <>
    m_pausedTime        LONGLONG ?
    m_timeDelta         LONGLONG ?
    m_targetZoomFactor  float ?
    m_currentZoomFactor float ?
    m_times             LPRingBuffer ?

    m_pD2DFactory       LPID2D1Factory ?
    m_pWICFactory       LPIWICImagingFactory ?
    m_pDWriteFactory    LPIDWriteFactory ?
    m_pRT               LPID2D1HwndRenderTarget ?
    m_pTextFormat       LPIDWriteTextFormat ?
    m_pSolidColorBrush  LPID2D1SolidColorBrush ?
    m_pRealization      LPIGeometryRealization ?
    m_pGeometry         LPID2D1Geometry ?

    DemoApp             proc :ptr, :ptr
    Release             proc

    Initialize          proc
    RunMessageLoop      proc
    CreateDeviceIndependentResources proc
    CreateGeometries    proc
    CreateDeviceResources proc
    DiscardDeviceResources proc
    DiscardGeometryData proc
    RenderMainContent   proc :float
    RenderTextInfo      proc
    OnRender            proc
    OnResize            proc :UINT, :UINT
    OnMouseMove         proc :LPARAM
    OnKeyDown           proc :WORD
    OnWheel             proc :WPARAM

    WndProc             proto :HWND, :UINT, :WPARAM, :LPARAM

    .ends
