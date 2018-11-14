ifndef _GDIPLUSPIXELFORMATS_H
_GDIPLUSPIXELFORMATS_H equ <>

ARGB			typedef DWORD
ARGB64			typedef DWORDLONG

ALPHA_SHIFT		equ 24
RED_SHIFT		equ 16
GREEN_SHIFT		equ 8
BLUE_SHIFT		equ 0
ALPHA_MASK		equ (0xff SHL ALPHA_SHIFT)

PixelFormat		typedef SDWORD

PixelFormatIndexed	equ 0x00010000
PixelFormatGDI		equ 0x00020000
PixelFormatAlpha	equ 0x00040000
PixelFormatPAlpha	equ 0x00080000
PixelFormatExtended	equ 0x00100000
PixelFormatCanonical	equ 0x00200000

PixelFormatUndefined	equ 0
PixelFormatDontCare	equ 0

PixelFormat1bppIndexed	equ (1 OR ( 1 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat4bppIndexed	equ (2 OR ( 4 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat8bppIndexed	equ (3 OR ( 8 SHL 8) OR PixelFormatIndexed OR PixelFormatGDI)
PixelFormat16bppGrayScale equ (4 OR (16 SHL 8) OR PixelFormatExtended)
PixelFormat16bppRGB555	equ (5 OR (16 SHL 8) OR PixelFormatGDI)
PixelFormat16bppRGB565	equ (6 OR (16 SHL 8) OR PixelFormatGDI)
PixelFormat16bppARGB1555 equ (7 OR (16 SHL 8) OR PixelFormatAlpha OR PixelFormatGDI)
PixelFormat24bppRGB	equ (8 OR (24 SHL 8) OR PixelFormatGDI)
PixelFormat32bppRGB	equ (9 OR (32 SHL 8) OR PixelFormatGDI)
PixelFormat32bppARGB	equ (10 OR (32 SHL 8) OR PixelFormatAlpha OR PixelFormatGDI OR PixelFormatCanonical)
PixelFormat32bppPARGB	equ (11 OR (32 SHL 8) OR PixelFormatAlpha OR PixelFormatPAlpha OR PixelFormatGDI)
PixelFormat48bppRGB	equ (12 OR (48 SHL 8) OR PixelFormatExtended)
PixelFormat64bppARGB	equ (13 OR (64 SHL 8) OR PixelFormatAlpha OR PixelFormatCanonical OR PixelFormatExtended)
PixelFormat64bppPARGB	equ (14 OR (64 SHL 8) OR PixelFormatAlpha OR PixelFormatPAlpha OR PixelFormatExtended)
PixelFormat32bppCMYK	equ (15 OR (32 SHL 8))
PixelFormatMax		equ 16

if (GDIPVER GE 0x0110)

PaletteType		typedef SDWORD
PaletteTypeCustom	equ 0
PaletteTypeOptimal	equ 1
PaletteTypeFixedBW	equ 2
PaletteTypeFixedHalftone8 equ 3
PaletteTypeFixedHalftone27 equ 4
PaletteTypeFixedHalftone64 equ 5
PaletteTypeFixedHalftone125 equ 6
PaletteTypeFixedHalftone216 equ 7
PaletteTypeFixedHalftone252 equ 8
PaletteTypeFixedHalftone256 equ 9

DitherType		typedef SDWORD
DitherTypeNone		equ 0
DitherTypeSolid		equ 1
DitherTypeOrdered4x4	equ 2
DitherTypeOrdered8x8	equ 3
DitherTypeOrdered16x16	equ 4
DitherTypeSpiral4x4	equ 5
DitherTypeSpiral8x8	equ 6
DitherTypeDualSpiral4x4 equ 7
DitherTypeDualSpiral8x8 equ 8
DitherTypeErrorDiffusion equ 9
DitherTypeMax		equ 10
endif

PaletteFlags		typedef SDWORD
PaletteFlagsHasAlpha	equ 0x0001
PaletteFlagsGrayScale	equ 0x0002
PaletteFlagsHalftone	equ 0x0004

ColorPalette		STRUC
Flags			UINT ?
Count			UINT ?
Entries			ARGB ?
ColorPalette		ENDS

endif
