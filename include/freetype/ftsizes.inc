ifndef FTSIZES_H_
define FTSIZES_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_New_Size proto \
                  face: FT_Face,
                  size: ptr FT_Size

FT_Done_Size proto \
                  size: FT_Size

FT_Activate_Size proto \
                  size: FT_Size

endif
