ifndef FTOUTLN_H_
define FTOUTLN_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Outline_Decompose proto :ptr, :ptr, :ptr
FT_Outline_New proto :FT_Library, :FT_UInt, :FT_Int, :ptr
FT_Outline_Done proto :FT_Library, :ptr
FT_Outline_Check proto :ptr
FT_Outline_Get_CBox proto :ptr, :ptr
FT_Outline_Translate proto  :ptr, :FT_Pos, :FT_Pos
FT_Outline_Copy proto :ptr, :ptr
FT_Outline_Transform proto :ptr, :ptr
FT_Outline_Embolden proto :ptr, :FT_Pos
FT_Outline_EmboldenXY proto :ptr, :FT_Pos, :FT_Pos
FT_Outline_Reverse proto :ptr
FT_Outline_Get_Bitmap proto :FT_Library, :ptr, :ptr
FT_Outline_Render proto :FT_Library, :ptr, :ptr

.enum FT_Orientation {
    FT_ORIENTATION_TRUETYPE   = 0,
    FT_ORIENTATION_POSTSCRIPT = 1,
    FT_ORIENTATION_FILL_RIGHT = FT_ORIENTATION_TRUETYPE,
    FT_ORIENTATION_FILL_LEFT  = FT_ORIENTATION_POSTSCRIPT,
    FT_ORIENTATION_NONE
    }

FT_Outline_Get_Orientation proto :ptr

endif
