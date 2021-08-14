define WINVER           0x0A00
define _WIN32_WINNT     0x0A00
define NTDDI_VERSION    0x0A000003

include windows.inc
include gdiplus.inc
;include d2d1.inc
;include dwrite_3.inc
include stdio.inc
include Pathcch.inc
include tchar.inc

define IDS_FONT         <"Segoe UI Light">
define IDS_FONT2        <"Caudex">
define WINDOWSTYLES     WS_SIZEBOX or WS_SYSMENU or WS_CLIPCHILDREN or WS_CAPTION or WS_MAXIMIZEBOX

define MAXOBJ 100

.class CGFont

    m_font          ptr ?
    m_gp            ptr ?
    m_family        ptr ?
    m_format        ptr ?
    m_style         int_t ?
    m_unit          int_t ?
    m_color         ARGB ?
    m_width         int_t ?
    m_height        int_t ?
    m_file          ptr wchar_t ?

    CGFont          proc :ptr wchar_t, :ptr wchar_t, :StringFormatFlags
    Release         proc
    SetFamily       proc :ptr wchar_t
    SetColor        proc :ARGB
    SetSize         proc :int_t
    SetFont         proc :ptr wchar_t, :int_t, :ARGB
    SetFormat       proc :StringFormatFlags
    SetAlignment    proc :StringAlignment
    SetGDI          proc :HDC, :int_t, :int_t
    Draw            proc :int_t, :int_t, :ptr wchar_t, :vararg
   .ends


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
    m_texty         int_t ?
    m_isFullScreen  BOOL ?
    m_hdc           HDC ?
    m_mem           HDC ?
    m_g1            ptr ?
    m_g2            ptr ?
    m_f1            ptr CGFont ?
    m_f2            ptr CGFont ?
    m_f3            ptr CGFont ?

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

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

