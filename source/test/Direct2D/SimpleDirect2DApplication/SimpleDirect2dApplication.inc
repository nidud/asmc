ifndef WINVER
define WINVER 0x0700
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0700
endif

include windows.inc
include wininet.inc
include stdio.inc
include d2d1.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none

.class DemoApp

    m_hwnd                      HWND ?
    m_pD2DFactory               ptr ID2D1Factory ?
    m_pWICFactory               ptr IWICImagingFactory ?
    m_pDWriteFactory            ptr IDWriteFactory ?
    m_pRenderTarget             ptr ID2D1HwndRenderTarget ?
    m_pTextFormat               ptr IDWriteTextFormat ?
    m_pPathGeometry             ptr ID2D1PathGeometry ?
    m_pLinearGradientBrush      ptr ID2D1LinearGradientBrush ?
    m_pBlackBrush               ptr ID2D1SolidColorBrush ?
    m_pGridPatternBitmapBrush   ptr ID2D1BitmapBrush ?
    m_pBitmap                   ptr ID2D1Bitmap ?
    m_pAnotherBitmap            ptr ID2D1Bitmap ?


    DemoApp proc :ptr
    Release proc

    Initialize proc
    RunMessageLoop proc
    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    CreateGridPatternBrush proc :ptr ID2D1RenderTarget, :ptr ptr ID2D1BitmapBrush
    DiscardDeviceResources proc
    OnRender proc
    OnResize proc :UINT, :UINT

    WndProc proto :HWND, :UINT, :WPARAM, :LPARAM

    LoadResourceBitmap proc :ptr ID2D1RenderTarget,
                            :ptr IWICImagingFactory,
                            :PCWSTR,
                            :PCWSTR,
                            :UINT,
                            :UINT,
                            :ptr ptr ID2D1Bitmap

    LoadBitmapFromFile proc :ptr ID2D1RenderTarget,
                            :ptr IWICImagingFactory,
                            :PCWSTR,
                            :UINT,
                            :UINT,
                            :ptr ptr ID2D1Bitmap

    .ends

ifdef _MSVCRT
.data
 IID_ID2D1Factory                IID _IID_ID2D1Factory
 IID_IDWriteFactory              IID _IID_IDWriteFactory
 IID_IWICImagingFactory          IID _IID_IWICImagingFactory
 CLSID_WICImagingFactory         IID _CLSID_WICImagingFactory
 GUID_WICPixelFormat32bppPBGRA   IID _GUID_WICPixelFormat32bppPBGRA
endif
