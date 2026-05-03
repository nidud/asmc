ifndef FTSTROKE_H_
define FTSTROKE_H_

include freetype/ftoutln.inc
include freetype/ftglyph.inc

FT_Stroker              typedef ptr FT_StrokerRec

.enum FT_Stroker_LineJoin {
    FT_STROKER_LINEJOIN_ROUND          = 0,
    FT_STROKER_LINEJOIN_BEVEL          = 1,
    FT_STROKER_LINEJOIN_MITER_VARIABLE = 2,
    FT_STROKER_LINEJOIN_MITER          = FT_STROKER_LINEJOIN_MITER_VARIABLE,
    FT_STROKER_LINEJOIN_MITER_FIXED    = 3
    }

.enum FT_Stroker_LineCap {
    FT_STROKER_LINECAP_BUTT = 0,
    FT_STROKER_LINECAP_ROUND,
    FT_STROKER_LINECAP_SQUARE
    }

.enum FT_StrokerBorder {
    FT_STROKER_BORDER_LEFT = 0,
    FT_STROKER_BORDER_RIGHT
    }

FT_Outline_GetInsideBorder proto :ptr
FT_Outline_GetOutsideBorder proto :ptr
FT_Stroker_New proto :FT_Library, :ptr
FT_Stroker_Set proto :FT_Stroker, :FT_Fixed, :FT_Stroker_LineCap, :FT_Stroker_LineJoin, :FT_Fixed
FT_Stroker_Rewind proto :FT_Stroker
FT_Stroker_ParseOutline proto :FT_Stroker, :ptr, :FT_Bool
FT_Stroker_BeginSubPath proto :FT_Stroker, :ptr, :FT_Bool
FT_Stroker_EndSubPath proto :FT_Stroker
FT_Stroker_LineTo proto :FT_Stroker, :ptr
FT_Stroker_ConicTo proto :FT_Stroker, :ptr, :ptr
FT_Stroker_CubicTo proto :FT_Stroker, :ptr, :ptr, :ptr
FT_Stroker_GetBorderCounts proto :FT_Stroker, :FT_StrokerBorder, :ptr, :ptr
FT_Stroker_ExportBorder proto :FT_Stroker, :FT_StrokerBorder, :ptr
FT_Stroker_GetCounts proto :FT_Stroker, :ptr, :ptr
FT_Stroker_Export proto :FT_Stroker, :ptr
FT_Stroker_Done proto :FT_Stroker
FT_Glyph_Stroke proto :ptr, :FT_Stroker, :FT_Bool
FT_Glyph_StrokeBorder proto :ptr, :FT_Stroker, :FT_Bool, :FT_Bool

endif
