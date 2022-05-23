ifndef FTADVANC_H_
define FTADVANC_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_ADVANCE_FLAG_FAST_ONLY  0x20000000

FT_Get_Advance proto \
                  face: FT_Face,
                gindex: FT_UInt,
            load_flags: FT_Int32,
              padvance: ptr FT_Fixed

FT_Get_Advances proto \
                  face: FT_Face,
                 start: FT_UInt,
                 count: FT_UInt,
            load_flags: FT_Int32,
             padvances: ptr FT_Fixed

endif
