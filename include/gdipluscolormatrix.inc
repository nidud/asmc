ifndef _GDIPLUSCOLORMATRIX_H
_GDIPLUSCOLORMATRIX_H equ <>

if (GDIPVER GE 0x0110)

;ColorChannelLUT[256]	 typedef BYTE

HistogramFormat		typedef SDWORD
HistogramFormatARGB	equ 0
HistogramFormatPARGB	equ 1
HistogramFormatRGB	equ 2
HistogramFormatGray	equ 3
HistogramFormatB	equ 4
HistogramFormatG	equ 5
HistogramFormatR	equ 6
HistogramFormatA	equ 7
endif ;;(GDIPVER GE 0x0110)

ColorMatrix		STRUC
m			REAL 5*5 dup(?)
ColorMatrix		ENDS

ColorMatrixFlags	typedef SDWORD
ColorMatrixFlagsDefault equ 0
ColorMatrixFlagsSkipGrays equ 1
ColorMatrixFlagsAltGray equ 2

ColorAdjustType		typedef SDWORD
ColorAdjustTypeDefault	equ 0
ColorAdjustTypeBitmap	equ 1
ColorAdjustTypeBrush	equ 2
ColorAdjustTypePen	equ 3
ColorAdjustTypeText	equ 4
ColorAdjustTypeCount	equ 5
ColorAdjustTypeAny	equ 6

ColorMap		STRUC
oldColor		dd ?
newColor		dd ?
ColorMap		ENDS

endif
