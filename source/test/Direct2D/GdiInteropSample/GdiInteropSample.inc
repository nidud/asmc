
;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.
ifndef WINVER               ;; Allow use of features specific to Windows 7 or later.
WINVER equ 0x0700           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows 7 or later.
_WIN32_WINNT equ 0x0700     ;; Change this to the appropriate value to target other versions of Windows.
endif

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

;******************************************************************
;*                                                                *
;*  Macros                                                        *
;*                                                                *
;******************************************************************

SafeRelease proto :ptr, :abs {

    mov rax,[_1]
    .if rax
        mov qword ptr [_1],NULL
        [rax]._2.Release()
    .endif
    }


ifndef HINST_THISCOMPONENT
ifndef _MSVCRT
extern __ImageBase:IMAGE_DOS_HEADER
endif
HINST_THISCOMPONENT equ <&__ImageBase>
endif

;******************************************************************
;*                                                                *
;*  DemoApp                                                       *
;*                                                                *
;******************************************************************

    LPID2D1Factory typedef ptr ID2D1Factory
    LPID2D1DCRenderTarget typedef ptr ID2D1DCRenderTarget
    LPID2D1SolidColorBrush typedef ptr ID2D1SolidColorBrush

.class DemoApp

    m_hwnd HWND ?
    m_pD2DFactory LPID2D1Factory ?
    m_pDCRT LPID2D1DCRenderTarget ?
    m_pBlackBrush LPID2D1SolidColorBrush ?

    DemoApp proc :ptr
    Release proc

    Initialize proc
    RunMessageLoop proc
    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    DiscardDeviceResources proc
    OnRender proc :ptr PAINTSTRUCT

    WndProc proto :HWND, :UINT, :WPARAM, :LPARAM
    .ends

ifdef _MSVCRT

    .data
    IID_ID2D1Factory IID _IID_ID2D1Factory

endif
