ifndef FTPARAMS_H_
define FTPARAMS_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_FAMILY FT_MAKE_TAG( 'i', 'g', 'p', 'f' )
define FT_PARAM_TAG_IGNORE_PREFERRED_FAMILY FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_FAMILY
define FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_SUBFAMILY FT_MAKE_TAG( 'i', 'g', 'p', 's' )
define FT_PARAM_TAG_IGNORE_PREFERRED_SUBFAMILY FT_PARAM_TAG_IGNORE_TYPOGRAPHIC_SUBFAMILY
define FT_PARAM_TAG_INCREMENTAL FT_MAKE_TAG( 'i', 'n', 'c', 'r' )
define FT_PARAM_TAG_IGNORE_SBIX FT_MAKE_TAG( 'i', 's', 'b', 'x' )
define FT_PARAM_TAG_LCD_FILTER_WEIGHTS FT_MAKE_TAG( 'l', 'c', 'd', 'f' )
define FT_PARAM_TAG_RANDOM_SEED FT_MAKE_TAG( 's', 'e', 'e', 'd' )
define FT_PARAM_TAG_STEM_DARKENING FT_MAKE_TAG( 'd', 'a', 'r', 'k' )
define FT_PARAM_TAG_UNPATENTED_HINTING FT_MAKE_TAG( 'u', 'n', 'p', 'a' )

endif
