ifndef FTOUTLN_H_
define FTOUTLN_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Outline_Decompose proto \
               outline: ptr FT_Outline,
        func_interface: ptr FT_Outline_Funcs,
                  user: ptr

FT_Outline_New proto \
               library: FT_Library,
             numPoints: FT_UInt,
           numContours: FT_Int,
             anoutline: ptr FT_Outline

FT_Outline_Done proto \
               library: FT_Library,
               outline: ptr FT_Outline

FT_Outline_Check proto \
               outline: ptr FT_Outline

FT_Outline_Get_CBox proto \
               outline: ptr FT_Outline,
                 acbox: ptr FT_BBox

FT_Outline_Translate proto \
               outline: ptr FT_Outline,
               xOffset: FT_Pos,
               yOffset: FT_Pos

FT_Outline_Copy proto \
                source: ptr FT_Outline,
                target: ptr FT_Outline

FT_Outline_Transform proto \
               outline: ptr FT_Outline,
                matrix: ptr FT_Matrix

FT_Outline_Embolden proto \
               outline: ptr FT_Outline,
              strength: FT_Pos

FT_Outline_EmboldenXY proto \
               outline: ptr FT_Outline,
             xstrength: FT_Pos,
             ystrength: FT_Pos

FT_Outline_Reverse proto \
               outline: ptr FT_Outline

FT_Outline_Get_Bitmap proto \
               library: FT_Library,
               outline: ptr FT_Outline,
               abitmap: ptr FT_Bitmap

FT_Outline_Render proto \
               library: FT_Library,
               outline: ptr FT_Outline,
                params: ptr FT_Raster_Params

.enum FT_Orientation {
    FT_ORIENTATION_TRUETYPE   = 0,
    FT_ORIENTATION_POSTSCRIPT = 1,
    FT_ORIENTATION_FILL_RIGHT = FT_ORIENTATION_TRUETYPE,
    FT_ORIENTATION_FILL_LEFT  = FT_ORIENTATION_POSTSCRIPT,
    FT_ORIENTATION_NONE
    }

FT_Outline_Get_Orientation proto \
               outline: ptr FT_Outline

endif
