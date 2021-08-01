
include windows.inc
include gdiplus.inc
include tchar.inc

define IDS_FONT_TYPEFACE <"Segoe UI Light">
define IDS_FONT_HEIGHT_LOGO 0
define IDS_FONT_HEIGHT_TITLE 50
define IDS_FONT_HEIGHT_DESCRIPTION 22
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
    m_width         int_t ?
    m_height        int_t ?
    m_rect          RECT <>
    m_bitmap        HBITMAP ?
    m_rc            RECT <>
    m_obj           object MAXOBJ dup(<>)
    m_count         uint_t ?
    m_timer         uint_t ?
    m_isFullScreen  BOOL ?

    CApplication    proc :HINSTANCE, :ptr CApplicationVtbl
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

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

