ifndef FTPFR_H_
define FTPFR_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Get_PFR_Metrics proto :FT_Face, :ptr, :ptr, :ptr, :ptr
FT_Get_PFR_Kerning proto :FT_Face, :FT_UInt, :FT_UInt, :ptr
FT_Get_PFR_Advance proto :FT_Face, :FT_UInt, :ptr

endif
