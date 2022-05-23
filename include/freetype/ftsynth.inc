ifndef FTSYNTH_H_
define FTSYNTH_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_GlyphSlot_Embolden proto \
                  slot: FT_GlyphSlot

FT_GlyphSlot_Oblique proto \
                  slot: FT_GlyphSlot

endif
