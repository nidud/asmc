ifndef FTBZIP2_H_
define FTBZIP2_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Stream_OpenBzip2 proto \
                stream: FT_Stream,
                source: FT_Stream


endif
