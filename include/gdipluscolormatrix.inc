ifndef _GDIPLUSCOLORMATRIX_H
define _GDIPLUSCOLORMATRIX_H

if (GDIPVER GE 0x0110)

;;----------------------------------------------------------------------------
;; Color channel look up table (LUT)
;;----------------------------------------------------------------------------

ColorChannelLUT STRUC
Colors		db 256 dup(?)
ColorChannelLUT ENDS

;;----------------------------------------------------------------------------
;; Per-channel Histogram for 8bpp images.
;;----------------------------------------------------------------------------

.enum HistogramFormat {
    HistogramFormatARGB,
    HistogramFormatPARGB,
    HistogramFormatRGB,
    HistogramFormatGray,
    HistogramFormatB,
    HistogramFormatG,
    HistogramFormatR,
    HistogramFormatA
    }
endif

;;----------------------------------------------------------------------------
;; Color matrix
;;----------------------------------------------------------------------------

ColorMatrix	STRUC
m		REAL 5*5 dup(?)
ColorMatrix	ENDS

;;----------------------------------------------------------------------------
;; Color Matrix flags
;;----------------------------------------------------------------------------

.enum ColorMatrixFlags {
    ColorMatrixFlagsDefault,
    ColorMatrixFlagsSkipGrays,
    ColorMatrixFlagsAltGray
    }

;;----------------------------------------------------------------------------
;; Color Adjust Type
;;----------------------------------------------------------------------------

.enum ColorAdjustType {
    ColorAdjustTypeDefault,
    ColorAdjustTypeBitmap,
    ColorAdjustTypeBrush,
    ColorAdjustTypePen,
    ColorAdjustTypeText,
    ColorAdjustTypeCount,
    ColorAdjustTypeAny	    ;; Reserved
    }

;;----------------------------------------------------------------------------
;; Color Map
;;----------------------------------------------------------------------------

ColorMap		STRUC
oldColor		Color <>
newColor		Color <>
ColorMap		ENDS

endif
