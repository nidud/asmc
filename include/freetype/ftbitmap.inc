ifndef FTBITMAP_H_
define FTBITMAP_H_

include freetype/freetype.inc
include freetype/ftcolor.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Bitmap_Init proto :ptr
FT_Bitmap_New proto :ptr
FT_Bitmap_Copy proto :FT_Library, :ptr, :ptr
FT_Bitmap_Embolden proto :FT_Library, :ptr, :FT_Pos, :FT_Pos
FT_Bitmap_Convert proto :FT_Library, :ptr, :ptr, :FT_Int
FT_Bitmap_Blend proto :FT_Library, :ptr, :FT_Vector, :ptr, :ptr, :FT_Color
FT_GlyphSlot_Own_Bitmap proto :FT_GlyphSlot
FT_Bitmap_Done proto :FT_Library, :ptr

endif
