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

FT_Outline_GetInsideBorder proto \
               outline: ptr FT_Outline


FT_Outline_GetOutsideBorder proto \
               outline: ptr FT_Outline

FT_Stroker_New proto \
               library: FT_Library,
              astroker: ptr FT_Stroker

FT_Stroker_Set proto \
               stroker: FT_Stroker,
                radius: FT_Fixed,
              line_cap: FT_Stroker_LineCap,
             line_join: FT_Stroker_LineJoin,
           miter_limit: FT_Fixed

FT_Stroker_Rewind proto \
               stroker: FT_Stroker

FT_Stroker_ParseOutline proto \
               stroker: FT_Stroker,
               outline: ptr FT_Outline,
                opened: FT_Bool

FT_Stroker_BeginSubPath proto \
               stroker: FT_Stroker,
                    to: ptr FT_Vector,
                  open: FT_Bool

FT_Stroker_EndSubPath proto \
               stroker: FT_Stroker

FT_Stroker_LineTo proto \
               stroker: FT_Stroker,
                    to: ptr FT_Vector

FT_Stroker_ConicTo proto \
               stroker: FT_Stroker,
               control: ptr FT_Vector,
                    to: ptr FT_Vector

FT_Stroker_CubicTo proto \
               stroker: FT_Stroker,
              control1: ptr FT_Vector,
              control2: ptr FT_Vector,
                    to: ptr FT_Vector

FT_Stroker_GetBorderCounts proto \
               stroker: FT_Stroker,
                border: FT_StrokerBorder,
           anum_points: ptr FT_UInt,
         anum_contours: ptr FT_UInt

FT_Stroker_ExportBorder proto \
               stroker: FT_Stroker,
                border: FT_StrokerBorder,
               outline: ptr FT_Outline

FT_Stroker_GetCounts proto \
               stroker: FT_Stroker,
           anum_points: ptr FT_UInt,
         anum_contours: ptr FT_UInt

FT_Stroker_Export proto \
               stroker: FT_Stroker,
               outline: ptr FT_Outline

FT_Stroker_Done proto \
               stroker: FT_Stroker

FT_Glyph_Stroke proto \
                pglyph: ptr FT_Glyph,
               stroker: FT_Stroker,
               destroy: FT_Bool

FT_Glyph_StrokeBorder proto \
                pglyph: ptr FT_Glyph,
               stroker: FT_Stroker,
                inside: FT_Bool,
               destroy: FT_Bool

endif
