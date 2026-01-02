
define sc_fontName             <"Calibri">
define sc_fontSize             20.0
define sc_textInfoBox          <10.0, 10.0, 350.0, 200.0>
define sc_textInfoBoxInset     10.0
define sc_defaultNumSquares    16
define sc_minNumSquares        1
define sc_maxNumSquares        1024
define sc_boardWidth           900.0
define sc_rotationSpeed        3.0
define sc_loupeInset           20.0
define sc_maxZoom              15.0
define sc_minZoom              1.0
define sc_zoomStep             1.5
define sc_zoomSubStep          1.1
define sc_strokeWidth          1.0

; This determines that maximum texture size we will
; generate for our realizations.

define sc_maxRealizationDimension 2000

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

    DemoApp             proc :ptr
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
