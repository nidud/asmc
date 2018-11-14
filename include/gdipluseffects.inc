ifndef _GDIPLUSEFFECTS_HPP
_GDIPLUSEFFECTS_HPP equ <>

if (GDIPVER GE 0x0110)

DEFINE_GUID(BlurEffectGuid, 0x633c80a4, 0x1843, 0x482b, 0x9e, 0xf2, 0xbe, 0x28, 0x34, 0xc5, 0xfd, 0xd4 )
DEFINE_GUID(SharpenEffectGuid, 0x63cbf3ee, 0xc526, 0x402c, 0x8f, 0x71, 0x62, 0xc5, 0x40, 0xbf, 0x51, 0x42 )
DEFINE_GUID(ColorMatrixEffectGuid, 0x718f2615, 0x7933, 0x40e3, 0xa5, 0x11, 0x5f, 0x68, 0xfe, 0x14, 0xdd, 0x74 )
DEFINE_GUID(ColorLUTEffectGuid, 0xa7ce72a9, 0xf7f,  0x40d7, 0xb3, 0xcc, 0xd0, 0xc0, 0x2d, 0x5c, 0x32, 0x12 )
DEFINE_GUID(BrightnessContrastEffectGuid, 0xd3a1dbe1, 0x8ec4, 0x4c17, 0x9f, 0x4c, 0xea, 0x97, 0xad, 0x1c, 0x34, 0x3d )
DEFINE_GUID(HueSaturationLightnessEffectGuid, 0x8b2dd6c3, 0xeb07, 0x4d87, 0xa5, 0xf0, 0x71, 0x8, 0xe2, 0x6a, 0x9c, 0x5f )
DEFINE_GUID(LevelsEffectGuid, 0x99c354ec, 0x2a31, 0x4f3a, 0x8c, 0x34, 0x17, 0xa8, 0x3, 0xb3, 0x3a, 0x25 )
DEFINE_GUID(TintEffectGuid, 0x1077af00, 0x2848, 0x4441, 0x94, 0x89, 0x44, 0xad, 0x4c, 0x2d, 0x7a, 0x2c )
DEFINE_GUID(ColorBalanceEffectGuid, 0x537e597d, 0x251e, 0x48da, 0x96, 0x64, 0x29, 0xca, 0x49, 0x6b, 0x70, 0xf8 )
DEFINE_GUID(RedEyeCorrectionEffectGuid, 0x74d29d05, 0x69a4, 0x4266, 0x95, 0x49, 0x3c, 0xc5, 0x28, 0x36, 0xb6, 0x32 )
DEFINE_GUID(ColorCurveEffectGuid, 0xdd6a0022, 0x58e4, 0x4a67, 0x9d, 0x9b, 0xd4, 0x8e, 0xb8, 0x81, 0xa5, 0x3d )


SharpenParams		STRUC
radius			float ?
amount			float ?
SharpenParams		ENDS

BlurParams		STRUC
radius			float ?
expandEdge		BOOL ?
BlurParams		ENDS

BrightnessContrastParams STRUC
brightnessLevel		SINT ?
contrastLevel		SINT ?
BrightnessContrastParams ENDS

RedEyeCorrectionParams	STRUC
numberOfAreas		UINT ?
areas			LPRECT ?
RedEyeCorrectionParams	ENDS

HueSaturationLightnessParams STRUC
hueLevel		SINT ?
saturationLevel		SINT ?
lightnessLevel		SINT ?
HueSaturationLightnessParams ENDS

TintParams		STRUC
hue			SINT ?
amount			SINT ?
TintParams		ENDS

LevelsParams		STRUC
highlight		SINT ?
midtone			SINT ?
shadow			SINT ?
LevelsParams		ENDS

ColorBalanceParams	STRUC
cyanRed			SINT ?
magentaGreen		SINT ?
yellowBlue		SINT ?
ColorBalanceParams	ENDS

ColorLUTParams		STRUC
lutB			ColorChannelLUT ?
lutG			ColorChannelLUT ?
lutR			ColorChannelLUT ?
lutA			ColorChannelLUT ?
ColorLUTParams		ENDS

CurveAdjustments	typedef SDWORD
AdjustExposure		equ 0
AdjustDensity		equ 1
AdjustContrast		equ 2
AdjustHighlight		equ 3
AdjustShadow		equ 4
AdjustMidtone		equ 5
AdjustWhiteSaturation	equ 6
AdjustBlackSaturation	equ 7

CurveChannel		typedef SDWORD
CurveChannelAll		equ 0
CurveChannelRed		equ 1
CurveChannelGreen	equ 2
CurveChannelBlue	equ 3

ColorCurveParams	STRUC
adjustment		CurveAdjustments ?
channel			CurveChannel ?
adjustValue		SINT ?
ColorCurveParams	ENDS

;Status __stdcall
GdipCreateEffect proto WINAPI \
		  guid: ptr GUID,
		effect: ptr
GdipDeleteEffect proto WINAPI \
		effect: ptr
GdipGetEffectParameterSize proto WINAPI \
		effect: ptr,
		 _size: ptr
GdipSetEffectParameters proto WINAPI \
		effect: ptr,
		params: ptr,
		 _size: ptr
GdipGetEffectParameters proto WINAPI \
		effect: ptr,
		 _size: ptr,
		params: ptr

ifndef _GDIPLUSEFFECTS_EXCLUDEOBJECTS
endif ;; _GDIPLUSEFFECTS_EXCLUDEEOBJECTS
endif ;;(GDIPVER GE 0x0110)

endif


