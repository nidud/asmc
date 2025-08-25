ifndef FTCID_H_
define FTCID_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Get_CID_Registry_Ordering_Supplement proto :FT_Face, :ptr, :ptr, :ptr
FT_Get_CID_Is_Internally_CID_Keyed proto :FT_Face, :ptr
FT_Get_CID_From_Glyph_Index proto :FT_Face, :FT_UInt, :ptr

endif
