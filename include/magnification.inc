ifndef _INC_MAGNIFIER
define _INC_MAGNIFIER

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __wincodec_h__
include wincodec.inc
endif

.pragma comment(lib, Magnification)

ifdef _WIN32

WC_MAGNIFIERA		equ <"Magnifier">
WC_MAGNIFIERW		equ <L"Magnifier">

ifdef _UNICODE
WC_MAGNIFIER		equ <WC_MAGNIFIERW>
else
WC_MAGNIFIER		equ <WC_MAGNIFIERA>
endif

else
WC_MAGNIFIER		equ <"Magnifier">
endif

MS_SHOWMAGNIFIEDCURSOR	equ 0x0001
MS_CLIPAROUNDCURSOR	equ 0x0002
MS_INVERTCOLORS		equ 0x0004


MW_FILTERMODE_EXCLUDE	equ 0
MW_FILTERMODE_INCLUDE	equ 1

MAGTRANSFORM		STRUC
v			real4 3 dup(?)
MAGTRANSFORM		ENDS
PMAGTRANSFORM		typedef ptr MAGTRANSFORM

MAGIMAGEHEADER		STRUC
width			UINT ?
height			UINT ?
format			WICPixelFormatGUID <>
stride			UINT ?
offs			UINT ?
cbSize			SIZE_T ?
MAGIMAGEHEADER		ENDS
PMAGIMAGEHEADER		typedef ptr MAGIMAGEHEADER

MAGCOLOREFFECT		STRUC
transform		real4 5 dup(?)
MAGCOLOREFFECT		ENDS
PMAGCOLOREFFECT		typedef ptr MAGCOLOREFFECT

CALLBACK(MagImageScalingCallback)

MagInitialize proto WINAPI
MagUninitialize proto WINAPI

MagSetWindowSource proto WINAPI \
		  hwnd: HWND,
		  rect: RECT

MagGetWindowSource proto WINAPI \
		  hwnd: HWND,
		 pRect: ptr RECT

MagSetWindowTransform proto WINAPI \
		  hwnd: HWND,
	    pTransform: PMAGTRANSFORM

MagGetWindowTransform proto WINAPI \
		  hwnd: HWND,
	    pTransform: PMAGTRANSFORM

MagSetWindowFilterList proto WINAPI \
		  hwnd: HWND,
	  dwFilterMode: DWORD,
		 count: SINT,
		 pHWND: ptr HWND

MagGetWindowFilterList proto WINAPI \
		  hwnd: HWND,
	 pdwFilterMode: ptr DWORD,
		 count: SINT,
		 pHWND: ptr HWND

MagSetImageScalingCallback proto WINAPI \
		  hwnd: HWND,
	      callback: MagImageScalingCallback

MagGetImageScalingCallback proto WINAPI \
		  hwnd: HWND

MagSetColorEffect proto WINAPI \
		  hwnd: HWND,
	       pEffect: PMAGCOLOREFFECT

MagGetColorEffect proto WINAPI \
		  hwnd: HWND,
	       pEffect: PMAGCOLOREFFECT

MagSetFullscreenTransform proto WINAPI \
	      magLevel: real4,
	       xOffset: SINT,
	       yOffset: SINT

MagGetFullscreenTransform proto WINAPI \
	     pMagLevel: ptr real4,
	      pxOffset: ptr SINT,
	      pyOffset: ptr SINT

MagSetFullscreenColorEffect proto WINAPI \
	       pEffect: PMAGCOLOREFFECT

MagGetFullscreenColorEffect proto WINAPI \
	       pEffect: PMAGCOLOREFFECT

MagSetInputTransform proto WINAPI \
	      fEnabled: BOOL,
	   pRectSource: LPRECT,
	     pRectDest: LPRECT

MagGetInputTransform proto WINAPI \
	     pfEnabled: ptr BOOL,
	   pRectSource: LPRECT,
	     pRectDest: LPRECT

MagShowSystemCursor proto WINAPI \
	   fShowCursor: BOOL


endif

endif
