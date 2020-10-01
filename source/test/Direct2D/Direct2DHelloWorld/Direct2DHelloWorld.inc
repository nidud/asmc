
;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER               ;; Allow use of features specific to Windows 7 or later.
WINVER equ 0x0700           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows 7 or later.
_WIN32_WINNT equ 0x0700     ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _UNICODE
_UNICODE equ 1
endif

;WIN32_LEAN_AND_MEAN  equ 1  ;; Exclude rarely-used stuff from Windows headers
;; Windows Header Files:
include windows.inc

;; C RunTime Header Files
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

;;
;; Macros
;;

SafeRelease proto :ptr, :abs {

    mov rax,[this]
    .if rax
        mov qword ptr [this],NULL
        [rax]._1.Release()
    .endif
    }


ifndef HINST_THISCOMPONENT
HINST_THISCOMPONENT equ <&__ImageBase>
endif

;;
;;  DemoApp
;;

    LPID2D1Factory              typedef ptr ID2D1Factory
    LPIWICImagingFactory        typedef ptr IWICImagingFactory
    LPIDWriteFactory            typedef ptr IDWriteFactory
    LPID2D1HwndRenderTarget     typedef ptr ID2D1HwndRenderTarget
    LPIDWriteTextFormat         typedef ptr IDWriteTextFormat
    LPID2D1SolidColorBrush      typedef ptr ID2D1SolidColorBrush

.class DemoApp

    m_hwnd              HWND ?
    m_pD2DFactory       LPID2D1Factory ?
    m_pWICFactory       LPIWICImagingFactory ?
    m_pDWriteFactory    LPIDWriteFactory ?
    m_pRenderTarget     LPID2D1HwndRenderTarget ?
    m_pTextFormat       LPIDWriteTextFormat ?
    m_pBlackBrush       LPID2D1SolidColorBrush ?


    DemoApp proc :ptr
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
    @CurSeg ends
else
    extern __ImageBase:byte
endif
