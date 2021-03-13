;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/DirectCompositionEffects
;

WINVER       equ 0x0700
_WIN32_WINNT equ 0x0700

include windows.inc
include atlbase.inc
include d3d11_1.inc
include d2d1_1.inc
include dcomp.inc
include dwmapi.inc
include math.inc

IDS_FONT_TYPEFACE           equ <"Segoe UI Light">
IDS_FONT_HEIGHT_LOGO        equ 0
IDS_FONT_HEIGHT_TITLE       equ 50
IDS_FONT_HEIGHT_DESCRIPTION equ 22

.enum VIEW_STATE { ZOOMEDOUT, ZOOMEDIN, }
.enum ACTION_TYPE { ZOOMOUT, ZOOMIN, }

LPID2D1Factory1 typedef ptr ID2D1Factory1
LPID2D1Device typedef ptr ID2D1Device
LPID2D1DeviceContext typedef ptr ID2D1DeviceContext
LPIDCompositionDevice typedef ptr IDCompositionDevice
LPIDCompositionTarget typedef ptr IDCompositionTarget
LPIDCompositionVisual typedef ptr IDCompositionVisual
LPIDCompositionSurface typedef ptr IDCompositionSurface
LPIDCompositionEffectGroup typedef ptr IDCompositionEffectGroup

.class CApplication

    _hinstance HINSTANCE ?

    _fontTypeface WCHAR 32 dup(?)
    _fontHeightLogo int_t ?
    _fontHeightTitle int_t ?
    _fontHeightDescription int_t ?

    _hwnd HWND ?

    _tileSize int_t ?

    _windowWidth int_t ?
    _windowHeight int_t ?

    _d3d11Device LPID3D11Device ?
    _d3d11DeviceContext LPID3D11DeviceContext ?

    _d2d1Factory LPID2D1Factory1 ?

    _d2d1Device LPID2D1Device ?
    _d2d1DeviceContext LPID2D1DeviceContext ?

    _device LPIDCompositionDevice ?
    _target LPIDCompositionTarget ?
    _visual LPIDCompositionVisual ?
    _visualLeft LPIDCompositionVisual ?
    _visualLeftChild LPIDCompositionVisual 4 dup(?)
    _visualRight LPIDCompositionVisual ?

    _surfaceLeftChild LPIDCompositionSurface 4 dup(?)

    _effectGroupLeft LPIDCompositionEffectGroup ?
    _effectGroupLeftChild LPIDCompositionEffectGroup 4 dup(?)
    _effectGroupRight LPIDCompositionEffectGroup ?

    _currentVisual int_t ?
    _state VIEW_STATE ?
    _actionType ACTION_TYPE ?


    WindowProc proto :HWND, :UINT, :WPARAM, :LPARAM

    CApplication proc :HINSTANCE, :ptr CApplicationVtbl
    Release proc

    Run proc

    BeforeEnteringMessageLoop proc
    EnterMessageLoop proc
    AfterLeavingMessageLoop proc

    CreateApplicationWindow proc
    ShowApplicationWindow proc
    DestroyApplicationWindow proc
    CreateD2D1Factory proc
    DestroyD2D1Factory proc
    CreateD2D1Device proc
    DestroyD2D1Device proc
    CreateD3D11Device proc
    DestroyD3D11Device proc
    CreateDCompositionDevice proc
    DestroyDCompositionVisualTree proc
    CreateDCompositionVisualTree proc
    DestroyDCompositionDevice proc

    CreateSurface proc :int_t, :float, :float, :float, :ptr ptr IDCompositionSurface
    CreateTranslateTransform proc :float, :float, :float, :ptr ptr IDCompositionTranslateTransform3D
    CreateTranslateTransform2 proc :float, :float, :float, :float, :float, :float, :float, :float, :ptr ptr IDCompositionTranslateTransform3D
    CreateScaleTransform proc :float, :float, :float, :float, :float, :float, :ptr ptr IDCompositionScaleTransform3D
    CreateScaleTransform2 proc :float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :ptr ptr IDCompositionScaleTransform3D
    CreateRotateTransform proc :float, :float, :float, :float, :float, :float, :float, :ptr ptr IDCompositionRotateTransform3D
    CreateRotateTransform2 proc :float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :ptr ptr IDCompositionRotateTransform3D
    CreatePerspectiveTransform proc :float, :float, :float, :ptr ptr IDCompositionMatrixTransform3D
    CreateLinearAnimation proc :float, :float, :float, :float, :ptr ptr IDCompositionAnimation

    SetEffectOnVisuals proc
    SetEffectOnVisualLeft proc
    SetEffectOnVisualLeftChildren proc
    SetEffectOnVisualRight proc

    ZoomOut proc
    ZoomIn proc

    OnKeyDown proc :WPARAM
    OnLeftButton proc
    OnClose proc
    OnDestroy proc
    OnPaint proc

    UpdateVisuals proc :int_t, :int_t

    .ends
