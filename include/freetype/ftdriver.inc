ifndef FTDRIVER_H_
define FTDRIVER_H_

include freetype/freetype.inc
include freetype/ftparams.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_HINTING_FREETYPE  0
define FT_HINTING_ADOBE	    1

define FT_CFF_HINTING_FREETYPE	FT_HINTING_FREETYPE
define FT_CFF_HINTING_ADOBE	FT_HINTING_ADOBE

define TT_INTERPRETER_VERSION_35  35
define TT_INTERPRETER_VERSION_38  38
define TT_INTERPRETER_VERSION_40  40

define FT_AUTOHINTER_SCRIPT_NONE   0
define FT_AUTOHINTER_SCRIPT_LATIN  1
define FT_AUTOHINTER_SCRIPT_CJK	   2
define FT_AUTOHINTER_SCRIPT_INDIC  3

FT_Prop_GlyphToScriptMap STRUC
face			FT_Face ?
map			ptr FT_UShort ?
FT_Prop_GlyphToScriptMap ENDS

FT_Prop_IncreaseXHeight STRUC
face			FT_Face ?
limit			FT_UInt ?
FT_Prop_IncreaseXHeight ENDS

endif
