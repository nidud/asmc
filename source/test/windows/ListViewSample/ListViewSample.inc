ifndef WINVER
define WINVER 0x0501
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0501
endif
ifndef _WIN32_WINDOWS
define _WIN32_WINDOWS 0x0410
endif
ifndef _WIN32_IE
define _WIN32_IE 0x0700
endif
define _USE_MATH_DEFINES

include windows.inc
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
include math.inc
include tchar.inc

option dllimport:none

define msc_fontName     <"Calibri">
define msc_fontSize     20.0

define msc_atlasWidth   2048    ; Size of bitmap atlas (in pixels)
define msc_atlasHeight  2048
define msc_iconSize     48      ; Width/Height of each icon
define msc_lineSpacing  10      ; Space between each item

; Number of frames to show while animating item repositioning

define msc_totalAnimatingItemFrames 60

; Number of frames to show while animating scrolls

define msc_totalAnimatingScrollFrames 10

; Static size of item info array

define msc_maxItemInfos ( msc_atlasHeight * msc_atlasWidth / (msc_iconSize * msc_iconSize) )


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

    m_pD2DFactory           ptr ID2D1Factory ?
    m_pWICFactory           ptr IWICImagingFactory ?
    m_pDWriteFactory        ptr IDWriteFactory ?
    m_pRT                   ptr ID2D1HwndRenderTarget ?
    m_pTextFormat           ptr IDWriteTextFormat ?
    m_pBlackBrush           ptr ID2D1SolidColorBrush ?
    m_pBindContext          ptr IBindCtx ?
    m_pBitmapAtlas          ptr ID2D1Bitmap ?

    ; Number of item infos actually loaded (<= msc_maxItemInfos)
    m_numItemInfos          UINT ?

    ; Maximum scroll amount
    m_scrollRange           UINT ?

    ; m_currentScrollPos is the current scroll position. We animate to the
    ; current scroll position from the previous scroll position,
    ; m_previousScrollPos, interpolating between the two based on the factor
    ; m_animatingItems / msc_totalAnimatingScrollFrames.
    m_previousScrollPos     SINT ?
    m_currentScrollPos      SINT ?
    m_animatingScroll       UINT ?

    ; m_animatingItems / msc_totalAnimatingItemFrames is the interpolation
    ; factor for animating between the previousPosition and currentPosition of
    ; each ItemInfo
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

    CompareAToZ proto a:ptr, b:ptr
    CompareZToA proto a:ptr, b:ptr
    CompareDirFirstAToZ proto a:ptr, b:ptr
   .ends

ifdef _MSVCRT
.data
 IID_ID2D1Factory           IID _IID_ID2D1Factory
 IID_IDWriteFactory         IID _IID_IDWriteFactory
 IID_IWICImagingFactory     IID _IID_IWICImagingFactory
 CLSID_WICImagingFactory    IID _CLSID_WICImagingFactory
 IID_IShellItemImageFactory IID _IID_IShellItemImageFactory
endif
