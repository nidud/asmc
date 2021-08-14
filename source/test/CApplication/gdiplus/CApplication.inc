
define WINVER 0x0700
define _WIN32_WINNT 0x0700

include windows.inc
include gdiplus.inc
include tchar.inc

define IDS_FONT_TYPEFACE <"Segoe UI Light">
define IDS_FONT_HEIGHT_LOGO 0
define IDS_FONT_HEIGHT_TITLE 50
define IDS_FONT_HEIGHT_DESCRIPTION 22
define MAXOBJ 3

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
    m_bitmap        HBITMAP ?
    m_rc            RECT <>
    m_obj           object MAXOBJ dup(<>)

    CApplication    proc :HINSTANCE
    Run             proc
    OnKeyDown       proc :WPARAM
    OnClose         proc
    OnDestroy       proc
    OnPaint         proc
    OnTimer         proc
    OnSize          proc :LPARAM

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

