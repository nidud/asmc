ifndef FTGASP_H_
define FTGASP_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_GASP_NO_TABLE               -1
define FT_GASP_DO_GRIDFIT           0x01
define FT_GASP_DO_GRAY              0x02
define FT_GASP_SYMMETRIC_GRIDFIT    0x04
define FT_GASP_SYMMETRIC_SMOOTHING  0x08

FT_Get_Gasp proto \
                  face: FT_Face,
                  ppem: FT_UInt

endif
