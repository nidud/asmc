ifndef _UXTHEME_H_
define _UXTHEME_H_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include commctrl.inc
include specstrings.inc

.pragma comment(lib, uxtheme)

if (NTDDI_VERSION GE NTDDI_VISTA)
MAX_THEMECOLOR		equ 64
MAX_THEMESIZE		equ 64
endif

HTHEME typedef HANDLE

if (NTDDI_VERSION GE NTDDI_WIN7)

BeginPanningFeedback proto WINAPI :HWND
UpdatePanningFeedback proto WINAPI :HWND, :LONG, :LONG, :BOOL
EndPanningFeedback proto WINAPI :HWND, :BOOL

endif

if (NTDDI_VERSION GE NTDDI_WIN8)

.enum TA_PROPERTY {
    TAP_FLAGS,
    TAP_TRANSFORMCOUNT,
    TAP_STAGGERDELAY,
    TAP_STAGGERDELAYCAP,
    TAP_STAGGERDELAYFACTOR,
    TAP_ZORDER,
    }

.enum TA_PROPERTY_FLAG {
    TAPF_NONE		    = 0x0,
    TAPF_HASSTAGGER	    = 0x1,
    TAPF_ISRTLAWARE	    = 0x2,
    TAPF_ALLOWCOLLECTION    = 0x4,
    TAPF_HASBACKGROUND	    = 0x8,
    TAPF_HASPERSPECTIVE	    = 0x10,
    }

GetThemeAnimationProperty proto WINAPI :HTHEME, :sdword, :sdword, :TA_PROPERTY, :ptr, :DWORD, :ptr

.enum TA_TRANSFORM_TYPE {
    TATT_TRANSLATE_2D,
    TATT_SCALE_2D,
    TATT_OPACITY,
    TATT_CLIP,
    }

.enum TA_TRANSFORM_FLAG {
    TATF_NONE		     = 0x0,
    TATF_TARGETVALUES_USER   = 0x1,
    TATF_HASINITIALVALUES    = 0x2,
    TATF_HASORIGINVALUES     = 0x4,
    }

.pragma pack(push, 8)

TA_TRANSFORM		STRUC
eTransformType		TA_TRANSFORM_TYPE ?
dwTimingFunctionId	dd ?
dwStartTime		dd ?
dwDurationTime		dd ?
eFlags			TA_TRANSFORM_FLAG ?
TA_TRANSFORM		ENDS
PTA_TRANSFORM		typedef ptr TA_TRANSFORM

TA_TRANSFORM_2D		STRUC
header			TA_TRANSFORM <>
rX			real4 ?
rY			real4 ?
rInitialX		real4 ?
rInitialY		real4 ?
rOriginX		real4 ?
rOriginY		real4 ?
TA_TRANSFORM_2D		ENDS
PTA_TRANSFORM_2D	typedef ptr TA_TRANSFORM_2D

TA_TRANSFORM_OPACITY	STRUC
header			TA_TRANSFORM <>
rOpacity		real4 ?
rInitialOpacity		real4 ?
TA_TRANSFORM_OPACITY	ENDS
PTA_TRANSFORM_OPACITY	typedef ptr TA_TRANSFORM_OPACITY

TA_TRANSFORM_CLIP	STRUC
header			TA_TRANSFORM <>
rLeft			real4 ?
rTop			real4 ?
rRight			real4 ?
rBottom			real4 ?
rInitialLeft		real4 ?
rInitialTop		real4 ?
rInitialRight		real4 ?
rInitialBottom		real4 ?
TA_TRANSFORM_CLIP	ENDS
PTA_TRANSFORM_CLIP	typedef ptr TA_TRANSFORM_CLIP

.pragma pack(pop)

GetThemeAnimationTransform proto WINAPI :HTHEME, :sdword, :sdword, :DWORD, : ptr, :DWORD, :ptr

.enum TA_TIMINGFUNCTION_TYPE {
    TTFT_UNDEFINED,
    TTFT_CUBIC_BEZIER,
    }

.pragma pack(push, 8)

TA_TIMINGFUNCTION	STRUC
eTimingFunctionType	TA_TIMINGFUNCTION_TYPE ?
TA_TIMINGFUNCTION	ENDS
PTA_TIMINGFUNCTION	typedef ptr TA_TIMINGFUNCTION

TA_CUBIC_BEZIER		STRUC
header			TA_TIMINGFUNCTION <>
rX0			real4 ?
rY0			real4 ?
rX1			real4 ?
rY1			real4 ?
TA_CUBIC_BEZIER		ENDS
PTA_CUBIC_BEZIER	typedef ptr TA_CUBIC_BEZIER

.pragma pack(pop)

GetThemeTimingFunction proto WINAPI :HTHEME, :sdword, :ptr, :DWORD, :ptr

endif

OpenThemeData proto WINAPI :HWND, :LPCWSTR

OTD_FORCE_RECT_SIZING	equ 0x00000001
OTD_NONCLIENT		equ 0x00000002
OTD_VALIDBITS		equ OTD_FORCE_RECT_SIZING OR OTD_NONCLIENT

OpenThemeDataEx proto WINAPI :HWND, :LPCWSTR, :DWORD
CloseThemeData proto WINAPI :HTHEME
DrawThemeBackground proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCRECT, :LPCRECT


DTBG_CLIPRECT		equ 0x00000001
DTBG_DRAWSOLID		equ 0x00000002
DTBG_OMITBORDER		equ 0x00000004
DTBG_OMITCONTENT	equ 0x00000008
DTBG_COMPUTINGREGION	equ 0x00000010
DTBG_MIRRORDC		equ 0x00000020
DTBG_NOMIRROR		equ 0x00000040
DTBG_VALIDBITS		equ (DTBG_CLIPRECT OR DTBG_DRAWSOLID OR DTBG_OMITBORDER OR DTBG_OMITCONTENT OR DTBG_COMPUTINGREGION OR DTBG_MIRRORDC)

DTBGOPTS		STRUC
dwSize			dd ?
dwFlags			dd ?
rcClip			RECT <>
DTBGOPTS		ENDS
PDTBGOPTS		typedef ptr DTBGOPTS

DrawThemeBackgroundEx proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :ptr, :ptr

DTT_GRAYED		equ 0x00000001
DTT_FLAGS2VALIDBITS	equ (DTT_GRAYED)

DrawThemeText proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCWSTR, :sdword, :DWORD, :DWORD, :ptr
GetThemeBackgroundContentRect proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :ptr, :ptr
GetThemeBackgroundExtent proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :ptr, :ptr
GetThemeBackgroundRegion proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :ptr, :ptr

.enum THEMESIZE {
    TS_MIN,
    TS_TRUE,
    TS_DRAW
    }

GetThemePartSize proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCRECT, :THEMESIZE, :ptr
GetThemeTextExtent proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCWSTR, :sdword, :DWORD, :LPCRECT, :LPRECT
GetThemeTextMetrics proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :ptr

HTTB_BACKGROUNDSEG	equ 0x00000000
HTTB_FIXEDBORDER	equ 0x00000002
HTTB_CAPTION		equ 0x00000004
HTTB_RESIZINGBORDER_LEFT equ 0x00000010
HTTB_RESIZINGBORDER_TOP equ 0x00000020
HTTB_RESIZINGBORDER_RIGHT equ 0x00000040
HTTB_RESIZINGBORDER_BOTTOM equ 0x00000080
HTTB_RESIZINGBORDER	equ (HTTB_RESIZINGBORDER_LEFT OR HTTB_RESIZINGBORDER_TOP OR HTTB_RESIZINGBORDER_RIGHT)
HTTB_SIZINGTEMPLATE	equ 0x00000100
HTTB_SYSTEMSIZINGMARGINS equ 0x00000200

HitTestThemeBackground proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :DWORD, :LPCRECT, :HRGN, :POINT, :ptr
DrawThemeEdge proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCRECT, :UINT, :UINT, :LPRECT
DrawThemeIcon proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCRECT, :HIMAGELIST, :sdword
IsThemePartDefined proto WINAPI :HTHEME, :sdword, :sdword
IsThemeBackgroundPartiallyTransparent proto WINAPI :HTHEME, :sdword, :sdword
GetThemeColor proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
GetThemeMetric proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :sdword, :ptr
GetThemeString proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :LPWSTR, :sdword
GetThemeBool proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
GetThemeInt proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
GetThemeEnumValue proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
GetThemePosition proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
GetThemeFont proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :sdword, :ptr
GetThemeRect proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :LPRECT

MARGINS			STRUC
cxLeftWidth		int_t ?
cxRightWidth		int_t ?
cyTopHeight		int_t ?
cyBottomHeight		int_t ?
MARGINS			ENDS
PMARGINS		typedef ptr MARGINS

GetThemeMargins proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :sdword, :LPCRECT, :ptr

if (NTDDI_VERSION GE NTDDI_VISTA)
MAX_INTLIST_COUNT	equ 402
else
MAX_INTLIST_COUNT	equ 10
endif

INTLIST			STRUC
iValueCount		int_t ?
iValues			int_t MAX_INTLIST_COUNT dup(?)
INTLIST			ENDS
PINTLIST		typedef ptr INTLIST

GetThemeIntList proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr

.enum PROPERTYORIGIN {
    PO_STATE,
    PO_PART,
    PO_CLASS,
    PO_GLOBAL,
    PO_NOTFOUND
    }

GetThemePropertyOrigin proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr
SetWindowTheme proto WINAPI :HWND, :LPCWSTR, :LPCWSTR
GetThemeFilename proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :LPWSTR, :sdword
GetThemeSysColor proto WINAPI :HTHEME, :sdword
GetThemeSysColorBrush proto WINAPI :HTHEME, :sdword
GetThemeSysBool proto WINAPI :HTHEME, :sdword
GetThemeSysSize proto WINAPI :HTHEME, :sdword
GetThemeSysFont proto WINAPI :HTHEME,:sdword, :ptr
GetThemeSysString proto WINAPI :HTHEME, :sdword, :LPWSTR, :sdword
GetThemeSysInt proto WINAPI :HTHEME, :sdword, :ptr
IsThemeActive proto WINAPI
IsAppThemed proto WINAPI
GetWindowTheme proto WINAPI :HWND

ETDT_DISABLE		equ 0x00000001
ETDT_ENABLE		equ 0x00000002
ETDT_USETABTEXTURE	equ 0x00000004
ETDT_ENABLETAB		equ (ETDT_ENABLE OR ETDT_USETABTEXTURE)

if (NTDDI_VERSION GE NTDDI_VISTA)
ETDT_USEAEROWIZARDTABTEXTURE equ 0x00000008
ETDT_ENABLEAEROWIZARDTAB equ (ETDT_ENABLE OR ETDT_USEAEROWIZARDTABTEXTURE)
ETDT_VALIDBITS		equ (ETDT_DISABLE OR ETDT_ENABLE OR ETDT_USETABTEXTURE OR ETDT_USEAEROWIZARDTABTEXTURE)
endif

EnableThemeDialogTexture proto WINAPI :HWND, :DWORD
IsThemeDialogTextureEnabled proto WINAPI :HWND

STAP_ALLOW_NONCLIENT	equ (1 SHL 0)
STAP_ALLOW_CONTROLS	equ (1 SHL 1)
STAP_ALLOW_WEBCONTENT	equ (1 SHL 2)
STAP_VALIDBITS		equ (STAP_ALLOW_NONCLIENT OR STAP_ALLOW_CONTROLS OR STAP_ALLOW_WEBCONTENT)

GetThemeAppProperties proto WINAPI
SetThemeAppProperties proto WINAPI :DWORD
GetCurrentThemeName proto WINAPI :LPWSTR, :sdword, :LPWSTR, :sdword, :LPWSTR, :sdword

SZ_THDOCPROP_DISPLAYNAME equ <L"DisplayName">
SZ_THDOCPROP_CANONICALNAME equ <L"ThemeName">
SZ_THDOCPROP_TOOLTIP	equ <L"ToolTip">
SZ_THDOCPROP_AUTHOR	equ <L"author">

GetThemeDocumentationProperty proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR, :sdword
DrawThemeParentBackground proto WINAPI :HWND, :HDC, :ptr
EnableTheming proto WINAPI :BOOL

GBF_DIRECT		equ 0x00000001
GBF_COPY		equ 0x00000002
GBF_VALIDBITS		equ (GBF_DIRECT OR GBF_COPY)

if (NTDDI_VERSION GE NTDDI_VISTA)

DTPB_WINDOWDC		equ 0x00000001
DTPB_USECTLCOLORSTATIC	equ 0x00000002
DTPB_USEERASEBKGND	equ 0x00000004

DrawThemeParentBackgroundEx proto WINAPI :HWND, :HDC, :DWORD, :ptr

.enum WINDOWTHEMEATTRIBUTETYPE {
    WTA_NONCLIENT = 1
    }

WTA_OPTIONS		STRUC
dwFlags			dd ?
dwMask			dd ?
WTA_OPTIONS		ENDS
PWTA_OPTIONS		typedef ptr WTA_OPTIONS

WTNCA_NODRAWCAPTION	equ 0x00000001
WTNCA_NODRAWICON	equ 0x00000002
WTNCA_NOSYSMENU		equ 0x00000004
WTNCA_NOMIRRORHELP	equ 0x00000008
WTNCA_VALIDBITS		equ (WTNCA_NODRAWCAPTION OR WTNCA_NODRAWICON OR WTNCA_NOSYSMENU OR WTNCA_NOMIRRORHELP)

SetWindowThemeAttribute proto WINAPI :HWND, :WINDOWTHEMEATTRIBUTETYPE, :PVOID, :DWORD

SetWindowThemeNonClientAttributes proto :HWND, :DWORD, :DWORD {
   .new wta:WTA_OPTIONS
    mov wta.dwFlags,r8d
    mov wta.dwMask,edx
    SetWindowThemeAttribute(rcx, WTA_NONCLIENT, addr wta, sizeof(wta))
    }

endif

CALLBACK(DTT_CALLBACK_PROC, :HDC, :LPWSTR, :sdword, :LPRECT, :UINT, :LPARAM)

DTT_TEXTCOLOR		equ (1 SHL 0)
DTT_BORDERCOLOR		equ (1 SHL 1)
DTT_SHADOWCOLOR		equ (1 SHL 2)
DTT_SHADOWTYPE		equ (1 SHL 3)
DTT_SHADOWOFFSET	equ (1 SHL 4)
DTT_BORDERSIZE		equ (1 SHL 5)
DTT_FONTPROP		equ (1 SHL 6)
DTT_COLORPROP		equ (1 SHL 7)
DTT_STATEID		equ (1 SHL 8)
DTT_CALCRECT		equ (1 SHL 9)
DTT_APPLYOVERLAY	equ (1 SHL 10)
DTT_GLOWSIZE		equ (1 SHL 11)
DTT_CALLBACK		equ (1 SHL 12)
DTT_COMPOSITED		equ (1 SHL 13)
DTT_VALIDBITS		equ (DTT_TEXTCOLOR OR DTT_BORDERCOLOR OR DTT_SHADOWCOLOR OR DTT_SHADOWTYPE OR DTT_SHADOWOFFSET OR DTT_BORDERSIZE OR DTT_FONTPROP OR DTT_COLORPROP OR DTT_STATEID OR DTT_CALCRECT OR DTT_APPLYOVERLAY OR DTT_GLOWSIZE OR DTT_COMPOSITED)

DTTOPTS			STRUC
dwSize			dd ?
dwFlags			dd ?
crText			COLORREF ?
crBorder		COLORREF ?
crShadow		COLORREF ?
iTextShadowType		int_t ?
ptShadowOffset		POINT <>
iBorderSize		int_t ?
iFontPropId		int_t ?
iColorPropId		int_t ?
iStateId		int_t ?
fApplyOverlay		BOOL ?
iGlowSize		int_t ?
pfnDrawTextCallback	DTT_CALLBACK_PROC ?
lParam			LPARAM ?
DTTOPTS			ENDS
PDTTOPTS		typedef ptr DTTOPTS

if (NTDDI_VERSION GE NTDDI_VISTA)

DrawThemeTextEx proto WINAPI :HTHEME, :HDC, :sdword, :sdword, :LPCWSTR, :sdword, :DWORD, :LPRECT, :ptr
GetThemeBitmap proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ULONG, :ptr
GetThemeStream proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :ptr, :ptr, :HINSTANCE
BufferedPaintInit proto WINAPI
BufferedPaintUnInit proto WINAPI

HPAINTBUFFER typedef HANDLE

.enum BP_BUFFERFORMAT {
    BPBF_COMPATIBLEBITMAP,
    BPBF_DIB,
    BPBF_TOPDOWNDIB,
    BPBF_TOPDOWNMONODIB
    }

BPBF_COMPOSITED		equ BPBF_TOPDOWNDIB

.enum BP_ANIMATIONSTYLE {
    BPAS_NONE,
    BPAS_LINEAR,
    BPAS_CUBIC,
    BPAS_SINE
    }

BP_ANIMATIONPARAMS	STRUC
cbSize			dd ?
dwFlags			dd ?
style			BP_ANIMATIONSTYLE ?
dwDuration		dd ?
BP_ANIMATIONPARAMS	ENDS
PBP_ANIMATIONPARAMS	typedef ptr BP_ANIMATIONPARAMS

BPPF_ERASE		equ 0x0001
BPPF_NOCLIP		equ 0x0002
BPPF_NONCLIENT		equ 0x0004

BP_PAINTPARAMS		STRUC
cbSize			dd ?
dwFlags			dd ?
prcExclude		LPRECT ?
pBlendFunction		LPBLENDFUNCTION ?
BP_PAINTPARAMS		ENDS
PBP_PAINTPARAMS		typedef ptr BP_PAINTPARAMS

BeginBufferedPaint proto WINAPI :HDC, :ptr, :BP_BUFFERFORMAT, :ptr, :ptr
EndBufferedPaint proto WINAPI :HPAINTBUFFER, :BOOL
GetBufferedPaintTargetRect proto WINAPI :HPAINTBUFFER, :ptr
GetBufferedPaintTargetDC proto WINAPI :HPAINTBUFFER
GetBufferedPaintDC proto WINAPI :HPAINTBUFFER
GetBufferedPaintBits proto WINAPI :HPAINTBUFFER, :ptr, :ptr
BufferedPaintClear proto WINAPI :HPAINTBUFFER, :ptr
BufferedPaintSetAlpha proto WINAPI :HPAINTBUFFER, :ptr, :BYTE
BufferedPaintMakeOpaque macro hBufferedPaint, prc
	exitm<BufferedPaintSetAlpha(hBufferedPaint, prc, 255)>
	endm

BufferedPaintStopAllAnimations proto WINAPI :HWND
HANIMATIONBUFFER typedef HANDLE
BeginBufferedAnimation proto WINAPI :HWND, :HDC, :ptr, :BP_BUFFERFORMAT, :ptr, :ptr, :ptr, :ptr
EndBufferedAnimation proto WINAPI :HANIMATIONBUFFER, :BOOL
BufferedPaintRenderAnimation proto WINAPI :HWND, :HDC
GetThemeTransitionDuration proto WINAPI :HTHEME, :sdword, :sdword, :sdword, :sdword, :ptr

endif
endif
endif

