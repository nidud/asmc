ifndef _UXTHEME_H_
_UXTHEME_H_ equ <>

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


include commctrl.inc
include SpecStrings.inc

ifndef THEMEAPI
if NOT defined(_UXTHEME_)
else
endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
MAX_THEMECOLOR		equ 64
MAX_THEMESIZE		equ 64
endif

HTHEME typedef HANDLE

if (NTDDI_VERSION GE NTDDI_WIN7)
;BOOL
BeginPanningFeedback proto WINAPI \
		  hwnd: HWND

;BOOL
UpdatePanningFeedback proto WINAPI \
		  hwnd: HWND,
  lTotalOverpanOffsetX: LONG,
  lTotalOverpanOffsetY: LONG,
	    fInInertia: BOOL


;BOOL
EndPanningFeedback proto WINAPI \
		  hwnd: HWND,
	  fAnimateBack: BOOL

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

DEFINE_ENUM_FLAG_OPERATORS(TA_PROPERTY_FLAG);

GetThemeAnimationProperty proto WINAPI \
		hTheme: HTHEME,
	 iStoryboardId: int_t,
	     iTargetId: int_t,
	     eProperty: TA_PROPERTY,
	    pvProperty: ptr VOID,
		cbSize: DWORD,
	    pcbSizeOut: ptr DWORD


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

DEFINE_ENUM_FLAG_OPERATORS(TA_TRANSFORM_FLAG);

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

GetThemeAnimationTransform proto WINAPI \
		hTheme: HTHEME,
	 iStoryboardId: int_t,
	     iTargetId: int_t,
      dwTransformIndex: DWORD,
	    pTransform: ptr TA_TRANSFORM,
		cbSize: DWORD,
	    pcbSizeOut: ptr DWORD


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

GetThemeTimingFunction proto WINAPI \
		hTheme: HTHEME,
     iTimingFunctionId: int_t,
       pTimingFunction: ptr TA_TIMINGFUNCTION,
		cbSize: DWORD,
	    pcbSizeOut: ptr DWORD

endif

OpenThemeData proto WINAPI \
		  hwnd: HWND,
	  pszClassList: LPCWSTR


OTD_FORCE_RECT_SIZING	equ 0x00000001
OTD_NONCLIENT		equ 0x00000002
OTD_VALIDBITS		equ OTD_FORCE_RECT_SIZING OR OTD_NONCLIENT

OpenThemeDataEx proto WINAPI \
		  hwnd: HWND,
	  pszClassList: LPCWSTR,
	       dwFlags: DWORD

CloseThemeData proto WINAPI \
		hTheme: HTHEME

DrawThemeBackground proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		 pRect: LPCRECT,
	     pClipRect: LPCRECT


DTBG_CLIPRECT		equ 0x00000001
DTBG_DRAWSOLID		equ 0x00000002
DTBG_OMITBORDER		equ 0x00000004
DTBG_OMITCONTENT	equ 0x00000008
DTBG_COMPUTINGREGION	equ 0x00000010
DTBG_MIRRORDC		equ 0x00000020
DTBG_NOMIRROR		equ 0x00000040
DTBG_VALIDBITS		equ (DTBG_CLIPRECT OR \
			     DTBG_DRAWSOLID OR \
			     DTBG_OMITBORDER OR \
			     DTBG_OMITCONTENT OR \
			     DTBG_COMPUTINGREGION OR \
			     DTBG_MIRRORDC)

DTBGOPTS		STRUC
dwSize			dd ?
dwFlags			dd ?
rcClip			RECT <>
DTBGOPTS		ENDS
PDTBGOPTS		typedef ptr DTBGOPTS

DrawThemeBackgroundEx proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		 pRect: LPCRECT,
	      pOptions: ptr DTBGOPTS


DTT_GRAYED		equ 0x00000001
DTT_FLAGS2VALIDBITS	equ (DTT_GRAYED)

DrawThemeText proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       pszText: LPCWSTR,
	       cchText: int_t,
	   dwTextFlags: DWORD,
	  dwTextFlags2: DWORD,
		 pRect: LPCRECT


GetThemeBackgroundContentRect proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	 pBoundingRect: LPCRECT,
	  pContentRect: LPRECT


GetThemeBackgroundExtent proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	  pContentRect: LPCRECT,
	   pExtentRect: LPRECT


GetThemeBackgroundRegion proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		 pRect: LPCRECT,
	       pRegion: ptr HRGN


.enum THEMESIZE {
    TS_MIN,
    TS_TRUE,
    TS_DRAW
    }

GetThemePartSize proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		   prc: LPCRECT,
		 eSize: THEMESIZE,
		   psz: ptr SIZE


GetThemeTextExtent proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       pszText: LPCWSTR,
	  cchCharCount: int_t,
	   dwTextFlags: DWORD,
	 pBoundingRect: LPCRECT,
	   pExtentRect: LPRECT


GetThemeTextMetrics proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		   ptm: ptr TEXTMETRICW



HTTB_BACKGROUNDSEG	equ 0x00000000
HTTB_FIXEDBORDER	equ 0x00000002
HTTB_CAPTION		equ 0x00000004
HTTB_RESIZINGBORDER_LEFT equ 0x00000010
HTTB_RESIZINGBORDER_TOP equ 0x00000020
HTTB_RESIZINGBORDER_RIGHT equ 0x00000040
HTTB_RESIZINGBORDER_BOTTOM equ 0x00000080
HTTB_RESIZINGBORDER	equ (HTTB_RESIZINGBORDER_LEFT OR \
			     HTTB_RESIZINGBORDER_TOP OR \
			     HTTB_RESIZINGBORDER_RIGHT)
HTTB_SIZINGTEMPLATE	equ 0x00000100
HTTB_SYSTEMSIZINGMARGINS equ 0x00000200

HitTestThemeBackground proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	     dwOptions: DWORD,
		 pRect: LPCRECT,
		  hrgn: HRGN,
		ptTest: POINT,
	 pwHitTestCode: ptr WORD

DrawThemeEdge proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	     pDestRect: LPCRECT,
		 uEdge: UINT,
		uFlags: UINT,
	  pContentRect: LPRECT

DrawThemeIcon proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
		 pRect: LPCRECT,
		  himl: HIMAGELIST,
	   iImageIndex: int_t

IsThemePartDefined proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t

IsThemeBackgroundPartiallyTransparent proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t

GetThemeColor proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		pColor: ptr COLORREF

GetThemeMetric proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 piVal: ptr int_t

GetThemeString proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
	       pszBuff: LPWSTR,
       cchMaxBuffChars: int_t

GetThemeBool proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 pfVal: ptr BOOL

GetThemeInt proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 piVal: ptr int_t

GetThemeEnumValue proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 piVal: ptr int_t

GetThemePosition proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		pPoint: ptr POINT

GetThemeFont proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 pFont: ptr LOGFONTW

GetThemeRect proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		 pRect: LPRECT

MARGINS			STRUC
cxLeftWidth		int_t ?
cxRightWidth		int_t ?
cyTopHeight		int_t ?
cyBottomHeight		int_t ?
MARGINS			ENDS
PMARGINS		typedef ptr MARGINS

GetThemeMargins proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
		   prc: LPCRECT,
	      pMargins: ptr MARGINS


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

GetThemeIntList proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
	      pIntList: ptr INTLIST


.enum PROPERTYORIGIN {
    PO_STATE,
    PO_PART,
    PO_CLASS,
    PO_GLOBAL,
    PO_NOTFOUND
    }

GetThemePropertyOrigin proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
	       pOrigin: ptr PROPERTYORIGIN

SetWindowTheme proto WINAPI \
		  hwnd: HWND,
	 pszSubAppName: LPCWSTR,
	  pszSubIdList: LPCWSTR


GetThemeFilename proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
      pszThemeFileName: LPWSTR,
       cchMaxBuffChars: int_t

GetThemeSysColor proto WINAPI \
		hTheme: HTHEME,
	      iColorId: int_t

GetThemeSysColorBrush proto WINAPI \
		hTheme: HTHEME,
	      iColorId: int_t

GetThemeSysBool proto WINAPI \
		hTheme: HTHEME,
	       iBoolId: int_t

GetThemeSysSize proto WINAPI \
		hTheme: HTHEME,
	       iSizeId: int_t

GetThemeSysFont proto WINAPI \
		hTheme: HTHEME,
	       iFontId: int_t,
		   plf: ptr LOGFONTW

GetThemeSysString proto WINAPI \
		hTheme: HTHEME,
	     iStringId: int_t,
	 pszStringBuff: LPWSTR,
     cchMaxStringChars: int_t

GetThemeSysInt proto WINAPI \
		hTheme: HTHEME,
		iIntId: int_t,
	       piValue: ptr int_t

IsThemeActive proto WINAPI

IsAppThemed proto WINAPI

GetWindowTheme proto WINAPI \
		  hwnd: HWND


ETDT_DISABLE		equ 0x00000001
ETDT_ENABLE		equ 0x00000002
ETDT_USETABTEXTURE	equ 0x00000004

ETDT_ENABLETAB		equ (ETDT_ENABLE OR ETDT_USETABTEXTURE)

if (NTDDI_VERSION GE NTDDI_VISTA)
ETDT_USEAEROWIZARDTABTEXTURE equ 0x00000008

ETDT_ENABLEAEROWIZARDTAB equ (ETDT_ENABLE OR ETDT_USEAEROWIZARDTABTEXTURE)
ETDT_VALIDBITS		equ (ETDT_DISABLE OR \
			     ETDT_ENABLE OR \
			     ETDT_USETABTEXTURE OR \
			     ETDT_USEAEROWIZARDTABTEXTURE)
endif

EnableThemeDialogTexture proto WINAPI \
		  hwnd: HWND,
	       dwFlags: DWORD

IsThemeDialogTextureEnabled proto WINAPI \
		  hwnd: HWND



STAP_ALLOW_NONCLIENT	equ (1UL SHL 0)
STAP_ALLOW_CONTROLS	equ (1UL SHL 1)
STAP_ALLOW_WEBCONTENT	equ (1UL SHL 2)
STAP_VALIDBITS		equ (STAP_ALLOW_NONCLIENT OR \
			     STAP_ALLOW_CONTROLS OR \
			     STAP_ALLOW_WEBCONTENT)

GetThemeAppProperties proto WINAPI

SetThemeAppProperties proto WINAPI \
	       dwFlags: DWORD


GetCurrentThemeName proto WINAPI \
      pszThemeFileName: LPWSTR,
       cchMaxNameChars: int_t,
	  pszColorBuff: LPWSTR,
      cchMaxColorChars: int_t,
	   pszSizeBuff: LPWSTR,
       cchMaxSizeChars: int_t


SZ_THDOCPROP_DISPLAYNAME equ <L"DisplayName">
SZ_THDOCPROP_CANONICALNAME equ <L"ThemeName">
SZ_THDOCPROP_TOOLTIP	equ <L"ToolTip">
SZ_THDOCPROP_AUTHOR	equ <L"author">

GetThemeDocumentationProperty proto WINAPI \
	  pszThemeName: LPCWSTR,
       pszPropertyName: LPCWSTR,
	  pszValueBuff: LPWSTR,
	cchMaxValChars: int_t


DrawThemeParentBackground proto WINAPI \
		  hwnd: HWND,
		   hdc: HDC,
		   prc: ptr RECT


EnableTheming proto WINAPI \
	       fEnable: BOOL


GBF_DIRECT		equ 0x00000001
GBF_COPY		equ 0x00000002
GBF_VALIDBITS		equ (GBF_DIRECT OR GBF_COPY)

if (NTDDI_VERSION GE NTDDI_VISTA)

DTPB_WINDOWDC		equ 0x00000001
DTPB_USECTLCOLORSTATIC	equ 0x00000002
DTPB_USEERASEBKGND	equ 0x00000004

DrawThemeParentBackgroundEx proto WINAPI \
		  hwnd: HWND,
		   hdc: HDC,
	       dwFlags: DWORD,
		   prc: ptr RECT



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
WTNCA_VALIDBITS		equ (WTNCA_NODRAWCAPTION OR \
			     WTNCA_NODRAWICON OR \
			     WTNCA_NOSYSMENU OR \
			     WTNCA_NOMIRRORHELP)

SetWindowThemeAttribute proto WINAPI \
		  hwnd: HWND,
	    eAttribute: WINDOWTHEMEATTRIBUTETYPE,
	   pvAttribute: PVOID,
	   cbAttribute: DWORD


SetWindowThemeNonClientAttributes proto :HWND, :DWORD, :DWORD {

    .new wta:WTA_OPTIONS

    mov wta.dwFlags,r8d
    mov wta.dwMask,edx
    SetWindowThemeAttribute(rcx, WTA_NONCLIENT, addr wta, sizeof(wta))
    }

endif

CALLBACK(DTT_CALLBACK_PROC, :HDC, :LPWSTR, :int_t, :LPRECT, :UINT, :LPARAM)

DTT_TEXTCOLOR		equ (1UL SHL 0)
DTT_BORDERCOLOR		equ (1UL SHL 1)
DTT_SHADOWCOLOR		equ (1UL SHL 2)
DTT_SHADOWTYPE		equ (1UL SHL 3)
DTT_SHADOWOFFSET	equ (1UL SHL 4)
DTT_BORDERSIZE		equ (1UL SHL 5)
DTT_FONTPROP		equ (1UL SHL 6)
DTT_COLORPROP		equ (1UL SHL 7)
DTT_STATEID		equ (1UL SHL 8)
DTT_CALCRECT		equ (1UL SHL 9)
DTT_APPLYOVERLAY	equ (1UL SHL 10)
DTT_GLOWSIZE		equ (1UL SHL 11)
DTT_CALLBACK		equ (1UL SHL 12)
DTT_COMPOSITED		equ (1UL SHL 13)
DTT_VALIDBITS		equ (DTT_TEXTCOLOR OR \
			     DTT_BORDERCOLOR OR \
			     DTT_SHADOWCOLOR OR \
			     DTT_SHADOWTYPE OR \
			     DTT_SHADOWOFFSET OR \
			     DTT_BORDERSIZE OR \
			     DTT_FONTPROP OR \
			     DTT_COLORPROP OR \
			     DTT_STATEID OR \
			     DTT_CALCRECT OR \
			     DTT_APPLYOVERLAY OR \
			     DTT_GLOWSIZE OR \
			     DTT_COMPOSITED)

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

DrawThemeTextEx proto WINAPI \
		hTheme: HTHEME,
		   hdc: HDC,
	       iPartId: int_t,
	      iStateId: int_t,
	       pszText: LPCWSTR,
	       cchText: int_t,
	   dwTextFlags: DWORD,
		 pRect: LPRECT,
	      pOptions: ptr DTTOPTS


GetThemeBitmap proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
	       dwFlags: ULONG,
	      phBitmap: ptr HBITMAP


GetThemeStream proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	      iStateId: int_t,
	       iPropId: int_t,
	     ppvStream: ptr VOID,
	     pcbStream: ptr DWORD,
		 hInst: HINSTANCE


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

BeginBufferedPaint proto WINAPI \
	     hdcTarget: HDC,
	     prcTarget: ptr RECT,
	      dwFormat: BP_BUFFERFORMAT,
	  pPaintParams: ptr BP_PAINTPARAMS,
		  phdc: ptr HDC


EndBufferedPaint proto WINAPI \
	hBufferedPaint: HPAINTBUFFER,
	 fUpdateTarget: BOOL


GetBufferedPaintTargetRect proto WINAPI \
	hBufferedPaint: HPAINTBUFFER,
		   prc: ptr RECT

GetBufferedPaintTargetDC proto WINAPI \
	hBufferedPaint: HPAINTBUFFER


GetBufferedPaintDC proto WINAPI \
	hBufferedPaint: HPAINTBUFFER


GetBufferedPaintBits proto WINAPI \
	hBufferedPaint: HPAINTBUFFER,
	     ppbBuffer: ptr RGBQUAD,
		pcxRow: ptr int_t


BufferedPaintClear proto WINAPI \
	hBufferedPaint: HPAINTBUFFER,
		   prc: ptr RECT


BufferedPaintSetAlpha proto WINAPI \
	hBufferedPaint: HPAINTBUFFER,
		   prc: ptr RECT,
		 alpha: BYTE


BufferedPaintMakeOpaque macro hBufferedPaint, prc
	exitm<BufferedPaintSetAlpha(hBufferedPaint, prc, 255)>
	endm

BufferedPaintStopAllAnimations proto WINAPI \
		  hwnd: HWND

HANIMATIONBUFFER typedef HANDLE

BeginBufferedAnimation proto WINAPI \
		  hwnd: HWND,
	     hdcTarget: HDC,
	     prcTarget: ptr RECT,
	      dwFormat: BP_BUFFERFORMAT,
	  pPaintParams: ptr BP_PAINTPARAMS,
      pAnimationParams: ptr BP_ANIMATIONPARAMS,
	      phdcFrom: ptr HDC,
		phdcTo: ptr HDC


EndBufferedAnimation proto WINAPI \
	  hbpAnimation: HANIMATIONBUFFER,
	 fUpdateTarget: BOOL


BufferedPaintRenderAnimation proto WINAPI \
		  hwnd: HWND,
	     hdcTarget: HDC


GetThemeTransitionDuration proto WINAPI \
		hTheme: HTHEME,
	       iPartId: int_t,
	  iStateIdFrom: int_t,
	    iStateIdTo: int_t,
	       iPropId: int_t,
	   pdwDuration: ptr DWORD


endif
endif
endif

