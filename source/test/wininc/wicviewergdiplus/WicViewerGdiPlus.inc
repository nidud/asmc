
IDR_MAINMENU            equ 104
IDM_EXIT                equ 106
IDM_FILE                equ 107

LPIWICImagingFactory    typedef ptr IWICImagingFactory
LPIWICBitmapSource      typedef ptr IWICBitmapSource

option dllimport:none

.class DemoApp

    m_hInst             HINSTANCE ?
    m_pGdiPlusBitmap    Bitmap <>
    m_pbBuffer          LPBYTE ?
    m_pIWICFactory      LPIWICImagingFactory ?
    m_pOriginalBitmapSource LPIWICBitmapSource ?

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

SafeRelease proto :ptr, :abs {
    mov rax,[this]
    .if rax
        mov qword ptr [this],NULL
        [rax]._1.Release()
    .endif
    }

    .data

    IID_IWICImagingFactory      IID _IID_IWICImagingFactory
    CLSID_WICImagingFactory     IID _CLSID_WICImagingFactory
    IID_IWICBitmapSource        IID _IID_IWICBitmapSource
    GUID_WICPixelFormat32bppBGR IID _GUID_WICPixelFormat32bppBGR

    @CurSeg ends






