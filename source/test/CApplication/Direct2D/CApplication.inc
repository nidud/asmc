
define WINVER           0x0A00
define _WIN32_WINNT     0x0A00
define NTDDI_VERSION    0x0A000003
define _USE_MATH_DEFINES

include windows.inc
include d2d1.inc
include dwrite.inc
include stdio.inc
include math.inc
include tchar.inc

option dllimport:none

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define IDS_TEXTFONT <"Segoe UI Light">
define IDS_MONOFONT <"Lucida Console">
define WINDOWSTYLES WS_OVERLAPPEDWINDOW
define MAXOBJ       300
define ID_TIMER     1

.template object
    m_pos           POINT <>
    m_mov           POINT <>
    m_radius        uint_t ?
    m_color         D3DCOLORVALUE <>
    m_brush         ptr ID2D1RadialGradientBrush ?
   .ends


.class CApplication

    m_hInstance         HINSTANCE ?
    m_hwnd              HWND ?
    m_rect              RECT <>
    m_size              D2D1_SIZE_U <>
    m_rc                RECT <>
    m_obj               object MAXOBJ dup(<>)
    m_count             uint_t ?
    m_texty             int_t ?
    m_timer             int_t ?
    m_intensity         int_t ?
    m_isFullScreen      BOOL ?
    m_pD2DFactory       ptr ID2D1Factory ?
    m_pDWriteFactory    ptr IDWriteFactory ?
    m_pRT               ptr ID2D1HwndRenderTarget ?
    m_pTextFont         ptr IDWriteTextFormat ?
    m_pTextFont2        ptr IDWriteTextFormat ?
    m_pMonoFont         ptr IDWriteTextFormat ?
    m_pSolidColorBrush  ptr ID2D1SolidColorBrush ?


    CApplication        proc :HINSTANCE
    Release             proc
    Run                 proc
    OnKeyDown           proc :WPARAM
    OnClose             proc
    OnDestroy           proc
    OnRender            proc
    OnSize              proc :UINT, :UINT
    InitObjects         proc
    GoFullScreen        proc
    GoPartialScreen     proc
    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    RenderMainContent   proc
    RenderTextInfo      proc
    DiscardDeviceResources proc
    BeforeEnteringMessageLoop proc
    EnterMessageLoop    proc
    AfterLeavingMessageLoop proc
    CreateApplicationWindow proc
    ShowApplicationWindow proc
    DestroyApplicationWindow proc
   .ends

SafeRelease proto p:abs {
    mov rax,p
    .if rax
        mov p,NULL
        [rax].@SubStr(typeid(p), 2).Release()
    .endif
    }

ifdef _MSVCRT
.data
 IID_ID2D1Factory   IID _IID_ID2D1Factory
 IID_IDWriteFactory IID _IID_IDWriteFactory
endif

