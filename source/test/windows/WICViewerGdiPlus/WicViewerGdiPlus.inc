
IDR_MAINMENU            equ 104
IDM_EXIT                equ 106
IDM_FILE                equ 107

option dllimport:none

.class DemoApp

    m_hInst             HINSTANCE ?
    m_pGdiPlusBitmap    Bitmap <>
    m_pbBuffer          ptr BYTE ?
    m_pIWICFactory      ptr IWICImagingFactory ?
    m_pOriginalBitmapSource ptr IWICBitmapSource ?

    DemoApp             proc
    Release             proc
    Initialize          proc :HINSTANCE

    CreateDIBFromFile   proc :HWND
    LocateImageFile     proc :HWND, :LPWSTR, :DWORD
    ConvertBitmapSource proc :HWND, :ptr ptr IWICBitmapSource
    CreateDIBSectionFromBitmapSource proc :ptr IWICBitmapSource
    DeleteBufferAndBmp  proc

    WndProc             proc :HWND, :UINT, :WPARAM, :LPARAM
    OnPaint             proc :HWND
   .ends

UIntMult proto asmcall :UINT, :UINT, :ptr UINT {
    imul _1,_2
    mov [_3],eax
    }

ifdef _MSVCRT
.data
 IID_IWICImagingFactory      IID _IID_IWICImagingFactory
 CLSID_WICImagingFactory     IID _CLSID_WICImagingFactory
 IID_IWICBitmapSource        IID _IID_IWICBitmapSource
 GUID_WICPixelFormat32bppBGR IID _GUID_WICPixelFormat32bppBGR
endif
