
define WINVER           0x0A00
define _WIN32_WINNT     0x0A00
define NTDDI_VERSION    0x0A000003

define _USE_MATH_DEFINES
define WIN32_LEAN_AND_MEAN

.pragma list(push, 0)

include windows.inc
include DirectX/d2d1.inc
include DirectX/dwrite.inc
include stdio.inc
include string.inc
include math.inc
include pcg_basic.inc

.pragma list(pop)

define CLASS_NAME <"MainWindowClass">
define WINDOW_NAME <"Windows samples">

define IDS_TEXTFONT <"Segoe UI Light">
define IDS_MONOFONT <"Lucida Console">
define WINDOWSTYLES WS_OVERLAPPEDWINDOW
define MAXOBJ       300
define ID_TIMER     1

pball_t typedef ptr Bounce

.class Bounce

    m_next          pball_t ?
    m_pos           POINT <>
    m_mov           POINT <>
    m_radius        uint_t ?
    m_brush         ptr ID2D1RadialGradientBrush ?
    m_color         D3DCOLORVALUE <>

    Bounce          proc
    Release         proc
    New             proc
    Up              proc
    Down            proc
   .ends


.class CApplication

    m_hInstance         HINSTANCE ?
    m_hwnd              HWND ?
    m_rect              RECT <>
    m_size              D2D1_SIZE_U <>
    m_rc                RECT <>
    m_obj               pball_t ?
    m_count             uint_t ?
    m_texty             int_t ?
    m_timer             int_t ?
    m_rand              int_t ?
    m_intensity         int_t ?
    m_isFullScreen      BOOL ?
    m_pD2DFactory       ptr ID2D1Factory ?
    m_pDWriteFactory    ptr IDWriteFactory ?
    m_pRT               ptr ID2D1HwndRenderTarget ?
    m_pTextFont         ptr IDWriteTextFormat ?
    m_pTextFont2        ptr IDWriteTextFormat ?
    m_pMonoFont         ptr IDWriteTextFormat ?
    m_pSolidColorBrush  ptr ID2D1SolidColorBrush ?


    CApplication                        proc :HINSTANCE
    Release                             proc
    Run                                 proc
    OnKeyDown                           proc :WPARAM
    OnClose                             proc
    OnDestroy                           proc
    OnRender                            proc
    OnSize                              proc :UINT, :UINT
    InitObjects                         proc
    GoFullScreen                        proc
    GoPartialScreen                     proc
    CreateDeviceIndependentResources    proc
    CreateDeviceResources               proc
    RenderMainContent                   proc
    RenderTextInfo                      proc
    DiscardDeviceResources              proc
    BeforeEnteringMessageLoop           proc
    EnterMessageLoop                    proc
    AfterLeavingMessageLoop             proc
    CreateApplicationWindow             proc
    ShowApplicationWindow               proc
    DestroyApplicationWindow            proc
    BoundRand                           proc :uint_t
    RangeRand                           proc :uint_t, :uint_t
    RandRGB                             proc :ptr D3DCOLORVALUE, :int_t
    ErrorMessage                        proc :HRESULT, :LPTSTR
   .ends

