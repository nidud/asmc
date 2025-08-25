ifndef FTADVANC_H_
define FTADVANC_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_ADVANCE_FLAG_FAST_ONLY  0x20000000

FT_Get_Advance proto :FT_Face, :FT_UInt, :FT_Int32, :ptr
FT_Get_Advances proto :FT_Face, :FT_UInt, :FT_UInt, :FT_Int32, :ptr

endif
