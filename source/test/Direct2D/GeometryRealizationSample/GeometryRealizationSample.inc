
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
    m_times             ptr RingBuffer ?

    m_pD2DFactory       ptr ID2D1Factory ?
    m_pWICFactory       ptr IWICImagingFactory ?
    m_pDWriteFactory    ptr IDWriteFactory ?
    m_pRT               ptr ID2D1HwndRenderTarget ?
    m_pTextFormat       ptr IDWriteTextFormat ?
    m_pSolidColorBrush  ptr ID2D1SolidColorBrush ?
    m_pRealization      ptr IGeometryRealization ?
    m_pGeometry         ptr ID2D1Geometry ?

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
