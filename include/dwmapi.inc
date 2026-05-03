.pragma list(push, 0)

ifndef _DWMAPI_H_
define _DWMAPI_H_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef MILCORE_KERNEL_COMPONENT
include wtypes.inc
include uxtheme.inc
endif

.pragma comment(lib, dwmapi)

.pragma pack(push, 1)

DWM_BB_ENABLE		equ 0x00000001
DWM_BB_BLURREGION	equ 0x00000002
DWM_BB_TRANSITIONONMAXIMIZED equ 0x00000004

DWM_BLURBEHIND		STRUC
dwFlags			dd ?
fEnable			BOOL ?
hRgnBlur		HRGN ?
fTransitionOnMaximized	BOOL ?
DWM_BLURBEHIND		ENDS
PDWM_BLURBEHIND		typedef ptr DWM_BLURBEHIND

.enum DWMWINDOWATTRIBUTE {
    DWMWA_NCRENDERING_ENABLED = 1,
    DWMWA_NCRENDERING_POLICY,
    DWMWA_TRANSITIONS_FORCEDISABLED,
    DWMWA_ALLOW_NCPAINT,
    DWMWA_CAPTION_BUTTON_BOUNDS,
    DWMWA_NONCLIENT_RTL_LAYOUT,
    DWMWA_FORCE_ICONIC_REPRESENTATION,
    DWMWA_FLIP3D_POLICY,
    DWMWA_EXTENDED_FRAME_BOUNDS,
    DWMWA_HAS_ICONIC_BITMAP,
    DWMWA_DISALLOW_PEEK,
    DWMWA_EXCLUDED_FROM_PEEK,
    DWMWA_CLOAK,
    DWMWA_CLOAKED,
    DWMWA_FREEZE_REPRESENTATION,
    DWMWA_LAST
    }

.enum DWMNCRENDERINGPOLICY {
    DWMNCRP_USEWINDOWSTYLE,
    DWMNCRP_DISABLED,
    DWMNCRP_ENABLED,
    DWMNCRP_LAST
    }

.enum DWMFLIP3DWINDOWPOLICY {
    DWMFLIP3D_DEFAULT,
    DWMFLIP3D_EXCLUDEBELOW,
    DWMFLIP3D_EXCLUDEABOVE,
    DWMFLIP3D_LAST
    }

DWM_CLOAKED_APP		equ 0x00000001
DWM_CLOAKED_SHELL	equ 0x00000002
DWM_CLOAKED_INHERITED	equ 0x00000004

HTHUMBNAIL		typedef HANDLE
PHTHUMBNAIL		typedef ptr HTHUMBNAIL

DWM_TNP_RECTDESTINATION equ 0x00000001
DWM_TNP_RECTSOURCE	equ 0x00000002
DWM_TNP_OPACITY		equ 0x00000004
DWM_TNP_VISIBLE		equ 0x00000008
DWM_TNP_SOURCECLIENTAREAONLY equ 0x00000010


DWM_THUMBNAIL_PROPERTIES STRUC
dwFlags			dd ?
rcDestination		RECT <>
rcSource		RECT <>
opacity			db ?
fVisible		BOOL ?
fSourceClientAreaOnly	BOOL ?
DWM_THUMBNAIL_PROPERTIES ENDS
PDWM_THUMBNAIL_PROPERTIES typedef ptr DWM_THUMBNAIL_PROPERTIES

DWM_FRAME_COUNT		typedef ULONGLONG
QPC_TIME		typedef ULONGLONG

UNSIGNED_RATIO		STRUC
uiNumerator		UINT32 ?
uiDenominator		UINT32 ?
UNSIGNED_RATIO		ENDS

DWM_TIMING_INFO		STRUC
cbSize			UINT32 ?
rateRefresh		UNSIGNED_RATIO <>
qpcRefreshPeriod	QPC_TIME ?
rateCompose		UNSIGNED_RATIO <>
qpcVBlank		QPC_TIME ?
cRefresh		DWM_FRAME_COUNT ?
cDXRefresh		UINT ?
qpcCompose		QPC_TIME ?
cFrame			DWM_FRAME_COUNT ?
cDXPresent		UINT ?
cRefreshFrame		DWM_FRAME_COUNT ?
cFrameSubmitted		DWM_FRAME_COUNT ?
cDXPresentSubmitted	UINT ?
cFrameConfirmed		DWM_FRAME_COUNT ?
cDXPresentConfirmed	UINT ?
cRefreshConfirmed	DWM_FRAME_COUNT ?
cDXRefreshConfirmed	UINT ?
cFramesLate		DWM_FRAME_COUNT ?
cFramesOutstanding	UINT ?
cFrameDisplayed		DWM_FRAME_COUNT ?
qpcFrameDisplayed	QPC_TIME ?
cRefreshFrameDisplayed	DWM_FRAME_COUNT ?
cFrameComplete		DWM_FRAME_COUNT ?
qpcFrameComplete	QPC_TIME ?
cFramePending		DWM_FRAME_COUNT ?
qpcFramePending		QPC_TIME ?
cFramesDisplayed	DWM_FRAME_COUNT ?
cFramesComplete		DWM_FRAME_COUNT ?
cFramesPending		DWM_FRAME_COUNT ?
cFramesAvailable	DWM_FRAME_COUNT ?
cFramesDropped		DWM_FRAME_COUNT ?
cFramesMissed		DWM_FRAME_COUNT ?
cRefreshNextDisplayed	DWM_FRAME_COUNT ?
cRefreshNextPresented	DWM_FRAME_COUNT ?
cRefreshesDisplayed	DWM_FRAME_COUNT ?
cRefreshesPresented	DWM_FRAME_COUNT ?
cRefreshStarted		DWM_FRAME_COUNT ?
cPixelsReceived		ULONGLONG ?
cPixelsDrawn		ULONGLONG ?
cBuffersEmpty		DWM_FRAME_COUNT ?
DWM_TIMING_INFO		ENDS

.enum DWM_SOURCE_FRAME_SAMPLING {
    DWM_SOURCE_FRAME_SAMPLING_POINT,
    DWM_SOURCE_FRAME_SAMPLING_COVERAGE,
    DWM_SOURCE_FRAME_SAMPLING_LAST
    }

c_DwmMaxQueuedBuffers	equ 8
c_DwmMaxMonitors	equ 16
c_DwmMaxAdapters	equ 16

DWM_PRESENT_PARAMETERS	STRUC
cbSize			UINT32 ?
fQueue			BOOL ?
cRefreshStart		DWM_FRAME_COUNT ?
cBuffer			UINT ?
fUseSourceRate		BOOL ?
rateSource		UNSIGNED_RATIO <>
cRefreshesPerFrame	UINT ?
eSampling		DWM_SOURCE_FRAME_SAMPLING ?
DWM_PRESENT_PARAMETERS	ENDS

DWM_FRAME_DURATION_DEFAULT equ -1

DwmDefWindowProc proto WINAPI :HWND, :UINT, :WPARAM, :LPARAM, :ptr
DwmEnableBlurBehindWindow proto WINAPI :HWND, :ptr

DWM_EC_DISABLECOMPOSITION equ 0
DWM_EC_ENABLECOMPOSITION equ 1

DwmEnableComposition proto WINAPI :UINT

DwmEnableMMCSS proto WINAPI :BOOL
DwmExtendFrameIntoClientArea proto WINAPI :HWND, :ptr
DwmGetColorizationColor proto WINAPI :ptr, :ptr
DwmGetCompositionTimingInfo proto WINAPI :HWND, :ptr
DwmGetWindowAttribute proto WINAPI :HWND, :DWORD, :ptr, :DWORD
DwmIsCompositionEnabled proto WINAPI :ptr
DwmModifyPreviousDxFrameDuration proto WINAPI :HWND, :SINT, :BOOL
DwmQueryThumbnailSourceSize proto WINAPI :HTHUMBNAIL, :PSIZE
DwmRegisterThumbnail proto WINAPI :HWND, :HWND, :PHTHUMBNAIL
DwmSetDxFrameDuration proto WINAPI :HWND, :SINT
DwmSetPresentParameters proto WINAPI :HWND, :ptr
DwmSetWindowAttribute proto WINAPI :HWND, :DWORD, :ptr, :DWORD
DwmUnregisterThumbnail proto WINAPI :HTHUMBNAIL
DwmUpdateThumbnailProperties proto WINAPI :HTHUMBNAIL, :ptr

if(_WIN32_WINNT GE 0x0601)

DWM_SIT_DISPLAYFRAME	equ 0x00000001

DwmSetIconicThumbnail proto WINAPI :HWND, :HBITMAP, :DWORD
DwmSetIconicLivePreviewBitmap proto WINAPI :HWND, :HBITMAP, :ptr, :DWORD
DwmInvalidateIconicBitmaps proto WINAPI :HWND
endif
DwmAttachMilContent proto WINAPI :HWND
DwmDetachMilContent proto WINAPI :HWND
DwmFlush proto WINAPI

ifndef MILCORE_KERNEL_COMPONENT
ifndef _MIL_MATRIX3X2D_DEFINED

MilMatrix3x2D		STRUC
S_11			DOUBLE ?
S_12			DOUBLE ?
S_21			DOUBLE ?
S_22			DOUBLE ?
X			DOUBLE ?
Y			DOUBLE ?
MilMatrix3x2D		ENDS

_MIL_MATRIX3X2D_DEFINED equ 1
endif

ifndef MILCORE_MIL_MATRIX3X2D_COMPAT_TYPEDEF
MIL_MATRIX3X2D		typedef MilMatrix3x2D
MILCORE_MIL_MATRIX3X2D_COMPAT_TYPEDEF equ 1
endif

DwmGetGraphicsStreamTransformHint proto WINAPI :UINT, :ptr
DwmGetGraphicsStreamClient proto WINAPI :UINT, :ptr
endif
DwmGetTransportAttributes proto WINAPI :ptr, :ptr, :ptr

.enum DWMTRANSITION_OWNEDWINDOW_TARGET {
    DWMTRANSITION_OWNEDWINDOW_NULL	    = -1,
    DWMTRANSITION_OWNEDWINDOW_REPOSITION    = 0,
    }

DwmTransitionOwnedWindow proto WINAPI :HWND, :DWMTRANSITION_OWNEDWINDOW_TARGET

if (NTDDI_VERSION GE NTDDI_WIN8)

.enum GESTURE_TYPE {
    GT_PEN_TAP			= 0,
    GT_PEN_DOUBLETAP		= 1,
    GT_PEN_RIGHTTAP		= 2,
    GT_PEN_PRESSANDHOLD		= 3,
    GT_PEN_PRESSANDHOLDABORT	= 4,
    GT_TOUCH_TAP		= 5,
    GT_TOUCH_DOUBLETAP		= 6,
    GT_TOUCH_RIGHTTAP		= 7,
    GT_TOUCH_PRESSANDHOLD	= 8,
    GT_TOUCH_PRESSANDHOLDABORT	= 9,
    GT_TOUCH_PRESSANDTAP	= 10,
    }

DwmRenderGesture proto WINAPI :GESTURE_TYPE, :UINT, :ptr, :ptr
DwmTetherContact proto WINAPI :DWORD, :BOOL, :POINT

.enum DWM_SHOWCONTACT {
    DWMSC_DOWN	    = 0x00000001,
    DWMSC_UP	    = 0x00000002,
    DWMSC_DRAG	    = 0x00000004,
    DWMSC_HOLD	    = 0x00000008,
    DWMSC_PENBARREL = 0x00000010,
    DWMSC_NONE	    = 0x00000000,
    DWMSC_ALL	    = 0xFFFFFFFF
    }

DwmShowContact proto WINAPI :DWORD, :DWM_SHOWCONTACT

endif ;; NTDDI_WIN8

.pragma pack(pop)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; _DWMAPI_H_

.pragma list(pop)

