.pragma list(push, 0)
ifndef _GDIPLUS_H
_GDIPLUS_H equ <>
include windef.inc

INT16           typedef sword
UINT16          typedef word
ifndef GDIPVER
GDIPVER         equ 0x0110;0x0100
endif

.pragma comment(lib, gdiplus)

.pragma pack(push, 8)

include GdiplusMem.inc
include GdiplusBase.inc
include GdiplusEnums.inc
include GdiplusTypes.inc
include GdiplusInit.inc
include GdiplusPixelFormats.inc
include GdiplusColor.inc
include GdiplusMetaHeader.inc
include GdiplusImaging.inc
include GdiplusColorMatrix.inc
if (GDIPVER GE 0x0110)
include GdiplusEffects.inc
endif
include GdiplusGpStubs.inc
include GdiplusHeaders.inc
include GdiplusFlat.inc
include GdiplusImageAttributes.inc
include GdiplusMatrix.inc
include GdiplusBrush.inc
include GdiplusPen.inc
include GdiplusStringFormat.inc
include GdiplusPath.inc
include GdiplusLineCaps.inc
include GdiplusGraphics.inc
include GdiplusMetafile.inc
include GdiplusCachedBitmap.inc
include GdiplusRegion.inc
include GdiplusFontCollection.inc
include GdiplusFontFamily.inc
include GdiplusFont.inc
include GdiplusBitmap.inc
include GdiplusImageCodec.inc

.pragma pack(pop)
endif
.pragma list(pop)
