ifndef FTGZIP_H_
define FTGZIP_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Stream_OpenGzip proto :FT_Stream, :FT_Stream
FT_Gzip_Uncompress proto :FT_Memory, :ptr, :ptr, :ptr, :FT_ULong

endif
