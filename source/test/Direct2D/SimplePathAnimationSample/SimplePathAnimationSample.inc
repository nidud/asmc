
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

;; Windows Header Files:
include windows.inc

;; C RunTime Header Files
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

;/******************************************************************
;*                                                                 *
;*  Macros                                                         *
;*                                                                 *
;******************************************************************/

SafeRelease proto :ptr, :abs {

    mov rax,[this]
    .if rax
        mov qword ptr [this],NULL
        [rax]._1.Release()
    .endif
    }


ifndef HINST_THISCOMPONENT
ifndef _MSVCRT
extern __ImageBase:IMAGE_DOS_HEADER
endif
HINST_THISCOMPONENT equ <&__ImageBase>
endif


;/******************************************************************
;*                                                                 *
;*  DemoApp                                                        *
;*                                                                 *
;******************************************************************/

    LPID2D1Factory          typedef ptr ID2D1Factory
    LPID2D1HwndRenderTarget typedef ptr ID2D1HwndRenderTarget
    LPID2D1PathGeometry     typedef ptr ID2D1PathGeometry
    LPID2D1SolidColorBrush  typedef ptr ID2D1SolidColorBrush

.class DemoApp

    m_hwnd              HWND ?
    m_pD2DFactory       LPID2D1Factory ?
    m_pRT               LPID2D1HwndRenderTarget ?
    m_pPathGeometry     LPID2D1PathGeometry ?
    m_pObjectGeometry   LPID2D1PathGeometry ?
    m_pRedBrush         LPID2D1SolidColorBrush ?
    m_pYellowBrush      LPID2D1SolidColorBrush ?
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
