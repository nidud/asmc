
include windows.inc
include gdiplus.inc
include stdio.inc
include tchar.inc

define IDS_FONT_TYPEFACE <"Segoe UI Light">
define RESTOREDWINDOWSTYLES WS_SIZEBOX or WS_SYSMENU or WS_CLIPCHILDREN or WS_CAPTION or WS_MAXIMIZEBOX

define MAXOBJ 100

.template object
    m_pos           POINT <>
    m_mov           POINT <>
    m_radius        uint_t ?
    m_color         ARGB ?
   .ends

.class CApplication

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_rect          RECT <>
    m_bitmap        HBITMAP ?
    m_rc            RECT <>
    m_obj           object MAXOBJ dup(<>)
    m_count         uint_t ?
    m_timer         uint_t ?
    m_isFullScreen  BOOL ?
    m_hdc           HDC ?
    m_mem           HDC ?
    m_g             ptr ?
    m_gm            ptr ?

    m_font          ptr ?
    m_fontfamily    ptr ?
    m_fontformat    ptr ?
    m_fontstyle     int_t ?
    m_fontunit      int_t ?
    m_fontcolor     ARGB ?

    CApplication    proc :HINSTANCE
    Run             proc
    OnKeyDown       proc :WPARAM
    OnClose         proc
    OnDestroy       proc
    OnPaint         proc
    OnTimer         proc
    OnSize          proc :LPARAM
    InitObjects     proc
    GoFullScreen    proc
    GoPartialScreen proc
    SetFont         proc :ptr wchar_t, :real4, :ARGB
    DrawString      proc :ptr, :int_t, :int_t, :ptr wchar_t, :vararg

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

