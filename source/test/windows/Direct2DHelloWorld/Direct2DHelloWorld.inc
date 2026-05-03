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
include math.inc
include d2d1.inc
include d2d1helper.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none

.class DemoApp

    m_hwnd              HWND ?
    m_pD2DFactory       ptr ID2D1Factory ?
    m_pWICFactory       ptr IWICImagingFactory ?
    m_pDWriteFactory    ptr IDWriteFactory ?
    m_pRenderTarget     ptr ID2D1HwndRenderTarget ?
    m_pTextFormat       ptr IDWriteTextFormat ?
    m_pBlackBrush       ptr ID2D1SolidColorBrush ?


    DemoApp proc
    Release proc

    Initialize proc
    RunMessageLoop proc
    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    DiscardDeviceResources proc
    OnRender proc
    OnResize proc :UINT, :UINT
   .ends

ifdef _MSVCRT
.data
 IID_ID2D1Factory    IID _IID_ID2D1Factory
 IID_IDWriteFactory  IID _IID_IDWriteFactory
endif
