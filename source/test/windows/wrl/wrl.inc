
define WINVER 0x0700
define _WIN32_WINNT 0x0700

include windows.inc
include gdiplus.inc
include objbase.inc
include shobjidl.inc
include stdio.inc
include wrl\client.inc
include wrl\implements.inc
include tchar.inc

define IDS_FONT_TYPEFACE <"Segoe UI Light">
define IDS_FONT_HEIGHT_LOGO 0
define IDS_FONT_HEIGHT_TITLE 50
define IDS_FONT_HEIGHT_DESCRIPTION 22

.class CApplication : public IAppVisibilityEvents

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_width         int_t ?
    m_height        int_t ?
    m_refcnt        int_t ?
    m_launchcnt     int_t ?
    m_cookie        uint_t ?
    m_AppVisibility ptr IAppVisibility ?
    m_yoffs         uint_t ?

    CApplication    proc :HINSTANCE
    Run             proc
    OnKeyDown       proc :WPARAM
    OnClose         proc
    OnDestroy       proc
    OnPaint         proc
    OnSize          proc :LPARAM
    Update          proc :BOOL

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

