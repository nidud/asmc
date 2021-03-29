
;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.

ifndef WINVER               ;; Allow use of features specific to Windows XP or later.
WINVER equ 0x0501           ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT         ;; Allow use of features specific to Windows XP or later.
_WIN32_WINNT equ 0x0501     ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINDOWS       ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410   ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE            ;; Allow use of features specific to IE 6.0 or later.
_WIN32_IE equ 0x0700        ;; Change this to the appropriate value to target other versions of IE.
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

include shobjidl.inc
include objbase.inc
include strsafe.inc

_USE_MATH_DEFINES equ 1
include math.inc
include tchar.inc

option dllimport:none


;/******************************************************************
;*                                                                 *
;*  Macros                                                         *
;*                                                                 *
;******************************************************************/

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

;; Size of bitmap atlas (in pixels)
msc_atlasWidth equ 2048
msc_atlasHeight equ 2048

;; Width/Height of each icon
msc_iconSize equ 48

;; Space between each item
msc_lineSpacing equ 10

;; Number of frames to show while animating item repositioning
msc_totalAnimatingItemFrames equ 60

;; Number of frames to show while animating scrolls
msc_totalAnimatingScrollFrames equ 10

;; Static size of item info array
msc_maxItemInfos equ msc_atlasHeight * msc_atlasWidth / (msc_iconSize * msc_iconSize)


;/******************************************************************
;*                                                                 *
;*  ItemInfo                                                       *
;*                                                                 *
;******************************************************************/

.class ItemInfo

    placement           D2D1_RECT_U <>
    szFilename          WCHAR MAX_PATH dup(?)
    currentPosition     FLOAT ?
    previousPosition    FLOAT ?
    isDirectory         BOOL ?

    .inline ItemInfo {
        mov rdx,rdi
        xor eax,eax
        mov rdi,rcx
        mov ecx,ItemInfo
        rep stosb
        mov rdi,rdx
        }

    .ends

.class ListViewApp

    LPID2D1Factory          typedef ptr ID2D1Factory
    LPIWICImagingFactory    typedef ptr IWICImagingFactory
    LPIDWriteFactory        typedef ptr IDWriteFactory
    LPID2D1HwndRenderTarget typedef ptr ID2D1HwndRenderTarget
    LPIDWriteTextFormat     typedef ptr IDWriteTextFormat
    LPID2D1SolidColorBrush  typedef ptr ID2D1SolidColorBrush
    LPIBindCtx              typedef ptr IBindCtx
    LPID2D1Bitmap           typedef ptr ID2D1Bitmap

    m_pD2DFactory           LPID2D1Factory ?
    m_pWICFactory           LPIWICImagingFactory ?
    m_pDWriteFactory        LPIDWriteFactory ?
    m_pRT                   LPID2D1HwndRenderTarget ?
    m_pTextFormat           LPIDWriteTextFormat ?
    m_pBlackBrush           LPID2D1SolidColorBrush ?
    m_pBindContext          LPIBindCtx ?
    m_pBitmapAtlas          LPID2D1Bitmap ?

    ;; Number of item infos actually loaded (<= msc_maxItemInfos)
    m_numItemInfos          UINT ?

    ;; Maximum scroll amount
    m_scrollRange           UINT ?

    ;; m_currentScrollPos is the current scroll position. We animate to the
    ;; current scroll position from the previous scroll position,
    ;; m_previousScrollPos, interpolating between the two based on the factor
    ;; m_animatingItems / msc_totalAnimatingScrollFrames.
    m_previousScrollPos     SINT ?
    m_currentScrollPos      SINT ?
    m_animatingScroll       UINT ?

    ;; m_animatingItems / msc_totalAnimatingItemFrames is the interpolation
    ;; factor for animating between the previousPosition and currentPosition of
    ;; each ItemInfo
    m_animatingItems        UINT ?

    m_d2dHwnd               HWND ?
    m_parentHwnd            HWND ?

    m_pFiles                ItemInfo msc_maxItemInfos dup(<>)


    ListViewApp proc
    Release proc

    Initialize proc

    RunMessageLoop proc

    CreateDeviceIndependentResources proc
    CreateDeviceResources proc
    DiscardDeviceResources proc

    OnRender proc

    OnResize proc

    OnChar proc aChar:SWORD


    OnVScroll proc wParam:WPARAM, lParam:LPARAM

    ;GetScrollRange proc
    ;GetScrollPos proc

    OnMouseWheel proc wParam:WPARAM, lParam:LPARAM

    OnLeftButtonDown proc diPosition:D2D1_POINT_2F

    CalculateD2DWindowSize proc :ptr D2D1_SIZE_U

    ChildWndProc proto hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    ParentWndProc proto hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    LoadDirectory proc

    GetFancyAccelerationInterpolatedValue proto linearFactor:FLOAT, p1:FLOAT, p2:FLOAT

    GetAnimatingItemInterpolationFactor proc
    GetAnimatingScrollInterpolationFactor proc
    GetInterpolatedScrollPosition proc

    GetScrolledDIPositionFromPixelPosition proc :D2D1_POINT_2U

    ;/******************************************************************
    ;*                                                                 *
    ;*  Comparator functions (for sorting)                             *
    ;*                                                                 *
    ;******************************************************************/

    CompareAToZ proto a:ptr, b:ptr
    CompareZToA proto a:ptr, b:ptr
    CompareDirFirstAToZ proto a:ptr, b:ptr

    .ends

ifdef _MSVCRT

    .data
    IID_ID2D1Factory                IID _IID_ID2D1Factory
    IID_IDWriteFactory              IID _IID_IDWriteFactory
    IID_IWICImagingFactory          IID _IID_IWICImagingFactory
    CLSID_WICImagingFactory         IID _CLSID_WICImagingFactory
    IID_IShellItemImageFactory      IID _IID_IShellItemImageFactory
    @CurSeg ends

endif
