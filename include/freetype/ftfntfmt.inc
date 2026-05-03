ifndef FTFNTFMT_H_
define FTFNTFMT_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Get_Font_Format proto \
                  face: FT_Face

FT_Get_X11_Font_Format proto \
                  face: FT_Face

endif
