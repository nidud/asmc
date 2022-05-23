ifndef FTBITMAP_H_
define FTBITMAP_H_

include freetype/freetype.inc
include freetype/ftcolor.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Bitmap_Init proto \
               abitmap: ptr FT_Bitmap

FT_Bitmap_New proto \
               abitmap: ptr FT_Bitmap

FT_Bitmap_Copy proto \
               library: FT_Library,
                source: ptr FT_Bitmap,
                target: ptr FT_Bitmap

FT_Bitmap_Embolden proto \
               library: FT_Library,
                bitmap: ptr FT_Bitmap,
             xStrength: FT_Pos,
             yStrength: FT_Pos

FT_Bitmap_Convert proto \
               library: FT_Library,
                source: ptr FT_Bitmap,
                target: ptr FT_Bitmap,
             alignment: FT_Int

FT_Bitmap_Blend proto \
               library: FT_Library,
                source: ptr FT_Bitmap,
         source_offset: FT_Vector,
                target: ptr FT_Bitmap,
        atarget_offset: ptr FT_Vector,
                 color: FT_Color

FT_GlyphSlot_Own_Bitmap proto \
                  slot: FT_GlyphSlot

FT_Bitmap_Done proto \
               library: FT_Library,
                bitmap: ptr FT_Bitmap

endif
