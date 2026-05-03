ifndef FTOTVAL_H_
define FTOTVAL_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_VALIDATE_BASE  0x0100
define FT_VALIDATE_GDEF  0x0200
define FT_VALIDATE_GPOS  0x0400
define FT_VALIDATE_GSUB  0x0800
define FT_VALIDATE_JSTF  0x1000
define FT_VALIDATE_MATH  0x2000
define FT_VALIDATE_OT    ( FT_VALIDATE_BASE OR FT_VALIDATE_GDEF OR FT_VALIDATE_GPOS OR FT_VALIDATE_GSUB OR FT_VALIDATE_JSTF OR FT_VALIDATE_MATH )

FT_OpenType_Validate proto :FT_Face, :FT_UInt, :ptr, :ptr, :ptr, :ptr, :ptr
FT_OpenType_Free proto :FT_Face, :FT_Bytes

endif
