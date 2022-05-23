ifndef FTGZIP_H_
define FTGZIP_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Stream_OpenGzip proto \
                stream: FT_Stream,
                source: FT_Stream

FT_Gzip_Uncompress proto \
                memory: FT_Memory,
                output: ptr FT_Byte,
            output_len: ptr FT_ULong,
                 input: ptr FT_Byte,
             input_len: FT_ULong

endif
