ifndef FTCID_H_
define FTCID_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Get_CID_Registry_Ordering_Supplement proto \
                  face: FT_Face,
              registry: ptr char_t,
              ordering: ptr char_t,
            supplement: ptr FT_Int

FT_Get_CID_Is_Internally_CID_Keyed proto \
                  face: FT_Face,
                is_cid: ptr FT_Bool

FT_Get_CID_From_Glyph_Index proto \
                  face: FT_Face,
           glyph_index: FT_UInt,
                   cid: ptr FT_UInt

endif
