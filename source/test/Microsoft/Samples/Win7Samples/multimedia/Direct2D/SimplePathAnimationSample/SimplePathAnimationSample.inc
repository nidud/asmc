ifndef WINVER
define WINVER 0x0700
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0700
endif

include windows.inc
include stdlib.inc
include malloc.inc
include memory.inc
include wchar.inc
include d2d1.inc
include d2d1helper.inc
include dwrite.inc
include wincodec.inc
include dwmapi.inc
include tchar.inc
include Animation.inc

option dllimport:none

.class DemoApp

    m_hwnd              HWND ?
    m_pD2DFactory       ptr ID2D1Factory ?
    m_pRT               ptr ID2D1HwndRenderTarget ?
    m_pPathGeometry     ptr ID2D1PathGeometry ?
    m_pObjectGeometry   ptr ID2D1PathGeometry ?
    m_pRedBrush         ptr ID2D1SolidColorBrush ?
    m_pYellowBrush      ptr ID2D1SolidColorBrush ?
    m_Animation         EaseInOutExponentialAnimation <>
    m_DwmTimingInfo     DWM_TIMING_INFO <>
    m_Time              float ?

    DemoApp             proc :ptr
    Release             proc

    Initialize          proc
    RunMessageLoop      proc
    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    DiscardDeviceResources proc
    OnRender            proc :ptr PAINTSTRUCT
    OnResize            proc :UINT, :UINT
    WndProc             proto :HWND, :UINT, :WPARAM, :LPARAM
   .ends

ifdef _MSVCRT
.data
 IID_ID2D1Factory IID _IID_ID2D1Factory
endif
