.pragma list(push, 0)

include windows.inc
include DirectX/d2d1.inc
include stdio.inc
include math.inc
include immintrin.inc
include commctrl.inc
include winres.inc
include tchar.inc

.pragma list(pop)

.pragma comment(linker,
    "/manifestdependency:\""
    "type='win32' "
    "name='Microsoft.Windows.Common-Controls' "
    "version='6.0.0.0' "
    "processorArchitecture='*' "
    "publicKeyToken='6595b64144ccf1df' "
    "language='*'"
    "\""
    )

define CLASS_NAME   <"MainWindowClass">
define WINDOWSTYLES WS_VISIBLE or WS_POPUP
define ID_TIMER     1
define IDD_HELP     129
define RADIUS       0.17

.class CApplication

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_rect          RECT <>
    m_size          D2D1_SIZE_U <>
    m_time          real4 ?
    m_DeltaX        real4 ?
    m_DeltaY        real4 ?
    m_radius        real4 ?
    m_step          int_t ?
    m_count         int_t ?
    m_texty         int_t ?
    m_timer         int_t ?
    m_intensity     int_t ?
    m_isFullScreen  BOOL ?
    m_pD2DFactory   ptr ID2D1Factory ?
    m_pRT           ptr ID2D1HwndRenderTarget ?
    m_brush         ptr ID2D1RadialGradientBrush ?

    CApplication    proc :HINSTANCE
    Release         proc
    Run             proc
    Point           proc :UINT
    OnKeyDown       proc :WPARAM
    OnRender        proc
    OnSize          proc :UINT, :UINT
    OnClose         proc
    GoFullScreen    proc
    GoPartialScreen proc
    CreateDeviceResources proc
    RenderMainContent proc
    EnterMessageLoop proc
    CreateApplicationWindow proc
    ErrorMessage    proc :HRESULT, :LPTSTR
   .ends

.data
 IID_ID2D1Factory GUID {0x06152247,0x6f50,0x465a,{0x92,0x45,0x11,0x8b,0xfd,0x3b,0x60,0x07}}

.code

 assume class:rbx

