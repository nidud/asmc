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
v			real4 3*3 dup(?)
MAGTRANSFORM		ENDS
PMAGTRANSFORM		typedef ptr MAGTRANSFORM

MAGIMAGEHEADER		STRUC
width			UINT ?
height			UINT ?
format			GUID <> ; WICPixelFormatGUID <>
stride			UINT ?
offs			UINT ?
cbSize			size_t ?
MAGIMAGEHEADER		ENDS
PMAGIMAGEHEADER		typedef ptr MAGIMAGEHEADER

MAGCOLOREFFECT		STRUC
transform		real4 5*5 dup(?)
MAGCOLOREFFECT		ENDS
PMAGCOLOREFFECT		typedef ptr MAGCOLOREFFECT

CALLBACK(MagImageScalingCallback)

MagInitialize proto WINAPI
MagUninitialize proto WINAPI

MagSetWindowSource proto WINAPI :HWND, :RECT
MagGetWindowSource proto WINAPI :HWND, :ptr
MagSetWindowTransform proto WINAPI :HWND, :PMAGTRANSFORM
MagGetWindowTransform proto WINAPI :HWND, :PMAGTRANSFORM
MagSetWindowFilterList proto WINAPI :HWND, :DWORD, :SINT, :ptr
MagGetWindowFilterList proto WINAPI :HWND, :ptr, :SINT, :ptr
MagSetImageScalingCallback proto WINAPI :HWND, :MagImageScalingCallback
MagGetImageScalingCallback proto WINAPI :HWND
MagSetColorEffect proto WINAPI :HWND, :PMAGCOLOREFFECT
MagGetColorEffect proto WINAPI :HWND, :PMAGCOLOREFFECT
MagSetFullscreenTransform proto WINAPI :real4, :SINT, :SINT
MagGetFullscreenTransform proto WINAPI :ptr, :ptr, :ptr
MagSetFullscreenColorEffect proto WINAPI :PMAGCOLOREFFECT
MagGetFullscreenColorEffect proto WINAPI :PMAGCOLOREFFECT
MagSetInputTransform proto WINAPI :BOOL, :LPRECT, :LPRECT
MagGetInputTransform proto WINAPI :ptr, :LPRECT, :LPRECT
MagShowSystemCursor proto WINAPI :BOOL

endif

endif
